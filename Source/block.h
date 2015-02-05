#ifndef BLOCK_H
#define BLOCK_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_opengl.h"
#include <vector>
#include <vector>
#include <iostream>
#include "core.h"
#include <fstream>
#include <stdlib.h>
#include <time.h>
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
        void update();
        void loadBlockSetup(const char* file);
        void newBlock(int id);

    protected:
    private:
        GLuint texture;
        box startPos;
        box position;
        int speed;
        int tickA;
        int tickB;
        vector<vector<box> > b_db;
        vector<vector<box> > currentBlocks;
};

#endif // BLOCK_H
