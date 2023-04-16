#include "rect.hpp"

Rect::Rect(int x, int y, int w, int h, int r, int g, int b, int a){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    this->isTouchingGround = true;
    this->rect = {x, y, w, h};
}

void Rect::draw(SDL_Renderer* gRenderer){
    SDL_SetRenderDrawColor(gRenderer, this->r, this->g, this->b, this->a);
    SDL_RenderFillRect(gRenderer, &this->rect);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gRenderer, &this->rect);
};
