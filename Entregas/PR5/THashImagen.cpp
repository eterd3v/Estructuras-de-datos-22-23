/**
 * @author Antonio Javier Armenteros Martínez ajam0011@red.ujaen.es
 * @date 05/12/2022
 */

#include "THashImagen.h"

unsigned long THashImagen::hash(unsigned long &clave, unsigned long &intento) {
    excpTablaCreada();
    if(capacidadTabla == 0)
        throw domain_error("[THashImagen::hash] No se puede calcular el hash con una tabla de capacidad 0.");

    //La mayoría de datos son clave%2==0 (6032 elementos)
    //La mayoría están entre 10^8 y 10^9. La minoría entre 10^5 y 10^6
    unsigned long aux=1,aux2=1;

    if(clave%2==0){             //Más que dispersar
        for (int i = 0; i < 9; ++i)
            aux = aux << 1;     //Desplazo a la izqda el bit
        aux = (aux - clave) % 100000000;
        aux2 += clave % 1000000;
        aux2 *= aux2;
    }else{                      //Menos que dispersar
        unsigned long bucle = clave;
        while (bucle){
            aux2 += bucle%1000;
            aux *= aux2 - aux;
            bucle /= 1000;
        }
    }

    while(!esPrimo(aux) && clave%aux == 0)
        ++aux;
    while(!esPrimo(aux2) && clave%aux2 == 0)
        ++aux2;

    unsigned long h1 = clave % aux, h2 = clave % aux2;
    return (h1 + h2*intento) % capacidadTabla;
}

unsigned long THashImagen::djb2(const string &cadena) {
    unsigned char* str = new unsigned char [cadena.size()];

    for (int i = 0; i < cadena.size(); ++i) {   //Comprobación de la limpieza de la cadena
        if(isdigit(cadena[i])) //isdigit para numeros, isalnum para alfunumericos, isalpha para letras
            str[i]=cadena[i];
        else
            throw invalid_argument(string("[THashImagen::djb2] La cadena '" + cadena + "' no contiene unicamente numeros."));
    }

    unsigned long hash = 5381;
    int c;
    while (c = *str++) hash = ((hash << 5) + hash) + c;
    return hash;
}

unsigned long THashImagen::primoMasCercano(unsigned long &num) {
    unsigned long aux = num;
    if(aux%2==0)
        ++aux;
    while (!esPrimo(aux))
        aux+=2;
    if(aux < num)
        throw runtime_error(string("[THashImagen::primoMasCercano] El primo mas cercano a " + to_string(num) + " no se ha podido calcular"));
    return aux;
}

bool THashImagen::esPrimo(unsigned long &num) { //Test de primalidad
    if(num < 10){
        if( num == 2 || num == 3 || num == 5 || num == 7)
            return true;
        return false;
    }

    if ((num%10)%2 == 0 || (num%10) == 5)
        return false;

    long double z = 1;
    for (int i = 0 ; i < 10 ; ++i)      //Cálculo de la raíz cuadrada por aproximación
        z -= (z*z - num) / (2*z);
    unsigned long raiz = (unsigned long) z;

    for (unsigned long divisor = 3; divisor < raiz ; divisor += 2)
        if(num%divisor == 0)
            return false;

    return true;
}

void THashImagen::excpTablaCreada() {
    if(tabla == nullptr)
        throw runtime_error(string("[THashImagen::numImages] La tabla hash de Imagenes no está creada."));
}

THashImagen::THashImagen() : tabla(nullptr), capacidadTabla(0),tamanioTabla(0),colisionesMax(0), colisionesTotal(0), colisiones10(0) {}

THashImagen::THashImagen(unsigned maxElementos, float lambda) {
    unsigned long tam = (unsigned long) (float) maxElementos / lambda;
    tam = primoMasCercano(tam);
    this->capacidadTabla = tam;
    tamanioTabla = colisionesMax = colisionesTotal = colisiones10 = 0;
    tabla = new vector<elem>(tam);
}

