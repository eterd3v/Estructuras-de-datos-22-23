//
// Created by Antonio on 12/11/2022.
//

#include "Usuario.h"

Usuario::Usuario(): email("NOMAIL"), userImages(), ib(nullptr){}

Usuario::Usuario(const string &email): email(email), userImages(), ib(nullptr){}

Usuario::Usuario(const Usuario &orig): email(orig.email), userImages(orig.userImages), ib(orig.ib) {}

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

unsigned int Usuario::getNumImages() const {
    return numImages;
}

void Usuario::insertarImagen(Imagen &img) {
    userImages.insert(pair<string,Imagen*>(img.getId(),&img));
    ++numImages;
}

std::vector<Imagen*> Usuario::buscarEtiq(const string &nombreEtiq){
    std::vector<Imagen*> aux;
    for(auto it = userImages.begin();it != userImages.end();++it){
        if(it->second)
            if(it->second->getEtiqueta(nombreEtiq))
                aux.push_back(it->second);
    }
    return aux;
}

Imagen* Usuario::buscarImagen(const std::string &id) {
    map<string,Imagen*>::iterator it = userImages.find(id);
    if(it == userImages.end())
        return nullptr;
    return it->second;
}

void Usuario::anadirEtiquetaImagen(const std::string &id, const std::string &nombreEti) {
    if(!ib)
        throw runtime_error(string("[Usuario::anadirEtiquetaImagen] El usuario " + this->email + " no tiene un Imagebook asociado."));

    Imagen* auxImg = buscarImagen(id);
    if(auxImg){
        Etiqueta* auxEti = ib->buscarMiEtiqueta(nombreEti);
        if(auxEti){
            auxImg->anadirEtiqueta(auxEti);
        }else
            throw runtime_error(string("[Usuario::anadirEtiquetaImagen] La etiqueta " + nombreEti + " no se puede incluir ya que no esta cargada en ImageBook."));
    }else
        throw runtime_error(string("[Usuario::anadirEtiquetaImagen] La imagen " + id + " no pertenece al usuario " + this->email));
}

Usuario::~Usuario() {}

const string &Usuario::getEmail() const {
    return email;
}

Imagen *Usuario::getImagenMasAntigua() {
    Imagen* aux = nullptr;
    for (map<string,Imagen*>::iterator it = userImages.begin();it != userImages.end();++it){
        if(it->second) {
            if (aux) {
                if (aux->getFecha() > it->second->getFecha())
                    aux = it->second;
            } else
                aux = it->second;
        }
    }
    return aux;
}

Imagen* Usuario::getImagenMasReciente() {
    Imagen* aux = nullptr;
    for (map<string,Imagen*>::iterator it = userImages.begin();it != userImages.end();++it){
        if(it->second) {
            if (aux) {
                if (aux->getFecha() < it->second->getFecha())
                    aux = it->second;
            } else
                aux = it->second;
        }
    }
    return aux;
}

void Usuario::setIb(ImageBook *ib) {
    Usuario::ib = ib;
}

vector<Usuario*> Usuario::buscarUsuariosEtiq(const std::string &nombreEti) {
    if(ib)
        return ib->buscarUsuarioEtiq(nombreEti);
    throw runtime_error(string("[Usuario::buscarUsuariosEtiq] El usuario " + this->email + " no tiene un Imagebook asociado."));
}

vector<Imagen *> Usuario::getImagenFecha(const Fecha &fecha) {
    vector<Imagen*> aux;

    for(pair<string, Imagen*> datos : userImages)
        if(datos.second->getFecha() == fecha)
            aux.push_back(datos.second);

    return aux;
}

void Usuario::mostrar() {
    cout << "====== El usuario " << email << " tiene "<< userImages.size() <<" imagenes: ======" << endl;
    for (auto it = userImages.begin(); it != userImages.end(); ++it)
        if(it->second)
            cout << it->second->to_string() << endl;
        else
            throw runtime_error(string("[Usuario::mostrar] El usuario " + this->email + " tiene una imagen nula."));
    cout << endl;
}