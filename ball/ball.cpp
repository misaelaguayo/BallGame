#include "ball.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_render.h>

Ball::Ball(int x, int y, int h, int radius, int r, int g, int b, int a){
    this->x = x;
    this->y = y;
    this->h = h;
    this->radius = radius;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Ball::draw(SDL_Renderer* gRenderer){
    filledCircleRGBA(gRenderer, this->x, this->y, this->radius, this->r, this->g, this->b, this->a);
    // outline with a white circle
    circleRGBA(gRenderer, this->x, this->y, this->radius -1, 255, 255, 255, 255);
};
