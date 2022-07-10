#pragma once
#include "user_control.h"
#include "gladiator.h"
#include "screen.h"
#include "string.h"

class Game_t
{
    public:
        int cc; 
        User_control_t User_control;
        Gladiator_t Gladiator;
        Arena_t Arena{10, 10};
        Screen_t Screen;

        Game_t():Gladiator("Player"), Screen(120,30)
        { 
            Arena.place_unit(&Gladiator, 5,5);
        }

        void Do();
};

extern Game_t Game;