THashImagen::THashImagen(THashImagen &thash) {
    this->tabla = new vector<elem>(thash.tabla->capacity());
    this->tabla->assign(thash.tabla->begin(),thash.tabla->end()); ///TODO: probar tb
    this->capacidadTabla = thash.capacidadTabla;
    this->tamanioTabla = thash.tamanioTabla;
    this->colisionesMax = thash.colisionesMax;
    this->colisionesTotal = thash.colisionesTotal;
    this->colisiones10 = thash.colisiones10;
}

THashImagen &THashImagen::operator=(THashImagen &thash) {
    if(tabla)
        delete tabla;
    this->tabla = new vector<elem>(thash.tabla->capacity());
    this->tabla->assign(thash.tabla->begin(),thash.tabla->end()); ///TODO: probar tb
    this->capacidadTabla = thash.capacidadTabla;
    this->tamanioTabla = thash.tamanioTabla;
    this->colisionesMax = thash.colisionesMax;
    this->colisionesTotal = thash.colisionesTotal;
    this->colisiones10 = thash.colisiones10;

    return *this;
}

Imagen* THashImagen::insertar(unsigned long &clave, Imagen &imagen) {
    excpTablaCreada();
    for (unsigned long intento = 0; intento < capacidadTabla; ++intento) {
        unsigned long pos = hash(clave,intento);
        if(tabla->at(pos).est == estado::vacio){
            tabla->at(pos).img = imagen;
            tabla->at(pos).est = estado::ocupado;
            tamanioTabla++;
            if(intento > colisionesMax)
                colisionesMax = intento;
            if(intento > 10)
                colisiones10++;
            colisionesTotal+=intento;
            return &tabla->at(pos).img;
        }
    }
    return nullptr;
}

bool THashImagen::borrar(unsigned long &clave, const string &id) {
    excpTablaCreada();
    for(long unsigned intento = 0; intento < this->capacidadTabla; ++intento){
        long unsigned pos = hash(clave,intento);
        if(tabla->at(pos).est == estado::ocupado)
            if(tabla->at(pos).img.getId() == id){
                tabla->at(pos).est = estado::eliminado;
                this->tamanioTabla--;
                return true;
            }
    }
    return false;
}

Imagen* THashImagen::buscar(unsigned long &clave,const string &id) {
    excpTablaCreada();
    for(long unsigned intento = 0; intento < this->capacidadTabla; ++intento){
        long unsigned pos = hash(clave,intento);
        if(tabla->at(pos).est == estado::ocupado){
            if(tabla->at(pos).img.getId() == id){
                return &tabla->at(pos).img;
            }
        }
    }
    return nullptr;
}

unsigned int THashImagen::numImages() {
    return tamanioTabla;
}

unsigned int THashImagen::maxColisiones() {
    return colisionesMax;
}

unsigned int THashImagen::numMax10() {
    return colisiones10;
}

long double THashImagen::promedioColisiones() {
    if(tamanioTabla == 0)
        throw domain_error("[THashImagen::promedioColisiones] La tabla actualmente no tiene posiciones ocupadas.");
    return (long double) colisionesTotal / (long double) tamanioTabla;
}

float THashImagen::factorCarga() {
    if(capacidadTabla == 0)
        throw domain_error("[THashImagen::factorCarga] La tabla actualmente no esta creada.");
    return (float) tamanioTabla / (float) capacidadTabla;
}

unsigned int THashImagen::tamTabla() {
    return capacidadTabla;
}

void THashImagen::mostrarEstadoTablaImagenes() {
    if(tabla){
        cout << "====== Estado actual de THashImagen ======" << endl;
        cout << "Factor de carga: " << factorCarga() << endl;
        cout << "Tamanio de la tabla: " << tamanioTabla << " / " << capacidadTabla << endl;
        cout << "Promedio de colisiones: " << this->promedioColisiones() << endl;
        cout << "Se han superado 10 colisiones " << colisiones10 << " veces." << endl;
        cout << "Se han registrado un maximo de " << colisionesMax << " colisiones."<< endl;
        cout << "==========================================" << endl << endl;
    }else
        cout << "====== Actualmente su THashImagen está vacío ======" << endl;
}

THashImagen::~THashImagen() {
    if(tabla)
        delete tabla;
}
