#!/bin/bash

inp="$1"
cpp_file="cnf.cpp"
input_file="${inp}.graph"
output_file="${inp}.satinput"
./c1 "$input_file" > "$output_file"
