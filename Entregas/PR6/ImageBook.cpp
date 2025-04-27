#include <fstream>
#include <sstream>
#include "Fecha.h"
#include "ImageBook.h"
#include <limits>
#include "UTM.h"
#include <math.h>

ImageBook::ImageBook():images(),labels(),users() {}

ImageBook::ImageBook(const std::string &fileImages, const std::string &fileLabels, const std::string &fileUsers):labels(),users(),images() {
    cargarFichero(0,fileLabels);
    cargarFichero(1,fileUsers);
    cargarFichero(2,fileImages);
}

void ImageBook::cargarFichero(const char &tipo, const std::string &fichero) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    float xMin=numeric_limits<float>::max(), yMin=xMin, xMax=-1*xMin, yMax=-1*xMin;

    is.open(fichero); //carpeta de proyecto
    if (is.good()) {

        while (getline(is, fila)) {

            if (!fila.empty()) { //¿Se ha leído una nueva fila?

                columnas.str(fila);
                switch (tipo) {
                    case 0: ///ETIQUETAS
                    {
                        try {
                            string etiqueta;
                            do{
                                etiqueta.clear();
                                getline(columnas, etiqueta, ',');
                                if(!etiqueta.empty())
                                    labels.emplace_back(Etiqueta(etiqueta, list<Imagen*>()));
                            }while(!etiqueta.empty());
                            columnas.clear();
                        } catch (exception &err) {
                            cout << err.what() << endl;
                        }
                        break;
                    }
                    case 1: /// USUARIOS
                    {
                        string correo;
                        getline(columnas, correo, ',');
                        columnas.clear();
                        try {
                            users[correo] = Usuario(correo);
                            users[correo].setIb(this);
                        } catch (exception &err) {
                            cout << err.what() << endl;
                        }
                        break;
                    }
                    case 2: ///IMAGENES
                    {
                        string id, email, nombre;
                        int tam, dia, mes, anno;

                        //formato de fila: id;email;nombre;tam;fecha;etiquetas;longitud;latitud
                        getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                        getline(columnas, email, ';');
                        getline(columnas, nombre, ';');
                        columnas >> tam; columnas.ignore();  //las secuencia numéricas se leen y trasforman directamente, omitiendo el carácter ';'
                        Fecha fecha;
                        {
                            columnas >> dia; columnas.ignore();
                            columnas >> mes; columnas.ignore();
                            columnas >> anno; columnas.ignore();
                            fecha.asignarDia(dia, mes, anno);
                        }
                        deque<Etiqueta*> etiquetas;
                        {
                            string lineaEtqs;
                            getline(columnas, lineaEtqs, ';');
                            do{ //Busco las etiquetas en la lista labels y lo añado al deque
                                size_t pos = lineaEtqs.find_first_of(",");
                                string etqAux;
                                (pos != string::npos) ? etqAux = lineaEtqs.substr(0,pos) : etqAux = lineaEtqs;
                                lineaEtqs.erase(0,etqAux.length()+1); //Quitamos la etiqueta que vamos a procesar del resto

                                for (list<Etiqueta>::iterator it = labels.begin(); it != labels.end(); ++it)
                                    if(it->getNombre() == etqAux)
                                        etiquetas.push_back(it.operator->());

                            }while(!lineaEtqs.empty());
                        }
                        UTM posUTM;
                        {
                            float longitud, latitud;
                            columnas >> longitud; columnas.ignore();
                            columnas >> latitud; columnas.ignore();
                            posUTM.asignar(longitud, latitud);
                        }



                        if(users.find(email) != users.end()){

                            images.emplace(id,Imagen(id, nombre, tam, stoi(id)%1000, fecha, posUTM, etiquetas));
                            {
                                float longitud = posUTM.getLongitud(), latitud = posUTM.getLatitud();
                                if(longitud < xMin) xMin = longitud;
                                if(latitud < yMin) yMin = latitud;
                                if(longitud > xMax) xMax = longitud;
                                if(latitud > yMax) yMax = latitud;
                            }

                            Imagen *imgPtr = nullptr;
                            if(images.find(id) != images.end())
                                imgPtr = &(images.find(id)->second);

                            if(imgPtr){
                                users[email].insertarImagen(*imgPtr);
                                users[email].actualizarPopularidad();
                                for (Etiqueta* e : etiquetas)
                                    if(e)
                                        e->nuevaImagen(imgPtr);
                            }
                        }
                        columnas.clear();
                        break;
                    }
                    default:
                        throw range_error(string("[ImageBook::cargarFicheros] El tipo de fichero no esta bien especificado."));
                };

            }
        }
        if(tipo==2){
            int nDiv = 619;
            Rango r(xMin,yMin,xMax,yMax);
            r.modificar(5);
            imagePos = new MallaRegular<Imagen*>(r,nDiv);

            Img img(600,600,RGBColor()); //Crea imagen de 600x600 de fondo negro

            ///AVISO PARA LA CORRECCIÓN
            ///La imagen generada en la defensa del 20 de diciembre con la entrega no voluntaria no es la que se
            ///puede generar con esta actualización de la versión voluntaria. Ahora es más visual y claro

            {   //Pintar cuadrículas a lo largo de la imagen para los puntos de las Imagenes
                RGBColor verdeOscuro(42, 98, 61);

                int divs = 20;  //Divisiones a obtener en la imagen
                float casillaX = r.distLong()/divs; //Tamaño en la imagen de cada casilla
                float casillaY = r.distLati()/divs;

                for (float x = r.getMinX(); x < r.getMaxX(); x += 0.01 ) { //Dibujo líneas paralelas al eje X
                    for(int j = 0; j < divs ; ++j){
                        float y = r.getMinY() + j*casillaY;
                        UTM utm(x,y);
                        img.pintarPixel(r, utm, verdeOscuro); //Pinto todas las imágenes de tonos amarillos-naranja-rojos
                    }
                }

                for (float y = r.getMinY(); y < r.getMaxY(); y += 0.01 ) { //Dibujo líneas paralelas al eje Y
                    for(int j = 0; j < divs ; ++j){
                        float x = r.getMinX() + j*casillaX;
                        UTM utm(x,y);
                        img.pintarPixel(r, utm, verdeOscuro); //Pinto todas las imágenes de tonos amarillos-naranja-rojos
                    }
                }

            }

            {   //Pintar cada coordenada de las imágenes de un color
                vector<RGBColor> colores;               //Paleta de colores https://www.color-hex.com/color-palette/4699
                colores.push_back(RGBColor(255,0,0));   //rojo
                colores.push_back(RGBColor(255,77,0));  //intermedio entre rojo y naranja
                colores.push_back(RGBColor(255,116,0)); //naranja
                colores.push_back(RGBColor(255,154,0)); //intermedio entre naranja y amarillo
                colores.push_back(RGBColor(255,193,0)); //amarillo

                char contador = 0;

                for( map<string,Imagen>::iterator it = images.begin(); it != images.end(); ++it ){
                    imagePos->insertar(it->second.getX(), it->second.getY(), &(it->second)); //Inserto las imágenes en la malla
                    if(contador==colores.size())
                        contador=0; //Reseteo del contador
                    UTM utm(it->second.getX(),it->second.getY());
                    img.pintarPixel(r, utm, colores[contador++]); //Pinto todas las imágenes de tonos amarillos-naranja-rojos
                }
            }

            { //Pintar de colores las Imagenes de las Etiquetas más populares
                vector<RGBColor> colores;                   //Paleta de colores https://www.color-hex.com/color-palette/74932
                colores.push_back(RGBColor(0,85,130));
                colores.push_back(RGBColor(0,134,173));
                colores.push_back(RGBColor(0,194,199));
                colores.push_back(RGBColor(151,235,219));
                colores.push_back(RGBColor(218,248,227));

                char contador = 0;

                Imagen* masPop = nullptr;
                unsigned likes=0;

                list<Etiqueta*> masPopulares = getMasLikes(); //Por defecto toma las 5 más populares
                for(Etiqueta* eti : masPopulares){
                    if(eti){
                        list<Imagen*> imgsPop = eti->getImages();
                        if(contador == colores.size())
                            contador = 0;
                        for(Imagen* imgPop : imgsPop){
                            if(imgPop){
                                UTM utm(imgPop->getX(),imgPop->getY());
                                img.pintarPixel(r, utm, colores[contador], true);   //Pinto el pixel grande
                                if(imgPop->getLikes() > likes){                     //Busco la imagen con más likes
                                    likes = imgPop->getLikes();
                                    masPop = imgPop;
                                }
                            }
                        }
                        contador++; //Cada etiqueta es pintado de un color distinto
                    }
                }

                if(masPop){ //Saco varias elipses de la imagen más popular de la etiqueta más popular
                    RGBColor purpura1(239, 187, 255); //Paleta de colores https://www.color-hex.com/color-palette/1835
                    RGBColor purpura2(216, 150, 255);
                    RGBColor purpura3(190, 41, 236);

                    float   xmin=masPop->getX()-1,  //Coordenadas para generar una elipse alrededor de la imagen
                            ymin=masPop->getY()-4,
                            xmax=masPop->getX()+1,
                            ymax=masPop->getY()+4;

                    Rango circulo(xmin,ymin,xmax,ymax);
                    img.pintarElipse(r, circulo, purpura1); //Pinto la elipse
                    circulo.modificar(2);                 //Amplío el rango de la elipse
                    img.pintarElipse(r, circulo, purpura2); //Pinto la elipse
                    circulo.modificar(4);                 //Amplío el rango de la elipse
                    img.pintarElipse(r, circulo, purpura3); //Pinto la elipse
                }

            }


            try {
                img.guardar("./mallaImagenes.ppm");
            }catch(ErrorEscrituraFichero &e) {
                cout << "[ImageBook::cargarFicheros] Error al escribir fichero que representa las Imagenes de ImageBook" << endl;
            }
        }
    }
    is.close();
}

