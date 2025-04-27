#include <iostream>
#include <string>
#include "ImageBook.h"
#include "Usuario.h"
#include "THashImagen.h"
#include <ctime>

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
    for (char i : eleccion)
        if(!isdigit(i))
            return -1;
    return stoi(eleccion);
}

/**
 * @brief Ejecución principal del programa con la implementación y ejercicios indicados de la práctica asociada al proyecto
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 06/12/2022
 * @return 0 si la ejecución fue exitosa. Cualquier otro número en cualquier otro caso.
 */
int main() {
    ImageBook* ib = nullptr;
    int primEj=1, ultEj=8, elc;
    string eleccion;

    while(true){
        cout << "Indique, del 1 al 5, un ejercicio a mostrar y pulse INTRO. Cualquier otro caracter finaliza la ejcucion." << endl;
        cout << "1 - Mostrar el factor de carga de la tabla junto al tamanio de la misma." << endl;
        cout << "2 - El usuario kenny_ohara73@yahoo.com quiere darle like a la ultima imagen que subio magdalen_upton99@gmail.com." << endl;
        cout << "3 - El usuario beau1@hotmail.com quiere darle like a la imagen con id 32477162" << endl;
        cout << "4 - Darle like a todas las imagenes con la etiqueta 'gato'" << endl;
        cout << "5 - Obtener el top 5 de etiquetas con mas likes." << endl;
        cout << "6 - Mostrar el top 3 de usuarios mas populares" << endl;
        cout << "7, 8 - Likes de 'pantalla', buscar y eliminar imagen 58540348, obtener likes, buscar 58540348 e insertar de nuevo." << endl;
        cout << "7, 8 - Mostrar el numero de colisiones maximo que se han producido al volver a insertar la imagen." << endl;


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
                    if(!ib)
                        ib = new ImageBook("../imagenes_v1.csv","../etiquetas.txt","../usuarios.txt");
                    ib->mostrarEstado();
                    ib->consultarImagenes();
                    break;
                }
                case 2:
                    if(ib) {
                        string usr1 = "kenny_ohara73@yahoo.com",usr2 = "noelia30@hotmail.com";
                        Usuario* kenny = ib->buscarUsuario(usr1);
                        Usuario* noelia = ib->buscarUsuario(usr2);
                        Imagen* ultima = noelia->getImagenMasReciente();
                        cout << "La ultima foto de " << usr2 << " (" << ultima->getNombre() << ") tiene " << ultima->getLikes() << " likes." << endl;
                        kenny->meGustaImagen(ultima);
                        cout << "La ultima foto de " << usr2 << " (" << ultima->getNombre() << ") tiene " << ultima->getLikes() << " likes." << endl;

                    }else
                        cout << "No estan cargados los ficheros de Imagebook" << endl;
                    break;
                case 3:
                    if(ib){
                        string usr = "beau1@hotmail.com", imgIdLike = "32477162";
                        Usuario* beau1 = ib->buscarUsuario(usr);
                        Imagen* imgAux = ib->buscarImagen(imgIdLike);
                        cout << "La foto " << imgAux->getNombre() << " tiene " << imgAux->getLikes() << " likes." << endl;
                        beau1->meGustaImagen(imgAux);
                        cout << "La foto " << imgAux->getNombre() << " tiene " << imgAux->getLikes() << " likes." << endl;

                    }else
                        cout << "No estan cargados los ficheros de Imagebook" << endl;
                    break;
                case 4:
                    if(ib){
                        string etqGato = "gato";
                        vector<Usuario*> vGatos = ib->buscarUsuarioEtiq(etqGato);
                        Etiqueta* gato = ib->buscarEtiqueta(etqGato);
                        cout << "La etiqueta " << gato->getNombre() << " tiene " << gato->getTotalLikes() << " likes." << endl;
                        vGatos.front()->likeAutomatico(etqGato);
                        cout << "La etiqueta " << gato->getNombre() << " tiene " << gato->getTotalLikes() << " likes." << endl;
                    }else
                        cout << "No estan cargados los ficheros de Imagebook" << endl;
                    break;
                case 5:
                    if(ib){
                        list<Etiqueta*> lEtqs = ib->getMasLikes();
                        cout << "====== Las 5 etiquetas con mas likes son ======" << endl;
                        for (Etiqueta* e : lEtqs)
                            if(e)
                                cout << e->getNombre() << ":" << e->getTotalLikes() << endl;
                    }else
                        cout << "No estan cargados los ficheros de Imagebook" << endl;
                    break;
                case 6:
                    if(ib){
                        list<Usuario*> lUsrs = ib->getMasPopulares();
                        cout << "====== Las 5 etiquetas con mas likes son ======" << endl;
                        for (Usuario* u : lUsrs)
                            if(u)
                                u->mostrar();
                    }else
                        cout << "No estan cargados los ficheros de Imagebook" << endl;
                    break;
                case 7:
                case 8:
                    if(ib){
                        Etiqueta* pantalla = ib->buscarEtiqueta("pantalla");
                        cout << "La etiqueta " << pantalla->getNombre() << " tiene " << pantalla->getTotalLikes() << " likes." << endl;
                        Imagen* imgAux = ib->buscarImagen("58540348");
                        if(imgAux)
                            cout << imgAux->toString() << endl;

                        Imagen *imgAux2;
                        imgAux2 = imgAux;


                        if(ib->borrarImagen("58540348"))
                            cout << "La imagen se ha borrado con exito" << endl;
                        else
                            cout << "La imagen no se ha borrado del sistema" << endl;

                        imgAux = ib->buscarImagen("58540348");
                        if(imgAux)
                            throw runtime_error("[main] La imagen no debería haberse encontrado.");

                        ib->insertarImagen("58540348",imgAux2);
                        ib->consultarImagenes();

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

