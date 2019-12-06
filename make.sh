#!/bin/bash

# Make mp1
chmod +x matrix.c
gcc matrix.c -o mp1 -lpthread
echo "Made mp1"

echo "ONE THREAD-------------------------"
# One thread
./mp1 1 128
./mp1 1 256
./mp1 1 512
./mp1 1 1024

echo "TWO THREAD-------------------------"
# Two threads
./mp1 2 128
./mp1 2 256
./mp1 2 512
./mp1 2 1024

echo "FOUR THREAD-------------------------"
# Four threads
./mp1 4 128
./mp1 4 256
./mp1 4 512
./mp1 4 1024

echo "EIGHT THREAD-------------------------"
# Eight threads
./mp1 8 128
./mp1 8 256
./mp1 8 512
./mp1 8 1024

echo "SIXTEEN THREAD-------------------------"
# Sixteen threads
./mp1 16 128
./mp1 16 256
./mp1 16 512
./mp1 16 1024

echo "Done"
