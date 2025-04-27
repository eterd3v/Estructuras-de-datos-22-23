/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 8/11/2022
 */

#ifndef PR2_USUARIO_H
#define PR2_USUARIO_H

#include <string>
#include "Imagen.h"
#include "VDinamico.h"

using namespace std;

class Imagen; //Para resolver dependencia circular con Usuario

/**
 * @brief Clase que modela a un Usuario
 */
class Usuario {
private:
    ///Identificador del Usuario
    string email;
    ///Imágenes que pertenecen a un Usuario
    VDinamico<Imagen*> userImages;
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
    unsigned int getNumImages();

    /**
     * @brief Método para asociar una Imagen ya existente al Usuario
     * @param [in] img Es el puntero a un objeto Imagen que pertenece a este Usuario
     */
    void insertarImagen(Imagen* &img);

    /**
     * @brief Método para encontrar todos los objeto de Imagen de un Usuario que tenga una misma Etiqueta
     * @param [in] etiq Es el string con el nombre de la Etiqueta que se desea buscar en las Imágenes del Usuario
     * @return Vector dinámico de punteros a las Imágenes con la Etiqueta etiq que tenga asociadas actualmente el Usuario
     */
    VDinamico<Imagen*> buscarEtiq(const string &etiq);

    ///@brief Función que muestra por consola toda la información relativa a un Usuario
    void mostrarUsr();

    ///@brief Destructor de la clase Usuario
    virtual ~Usuario();
};


#endif //PR2_USUARIO_H
