#ifndef CORE_H
#define CORE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_opengl.h"
#include "structures.h"
#include <iostream>
#include <vector>
using namespace std;



namespace core{
    GLuint loadImg(const char* file);
    void draw(GLuint texture, box position);
    bool ticker(int* ticker, int sleep);
    bool controls_ticker(int* ticker, int sleep);
    void fillRectangle(box draw, double R, double G, double B);
    //void resetY(vector<box> block);
}

#endif
;
