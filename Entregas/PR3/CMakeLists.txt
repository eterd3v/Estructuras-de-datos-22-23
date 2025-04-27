cmake_minimum_required(VERSION 3.23)
project(PR3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PR3
        fecha.cpp
        fecha.h
        Imagen.cpp
        Imagen.h
        main.cpp
        VDinamico.cpp
        VDinamico.h ListaDEnlazada.cpp ListaDEnlazada.h Nodo.cpp Nodo.h Etiqueta.cpp Etiqueta.h Iterador.cpp Iterador.h ImageBook.cpp ImageBook.h AVL.cpp AVL.h NodoAVL.cpp NodoAVL.h Usuario.cpp Usuario.h)
