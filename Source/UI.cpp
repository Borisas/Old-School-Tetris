#include "UI.h"


ui::ui(){

    //10blocks = 176
    this->game_ui[0].x = 426;
    this->game_ui[0].y = 0;
    this->game_ui[0].h = 480;
    this->game_ui[0].w = 2;
    this->game_ui[1].x = 465;
    this->game_ui[1].y = 40;
    this->game_ui[1].h = 128;
    this->game_ui[1].w = 128;
    this->game_ui[2].x = 467;
    this->game_ui[2].y = 42;
    this->game_ui[2].w = 124;
    this->game_ui[2].h = 124;
    this->game_ui[3].x = 226;
    this->game_ui[3].y = 0;
    this->game_ui[3].h = 480;
    this->game_ui[3].w = 2;
};
ui::~ui(){};

void ui::draw(){
    core::fillRectangle(this->game_ui[0],1,1,1);
    core::fillRectangle(this->game_ui[1],1,1,1);
    core::fillRectangle(this->game_ui[2],0,0,0);
    core::fillRectangle(this->game_ui[3],1,1,1);

}

