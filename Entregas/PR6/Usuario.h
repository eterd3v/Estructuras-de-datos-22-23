/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 05/12/2022
 */

#ifndef PR2_USUARIO_H
#define PR2_USUARIO_H

#include "Imagen.h"
#include "ImageBook.h"
#include "Rango.h"
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class ImageBook; //Para resolver dependencia circular con Usuario

/**
 * @brief Clase que modela a un Usuario
 */
class Usuario {
private:
    ///Identificador del Usuario
    string email;
    ///Popularidad del usuario, según sus likes
    unsigned int popularidad;
    ///Asociación linkIB
    ImageBook* ib;
    ///Imágenes que pertenecen a un Usuario
    std::map<std::string, Imagen*> userImages;
    ///Cantidad de imagenes del usuario
    unsigned numImages;
    ///@brief Método privado para comprobar si tiene un ImageBook asociado. De no tener salta una excepción.
    void ibAsociado(); //Decidí ponerlo como privado para que el usuario no pueda provocar una excepción de forma intencionada
public:

    ///@brief Constructor por defecto de Usuario
    Usuario();

    /**
     * @brief Constructor parametrizado de Usuario
     * @param [in] email Es el correo con el que se va a crear el nuevo Usuario
     */
    Usuario(const string &email);

    /**
     * @brief Constructor copia de Usuario
     * @param [in] orig Es el objeto origen del que se va a copiar los datos para el nuevo Usuario
     */
    explicit Usuario(const Usuario &orig);

    /**
     * @brief Operador relacional menor de Usuario
     * @param [in] orig Es el Usuario de origen que va usarse en la comparación
     * @return true si es menor. En cualquier otro caso false.
     */
    bool operator<(const Usuario &orig);

    /**
     * @brief Operador relacional mayor de Usuario
     * @param [in] orig Es el Usuario de origen que va usarse en la comparación
     * @return true si es mayor. En cualquier otro caso false.
     */
    bool operator>(const Usuario &orig);

    /**
     * @brief Operador relacional menor o igual de Usuario
     * @param [in] orig Es el Usuario de origen que va usarse en la comparación
     * @return true si es menor o igual. En cualquier otro caso false.
     */
    bool operator<=(const Usuario &orig);

    /**
     * @brief Operador relacional mayor o igual de Usuario
     * @param [in] orig Es el Usuario de origen que va usarse en la comparación
     * @return true si es mayor o igual. En cualquier otro caso false.
     */
    bool operator>=(const Usuario &orig);

    /**
     * @brief Operador relacional de igualdad de Usuario
     * @param [in] orig Es el Usuario de origen que va usarse en la comparación
     * @return true si orig tiene el mismo mail. false en cualquier otro caso.
     */
    bool operator==(const Usuario &orig);

    /**
     * @brief Operador relacional menor de Usuario
     * @param [in] orig Es el Usuario de origen que va usarse en la comparación
     * @return true si es menor. En cualquier otro caso false.
     */
    bool operator!=(const Usuario &orig);

    /**
     * @brief Método para asociar una Imagen ya existente al Usuario
     * @param [in] img Es el puntero a un objeto Imagen que contiene a este Usuario
     */
    void insertarImagen(Imagen &img);

    /**
     * @brief Método para añadir a una Imagen preexistente en Usuario, una Etiqueta
     * @param [in] id Es el identificador de la Imagen asociada
     * @param [in] nombreEti Es la Etiqueta asociada a incluir en la imagen
     */
    void anadirEtiquetaImagen(const string &id, const string &nombreEti);

    /**
     * @brief Método para conseguir una Imagen del Usuario, dada una Etiqueta
     * @param [in] id Es el id asociado la Etiqueta
     * @return Puntero a la Imagen con el id de la Etiqueta.
     */
    Imagen* buscarImagen(const string &id);

    /**
     * @brief Método para encontrar todos los objeto de Imagen de un Usuario que tenga una misma Etiqueta
     * @param [in] nombreEtiq Es el string con el nombre de la Etiqueta que se desea buscar en las Imágenes del Usuario
     * @return Vector dinámico de punteros a las Imágenes con la Etiqueta etiq que tenga asociadas actualmente el Usuario
     */
    vector<Imagen*> buscarEtiq(const string &nombreEtiq);

