#include <iostream>
#include <string>
#include <exception>
#include "Imagen.h"
#include "ImageBook.h"

/**
 * @brief Método que saca por consola el tiempo transcurrido con un objeto clock_t
 * @param reloj es el objeto instanciado del que se va a partir para medir el tiempo transcurrido
 */
void consola_rlj(clock_t &reloj) {
    cout << "[Tiempo transcurrido: " << ((clock() - reloj) / (float) CLOCKS_PER_SEC) << " segs.]" << endl << endl;
}

/**
 * @brief Ejecución principal del programa con la implementación y ejercicios indicados de la practica asociada al proyecto
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 26/10/2022
 * @return 0 si la ejecución fue exitosa. Cualquier otro número en cualquier otro caso.
 */
int main() {

    ImageBook* ib = nullptr;

    while(true){
        unsigned int elc = 0;
        cout << "Indique, del 1 al 5, un ejercicio a mostrar y pulse INTRO. Cualquier otro caracter terminará la ejcución." << endl;
        cout << "1 o 2 - Instanciar un objeto de la clase ImageBook con los ficheros etiquetas.txt y imagenes_v1.csv" << endl;
        cout << "3 - Devolver la etiqueta más repetida de ImageBook" << endl;
        cout << "4 - Mostrar por pantalla las imagenes con la etiqueta 'playa' y posteriormente 'comida." << endl;
        cout << "5 - Unir las listas del anterior ejercicio, usando el operador +, y mostrarlo por pantalla" << endl;
        cin >> elc;
        if(!(1<=elc && elc<=5))
            break;
        clock_t rlj_ejercicio = clock();
        switch (elc) {
            case 1:
            case 2:
                try{
                    if(ib != nullptr) {
                        cout << "[EJ1] A continuación se van a sobreescribir todos los datos existentes de ImageBook." << endl;
                        delete ib;
                    }
                    ib = new ImageBook("../imagenes_v1.csv","../etiquetas.txt");
                    ib->mostrarEstado();
                } catch (exception &err) {
                    cout << err.what() << endl;
                }
                break;
            case 3:
                try{
                    if(ib == nullptr)
                        throw runtime_error(string("[EJ3] No se ha instanciado el ImageBook del primer ejercicio"));
                    cout << "La etiqueta mas repetida es: " << ib->etiqMasRepetida() << endl;
                } catch (exception &err) {
                    cout << err.what() << endl;
                }
                break;
            case 4:
                try{
                    if(ib == nullptr)
                        throw runtime_error(string("[EJ4] No se ha instanciado el ImageBook del primer ejercicio"));

                    cout << "============================" << " Etiqueta 'playa' " << "============================" << endl;
                    ListaDEnlazada<Imagen> imgsPlaya = ib->buscarImgEtq("playa");
                    Iterador<Imagen> it = imgsPlaya.iterador();
                    for (int i = 0; i < imgsPlaya.getTam(); ++i) {
                        cout << it.dato().to_string()<< endl;
                        it.siguiente();
                    }
                    cout << "============================" << " Etiqueta 'comida' " << "============================" << endl;
                    ListaDEnlazada<Imagen> imgsComida = ib->buscarImgEtq("comida");
                    it = imgsComida.iterador();
                    for (int i = 0; i < imgsComida.getTam(); ++i) {
                        cout << it.dato().to_string()<< endl;
                        it.siguiente();
                    }
                } catch (exception &err) {
                    cout << err.what() << endl;
                }
                break;
            case 5:
                try{
                    if(ib == nullptr)
                        throw runtime_error(string("[EJ5] No se ha instanciado el ImageBook del primer ejercicio"));

                    cout << "============================" << " Etiqueta 'playa' + 'comida' " << "============================" << endl;
                    ListaDEnlazada<Imagen> imgsAux = ib->buscarImgEtq("playa") + ib->buscarImgEtq("comida");
                    Iterador<Imagen> it = imgsAux.iterador();
                    for (int i = 0; i < imgsAux.getTam(); ++i) {
                        cout << it.dato().to_string() << endl;
                        it.siguiente();
                    }

                } catch (exception &err) {
                    cout << err.what() << endl;
                }
                break;
        }
        consola_rlj(rlj_ejercicio);
    }
    return 0;

}

