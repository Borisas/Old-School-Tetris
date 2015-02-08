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

};
ui::~ui(){};

void ui::draw(int score){
    for(unsigned int i = 0; i < 8; i++){
        core::fillRectangle(this->game_ui[i], 1, 1, 1);
    }
    core::renderText(68,20,"HOLDING", 20);
    core::renderText(78,260, "SCORE", 20);
    core::renderText(506,20, "NEXT", 20);
    core::renderText(4, 284, core::toString(score), 22);


}