    /**
     * @brief Método para buscar los usuarios a través de una etiqueta específica
     * @param [in] nombreEti Es el string asociado a la etiqueta a buscar
     * @return Vector de punteros de Usuarios asociados a la etiqueta
     */
    vector<Usuario*> buscarUsuariosEtiq(const string &nombreEti);

    /**
     * @brief Método para conseguir las imágenes de un usuario en una fecha específica
     * @param [in] fecha Es la Fecha en la que se tomaron las imágenes
     * @return Vector de punteros de imagenes que se tomaron en la Fecha fecha
     */
    vector<Imagen*> getImagenFecha(const Fecha &fecha);

    /**
     * @brief Método para conseguir la Imagen más antigua del Usuario
     * @return Puntero a la Imagen más antigua del Usuario
     */
    Imagen* getImagenMasAntigua();

    /**
     * @brief Método para conseguir la Imagen más reciente del Usuario
     * @return Puntero de la Imagen más reciente del Usuario
     */
    Imagen* getImagenMasReciente();

    /**
     * @brief Método para conseguir todas las imágenes con la etiqueta dada de todos los usuarios del sistema
     * @param [in] nombreEti es el nombre de la etiqueta a buscar en el sistema
     * @return Vector de punteros de Imagen que corresponde a la descripción de este método
     */
    vector<Imagen*> getImagenesEtiqueta (const string &nombreEti);

    /**
     * @brief Función para conseguir las imágenes del Usuario tomadas en una zona específica
     * @param [in] rango Es el Rango o zona de búsqueda de las imágenes tomadas
     * @return Vector de punteros a Imagen que coinciden con la búsqueda. Puede ser un vector vacío.
     */
    vector<Imagen*> imagenEnZona(const Rango &rango) const;

    /**
     * @brief Función para dar like a todas las Imágenes que estén dentro de un Rango específico
     * @param [in] rango Es el Rango donde se pretende dar like a todas las Imagenes que alberga
     */
    void likeAutomaticoZona(const Rango &rango);

    /**
     * @brief Método para dar un 'Me gusta' a una Imagen. Provoca excepción si la Imagen contiene a al mismo usuario que llama a la función
     * @param [in] img Es un puntero a la Imagen a la que dar 'Me gusta'
     */
    void meGustaImagen (Imagen* &img);

    /**
     * @brief Método para dar un like automáticamente a toda Imagen con una Etiqueta dada
     * @param [in] nombreEtiq Es el nombre de la etiqueta a realizar el like automático
     */
    void likeAutomatico (const string &nombreEtiq);

    ///@brief Método para actualizar la popularidad del Usuario
    void actualizarPopularidad();

    /** Setters de atributos de la clase */
    void setIb(ImageBook *ib);
    void setEmail(const string &email);
    void setPopularidad(unsigned int popularidad);

    /** Getters de atributos de la clase */
    /**
     * @brief Getter del atributo email de Usuario
     * @return Cadena de caracteres con el email.
     */
    const string &getEmail() const;

    /**
     * @brief Getter del atributo popularidad de Usuario
     * @return Entero positivo asociado a la populariodad del Usuario.
     */
    unsigned int getPopularidad() const;

    /**
     * @brief Función para conseguir el número de Imágenes asociadas al Usuario
     * @return Entero sin signo que corresponde a la cantidad de Imágenes de dicho Usuario
     */
    unsigned int getNumImages() const;

    /**
     * @brief Función que muestra por consola la información de un Usuario
     * @param [in] modo Booleano que, si es false (por defecto), muestra una versión reducida. Si true incluye la información de cada Imagen y Etiqueta asociados
     */
    void mostrar(const bool modo = false);

    ///@brief Destructor de la clase Usuario
    virtual ~Usuario();
};

#include "ImageBook.h"


#endif //PR2_USUARIO_H
