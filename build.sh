#!/bin/bash
# Build script for the game
g++ game.cpp ball/ball.cpp -o build/game -lSDL2 -lSDL2_gfx
