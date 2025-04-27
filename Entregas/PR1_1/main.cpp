#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ContenedorImagenes.h"
#include "Imagen.h"

/**
 * @brief Método que saca por consola el tiempo transcurrido con un objeto clock_t
 * @param reloj
 */
void consola_rlj(clock_t &reloj){
    cout << "Tiempo transcurrido: " << ((clock() - reloj) / (float) CLOCKS_PER_SEC) << " segs." << endl;
}

/**
 * @brief Ejecución principal del programa
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 26/09/2022
 * @return 0 si la ejecución fue exitosa. Cualquier otro número en cualquier otro caso.
 */
int main() {

    ContenedorImagenes ci(10000);

    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string id = "";
    std::string email="";
    std::string nombre="";
    int tam = 0;
    int dia = 0;
    int mes = 0;
    int anno = 0;
    std::string etiquetas="";

    is.open("../imagenes_v1.csv"); //carpeta de proyecto
    if ( is.good() ) {

        Imagen ImgAux; //Creo una Imagen auxiliar por defecto para introducir datos en el contenedor

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id;email;nombre;tam;fecha;etiquetas

                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas,email,';');
                getline(columnas,nombre,';');

                columnas >> tam;   //las secuencia numéricas se leen y trasforman directamente
                columnas.ignore(); //omitimos carácter ';' siguiente

                columnas >> dia; columnas.ignore();
                columnas >> mes; columnas.ignore();
                columnas >> anno; columnas.ignore();

                getline(columnas,etiquetas,';');

                fila="";
                columnas.clear();

                try{
                    ImgAux.setId(id);
                    ImgAux.setNombre(nombre);
                    ImgAux.setEmail(email);
                    ImgAux.setEtiquetas(etiquetas);
                    ImgAux.setFecha(dia, mes, anno);
                    ImgAux.setTam(tam);
                    ci.asigna(ImgAux, contador);
                    ++contador;
                } catch (exception &err) { //Captura la excepción del contenedor si la hubiera
                    cout << err.what() << endl;
                }
            }
        }

        is.close();

        std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    cout << endl << "EJERCICIO 1: mostrar los 50 primeras imagenes del contenedor con su nombre, etiqueta, etc..." << endl;
    clock_t rlj_ej = clock();
    for (int i = 0; i < 50; ++i)
        cout << ci.recupera(i).to_string() << endl;
    consola_rlj(rlj_ej);

    cout << endl << "EJERCICIO 2: Ordenar al reves y mostrar imagenes del contenedor" << endl;
    rlj_ej = clock();
    ci.ordenarRev();
    consola_rlj(rlj_ej);
    for (int i = 0; i < 50; ++i)
        cout << ci.recupera(i).to_string() << endl;

    cout << endl << "EJERCICIO 3: Ordenar normal (menor a mayor) y mostrar imagenes del contenedor" << endl;
    rlj_ej = clock();
    ci.ordenar();
    consola_rlj(rlj_ej);
    for (int i = 0; i < 20; ++i)
        cout << ci.recupera(i).to_string() << endl;

    cout << endl << "EJERCICIO 4: Buscar imagenes con algun identificador que se conozca que existe y otro que no" << endl;
    rlj_ej = clock();
    try {
        Fecha fecha_aux(3,2,2020);
        Imagen imgaux1("581044781","magdalen_upton99@gmail.com","picture34583.jpeg",793243,fecha_aux,"presidente,nublado,leon,escritorio,solicitud,deterioro");
        unsigned int posicion = ci.busca(imgaux1);
        cout << "La imagen " << ci.recupera(posicion).getNombre() << " se encuentra en la posicion " + to_string(posicion) << endl << imgaux1.to_string() << endl << endl;

        fecha_aux.asignarDia(5,7,2022); //En realidad la fecha que está en el archivo csv es el 5/7/2021
        Imagen imgaux2("515996453","beau1@hotmail.com","picture97665.gif",921709,fecha_aux,"hogar,jueves,actividad,japones,competencia");
        posicion = ci.busca(imgaux2);
        cout << "La imagen " << imgaux2.getNombre() << " se encuentra en la posicion " + to_string(posicion) << endl << imgaux2.to_string() << endl << endl;
    } catch (exception &err) {
        cout << err.what() << endl;
    }
    consola_rlj(rlj_ej);

    cout << endl << "EJERCICIO 5: Recuperar las 20 primeras imagenes (o menos) del usuario magdalen_upton99@gmail.com durante el 2020" << endl;
    rlj_ej = clock();
    try{
        Fecha Fecha_ini(1,1,2020), Fecha_fin(31,12,2020);
        ContenedorImagenes ci_aux = ci.localiza("magdalen_upton99@gmail.com",Fecha_ini,Fecha_fin);
        for (int i = 0; i < ci_aux.tam(); ++i)
            cout << ci_aux.recupera(i).to_string() << endl;
    }catch (exception &err) {
        cout << err.what() << endl;
    }
    consola_rlj(rlj_ej);

}