void ImageBook::cargar(const string &fileImages, const string &fileLabels, const string &fileUsers) {
    if(!images.empty()){
        images.clear();
        if(imagePos)
            delete imagePos;
    }
    if(!labels.empty())
        labels.clear();
    if(!users.empty())
        users.clear();

    cargarFichero(0,fileLabels);
    cargarFichero(1,fileUsers);
    cargarFichero(2,fileImages);
}

Etiqueta* ImageBook::buscarMiEtiqueta(const std::string &etq) {
    for (list<Etiqueta>::iterator it = labels.begin(); it != labels.end(); ++it){
        if(it->getNombre() == etq)
            return it.operator->();
    }
    return nullptr;
}

Usuario* ImageBook::buscarUsuario(const std::string &email) {
    map<string,Usuario>::iterator it = users.find(email);
    if(it == users.end())
        throw runtime_error(string("[ImageBook::buscarUsuario] No se ha encontrado el usuario " + email + " en el ImageBook"));
    return &(it->second);
}

vector<Usuario*> ImageBook::buscarUsuarioEtiq(const std::string &etiqueta) {
    vector<Usuario*> aux;
    for (map<string,Usuario>::iterator it = users.begin(); it != users.end() ; ++it)
        if(!(it->second.buscarEtiq(etiqueta).empty()))
            aux.push_back(&(it->second));
    return aux;
}

