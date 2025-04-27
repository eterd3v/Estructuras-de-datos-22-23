/*
 * File:   UTM.cpp
 * Author: Lorena
 * 
 * Created on 14 de octubre de 2021, 11:25
 */

#include "UTM.h"

UTM::UTM() : latitud(0.0), longitud(0.0) {}

UTM::UTM(const float &longitud,const float &latitud) : latitud(latitud), longitud(longitud) {}

UTM::UTM(const UTM& orig): latitud(orig.latitud), longitud(orig.longitud) {}

UTM& UTM::operator=(const UTM &orig){
    this->longitud = orig.longitud;
    this->latitud = orig.latitud;
    return *this;
}

void UTM::asignar(const float &longitud, const float &latitud){
    this->longitud = longitud;
    this->latitud = latitud;
}

bool UTM::operator==(const UTM &orig){ ///TODO: revisar
    return longitud == orig.longitud & latitud == orig.latitud; //Comprueba coordenadas y operador AND a nivel de bit
}

bool UTM::operator!=(const UTM &orig){ ///TODO: revisar
    return ~(longitud == orig.longitud & latitud == orig.latitud); //Comprueba coordenadas, operador AND y negación
}

//bool UTM::operator<(const UTM &orig){ ///TODO: revisar
//    return this->longitud < orig.longitud;
//}
//
//bool UTM::operator>(const UTM &orig){ ///TODO: revisar
//    return this->longitud > orig.longitud;
//}

float UTM::getLongitud() const {
    return longitud;
}

float UTM::getLatitud() const {
    return latitud;
}

UTM::~UTM() {}

void UTM::setLongitud(float longitud) {
    this->longitud = longitud;
}

void UTM::setLatitud(float latitud) {
    this->latitud = latitud;
}

void UTM::aumentar(const float &cantidad){
    longitud += cantidad;
    latitud += cantidad;
}

void UTM::disminuir(const float &cantidad){
    longitud -= cantidad;
    latitud -= cantidad;
}
