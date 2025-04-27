/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 26/09/2022
 */

#ifndef PR2_IMAGEBOOK_H
#define PR2_IMAGEBOOK_H

#include "Imagen.h"
#include "VDinamico.h"
#include "ListaDEnlazada.h"
#include "Etiqueta.h"

using namespace std;

/**
 * @brief Clase que gestiona los objetos Imagen y Etiqueta
 */
class ImageBook {
private:
    VDinamico<Imagen> images;
    ListaDEnlazada<Etiqueta> labels;

    /**
     * @brief Función para cargar desde ficheros Imagenes o Etiquetas en los atributos de ImageBook
     * @param [in] tipo es el tipo de fichero a introducir. true si el fichero es de Etiqueta y false si el fichero es de Imagen.
     * @param [in] fichero es una cadena de caracteres que indica la dirección del fichero a cargar.
     */
    void cargarFicheros(const bool &tipo, const std::string &fichero); //True = label, false = Imagen

    /**
     * @brief Método que busca una Etiqueta guardada en ImageBook
     * @param [in] etq es el nombre de la etiqueta que se desea encontrar
     * @return Devuelve la dirección de memoria en la que está la Etiqueta a buscar
     */
    Etiqueta* buscarMiEtiqueta(const string &etq);

public:

    /**
     * @brief Constructor por defecto de la clase ImageBook
     */
    ImageBook();

    /**
     * @brief Constructor parametrizado de ImageBook
     * @param [in] fileImages es un string que indica la dirección del fichero de las Imagenes a cargar.
     * @param [in] fileLabels es un string que indica la dirección del fichero de las Etiquetas a cargar.
     */
    ImageBook(const string &fileImages, const string &fileLabels);

    /**
     * @brief Método para cargar los ficheros en las clase ImageBook. Si hay algún dato cargado (de cualquier tipo) se borra
     * @param [in] fileImages es un string que indica la dirección del fichero de las Imagenes a cargar.
     * @param [in] fileLabels es un string que indica la dirección del fichero de las Etiquetas a cargar.
     */
    void cargarFicheros(const string &fileImages, const string &fileLabels);

    /**
     * @brief Método para conseguir todas las Imágenes con la misma etiqueta
     * @param [in] etiqueta es el nombre de la etiqueta a buscar en las imágnes
     * @return Lista doblemente enlazada de Imagenes, todas con la misma etiqueta
     */
    ListaDEnlazada<Imagen> buscarImgEtq(const string etiqueta);

    /**
     * @brief Función que encuentra la Etiqueta más repetida en las imágenes cargadas de ImageBook
     * @return El nombre de la etiqueta más repetida
     */
    string etiqMasRepetida();

    /**
     * @brief Muestra por consola cuantas Imágenes y Etiquetas se han cargado en memoria.
     */
    void mostrarEstado();

    virtual ~ImageBook();
};


#endif //PR2_IMAGEBOOK_H