vector<Usuario*> ImageBook::getMasActivos() {
    vector<Usuario*> aux;
    unsigned maxImgUsr = 0;

    for (map<string,Usuario>::iterator it = users.begin(); it != users.end() ; ++it){
        if(it->second.getNumImages() > maxImgUsr){
            aux.clear();
            aux.push_back(&(it->second));
            maxImgUsr = it->second.getNumImages();
        }else if(it->second.getNumImages() == maxImgUsr){
            aux.push_back(&(it->second));
        }
    }
    return aux;
}

list<Etiqueta *> ImageBook::getMasLikes(unsigned int cant) {

    list<Etiqueta*> likes;
    for (unsigned int i = 0; i < cant; ++i)
        likes.push_back(nullptr);

    for (list<Etiqueta>::iterator itLbls = labels.begin(); itLbls != labels.end(); ++itLbls){

        bool esta = false;
        for(Etiqueta* e : likes) //Para evitar duplicados comprobamos antes si esta o no
            if(e)
                if(e->getNombre() == itLbls->getNombre())
                    esta = true;

        if(!esta){
            for (list<Etiqueta*>::iterator itLks = likes.begin(); itLks != likes.end(); ++itLks){
                if(itLks.operator*()){ //Si la Etiqueta existe
                    if(itLks.operator*()->getTotalLikes() < itLbls.operator*().getTotalLikes()){ //En el vector del top hay una Etiqueta con menos likes
                        likes.insert(itLks, &(itLbls.operator*()));
                        likes.pop_back();
                        break; //No hace falta iterar más, se ha insertado una Etiqueta que tenía más likes
                    }
                }else{
                    likes.push_front(&(itLbls.operator*()));    //Inserto para tomar Etiquetas con likes
                    likes.pop_back();                           //Borro al final para mantener la misma cantidad siempre
                }
            }
        }

    }
    return likes;
}

