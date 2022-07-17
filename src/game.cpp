#include "game.h"

void Game_t::Do()
{
    //Screen.fill('.');
    Arena_t arena(10, 10);
    arena.simple_construct();
    arena.place_unit(&Gladiator, 2,2);
    Screen.draw(arena);
    Screen.draw_char(Gladiator.X,Gladiator.Y, '@', Screen_t::RED, Screen_t::BLACK);
    Screen.show();
    while(1)
    {
        User_control.Do();

        Screen.fill(' ');

        auto cmd = User_control.get_cmd();
        coord_t coord = {Gladiator.X,Gladiator.Y};


        if(cmd != User_control_t::NOTHING)
        {
            if(cmd == User_control_t::EXIT)
            {
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
            
            Gladiator.move(&coord);

            Screen.draw(arena);
            Screen.draw_char(coord.x, coord.y, '@', Screen_t::RED, Screen_t::BLACK);

            Screen.show();
        }
    }
}

Game_t Game;