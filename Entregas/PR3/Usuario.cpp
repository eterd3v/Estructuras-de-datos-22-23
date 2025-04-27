//
// Created by Antonio on 12/11/2022.
//

#include "Usuario.h"

Usuario::Usuario():email("NOMAIL"),userImages() {}

Usuario::Usuario(const string &email):email(email),userImages() {}

Usuario::Usuario(const Usuario &orig):email(orig.email),userImages(orig.userImages) {}

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

unsigned int Usuario::getNumImages() {
    return this->userImages.tamlog();
}

void Usuario::insertarImagen(Imagen* &img) {
    if(!img)
        throw runtime_error(string("[Usuario::insertarImagen] Se está intentando insertar un puntero nulo como imagen"));
    this->userImages.insertar(img);
}

VDinamico<Imagen*> Usuario::buscarEtiq(const string &etiq){
    VDinamico<Imagen*> aux;
    for (int i = 1; i < userImages.tamlog(); ++i) {
        if(userImages[i])
            if(userImages[i]->getEtiqueta() == etiq)
                aux.insertar(userImages[i]);                //userImages devuelve por referencia su contenido
    }
    return aux;
}

Usuario::~Usuario() {

}

const string &Usuario::getEmail() const {
    return email;
}

void Usuario::mostrarUsr() {
    cout << "====== El usuario " << email << " tiene "<< userImages.tamlog() <<" imagenes: ======" << endl;
    for (int i = 1; i <= userImages.tamlog(); ++i)
        if(userImages[i])
            cout << userImages[i]->to_string() << endl;
        else
            throw runtime_error(string("[Usuario::mostrarUsr] El usuario " + this->email + " tiene una imagen nula."));
    cout << endl;
}