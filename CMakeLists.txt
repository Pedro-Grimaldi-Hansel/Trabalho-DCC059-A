cmake_minimum_required(VERSION 3.14)
project(dcc059-trabalho-1)

file(GLOB SOURCE_FILES "src/*.cpp")
file(COPY arquivoDeEntrada.txt DESTINATION ${CMAKE_BINARY_DIR})
include_directories(src)
include_directories(instancias)
file(COPY "instancias" DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(src)
add_subdirectory("instancias")
add_executable(main main.cpp ${SOURCE_FILES})