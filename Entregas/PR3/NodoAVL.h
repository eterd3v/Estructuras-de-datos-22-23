/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 3/11/2022
 */

#ifndef PR2_NODOAVL_H
#define PR2_NODOAVL_H

#include <cstdlib>
#include <stdexcept>

using namespace std;

///@brief Clase que implementa un nodo de un árbol AVL
template <class T>
class NodoAVL {
public:

    ///@brief Constructor por defecto de la clase NodoAVL
    ///Instancia un nodo vacío, de balance 0 y con hijos nulos
    NodoAVL();

    /**
     * @brief Constructor parametrizado modificado de la clase NodoAVL
     * Es igual al constructor por defecto a excepción del dato a incluir en el nodo.
     * @param [in] dato Es el dato a incluir en el nodo.
     */
    NodoAVL(T &dato);

    /**
     * @brief Constructor parametrizado de NodoAVL
     * @param [in] dato Es el dato a incluir en el nodo
     * @param [in] bal Es el balanceo correspondiente del nodo en el árbol AVL
     * @param [in] izq Es un puntero al hijo izquierdo del nodo. Por defecto es nullptr
     * @param [in] der Es un puntero al hijo derecho del nodo. Por defecto es nullptr
     */
    NodoAVL(T &dato, char bal, NodoAVL<T>* izq = nullptr, NodoAVL<T>* der = nullptr);

    /**
     * @brief Comprueba si el nodo tiene un hijo izquierdo.
     * @return true si tiene hijo izquierdo. false en cualquier otro caso.
     */
    bool hayIzq();

    /**
     * @brief Comprueba si el nodo tiene un hijo derecho.
     * @return true si tiene hijo derecho. false en cualquier otro caso.
     */
    bool hayDer();

    /**
     * @brief Comprueba si el NodoAVL es un nodo padre
     * @return true si tiene hijo izquierdo o derecho. false en cualquier otro caso.
     */
    bool esPadre();

    /**
     * @brief Comprueba si el NodoAVL es un nodo hoja
     * @return true si el nodo es hoja. false en cualquier otro caso.
     */
    bool esHoja();

    /// Es el hijo izquierdo del nodo como un puntero de la clase
    NodoAVL<T>* izq;
    /// Es el hijo derecho del nodo como un puntero de la clase
    NodoAVL<T>* der;
    /// Es el dato que almacena el NodoAVL
    T dato;
    /// Es el balanceo actual del nodo
    char bal;

    ///@brief Destructor de la clase
    ~NodoAVL();

};

template<class T>
NodoAVL<T>::NodoAVL() : dato(NULL), izq(nullptr), der(nullptr), bal(0) {}

template<class T>
NodoAVL<T>::NodoAVL(T &dato) : dato(dato), izq(nullptr), der(nullptr), bal(0){}

template<class T>
NodoAVL<T>::NodoAVL(T &dato,char bal, NodoAVL<T> *izq, NodoAVL<T> *der) : dato(dato), izq(izq), der(der), bal(bal) {}

template<class T>
bool NodoAVL<T>::hayIzq() {
    if(izq == nullptr)
        return false;
    return true;
}

template<class T>
bool NodoAVL<T>::hayDer() {
    if(der == nullptr)
        return false;
    return true;
}

template<class T>
bool NodoAVL<T>::esPadre() {
    if(hayIzq() || hayDer())    //Con 1 o 2 hijos
        return true;
    return false;
}

template<class T>
bool NodoAVL<T>::esHoja() {
    if(!hayIzq() && !hayDer())  //Sin hijos
        return true;
    return false;
}

template<class T>
NodoAVL<T>::~NodoAVL() {
    if(esPadre())
        throw runtime_error(string("[NodoAVL<T>::~NodoAVL] Se está intentando borrar un nodo padre."));
}

#endif //PR2_NODOAVL_H
