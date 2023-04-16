#ifndef RECT_HPP
#define RECT_HPP

#include <SDL2/SDL_render.h>
class Rect {
public:
    Rect(int x, int y, int w, int h, int r, int g, int b, int a);
    int x;
    int y;
    int w;
    int h;
    int r;
    int g;
    int b;
    int a;
    bool isTouchingGround;
    SDL_Rect rect;

    void draw(SDL_Renderer* gRenderer);
};

#endif /* RECT_HPP */
