#!/bin/bash

cd src/

echo "compilation..."
g++ -O2 main.cpp commands.cpp calculator.cpp utils.cpp -o calc
echo "done!"

echo "Installation..."
sudo mv calc /bin*
echo "done!"

echo "Thanks you!"

calc
