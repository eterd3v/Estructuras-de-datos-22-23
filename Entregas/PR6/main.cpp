#include <iostream>
#include <string>
#include "ImageBook.h"
#include "Usuario.h"
#include "Rango.h"
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
 * @brief Método para calcular el sumatorio de likes de varias Imagenes
 * Función auxiliar para la ejecución del programa de prueba, parte 5 y 6
 * @param [in] imagenes Es un vector de punteros Imagen con el que calcular la suma de likes
 * @return Entero positivo con la suma de todos los likes de las Imagenes
 */
unsigned int sumatorioLikes(const vector<Imagen*> &imagenes){
    unsigned int sumaLikes = 0;
    for(Imagen* img : imagenes)
        if(img)
            sumaLikes += img->getLikes();
    return sumaLikes;
}

/**
 * @brief Método para mostrar las imágenes pedidas en el programa de prueba 5 y 6
 * @param [in] imagenes Es un vector de punteros de Imagen a mostrar
 */
void mostrarImagenes(const vector<Imagen*> &imagenes){
    for (Imagen* img : imagenes)
        if(img)
            cout << img->toString() << endl;
}

/**
 * @brief Ejecución principal del programa con la implementación y ejercicios indicados de la práctica asociada al proyecto
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 15/12/2022
 * @return 0 si la ejecución fue exitosa. Cualquier otro número en cualquier otro caso.
 */
