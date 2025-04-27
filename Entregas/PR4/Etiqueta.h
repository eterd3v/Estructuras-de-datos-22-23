/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 26/09/2022
 */

#ifndef PR2_ETIQUETA_H
#define PR2_ETIQUETA_H

#include <string>

using namespace std;

/**
 * @brief Clase que sirve como etiqueta de una Imagen
 */
class Etiqueta {
private:
    string nombre;
public:

    /**
     * @brief Constructor por defecto de etiqueta
     */
    Etiqueta();

    /**
     * Constructor parametrizado de etiqueta
     * @param [in] nombre es el nombre de la etiqueta
     */
    Etiqueta(const string &nombre);

    /**
     * @brief Operador relacional de igualdad
     * @param [in] rhs es el objeto Etiqueta con el que se va comparar con this
     * @return true si los atributos de los objetos son iguales. false en cualquier otro caso
     */
    bool operator==(const Etiqueta &rhs) const;

    /**
     * @brief Operador relacional de distinción
     * @param [in] rhs es el objeto Etiqueta con el que se va comparar con this
     * @return true si los atributos de los objetos son distintos. false en cualquier otro caso
     */
    bool operator!=(const Etiqueta &rhs) const;

    /** Getter y setter del atributo nombre*/
    const string &getNombre() const;
    void setNombre(const string &nombre);

    virtual ~Etiqueta();
};


#endif //PR2_ETIQUETA_H
