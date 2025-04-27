#include <fstream>
#include <sstream>
#include "Fecha.h"
#include "Iterador.h"
#include "ImageBook.h"

ImageBook::ImageBook():images(10000),labels(),users() {}

ImageBook::ImageBook(const std::string &fileImages, const std::string &fileLabels, const std::string &fileUsers):labels(),users(),images(10000) {
    cargarFicheros(0,fileLabels);
    cargarFicheros(1,fileUsers);
    cargarFicheros(2,fileImages);
}

void ImageBook::cargarFicheros(const char &tipo, const std::string &fichero) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    is.open(fichero); //carpeta de proyecto
    if (is.good()) {

        while (getline(is, fila)) {

            if (fila != "") { //¿Se ha leído una nueva fila?

                columnas.str(fila);

                switch (tipo) { //Dependiendo del tipo de archivo, se tratarán las filas de una forma u otra
                    case 0: ///ETIQUETAS
                    {
                        string etiqueta;
                        getline(columnas, etiqueta, ',');
                        columnas.clear();
                        try {
                            Etiqueta et(etiqueta);
                            labels.insertaFin(et);
                        } catch (exception &err) {
                            cout << err.what() << endl;
                        }
                        break;
                    }
                    case 1: ///USUARIOS
                    {
                        string correo;
                        getline(columnas, correo, ',');
                        columnas.clear();
                        try {
                            Usuario usr(correo);
                            this->users.inserta(usr);
                        } catch (exception &err) {
                            cout << err.what() << endl;
                        }
                        break;
                    }
                    case 2: ///IMÁGENES
                    {
                        string id, email, nombre, etiqueta;
                        int tam, dia, mes, anno;

                        //formato de fila: id;email;nombre;tam;fecha;etiquetas
                        getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                        getline(columnas, email, ';');
                        getline(columnas, nombre, ';');
                        columnas >> tam; columnas.ignore();  //las secuencia numéricas se leen y trasforman directamente, omitiendo el carácter ';'
                        columnas >> dia; columnas.ignore();
                        columnas >> mes; columnas.ignore();
                        columnas >> anno; columnas.ignore();
                        getline(columnas, etiqueta, ',');
                        fila = "";
                        columnas.clear();
                        try {

                            Etiqueta *etAux = buscarMiEtiqueta(etiqueta);
                            Usuario usrFich(email);
                            Usuario *usrAux;
                            usrAux = users.buscaIt(usrFich);

                            if(etAux){
                                if(usrAux){
                                    images.insertar(Imagen(id, usrAux, nombre, tam, Fecha(dia, mes, anno), etAux));
                                    Imagen* imgAux = &images[images.tamlog()];
                                    if(imgAux)
                                        usrAux->insertarImagen(imgAux);
                                    else
                                        throw runtime_error(string("[ImageBook::cargarFicheros] No se pudo añadir la imagen " + id + " al usuario " + email));
                                }else
                                    throw runtime_error(string("[ImageBook::cargarFicheros] No se pudo asociar el usuario " + email + " en el sistema Imagebook."));
                            }else
                                throw runtime_error(string("[ImageBook::cargarFicheros] No se pudo encontrar la etiqueta '" + etiqueta + "' en el sistema Imagebook."));
                        } catch (exception &err) {
                            cout << err.what() << endl;
                        }
                        break;
                    }
                    default:
                        throw range_error(string("[ImageBook::cargarFicheros] El tipo de fichero no esta bien especificado."));
                }
            }
        }
        is.close();
    } else
        throw logic_error(string ("[ImageBook::cargarFicheros] Error en la apertura o tratamiento del fichero " + fichero ));
}

void ImageBook::cargarFicheros(const std::string &fileImages, const std::string &fileLabels, const std::string &fileUsers) {
    if(images.tamlog() > 0)
        for (int i = 1; i < images.tamlog(); ++i)
            images.borrar();
    if(labels.getTam() > 0)
        for (int i = 0; i < labels.getTam(); ++i)
            labels.borrarFinal();
    if(users.numElementos() > 0)
        users.borraTodo();

    cargarFicheros(0,fileLabels);
    cargarFicheros(1,fileUsers);
    cargarFicheros(2,fileImages);
}

Etiqueta* ImageBook::buscarMiEtiqueta(const std::string &etq) {
    Iterador<Etiqueta> it = labels.iterador();
    for (int i = 0; i < labels.getTam(); ++i){
        if(it.dato().getNombre() == etq)
            return &(it.dato());
        it.siguiente();
    }
    return nullptr;
}

Usuario *ImageBook::buscarUsuario(const std::string &email) {
    Usuario aux(email);
    return users.buscaRec(aux);
}

VDinamico<Usuario *> ImageBook::buscarUsuarioEtiq(const std::string &etiqueta) {
    VDinamico<Usuario*> aux(128);
    VDinamico<Usuario*> usrs = this->users.recorreInorden();
    for (int i = 1; i <= usrs.tamlog() ; ++i)
        if(usrs[i]->buscarEtiq(etiqueta).tamlog() > 0)
            aux.insertar(usrs[i]);
    return aux;
}

VDinamico<Usuario *> ImageBook::getMasActivos() {
    VDinamico<Usuario*> usrs = this->users.recorreInorden();
    VDinamico<Usuario*> aux;

    unsigned maxImgUsr = 0;

    for (int i = 1; i <= usrs.tamlog() ; ++i) {
        if(usrs[i]){
            if(usrs[i]->getNumImages() > maxImgUsr){
                aux.borrarTodo();
                aux.insertar(usrs[i]);
                maxImgUsr = usrs[i]->getNumImages();
            }else if (usrs[i]->getNumImages() == maxImgUsr){
                aux.insertar(usrs[i]);
            }
        }
    }
    return aux;
}

void ImageBook::mostrarEstado() {
    cout << "Estado actual de su ImageBook" << endl;
    cout << "Etiquetas cargadas : " << labels.getTam() << endl;
    cout << "Usuarios cargados : " << users.numElementos() << endl;
    cout << "Imagenes cargadas : " << images.tamlog() << endl;
}

ImageBook::~ImageBook() {}

