/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 20/09/2022
 */
#ifndef IMAGENES_CONTENEDORIMAGENES_H
#define IMAGENES_CONTENEDORIMAGENES_H

#include "Imagen.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

//Tamaño predefinido del array unidimensional como la variable TAM_PREDEF
constexpr unsigned int TAM_PREDEF = 100;

/**
 * @brief Clase que va a servir de contenedor de la clase Imagen
 */
class ContenedorImagenes {
private:

    Imagen* contendorImgs;

    //Tamaño actual del contenedor de imágenes
    unsigned int tamContenedor;

    //Tamaño máximo del contenedor de imágenes, establecido en el constructor
    unsigned int tamMax;
public:

    /**
     * Constructor por defecto de la clase ContenedorImagenes
     */
    ContenedorImagenes();

    /**
     * Constructor de ContenedorImagenes.
     * @param tamMax es un entero positivo que va a determinar el tamaño del contenedor de imágenes. Si no se le asigna un tamaño, se le aplicará uno por defecto (TAM_PREDEF)
     */
    ContenedorImagenes(unsigned int tamMax);

    /**
     * Constructor copia de la clase ContenedorImagenes
     * @param orig es la instancia de ContenedorImagenes de la cual se van a copiar todos los datos
     */
    ContenedorImagenes(const ContenedorImagenes &orig);

    /**
     * Constructor copia parcial de la clase ContenedorImagenes
     * @param orig es la instancia de un ContenedorImagenes de la cual se van a copiar la información
     * @param posicionInicial es la posición donde se va a empezar a copiar
     * @param numElementos es la cantidad de Imágenes que se van a copiar desde orig
     */
    ContenedorImagenes(const ContenedorImagenes& orig, unsigned int posicionInicial, unsigned int numElementos);

    /**
     * Método para asignar una Imagen a una posición del contenedor.
     * @param dato es la Imagen que va a ser asignada.
     * @param pos es la número entero positivo que indicará la posición donde se va a asignar al contenedor. Lanza una excepción si la posición rebasa al contenedor.
     */
    void asigna(const Imagen &dato, unsigned int pos);

    /**
     * Recupera una imagen del contenedor a través de la posición.
     * @param pos es la posición de la imagen a extraer. Si excede los límites ocurre una excepción
     * @return Imagen del contenedor que se encuentra en la posición pos
     */
    Imagen recupera(unsigned int pos);

    /**
     * A través de una Imagen, sacar la posición de este en el contenedor.
     * @param img es la Imagen que se quiere buscar en el contenedor. Si la Imagen no se encuentra en el contenedor genera una excepción.
     * @return Número entero positivo que indica la posición de la imagen en el contenedor.
     */
    unsigned int busca(const Imagen &img);

    /**
     * Conseguir imágenes del contenedor actual aplicando filtros en un nuevo contenedor.
     * @param email es el correo electrónico asociado a la imagen.
     * @param Fecha_inicial es la fecha anterior a las imágenes a localizar.
     * @param Fecha_final es la fecha posterior a las imágenes a localizar. Es igual o más reciente que Fecha_inicial o provocará una excepción.
     * @param cantidad se refiera al número de imágenes a almacenar. Si es mayor a la capacidad máxima actual, provoca una excepción.
     * @return ContenedorImagenes con tantas Imagen como encuentre.
     */
    ContenedorImagenes localiza(const string email, const Fecha Fecha_inicial, const Fecha Fecha_final, unsigned int cantidad = 20);

    /**
     * Método para ordenar las imágenes del contenedor
     */
    void ordenar();

    /**
     * Método para ordenar las imágenes del contenedor en orden inverso a ordenar()
     */
    void ordenarRev();

    /**
     * Conseguir el tamaño del contenedor actual.
     * @return Número entero positivo que corresponde al tamaño del contenedor actual.
     */
    unsigned int tam();

    virtual ~ContenedorImagenes();

};


#endif //IMAGENES_CONTENEDORIMAGENES_H
