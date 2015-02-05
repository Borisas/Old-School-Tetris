#ifndef UI_H
#define UI_H
#include "core.h"
#include "structures.h"

class ui{
    public:
        ui();
        ~ui();
        void draw();
    private:
        box game_ui[4];

};

#endif
