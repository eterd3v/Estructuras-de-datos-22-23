///@author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
///@date 15-12-2022

#ifndef PR6_RANGO_H
#define PR6_RANGO_H

#include "UTM.h"
#include <iostream>

using namespace std;

///@brief Clase que implementa un rango de coordenadas Coords
class Rango {
private:
    ///Coordenadas minimas del rango
    UTM min;
    ///Coordenadas máximas del rango
    UTM max;
public:
    ///@brief Constructor por defecto del Rango
    Rango();

    ///@brief Constructor parametrizado del Rango
    Rango(const UTM &min,const UTM&max);

    ///@brief Constructor parametrizado del Rango
    Rango(const float &xMin,const float &yMin,const float &xMax,const float &yMax);

    ///@brief Constructor copia de Rango
    Rango(const Rango &orig);

    ///@brief Operador de asignación de Rango
    Rango& operator=(const Rango &orig);

    /** Operadores de desplazamiento del Rango por el eje de coordenadas */
    ///@brief Operador para desplazar el Rango justo a la DERECHA de donde está actualmente
    void operator+();
    ///@brief Operador para desplazar el Rango justo a la IZQUIERDA de donde está actualmente
    void operator-();
    ///@brief Operador para desplazar el Rango justo hacia ARRIBA de donde está actualmente
    void operator++();
    ///@brief Operador para desplazar el Rango justo hacia ABAJO de donde está actualmente
    void operator--();

    /**
     * @brief Método para comprobar si unas coordenas UTM pertenecen al rango (menor o igual)
     * @param [in] coords Son las coordenadas UTM a comprobar
     * @return True si las coordenadas coords pertenecen al Rango. False en cualquier otro caso
     */
    bool contiene(const UTM &coords) const;

    /**
     * @brief Método para comprobar si Rango dado esta dentro a otro o no, ya sea igual o menor a este
     * @param [in] rango Es el Rango que va a comprobarse si está dentro del otro (this)
     * @return True si realmente el rango contiene a this. False en cualquier en otro caso.
     */
    bool contiene(const Rango &rango) const;

    /**
     * @brief Método para modificar dado una distancia todas las coordenadas del Rango desde los vértices.
     * Si en algún momento se invierten los vértices estos se intercambiarían
     * @param [in] distancia Es un número flotante con el que modificar todas las coordenadas del rango
     */
    void modificar(const float &distancia);

    /**
     * @brief Método para conseguir la intersección de dos objeto Rango. En caso de no tener espacio en común saca una
     * excepción de tipo logic_error
     * @param [in] rango Es el rango con el que se va a realizar la intersección
     * @return Rango nuevo que corresponde a la intersección de ambos rangos.
     */
    Rango interseccion(const Rango &rango) const;

    /**
     * @brief Método para dar la distancia entre max y min del eje X
     * @return Número flotante con la distancia de la longitud
     */
     float distLong() const;

    /**
     * @brief Método para dar la distancia entre max y min del eje Y
     * @return Número flotante con la distancia de la latitud
     */
    float distLati() const;

    ///@brief Método para actualizar que UTM es el máximo y cuál es el mínimo
    void actualizar();

    ///Setters y getters de los atributos
    const UTM &getMin() const;
    void setMin(const UTM &min);
    const UTM &getMax() const;
    void setMax(const UTM &max);

    ///Getters directos de coordenadas
    const float getMinX() const;
    const float getMinY() const;
    const float getMaxX() const;
    const float getMaxY() const;
    const UTM getCentro() const;

    /**
     * @brief Método que devuelve una cadena de caracteres con las coordenadas relativas al Rango
     * @return Cadena de caracteres con las posiciones del Rango
     */
    string toString() const;

    ///@brief Destructor
    ~Rango();
};


#endif //PR6_RANGO_H
