#!/bin/bash

inp="$1"
cpp_file="cnf_max.cpp"
input_file="${inp}.graph"
output_file="${inp}.mapping"
./cp2 "$input_file" > "$output_file"