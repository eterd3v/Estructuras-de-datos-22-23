/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 26/10/2022
 */
#ifndef PR2_NODO_H
#define PR2_NODO_H

#include <stdexcept>

/**
 * @brief Clase que actúa como nodo esencial para la estructura de datos de ListaDEnlazada<T>
 * @tparam T es el tipo dato de que es almacenado por el nodo.
 */
template <class T>
class Nodo {
public:
    T dato;         ////Es el dato de tipo T que almacena el Nodo<T>
    Nodo<T>* ant;   ////Es un puntero que indica la posición del anterior Nodo<T>
    Nodo<T>* sig;   ////Es un puntero que indica la posición del posterior Nodo<T>

    /**
     * @brief Constructor por defecto de la clase Nodo<T>
     */
    Nodo();

    /**
     * @brief Constructor parametrizado de la clase Nodo<T>
     * @param [in] dato es el elemento que va a ser almacenado en el nodo.
     * @param [in] nodoAnt es el puntero al Nodo<T> que se encuentra en una posición anterior. Por defecto es un puntero nulo
     * @param [in] nodoSig es el puntero al Nodo<T> que se encuentra en una posición posterior. Por defecto es un puntero nulo
     */
    Nodo(T& dato, Nodo<T>* nodoAnt = nullptr, Nodo<T>* nodoSig = nullptr);

    /**
     * @brief Método que pone como nulos los Nodo<T> anterior y siguiente
     */
    void nullAntSig();

    /** Getters de Nodo*/
    T getDato() const;
    Nodo<T>* getAnt() const ;
    Nodo<T>* getSig() const ;

    /** Setters de Nodo*/
    void setDato(T dato);
    void setAnt(Nodo<T> *ant);
    void setSig(Nodo<T> *sig);

    /**
     * @brief Setter de los punteros de Nodo<T> de this
     * @param [in] ant es el Nodo<T> de la anterior posición que se desea establecer. Por defecto es un puntero nulo
     * @param [in] sig es el Nodo<T> de la siguiente posición que se desea establecer. Por defecto es un puntero nulo
     */
    void setAntSig(Nodo<T> *ant = nullptr, Nodo<T> *sig = nullptr);

    virtual ~Nodo();
};

template<class T>
Nodo<T>::Nodo():dato(new T), ant(nullptr), sig(nullptr){}

template<class T>
Nodo<T>::Nodo(T& dato, Nodo<T>* nodoAnt, Nodo<T>* nodoSig):
    dato(dato), ant(nodoAnt), sig(nodoSig){}

template<class T>
Nodo<T>::~Nodo(){
    if(ant == nullptr && sig == nullptr){
        delete ant;
        delete sig;
    }else
        throw std::runtime_error("Nodo<T>::~Nodo - El nodo no se puede eliminar, ant o sig no son punteros nulos.");
}

template<class T>
void Nodo<T>::setAntSig(Nodo<T> *ant, Nodo<T> *sig) {
    this->setAnt(ant);
    this->setPos(sig);
}

template<class T>
void Nodo<T>::nullAntSig() {
    ant = sig = nullptr;
}

template<class T>
T Nodo<T>::getDato() const {
    return dato;
}

template<class T>
Nodo<T>* Nodo<T>::getAnt() const {
    return ant;
}

template<class T>
Nodo<T>* Nodo<T>::getSig() const {
    return sig;
}

template<class T>
void Nodo<T>::setDato(T dato) {
    Nodo::dato = dato;
}

template<class T>
void Nodo<T>::setAnt(Nodo<T> *ant) {
    Nodo::ant = ant;
}

template<class T>
void Nodo<T>::setSig(Nodo<T> *sig) {
    Nodo::sig = sig;
}

#endif //PR2_NODO_H