list<Usuario *> ImageBook::getMasPopulares(const unsigned int cant) {

    list<Usuario*> pplrs;
    for (unsigned int i = 0; i < cant; ++i)
        pplrs.push_back(nullptr);

    for (map<string,Usuario>::iterator itUsrs = users.begin(); itUsrs != users.end(); ++itUsrs){

        for(list<Usuario*>::iterator itPops = pplrs.begin(); itPops != pplrs.end(); ++itPops){
            if(itPops.operator*()){ //Si el Usuario (puntero) existe
                if(itUsrs->second.getPopularidad() > itPops.operator*()->getPopularidad()){
                    pplrs.insert(itPops, &(itUsrs->second));    //Añado en la posición anterior el siguiente más popular
                    pplrs.pop_back();                           //A continuación quito el último para que no se desborde la cantidad
                    break;
                }
            }else{
                pplrs.push_front(&(itUsrs->second));
                pplrs.pop_back();
            }
        }

    }
    return pplrs;
}

list<Imagen *> ImageBook::buscarImagEtiq(const string &nombreEti) { ///TODO: nuevo
    list<Imagen*> aux;
    for (list<Etiqueta>::iterator it = labels.begin(); it != labels.end() ; ++it)
        if(it->getNombre() == nombreEti){
            aux = it->getImages();
            if(aux.empty())
                throw runtime_error(string("[ImageBook::buscarImagEtiq] La etiqueta "+ nombreEti + " no se encuentra en ninguna Imagen."));
        }
    return aux;
}

Etiqueta *ImageBook::buscarEtiqueta(const string &nombreEti) {
    Etiqueta* aux = nullptr;
    for (list<Etiqueta>::iterator it = labels.begin(); it != labels.end() ; ++it) {
        if(it->getNombre() == nombreEti){
            aux = it.operator->();
            break;
        }
    }
    return aux;
}

vector<Imagen*> ImageBook::buscarImagLugar(const Rango &r){
    if(imagePos)
        return imagePos->buscarRango(r);
    return vector<Imagen*>();
}

vector<Imagen*> ImageBook::buscarImagEtiLugar(const string &nombre,const Rango &r){
    vector<Imagen*> aux;
    if(imagePos){
        vector<Imagen*> imgsRango = imagePos->buscarRango(r);
        for(Imagen* img : imgsRango)
            if(img != nullptr)   //Que exista el puntero a la Imagen
                if(img->getEtiqueta(nombre))  //Que exista el puntero a la etiqueta
                    aux.push_back(img);
    }
    return aux;
}

vector<Usuario*> ImageBook::buscarUsuarLugar(const Rango &r) {
    vector<Usuario*> aux;
    if(imagePos){
        try{
            Rango g (imagePos->getRangoMalla().interseccion(r)); //Buscamos dentro de la intersección con la malla imagePos
            for(auto it = users.begin(); it != users.end(); ++it)
                if(!(it->second.imagenEnZona(g).empty())) //Si no está vacío es porque el Usuario contiene imágenes en la zona
                    aux.push_back(&(it->second));
        }catch(exception &err){
            cout << err.what() << endl;
        }
    }
    return aux;
}

