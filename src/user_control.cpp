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

User_control::Do()
{
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
            std::cout << "Forward";
            break;
        }
        case KEY_DOWN:
        case 's':
        case 'S':
        {
            std::cout << "Back";
            break;
        }
        case KEY_LEFT:
        case 'a':
        case 'A':
        {
            std::cout << "Left";
            break;
        }
        case KEY_RIGHT:
        case 'd':
        case 'D':
        {
            std::cout << "Right";
            break;
        }
        default:
            break;
        }
        std::cout << "\n";
    }


}
