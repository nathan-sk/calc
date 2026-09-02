#!/bin/bash

cd src/
g++ main.cpp commands.cpp calculator.cpp utils.cpp -o calc
sudo mv calc /bin
