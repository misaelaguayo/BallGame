#ifndef BALL_HPP
#define BALL_HPP

#include <SDL2/SDL_render.h>
class Ball {
public:
    Ball(int x, int y, int h, int radius, int r, int g, int b, int a);
    int x;
    int y;
    int h;
    int radius;
    int r;
    int g;
    int b;
    int a;

    void update();
    void draw(SDL_Renderer* gRenderer);
    void handleInput();
};

#endif /* BALL_HPP */
