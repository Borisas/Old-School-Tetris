#include "block.h"

block::block(const char* img)
{
    this->texture = core::loadImg(img);
    this->speed = 10;
    this->tickA = 0;
    this->tickB = 0;
    this->startPos.x = 10;
    this->startPos.y = 10;
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
}
void block::set_pos(double x, double y, double w, double h){
    this->position.x = x;
    this->position.y = y;
    this->position.h = h;
    this->position.w = w;
}
void block::drop(){
    if(tickA >= speed){
        for(int i = 0; i < this->currentBlocks.size(); i++){
            for(int j = 0; j < this->currentBlocks[i].size(); j++){
                core::draw(this->texture, this->currentBlocks[i][j]);
                this->currentBlocks[i][j].y +=16;
            }
        }
        this->tickA = 0;
    }
    else
        this->tickA+=1;

}
void block::set_speed(int speed){
    this->speed = speed;
}
void block::update(){
    this->draw();
    this->drop();
    if(tickB >= 250){
        int random = rand() % this->b_db.size();
        cout << random;
        this->newBlock(random);
        this->tickB = 0;
    }
    else
        this->tickB+=1;

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

}
