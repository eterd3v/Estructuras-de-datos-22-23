/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 03/11/2022
 */

#ifndef PR2_AVL_H
#define PR2_AVL_H

#include "NodoAVL.h"
#include <string>
#include <stdexcept>
#include "VDinamico.h"

using namespace std;

/**
 * @brief Implementación de la estructura de datos correspondiente a un árbol AVL
 * @tparam T Tipo de dato con el que se instancia la clase
 */
template <class T>
class AVL {
private:

    ///Es el nodo raíz del árbol AVL
    NodoAVL<T>* raiz;
    ///Almacena el número de nodos con datos del árbol
    unsigned long tam;

    /**
     * @brief Método recursivo para copiar un árbol AVL en preorden
     * @param [in] nodo Es el nodo padre del árbol AVL donde se va a hacer la copia recursiva.
     * @param [in] nodoOrig Es el nodo padre del árbol que va a ser copiado recursivamente.
     */
    void copiaPreorden(NodoAVL<T> *&nodo, NodoAVL<T> *&nodoOrig);

    /**
     * @brief Función recursiva para comprobar si dos árboles AVL son iguales en contenido y estructura.
     * @param [in] nodo Es el nodo padre del árbol AVL que se va a comprobar junto con nodoOrig.
     * @param [in] nodoOrig Es el nodo padre del otro árbol que va a comprobarse con nodo.
     * @return true si ambos árboles son iguales. En caso contrario devuelve false.
     */
    bool igualdadPreorden(NodoAVL<T> *&nodo, NodoAVL<T> *&nodoOrig);

    /**
     * @brief Método recursivo para insertar un dato en el árbol AVL en preorden.
     * @param [in] nodo Es el nodo padre del árbol AVL de donde se va a partir para la recursividad.
     * @param [in] dato Es el dato que se busca insertar en el AVL
     * @return 0 si no fue insertado y 1 si la insercción fue existosa.
     */
    int insertaDato(NodoAVL<T>* &nodo, T& dato);

    /**
     * @brief Método para rotar nodos por balanceos
     * @param [in] p Es el nodo que se busca balancear a la izquierda
     */
    void rotIzqda(NodoAVL<T>* &p);

    /**
     * @brief Método para rotar nodos por balanceos
     * @param [in] p Es el nodo que se busca balancear a la derecha
     */
    void rotDecha(NodoAVL<T>* &p);

    /**
     * @brief Función recursiva para buscar un dato en el árbol en preorden
     * @param [in] dato Es el dato de tipo T a buscar
     * @param [in] nodo Es el nodo padre del árbol por el que empezar la búsqueda.
     * @return nullptr si no
     */
    T* buscaPreorden(T& dato, NodoAVL<T>* &nodo);

    /**
     * @brief Función recursiva en inorden para el método recorreInorden
     * @param [in] vDatos Es el vector dinámico que va a guardar los elementos del árbol AVL
     * @param [in] nodo Es el nodo padre del árbol AVL por el que empezar la recursividad.
     */
    void inordenVector(VDinamico<T*> &vDatos, NodoAVL<T>* &nodo);

    /**
     * @brief Método para conseguir la altura de un árbol AVL
     * @param [in] nodo Es el nodo padre del árbol por el que empezar a contar la altura.
     * @return Entero sin signo que corresponde a la altura actual del árbol.
     */
    unsigned alturaAVL(NodoAVL<T>* &nodo) const;

    /**
     * @brief Función recursiva para borrar un dato del árbol AVL en postorden
     * @param [in] nodo Es el nodo padre del árbol AVL por el borrar de forma recursiva.
     */
    void borrarPostOrden(NodoAVL<T>* &nodo);

public:

    ///@brief Constructor por defecto de la clase AVL
    AVL();

    /**
     * @brief Constructor copia de la clase AVL
     * @param [in] orig Es una instancia ya existente de la clase AVL
     */
    AVL(const AVL& orig);

    /**
     * @brief Operador de asignación de la clase AVL
     * @param [in] orig Es el árbol AVL ya existente de la que se va copiar.
     * @return Referencia de clase copiada para concatenar lecturas o escrituras.
     */
    AVL& operator=(const AVL& orig);

    /**
     * @brief Operador de igualdad de la clase AVL
     * @param [in] orig Es el árbol AVL ya existente de la que se va copiar.
     * @return true si los árboles son iguales en contenido y estructura. false en cualquier otro caso
     */
    bool operator==(AVL& orig) const;

