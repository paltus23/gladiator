#pragma once
#include "user_control.h"
#include "gladiator.h"
#include "screen.h"
#include "string.h"
#include "menu.h"

/** the Game process is divided into several modes
 * 1 - fighting mode 
 * 2 - walking mode
*/
class Game_t
{
    private:
        enum State_t
        {
            STATE_START_MENU,
            STATE_BATTLE,
            STATE_FINISH_BATTLE,
            STATE_FINISH_GAME
        };

        User_control_t::cmd_t Cmd;
    public:
        User_control_t User_control;
        Menu_t Menu;
        Gladiator_t *Gladiator;
        Room_t *Arena;
        Screen_t Screen;
        State_t State;


        ///@todo postpone this. because, I don't know, what I should do with this at now. remove create Screen and make auto-adjust for size of window. 
        Game_t():Screen(120,30)
        {
            State = STATE_START_MENU;
            Menu.Set_state(Menu_t::STATE_START_MENU);
        }

        ~Game_t();

        int Do();
        void Do_battle();                     ///> planning the next step with walking steps and hits
        void Process_fighting_step();           ///> process step after finish planning
        void Do_walk();                         ///> play mode when main player walks in search of new enemy
        void Init();

};

extern Game_t Game;