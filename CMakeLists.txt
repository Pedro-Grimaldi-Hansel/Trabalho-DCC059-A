cmake_minimum_required(VERSION 3.14)
project(dcc059-trabalho-1)

file(GLOB SOURCE_FILES "src/*.cpp")
file(COPY arquivoDeEntrada.txt DESTINATION ${CMAKE_BINARY_DIR})
include_directories(src)
include_directories(instancia Cobertura de Vertices)
file(COPY "instancia Cobertura de Vertices" DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(src)
add_subdirectory("instancia Cobertura de Vertices")
add_executable(main main.cpp ${SOURCE_FILES})