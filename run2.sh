#!/bin/bash

inp="$1"
cpp_file="parse1.cpp"
input_file="${inp}.satoutput"
input_file2="${inp}.graph"
output_file="${inp}.mapping"
./cp1 "$input_file" "$input_file2"> "$output_file"