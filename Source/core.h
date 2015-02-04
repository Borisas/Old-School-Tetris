#ifndef CORE_H
#define CORE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_opengl.h"
#include "structures.h"
#include <iostream>
using namespace std;



namespace core{
    GLuint loadImg(const char* file);
    void draw(GLuint texture, box position);

}

#endif
;
