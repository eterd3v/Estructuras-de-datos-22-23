/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 20/09/2022
 */
#include "Imagen.h"
#include <stdexcept>

void Imagen::setId(const string &id) {
    Imagen::id = id;
}

void Imagen::setUsr(Usuario *usr) {
    Imagen::usr = usr;
}

void Imagen::setNombre(const string &nombre) {
    Imagen::nombre = nombre;
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

Usuario *Imagen::getUsr() const {
    return usr;
}

const string &Imagen::getNombre() const {
    return nombre;
}

const Fecha &Imagen::getFecha() const {
    return fecha;
}

unsigned int Imagen::getTam() const {
    return tam;
}

Imagen::Imagen() : id("0"), usr(nullptr), nombre("Sin_nombre"), etiqueta(nullptr),
                   tam(0), fecha(1, 1, 1980) {}

Imagen::Imagen(const std::string &id, Usuario* &usr, const std::string &nombre, unsigned int tam, const Fecha &fecha, Etiqueta* &etiquetada)
        : id(id), nombre(nombre), tam(tam), fecha(fecha){
    (usr) ? (this->usr = usr) : (this->usr = nullptr);
    (etiquetada) ? (this->etiqueta = etiquetada) : (this->etiqueta = nullptr);
}

string Imagen::to_string() {
    string aux = id + ":";
    if(usr)
        aux += usr->getEmail() + ":";
    aux += nombre + ":";
    if(etiqueta)
        aux += etiqueta->getNombre() + ":";
    aux += fecha.cadena() + ":" + std::to_string(tam) + ":";
    return aux;

}

Imagen &Imagen::operator=(const Imagen &orig) {
    this->id = orig.id;
    this->usr = orig.usr;
    this->nombre = orig.nombre;
    this->etiqueta = orig.etiqueta;
    this->tam = orig.tam;
    this->fecha = orig.fecha;
    return *this;
}

bool Imagen::operator<(const Imagen &orig) const {
    return stoul(this->id) < stoul(orig.id);
}

bool Imagen::operator==(const Imagen &orig) const {
    return id == orig.id;
}

bool Imagen::operator!=(const Imagen &orig) const {
    return !(orig == *this);
}

string Imagen::getEtiqueta() const {
    if(etiqueta)
        return etiqueta->getNombre();
    throw std::runtime_error("[Imagen::getEtiqueta] Se ha intentado acceder a la etiqueta de una imagen sin etiqueta asociada.");
}

void Imagen::setEtiqueta(Etiqueta* &etiquetada) {
    etiqueta = etiquetada;
}

Imagen::~Imagen() {}
