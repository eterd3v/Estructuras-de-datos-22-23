cmake_minimum_required(VERSION 3.23)
project(PR6)

set(CMAKE_CXX_STANDARD 17)

add_executable(PR6 main.cpp
        Etiqueta.h Etiqueta.cpp
        Imagen.h Imagen.cpp
        Usuario.h Usuario.cpp
        ImageBook.h ImageBook.cpp
        fecha.h fecha.cpp
        UTM.h UTM.cpp
        MallaRegular.cpp MallaRegular.h
        Rango.cpp Rango.h
        img.h img.cpp)