//
// Created by Antonio on 24/10/2022.
//

#include "Etiqueta.h"

Etiqueta::Etiqueta(const string &nombre) : nombre(nombre) {}

Etiqueta::Etiqueta(): nombre("") {}

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

