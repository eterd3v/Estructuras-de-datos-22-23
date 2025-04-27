#include <fstream>
#include <sstream>
#include "Fecha.h"
#include "ImageBook.h"

ImageBook::ImageBook():images(nullptr),labels(),users() {}

ImageBook::ImageBook(const std::string &fileImages, const std::string &fileLabels, const std::string &fileUsers):labels(),users(),images(nullptr) {
    cargarFichero(0,fileLabels);
    cargarFichero(1,fileUsers);
    this->images = new THashImagen(10000,0.65);
    cargarFichero(2,fileImages);
}

void ImageBook::cargarFichero(const char &tipo, const std::string &fichero) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    is.open(fichero); //carpeta de proyecto
    if (is.good()) {

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
                                    labels.push_back(Etiqueta(etiqueta, list<Imagen*>()));
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

                            Imagen imgAux(id,nombre,tam, stoi(id)%1000,Fecha(dia,mes,anno),aux);
                            long unsigned clave = images->djb2(id);
                            Imagen* ptrImg = images->insertar(clave,imgAux);
                            users[email].insertarImagen(*ptrImg);
                            users[email].actualizarPopularidad();
                            for (Etiqueta* e : aux)
                                if(e)
                                    e->nuevaImagen(ptrImg);
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
    if(images)
        if(images->numImages() > 0)
            delete images;
    if(!labels.empty())
        labels.clear();
    if(!users.empty())
        users.clear();

    cargarFichero(0,fileLabels);
    cargarFichero(1,fileUsers);
    this->images = new THashImagen(10000,0.65);
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
    for (map<string,Usuario>::iterator it = users.begin(); it != users.end() ; ++it)
        if(!(it->second.buscarEtiq(etiqueta).empty()))
            aux.push_back(&(it->second));
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

list<Etiqueta *> ImageBook::getMasLikes() {
    unsigned int cant = 5; //cant para la cantidad del top de likes

    list<Etiqueta*> likes;
    for (unsigned int i = 0; i < cant; ++i)
        likes.push_back(nullptr);

    for (list<Etiqueta>::iterator itLbls = labels.begin(); itLbls != labels.end(); ++itLbls){

        bool esta = false;
        for(Etiqueta* e : likes) //Para evitar duplicados comprobamos antes si esta o no
            if(e)
                if(e->getNombre() == itLbls->getNombre())
                    esta = true;

        if(!esta){
            for (list<Etiqueta*>::iterator itLks = likes.begin(); itLks != likes.end(); ++itLks){
                if(itLks.operator*()){ //Si la Etiqueta existe
                    if(itLks.operator*()->getTotalLikes() < itLbls.operator*().getTotalLikes()){ //En el vector del top hay una Etiqueta con menos likes
                        likes.insert(itLks, &(itLbls.operator*()));
                        likes.pop_back();
                        break; //No hace falta iterar más, se ha insertado una Etiqueta que tenía más likes
                    }
                }else{
                    likes.push_front(&(itLbls.operator*()));    //Inserto para tomar Etiquetas con likes
                    likes.pop_back();                           //Borro al final para mantener la misma cantidad siempre
                }
            }
        }

    }
    return likes;
}

list<Usuario *> ImageBook::getMasPopulares() {
    unsigned int cant = 3; //Cantidad de Usuarios que van a mostrarse
    list<Usuario*> pplrs;
    for (unsigned int i = 0; i < cant; ++i)
        pplrs.push_back(nullptr);

    for (map<string,Usuario>::iterator itUsrs = users.begin(); itUsrs != users.end(); ++itUsrs){

        for(list<Usuario*>::iterator itPops = pplrs.begin(); itPops != pplrs.end(); ++itPops){
            if(itPops.operator*()){ //Si el Usuario (puntero) existe
                if(itUsrs->second.getPopularidad() > itPops.operator*()->getPopularidad()){
                    pplrs.insert(itPops, &(itUsrs->second));    //Añado en la posición anterior el siguiente más popular
                    pplrs.pop_back();                           //A continuación quito el último para que no se desborde la cantidad
                    break;
                }
            }else{
                pplrs.push_front(&(itUsrs->second));
                pplrs.pop_back();
            }
        }

    }
    return pplrs;
}

list<Imagen *> ImageBook::buscarImagEtiq(const string &nombreEti) { ///TODO: nuevo
    list<Imagen*> aux;
    for (list<Etiqueta>::iterator it = labels.begin(); it != labels.end() ; ++it)
        if(it->getNombre() == nombreEti){
            aux = it->getImages();
            if(aux.empty())
                throw runtime_error(string("[ImageBook::buscarImagEtiq] La etiqueta "+ nombreEti + " no se encuentra en ninguna Imagen."));
        }
    return aux;
}

Etiqueta *ImageBook::buscarEtiqueta(const string &nombreEti) { ///TODO: nuevo
    Etiqueta* aux = nullptr;
    for (list<Etiqueta>::iterator it = labels.begin(); it != labels.end() ; ++it) {
        if(it->getNombre() == nombreEti){
            aux = it.operator->();
            break;
        }
    }
    return aux;
}

bool ImageBook::insertarImagen(const string &id, Imagen *&img) {
    if(!images)
        throw runtime_error(string("[ImageBook::insertarImagen] No se pueden buscar imagenes actualmente debido a un fallo del contenedor de imagenes."));
    long unsigned clave = images->djb2(id);
    return images->insertar(clave, *img);
}

Imagen *ImageBook::buscarImagen(const string &id) {
    if(!images)
        throw runtime_error(string("[ImageBook::buscarImagen] No se pueden buscar imagenes actualmente debido a un fallo del contenedor de imagenes."));
    long unsigned clave = images->djb2(id);
    return images->buscar(clave, id);
}

bool ImageBook::borrarImagen(const string &id) {
    if(!images)
        throw runtime_error(string("[ImageBook::borrarImagen] No se pueden borrar imagenes actualmente debido a un fallo del contenedor de imagenes."));
    long unsigned clave = images->djb2(id);
    bool aux = images->borrar(clave,id);
    return aux;
}

void ImageBook::mostrarEstado() {
    cout << "====== Estado actual de su ImageBook ======" << endl;
    cout << "Etiquetas cargadas: " << labels.size() << endl;
    cout << "Usuarios cargados: " << users.size() << endl;
    if(images)
        cout << "Imagenes cargadas: " << images->numImages() << endl;
    else
        cout << "Actualmente no es posible conocer informacion de la imagenes." << endl;
    cout << "===========================================" << endl << endl;

}

vector<Usuario *> ImageBook::buscarUsuarioFechaImagen(const Fecha &f) {
    vector<Usuario*> aux;
    for(pair<const string, Usuario> datos : this->users)
        if(datos.second.getImagenFecha(f).empty())
            aux.push_back(&(datos.second));
    return aux;
}

void ImageBook::consultarImagenes() {
    if(images)
        images->mostrarEstadoTablaImagenes();
}

ImageBook::~ImageBook() {}

