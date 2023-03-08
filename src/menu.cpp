#include "menu.h"



const char* Start_menu_str[] = 
{
    "Start game",
    "Create random room",
    "Options",
    "Exit"
};

const char* Game_menu_str[] = 
{
    "New battle",
    "Contimue",
    "Back"
};

void Menu_t::Do(User_control_t::cmd_t cmd)
{

    switch (cmd)
    {
    case (User_control_t::DOWN):
        Cursor++;
        break;
    case (User_control_t::UP):
        Cursor--;
        break;
    default:
        break;
    }


    if(Cursor >= Cursor_max)
        Cursor = 0;
    else if(Cursor <= -1)
        Cursor = Cursor_max - 1;

}

void Menu_t::Set_state(State_t state)
{
    State = state;
    Cursor = 0;

    switch (state)
    {
    case STATE_NOTHING:     
        Cursor_max = 0;        
        break;
    case STATE_START_MENU:  
        Cursor_max = sizeof(Start_menu_str) / sizeof(Start_menu_str[0]);
        Menu_str_ptr = Start_menu_str;
        break;
    case STATE_GAME_MENU:   
        Cursor_max = sizeof(Game_menu_str) / sizeof(Game_menu_str[0]);
        Menu_str_ptr = Game_menu_str;
        break;
    default:
        break;
    }
    
}

const char** Menu_t::Get_menu_str() const
{
    return Menu_str_ptr;
}