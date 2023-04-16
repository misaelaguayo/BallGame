#!/bin/bash
# Build script for the game
g++ game.cpp ball/ball.cpp rect/rect.cpp -o build/game -lSDL2 -lSDL2_gfx