    /**
     * @brief Función para insertar un dato T en el AVL.
     * @param [in] dato Es el dato simple o compuesto que se desea incluir en el AVL.
     * @return True si la inserción ha sido existosa. False en cualquier otro caso.
     */
    bool inserta(T &dato);

    /**
     * @brief Método para borrar todos los nodos del árbol AVL sin destruir el objeto
     */
    void borraTodo();

    /**
     * @brief Método para buscar de forma recursiva el parámetro dato
     * @param [in] dato Es un objeto de tipo T que se desea encontrar en el árbol
     * @return Si se encuentra el dato se devuelve un puntero al dato en el AVL o nullptr en cualquier otro caso
     */
    T* buscaRec(T& dato);

    /**
     * @brief Método para buscar de forma iterativa el parámetro dato
     * @param [in] dato Es un objeto de tipo T que se desea encontrar en el árbol
     * @return Si se encuentra el dato se devuelve un puntero al dato en el AVL o nullptr en cualquier otro caso
     */
    T* buscaIt(T &dato) const;

    /**
     * @brief Función para recorrer en inorden el árbol AVL
     * @return Vector dinámico con un puntero a cada dato que guarda el árbol AVL
     */
    VDinamico<T*> recorreInorden();

    /**
     * @brief Función para conseguir el número de elementos actual del árbol AVL
     * @return Número entero long sin signo con la cantidad de elementos correspondiente
     */
    unsigned long numElementos() const;

    /**
     * @brief Conseguir la altura actual del árbol AVL
     * @return Número entero sin signo con la altura correspondiente
     */
    unsigned int altura();

    ///@brief Destructor de la clase AVL
    ~AVL();

};

template <class T>
AVL<T>::AVL(): raiz(nullptr), tam(0){}

template <class T>
AVL<T>::AVL(const AVL<T> &orig) : raiz(nullptr), tam(0) {
    NodoAVL<T>* nodoOrig = orig.raiz;
    copiaPreorden(this->raiz, nodoOrig);
}

template <class T>
void AVL<T>::copiaPreorden(NodoAVL<T>* &nodo, NodoAVL<T>* &nodoOrig) {
    if(nodoOrig){
        nodo = new NodoAVL<T>(nodoOrig->dato, nodoOrig->bal);
        tam++;
        copiaPreorden(nodo->izq, nodoOrig->izq);
        copiaPreorden(nodo->der, nodoOrig->der);
    }
}

template <class T>
AVL<T> &AVL<T>::operator=(const AVL<T> &orig) {
    if(*this == orig)
        return *this;

    borrarPostOrden(raiz);
    copiaPreorden(raiz, orig.raiz);

    return *this;
}

template <class T>
bool AVL<T>::operator==(AVL<T> &orig) const {
    if(orig.tam == this->tam)
        return igualdadPreorden(this->raiz, orig.raiz);
    return false;
}

template <class T>
bool AVL<T>::igualdadPreorden(NodoAVL<T> *&nodo, NodoAVL<T> *&nodoOrig) {
    bool aux = false;                                               ///Suponemos falso por si es puntero nulo
    if(nodo != nullptr && nodoOrig != nullptr){                     ///Si existe el nodo en ambos
        if (nodo->dato == nodoOrig->dato)                           ///Si el dato es el mismo, aux=true (sustituye false de los nullptr)
            aux = true;
        if(nodo->esPadre() && nodoOrig->esPadre()){                 ///Si el nodo es padre de 1 o 2 hijos
            if(aux && nodo->hayIzq() && nodoOrig->hayIzq())         ///Hay nodo izquierda. Entra si ya sabe que el dato es el mismo en ambos AVL
                aux = aux & igualdadPreorden(nodo->izq,nodoOrig->izq);
            if(aux && nodo->hayDer() && nodoOrig->hayDer())         ///Hay nodo derecha. Entra si ya sabe que el dato es el mismo en ambos AVL
                aux = aux & igualdadPreorden(nodo->der, nodoOrig->der);
        }
    }
    return aux;
}

template<class T>
bool AVL<T>::inserta(T &dato) {
    return insertaDato(raiz, dato);
}

