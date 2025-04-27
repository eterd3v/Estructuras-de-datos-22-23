#include <fstream>
#include <sstream>
#include "Fecha.h"
#include "Iterador.h"

#include "ImageBook.h"

ImageBook::ImageBook():images(),labels() {}

ImageBook::ImageBook(const std::string &fileImages, const std::string &fileLabels):images(),labels() {
    cargarFicheros(true,fileLabels);
    cargarFicheros(false,fileImages);
}

void ImageBook::cargarFicheros(const std::string &fileImages, const std::string &fileLabels) {
    if(images.tamlog() > 0){
        for (int i = 1; i < images.tamlog(); ++i)
            images.borrar();
    }
    if(labels.getTam() > 0){
        for (int i = 0; i < labels.getTam(); ++i)
            labels.borrarFinal();
    }
    cargarFicheros(true,fileLabels);
    cargarFicheros(false,fileImages);
}

void ImageBook::cargarFicheros(const bool &tipo, const std::string &fichero) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    is.open(fichero); //carpeta de proyecto
    if (is.good()) {

        while (getline(is, fila)) {

            if (fila != "") { //¿Se ha leído una nueva fila?

                columnas.str(fila);
                //Dependiendo del tipo de archivo, se tratarán las filas de una forma u otra
                if(tipo){   //Si es true el fichero es una instancia de Etiqueta.
                    string etiqueta = "";
                    getline(columnas,etiqueta,',');
                    columnas.clear();
                    try{
                        Etiqueta et(etiqueta);
                        labels.insertaFin(et);
                    }catch(exception &err){
                        cout << err.what() << endl;
                    }
                }else{      //Si es false es una instancia de Imagen
                    string id = "", email = "", nombre = "", etiqueta = "";
                    int tam = 0, dia = 0, mes = 0, anno = 0;
                    //formato de fila: id;email;nombre;tam;fecha;etiquetas

                    getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                    getline(columnas, email, ';');
                    getline(columnas, nombre, ';');

                    columnas >> tam;   //las secuencia numéricas se leen y trasforman directamente
                    columnas.ignore(); //omitimos carácter ';' siguiente

                    columnas >> dia; columnas.ignore();
                    columnas >> mes; columnas.ignore();
                    columnas >> anno; columnas.ignore();

                    getline(columnas, etiqueta,',');
                    fila = ""; columnas.clear();
                    try {
                        Etiqueta *etAux = buscarMiEtiqueta(etiqueta);
                        images.insertar(Imagen (id, email, nombre, tam, Fecha(dia,mes,anno), etAux));
                    } catch (exception &err) { //Captura la excepción del vector si la hubiera
                        cout << err.what() << endl;
                    }
                }
            }
        }
        is.close();
    } else {
        throw logic_error(string ("[ImageBook::cargarFicheros] Error en la apertura o tratamiento del fichero " + fichero + "." ));
    }
}

Etiqueta* ImageBook::buscarMiEtiqueta(const std::string &etq) {
    Iterador<Etiqueta> it = labels.iterador();
    for (int i = 0; i < labels.getTam(); ++i){
        if(it.dato().getNombre() == etq)
            return &(it.dato());
        it.siguiente();
    }
    throw logic_error(string("[ImageBook::buscarMiEtiqueta] La etiqueta " + etq + " no se encuentra en su ImageBook."));
}

ListaDEnlazada<Imagen> ImageBook::buscarImgEtq(const std::string etiqueta) {
    ListaDEnlazada<Imagen> busqueda;
    for (int i = 1; i < images.tamlog(); ++i) {
        if (images[i].getEtiqueta() == etiqueta){
            Imagen imgAux(images[i]);
            busqueda.insertaFin(imgAux);
        }
    }
    return busqueda;
}

string ImageBook::etiqMasRepetida() {

    string masRepStr="";
    unsigned masRepUns=0;

    Iterador<Etiqueta> itLb = labels.iterador();
    for (int i = 0; i < labels.getTam(); ++i) {                     //Recorro todas las etiquetas
        unsigned vecesLb = 0;                                       //Anoto cuantas veces aparece cada etiqueta
        for (int j = 1; j <= images.tamlog(); ++j) {                //Por cada etiqueta, miro las imagenes
            if(itLb.dato().getNombre() == images[j].getEtiqueta()){ //Si la imagen tiene la etiqueta
                vecesLb++;                                          //Aparece esa etiqueta +1 vez
                if(vecesLb > masRepUns){                            //Me quedo con el mayor número de ocurrencias
                    masRepUns = vecesLb;
                    masRepStr = itLb.dato().getNombre();
                }
            }
        }
        itLb.siguiente();
    }
    return masRepStr;
}

void ImageBook::mostrarEstado() {
    cout << "Estado actual de su ImageBook" << endl;
    cout << "Etiquetas cargadas : " << labels.getTam() << endl;
    cout << "Imagenes cargadas : " << images.tamlog() << endl;
}

ImageBook::~ImageBook() {}

