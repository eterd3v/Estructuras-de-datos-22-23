/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 26/09/2022
 */
#ifndef IMAGENES_IMAGEN_H
#define IMAGENES_IMAGEN_H

#include <string>
#include "fecha.h"
#include "Etiqueta.h"
#include "Usuario.h"

class Usuario; //Para resolver dependencia circular con Imagen

using namespace std;

/**
 * @brief Clase que simula un archivo de imagen.
 */
class Imagen {
private:
    string id;
    string nombre;
    Usuario* usr;
    Etiqueta* etiqueta;
    Fecha fecha;
    unsigned int tam;
public:

    /** Construye un objeto Imagen con atributos por defecto (id=0,email=No_email,nombre=Sin_nombre,etiquetas=Sin_etiquetas,tam=0,fecha=1/1/1980 )
     *  @brief Constructor por defecto de la clase Imagen
     */
    Imagen();

    /** Constructor de la clase Imagen que utilizará como atributos los datos de los parámetros
     * @brief Constructor parametrizado de la clase Imagen
     * @param [in] id Es una cadena de caraceteres que representa el identificador de la imagen
     * @param [in] usr Es un puntero a un Usuario que está asociado a la Imagen como poseedor de ella.
     * @param [in] nombre Es una cadena de caraceteres que representa el nombre de la imagen
     * @param [in] tam Es un entero positivo asociado al tamaño que ocupa la imagen
     * @param [in] fecha Es la Fecha asociada a la imagen
     * @param [in] etiquetada Es un objeto Etiqueta asociada a la imagen
     */
    Imagen(const string &id, Usuario* &usr, const string &nombre, unsigned int tam, const Fecha &fecha, Etiqueta* &etiquetada);

    /** Asignación de la clase Imagen con otra
     * @brief Operador de asignación de la clase Imagen
     * @param [in] orig es la Imagen desde la cual se van a asignar los datos a otra Imagen.
     * @return referencia sobre la instancia de la Imagen para poder seguir realizando asignaciones.
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
     * @param [in] orig es la otra Imagen con quien se va a realizar la comparación.
     * @return true si todos los atributos son iguales. false en cualquier otro caso.
     */
    bool operator!=(const Imagen &orig) const;

    /**
     * Método para devolver una cadena de caracteres de la información de la imagen.
     * @brief Método para devolver un string de los parámetros de la imagenes.
     * @return Cadena de caracteres con cada uno de los atributos de la imagen (id, email, nombre, ...).
     */
    string to_string();

    /* Getters de los atributos privados de la clase*/
    const string &getId() const;

    const string &getNombre() const;

    Usuario *getUsr() const;

    string getEtiqueta() const;

    const Fecha &getFecha() const;

    unsigned int getTam() const;

    /* Setters de los atributos privados de la clase*/
    void setId(const string &id);

    void setUsr(Usuario *usr);

    void setNombre(const string &nombre);

    void setEtiqueta(Etiqueta* &etiquetada);

    void setFecha(const unsigned int dia,const unsigned int mes,const unsigned int anno);

    void setTam(unsigned int tam);

    virtual ~Imagen();

};

#endif //IMAGENES_IMAGEN_H