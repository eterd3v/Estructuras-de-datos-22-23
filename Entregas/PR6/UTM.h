/*
 * File:   UTM.h
 * Author: Lorena
 *
 * Created on 14 de octubre de 2021, 11:25
 */

#ifndef UTM_H
#define UTM_H

///@brief Clase que implementa coordenadas cartesianas
class UTM {
public:
    ///@brief Constructor por defecto de UTM
    UTM();

    ///@brief Constructor parametrizado de UTM
    ///@param [in] longitud Es un número flotante que corresponde a la longitud de coordenadas UTM
    ///@param [in] latitud Es un número flotante que corresponde a la latitud de coordenadas UTM
    UTM(const float &longitud,const float &latitud);

    ///@brief Constructor copia
    UTM(const UTM& orig);

    ///@brief Operador de asignación de UTM
    UTM& operator=(const UTM &orig);

    /**
     * @brief Método para asignar la longitud y la latitud de coordenadas UTM
     * @param [in] longitud Son las coordenas de longitud a sobreescribir
     * @param [in] latitud Son las coordenas de latitud a sobreescribir
     */
    void asignar(const float &longitud, const float &latitud);

    ///@brief Operador de igualdad de UTM
    bool operator==(const UTM &orig);

    ///@brief Operador de desigualdad de UTM
    bool operator!=(const UTM &orig);

//    bool operator<(const UTM &orig);
//    bool operator>(const UTM &orig);

    /**
     * @brief Método para aumentar tanto la longitud y la latitud en una cantidad especificada
     * @param cantidad Es el número flotante a aumentar en ambas coordenadas
     */
    void aumentar(const float &cantidad);

    /**
     * @brief Método para disminuir tanto la longitud y la latitud en una cantidad especificada
     * @param cantidad Es el número flotante a disminuir en ambas coordenadas
     */
    void disminuir(const float &cantidad);

    /// Setters y getters de longitud y latitud
    void setLongitud(float longitud);
    float getLongitud() const;
    void setLatitud(float latitud);
    float getLatitud() const;

    ///@brief Destructor
    virtual ~UTM();
private:
    float longitud;
    float latitud;
};

#endif /* UTM_H */

