cmake_minimum_required(VERSION 4.0)
project(TP_SOL_LAB08_2025_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP_SOL_LAB08_2025_1 main.cpp
        MiBiblioteca/TablaDeInfracciones.h
        MiBiblioteca/Fecha.h
        MiBiblioteca/EmpresasRegistradas.h
        MiBiblioteca/FuncionesAux.h
        MiBiblioteca/FuncionesAux.cpp)
