#ifndef CORE_H
#define CORE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_opengl.h"
#include "structures.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;



namespace core{
    GLuint loadImg(const char* file);
    string toString(int number);
    void draw(GLuint texture, box position);
    bool ticker(int* ticker, int sleep);
    bool controls_ticker(int* ticker, int sleep);
    void fillRectangle(box draw, double R, double G, double B);
    box getBox(vector<box> block);
    bool collision(box a, box b);
    bool collisionR(box a, box b);
    bool collisionL(box a, box b);
    void renderText(int x, int y, string text, int fontSize);
    GLuint SDLSurfaceToTexture(SDL_Surface* surface);
}

#endif
;
