#!/bin/bash

# Compilar o código C++
cd build
make

# Pasta de entrada
input_dir="instancias"

# Arquivo de saída
output_file="arquivoDeSaida.txt"

# Executar o programa para cada arquivo de entrada
for input_file in $input_dir/*
do
    echo $input_file
    ./main $input_file $output_file 0 0 1
done