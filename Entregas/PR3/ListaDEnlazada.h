/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 26/09/2022
 */
#ifndef PR2_LISTADENLAZADA_H
#define PR2_LISTADENLAZADA_H

#include "Nodo.h"
#include "Iterador.h"
#include <stdexcept>
#include <iostream>

using namespace std;

/**
 * @brief Es una clase que implementa la lista doblemente enlazada como estructura de datos
 * @tparam T es el tipo dato de plantilla de la clase. ListaDEnlazada puede usarse con cualquier dato si se sustituye por T
 */
template<class T>
class ListaDEnlazada {
private:
    /// Es un puntero de Nodo<T> que actúa como la cabecera de la lista
    Nodo<T>* cabecera;
    /// Es un puntero de Nodo<T> que actúa como la cola de la lista
    Nodo<T>* cola;
    /// Es el tamaño actual de elementos en la ListaDEnlazada<T>
    unsigned int tam;
public:

    /**
     * @brief Constructor por defecto de la clase
     */
    ListaDEnlazada();

    /**
     * @brief Constructor copia de la lista doblemente enlazada
     * @param [in] original es de donde se van a copiar los elementos para la lista nueva
     */
    ListaDEnlazada(const ListaDEnlazada<T> &original);

    /**
     * @brief Es el operador de asignación de lista doblemente enlazada.
     * @param [in] original es la lista de donde se van a tomar los elementos para la asignación.
     * @return referencia sobre la instancia de la ListaDEnlazada para poder seguir realizando asignaciones.
     */
    ListaDEnlazada& operator=(const ListaDEnlazada &original);

    /**
     * @brief Operador para comparar la igualdad entre dos clases ListaDEnlazada
     * @param [in] original es la lista con la que se va a comparar con this
     * @return true si son iguales en elementos. false en cualquier otro caso
     */
    bool operator==(const ListaDEnlazada &original);

    /**
     * @brief Operador que suma una ListaDEnlazada tras otra
     * @param [in] original es la lista que va a unirse al final de la lista de this
     * @return Una lista con los objetos de this y después de original, es decir, this + original
     */
    ListaDEnlazada<T> operator+(const ListaDEnlazada &original);

    /**
     * @brief Método para concatenar una lista al final de this.
     * @param [in] listaCont es la ListaDEnlazada que se concatena al final de this
     */
    void concatena(const ListaDEnlazada<T> &listaCont);

    /**
     * @brief Función para crear un iterador asociado a la lista.
     * @return un Iterador<T> nuevo situado al inicio de la lista.
     */
    Iterador<T> iterador();

    /**
     * @brief Método para insertar por en medio de la ListaDEnlazada<T>
     * @param [in] i es un Iterador<T> que indica la posicion posterior a donde se va insertar dato
     * @param [in] dato es el nuevo dato que va a incluirse en la lista
     */
    void inserta(Iterador<T> &i, T &dato);

    /**
     * @brief Método para borrar por en medio de la ListaDEnlazada<T>
     * @param [in] i es un Iterador<T> que indica el dato que se va a borrar de this
     */
    void borra(Iterador<T> &i);

    /**
     * @brief Función que permite insertar al inicio de la lista
     * @param [in] dato es el elemento T a insertar al principio de la lista
     */
    void insertaInicio(T& dato);

    /**
     * @brief Método que permite insertar al final de la lista
     * @param [in] dato es el elemento T a insertar al final de la lista
     */
    void insertaFin(T& dato);

    /**
     * @brief Método que permite borrar el elemento situado al inicio de la lista
     */
    void borrarInicio();

    /**
    * @brief Función que permite borrar el elemento situado al final de la lista
    */
    void borrarFinal();

    /**
     * @brief Función el dato de la ListaDEnlazada<T> que está situado al principio
     * @return dato T de la lista situado al inicio
     */
    T& inicio();

    /**
     * @brief Función el dato de la ListaDEnlazada<T> que está situado al final
     * @return dato T de la lista situado al final
     */
    T& fin();

    /**
     * @brief Método para conseguir el tamaño actual de elementos de la lista
     * @return número entero sin signo que corresponde al tamaño de la lista
     */
    unsigned getTam();

    virtual ~ListaDEnlazada();

};

template<class T>
ListaDEnlazada<T>::ListaDEnlazada()
    : cabecera(nullptr), cola(nullptr), tam(0){}

template<class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada<T> &original): cabecera(nullptr), cola(nullptr), tam(0){
    Nodo<T>* itOrg = original.cabecera;
    for (int i = 0; i < original.tam; ++i) {
        this->insertaFin(itOrg->dato);
        itOrg = itOrg->sig;
    }
}

template <class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::operator=(const ListaDEnlazada<T> &original) {
    if (*this == original)
        return *this;

    while (this->cabecera != nullptr){ //Borro los contenidos de la lista actual
        borrarInicio();
    }

    Nodo<T>* itOrg = original.cabecera; //Construyo una nueva lista en this igual a original
    for (int i = 0; i < original.tam; ++i) {
        this->insertaFin(itOrg->dato);
        itOrg = itOrg->sig;
    }

    return *this;
}

