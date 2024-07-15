#!/bin/bash

# Build the inscount tool
mkdir -p build
cd build
cmake ..
make

# Run the busy loop program with the inscount tool
../pin/pin -t inscount -- ../busy_loop

# Check the output
if [ -f inscount.out ]; then
    echo "inscount.out generated successfully."
    cat inscount.out
else
    echo "inscount.out not found. Test failed."
    exit 1
fi

# Clean up
cd ..
rm -rf build