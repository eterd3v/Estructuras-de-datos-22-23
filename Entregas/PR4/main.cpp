#include <iostream>
#include <string>
#include "ImageBook.h"
#include "Usuario.h"
#include <vector>

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
 * @date 22/11/2022
 * @return 0 si la ejecución fue exitosa. Cualquier otro número en cualquier otro caso.
 */
int main() {
    ImageBook* ib = nullptr;
    int primEj=1, ultEj=6, elc;
    string eleccion;

    while(true){
        cout << "Indique, del 1 al 5, un ejercicio a mostrar y pulse INTRO. Cualquier otro caracter finaliza la ejcucion." << endl;
        cout << "1 - Instanciar la clase ImageBook con los ficheros etiquetas.txt, usuarios.txt e imagenes_v1.csv." << endl;
        cout << "2 - noelia30@hotmail.com quiere incluir 'playa' en sus imagenes cuyo id es 625722993" << endl;
        cout << "3 - kenny_ohara73@yahoo.com quiere modificar su ultima imagen. Encontrarla e incluir la etiqueta 'viernes'" << endl;
        cout << "4 - elton.botsford@yahoo.com quiere conocer a los usuarios con la etiqueta 'arroz'. Mostrar usuarios obtenidos e email." << endl;
        cout << "5 - Buscar a los usuarios que publicaron el dia 7/9/2021 y mostrar sus datos. De entre ellos, mostrar publico mas imagenes." << endl;
        cout << "6 - Comprobar si el usuario chesley.gerlach@hotmail.com es el mas activo de la red social" << endl;


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
                    break;
                }
                case 2:
                    if(ib) {
                        string usr = "noelia30@hotmail.com", etiqueta = "playa", id = "625722993";

                        Usuario* auxUsr = ib->buscarUsuario(usr);
                        auxUsr->mostrar();

                        auxUsr->anadirEtiquetaImagen(id,etiqueta);
                        auxUsr->mostrar();
                    }else
                        cout << "No estan cargados los ficheros de Imagebook" << endl;
                    break;
                case 3:
                    if(ib){
                        string usr = "kenny_ohara73@yahoo.com", etiqueta = "viernes";
                        Usuario* auxUsr = ib->buscarUsuario(usr);
                        auxUsr->mostrar();

                        Imagen* auxImg = ib->buscarUsuario(usr)->getImagenMasReciente();
                        Etiqueta* auxEti = ib->buscarMiEtiqueta(etiqueta);
                        auxImg->anadirEtiqueta(auxEti);

                        auxUsr->mostrar();
                    }else
                        cout << "No estan cargados los ficheros de Imagebook" << endl;
                    break;
                case 4:
                    if(ib){
                        string usr = "elton.botsford@yahoo.com", etiqueta = "arroz";
                        vector<Usuario*> vAux = ib->buscarUsuarioEtiq(etiqueta);

                        cout << "====== Imagebook tiene " << vAux.size() << " imagenes con la etiqueta " << etiqueta << " ======" << endl;
                        for(Usuario* usr : vAux){
                            try{
                                if(usr)
                                    usr->mostrar();
                                else
                                    throw runtime_error (string("[main::ej4] Hay un usuario no valido"));
                            }catch (exception &err){
                                cout << err.what() << endl;
                            }
                        }

                    }else
                        cout << "No estan cargados los ficheros de Imagebook" << endl;
                    break;
                case 5:
                    if(ib){
                        Fecha miFecha(7,9,2021);
                        vector<Usuario*> dia = ib->buscarUsuarioFechaImagen(miFecha);
                        unsigned max = 0;
                        Usuario* maxUsr = nullptr;

                        for (int i = 0; i < dia.size(); ++i) {
                            if(dia[i])
                                if(dia[i]->getNumImages() > max){
                                    max = dia[i]->getNumImages();
                                    maxUsr = dia[i];
                                }
                        }

                        cout << "====== Todas las personas del dia " << miFecha.cadena() << " ======" << endl;
                        for (int i = 0; i < dia.size(); ++i)
                            dia[i]->mostrar();

                        cout << endl << "====== La persona con mas imagenes del dia " << maxUsr->getEmail()  << "======" << endl;
                        maxUsr->mostrar();

                    }else
                        cout << "No estan cargados los ficheros de Imagebook" << endl;
                    break;
                case 6:
                    if(ib){
                        string email = "chesley.gerlach@hotmail.com";
                        vector<Usuario*> activo = ib->getMasActivos();
                        for(Usuario* usr : activo)
                            usr->mostrar();

                        for (int i = 0; i < activo.size(); ++i) {
                            if(activo[i])
                                if(activo[i]->getEmail() == email){
                                    cout << endl << "====== " << email << " es el mas activo de la red social ======." << endl;
                                    activo[i]->mostrar();
                                    break;
                                }
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

