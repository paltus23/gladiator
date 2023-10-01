#include "game.h"

#include "utils.h"

void Game_t::Init()
{
    Menu.Set_state(Menu_t::STATE_START_MENU);
}

int Game_t::Do()
{
    User_control.Do();
    Cmd = User_control.get_cmd();
    
    

    switch (State)
    {
    case STATE_START_MENU:

        Menu.Do((User_control_t::cmd_t)Cmd);
        Screen.clear();
        Screen.draw(Menu, 1, 1);

        if(Cmd == User_control_t::ENTER)
        {
            if(Menu.Get_cursor() == Menu_t::START_GAME)
            {
                State = STATE_BATTLE;
                Gladiator = new Gladiator_t("Player");
                Arena = new Room_t(10, 10);
                Arena->simple_construct();
                Arena->place_unit(Gladiator, 2,2);
                Screen.clear();
                Screen.draw(*Arena);
                Screen.draw_char(Gladiator->X,Gladiator->Y, '@', Screen_t::RED, Screen_t::BLACK);
                Screen.show();
            }
            if(Menu.Get_cursor() == Menu_t::CREATE_RANDOM_ROOM)
            {
                State = STATE_BATTLE;
                Gladiator = new Gladiator_t("Player");
                Arena = new Room_t(20, 20);
                Arena->create_random();
                coord_t cursor_out;
                bool (*get_cell)(int, int, void*) = [](int x, int y, void* obj) -> bool
                {
                    if(((Room_t*)obj)->Cells2[x][y] == Room_t::FLOOR)
                        return false;
                    else
                        return true;
                };
                auto result = search_way_out(Arena, 2, 2, 20, 20, cursor_out, get_cell);
                Arena->place_unit(Gladiator, cursor_out.x, cursor_out.y);
                Screen.clear();
                Screen.draw(*Arena);
                if(result)
                {
                    Screen.draw_char(Gladiator->X,Gladiator->Y, '@', Screen_t::RED, Screen_t::BLACK);
                }
                Screen.show();
            }

            if(Menu.Get_cursor() == Menu_t::EXIT)
            {
                State = STATE_FINISH_GAME;
            }
        }

        if(Cmd == User_control_t::EXIT)
        {
            State = STATE_FINISH_GAME;
        }

        Screen.show();
        break;
    case STATE_BATTLE:
    {
        Do_battle();
        if (State == STATE_START_MENU)
        {
            delete Gladiator;
            delete Arena;
        }
        break;
    }
    case STATE_FINISH_BATTLE:
        State = STATE_FINISH_GAME;
        break;
    case STATE_FINISH_GAME:
        Screen.clear();
        Screen.show();
        return 1;
        break;
    default:
        break;
    }
    return 0;
}



void Game_t::Do_battle()
{
    Screen.fill(' ');

    coord_t coord = {Gladiator->X,Gladiator->Y};

    if(Cmd != User_control_t::NOTHING)
    {
        if(Cmd == User_control_t::EXIT)
        {
            State = STATE_START_MENU;
            return;
        }

        switch (Cmd)
        {
        case User_control_t::LEFT:  coord.x--; break;
        case User_control_t::RIGHT: coord.x++; break;
        case User_control_t::UP:    coord.y--; break;
        case User_control_t::DOWN:  coord.y++; break;
        default: break;
        }
        
        Gladiator->move(&coord);

        //Enemy->move(&coord);

        Screen.draw(*Arena);
        Screen.draw_char(coord.x, coord.y, '@', Screen_t::RED, Screen_t::BLACK);

        Screen.show();
    }
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
