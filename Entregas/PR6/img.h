//
//  Created by Antonio Rueda y Lidia Ortega 
//

#ifndef PPM_IMG_H
#define PPM_IMG_H

#define _USE_MATH_DEFINES //Para obtener PI

#include "img.h"
#include "Rango.h"
#include "UTM.h"
#include <cmath>
#include <string>
#include <iostream>
//#include <vecot>

using namespace std;

/** Error al abrir un fichero para lectura */
class ErrorLecturaFichero {};
/** Formato incorrecto (no es una imagen PPM) */
class ErrorFormatoFichero {};
/** Error al abrir un fichero para escritura */
class ErrorEscrituraFichero {};

/** Color con tres componentes: rojo, verde, negro codificadas en 3 bytes */
class RGBColor {
    unsigned char r, g, b;
    
public:
    /** Iniciar a negro */
    RGBColor() { r = g = b = 0; }
    
    /** Iniciar al color indicado */
    RGBColor(unsigned char r, unsigned char g, unsigned char b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    
    /** Indica si ambos colores son iguales */
    bool operator==(RGBColor &color) {
        return color.r == r && color.g == g && color.b == b;
    }
    
    /** Indica si se trata de distinto colores */
    bool operator!=(RGBColor &color) {
        return !(*this == color);
    }
        
    /** Obtener componente rojo */
    unsigned char rojo() const { return r; }
    /** Obtener componente verde */
    unsigned char verde() const { return g; }
    /** Obtener componente azul */
    unsigned char azul() const { return b; }
};

/** Operador de salida a stream */
ostream &operator<<(ostream &os, const RGBColor &color);

/** Clase para leer imágenes en formato PPM */
class Img {
    /** Pixels codificados en rgb */
    RGBColor *pixels;
    /** Tamaño de la imagen */
    int filas, columnas;
    
public:
    /** Constructor para una imagen vacía del tamaño indicado */
    Img(int filas, int columnas);
    
    /** Constructor para una imagen vacía al tamaño y color RGB indicado */
    Img(int filas, int columnas, const RGBColor &color);
    
    /** Constructor para leer la imagen de un fichero PPM indicado */
    Img(const string &fileName);
    
    /** Acceder al color situado en la posición (x, y) */
    RGBColor &pixel(int x, int y) { return pixels[y * filas + x]; }

    void pintarPixel(int x, int y, char r, char g, char b) {
    	RGBColor color(r,g,b);
    	pixels[y * filas + x] = color;
    }
    
    /** Pinta un punto grande en las coordenadas (x,y) en la imagen */
    void pintarPixelGrande(int x, int y, char r, char g, char b) {
   		pintarPixel (x,y,r,g,b);
   		pintarPixel (x,y+1,r,g,b);
   		pintarPixel (x+1,y,r,g,b);
   		pintarPixel (x+1,y+1,r,g,b);    
    }

	/** Pinta un recuadro con las coordenadas de las esquinas indicadas */
    void pintarRecuadro(int xmin, int ymin, int xmax, int ymax, int r, int g, int b);

    /** Guardar la imagen en un fichero PPM */
    void guardar(const string &fileName);
    
    /** Numero de filas */
    int numFilas() {
        return filas;
    }

    /** Numero de columnas */
    int numColumnas(){
        return columnas;
    }

    ///@brief Método para dibujar un pixel dentro de un rango
    void pintarPixel(Rango &limites, UTM &coords, RGBColor &color, bool grande = false){
        if(limites.contiene(coords)){
            double pixelPorGradoX = (double) (this->filas - 1) / (double) limites.distLati(); //La latitud en img.h aquí se entiene como la longitud
            double pixelPorGradoY = (double) (this->columnas - 1) / (double) limites.distLong();

            double vlon = (double) coords.getLongitud();
            double vlat = (double) coords.getLatitud();

            double minlat = limites.getMinY();
            double minlon = limites.getMinX();

            int posX = (vlat - minlat) * pixelPorGradoX;
            int posY = this->columnas - 1 - ((vlon - minlon) * pixelPorGradoY);

            if(grande)
                this->pintarPixelGrande(posX,posY,color.rojo(),color.verde(),color.azul());
            else
                this->pintarPixel(posX,posY,color.rojo(),color.verde(),color.azul());
        }

    }

    ///@brief Método para dibujar una recuadro dentro de un rango
    void pintarRecuadro(Rango &limites, Rango &recuadro, RGBColor &color){
        if(limites.contiene(recuadro)){
            double pixelPorGradoX = (double) (this->filas - 1) / (double) limites.distLati(); //La latitud en img.h aquí se entiene como la longitud
            double pixelPorGradoY = (double) (this->columnas - 1) / (double) limites.distLong();

            double minlat = (double) limites.getMinY();
            double minlon = (double) limites.getMinX();

            double lon1 = (double) recuadro.getMinX();
            double lat1 = (double) recuadro.getMinY();
            double lon2 = (double) recuadro.getMaxX();
            double lat2 = (double) recuadro.getMaxY();

            this->pintarRecuadro(
                    (lat1 - minlat) * pixelPorGradoX,
                    this->columnas - 1 - ((lon1 - minlon) * pixelPorGradoY),
                    (lat2 - minlat) * pixelPorGradoX,
                    this->columnas - 1 - ((lon2 - minlon) * pixelPorGradoY),
                    color.rojo(), color.verde(), color.azul()); //Colores
        }


    }

    ///@brief Método para dibujar una elipse dentro de un rango
    void pintarElipse(Rango &limites, Rango &recuadro, RGBColor &color){
        float semiejeA = recuadro.distLong() / 2; //Semieje mayor, a, de la elipse
        float semiejeB = recuadro.distLati() / 2; //Semieje menor, b, de la elipse

        float alfa = (float) M_PI / 2;      //90 grados es el máximo que hace falta calcular. El resto es simétrico
        float radian = 1 / (float) M_PI;    //1 radián
        float beta = radian / 20;           //El aumento del ángulo, beta, determina la precisión. Cuanto menor, mejor

        for (float i = 0.0; i <= alfa; i+=beta) { //Bucle para iterar los grados

            float puntoX = semiejeA * cos(i);    //Saco la coordenada X de la elipse
            float puntoY = semiejeB * sin(i);    //Saco la coordenada Y de la elipse

            UTM utm1(recuadro.getCentro());
            UTM utm2(recuadro.getCentro());
            UTM utm3(recuadro.getCentro());
            UTM utm4(recuadro.getCentro());

            utm1.asignar(utm1.getLongitud() + puntoX, utm1.getLatitud() + puntoY); //Cuadrante 1
            utm2.asignar(utm2.getLongitud() + puntoX, utm2.getLatitud() - puntoY); //Cuadrante 3
            utm3.asignar(utm3.getLongitud() - puntoX, utm3.getLatitud() + puntoY); //Cuadrante 2
            utm4.asignar(utm4.getLongitud() - puntoX, utm4.getLatitud() - puntoY); //Cuadrante 4

            pintarPixel(limites,utm1,color);    //Dibujamos los casos simétricos
            pintarPixel(limites,utm2,color);
            pintarPixel(limites,utm3,color);
            pintarPixel(limites,utm4,color);
        }

    }

};

#endif

