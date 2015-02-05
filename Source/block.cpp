#include "block.h"

block::block(const char* img)
{
    this->texture = core::loadImg(img);
    this->speed = 10;
    this->tickA = 0;
    this->tickB = 0;
    this->tickC = 0;
    this->tickD = 0;
    this->startPos.x = 310;
    this->startPos.y = 0;
    this->holding = false;
    this->loadBlockSetup("blocks.txt");
    srand (time(NULL));
    //ctor
}

block::~block()
{
    //dtor
}

void block::draw(){
    //core::draw(this->texture, this->position);
    for(int i = 0; i < this->currentBlocks.size(); i++){
        for(int j = 0; j < this->currentBlocks[i].size(); j++){
            core::draw(this->texture, this->currentBlocks[i][j]);
        }
    }
    if(this->holding){
        int sx = this->held[0].x;
        int sy = this->held[0].y;
        for(int i = 0; i < this->held.size(); i ++){
            this->temporary.push_back(this->held[i]);
        }
        for(int i = 0; i < this->temporary.size(); i++){
            this->temporary[i].x = (this->held[i].x - sx) + 517;
            this->temporary[i].y = this->held[i].y - sy + 82;
        }
        for(int i = 0; i < this->temporary.size(); i++)
            core::draw(this->texture, this->temporary[i]);
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
        for(int i = 0; i < this->currentBlocks.size(); i++){
            for(int j = 0; j < this->currentBlocks[i].size(); j++){
                core::draw(this->texture, this->currentBlocks[i][j]);
                this->currentBlocks[i][j].y +=16;
            }
        }
    }

}
void block::set_speed(int speed){
    this->speed = speed;
}
void block::update(){
    this->draw();
    this->drop();
    if(core::ticker(&tickB,250)){
        int random = rand() % (this->b_db.size()-1);
        cout << random;
        this->newBlock(random);

    }

}
void block::loadBlockSetup(const char* file){
    ifstream b_file(file);
    int temp;
    int i =0;
    int j =0;

    box tempBox;
    int blockCount;
    if(!b_file.is_open())
        cout << "failed to open file " << file << endl;
    else{
        while(!b_file.eof()){
        vector<box> tempBlock;
            for(int i=0; i < 4; i++){

                for(int j=0; j < 4; j++){
                    b_file >> temp;
                    if(temp == 1){
                        tempBox.x = this->startPos.x + 16 * (j+1) + j*2;
                        tempBox.y = this->startPos.y + 16 * (i+1) + i*2;
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
    this->current = this->currentBlocks.size()-1;
    this->c_hold ++;
}
void block::move(int amount){
    if(core::ticker(&tickC, (4+this->speed/2))){
        int checker = 0;
        for(int i = 0; i < this->currentBlocks[this->current].size(); i++){
            int cx = this->currentBlocks[this->current][i].x;
            int cw = this->currentBlocks[this->current][i].w;
            if(amount > 0){
                if(cx + cw + amount > 426)
                    checker++;
            }
            if(amount < 0){
                if(cx + amount < 226)
                    checker++;
            }
        }
        if(checker == 0){
            for(int i = 0; i < this->currentBlocks[this->current].size(); i++){
                this->currentBlocks[this->current][i].x += amount;
            }
        }
    }
}
void block::hold(){
    if(this->c_hold > 0){
        if(!this->holding){
            for(int i = 0; i < this->currentBlocks[this->current].size(); i ++){
                this->held.push_back(this->currentBlocks[this->current][i]);
            }
            this->currentBlocks.pop_back();
            this->holding = true;
            this->tickB = 250;
            this->c_hold = -1;
        }
        else{
            for(int i = 0; i < this->currentBlocks[this->current].size(); i ++){
                this->temporary.push_back(this->currentBlocks[this->current][i]);
            }
            this->currentBlocks.pop_back();
            int sy = this->held[0].y;
            int sx = this->startPos.x - this->held[0].x;
            for(int i = 0; i < this->held.size(); i ++){
                this->held[i].y -= sy;
                this->held[i].x -= sx;
            }
            this->currentBlocks.push_back(this->held);
            this->held.clear();
            for(int i = 0; i < this->temporary.size(); i++){
                this->held.push_back(this->temporary[i]);
            }

            temporary.clear();
            this->c_hold = 0;
        }
    }
}
