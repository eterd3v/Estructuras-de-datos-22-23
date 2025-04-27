/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 05/12/2022
 */

#ifndef PR5_THASHIMAGEN_H
#define PR5_THASHIMAGEN_H

#include "Imagen.h"

///@brief Diferentes tipos de estado para las posiciones de la tabla.
enum estado{vacio,eliminado,ocupado};

///@brief Struct que va a servir como tipo de elemento para la tabla hash
struct elem{
    estado est = estado::vacio;
    Imagen img;
};

///@brief Clase que implementa una tabla hash específica para datos de tipo Imagen
class THashImagen {
private:

    /// Vector que va a usarse para la tabla hash
    vector<elem> *tabla;
    ///Capacidad de elementos de la tabla. No confundir con la capacidad de la estructura de datos del vector
    unsigned long capacidadTabla;
    ///Cantidad de elementos elem que tiene la tabla con estado ocupado
    unsigned long tamanioTabla;
    ///Registra el maximo de colisiones en la insercción
    unsigned long colisionesMax;
    ///Sumatorio de todas las colisiones producidas en la insercción
    unsigned long colisionesTotal;
    ///Registra el número de veces que las colisiones han sido mayor a 10
    unsigned long colisiones10;

    /**
     * @brief
     * @param [in] clave
     * @param [in] intento
     * @return Entero long sin signo correspodiente al hash generado por la clave e intento.
     */
    unsigned long hash(unsigned long &clave, unsigned long &intento);

    /**
     * @brief
     * @param [in] num
     * @return
     */
    unsigned long primoMasCercano(unsigned long &num);

    /**
     * @brief
     * @param [in] num
     * @return
     */
    bool esPrimo(unsigned long &num);

    ///@brief Método para comprobar si la tabla está instanciada. De lo contrario salta excepción.
    void excpTablaCreada();

public:

    ///@brief Constructor por defecto
    THashImagen();

    /**
     * @brief Constructor parametrizado de la tabla hash
     * @param [in] maxElementos Es un entero sin signo que corresponde a la cantidad de Imagenes a almacenar
     * @param [in] lambda Es número flotante que indica el factor de carga deseado para la tabla hash
     */
    THashImagen(unsigned maxElementos = 10000, float lambda=0.7);

    /**
     * @brief Constructor copia de THashImagen
     * @param [in] thash Es la THashImagen de la que se va a partir para la copia
     */
    THashImagen(THashImagen &thash);

    /**
     * @brief Método para asignar una THashImagen a otra
     * @param [in] thash Es la THashImagen de la que se va a partir para la asignación
     */
    THashImagen& operator=(THashImagen &thash);


    /**
     * @brief Método para insertar una Imagen en la THashImagen
     * @param [in] clave Es un entero sin signo ampliado que corresponde a la clave asociada al objeto Imagen a insertar
     * @param [in] imagen Es el objeto de tipo Imagen dispuesto a ocupar una posicion de la tabla
     * @return Puntero de la Imagen, si la insercción fue un exito. nullptr en cualquier otro caso.
     */
    Imagen* insertar(unsigned long &clave, Imagen &imagen);

    /**
     * @brief Método para borrar una Imagen en la THashImagen
     * @param [in] clave Es un entero sin signo ampliado que corresponde a la clave asociada del objeto Imagen a borrar
     * @param [in] id Es el identificador asociado a la Imagen a borrar
     * @return true si el borrado fue exitoso. false en cualquier otro caso
     */
    bool borrar(unsigned long &clave, const string &id);

    /**
     * @brief Método para buscar una Imagen en la THashImagen
     * @param [in] clave Es un entero sin signo ampliado que corresponde a la clave asociada del objeto Imagen a buscar
     * @param [in] id Es el identificador asociado a la Imagen a buscar
     * @return Puntero de la Imagen, si la busqueda fue un exito. nullptr en cualquier otro caso.
     */
    Imagen* buscar(unsigned long &clave,const string &id);

    /**
     * @brief Función que genera una clave para un objeto Imagen a través de una cadena
     * @param [in] cadena Es la cadena de caracteres de donde partir a generar la clave
     * @return Entero sin signo ampliado
     */
    unsigned long djb2(const string &cadena);

    ///@brief Método para conocer cuantas imagenes están ocupando posiciones en la tabla
    ///@return Entero sin signo que indica la cantidad de imagenes introducidas en la tabla hash
    unsigned numImages();

    ///@brief Método para obtener el máximo de colisiones producidas en las insercciones
    ///@return Entero sin signo con el máximo de colisiones producidas
    unsigned maxColisiones();

    ///@brief Método para recuperar las veces que se han superado las 10 colisiones en las insercciones
    ///@return Entero sin signo con las veces que se han superado 10 colisiones
    unsigned numMax10();

    ///@brief Método para obtener el promedio de colisiones producidas en las insercciones
    ///@return Número long double con el promedio de las colisiones
    long double promedioColisiones();

    ///@brief Método para obtener el factor de carga de la tabla hash
    ///@return Número en representación flotante que indica el factor de carga
    float factorCarga();

    ///@brief Método para obtener el tamaño de la tabla (no la cantidad de sus elementos)
    ///@return Entero sin signo que se corresponde con el tamaño de la tabla
    unsigned tamTabla();

    ///@brief Muestra por consola el estado actual de la tabla hash con varios de sus atributos asociados
    void mostrarEstadoTablaImagenes();

    ~THashImagen();
};


#endif //PR5_THASHIMAGEN_H
