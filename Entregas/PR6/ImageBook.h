/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 05/12/2022
 */

#ifndef PR2_IMAGEBOOK_H
#define PR2_IMAGEBOOK_H

#include "Imagen.h"
#include "Etiqueta.h"
#include "Usuario.h"
#include "MallaRegular.h"
#include "img.h"
#include <vector>
#include <queue>
#include <list>
#include <map>

using namespace std;

class Usuario;

///@brief Clase que gestiona los objetos Imagen, Etiqueta y Usuario
class ImageBook {
private:
    ///@brief Es la estructura de datos donde se guardan los objetos Imagen
    map<string,Imagen> images;
    ///@brief Malla regular que contiene la posición de cada Imagen
    MallaRegular<Imagen*> *imagePos;
    ///@brief Es la estructura de datos donde se guardan los objetos Etiqueta
    list<Etiqueta> labels;
    ///@brief Es la estructura de datos donde se guardan los objetos Usuario
    map<string,Usuario> users;

    /**
     * @brief Función para cargar desde un fichero .csv todas las Imagenes, Etiquetas y Usuarios en el ImageBook
     * @param [in] tipo es el tipo de fichero a introducir. 0 si el fichero es de Etiqueta, 1 si es de Usuario y 2 si el fichero es de Imagen.
     * @param [in] fichero es una cadena de caracteres que indica la dirección del fichero a cargar.
     */
    void cargarFichero(const char &tipo, const std::string &fichero);

public:

    ///@brief Constructor por defecto de la clase ImageBook
    ImageBook();

    /**
     * @brief Método para cargar los ficheros en el objeto ImageBook. Si hay algún dato cargado (de cualquier tipo) se borra.
     * @param [in] fileImages Es un string que indica la dirección del fichero de las Imagenes a cargar.
     * @param [in] fileLabels Es un string que indica la dirección del fichero de las Etiquetas a cargar.
     * @param [in] fileUsers Es un string que indica la dirección del fichero de los Usuarios a cargar.
     */
    void cargar(const string &fileImages, const string &fileLabels, const string &fileUsers);

    /**
     * @brief Constructor parametrizado de ImageBook
     * @param [in] fileImages Es un string que indica la dirección del fichero de las Imagenes a cargar.
     * @param [in] fileLabels Es un string que indica la dirección del fichero de las Etiquetas a cargar.
     * @param [in] fileUsers Es un string que indica la dirección del fichero de los Usuarios a cargar.
     * @param [in] lambda Es un número flotante que indica el factor de carga con el que se van a guardar Imagenes.
     */
    ImageBook(const string &fileImages, const string &fileLabels, const string &fileUsers);

    /**
     * @brief Método que busca una Etiqueta guardada en ImageBook
     * @param [in] etq es el nombre de la etiqueta que se desea encontrar
     * @return Devuelve la dirección de memoria en la que está la Etiqueta a buscar
     */
    Etiqueta* buscarMiEtiqueta(const string &etq);

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
     * @param [in] cant Entero positivo que indica la cantidad de Etiquetas con más likes a recopilar
     * @return Cola doblemente enlazada de punteros de Etiqueta con más likes.
     */
    list<Etiqueta*> getMasLikes(unsigned int cant = 5);

    /**
     * @brief Método para conseguir aquellos Usuarios más populares según sus likes en el sistema
     * @param [in] cant Entero positivo que indica la cantidad de Usuario a contabilizar
     * @return Lista de punteros de Usuario más populares de la aplicación
     */
    list<Usuario*> getMasPopulares(const unsigned int cant = 3);

    /**
     * @brief Método para buscar todas las Imagenes que comparten una misma Etiqueta
     * @param [in] nombreEti Es la cadena de caracteres que refleja la Etiqueta de filtro de las Imagenes
     * @return Lista de punteros de Imagen que comparten la etiqueta nombreEti
     */
    list<Imagen*> buscarImagEtiq (const string &nombreEti);

    /**
     * @brief Método para buscar una Etiqueta específica en la aplicación
     * @param [in] nombreEti Es el nombre de la Etiqueta como cadena de caracteres a buscar
     * @return Puntero a la Etiqueta correspondiente si la halla. De lo contrario devuelve nullptr
     */
    Etiqueta* buscarEtiqueta (const string &nombreEti);

    /**
     * @brief Método para buscar Imagenes dado un Rango de coordenadas
     * @param [in] r Es el Rango de coordenadas a buscar en el sistema
     * @return Vector de punteros de Imagen que coinciden con la búsqueda del Rango r.
     */
    vector<Imagen*> buscarImagLugar(const Rango &r);

    /**
     * @brief Método para buscar Imagenes que comparten una Etiqueta en un Rango de coordenadas concreto
     * @param [in] nombre Es el nombre de la Etiqueta a hallar dentro del Rango r
     * @param [in] r Es el Rango de coordenadas donde se va a buscar en la aplicación
     * @return Vector de punteros de Imagen que coinciden con la búsqueda del Rango r.
     */
    vector<Imagen*> buscarImagEtiLugar(const string &nombre,const Rango &r);

    /**
     * @brief Método para buscar Usuarios que han tomado al menos una foto en un Rango de coordenadas
     * @param [in] r Es el Rango de coordenadas donde se van a buscar los Usuarios
     * @return Vector de punteros de Usuario que tomaron al menos una foto dentro del Rango r.
     */
    vector<Usuario*> buscarUsuarLugar(const Rango &r);

    /**
     * @brief Función para buscar la Etiqueta más repetida dentro de un Rango especificado
     * @param [in] r Es el Rango de coordenadas donde buscar la Etiqueta
     * @return Puntero a la Etiqueta más repetida dentro del Rango r. Si no llega a encontrar nada devuelve nullptr
     */
    Etiqueta* buscaEtiquetaRepetida(const Rango &r);

    /**
     * @brief Método para insertar una Imagen no existente en la aplicación
     * @param [in] id Es el identificador único de la Imagen
     * @param [in] img Es la Imagen no existente a añadir
     * @return True si la inserción fue exitosa o false si no lo fue
     */
    bool insertarImagen(const string &id, Imagen &img);

    /**
     * @brief Función para buscar una Imagen en la aplicación
     * @param [in] id Es el identificador único de la Imagen como cadena de caracteres
     * @return Puntero a la Imagen encontrada por su id. Si no llega a encontrar nada devuelve nullptr
     */
    Imagen* buscarImagen(const string &id);

    /**
     * @brief Método para borrar una Imagen ya existente en la aplicación
     * @param [in] id Es el identificador único de la Imagen
     * @return True si el borrado fue un éxito. De lo contrario devuelve false si no pudo borrarse
     */
    bool borrarImagen(const string &id);

    ///@brief Muestra por consola cuantas Imágenes, Etiquetas y Usuarios se han cargado en memoria.
    void mostrarEstado();

    ///@brief Destructor por defecto de ImageBook
    virtual ~ImageBook();
};


#endif //PR2_IMAGEBOOK_H
