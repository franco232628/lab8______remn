cmake_minimum_required(VERSION 4.0)
project(lab_8_2024_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_8_2024_2 main.cpp
        Biblioteca/AuxiliaryFunctions.cpp
        Biblioteca/AuxiliaryFunctions.hpp
        Biblioteca/Utils.hpp
        Biblioteca/Distrito.hpp
        Biblioteca/Plato.hpp
        Biblioteca/PlatoPedido.hpp
        Biblioteca/Cliente.hpp)
