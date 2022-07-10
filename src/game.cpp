#include "game.h"



void Game_t::Do()
{
    Screen.fill('.');
    Screen.draw_char(Gladiator.X,Gladiator.Y, '@');
    Screen.show();
    while(1)
    {
        User_control.Do();

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
                Gladiator.move(&coord);
                break;
            case User_control_t::RIGHT:
                coord.x++;
                Gladiator.move(&coord);
                break;
            case User_control_t::UP:
                coord.y--;
                Gladiator.move(&coord);
                break;
            case User_control_t::DOWN:
                coord.y++;
                Gladiator.move(&coord);
                break;
            default:
                break;
            }
            
            Screen.fill('.');
            Screen.draw_char(coord.x, coord.y, '@');
            Screen.show();
        }


    }
}

Game_t Game;