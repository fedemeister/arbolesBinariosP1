cmake_minimum_required(VERSION 3.9)
project(arbolesBinarios)

set(CMAKE_CXX_STANDARD 11)

add_executable(arbolesBinarios abin_vec.h abin_celdas.h abin_vec1.h abin_E-S.h operaAbin.cpp)