#include "block.h"

#define PI 3.14159265

block::block(const char* img, const char* fallimg)
{
    this->texture = core::loadImg(img);
    this->fall_texture = core::loadImg(fallimg);
    this->speed = 10;
    this->tickA = 0;
    this->tickB = 0;
    this->tickC = 0;
    this->tickD = 0;
    this->tickE = 0;
    this->tickF = 0;
    this->startPos.x = 310;
    this->startPos.y = 0;
    this->holding = false;
    this->loadBlockSetup("blocks.txt");
    srand (time(NULL));
    this->c_drop = true;
    //ctor
}

block::~block()
{
    //dtor
}

void block::draw(){
    for(unsigned int i = 0; i < this->currentBlocks.size(); i++){
        for(unsigned int j = 0; j < this->currentBlocks[i].size(); j++){
            if(i == this->current)
                core::draw(this->fall_texture, this->currentBlocks[i][j]);
            else
                core::draw(this->texture, this->currentBlocks[i][j]);
        }
    }
    if(this->holding){
        box now = core::getBox(this->held);
        int sx = now.x;
        int sy = now.y;
        for(unsigned int i = 0; i < this->held.size(); i ++){
            this->temporary.push_back(this->held[i]);
        }
        for(unsigned int i = 0; i < this->temporary.size(); i++){
            this->temporary[i].x = (this->held[i].x - sx) + 517;
            this->temporary[i].y = this->held[i].y - sy + 82;
        }
        for(unsigned int i = 0; i < this->temporary.size(); i++)
            core::draw(this->fall_texture, this->temporary[i]);
        this->temporary.clear();
    }
}
void block::set_pos(double x, double y, double w, double h){
    this->position.x = x;
    this->position.y = y;
    this->position.h = h;
    this->position.w = w;
}
void block::drop(){
    if(core::ticker(&tickA, speed)){
        for(unsigned int i = 0; i < this->currentBlocks.size(); i++){
            if(this->moving[i]){
                for(unsigned int j = 0; j < this->currentBlocks[i].size(); j++){
                    this->currentBlocks[i][j].y +=16;
                    if(this->currentBlocks[i][j].y+this->currentBlocks[i][j].h >= 465)
                        this->moving[i] = false;
                }
            }
        }
    }
}
void block::set_speed(int speed){
    this->speed = speed;
}
void block::update(){
    if(this->c_drop){
        int random = rand() % (this->b_db.size()-1);
        this->newBlock(random);
        this->c_drop = false;
    }
    this->draw();
    this->collision();
    this->drop();
    this->checkClear();
    if(tickB < 4+this->speed/2)
        tickB++;
    if(tickE < 20)
        tickE++;
    if(!this->moving[this->current])
        if(core::ticker(&tickF, 60))
            this->c_drop = true;
}
void block::loadBlockSetup(const char* file){
    ifstream b_file(file);
    int temp;

    box tempBox;
    if(!b_file.is_open())
        cout << "failed to open file " << file << endl;
    else{
        while(!b_file.eof()){
        vector<box> tempBlock;
            for(int i=0; i < 4; i++){
                for(int j=0; j < 4; j++){
                    b_file >> temp;
                    if(temp == 1){
                        tempBox.x = this->startPos.x + 16 * (j+1);
                        tempBox.y = this->startPos.y + 16 * (i+1);
                        tempBox.w = 16;
                        tempBox.h = 16;
                        tempBlock.push_back(tempBox);
                    }
                }

            }
            this->b_db.push_back(tempBlock);
        }
    }
    b_file.close();
}
void block::newBlock(int id){
    this->currentBlocks.push_back(this->b_db[id]);
    this->moving.push_back(true);
    this->current = this->currentBlocks.size()-1;
    this->c_hold ++;
    this->rotation = 0;
}
void block::move(int amount){
    if(core::ticker(&tickC, (4+this->speed/2))){
        this->tickF = 0;
        int checker = 0;
        for(unsigned int i = 0; i < this->currentBlocks[this->current].size(); i++){
            int cx = this->currentBlocks[this->current][i].x;
            int cw = this->currentBlocks[this->current][i].w;
            if(amount > 0){
                if(cx + cw + amount > 426)
                    checker++;
                for(unsigned int i = 0; i < this->currentBlocks.size()-1; i++){
                    for(unsigned int j = 0; j <  this->currentBlocks[i].size(); j++){
                        for(unsigned int k = 0; k < this->currentBlocks[this->current].size(); k++){
                            if(core::collisionR(this->currentBlocks[this->current][k], this->currentBlocks[i][j]))
                                checker++;
                        }
                    }
                }
            }
            if(amount < 0){
                if(cx + amount < 226)
                    checker++;
                for(unsigned int i = 0; i < this->currentBlocks.size()-1; i++){
                    for(unsigned int j = 0; j <  this->currentBlocks[i].size(); j++){
                        for(unsigned int k = 0; k < this->currentBlocks[this->current].size(); k++){
                            if(core::collisionL(this->currentBlocks[this->current][k], this->currentBlocks[i][j]))
                                checker++;
                        }
                    }
                }
            }

        }
        if(checker == 0){
            for(unsigned int i = 0; i < this->currentBlocks[this->current].size(); i++){
                this->currentBlocks[this->current][i].x += amount;
            }
        }
    }
}
void block::hold(){
    if(this->c_hold > 0){
        if(!this->holding){
            for(unsigned int i = 0; i < this->currentBlocks[this->current].size(); i ++){
                this->held.push_back(this->currentBlocks[this->current][i]);
            }
            this->currentBlocks.pop_back();
            this->moving.pop_back();
            this->holding = true;
            this->tickB = 250;
            this->c_hold = -1;
            this->c_drop = true;
        }
        else{
            for(unsigned int i = 0; i < this->currentBlocks[this->current].size(); i ++){
                this->temporary.push_back(this->currentBlocks[this->current][i]);
            }
            this->currentBlocks.pop_back();
            int sy = this->held[0].y;
            int sx = this->held[0].x;
            for(unsigned int i = 0; i < this->held.size(); i ++){
                this->held[i].y -= sy;
                this->held[i].x -= sx;
                this->held[i].x += this->startPos.x;
            }
            this->currentBlocks.push_back(this->held);
            this->held.clear();
            for(unsigned int i = 0; i < this->temporary.size(); i++){
                this->held.push_back(this->temporary[i]);
            }

            temporary.clear();
            this->c_hold = 0;
        }

    }
}
void block::rotate(){
    if(core::ticker(&tickE, 20)){
        this->tickF = 0;
        int temp;
        box now = core::getBox(this->currentBlocks[this->current]);
        int cx = now.x;
        int cy = now.y;
        for(unsigned int i = 0; i < this->currentBlocks[this->current].size(); i++){
            this->currentBlocks[this->current][i].x -= cx;
            this->currentBlocks[this->current][i].y -= cy;
        }
        for(unsigned int i = 0; i < this->currentBlocks[this->current].size(); i++){
            temp = this->currentBlocks[this->current][i].x;
            this->currentBlocks[this->current][i].x = -1*(this->currentBlocks[this->current][i].y);
            this->currentBlocks[this->current][i].y = temp;
        }
        now = core::getBox(this->currentBlocks[this->current]);
        int cxa = now.x;
        int cya = now.y;
        for(unsigned int i = 0; i < this->currentBlocks[this->current].size(); i++){
            this->currentBlocks[this->current][i].x -= cxa -cx;
            this->currentBlocks[this->current][i].y -= cya -cy;
        }


    }
}
void block::collision(){
    for(unsigned int i = 0; i < this->currentBlocks.size()-1; i++){
        for(unsigned int j = 0; j <  this->currentBlocks[i].size(); j++){
            for(unsigned int k = 0; k < this->currentBlocks[this->current].size(); k++){
                if(core::collision(this->currentBlocks[this->current][k], this->currentBlocks[i][j]))
                    this->moving[this->current] = false;
                /*if(!(core::collision(this->currentBlocks[this->current][k], this->currentBlocks[i][j])) &&
                    this->currentBlocks[this->current][k].y+this->currentBlocks[this->current][k].h >= 465)
                    this->moving[this->current] = true;*/
            }
        }
    }
}
void block::stopMoving(){
    this->moving[this->current] = false;
    if(core::ticker(&tickF, 50)){
        this->c_drop = true;
    }
}
void block::changePos(int x, int y, int id){
    for(unsigned int i = 0; i < this->currentBlocks[id].size(); i++){
        this->currentBlocks[id][i].x += x;
        this->currentBlocks[id][i].y += y;
    }
}
void block::checkClear(){
    for(int k = 0; k < 30; k++){
        int blockCount = 0;
        for(unsigned int i = 0; i < this->currentBlocks.size()-1; i++){
            for(unsigned int j = 0; j < this->currentBlocks[i].size(); j ++){
                if(this->currentBlocks[i][j].y == k*16)
                    blockCount ++;
            }
        }
        if(blockCount >= 12)
            this->clear(k);
    }
}
void block::clear(int line){
    for(unsigned int i = 0; i < this->currentBlocks.size()-1; i++){
        for(unsigned int j = 0; j < this->currentBlocks[i].size(); j ++){
            if(this->currentBlocks[i][j].y == line*16){
                this->currentBlocks[i].erase(this->currentBlocks[i].begin() + j);
                j--;
            }
            if(this->currentBlocks[i][j].y < line*16)
                this->currentBlocks[i][j].y +=16;
        }
    }
}
