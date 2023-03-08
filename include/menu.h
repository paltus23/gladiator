#ifndef MENU_H
#define MENU_H

#include "string.h"
#include "types.h"
#include "user_control.h"


class Menu_t 
{

    public:
        enum START_MENU
        {
            START_GAME,
            CREATE_RANDOM_ROOM,
            OPTIONS,
            EXIT
        };

        enum GAME_MENU
        {
            NEW_BATTLE,
            CONTINUE,
            BACK
        };

        enum State_t
        {
            STATE_NOTHING,
            STATE_START_MENU,
            STATE_GAME_MENU,
        };
        Menu_t():Cursor(0)
        {}
        virtual ~Menu_t()
        {}

        void Do(User_control_t::cmd_t cmd);

        void Set_state(State_t state);
        State_t Get_state() const
        {
            return State;
        }
        void Set_cursor(int cursor)
        {
            Cursor = cursor;
        }
        int Get_cursor() const
        {
            return Cursor;
        }
        int Get_cursor_max() const
        {
            return Cursor_max;
        }
        const char** Get_menu_str() const;
    private:
        const char** Menu_str_ptr;
        int Cursor;
        int Cursor_max;
        State_t State;
};

#endif // MENU_H