cmake_minimum_required(VERSION 4.0)
project(test15)

set(CMAKE_CXX_STANDARD 20)

add_executable(test15 main.cpp
        Bibliotecas/funciones.cpp
        Bibliotecas/funciones.h
        Bibliotecas/Facultad.h
        Bibliotecas/Alumno.h)
