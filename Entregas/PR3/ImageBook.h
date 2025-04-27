/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 8/11/2022
 */

#ifndef PR2_IMAGEBOOK_H
#define PR2_IMAGEBOOK_H

#include "Imagen.h"
#include "VDinamico.h"
#include "ListaDEnlazada.h"
#include "Etiqueta.h"
#include "AVL.h"
#include "Usuario.h"

using namespace std;

/**
 * @brief Clase que gestiona los objetos Imagen, Etiqueta y Usuario
 */
class ImageBook {
private:
    ///@brief Es la estructura de datos donde se guardan los objetos Imagen
    VDinamico<Imagen> images;
    ///@brief Es la estructura de datos donde se guardan los objetos Etiqueta
    ListaDEnlazada<Etiqueta> labels;
    ///@brief Es la estructura de datos donde se guardan los objetos Usuario
    AVL<Usuario> users;

    /**
     * @brief Función para cargar desde ficheros Imagenes o Etiquetas en los atributos de ImageBook
     * @param [in] tipo es el tipo de fichero a introducir. 0 si el fichero es de Etiqueta, 1 si es de Usuario y 2 si el fichero es de Imagen.
     * @param [in] fichero es una cadena de caracteres que indica la dirección del fichero a cargar.
     */
    void cargarFicheros(const char &tipo, const std::string &fichero);

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
     * @brief Método para cargar los ficheros en el objeto ImageBook. Si hay algún dato cargado (de cualquier tipo) se borra.
     * @param [in] fileImages Es un string que indica la dirección del fichero de las Imagenes a cargar.
     * @param [in] fileLabels Es un string que indica la dirección del fichero de las Etiquetas a cargar.
     * @param [in] fileUsers Es un string que indica la dirección del fichero de los Usuarios a cargar.
     */
    void cargarFicheros(const string &fileImages, const string &fileLabels, const std::string &fileUsers);

    /**
     * @brief Constructor parametrizado de ImageBook
     * @param [in] fileImages Es un string que indica la dirección del fichero de las Imagenes a cargar.
     * @param [in] fileLabels Es un string que indica la dirección del fichero de las Etiquetas a cargar.
     * @param [in] fileUsers Es un string que indica la dirección del fichero de los Usuarios a cargar.
     */
    ImageBook(const string &fileImages, const string &fileLabels, const string &fileUsers);

    /**
     * @brief Función para buscar un usuario cargado en la clase Imagebook
     * @param [in] email Es el correo asociado al Usuario a buscar
     * @return Si el Usuario con email se encuentra devuelve un puntero de este. En cualquier otro caso devuelve nullptr.
     */
    Usuario* buscarUsuario(const string &email);

    /**
     * @brief Método para conseguir Usuarios que contengan al menos una etiqueta específica en sus Imágenes
     * @param [in] etiqueta es el nombre de la etiqueta a buscar en las Imágenes de los Usuarios
     * @return Vector dinámico de punteros a Usuario que tienen asociado en sus Imagenes al menos 1 ocurrencia de etiqueta.
     */
    VDinamico<Usuario *> buscarUsuarioEtiq(const string &etiqueta);

    /**
     * @brief Conseguir el/los Usuario/s más activos del sistema (con más Imágenes)
     * @return Vector dinámico de punteros de los Usuarios que almecan más Imágenes que el resto.
     */
    VDinamico<Usuario*> getMasActivos();

    /**
     * @brief Muestra por consola cuantas Imágenes y Etiquetas se han cargado en memoria.
     */
    void mostrarEstado();

    virtual ~ImageBook();
};


#endif //PR2_IMAGEBOOK_H
