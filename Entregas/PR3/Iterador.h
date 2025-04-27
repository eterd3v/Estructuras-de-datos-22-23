/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 26/09/2022
 */

#ifndef PR2_ITERADOR_H
#define PR2_ITERADOR_H

#include "Nodo.h"

template<class T>       //Código necesario para friend class con Iterador<T>
class ListaDEnlazada;   //Código necesario para friend class con Iterador<T>

/**
 * @brief Clase que encapsula el comportamiento de la clase Nodo con ListaDEnlazada
 * @tparam T es el tipo dato de plantilla de la clase.
 */
template<class T>
class Iterador{
private:
    ///Nodo<T> que es encapsulado por la clase Iterador<T>
    Nodo<T>* nodo;
    friend class ListaDEnlazada<T>;
public:
    /**
     * @brief Constructor por defecto de la clase Iterador
     */
    Iterador():nodo(nullptr) {}

    /**
     * @brief Constructor parametrizado de la clase Iterador
     * @param [in] nodo es el nodo con el que se asocia el Iterador
     */
    explicit Iterador(Nodo<T>* nodo) : nodo(nodo) {}

    /**
     * @brief Método para conocer si el Iterador tiene un nodo anterior
     * @return true si tiene un elemento anterior. false en cualquier otro caso
     */
    bool hayAnterior() { return nodo->ant != nullptr; }

    /**
     * @brief Método para conocer si el Iterador tiene un nodo posterior
     * @return true si tiene un elemento posterior. false en cualquier otro caso
     */
    bool haySiguiente() { return nodo->sig != nullptr; }

    /**
     * @brief Función para ir al nodo anterior del Iterador<T>
     */
    void anterior() {
        if (nodo->ant != nullptr)
            nodo = nodo->ant;
    }

    /**
     * @brief Función para ir al nodo siguiente del Iterador<T>
     */
    void siguiente() {
        if (nodo->sig != nullptr)
            nodo = nodo->sig;
    }

    /**
     * @brief Operador de asignación de Iterador<T>
     * @param [in] orig es el objeto que se va a asignar al iterador this
     * @return referencia sobre la instancia de Iterador<T> para poder seguir realizando asignaciones.
     */
    Iterador& operator=(const Iterador<T>& orig){
        nodo = orig.nodo;
        return *this;
    }

    /**
     * @brief Método para acceder al dato que es apuntado por el iterador
     * @return dato de tipo T apuntado por el nodo
     */
    T& dato() { return nodo->dato; }

};


#endif //PR2_ITERADOR_H
