# Calc

![Calc](https://github.com/nathan-sk/calc/blob/main/screenshot.png)

A simple calculator program for the terminal, written in C++.

## Installation

Run the `install.sh` file or compile the project yourself:

Enter the `src/` directory:

`cd src/`

compile the program by running the following command:

`g++ -O2 main.cpp commands.cpp calculator.cpp utils.cpp -o calc`

move the file to the \bin directory:

`sudo mv calc /usr/local/bin`

and run the program:

`calc`

## Features

What works:
* Addition, subtraction, division, and multiplication operators
* Modulo operator
* Operator precedence
* Nested parentheses
* `pi()` and `sqrt()` functions
* Exponents (powers)
* Basic commands: `clear`, `exit` or `quit`, `help`, and `debug`

What is missing:
* Numbers larger than `double`
* A wide range of functions
* Availability on platforms other than Linux

## To-do

| Feature | Progress |
| :---- | :---- |
| 1. Adding functions | 20% |
| 2. Windows availability | 40% |
| 3. Creating releases | 0% |
| 4. Using C++ classes | 10% |

## Get involved

Exponentiation does not work when chained (stacked).
Any help is [welcome](https://github.com/nathan-sk/calc/issues)!