int main() {

    ImageBook* ib = nullptr;
    int primEj=1, ultEj=6, elc;
    string eleccion;

    while(true){
        cout << "=== Indique, del 1 al 6, un ejercicio a mostrar y pulse INTRO. Pulsar otro caracter finaliza la ejecucion ===" << endl;
        cout << "1 - Instanciar ImageBook y (VOLUNTARIO) crear un fichero que visualize sus puntos en una malla." << endl;
        cout << "2 - Imgs de rango (34.04,-81.06) min y (55.04,-65.06) max y comparten etiqueta reciente de kenny_ohara73@yahoo.com." << endl;
        cout << "3 - Mostrar emails de las fotos tomadas en el rango (36.388698,-121.72439) min y (39.388698,-89.72439) max" << endl;
        cout << "4 - Mostrar la etiqueta mas repetida dentro del rango (30.0201,-98.2340) min y (60.0039,-80.99) max." << endl;
        cout << "5,6 - Imagenes del usuario 'beau1@hotmail.com' del rango (30.8304,-94.8684) min y (47.3304,-65.3684) max"
        << endl << " y obtener de ellas la imagen con mas likes. Luego, dar like en el rango de la imagen con mas likes:"
        << endl << "(longitudImgMasLikes-0.1, latitudImgMasLikes-0.1) min y (longitudImgMasLikes+0.1, latitudImgMasLikes+0.1) max"
        << endl << " Mostrar los likes de las imagenes antes y despes del cambio." << endl;
        cout << "=== === === === === === === === === === === === === === === === === === === === === === === === === === ===" << endl << endl;


        do{ //Comprueba que la entrada del ejercicio sea un número
            cin >> eleccion;
            elc = numEjercicio(eleccion);
        }while(elc == -1);

        if(elc < primEj || ultEj < elc)
            break;
        try{
            if(elc != 1 && ib == nullptr)   //Comprobación de que ImageBook este instanciado en el resto de ejercicios que no sean el 1
                throw runtime_error(string("[main] ImageBook no esta creado en memoria. Ejecute antes el ejercicio 1."));

            clock_t rlj_ejercicio = clock();
            switch (elc) {
                case 1: {
                    if (!ib)
                        ib = new ImageBook("../imagenes_v2_mod.csv", "../etiquetas.txt", "../usuarios.txt");
                    ib->mostrarEstado();
                }
                    break;
                case 2: {
                    string usr1 = "kenny_ohara73@yahoo.com";
                    Usuario *kenny = ib->buscarUsuario(usr1);
                    Imagen *masReciente;

                    if (kenny)
                        masReciente = kenny->getImagenMasReciente();
                    else
                        throw runtime_error(
                                string("[main::ej1] No se ha podido hallar el usuario " + usr1 + " en el sistema."));

                    if (masReciente) {
                        vector<string> etiquetas = masReciente->getEtiquetas();
                        Rango r(34.04, -81.06, 55.04, -65.06);
                        unsigned suma = 0;
                        for (int i = 0; i < etiquetas.size(); ++i) {
                            vector<Imagen *> aux = ib->buscarImagEtiLugar(etiquetas[i], r);
                            cout << "En el rango hay " << aux.size() << " imagenes que comparten la etiqueta " << etiquetas[i] << endl;
                            mostrarImagenes(aux);
                            suma += aux.size();
                        }
                        cout << endl << "Kenny comparte recientemente " + to_string(suma) + " etiquetas en el rango " +
                                r.toString() << endl;
                    } else
                        throw runtime_error(string("[main::ej2] No se ha podido hallar la imagen mas reciente de " + usr1));

                }
                    break;
                case 3: {
                    Rango r(36.388698, -121.72439, 39.388698, -89.72439);
                    vector<Usuario *> usrsRango = ib->buscarUsuarLugar(r);
                    cout << "=== Se han encontrado " << to_string(usrsRango.size()) << " en el rango " << r.toString() << " ===" << endl << endl;
                    for(Usuario* usr: usrsRango)
                        if(usr)
                            usr->mostrar();
                    cout << endl << "=== Se han encontrado " << to_string(usrsRango.size()) << " en el rango " << r.toString() << " ===" << endl;
                }
                    break;
                case 4: {
                    Rango r(30.0201,-98.2340,60.0039,-80.99);
                    Etiqueta* aux = ib->buscaEtiquetaRepetida(r);
                    if(aux)
                        cout << "La etiqueta '" << aux->getNombre() << "' es la mas repetida en el rango " << r.toString() << endl;
                    else
                        throw runtime_error(string("[main::ej4] Hubo un problema y no se encuentra la Etiqueta en el rango " + r.toString()));
                }
                    break;
                case 5:
                case 6:{
                    string beau1="beau1@hotmail.com";
                    Rango r(30.8304,-94.8684,47.3304,-65.3684);

                    Usuario* usrBeau = ib->buscarUsuario(beau1);
                    if(usrBeau == nullptr)
                        throw runtime_error(string("[main::ej5/ej6] Hubo un problema y no se ha encontrado al usuario " + beau1));

                    vector<Imagen*> imgsBeau = usrBeau->imagenEnZona(r);
                    if(imgsBeau.empty())
                        throw runtime_error(string("[main::ej5/ej6] Hubo un problema y el usuario " + beau1 + " no posee imagenes en la zona " + r.toString()));
                    cout << beau1 << " tiene " << to_string(imgsBeau.size())<< " imagenes en el rango " + r.toString() << endl;

                    Imagen* maxImg = nullptr;

                    for(Imagen* img : imgsBeau){ //Búsqueda de la imagen con mas likes
                        if(img){
                            if(maxImg){
                                if(img->getLikes() > maxImg->getLikes())
                                    maxImg = img;
                            }else
                                maxImg = img;
                        }
                    }

                    if(maxImg == nullptr)
                        throw runtime_error(string("[main::ej5/ej6] Hubo un problema y no se ha podido encontrar la imagen mas famosa de " + beau1));
                    cout << "La imagen mas famosa de '" + beau1 + "' en el rango " + r.toString() + " es '" + maxImg->getNombre() + "'." << endl;
                    cout << "La imagen mas famosa de '" + beau1 + "' tiene de coordenadas x=" + to_string(maxImg->getX()) + ", y=" + to_string(maxImg->getY()) << endl;

                    Rango g(maxImg->getX(),maxImg->getY(),maxImg->getX(),maxImg->getY());
                    g.modificar(0.1);
                    unsigned int sumaLikes = sumatorioLikes(ib->buscarImagLugar(g));
                    mostrarImagenes(ib->buscarImagLugar(g));
                    cout << endl << "-ANTES- En el rango " << g.toString() << " hay un total de " << sumaLikes << " likes" << endl << endl;

                    usrBeau->likeAutomaticoZona(g);
                    sumaLikes = sumatorioLikes(ib->buscarImagLugar(g));
                    mostrarImagenes(ib->buscarImagLugar(g));
                    cout << "-DESPUES- En el rango " << g.toString() << " hay un total de " << sumaLikes << " likes" << endl;


                }
                    break;
            }
            consola_rlj(rlj_ejercicio);
        } catch (exception &err) {
            cout << err.what() << endl;
        }
    }
    return 0;

}

