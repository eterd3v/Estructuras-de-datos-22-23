/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 08/10/2022
 */

#ifndef IMAGENES_VDINAMICO_H
#define IMAGENES_VDINAMICO_H

#include <math.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <exception>

using namespace std;

/**
 * @brief Clase que servirá como un vector dinámico para datos de tipo T
 * @tparam T es el tipo de dato a usar en el vector dinámico. Cualquiera es válido.
 */
template <class T>
class VDinamico {
private:
    //Vector de T, creado en memoria dinámica
    T* vectorDin;
    //Tamaño lógico asociado al vector (elementos ocupados)
    unsigned int tamLogico;
    //Tamaño físico asociado al vector (máximo de elementos que se pueden ocupar)
    unsigned int tamFisico;

    /**
     * Método para sacar la potencia en base 2 inmediatamente superior al parametro num
     * @param num es el número del cuál se va a obtener su potencia en base 2
     * @return potencia en base 2 con exponente suficiente (2^X+1) como para rebasar num
     */
    unsigned int potenciaSup(unsigned int num);

    /**
     * @brief Función privada para alojar el doble de espacio físico al vector dinámico.
     */
    void alojarDoble();

    /**
     * @brief Función privada para alojar la mitad del espacio físico ocupado del vector dinámico.
     */
    void alojarMitad();

public:

    /**
     * @brief Constructor por defecto de la clase VDinamico
     */
    VDinamico();

    /**
     * @brief Constructor de la clase VDinamico usando un tamaño lógico deseado.
     * @param tamlog es el tamaño lógico que se busca del vector
     */
    explicit VDinamico(unsigned int tamlog);

    /**
     * @brief Constructor copia de la clase VDinamico
     * @param origen es una instancia de VDinamico que va a ser copiada para el nuevo objeto
     */
    VDinamico(const VDinamico<T> &origen);

    /**
     * @brief Constructor copia parcial de la clase VDinamico
     * @param origen es un objeto de tipo VDinamico<T> ya instanciado que va a ser parcialmente copiado
     * @param posicionInicial es la posición inicial desde la cual se van a copiar los datos de origen. Va desde 0 hasta TAMAÑO - 1
     * @param numElementos es la cantidad de elementos que se van a copiar para la creación del nuevo vector.
     */
    VDinamico(const VDinamico<T> &origen, unsigned int posicionInicial, unsigned int numElementos);

    /**
     * @brief Operador de asignación de la clase VDinamico
     * @param orig es la instancia de VDinamico que se va a usar para la asignación
     * @return objeto que ha sido asignado para permitir más operaciones de lectura y escritura.
     */
    VDinamico& operator=(const VDinamico &orig);

    /**
     * @brief Operador de lectura y escritura
     * @param posicion es la posición a la que se desea acceder. Sólo permite desde 1 hasta tamlog()
     * @return dato del vector alojado en la posición indicada
     */
    T& operator[](const unsigned int posicion);

    /**
     * @brief Método para insertar datos en el vector dinámico
     * @param dato del mismo tipo con el que instanció la plantilla del vector que va a ser introducido.
     * @param pos indica la posición donde se desea insertar el dato. Inserta al final por defecto.
     */
    void insertar(const T& dato, unsigned int pos = UINT_MAX);

    /**
     * @brief Método para borrar elementos del vector dinámico
     * @param pos es la posición del vector a borrar. Sólo permite desde 1 hasta tamlog()
     * @return dato de tipo T que se encuentra en la posición a borrar
     */
    T borrar(unsigned int pos = UINT_MAX);

    /**
     * @brief Función que ordena de menor a mayor los datos cargados en el vector dinámico. Necesita del operador <
     */
    void ordenar();

    /**
     * @brief Función que ordena de mayor a menor los datos cargados en el vector dinámico. Necesita del operador <
     */
    void ordenarRev();

    /**
     * @brief Búsqueda binaria de un dato en el vector dinámico
     * @param dato del mismo tipo con el que se instanció la plantilla del vector para ser buscado.
     * @return un entero tal que está entre el 1 y el tamlog (ambos incluidos). -1 si no se econcontró.
     */
    int busquedaBin(const T &dato);

    /**
     * @brief Función para conocer el tamaño lógico del vector
     * @return Entero sin signo que representa el tamaño del vector. 0 significa que no tiene elementos.
     */
    unsigned int tamlog();

    /**
     * @brief Destructor de la clase VDinamico
     */
    virtual ~VDinamico();
};

template<class T>
unsigned int VDinamico<T>::potenciaSup(unsigned int num){
    if(num < 1)
        throw invalid_argument("ERROR: No se puede obtener la potencia del parametro num.");

    unsigned int potencia = (unsigned int) log2(num); //Se busca el logaritmo en base 2 y lo guardo
    if (pow(2,potencia) < num)  //Mira si se queda corto
        potencia++;
    potencia=pow(2,potencia+1); //Reuso la variable para hacer la potencia en base 2

    return potencia;
}

template<class T>
void VDinamico<T>::alojarDoble(){
    VDinamico<T> v_aux(*this);      //Copio los elementos del vector auxiliar al mio
    delete[] vectorDin;             //Lo borro
    vectorDin = new T[tamFisico *= 2];
    *this = v_aux;                  //Asigno nuevo espacio y volvemos a meter los elementos
}

template<class T>
void VDinamico<T>::alojarMitad(){
    VDinamico<T> vAux ((*this), 0, tamLogico);
    delete[] vectorDin;
    vectorDin = new T[tamFisico /= 2];
    (*this) = vAux;
}

template<class T>
VDinamico<T>::VDinamico(): tamFisico(1), tamLogico(0){
    vectorDin = new T[tamFisico];
}

