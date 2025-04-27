#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>
#include "VDinamico.h"
#include "Imagen.h"

/**
 * @brief Método que saca por consola el tiempo transcurrido con un objeto clock_t
 * @param reloj
 */
void consola_rlj(clock_t &reloj) {
    cout << "[Tiempo transcurrido: " << ((clock() - reloj) / (float) CLOCKS_PER_SEC) << " segs.]" << endl << endl;
}

/**
 * @brief Método auxiliar del tercer ejercicio para sacar por consola un dato de tipo imagen del vector
 * @param vDin es el vector dinámico cargado de imágenes
 * @param pos es la posición en la que supuestamente se encuentra la imagen
 * @param id es el identificador que tiene asociado la imagen
 */
void consolaPosImg(VDinamico<Imagen> &vDin, int pos, string id) {
    if (pos == -1)
        cout << "La imagen con Id " << id << "  no se ha podido encontrar en el vector." << endl;
    else if (vDin[pos].getId() == id)
        cout << "La imagen " << vDin[pos].getId() << " se encuentra en la posicion " << pos << " del vector." << endl;
    else
        cout << "La imagen con Id " << id << " no coincide con la del vector " << vDin[pos].getId() << "." << endl;
}

/**
 * @brief Ejecución principal del programa
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 8/10/2022
 * @return 0 si la ejecución fue exitosa. Cualquier otro número en cualquier otro caso.
 */
int main() {

    VDinamico<Imagen> vDin(256);

    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    std::string id = "";
    std::string email = "";
    std::string nombre = "";
    int tam = 0;
    int dia = 0;
    int mes = 0;
    int anno = 0;
    std::string etiquetas = "";

    is.open("../imagenes_v1.csv"); //carpeta de proyecto
    if (is.good()) {


        clock_t t_ini = clock();

        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                //formato de fila: id;email;nombre;tam;fecha;etiquetas

                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, email, ';');
                getline(columnas, nombre, ';');

                columnas >> tam;   //las secuencia numéricas se leen y trasforman directamente
                columnas.ignore(); //omitimos carácter ';' siguiente

                columnas >> dia;
                columnas.ignore();
                columnas >> mes;
                columnas.ignore();
                columnas >> anno;
                columnas.ignore();

                getline(columnas, etiquetas, ';');

                fila = "";
                columnas.clear();

                try {
                    Fecha fAux(dia, mes, anno);
                    Imagen ImgAux(id, email, nombre, tam, fAux, etiquetas);
                    vDin.insertar(ImgAux);
                } catch (exception &err) { //Captura la excepción del vector si la hubiera
                    cout << err.what() << endl;
                }
            }
        }

        is.close();

        std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    while(true){
        unsigned int elc = 0;
        cout << "Indique, del 1 al 4, un ejercicio a mostrar y pulse INTRO. Cualquier otro caracter terminará la ejcución." << endl;
        cout << "1 - Ordenar al reves y mostrar 50 imagenes del contenedor" << endl;
        cout << "2 - Ordenar normal (menor a mayor) y mostrar 50 imagenes del contenedor" << endl;
        cout << "3 - Buscar imagenes segun su identificador." << endl;
        cout << "4 - Descargar (vector nuevo) y borrar las imagenes del usuario magdalen_upton99@gmail.com" << endl;
        cin >> elc;
        if(!(1<=elc && elc<=4))
            break;
        clock_t rlj_ejercicio = clock();
        switch (elc) {
            case 1:
                try{
                    vDin.ordenarRev();
                    for (int i = 1; i <= 50; ++i)
                        cout << "|" << i << "| " << vDin[i].to_string() << endl;
                } catch (exception &err) {
                    cout << err.what() << endl;
                }
                break;
            case 2:
                try{
                    vDin.ordenar();
                    for (int i = 1; i <= 50; ++i)
                        cout << "|" << i << "| " << vDin[i].to_string() << endl;
                } catch (exception &err) {
                    cout << err.what() << endl;
                }
                break;
            case 3:
                try{
                        Imagen imgAux;
                        string vIds[] = {"346335905", "999930245", "165837", "486415569", "61385551"};
                        for (int i = 0; i < 5 ; ++i){
                            imgAux.setId(vIds[i]);
                            consolaPosImg(vDin,vDin.busquedaBin(imgAux),vIds[i]);
                        }
                } catch (exception &err) {
                    cout << err.what() << endl;
                }
                break;
            case 4:
                try{
                    VDinamico<Imagen> vAuxMail;
                    VDinamico<int> vPosiciones;
                    string email = "magdalen_upton99@gmail.com";

                    for (int i = 1; i <= vDin.tamlog() ; ++i) {
                        if(email == vDin[i].getEmail()){
                            vAuxMail.insertar(vDin[i]);
                            vPosiciones.insertar(i);
                        }
                    }

                    if(vAuxMail.tamlog() == 0){
                        email = "ERROR: No se ha encontrado el correo " + email + " en el vector.";
                        throw logic_error(email);
                    }

                    cout << "Se han encontrado imagenes de " << email << "en el vector. Se mostraran 10 de " << vAuxMail.tamlog() << " que hay." << endl;
                    for (int i = 1; i <= 10 && i < vAuxMail.tamlog(); ++i)
                        cout << "|" << i << "| " << vAuxMail[i].to_string() << endl;

                    cout << "Borrando imagenes del vector original..." << endl;
                    for(int i = vPosiciones.tamlog(); i > 0; --i) //Importa el orden en el que se introdujo en el vector
                        vDin.borrar(vPosiciones[i]);

                    cout << "Comprobando..." << endl;
                    for(int i=1; i <= vDin.tamlog(); ++i)
                        if(vDin[i].getEmail() == email)
                            throw logic_error("ERROR: Se han encontrado mas correos electronicos en el vector original");

                    cout << "Se han extraido " << vAuxMail.tamlog() << " imagenes del vector original. Ahora quedan (" << vDin.tamlog() << ") imagenes restantes." << endl;
                } catch (exception &err) {
                    cout << err.what() << endl;
                }
                break;
        }
        consola_rlj(rlj_ejercicio);
    }
    return 0;
}