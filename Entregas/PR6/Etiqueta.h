/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 01/12/2022
 */

#ifndef PR2_ETIQUETA_H
#define PR2_ETIQUETA_H

#include <string>
#include <list>
#include "Imagen.h"

using namespace std;

class Imagen;

/**
 * @brief Clase que sirve como etiqueta de una Imagen
 */
class Etiqueta {
private:
    ///Nombre por el que se identifica la Etiqueta
    string nombre;
    ///Lista de todos los objeto Imagen que tienen esta Etiqueta
    list<Imagen*> etiImages;
public:

    /**
     * @brief Constructor por defecto de etiqueta
     */
    Etiqueta();

    /**
     * Constructor parametrizado de etiqueta
     * @param [in] nombre es el nombre de la etiqueta
     */
    Etiqueta(const string &nombre, const list<Imagen*> &etiImagen);

    /**
     * @brief Constructor copia de la clase Etiqueta
     * @param [in] orig Es la Etiqueta de la que se va partir para instanciar el nuevo objeto
     */
    Etiqueta(const Etiqueta &orig);

    /**
     * @brief Operador relacional de igualdad
     * @param [in] rhs Es el objeto Etiqueta con el que se va a comparar con this
     * @return true si los atributos de los objetos son iguales. false en cualquier otro caso
     */
    bool operator==(const Etiqueta &rhs) const;

    /**
     * @brief Operador relacional de distinción
     * @param [in] rhs Es el objeto Etiqueta con el que se va a comparar con this
     * @return true si los atributos de los objetos son distintos. false en cualquier otro caso
     */
    bool operator!=(const Etiqueta &rhs) const;

    unsigned int getTotalLikes();

    void nuevaImagen(Imagen* &img);

    /** Getter y setter del atributo nombre*/
    const string &getNombre() const;
    void setNombre(const string &nombre);
    list<Imagen*> getImages();

    virtual ~Etiqueta();
};


#endif //PR2_ETIQUETA_H
