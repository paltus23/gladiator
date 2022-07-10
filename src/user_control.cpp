#include "user_control.h"
#include <iostream>
#include <conio.h>


enum{
    KEY_CODE = 0xE0,
    KEY_UP =  KEY_CODE * 256 + 0x48 ,
    KEY_DOWN = KEY_CODE * 256 + 0x50,
    KEY_LEFT = KEY_CODE * 256 + 0x4b,
    KEY_RIGHT = KEY_CODE * 256 + 0x4d,
    KEY_ESCAPE = 0x1b,
    KEY_RETURN = 0x0d,
};

User_control_t::Do()
{
    Cmd = NOTHING;
    if (_kbhit())
    {
        int key = _getch();

        if(key == KEY_CODE)
        {
            key = _getch();
            key = KEY_CODE * 256 + key;
        }
        switch (key)
        {
        case KEY_UP:
        case 'w':
        case 'W':
        {
            Cmd = UP;
            break;
        }
        case KEY_DOWN:
        case 's':
        case 'S':
        {
            Cmd = DOWN;
            break;
        }
        case KEY_LEFT:
        case 'a':
        case 'A':
        {
            Cmd = LEFT;
            break;
        }
        case KEY_RIGHT:
        case 'd':
        case 'D':
        {
            Cmd = RIGHT;
            break;
        }
        case KEY_ESCAPE:
            Cmd = EXIT;
            break;
        default:
            break;
        }
    }


}
