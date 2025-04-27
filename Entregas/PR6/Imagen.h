/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 01/12/2022
 */
#ifndef IMAGENES_IMAGEN_H
#define IMAGENES_IMAGEN_H

#include "fecha.h"
#include "Etiqueta.h"
#include "UTM.h"
#include <string>
#include <deque>
#include <vector>
#include <iostream>

using namespace std;

class Etiqueta;

/**
 * @brief Clase que simula un archivo de imagen.
 */
class Imagen {
private:
    ///Identificador único de cada Imagen
    string id;
    ///Nombre de la Imagen
    string nombre;
    ///Etiquetas de la Imagen
    deque<Etiqueta*> etiquetada;
    ///Fecha de la Imagen
    Fecha fecha;
    ///Tamaño que ocupa la Imagen
    unsigned int tam;
    ///Cantidad de likes que posee actualmente la Imagen
    unsigned int likes;
    ///Posición geográfica donde fue tomada la Imagen
    UTM pos;
public:

    /** Construye un objeto Imagen con atributos por defecto
     *  @brief Constructor por defecto de la clase Imagen
     */
    Imagen();

    /** Constructor de la clase Imagen que utilizará como atributos los datos de los parámetros
     * @brief Constructor parametrizado de la clase Imagen
     * @param [in] id Es una cadena de caraceteres que representa el identificador de la imagen
     * @param [in] usr Es un puntero a un Usuario que está asociado a la Imagen como poseedor de ella.
     * @param [in] nombre Es una cadena de caraceteres que representa el nombre de la imagen
     * @param [in] tam Es un entero positivo asociado al tamaño que ocupa la imagen
     * @param [in] likes Es un entero positivo asociado a los likes que tiene una imagen
     * @param [in] fecha Es la Fecha asociada a la imagen
     * @param [in] etiquetas Son los objetos Etiquetas contenidos en un deque
     * @param [in] pos Es el objeto UTM correspondiente a la posición geografica donde fue tomada la Imagen
     */
    Imagen(const string &id, const string &nombre, unsigned int tam, unsigned int likes, const Fecha &fecha, const UTM &pos, const deque<Etiqueta *> &etiquetas);

    /**
     * @brief Contrusctor copia de Imagen
     * @param [in] orig Es el objeto Imagen que va a ser copiado para el nuevo objeto
     */
    Imagen(const Imagen &orig);

    /** Asignación de la clase Imagen con otra
     * @brief Operador de asignación de la clase Imagen
     * @param [in] orig Es la Imagen desde la cual se van a asignar los datos a otra Imagen.
     * @return Referencia sobre la instancia de la Imagen para poder seguir realizando asignaciones.
     */
    Imagen &operator=(const Imagen &orig);

    /**
     * Operador comparativo de imágenes. La comparativa se realiza según el atributo id.
     * @brief Comparador de imágenes a través del id.
     * @param [in] orig es la otra Imagen con quien se va a comparar.
     * @return true o false, según que id es mayor.
     */
    bool operator<(const Imagen &orig) const;

    /**
     * Operador de comparación entre Imagen. Compara todos los atributos.
     * @brief Operador de comparación entre Imagen.
     * @param [in] orig es la otra Imagen con quien se va a realizar la comparación.
     * @return true si todos los atributos son iguales. false en cualquier otro caso.
     */
    bool operator==(const Imagen &orig) const;

    /**
     * Operador de comparación entre Imagen. Compara todos los atributos.
     * @brief Operador de comparación entre Imagen.
     * @param [in] orig Es la otra Imagen con quien se va a realizar la comparación.
     * @return true si todos los atributos son iguales. false en cualquier otro caso.
     */
    bool operator!=(const Imagen &orig) const;

    /**
     * Método para devolver una cadena de caracteres de la información de la imagen.
     * @brief Método para devolver un string de los parámetros de la imagenes.
     * @param [in] modo Booleano que permite mostrar una versión reducida si el valor es false o ampliada si es true
     * @return Cadena de caracteres con cada uno de los atributos de la imagen (id, email, nombre, ...).
     */
    string toString(const bool modo = false);

    /**
     * @brief Método para añadir una Etiqueta a la Imagen
     * @param [in] etqAdd es la Etiqueta a añadir
     */
    void anadirEtiqueta(Etiqueta* &etqAdd);

    /**
     * @brief Método para conseguir todos los objetos Etiqueta de la Imagen
     * @return Vector de STL de tipo string con los nombres de cada Etiqueta asociada
     */
    vector<string> getEtiquetas() const;

    Etiqueta* getEtiqueta(const string &etqBuscar) const;

    ///@brief Función para aumentar en 1 los likes de la Imagen
    void nuevoLike();

    /** Getters de los atributos privados de la clase*/
    const string &getId() const;
    const string &getNombre() const;
    const Fecha &getFecha() const;
    unsigned int getTam() const;
    unsigned int getLikes() const;
    const UTM &getPos() const;
    ///@brief Método para obtener la coordenada X de la Imagen
    const float getX() const;
    ///@brief Método para obtener la coordenada Y de la Imagen
    const float getY() const;

    /** Setters de los atributos privados de la clase*/
    void setId(const string &id);
    void setNombre(const string &nombre);
    void setFecha(const unsigned int dia,const unsigned int mes,const unsigned int anno);
    void setTam(unsigned int tam);
    void setLikes(unsigned int likes);
    void setPos(const UTM &pos);

    virtual ~Imagen();

};

#endif //IMAGENES_IMAGEN_H