/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 20/09/2022
 */
#include "ContenedorImagenes.h"

ContenedorImagenes::ContenedorImagenes(): tamMax(TAM_PREDEF), tamContenedor(0) {
    contendorImgs = new Imagen[TAM_PREDEF];
}

ContenedorImagenes::ContenedorImagenes(unsigned int tamMax):tamMax(tamMax), tamContenedor(0) {
    contendorImgs = new Imagen[tamMax];
}

ContenedorImagenes::ContenedorImagenes(const ContenedorImagenes &orig){
    contendorImgs = new Imagen[orig.tamMax];
    for (int i = 0; i < orig.tamContenedor; ++i)
        this->contendorImgs[i]=orig.contendorImgs[i];
    tamMax=orig.tamMax;
    tamContenedor=orig.tamContenedor;
}

ContenedorImagenes::ContenedorImagenes(const ContenedorImagenes& orig, unsigned int posicionInicial, unsigned int numElementos){

    if(posicionInicial + numElementos > orig.tamMax){
        tamMax = numElementos;
        tamContenedor=0;
        for (int i = posicionInicial; i < posicionInicial + numElementos; ++i){

            this->contendorImgs[tamContenedor++]=orig.contendorImgs[i];

        }
    }else
        throw invalid_argument("ERROR: Se está intentando copiar elementos que no se encuentran en el contenedor original");


}

void ContenedorImagenes::asigna(const Imagen& dato, unsigned int pos){
    if (pos > tamContenedor)
        throw out_of_range("Error: se ha intentado colocar la imagen " + dato.getId() + " en una posicion invalida.");

    contendorImgs[pos] = dato;
    this->tamContenedor++;
}

Imagen ContenedorImagenes::recupera(unsigned int pos) {
    if(pos > this->tamContenedor)
        throw out_of_range("Error: se ha intentado acceder una posicion invalida (" + to_string(pos) + "/" + to_string(this->tamContenedor)+")");

    return contendorImgs[pos];
}

unsigned int ContenedorImagenes::busca(const Imagen &img){
    unsigned int derecha = tamContenedor, izquierda = 0; //Extremos del contenedor
    unsigned int pos; //Posición que buscamos en el contenedor.

    while(img.getId() != contendorImgs[pos].getId() && izquierda != derecha){ //Búsqueda binaria de la imagen en el contenedor
        pos = (derecha + izquierda)/2;
        (img < contendorImgs[pos]) ? (derecha = pos) : (izquierda = pos);
    }

    if(img != contendorImgs[pos])
        throw invalid_argument("ERROR: La imagen " + img.getNombre() + " con id " + img.getId() + "no se encuentra en el contenedor.");

    return pos;
}

ContenedorImagenes ContenedorImagenes::localiza(const string email, const Fecha Fecha_inicial, const Fecha Fecha_final, unsigned int cantidad){

    if(cantidad > tamContenedor)
        throw invalid_argument("ERROR: Se intenta recopilar mas imagenes de las que hay en el contenedor.");

    if(Fecha_final < Fecha_inicial)
        throw invalid_argument("ERROR: la Fecha final es anterior a la Fecha inicial");

    ContenedorImagenes aux(cantidad);

    for (int i = 0; i < tamContenedor; ++i) {
        if(contendorImgs[i].getEmail() == email && Fecha_inicial <= contendorImgs[i].getFecha() && contendorImgs[i].getFecha() <= Fecha_final)
            if(aux.tam() < cantidad)
                aux.asigna(contendorImgs[i],aux.tam());
    }

    return aux;
}


void ContenedorImagenes::ordenar() {
    sort(contendorImgs,contendorImgs + tamContenedor);
}

void ContenedorImagenes::ordenarRev() {
    ordenar();
    reverse(contendorImgs, contendorImgs + tamContenedor);
}

unsigned int ContenedorImagenes::tam(){
    return tamContenedor;
}

ContenedorImagenes::~ContenedorImagenes() {
    delete[] contendorImgs;
}