template <class T>
bool ListaDEnlazada<T>::operator==(const ListaDEnlazada<T> &original) {
    if(this->tam == original.tam){
        Nodo<T>* itOrg = original.cabecera;
        Nodo<T>* itThis = this->cabecera;

        for (int i = 0; i < original.tam; ++i) {
            if (itThis->dato != itOrg->dato)    // /!\ T debe tener el operador !=
                return false;
            itThis = itThis->sig;
            itOrg = itOrg->sig;
        }
        return true;
    }
    return false;
}

template <class T>
ListaDEnlazada<T> ListaDEnlazada<T>::operator+(const ListaDEnlazada<T> &original) {
    ListaDEnlazada<T> *aux = new ListaDEnlazada<T>(*this);
    aux->concatena(original);
    return *aux;
}

template <class T>
void ListaDEnlazada<T>::concatena(const ListaDEnlazada<T> &listaCont) {
    Nodo<T>* itAux = listaCont.cabecera;
    for (int i = 0; i < listaCont.tam; ++i) {
        this->insertaFin(itAux->dato);
        itAux = itAux->sig;
    }
}

template <class T>
Iterador<T> ListaDEnlazada<T>::iterador() {
    return Iterador<T> (cabecera);
}

template<class T>
void ListaDEnlazada<T>::inserta(Iterador<T> &i, T &dato) { //inserta en la posicion anterior apuntada por el it
    if(i.haySiguiente() == false && i.hayAnterior() == false)
        throw runtime_error("[ListaDEnlazada<T>::inserta] Se ha intentado insertar con un iterador sin siguiente o anterior.");

    if(i.hayAnterior() == false){ //Borra inicio
        insertaInicio(dato);
    } else if(i.haySiguiente() == false){
        insertaFin(dato);
    } else {
        Nodo<T> *nuevo = new Nodo<T>(dato,i.nodo->ant,i.nodo), *auxAnt = i.nodo->ant;
        auxAnt->sig = i.nodo->ant = nuevo; //El nodo auxAnt tiene como sig a Nuevo y también ocurre con el nodo del iterador y su ant
        ++tam;
    }
}

template<class T>
void ListaDEnlazada<T>::borra(Iterador<T> &i) { //borra el elemento referenciado por el iterador
    if(i.haySiguiente() == false && i.hayAnterior() == false)
        throw runtime_error("[ListaDEnlazada<T>::borra] Se ha intentado borrar con un iterador sin siguiente o anterior.");

    if(i.hayAnterior() == false){ //Borra inicio
        borrarInicio();
    } else if(i.haySiguiente() == false){
        borrarFinal();
    } else {
        Nodo<T>* auxAnt = i.nodo->ant, *auxSig = i.nodo->sig;
        auxAnt->sig = auxSig;
        auxSig->ant = auxAnt;
        i.nodo->nullAntSig();
        delete i.nodo;
        i.nodo = nullptr;
        --tam;
    }
}

template<class T>
void ListaDEnlazada<T>::insertaInicio(T &dato) {
    Nodo<T> *nuevo = new Nodo<T>(dato);
    if(cabecera == nullptr){
        cabecera = cola = nuevo;
    }else{
        nuevo->sig = cabecera;
        cabecera->ant = nuevo;
        cabecera = nuevo;
    }
    tam++;
}

template<class T>
void ListaDEnlazada<T>::insertaFin(T &dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if(cola == nullptr){
        cabecera = cola = nuevo;
    }else{
        cola->sig = nuevo;
        nuevo->ant = cola;
        cola = nuevo;
    }
    tam++;
}

template<class T>
void ListaDEnlazada<T>::borrarInicio(){
    if (cabecera == nullptr)
        throw runtime_error("[ListaDEnlazada<T>::borrarInicio] Se ha intentado borrar sin datos por el inicio de la lista.");

    Nodo<T>* borrar = cabecera;
    if (cabecera == cola){ // Sólo queda 1 nodo
        cabecera = cola = nullptr;
    }else{                  // Hay más de un nodo
        cabecera = cabecera->sig; //Actualizo sig y ant de cabecera
        cabecera->ant = nullptr;
        borrar->nullAntSig(); //Aislo borrar por destructor de Nodo
    }
    delete borrar;
    tam--;
}

template<class T>
void ListaDEnlazada<T>::borrarFinal(){
    if (cola == nullptr)
        throw runtime_error("[ListaDEnlazada<T>::borrarFinal] Se ha intentado borrar sin datos por el final de la lista.");

    Nodo<T>* borrar = cola;
    if(cola == cabecera){   //Sólo hay 1 nodo
        cola = cabecera = nullptr;
    }else{                  //Hay más de un nodo
        cola = cola->ant;
        cola->sig = nullptr;
    }
    borrar->nullAntSig();
    delete borrar;
    tam--;
}

template<class T>
T& ListaDEnlazada<T>::inicio() {
    if (cabecera == nullptr)
        throw runtime_error("[ListaDEnlazada<T>::inicio] Se ha intentado tomar un elemento vacio del inicio.");

    return cabecera->dato;
}

template<class T>
T& ListaDEnlazada<T>::fin() {
    if (cola == nullptr)
        throw runtime_error("[ListaDEnlazada<T>::inicio] Se ha intentado tomar un elemento vacio del final.");

    return cola->dato;
}

template<class T>
unsigned ListaDEnlazada<T>::getTam(){
    return this->tam;
}

template<class T>
ListaDEnlazada<T>::~ListaDEnlazada(){
    while (cabecera != nullptr){
        borrarInicio();
    }
}

#endif //PR2_LISTADENLAZADA_H