Etiqueta* ImageBook::buscaEtiquetaRepetida(const Rango &r){
    if(imagePos == nullptr)
        return nullptr;

    ///@brief Clase auxiliar para buscar la Etiqueta más repetida
    class EtiRepe{
    public:
        Etiqueta* etiAux;
        unsigned ocurrencias;
        EtiRepe() : etiAux(nullptr), ocurrencias(1){};
        EtiRepe(Etiqueta* &etiAux) : etiAux(etiAux), ocurrencias(1){}
        ~EtiRepe() = default;
    };

    ///Mapa auxiliar para identificar por el nombre de las etiquetas y guarda su puntero y ocurrencias en el rango
    map<string,EtiRepe> mapAux;

    vector<Imagen*> imgsRango = imagePos->buscarRango(r);
    if(imgsRango.empty())
        return nullptr;

    for(Imagen* img : imgsRango){
        if(img){
            vector<string> etiquetas = img->getEtiquetas();
            for (int i = 0; i < etiquetas.size(); ++i) {
                Etiqueta* aux = img->getEtiqueta(etiquetas[i]);
                if(aux && mapAux.find(etiquetas[i])==mapAux.end())  //Si encuentra la etiqueta en la Imagen y no está en el mapa se añade
                    mapAux.emplace(etiquetas[i], EtiRepe(aux));
                else                                                //Si está aumenta sus ocurrencias
                    mapAux[etiquetas[i]].ocurrencias++;
            }
        }
    }

    EtiRepe max;
    for(auto it = mapAux.begin(); it != mapAux.end(); ++it)
        if(it->second.ocurrencias > max.ocurrencias){ //Búsqueda de la etiqueta con más ocurrencias
            max.etiAux = it->second.etiAux;
            max.ocurrencias = it->second.ocurrencias;
        }

    return max.etiAux;
}


bool ImageBook::insertarImagen(const string &id, Imagen &img) {
    if(images.empty())
        throw runtime_error(string("[ImageBook::insertarImagen] No se pueden buscar imagenes actualmente debido a un fallo del contenedor de imagenes."));
    if(images.find(id) == images.end()){
        images.insert(std::pair<string,Imagen>(id,img));
        return true;
    }else
        throw runtime_error(string("[ImageBook::insertarImagen] Se ha intentado insertar una imagen con clave ya insertada."));
}

Imagen* ImageBook::buscarImagen(const string &id) {
    if(images.empty())
        throw runtime_error(string("[ImageBook::buscarImagen] No se pueden buscar imagenes actualmente debido a un fallo del contenedor de imagenes."));
    Imagen* ptrAux = nullptr;
    if(images.find(id) != images.end())
        ptrAux = &(images.find(id)->second);
    return ptrAux;
}

bool ImageBook::borrarImagen(const string &id) {
    if(images.empty())
        throw runtime_error(string("[ImageBook::borrarImagen] No se pueden borrar si el contenedor esta vacio."));
    if(images.find(id)==images.end())
        throw runtime_error(string("[ImageBook::borrarImagen] No se encuentra la Imagen en el sistema."));
    images.erase(images.find(id));
    return true;
}

void ImageBook::mostrarEstado() {
    cout << "====== Estado actual de su ImageBook ======" << endl;
    cout << "Etiquetas cargadas: " << labels.size() << endl;
    cout << "Usuarios cargados: " << users.size() << endl;
    cout << "Imagenes cargadas: " << images.size() << endl;
    if(imagePos)
        imagePos->datosMalla();
    cout << "===========================================" << endl << endl;

}

vector<Usuario *> ImageBook::buscarUsuarioFechaImagen(const Fecha &f) {
    vector<Usuario*> aux;
    for(pair<const string, Usuario> par : this->users)
        if(par.second.getImagenFecha(f).empty())
            aux.push_back(&(par.second));
    return aux;
}

ImageBook::~ImageBook() {
    if(imagePos)
        delete imagePos;
}

