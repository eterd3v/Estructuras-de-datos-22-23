/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 05/12/2022
 */

#ifndef PR2_IMAGEBOOK_H
#define PR2_IMAGEBOOK_H

#include "Imagen.h"
#include "Etiqueta.h"
#include "Usuario.h"
#include "THashImagen.h"
#include <vector>
#include <list>
#include <map>

using namespace std;

class Usuario;

///@brief Clase que gestiona los objetos Imagen, Etiqueta y Usuario
class ImageBook {
private:
    ///@brief Es la estructura de datos donde se guardan los objetos Imagen
    THashImagen *images;
    ///@brief Es la estructura de datos donde se guardan los objetos Etiqueta
    std::list<Etiqueta> labels;
    ///@brief Es la estructura de datos donde se guardan los objetos Usuario
    std::map<string,Usuario> users;

    /**
     * @brief Función para cargar desde un fichero .csv todas las Imagenes, Etiquetas y Usuarios en el ImageBook
     * @param [in] tipo es el tipo de fichero a introducir. 0 si el fichero es de Etiqueta, 1 si es de Usuario y 2 si el fichero es de Imagen.
     * @param [in] fichero es una cadena de caracteres que indica la dirección del fichero a cargar.
     */
    void cargarFichero(const char &tipo, const std::string &fichero);

public:

    /**
     * @brief Método que busca una Etiqueta guardada en ImageBook
     * @param [in] etq es el nombre de la etiqueta que se desea encontrar
     * @return Devuelve la dirección de memoria en la que está la Etiqueta a buscar
     */
    Etiqueta* buscarMiEtiqueta(const string &etq);

    ///@brief Constructor por defecto de la clase ImageBook
    ImageBook();

    /**
     * @brief Método para cargar los ficheros en el objeto ImageBook. Si hay algún dato cargado (de cualquier tipo) se borra.
     * @param [in] fileImages Es un string que indica la dirección del fichero de las Imagenes a cargar.
     * @param [in] fileLabels Es un string que indica la dirección del fichero de las Etiquetas a cargar.
     * @param [in] fileUsers Es un string que indica la dirección del fichero de los Usuarios a cargar.
     */
    void cargar(const string &fileImages, const string &fileLabels, const std::string &fileUsers);

    /**
     * @brief Constructor parametrizado de ImageBook
     * @param [in] fileImages Es un string que indica la dirección del fichero de las Imagenes a cargar.
     * @param [in] fileLabels Es un string que indica la dirección del fichero de las Etiquetas a cargar.
     * @param [in] fileUsers Es un string que indica la dirección del fichero de los Usuarios a cargar.
     * @param [in] lambda Es un número flotante que indica el factor de carga con el que se van a guardar Imagenes.
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
    vector<Usuario*> buscarUsuarioEtiq(const string &etiqueta);

    /**
     * @brief Método para obtener los objeto Usuario que tomaron una Imagen en la Fecha f
     * @param [in] f Es la Fecha en la que se tomaron los objetos Imagen
     * @return Vector de punteros de Usuario que corresponden a aquellos que tomaron una Imagen en la Fecha f
     */
    vector<Usuario*> buscarUsuarioFechaImagen(const Fecha &f);

    /**
     * @brief Conseguir el/los Usuario/s más activos del sistema (con más Imágenes)
     * @return Vector dinámico de punteros de los Usuarios que almecan más Imágenes que el resto.
     */
    vector<Usuario*> getMasActivos();

    /**
     * @brief Función para conseguir los 5 objetos Etiqueta con más likes
     * @return Cola doble de punteros de los objetos Etiqueta con más likes.
     */
    list<Etiqueta *> getMasLikes();

    list<Usuario*> getMasPopulares();

    list<Imagen*> buscarImagEtiq (const string &nombreEti); ///TODO: nuevo

    Etiqueta* buscarEtiqueta (const string &nombreEti); ///TODO: nuevo

    bool insertarImagen(const string &id, Imagen* &img);

    Imagen* buscarImagen(const string &id);

    bool borrarImagen(const string &id);

    ///@brief Muestra por consola cuantas Imágenes, Etiquetas y Usuarios se han cargado en memoria.
    void mostrarEstado();

    ///@brief Muestra por consola la información relativa a las imagenes de THashImagen.
    void consultarImagenes();

    virtual ~ImageBook();
};


#endif //PR2_IMAGEBOOK_H
