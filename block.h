#ifndef BLOCK_H
#define BLOCK_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_opengl.h"
#include <vector>
#include <iostream>
#include "../core.h"
using namespace std;


class block
{
    public:
        block(const char* img);
        virtual ~block();
        void draw();
        void set_pos(double x, double y, double w, double h);
        void set_speed(int speed);
        void drop();


    protected:
    private:
        GLuint texture;
        box position;
        int speed;
};

#endif // BLOCK_H
