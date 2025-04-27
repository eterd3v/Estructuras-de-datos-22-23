/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 01/12/2022
 */
#include "Imagen.h"
#include <stdexcept>
#include <vector>

void Imagen::setId(const string &id) {
    Imagen::id = id;
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

const Fecha &Imagen::getFecha() const {
    return fecha;
}

unsigned int Imagen::getTam() const {
    return tam;
}

Imagen::Imagen()
        : id("0"), nombre("Sin_nombre"), tam(0), fecha(1, 1, 1980), etiquetada(), likes(0) {}

Imagen::Imagen(const string &id, const string &nombre, unsigned int tam, unsigned int likes, const Fecha &fecha, const deque<Etiqueta *> &etiquetas)
        : id(id), nombre(nombre), tam(tam), likes(likes), fecha(fecha), etiquetada(etiquetas) {}

Imagen::Imagen(const Imagen &orig)
        : id(orig.id), nombre(orig.nombre), tam(orig.tam), likes(orig.likes), fecha(orig.fecha), etiquetada(orig.etiquetada) {}

string Imagen::toString() {
    string aux = id + ":";
    aux += nombre + ":";
    if(!etiquetada.empty()){
        for(Etiqueta* etq : etiquetada)
            if(etq)
                aux += etq->getNombre() + ",";
    }
    aux += fecha.cadena() + ":" + std::to_string(tam) + ":";
    return aux;
}

Imagen &Imagen::operator=(const Imagen &orig) {
    this->id = orig.id;
    this->nombre = orig.nombre;
    this->etiquetada = orig.etiquetada;
    this->tam = orig.tam;
    this->likes = orig.likes;
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

Etiqueta* Imagen::getEtiqueta(const string &etqBuscar) const {
    if(etiquetada.empty())
        throw std::runtime_error("[Imagen::getEtiqueta] Se ha intentado a una imagen sin etiquetas asociadas.");

    for(Etiqueta* etq : etiquetada)
        if(etq){
            if(etq->getNombre() == etqBuscar)
                return etq;
        }else
            throw std::runtime_error("[Imagen::getEtiqueta] En la busqueda de la etiqueta " + etqBuscar + " se ha encontrado etiquetas nulas en la Imagen.");

    return nullptr;
}

std::vector<string> Imagen::getEtiquetas() const {
    std::vector<string> aux;
    for(Etiqueta* e : this->etiquetada)
        if(e)
            aux.push_back(e->getNombre());
        else
            throw runtime_error(string("[Imagen::getEtiquetas] La imagen " + this->id + " tiene asociado etiquetas no permitidas"));
    return aux;
}

void Imagen::anadirEtiqueta(Etiqueta* &etqAdd) { //Como la clase no es controladora de las etiquetas no creo que deba asociar la nueva Etiqueta a la Imagen (etiImages)
    if(etqAdd)
        this->etiquetada.push_back(etqAdd);
    else
        throw logic_error(string("[Imagen::anadirEtiqueta] Se ha intentado añadir una etiqueta inválida a la imagen " + this->id));
}

void Imagen::nuevoLike() {
    likes++;
}

Imagen::~Imagen() {}

unsigned int Imagen::getLikes() const {
    return likes;
}

void Imagen::setLikes(unsigned int likes) {
    this->likes = likes;
}
