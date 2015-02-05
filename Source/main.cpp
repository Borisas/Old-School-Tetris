#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_opengl.h"
#include "core.h"
#include "block.h"
#include "UI.h"
#include <iostream>
using namespace std;


int main( int argc, char* args[] )
{
    //INITIALIZATION******
    bool gameLoop = true;
	SDL_GLContext context;

    if(SDL_Init( SDL_INIT_EVERYTHING ) == -1){
        cout << "SDL_Error:%s\n" <<SDL_GetError() << endl;
		gameLoop = false;
	}
	SDL_Window* window = NULL;
	window = SDL_CreateWindow("TetrisVgtu", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        gameLoop=false;
        printf("SDL_Error:%s\n",SDL_GetError());
    }
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    context = SDL_GL_CreateContext(window);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glOrtho(0,640,480,0,-1,1);

    SDL_Event occur;

    Uint32 lastTick;
    Uint32 currentTick;
    const int FPS = 60;
	double period = 1000 / (double)FPS;
    int milliPeriod = (int)period;
    int sleep;
    //********************
    block b("assets/block.bmp");
    b.set_pos(10, 10, 16,16);
    b.set_speed(20);
    b.newBlock(1);

    ui u;

    while(gameLoop){
        lastTick = SDL_GetTicks();
        while( SDL_PollEvent(&occur)){
            if(occur.type == SDL_QUIT)
                    gameLoop = false;
        }
        const Uint8* keystates = SDL_GetKeyboardState( NULL );

        if(keystates[SDL_SCANCODE_A]){
            b.move(-16);
        }
        if(keystates[SDL_SCANCODE_D]){
            b.move(16);
        }
        if(keystates[SDL_SCANCODE_SPACE]){
            b.hold();
        }

        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);

        u.draw();
        b.update();


        //FPS CONTROL---
        currentTick = SDL_GetTicks();
        sleep = milliPeriod - (currentTick - lastTick);
        if(sleep < 0) { sleep = 0; }
        SDL_Delay(sleep);
        //--------------
		SDL_GL_SwapWindow(window);
    }

    glDisable(GL_BLEND);
	SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
};
