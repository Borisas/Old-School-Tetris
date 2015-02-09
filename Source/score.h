#ifndef SCORE_H
#define SCORE_H
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

class score{
    public:
        score();
        ~score();
        void loadScore();
        int getPlaceScore(int place);
        void addScore(int score);
        void writeScore();
        int difficulty(int score, int difficulty);
    private:
        void sort();
        vector<int> s_db;
};


#endif
