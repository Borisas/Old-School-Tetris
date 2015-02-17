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
#include <cmath>
using namespace std;


class block
{
    public:
        block(const char* img, const char* fallimg);
        virtual ~block();
        void draw();
        void set_pos(double x, double y, double w, double h);
        void set_speed(int speed);
        void drop();
        void forceDrop();
        void update(int *score);
        void loadBlockSetup(const char* file);
        void newBlock(int id);
        void move(int amount);
        void rotate();
        void hold();
        void collision();
        void stopMoving();
        void changePos(int x, int y, int id);
        int checkClear();
        void clear(int line);
        void clean();
        bool loseCheck();
        void newGame();
        void modPos(int id, int x, int y);
    protected:
    private:
        GLuint texture;
        GLuint fall_texture;
        box startPos;
        box position;
        unsigned int current;
        int speed;
        int rotation;
        int tickA;
        int tickB;
        int tickC;
        int tickD;
        int tickE;
        int tickF;
        bool holding;
        int c_hold;
        bool c_drop;
        unsigned int next;
        vector<bool> moving;
        vector<box> held;
        vector<box> temporary;
        vector<vector<box> > b_db;
        vector<vector<box> > currentBlocks;
};

#endif // BLOCK_H
