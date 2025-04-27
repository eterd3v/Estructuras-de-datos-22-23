//
// Created by Antonio on 16/12/2022.
//

#include "Rango.h"
#include <stdexcept>

void Rango::actualizar(){
    if(max.getLongitud() < min.getLongitud() && max.getLatitud() < min.getLatitud()){
        UTM aux(max);
        max = min;
        min = aux;
    }
}

Rango::Rango() : min(0.0,0.0), max(1.0,1.0) {};

Rango::Rango(const UTM &min,const UTM&max) : min(min), max(max){
    actualizar();
}

Rango::Rango(const float &xMin,const float &yMin,const float &xMax,const float &yMax):min(xMin,yMin), max(xMax,yMax){
    actualizar();
}

Rango::Rango(const Rango &orig) : min(orig.min), max(orig.max) {}

Rango& Rango::operator=(const Rango &orig){
    this->min = orig.min;
    this->max = orig.max;
    return *this;
}

void Rango::operator+(){ //Desplaza a la DERECHA el Rango
    float diffX = max.getLongitud() - min.getLongitud(); //diferencia de la longitud
    min.setLongitud(max.getLongitud()); //Cambiar la longitud por la de max (va a la derecha)
    max.setLongitud(max.getLongitud() + diffX); //Aumentar la diferencia de longitud
}

void Rango::operator-(){ //Desplaza a la IZQUIERDA el Rango
    float diffX = max.getLongitud() - min.getLongitud(); //diferencia de la longitud
    max.setLongitud(min.getLongitud()); //Cambiar la longitud por la de min (va a la izquierda)
    min.setLongitud(min.getLongitud() - diffX); //Disminuir la diferencia de longitud
}

void Rango::operator++(){ //Desplaza hacia ARRIBA el Rango
    float diffY = max.getLatitud() - min.getLatitud(); //diferencia de la latitud
    min.setLatitud(max.getLatitud());
    max.setLatitud(max.getLatitud() + diffY);
}

void Rango::operator--(){ //Desplaza hacia ABAJO el Rango
    float diffY = max.getLatitud() - min.getLatitud(); //diferencia de la latitud
    max.setLatitud(min.getLatitud());
    min.setLatitud(min.getLatitud() - diffY);
}

bool Rango::contiene(const UTM &coords) const{ //Las coordenadas deben estar dentro del rango
    if(min.getLongitud() <= coords.getLongitud() && min.getLatitud() <= coords.getLatitud()) //Mayor o igual que min
        if(max.getLongitud() >= coords.getLongitud() && max.getLatitud() >= coords.getLatitud()) //Menor o igual que max
            return true;
    return false;
}

bool Rango::contiene(const Rango &rango) const{
    return contiene(rango.min) & contiene(rango.max); //Comprueba coordenadas y operador AND a nivel de bit
}

void Rango::modificar(const float &distancia){ //Aumenta o disminuye el rango desde los vértices
    if(distancia >= 0.0){
        this->min.aumentar(-1*distancia);
        this->max.aumentar(distancia);
    }else{
        this->min.disminuir(distancia);
        this->max.disminuir(-1*distancia);
        actualizar(); //Si se invierten los vértices hay que intercambiar min por max y viceversa
    }
}

Rango Rango::interseccion(const Rango &rango) const{ //Un rango puede tener 0, 1, 2 o 4 coordenadas de otro rango
    if(contiene(rango))
        return rango;

    UTM rMinAlt(rango.getMinX(),rango.getMaxY()); //vertice izquierdo superior
    UTM rMaxAlt(rango.getMaxX(),rango.getMinY());

    bool izqabj = this->contiene(rango.getMin()); //vertice de la izquierda inferior
    bool derarr = this->contiene(rango.getMax()); //vertice de la derecha superior
    bool izqarr = this->contiene(rMinAlt);        //vertice de la izquierda superior
    bool derabj = this->contiene(rMaxAlt);        //vertice de la derecha inferior

    //Mi rango incluye dos vertices del otro rango (es decir, una arista ya sea la izquierda, derecha, arriba o abajo)
    if (izqabj & izqarr || derarr & derabj || derarr & izqarr || izqabj & derabj ){
        Rango aux(rango);

        if(izqabj & izqarr) //arista de la izquierda del rango => hay que desplazar la arista derecha
            aux.setMin(UTM(this->getMin().getLongitud(),rango.getMin().getLatitud()));
        if(derarr & derabj) //arista de la derecha del rango => hay que desplazar la arista izquierda
            aux.setMax(UTM(this->getMax().getLongitud(),rango.getMax().getLatitud()));
        if(derarr & izqarr) //arista de arriba del rango => hay que subir la arista inferior
            aux.setMin(UTM(rango.getMin().getLongitud(),this->getMin().getLatitud()));
        if(izqabj & derabj) //arista de abajo del rango => hay que bajar la arista superior
            aux.setMax(UTM(rango.getMax().getLongitud(),this->getMax().getLatitud()));

        return aux;
    }

    //Mi rango al menos contiene 1 UTM
    if(izqabj || derarr || izqarr || derabj){
        Rango aux(*this);
        if(izqabj) //Contiene el vertice izquierdo inferior del rango.
            aux.setMin(rango.getMin());
        else if(derarr) //Contiene el vertice derecho superior del rango.
            aux.setMax(rango.getMax());
        else if(izqarr){ //Contiene el vertice izquierdo superior del rango.
            aux.setMax(UTM(rMaxAlt.getLongitud(),max.getLatitud()));
            aux.setMin(UTM(min.getLongitud(),rMaxAlt.getLatitud()));
        }else{ //if(derabj) //Contiene el vertice derecho inferior del rango.
            aux.setMin(UTM(rMaxAlt.getLongitud(),min.getLatitud()));
            aux.setMax(UTM(max.getLongitud(),rMaxAlt.getLatitud()));
        }
        return aux;
    }

    throw std::logic_error("[Rango::interseccion] Los rangos no se intersecan ningun espacio comun.");

}

float Rango::distLong() const{
    return max.getLongitud() - min.getLongitud();
}

float Rango::distLati() const{
    return max.getLatitud() - min.getLatitud();
}

const UTM &Rango::getMin() const {
    return min;
}

void Rango::setMin(const UTM &min) {
    Rango::min = min;
}

const UTM &Rango::getMax() const {
    return max;
}

void Rango::setMax(const UTM &max) {
    Rango::max = max;
}

const float Rango::getMinX() const{
    return this->min.getLongitud();
}

const float Rango::getMinY() const{
    return this->min.getLatitud();
}

const float Rango::getMaxX() const{
    return this->max.getLongitud();
}

const float Rango::getMaxY() const{
    return this->max.getLatitud();
}

string Rango::toString() const{
    return "min(" + to_string(getMinX())+","+to_string(getMinY())+") y max(" + to_string(getMaxX())+","+to_string(getMaxY())+")";
}

const UTM Rango::getCentro() const{
    float centroX = this->min.getLongitud() + (this->distLong()/2);
    float centroY = this->min.getLatitud() + (this->distLati()/2);
    return UTM(centroX,centroY);
}


Rango::~Rango() {}