template<class T>
VDinamico<T>::VDinamico(unsigned int tamlog){
    tamFisico = potenciaSup(tamlog);
    tamLogico = 0; //Se inicializa vacío
    vectorDin = new T[tamFisico];
}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &origen): tamFisico(origen.tamFisico), tamLogico(origen.tamLogico){
    vectorDin = new T[tamFisico];
    for(int i = 0; i < tamLogico; i++)
        vectorDin[i]=origen.vectorDin[i];
}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T> &origen, unsigned int posicionInicial, unsigned int numElementos){
    if(numElementos + posicionInicial > origen.tamLogico) //Aquí tiene más sentido que no se exceda el tamaño lógico y no el físico por ser un vector dinámico
        throw invalid_argument("ERROR: El número de elementos a copiar exceden a los que existen en VDinamico<T> &origen.");
    if(numElementos == 0)
        throw invalid_argument("ERROR: No se va a copiar ningún elemento");

    tamFisico = potenciaSup(numElementos);
    tamLogico = numElementos;
    vectorDin = new T[tamFisico];
    for (int i = 0; i < numElementos; ++i)
        vectorDin[i]=origen.vectorDin[posicionInicial+i];
}

template<class T>
VDinamico<T> &VDinamico<T>::operator=(const VDinamico<T> &orig) {
    if(orig.tamLogico <= tamFisico){ //A this le tiene que caber todos los elementos de orig
        tamLogico = orig.tamLogico;
        for (int i = 0; i < tamLogico; ++i)
            vectorDin[i] = orig.vectorDin[i];
    } else
        throw length_error("ERROR: El vector que va a recibir la asignación tiene tamaño insuficiente" );
    return *this;
}

template<class T>
T& VDinamico<T>::operator[](const unsigned int posicion){
    if(!(1 <= posicion && posicion <= tamLogico))
        throw invalid_argument("ERROR: Se ha intentado acceder a una posición invalida en el vector");
    return vectorDin[posicion - 1];
}

template<class T>
void VDinamico<T>::insertar(const T& dato, unsigned int pos){
    if(tamLogico < pos && pos < UINT_MAX)
        throw length_error("ERROR: No se puede insertar en esa posición ya que no está en el vector o sus límites.");

    if(tamLogico >= tamFisico)         //El tamaño se queda corto y hay que asignar más espacio para el vector
        alojarDoble();

    switch (pos) {
        case UINT_MAX: tamLogico:
            vectorDin[tamLogico]=dato;
            break;
        case 0:
            throw invalid_argument("ERROR: La posición 0 no es válida para insertar un dato. Sólo entre 1 <= pos <= TAM");
            break;
        default:
            T datoAux1, datoAux2 = dato;
            for (unsigned int i = pos; i <= tamLogico; ++i) { //Se ejecuta hasta el tamLógico para copiar todos los auxiliares
                datoAux1=vectorDin[i];  //Lo que haya en la posición, lo meto en un dato aux 1
                vectorDin[i]=datoAux2;  //Ahora se sobreescribe el dato con lo que hay en el dato aux 2
                datoAux2 = datoAux1;    //Como ya está en el vector, el siguiente dato que se va a almacenar será el dato aux 1 para desplazarse a la derecha
            }
            break;
    }
    tamLogico++;
}

template<class T>
T VDinamico<T>::borrar(unsigned int pos){
    if(tamLogico < pos && pos < UINT_MAX)
        throw invalid_argument("ERROR: No se puede borrar en esa posición ya que no está en el vector o sus límites.");
    if(tamLogico == 0)
        throw invalid_argument("ERROR: No hay más elementos en el vector. No se puede borrar más.");
    if(pos == 0)
        throw invalid_argument("ERROR: La posición 0 no es válida para borrar un dato. Sólo entre 1 <= pos <= TAM");

    if(tamLogico * 3 <= tamFisico)         //Esperar a 1/3 del tamaño máximo para disminuir el tamaño fisico del vector
        alojarMitad();

    if(pos == UINT_MAX)                    //si pos == UINT_MAX entonces se borra por el final
        pos = tamLogico;

    T aux = vectorDin[pos -= 1];            //Tomo el valor indicado en la posición

    for(unsigned int i = pos; i < tamLogico; i++){    //Itera hasta el último para ir trasladando elementos
        vectorDin[i] = vectorDin[i+1];
    }

    tamLogico -= 1;
    return aux;
}

template<class T>
void VDinamico<T>::ordenar(){
    sort(vectorDin, vectorDin+tamLogico);
}

template<class T>
void VDinamico<T>::ordenarRev(){
    ordenar();
    reverse(vectorDin, vectorDin+tamLogico);
}

template<class T>
int VDinamico<T>::busquedaBin(const T &dato){
    int izquierda = 0, derecha = tamLogico-1; //Extremos del contenedor
    int pos = derecha; //Posición que buscamos en el contenedor.

    while(izquierda <= derecha){ //Bucle hasta encontrar el dato.
        if(dato == vectorDin[pos])
            return pos + 1;
        pos = (izquierda + derecha)/2; //Sólo se queda con la parte entera (da igual los decimales).
        (dato < vectorDin[pos]) ? (derecha = pos - (izquierda+derecha)%2) : (izquierda = pos + (izquierda+derecha)%2); // Solución => pos +- (izq+der)%2 para tb salir del bucle
    }

    return -1;
}

template<class T>
unsigned int VDinamico<T>::tamlog(){
    return  tamLogico;
}

template<class T>
VDinamico<T>::~VDinamico() {
    delete []vectorDin;
}

#endif //IMAGENES_VDINAMICO_H
