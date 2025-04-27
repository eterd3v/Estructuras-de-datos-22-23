///@author Antonio Javier Armenteros Martínez
///@date 15-12-2022

#ifndef PR6_MALLAREGULAR_H
#define PR6_MALLAREGULAR_H

#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <cmath>
#include "Rango.h"
#include "UTM.h"

using namespace std;

template<class T>
class MallaRegular;

///@brief Clase que implementa el nodo de MallaRegular
template <class T>
class Casilla{
private:
    friend class MallaRegular<T>;
    list<T> puntos;
public:
    ///@brief Constructor por defecto de Casilla
    Casilla() = default;

    /**
     * @brief Función para insertar un nuevo dato T en la Casilla
     * @param [in] dato Es el dato de tipo T a incluir en la lista de puntos
     */
    void insertar(const T &dato) {puntos.push_back(dato);}

    /**
     * @brief Método para buscar un dato en la Casilla
     * @param [in] dato Es el dato de tipo T a buscar en la lista de puntos
     * @return Puntero al dato T si es encontrado. En cualquier otro caso devuelve nullptr
     */
    T* buscar(const T &dato);

    /**
     * @brief Método para borrar un dato ya existente en la Casilla
     * @param [in] dato Es el dato de tipo T a borrar en la lista de puntos
     * @return True si el dato ha sido borrado con éxito. False en cualquier otro caso.
     */
    bool borrar(const T &dato);

    ///@brief Destructor por defecto
    ~Casilla() = default;
};

template<class T>
T* Casilla<T>::buscar(const T &dato){
    for (auto it = puntos.begin(); it != puntos.end(); ++it )
        if(*it == dato)
            return &(*it);
    return nullptr;
}

template<class T>
bool Casilla<T>::borrar(const T &dato){
    for (auto it = puntos.begin(); it != puntos.end(); ++it )
        if(*it == dato){
            puntos.erase(it);
            return true;
        }
    return false;
}

///@brief Clase que implementa la estructura de datos de malla regular
template <class T>
class MallaRegular {
private:
    ///Rango de coordenadas correspondiente a la malla
    Rango rangoMalla;
    ///Tamaño de las Casillas
    Rango tamCasilla;
    ///Número de casillas almacenadas en la malla
    unsigned int nCasillas;
    ///Matriz que va a almacenar los nodos de la matriz
    vector<vector<Casilla<T>>> matriz;

    /**
     * @brief Método para obtener la casilla dado unas coordenadas
     * @param [in] x Es un número flotante que corresponde a la coordenada X que está incluido en la casilla
     * @param [in] y Es un número flotante que corresponde a la coordenada Y que está incluido en la casilla
     * @return Puntero de la Casilla que contiene las coordenadas (x,y)
     */
    Casilla<T> *obtenerCasilla(const float &x,const float &y);
public:
    ///@brief Constructor por defecto de MallaRegular.
    MallaRegular();

    /**
     * @brief Constructor parametrizado de MallaRegular.
     * @param [in] rangoMalla Es el Rango de coordenadas que va a manejar la malla .
     * @param [in] nDiv Es un entero positivo que representa las divisiones que se van a dar en la malla.
     */
    MallaRegular(const Rango &rangoMalla, const unsigned int &nDiv);

    /**
     * @brief Método para insertar un dato en la MallaRegular
     * @param [in] x Es la coordenada X donde se va insertar el dato
     * @param [in] y Es la coordenada Y donde se va insertar el dato
     * @param [in] dato Es el dato que va a ser introducido en las coordenadas (x,y)
     */
    void insertar(const float &x, const float &y, const T& dato);

    /**
     * @brief Función para buscar todos los elementos que estén dentro de un Rango de búsqueda
     * @param [in] r Es el Rango donde se va a buscar los objetos tipo T
     * @return Vector de elementos T que coinciden con el Rango de búsqueda
     */
    vector<T> buscarRango(const Rango &r);

    ///@brief Método que devuelve el máximo de elementos por Casilla en forma de entero sin signo
    unsigned maxElementosPorCelda();

    ///@brief Método que devuelve el promedio de elementos por Casilla en forma de número flotante
    float promedioElementosPorCelda();

