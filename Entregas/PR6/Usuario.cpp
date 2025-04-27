/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 05/12/2022
 */

#include "Usuario.h"

void Usuario::ibAsociado() {
    if(!ib)
        throw runtime_error(string("[Usuario::ibAsociado] El usuario " + this->email + " no tiene un Imagebook asociado."));
}

Usuario::Usuario(): email("NOMAIL"), userImages(), numImages(0),ib(nullptr){}

Usuario::Usuario(const string &email): email(email), userImages(), numImages(0), ib(nullptr){}

Usuario::Usuario(const Usuario &orig): email(orig.email), userImages(orig.userImages),numImages(0), ib(orig.ib) {}

bool Usuario::operator<(const Usuario &orig) {
    return this->email < orig.email;
}

bool Usuario::operator>(const Usuario &orig) {
    return this->email > orig.email;
}

bool Usuario::operator<=(const Usuario &orig) {
    return this->operator<(orig) & this->operator==(orig);
}

bool Usuario::operator>=(const Usuario &orig) {
    return this->operator>(orig) & this->operator==(orig);
}

bool Usuario::operator==(const Usuario &orig) {
    if(this->email == orig.email)
        return true;
    return false;
}

bool Usuario::operator!=(const Usuario &orig) {
    return !this->operator==(orig);
}

void Usuario::insertarImagen(Imagen &img) {
    userImages.insert(pair<string,Imagen*>(img.getId(),&img));
    ++numImages;
}

void Usuario::anadirEtiquetaImagen(const std::string &id, const std::string &nombreEti) {
    ibAsociado();

    Imagen* auxImg = buscarImagen(id);
    if(auxImg){
        Etiqueta* auxEti = ib->buscarMiEtiqueta(nombreEti);
        if(auxEti){
            auxImg->anadirEtiqueta(auxEti);
        }else
            throw runtime_error(string("[Usuario::anadirEtiquetaImagen] La etiqueta " + nombreEti + " no se puede incluir ya que no esta cargada en ImageBook."));
    }else
        throw runtime_error(string("[Usuario::anadirEtiquetaImagen] La imagen " + id + " no contiene al usuario " + this->email));
}

Imagen* Usuario::buscarImagen(const std::string &id) {
    map<string,Imagen*>::iterator it = userImages.find(id);
    if(it == userImages.end())
        return nullptr;
    return it->second;
}

vector<Imagen*> Usuario::buscarEtiq(const string &nombreEtiq){
    vector<Imagen*> aux;
    for(auto it = userImages.begin();it != userImages.end();++it)
        if(it->second)
            if(it->second->getEtiqueta(nombreEtiq))
                aux.push_back(it->second);
    return aux;
}

vector<Usuario*> Usuario::buscarUsuariosEtiq(const std::string &nombreEti) {
    ibAsociado();
    return ib->buscarUsuarioEtiq(nombreEti);
}

vector<Imagen*> Usuario::getImagenFecha(const Fecha &fecha) {
    vector<Imagen*> aux;

    for(pair<string, Imagen*> datos : userImages)
        if(datos.second->getFecha() == fecha)
            aux.push_back(datos.second);

    return aux;
}

Imagen* Usuario::getImagenMasAntigua() {
    Imagen* aux = nullptr;
    for (pair<string, Imagen*> datos : this->userImages) {
        if(datos.second && aux){ //Para actualizar, si se itera sobre un puntero no nulo y ya se guarda un puntero reciente
            if (aux->getFecha() > datos.second->getFecha())
                aux = datos.second;
        }else if(datos.second)  //Para guardar una supuesta imagen más reciente, si se itera sobre un puntero no nulo de imagen
            aux = datos.second;
    }
    return aux;
}

Imagen* Usuario::getImagenMasReciente() {
    Imagen* aux = nullptr;
    for (pair<string, Imagen*> datos : this->userImages) {
        if(datos.second && aux){ //Para actualizar, si se itera sobre un puntero no nulo y ya se guarda un puntero reciente
            if (aux->getFecha() < datos.second->getFecha())
                aux = datos.second;
        }else if(datos.second)  //Para guardar una supuesta imagen más reciente, si se itera sobre un puntero no nulo de imagen
            aux = datos.second;
    }
    return aux;
}

