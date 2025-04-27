/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 20/09/2022
 */
#include "Imagen.h"

void Imagen::setId(const string &id) {
    Imagen::id = id;
}

void Imagen::setEmail(const string &email) {
    Imagen::email = email;
}

void Imagen::setNombre(const string &nombre) {
    Imagen::nombre = nombre;
}

void Imagen::setEtiquetas(const string &etiquetas) {
    Imagen::etiquetas = etiquetas;
}

void Imagen::setFecha(const unsigned int dia, const unsigned int mes, const unsigned int anno) {
    this->fecha.asignarDia(dia,mes,anno);
}

void Imagen::setTam(unsigned int tam) {
    Imagen::tam = tam;
}

const string &Imagen::getId() const {
    return id;
}

const string &Imagen::getNombre() const {
    return nombre;
}

const string &Imagen::getEmail() const {
    return email;
}

const string &Imagen::getEtiquetas() const {
    return etiquetas;
}

const Fecha &Imagen::getFecha() const {
    return fecha;
}

unsigned int Imagen::getTam() const {
    return tam;
}

Imagen::Imagen() : id("0"), email("No_email"), nombre("Sin_nombre"), etiquetas("Sin_etiquetas"),
                   tam(0), fecha(1, 1, 1980) {}

Imagen::Imagen(const string &id, const string &email, const string &nombre, unsigned int tam, const Fecha &fecha,
                const string &etiquetas) : id(id), email(email), nombre(nombre), etiquetas(etiquetas), fecha(fecha), tam(tam) {}

string Imagen::to_string() {
    return id + ":" + email + ":" + nombre + ":" + etiquetas + ":" + fecha.cadena() + ":" + std::to_string(tam);
}

Imagen &Imagen::operator=(const Imagen &orig) {
    this->id = orig.id;
    this->email = orig.email;
    this->nombre = orig.nombre;
    this->etiquetas = orig.etiquetas;
    this->tam = orig.tam;
    this->fecha = orig.fecha;
    return *this;
}

bool Imagen::operator<(const Imagen &orig) const {
    return stoul(this->id) < stoul(orig.id);
}

bool Imagen::operator==(const Imagen &orig) const {
    return id == orig.id &&
           email == orig.email &&
           nombre == orig.nombre &&
           etiquetas == orig.etiquetas &&
           fecha == orig.fecha &&
           tam == orig.tam;
}

bool Imagen::operator!=(const Imagen &orig) const {
    return !(orig == *this);
}
