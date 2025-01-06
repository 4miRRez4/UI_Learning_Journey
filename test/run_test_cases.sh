#!/bin/bash


INPUT_DIR="test/P02-TC/in"
OUTPUT_FILE="output.txt"

> "$OUTPUT_FILE"

for file in "$INPUT_DIR"/*.txt; do
    echo "Processing file: $file" >> "$OUTPUT_FILE"
    ./main.out < "$file" >> "$OUTPUT_FILE"
    echo -e "\n" >> "$OUTPUT_FILE" 
done

echo "All files processed. Results saved to $OUTPUT_FILE."
