/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 01/12/2022
 */

#include "Etiqueta.h"

Etiqueta::Etiqueta(): nombre(""), etiImages() {}

Etiqueta::Etiqueta(const string &nombre, const list<Imagen*> &etiImages) : nombre(nombre), etiImages(etiImages) {}

Etiqueta::Etiqueta(const Etiqueta &orig) : nombre(orig.nombre), etiImages(orig.etiImages){}

Etiqueta::~Etiqueta() {}

const string &Etiqueta::getNombre() const {
    return nombre;
}

void Etiqueta::setNombre(const string &nombre) {
    Etiqueta::nombre = nombre;
}

bool Etiqueta::operator==(const Etiqueta &rhs) const {
    return nombre == rhs.nombre;
}

bool Etiqueta::operator!=(const Etiqueta &rhs) const {
    return !(rhs == *this);
}

void Etiqueta::nuevaImagen(Imagen *&img) {
    if(img)
        etiImages.push_back(img);
    else
        throw runtime_error(string("[Etiqueta::nuevaImagen] La etiqueta " + this->nombre + " no se ha podido incluir una imagen nueva."));
}

list<Imagen *> Etiqueta::getImages() {
    return this->etiImages;
}

unsigned int Etiqueta::getTotalLikes() {
    unsigned int aux = 0;
    for (Imagen* img : this->etiImages)
        if(img)
            (aux += img->getLikes());
        else
            throw runtime_error(string("[Etiqueta::getTotalLikes] No se puede calcular los likes de " + this->nombre));
    return aux;
}