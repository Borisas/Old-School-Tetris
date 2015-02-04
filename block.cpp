#include "block.h"

block::block(const char* img)
{
    this->texture = core::loadImg(img);
    //ctor
}

block::~block()
{
    //dtor
}

void block::draw(){
    core::draw(this->texture, this->position);
}
void block::set_pos(double x, double y, double w, double h){
    this->position.x = x;
    this->position.y = y;
    this->position.h = h;
    this->position.w = w;
}
void block::drop(){
    int tick = 0;
    if(tick >= speed){
        this->position.y += 16;
    }

}
void block::set_speed(int speed){
    this->speed = speed;
}
