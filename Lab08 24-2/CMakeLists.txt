cmake_minimum_required(VERSION 4.0)
project(test16)

set(CMAKE_CXX_STANDARD 20)

add_executable(test16 main.cpp
        Bibliotecas/funciones.cpp
        Bibliotecas/funciones.h
        Bibliotecas/Distrito.h
        Bibliotecas/Plato.h
        Bibliotecas/PlatoPedido.h
        Bibliotecas/Cliente.h)
