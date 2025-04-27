cmake_minimum_required(VERSION 3.23)
project(PR5)

set(CMAKE_CXX_STANDARD 14)

add_executable(PR5 main.cpp
        THashImagen.cpp THashImagen.h
        Etiqueta.h Etiqueta.cpp
        Imagen.cpp Imagen.h
        Usuario.h Usuario.cpp
        ImageBook.cpp ImageBook.cpp
        fecha.h fecha.cpp )
