#include "game.h"

int Game_t::Do()
{
    User_control.Do();

    auto cmd = User_control.get_cmd();
    
    

    switch (State)
    {
    case STATE_START_MENU:
        /* code */

        Menu.Do((User_control_t::cmd_t)cmd);
        Screen.clear();
        Screen.draw(Menu, 1, 1);

        if(cmd == User_control_t::ENTER)
        {
            if(Menu.Get_cursor() == Menu_t::START_GAME)
            {
                State = STATE_BATTLE;
                Gladiator = new Gladiator_t("Player");
                Arena = new Arena_t(10, 10);
                Arena->simple_construct();
                Arena->place_unit(Gladiator, 2,2);
                Screen.clear();
                Screen.draw(*Arena);
                Screen.draw_char(Gladiator->X,Gladiator->Y, '@', Screen_t::RED, Screen_t::BLACK);
                Screen.show();
            }
            if(Menu.Get_cursor() == Menu_t::EXIT)
            {
                State = STATE_FINISH_GAME;
            }
        }

        if(cmd == User_control_t::EXIT)
        {
            State = STATE_FINISH_GAME;
        }

        Screen.show();
        break;
    case STATE_BATTLE:
        {
            Screen.fill(' ');

            coord_t coord = {Gladiator->X,Gladiator->Y};

            if(cmd != User_control_t::NOTHING)
            {
                if(cmd == User_control_t::EXIT)
                {
                    State = STATE_START_MENU;
                    break;
                }

                switch (cmd)
                {
                case User_control_t::LEFT:
                    coord.x--;
                    break;
                case User_control_t::RIGHT:
                    coord.x++;
                    break;
                case User_control_t::UP:
                    coord.y--;
                    break;
                case User_control_t::DOWN:
                    coord.y++;
                    break;
                default:
                    break;
                }
                
                Gladiator->move(&coord);

                Screen.draw(*Arena);
                Screen.draw_char(coord.x, coord.y, '@', Screen_t::RED, Screen_t::BLACK);

                Screen.show();
            }
        }
        break;

    case STATE_FINISH_BATTLE:
        /* code */
        break;
    case STATE_FINISH_GAME:
        /* code */
        Screen.clear();
        Screen.show();
        return 1;
        break;
    default:
        break;
    }
    return 0;
}

void Game_t::Init()
{
    Menu.Set_state(Menu_t::STATE_START_MENU);
}

void Game_t::Do_fighting()
{
}


void Game_t::Process_fighting_step()
{
}

void Game_t::Do_walk()
{
}

Game_t::~Game_t()
{
    if(Gladiator)
        delete Gladiator;
    if(Arena)
        delete Arena;
}
Game_t Game;