    ///@brief Función para sacar por consola los datos relativos a la MallaRegular
    void datosMalla();

    ///@brief Método para conseguir el Rango total de la MallaRegular
    const Rango& getRangoMalla() const;

    ///@brief Destructor por defecto
    virtual ~MallaRegular();
};

template<class T>
Casilla<T>* MallaRegular<T>::obtenerCasilla(const float &x,const float &y){
    int i = (x - rangoMalla.getMinX()) / tamCasilla.distLong();
    int j = (y - rangoMalla.getMinY()) / tamCasilla.distLati();
    if(rangoMalla.contiene(UTM(x,y)))
        return &matriz[j][i]; //Filas es la j, Columnas es la i
}

template<class T>
MallaRegular<T>::MallaRegular() : rangoMalla(), tamCasilla(), nCasillas(0), matriz() {};

template<class T>
MallaRegular<T>::MallaRegular(const Rango &rangoMalla, const unsigned int &nDiv) : rangoMalla(rangoMalla), tamCasilla(), nCasillas(nDiv * nDiv){
    float tamCasX = rangoMalla.distLong() / nDiv;
    float tamCasY = rangoMalla.distLati() / nDiv;
    tamCasilla.setMin(UTM(rangoMalla.getMinX()          ,rangoMalla.getMaxY() - tamCasY)); //Coloco la casilla modelo en el mismo sitio en el que se podría recorrer la matriz
    tamCasilla.setMax(UTM(rangoMalla.getMinX() + tamCasX,rangoMalla.getMaxY()          ));
    matriz.insert(matriz.begin(), nDiv, vector<Casilla<T> >(nDiv));
};

template<class T>
void MallaRegular<T>::insertar(const float &x, const float &y, const T& dato){
    Casilla<T> *c = obtenerCasilla(x,y);
    if(c)
        c->insertar(dato);
}


template<class T>
vector<T> MallaRegular<T>::buscarRango(const Rango &r){
    vector<T> aux;
    try{ //Hay un método (intersección) puede provocar una excepción
        Rango g = rangoMalla.interseccion(r); //Tomo la intersección del rango con el rango de la malla
        for(int i = 0; i < matriz.size(); ++i)
            for(int j = 0; j < matriz.size(); ++j)
                for(auto it = matriz[i][j].puntos.begin(); it != matriz[i][j].puntos.end() ; ++it)
                    if(g.contiene((*it)->getPos())) //Si el dato está dentro de la intersección se añade
                        aux.push_back(*it);
    }catch(exception &err){
        cout << err.what() << endl;
    }
    return aux;
}

template<class T>
unsigned MallaRegular<T>::maxElementosPorCelda(){
    unsigned int max = 0;
    for(int i = 0; i < matriz.size(); ++i)
        for(int j = 0; j < matriz.size(); ++j)
            if(matriz[i][j].puntos.size() > max) //Guardo el máximo, que es el tamaño del contenedor
                max = matriz[i][j].puntos.size();
    return max;
}

template<class T>
float MallaRegular<T>::promedioElementosPorCelda(){
    unsigned int suma = 0;
    for(int i = 0; i < matriz.size(); ++i)
        for(int j = 0; j < matriz.size(); ++j)
            suma += matriz[i][j].puntos.size(); //Sumo el tamaño que tiene cada lista
    return (float) suma / (float) sqrt(nCasillas);
}


template<class T>
void MallaRegular<T>::datosMalla(){
    cout << "Coordenadas " << rangoMalla.toString() << endl;
    cout << "Tamaño de la longitud de las casillas: " << rangoMalla.distLong()/sqrt(nCasillas) << endl;
    cout << "Tamaño de la latitud de las casillas: " << rangoMalla.distLati()/sqrt(nCasillas) << endl;
    cout << "Promedio de elementos por celda: " << to_string(promedioElementosPorCelda()) << endl;
    cout << "Maximo de elementos por celda: " << to_string(maxElementosPorCelda()) << endl;
}

template<class T>
const Rango& MallaRegular<T>::getRangoMalla() const {
    return rangoMalla;
}


template<class T>
MallaRegular<T>::~MallaRegular() {};

#endif //PR6_MALLAREGULAR_H
