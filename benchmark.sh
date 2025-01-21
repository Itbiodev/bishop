#!/bin/bash

INPUT_SIZES=(10 100 1000 10000 100000)
OUTPUT_FILE="benchmark_results.csv"
BUILD_DIR="./build"
SOURCE_DIR="."

mkdir -p "$BUILD_DIR"

SOURCE_FILES=($(find "$SOURCE_DIR" -maxdepth 1 -name "*.c"))

for source in "${SOURCE_FILES[@]}"; do
    program_name=$(basename "${source%.c}")
    echo "Building $program_name..."
    gcc -O3 "$source" -o "$BUILD_DIR/$program_name"
done

echo "program,input_size,mean,stddev" > "$OUTPUT_FILE"

for source in "${SOURCE_FILES[@]}"; do
    program=$(basename "${source%.c}")
    program_path="$BUILD_DIR/$program"
    for size in "${INPUT_SIZES[@]}"; do
        hyperfine --warmup 10 \
	          --shell none \
	          --export-json temp.json \
	          "$program_path $size" \
                  # --runs 100 \
        mean=$(jq '.results[0].mean' temp.json)
        stddev=$(jq '.results[0].stddev' temp.json)
        echo "$program,$size,$mean,$stddev" >> "$OUTPUT_FILE"
    done
done

rm temp.json

echo "Benchmarking complete. Results saved to benchmark_results.csv"