template<class T>
int AVL<T>::insertaDato(NodoAVL<T>* &nodo, T &dato) {
    NodoAVL<T> *p = nodo;
    int deltaH = 0; //Variación de la altura del subárbol
    if (!p) {       //En la recursión se llega a un nodo hoja
        p = new NodoAVL<T>(dato);
        tam++;
        nodo = p;
        deltaH = 1;
    } else if (dato > p->dato) {
        if (insertaDato(p->der, dato)) {
            p->bal--;
            if (p->bal == -1)
                deltaH = 1;
            else if (p->bal == -2) {
                if (p->der->bal == 1)
                    rotDecha(p->der); //Rotación doble caso 3
                rotIzqda(nodo); //Rotación simple caso 4
            }
        }
    } else if (dato < p->dato) {
        if (insertaDato(p->izq, dato)) {
            p->bal++;
            if (p->bal == 1)
                deltaH = 1;
            else if (p->bal == 2) {
                if (p->izq->bal == -1)
                    rotIzqda(p->izq); //Rotación doble caso 2
                rotDecha(nodo); //Rotación simple caso 1
            }
        }
    }
    return deltaH;
}

template<typename T>
void AVL<T>::rotIzqda(NodoAVL<T>* &p){
    NodoAVL<T> *q = p, *r;
    p = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if(q->bal > 0) r->bal += q->bal;
}


template<typename T>
void AVL<T>::rotDecha(NodoAVL<T>* &p){
    NodoAVL<T> *q = p, *l;
    p = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if(q->bal < 0) l->bal -= -q->bal;
}

template <class T>
void AVL<T>::borraTodo() {
    if(!(raiz== nullptr)){
        borrarPostOrden(raiz);
    }
}

template <class T>
T* AVL<T>::buscaRec(T &dato) {
    return buscaPreorden(dato, raiz);
}

template <class T>
T* AVL<T>::buscaPreorden(T &dato, NodoAVL<T>* &nodo){
    if(nodo){
        if(nodo->dato == dato)                      //Preorden
            return &(nodo->dato);
        T* datoAVL;                                 //Si es hijo izq o der
        (dato < nodo->dato) ? (datoAVL = buscaPreorden(dato, nodo->izq)) : (datoAVL = buscaPreorden(dato, nodo->der));
        if(datoAVL)                                 //Si ya ha encontrado el dato, lo devuelve
            return datoAVL;
    }
    return nullptr;
}

template<class T>
T* AVL<T>::buscaIt(T &dato) const {

    NodoAVL<T>* miRaiz = this->raiz;

    while(miRaiz){
        if(dato == miRaiz->dato)
            return &(miRaiz->dato);
        if (dato < miRaiz->dato && miRaiz->izq)
            miRaiz = miRaiz->izq;
        else if (dato > miRaiz->dato && miRaiz->der)
            miRaiz = miRaiz->der;
        else
            miRaiz = nullptr;
    }

    return nullptr;
}

template <class T>
VDinamico<T*> AVL<T>::recorreInorden() {
    VDinamico<T*> vDatos;
    inordenVector(vDatos,this->raiz);
    return vDatos;
}

template <class T>
void AVL<T>::inordenVector(VDinamico<T*> &vDatos, NodoAVL<T>* &nodo) {
    if(nodo){
        inordenVector(vDatos,nodo->izq);
        vDatos.insertar(&(nodo->dato));
        inordenVector(vDatos,nodo->der);
    }
}

template<class T>
unsigned long AVL<T>::numElementos() const {
    return tam;
}

template<class T>
unsigned AVL<T>::altura(){
    return alturaAVL(this->raiz);
}

template<class T>
unsigned AVL<T>::alturaAVL(NodoAVL<T> *&nodo) const{
    if(nodo == nullptr)     //Si es nodo nulo no lo procesa
        return 0;
    //Existe el nodo => Luego se devuelve un +1 en return
    unsigned altIzq = this->alturaAVL(nodo->izq);
    unsigned altDer = this->alturaAVL(nodo->der);

    if(altIzq >= altDer)
        return 1 + altIzq;
    return 1 + altDer;      //Si llega aquí es que la altura de la derecha es mayor
}

template <class T>
AVL<T>::~AVL() {
    borraTodo();
}

template<class T>
void AVL<T>::borrarPostOrden(NodoAVL<T>* &nodo) {
    if(nodo){
        borrarPostOrden(nodo->der);
        borrarPostOrden(nodo->izq);
        nodo->izq = nodo->der = nullptr;
        delete nodo;
    }
}

#endif //PR2_AVL_H
