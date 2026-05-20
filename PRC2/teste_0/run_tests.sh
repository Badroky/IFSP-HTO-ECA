#!/bin/bash

# Move to script's directory so it works regardless of where it's called from
cd "$(dirname "$0")"

echo "Compiling test_ordenar.c..."
gcc test_ordenar.c -o test_ordenar
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Running tests..."
./test_ordenar
if [ $? -ne 0 ]; then
    echo "Tests failed!"
    exit 1
fi

echo "All tests completed successfully."
exit 0