vector<Imagen *> Usuario::getImagenesEtiqueta(const string &nombreEti) {
    ibAsociado();
    vector<Imagen*> aux;
    vector<Usuario*> usrsEtiq = ib->buscarUsuarioEtiq(nombreEti);
    for (Usuario* usr : usrsEtiq){
        if(usr){
            vector<Imagen*> imgsEtiq = usr->buscarEtiq(nombreEti);
            for (Imagen* img : imgsEtiq)
                aux.push_back(img);
        }
    }
    return aux;
}

vector<Imagen*> Usuario::imagenEnZona(const Rango &rango) const {
    vector<Imagen*> aux;
    for (pair<string, Imagen*> datos : this->userImages)
        if(datos.second) //Si existe el puntero a la Imagen (no es nulo)
            if(rango.contiene(datos.second->getPos())) //Y la posición está dentro del rango
                aux.push_back(datos.second);
    return aux;
}

void Usuario::likeAutomaticoZona(const Rango &rango){
    ibAsociado();
    vector<Usuario*> vUsrEtq = ib->buscarUsuarLugar(rango);
    for (Usuario* usr : vUsrEtq) //Pasamos por todos los usuarios que han hecho una foto dentro de ese rango
        if(usr)
            if(usr->getEmail() != this->email) //No vale dar auto-like
                for(Imagen* img : usr->imagenEnZona(rango)) //Damos likes a las imagenes que contienen la etiqueta del parámetro del método
                    img->nuevoLike();
}

void Usuario::meGustaImagen(Imagen *&img) {
    if(!img)
        throw invalid_argument("[Usuario::meGustaImagen] Se ha pasado una imagen nula.");
    if(this->buscarImagen(img->getId()))
        throw domain_error(string("[Usuario::meGustaImagen] Un usuario no se puede dar like a si mismo."));
    img->nuevoLike();
}

void Usuario::likeAutomatico(const string &nombreEtiq) {
    ibAsociado();
    vector<Usuario*> vUsrEtq = ib->buscarUsuarioEtiq(nombreEtiq);
    for (Usuario* usr : vUsrEtq){ //Pasamos por todos los usuarios del sistema
        if(usr){
            if(usr->getEmail() != this->email){ //No vale dar auto-like
                vector<Imagen*> vImgUsr = usr->getImagenesEtiqueta(nombreEtiq);
                    for(Imagen* img : vImgUsr) //Damos likes a las imagenes que contienen la etiqueta del parámetro del método
                        img->nuevoLike();
            }
        }
    }
}

void Usuario::actualizarPopularidad() {
    popularidad = 0;
    for (pair<string, Imagen*> datos : this->userImages)
        if(datos.second)
            popularidad += datos.second->getLikes();
        else
            throw runtime_error(string("[Usuario::actualizarPopularidad] El usuario " + this->email + " tiene una imagen nula."));
}

void Usuario::setIb(ImageBook *ib) {
    Usuario::ib = ib;
}

void Usuario::setEmail(const string &email) {
    Usuario::email = email;
}

void Usuario::setPopularidad(unsigned int popularidad) {
    Usuario::popularidad = popularidad;
}

const string &Usuario::getEmail() const {
    return email;
}

unsigned int Usuario::getPopularidad() const {
    return popularidad;
}

unsigned int Usuario::getNumImages() const {
    return numImages;
}

void Usuario::mostrar(const bool modo) {
    cout << "====== " << email;
    if(ib)
        cout << "esta en un ImageBook, ";
    cout << " tiene "<< userImages.size() <<" imagenes y tiene ";
    actualizarPopularidad();
    cout << popularidad << " likes. ======" << endl;

    if(modo){
        for (pair<string, Imagen*> datos : this->userImages)
            if (datos.second)
                cout << datos.second->toString() << endl;
            else
                throw runtime_error(string("[Usuario::mostrar] El usuario " + this->email + " tiene una imagen nula."));
        cout << endl;
    }
}

Usuario::~Usuario() {}
