/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 8/11/2022
 */

#ifndef PR2_USUARIO_H
#define PR2_USUARIO_H

#include "Imagen.h"
#include "ImageBook.h"
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
    ///Asociación linkIB
    ImageBook* ib;
    ///Imágenes que pertenecen a un Usuario
    std::map<std::string, Imagen*> userImages;
    ///Cantidad de imagenes del usuario
    unsigned numImages;
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
     * @brief Getter del atributo email de Usuario
     * @return Cadena de caracteres con el email.
     */
    const string &getEmail() const;

    /**
     * @brief Función para conseguir el número de Imágenes asociadas al Usuario
     * @return Entero sin signo que corresponde a la cantidad de Imágenes de dicho Usuario
     */
    unsigned int getNumImages() const;

    /**
     * @brief Método para asociar una Imagen ya existente al Usuario
     * @param [in] img Es el puntero a un objeto Imagen que pertenece a este Usuario
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
    std::vector<Imagen*> buscarEtiq(const string &nombreEtiq);

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
     * @return Puntero de la Imagen más antigua del Usuario
     */
    Imagen* getImagenMasAntigua();

    /**
     * @brief Método para conseguir la Imagen más antigua del Usuario
     * @return Puntero de la Imagen más reciente del Usuario
     */
    Imagen* getImagenMasReciente();

    void setIb(ImageBook *ib);

    ///@brief Función que muestra por consola toda la información relativa a un Usuario
    void mostrar();

    ///@brief Destructor de la clase Usuario
    virtual ~Usuario();
};

#include "ImageBook.h"


#endif //PR2_USUARIO_H
