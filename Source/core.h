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
    int collisionComp(box a, box b);
    void renderText(int x, int y, string text, int fontSize);
    void renderText(int x, int y, string text, int fontSize, int R, int G, int B);
    GLuint SDLSurfaceToTexture(SDL_Surface* surface);
    bool clickOn_LMB(box a, SDL_Event e);
    bool mouseOver(box a, SDL_Event e);
}

#endif
;
