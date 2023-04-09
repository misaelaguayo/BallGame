#!/bin/bash

# Compile game.cpp
g++ -c game.cpp

# Link game.o and create executable
g++ game.o -o game -lSDL2main -lSDL2
