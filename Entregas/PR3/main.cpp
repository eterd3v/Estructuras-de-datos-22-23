#include <iostream>
#include <string>
#include "ImageBook.h"
#include "Usuario.h"
#include "AVL.h"
#include "VDinamico.h"
#include <random>

/**
 * @brief Método que saca por consola el tiempo transcurrido con un objeto clock_t
 * @param [in] reloj Es el objeto instanciado del que se va a partir para medir el tiempo transcurrido.
 */
void consola_rlj(clock_t &reloj) {
    cout << "[Tiempo transcurrido: " << ((float)(clock() - reloj) / (float) CLOCKS_PER_SEC) << " segs.]" << endl << endl;
}

/**
 * @brief Función para extraer de una cadena el número del ejercicio a ejecutar
 * @param [in] eleccion Es la cadena de caracteres guardada de la entrada del usuario del progerama.
 * @return -1 si eleccion no está formado por números. En cualquier otro caso se convierte eleccion en un int.
 */
int numEjercicio(const string &eleccion){
    for (char i : eleccion){
        if(!isdigit(i))
            return -1;
    }
    return stoi(eleccion);
}

/**
 * @brief Ejecución principal del programa con la implementación y ejercicios indicados de la práctica asociada al proyecto
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 6/11/2022
 * @return 0 si la ejecución fue exitosa. Cualquier otro número en cualquier otro caso.
 */
int main() {
    ImageBook* ib = nullptr;
    int primEj=1, ultEj=5, elc;
    string eleccion;

    while(true){
        cout << "Indique, del 1 al 5, un ejercicio a mostrar y pulse INTRO. Cualquier otro caracter finaliza la ejcucion." << endl;
        cout << "1 - Instanciar un arbol AVL e incluir en el 1000000 enteros sin signo aleatorios y mostrar su altura." << endl;
        cout << "2 - Instanciar la clase ImageBook con los ficheros etiquetas.txt, usuarios.txt e imagenes_v1.csv." << endl;
        cout << "3 - Mostrar los datos de los usuarios: eliza39@yahoo.com, betty95@hotmail.com, victor6@gmail.com, manolete@gmail.com" << endl;
        cout << "4 - Mostrar los usuarios que contengan al menos una imagen con la etiqueta 'playa' y posteriormente con 'comida." << endl;
        cout << "5 - Devolver el/los usuarios mas activos en la red porque hayan publicado mas imagenes." << endl;

        do{ //Comprueba que la entrada del ejercicio sea un número
            cin >> eleccion;
            elc = numEjercicio(eleccion);
        }while(elc == -1);

        if(elc < primEj || ultEj < elc)
            break;
        try{
            clock_t rlj_ejercicio = clock();
            switch (elc) {
                case 1:
                {
                    AVL<unsigned> ej1;

                    std::random_device rd;
                    unsigned int aux, max=1000000;
                    while (ej1.numElementos() != max){
                        aux = rd();
                        if(!ej1.buscaIt(aux))
                            ej1.inserta(aux);
                    }
                    cout << "La altura del arbol tras un millon de aleatorios es de " << ej1.altura() << endl;
                }
                    break;
                case 2:
                {
                    if(!ib)
                        ib = new ImageBook("../imagenes_v1.csv","../etiquetas.txt","../usuarios.txt");
                    ib->mostrarEstado();
                }
                    break;
                case 3:
                    if(ib){
                        string correos[4] = {"eliza39@yahoo.com","betty95@hotmail.com","victor6@gmail.com","manolete@gmail.com"};
                        Usuario* usr0 = ib->buscarUsuario(correos[0]);
                        Usuario* usr1 = ib->buscarUsuario(correos[1]);
                        Usuario* usr2 = ib->buscarUsuario(correos[2]);
                        Usuario* usr3 = ib->buscarUsuario(correos[3]);
                        if(usr0) usr0->mostrarUsr();
                        else cout << "No se encontro el usuario " << correos[0] << endl;
                        if(usr1) usr1->mostrarUsr();
                        else cout << "No se encontro el usuario " << correos[1] << endl;
                        if(usr2) usr2->mostrarUsr();
                        else cout << "No se encontro el usuario " << correos[2] << endl;
                        if(usr3) usr3->mostrarUsr();
                        else cout << "No se encontro el usuario " << correos[3] << endl;
                    }else
                        cout << "No estan cargados los ficheros de Imagebook" << endl;
                    break;
                case 4:
                    if(ib){
                        string playa="playa",comida="comida";
                        VDinamico<Usuario*> usrPlaya = ib->buscarUsuarioEtiq(playa);
                        if(usrPlaya.tamlog()>0){
                            cout << "============== USUARIOS CON LA ETIQUETA '" << playa << "' ==============" << endl << endl;
                            for (int i = 1; i <= usrPlaya.tamlog() ; ++i) {
                                if(usrPlaya[i]){
                                    usrPlaya[i]->mostrarUsr();
                                    cout << endl;
                                }
                            }
                        }

                        VDinamico<Usuario*> usrComida = ib->buscarUsuarioEtiq(comida);
                        if(usrComida.tamlog()>0){
                            cout << endl << "============== USUARIOS CON LA ETIQUETA '" << comida << "' ==============" << endl << endl;
                            for (int i = 1; i <= usrComida.tamlog() ; ++i) {
                                if(usrComida[i]){
                                    usrComida[i]->mostrarUsr();
                                }
                            }
                        }
                    }else
                        cout << "No estan cargados los ficheros de Imagebook" << endl;
                    break;
                case 5:
                    if(ib){
                        VDinamico<Usuario*> usrsActivos = ib->getMasActivos();
                        if(usrsActivos.tamlog() == 0)
                            throw length_error("[main] No hay ningún usuario cargado en el sistema actualmente");
                        for (int i = 1; i <= usrsActivos.tamlog() ; ++i) {
                            usrsActivos[i]->mostrarUsr();
                        }
                    }else
                        cout << "No estan cargados los ficheros de Imagebook" << endl;
                    break;
            }
            consola_rlj(rlj_ejercicio);
        } catch (exception &err) {
            cout << err.what() << endl;
        }
    }
    return 0;

}

