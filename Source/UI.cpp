#include "UI.h"


ui::ui(){

    //10blocks = 176
    //GAME BORDERS
    //RIGHT
    this->game_ui[0].x = 426;
    this->game_ui[0].y = 0;
    this->game_ui[0].h = 480;
    this->game_ui[0].w = 2;
    //LEFT
    this->game_ui[1].x = 226;
    this->game_ui[1].y = 0;
    this->game_ui[1].h = 480;
    this->game_ui[1].w = 2;
    //=====

    //NEXT BLOCK BOX
    this->game_ui[2].x = 426;
    this->game_ui[2].y = 45;
    this->game_ui[2].h = 2;
    this->game_ui[2].w = 216;
    this->game_ui[3].x = 426;
    this->game_ui[3].y = 175;
    this->game_ui[3].h = 2;
    this->game_ui[3].w = 216;
    //=====

    //HOLD BLOCK BOX
    this->game_ui[4].x = 0;
    this->game_ui[4].y = 45;
    this->game_ui[4].w = 226;
    this->game_ui[4].h = 2;
    this->game_ui[5].x = 0;
    this->game_ui[5].y = 175;
    this->game_ui[5].w = 226;
    this->game_ui[5].h = 2;
    //======

    //SCORE BOX
    this->game_ui[6].x = 0;
    this->game_ui[6].y = 280;
    this->game_ui[6].w = 226;
    this->game_ui[6].h = 2;
    this->game_ui[7].x = 0;
    this->game_ui[7].y = 310;
    this->game_ui[7].w = 227;
    this->game_ui[7].h = 2;
    //======

    //Dificulty box
    this->game_ui[8].x = 0;
    this->game_ui[8].y = 280;
    this->game_ui[8].w = 226;
    this->game_ui[8].h = 2;
    this->game_ui[9].x = 0;
    this->game_ui[9].y = 310;
    this->game_ui[9].w = 227;
    this->game_ui[9].h = 2;
    //===

    this->menu_ui[0].x = 40;
    this->menu_ui[0].y = 0;
    this->menu_ui[0].w = 2;
    this->menu_ui[0].h = 480;
    this->menu_ui[1].x = 240;
    this->menu_ui[1].y = 0;
    this->menu_ui[1].w = 2;
    this->menu_ui[1].h = 480;

    this->menu_ui[2].x = 240;
    this->menu_ui[2].y = 195;
    this->menu_ui[2].w = 400;
    this->menu_ui[2].h = 2;
    this->menu_ui[3].x = 240;
    this->menu_ui[3].y = 250;
    this->menu_ui[3].w = 400;
    this->menu_ui[3].h = 2;

    this->menu_ui[4].x = 270; this->menu_ui[4].y = 250; this->menu_ui[4].w = 2; this->menu_ui[4].h = 230;
    this->menu_ui[5].x = 550; this->menu_ui[5].y = 250; this->menu_ui[5].w = 2; this->menu_ui[5].h = 230;

};
ui::~ui(){};

void ui::drawGame(int score, int difficulty){
    for(unsigned int i = 0; i < 10; i++){
        core::fillRectangle(this->game_ui[i], 1, 1, 1);
    }
    core::renderText(68,20,"HOLDING", 20);
    core::renderText(78,260, "SCORE", 20);
    core::renderText(506,20, "NEXT", 20);
    core::renderText(4, 284, core::toString(score), 22);
    core::renderText(68, 350, "DIFFICULTY", 20);
    core::renderText(68, 380, core::toString(difficulty), 22);
}
void ui::drawMenu(int select){
    for(unsigned int i = 0; i < 6; i ++){
        core::fillRectangle(this->menu_ui[i], 1, 1, 1);
    }
    core::renderText(440, 200, "TETRIS", 50);
    switch(select){
        case 0:
            core::renderText(60, 150, "Play", 30);
            core::renderText(60, 250, "Exit", 30);
            break;
        case 1:
            core::renderText(60, 150, "Play", 30, 0,0,255);
            core::renderText(60, 250, "Exit", 30);
            break;
        case 2:
            core::renderText(60, 150, "Play", 30);
            core::renderText(60, 250, "Exit", 30,0,0,255);
            break;
    }
}

