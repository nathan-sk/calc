# Calc

![Calc](https://github.com/nathan-sk/calc/blob/main/screenshot.png)

A simple calculator program for the terminal, written in C++.

## Installation

### 1. download the binaries :

[Download releases](https://github.com/nathan-sk/calc/releases/)

### 2. or install it manually :

Enter the `src/` directory

`cd src/`

#### 1. run the `install.sh` file

`chmod u+x install.sh`

`./install.sh`

#### 2. or compile the project yourself

compile the program by running the following command:

`g++ -O2 main.cpp commands.cpp calculator.cpp utils.cpp functions.cpp -o calc`

move the file to the \bin directory:

`sudo mv calc /usr/local/bin`


and run the program:

`calc`

## Features

What works:
* Addition, subtraction, division, and multiplication operators
* Modulo operator
* operator priorities
* Nested parentheses
* functions : pi(), sqrt(), abs(), sin(), cos(), tan(), floor(), ceil(), and round()
* Exponents (powers)
* Basic commands: `clear`, `exit` or `quit`, and `help`

What is missing:
* Numbers larger than `double`

## To-do

### v1.0

| Feature | Progress |
| :---- | :---- |
| 1. Adding functions | 100% |
| 2. Windows availability | 100% |
| 3. Creating releases | 100% |
| 4. Using C++ classes | 80% |

## Get involved

Exponentiation does not work when chained (stacked).
Any help is [welcome](https://github.com/nathan-sk/calc/issues)!
