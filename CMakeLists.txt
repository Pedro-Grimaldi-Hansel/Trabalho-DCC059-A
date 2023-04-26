cmake_minimum_required(VERSION 3.14)
project(dcc059-trabalho-1)

file(GLOB SOURCE_FILES "src/*.cpp")
list(APPEND SOURCE_FILES "arquivoDeEntrada.txt" "arquivoDeSaida.txt")
include_directories(src)

add_subdirectory(src)
add_executable(main main.cpp ${SOURCE_FILES})