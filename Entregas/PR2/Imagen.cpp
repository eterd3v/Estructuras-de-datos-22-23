/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 20/09/2022
 */
#include "Imagen.h"
#include <stdexcept>

void Imagen::setId(const string &id) {
    Imagen::id = id;
}

void Imagen::setEmail(const string &email) {
    Imagen::email = email;
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

const string &Imagen::getNombre() const {
    return nombre;
}

const string &Imagen::getEmail() const {
    return email;
}

const Fecha &Imagen::getFecha() const {
    return fecha;
}

unsigned int Imagen::getTam() const {
    return tam;
}

Imagen::Imagen() : id("0"), email("No_email"), nombre("Sin_nombre"), etiqueta(nullptr),
                   tam(0), fecha(1, 1, 1980) {}

Imagen::Imagen(const std::string &id, const std::string &email, const std::string &nombre, unsigned int tam, const Fecha &fecha, Etiqueta* &etiquetada)
        : id(id),email(email),nombre(nombre),tam(tam),fecha(fecha){
    this->etiqueta = etiquetada;
}

string Imagen::to_string() {
    return id + ":" + email + ":" + nombre + ":" + etiqueta->getNombre() + ":" + fecha.cadena() + ":" + std::to_string(tam);
}

Imagen &Imagen::operator=(const Imagen &orig) {
    this->id = orig.id;
    this->email = orig.email;
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
    if(etiqueta == nullptr)
        throw std::runtime_error("[Imagen::getEtiqueta] Se ha intentado acceder a la etiqueta de una imagen sin etiqueta asociada.");
    return etiqueta->getNombre();
}

void Imagen::setEtiqueta(Etiqueta* &etiquetada) {
    etiqueta = etiquetada;
}

Imagen::~Imagen() {}
