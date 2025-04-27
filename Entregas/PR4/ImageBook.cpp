#include <fstream>
#include <sstream>
#include "Fecha.h"
#include "ImageBook.h"

ImageBook::ImageBook():images(),labels(),users() {}

ImageBook::ImageBook(const std::string &fileImages, const std::string &fileLabels, const std::string &fileUsers):labels(),users(),images(10000) {
    cargarFichero(0,fileLabels);
    cargarFichero(1,fileUsers);
    cargarFichero(2,fileImages);
}

void ImageBook::cargarFichero(const char &tipo, const std::string &fichero) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    is.open(fichero); //carpeta de proyecto
    if (is.good()) {

        unsigned contador_imagenes = 0;
        while (getline(is, fila)) {

            if (fila != "") { //¿Se ha leído una nueva fila?

                columnas.str(fila);
                switch (tipo) {
                    case 0: ///ETIQUETAS
                    {
                        try {
                            string etiqueta;
                            do{
                                etiqueta.clear();
                                getline(columnas, etiqueta, ',');
                                if(etiqueta != "")
                                    labels.push_back(Etiqueta(etiqueta));
                            }while(etiqueta != "");
                            columnas.clear();
                        } catch (exception &err) {
                            cout << err.what() << endl;
                        }
                        break;
                    }
                    case 1: /// USUARIOS
                    {
                        string correo;
                        getline(columnas, correo, ',');
                        columnas.clear();
                        try {
                            users[correo] = Usuario(correo);
                            users[correo].setIb(this);
                        } catch (exception &err) {
                            cout << err.what() << endl;
                        }
                        break;
                    }
                    case 2: ///IMAGENES
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

                        if(users.find(email) != users.end()){
                            deque<Etiqueta*> aux;
                            do{
                                etiqueta.clear();
                                getline(columnas, etiqueta, ',');
                                for (list<Etiqueta>::iterator it = labels.begin(); it != labels.end(); ++it){
                                    if(it->getNombre() == etiqueta)
                                        aux.push_back(it.operator->());
                                }
                            }while(etiqueta != "");

                            Imagen imgAux(id,nombre,tam, Fecha(dia,mes,anno),aux);
                            images[contador_imagenes]=imgAux;
                            users[email].insertarImagen(images[contador_imagenes]);
                            contador_imagenes++;
                        }
                        columnas.clear();
                        break;
                    }
                    default:
                        throw range_error(string("[ImageBook::cargarFicheros] El tipo de fichero no esta bien especificado."));
                };

            }
        }
    }
    is.close();
}

void ImageBook::cargar(const string &fileImages, const string &fileLabels, const std::string &fileUsers) {
    if(!images.empty())
        images.clear();
    if(!labels.empty())
        labels.clear();
    if(!users.empty())
        users.clear();

    cargarFichero(0,fileLabels);
    cargarFichero(1,fileUsers);
    cargarFichero(2,fileImages);
}

Etiqueta* ImageBook::buscarMiEtiqueta(const std::string &etq) {
    for (list<Etiqueta>::iterator it = labels.begin(); it != labels.end(); ++it){
        if(it->getNombre() == etq)
            return it.operator->();
    }
    return nullptr;
}

Usuario* ImageBook::buscarUsuario(const std::string &email) {
    map<string,Usuario>::iterator it = users.find(email);
    if(it == users.end())
        throw runtime_error(string("[ImageBook::buscarUsuario] No se ha encontrado el usuario " + email + " en el ImageBook"));
    return &(it->second);
}

vector<Usuario*> ImageBook::buscarUsuarioEtiq(const std::string &etiqueta) {
    vector<Usuario*> aux;

    for (map<string,Usuario>::iterator it = users.begin(); it != users.end() ; ++it){
        if(!(it->second.buscarEtiq(etiqueta).empty())){
            aux.push_back(&(it->second));
        }
    }

    return aux;
}

vector<Usuario*> ImageBook::getMasActivos() {
    vector<Usuario*> aux;
    unsigned maxImgUsr = 0;

    for (map<string,Usuario>::iterator it = users.begin(); it != users.end() ; ++it){
        if(it->second.getNumImages() > maxImgUsr){
            aux.clear();
            aux.push_back(&(it->second));
            maxImgUsr = it->second.getNumImages();
        }else if(it->second.getNumImages() == maxImgUsr){
            aux.push_back(&(it->second));
        }
    }
    return aux;
}

void ImageBook::mostrarEstado() {
    cout << "Estado actual de su ImageBook" << endl;
    cout << "Etiquetas cargadas : " << labels.size() << endl;
    cout << "Usuarios cargados : " << users.size() << endl;
    cout << "Imagenes cargadas : " << images.size() << endl;
}

vector<Usuario *> ImageBook::buscarUsuarioFechaImagen(const Fecha f) {
    vector<Usuario*> aux;

    for (map<string,Usuario>::iterator it = users.begin(); it != users.end() ; ++it){
        if(!it->second.getImagenFecha(f).empty())
            aux.push_back(&(it->second));
    }

    return aux;
}

ImageBook::~ImageBook() {}

