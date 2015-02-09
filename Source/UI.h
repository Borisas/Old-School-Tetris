#ifndef UI_H
#define UI_H
#include "core.h"
#include "structures.h"

class ui{
    public:
        ui();
        ~ui();
        void drawGame(int score,int difficulty);
        void drawMenu(int select);
    private:
        box game_ui[10];
        box menu_ui[6];

};

#endif
