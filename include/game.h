#pragma once
#include "user_control.h"
#include "gladiator.h"
#include "string.h"

class Game_t
{
    public:
        int cc; 
        User_control_t User_control;
        Gladiator_t Gladiator;
        Arena_t Arena{10, 10};
        //Screen Screen;

        Game_t():Gladiator("Player")
        { 
            Arena.place_unit(&Gladiator, 2,2);
        }
        ~Game_t();
        void Do();
};