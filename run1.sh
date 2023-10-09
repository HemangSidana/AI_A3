#!/bin/bash

inp="$1"
cpp_file="cnf3.cpp"
input_file="${inp}.graph"
output_file="${inp}.satinput"
./compiled_p1 "$input_file" > "$output_file"