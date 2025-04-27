cmake_minimum_required(VERSION 3.23)
project(PR4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PR4
        fecha.cpp
        fecha.h
        Imagen.cpp
        Imagen.h
        main.cpp
        Etiqueta.cpp Etiqueta.h ImageBook.cpp ImageBook.h Usuario.cpp Usuario.h)
