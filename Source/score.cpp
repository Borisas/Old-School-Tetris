#include "score.h"

score::score(){
    this->loadScore();
}

score::~score(){
}


void score::loadScore(){
    ifstream file("assets/score");
    int temp;
    if(!file.is_open()){
        cout << "FAILED TO OPEN FILE score" << endl;
    }
    else{
        while(!file.eof()){
            file >> temp;
            this->s_db.push_back(temp);
        }
        file.close();
        this->sort();
    }
}
void score::writeScore(){
    ofstream file("assets/score");
    if(!file.is_open()){
        cout << "FAILED TO OPEN FILE score" << endl;
    }
    else{
        for(unsigned int i = 0; i < this->s_db.size(); i++){
            file << this->s_db[i] << endl;
        }
    }
}

void score::sort(){
    int temp;
    for(unsigned int i = 0; i < this->s_db.size(); i++){
        for(unsigned int j = 0; j < this->s_db.size(); j++){
            if(this->s_db[i] > this->s_db[j]){
                temp = this->s_db[i];
                this->s_db[i] = this->s_db[j];
                this->s_db[j] = temp;
            }
        }
    }
}
int score::getPlaceScore(int place){
    return this->s_db[place-1];
}
void score::addScore(int score){
    this->s_db.push_back(score);
    this->sort();
}
int score::difficulty(int score, int difficulty){
    int temp = (int)(2*sqrt(80*score))/500;
    if(temp>20)
        temp = 20;
    return temp;
}
