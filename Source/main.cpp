#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_opengl.h"
#include "core.h"
#include "block.h"
#include "UI.h"
#include "score.h"
#include <iostream>
#include <string>
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
	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        gameLoop=false;
        printf("SDL_Error:%s\n",SDL_GetError());
    }
    if(TTF_Init() == -1) {
        cout << "TTF_Init_Error: %s\n" << TTF_GetError() << endl;
        gameLoop = false;
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
    int state = 0;
    int selected = 1;
    int tickA = 0;
    //********************

    block b("assets/block.bmp", "assets/falling.bmp");
    b.set_pos(10, 10, 16,16);
    ui u;
    score s;
    bool load = true;
    int score = 0;
    int difficulty = 0;
    //MENU BOXES
    box menu[3];
    menu[0].x = 40; menu[0].y = 150; menu[0].w = 210; menu[0].h = 33;
    menu[1].x = 40; menu[1].y = 250; menu[1].w = 210; menu[1].h = 33;
    //===

    while(gameLoop){
        tickA++;
        difficulty = s.difficulty(score,difficulty);
        lastTick = SDL_GetTicks();
        b.set_speed(20-difficulty);
        while( SDL_PollEvent(&occur)){
            if(occur.type == SDL_QUIT)
                gameLoop = false;
            for(unsigned int i = 0; i < 3; i++){
                if(core::mouseOver(menu[i], occur))
                    selected = i+1;
                if(core::clickOn_LMB(menu[i], occur)){
                    if(i == 0){
                        //START
                        state = 1;
                        load = true;
                    }
                    if(i == 1){
                        //Exit
                        gameLoop = false;
                    }
                }
            }
        }
        const Uint8* keystates = SDL_GetKeyboardState( NULL );

        if(keystates[SDL_SCANCODE_LEFT] && state == 1){
            b.move(-16);
        }
        if(keystates[SDL_SCANCODE_RIGHT] && state == 1){
            b.move(16);
        }
        if(keystates[SDL_SCANCODE_DOWN]){
            if(state == 1)
                b.set_speed(5);
            if(state == 0){
                if(core::ticker(&tickA, 15)){
                    selected++;
                    if(selected > 2)
                        selected = 1;
                }
            }
        }
        if(keystates[SDL_SCANCODE_UP]){
            if(state == 1){
                b.instaDrop();
            }
        }
        if(keystates[SDL_SCANCODE_UP] && state == 0){
            if(core::ticker(&tickA, 15)){
                selected--;
                if(selected < 1)
                    selected = 2;
            }
        }
        if(keystates[SDL_SCANCODE_RETURN] && state == 0){
            switch(selected){
                case 1:
                    state = 1;
                    load = true;
                    break;
                case 2:
                    gameLoop = false;
                    break;
            }
        }
        if(keystates[SDL_SCANCODE_SPACE] && state == 1){
            b.rotate();
        }
        if(keystates[SDL_SCANCODE_LSHIFT] && state == 1){
            b.hold();
        }
        if(keystates[SDL_SCANCODE_ESCAPE] && state == 1){
            state = 0;
            s.addScore(score);
        }

        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);




        if(state == 1){
            if(load){
                b.newGame();
                score = 0;
                load = false;
            }
            u.drawGame(score,difficulty);
            b.update(&score);
            if(b.loseCheck()){
                state = 0;
                s.addScore(score);
            }
        }
        if(state == 0){
            core::renderText(280,280, "Top 5 scores", 25);
            for(int i = 1; i <= 5; i++)
                core::renderText(290, 290+25*i,core::toString(i) + ". " + core::toString(s.getPlaceScore(i)), 20);
            u.drawMenu(selected);
        }

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
    TTF_Quit();
    s.writeScore();
	return 0;
};
