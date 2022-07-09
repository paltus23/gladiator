#include "test_code.h"

#include "arena.h"
#include "gladiator.h"
#include "settings.h"
#include "screen.h"
#include "dice.h"
#include "ocean.h"
#include "user_control.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>


//using namespace std;

void setColor(int colorBack, int colorFore)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (colorBack << 4) | colorFore);
}

void change_colour(int colorBack, int colorFore, COORD dwWriteCoord)
{
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    WORD attr = (colorBack << 4) | colorFore;

    long unsigned int num;
    WriteConsoleOutputAttribute(  handle,  &attr,  1,  dwWriteCoord, &num);
}

void print_ocean(Ocean *ocean)
{
    Ocean::print(ocean);
}

void test_print_colour_screen()
{
    Settings settings;
    //set size of console window
    settings.console_screen_size_x = 120;
    settings.console_screen_size_y = 30;

    Screen screen(settings.console_screen_size_x, settings.console_screen_size_y);

    Arena arena(50,20);

//    Gladiator hummy("Hummy");

//    arena.place_unit((Unit*)&hummy, 10, 10);

//    arena.print_units();


    system("cls");

    char s[100] ;
    
    setColor(0, 8);

    //turn off cursor visibility
    const CONSOLE_CURSOR_INFO console_cursor_info = {1,false};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console_cursor_info);

    screen.draw_rectangle(0, 0, 120, 30, '.');

    screen.show();

    int last_pos = -1;
    //print run red symbol '@'
    for(int i = 5; i<20; i++)
    {

        //clear last cell
        if(last_pos >=0)
        {
            setColor(0, 8);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {last_pos,20});
            std::cout << '.';
        }

        //print '@'
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {i,20});
        setColor(0, 4);
        std::cout << '@';
        last_pos = i;
        //SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console_cursor_info);
        Sleep(300);
    }

}




void test_draw_rectangle()
{
    Screen screen(50, 50);

    // screen.draw_rectangle(-2,-2,500,7,'v');

    system("cls");

    screen.fill('.');

    screen.draw_rectangle(3,3,5,5,'v');
    screen.draw_rectangle(1,1,5,5,'m');
    screen.draw_rectangle(2,2,5,5,'u');

    screen.draw_rectangle(-2,-2,5,5,'c');
    screen.draw_rectangle(49,49,5,5,'p');


    screen.draw_rectangle(-2,20,5,5,'%');
    screen.draw_rectangle(-12,-12,5,5,'M');
    screen.show();

}

void test_fast_screen_show()
{

    coord_t coord;
    Screen::get_console_size(&coord);

    Screen screen(coord.x, coord.y);

    // screen.draw_rectangle(-2,-2,500,7,'v');

    system("cls");
    setColor(0, 8);
    screen.fill('.');
    screen.show();
    screen.draw_rectangle(3,3,5,5,'v');
    screen.show();
    screen.draw_rectangle(1,1,5,5,'m');
    screen.show();
    screen.draw_rectangle(2,2,5,5,'u');
    screen.show();
    screen.draw_rectangle(-2,-2,5,5,'c');
    screen.show();
    screen.draw_rectangle(49,49,5,5,'p');
    screen.show();
    screen.draw_rectangle(-2,20,5,5,'%');
    screen.show();
    screen.draw_rectangle(-12,-12,5,5,'M');
    screen.show();

    COORD c = {10,10};
    change_colour(0, 8, c);

}

void test_create_isle()
{

    coord_t c = {10,10};
    Ocean *ocean = new Ocean(c);

    // ocean->create_random_isle(3,2,2);
    // ocean->create_random_isle(4,2,2);
    // ocean->create_random_isle(5,8,2);
    // ocean->create_random_isle(6,2,2);    
    ocean->create_random_isle(7,9,0,20);
    ocean->create_random_isle(8,0,0, 20);


    print_ocean(ocean);

    //bad working with delete. 
    delete ocean;

}


/**
* @brief create simple isle and check find way out
*/
void test_search_way_out()
{
    coord_t c = {10,10};
    Ocean *ocean = new Ocean(c);

    area_t isle{
      // 0  1  2  3  4  5  6  7  8
        {1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 1, 1, 1, 0},
        {1, 1, 1, 0, 0, 1, 1, 1, 0},
        {1, 1, 0, 0, 0, 1, 1, 1, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0},
    };
    printf("add isle\n");

    ocean->add_isle(0,0, isle);

    coord_t cursor_out;

    ocean->search_way_out(1, 1, cursor_out);
    printf("Coord out [%d, %d] = %d\n", cursor_out.x, cursor_out.y, ocean->get_cell(cursor_out));
    ocean->set_cell(cursor_out, 2);

    // ocean->search_way_out(5, 6, cursor_out);
    // printf("Coord out [%d, %d] = %d\n", cursor_out.x, cursor_out.y, ocean->get_cell(cursor_out));
    // ocean->set_cell(cursor_out, 3);

    print_ocean(ocean);

    
    delete ocean;
}


/**
*
*/
void test_assign_vectors()
{
    std::vector<int> x1, x2;
    x1 = {1,2,3};
    x2 = x1;

    auto s = x1.size();
    auto x = x2.begin();
    ++x;
    x2.insert(x, x1.data(), x1.data() + s);
    for(int x:x2)
    {
        printf("%d\n",x);
    }
}


void test_user_control()
{
    User_control user_control;
    while(1)
    {
        user_control.Do();
        if (user_control.cmd == User_control::EXIT)
            break;
    }
}

void test_print_simple_colour_rect()
{
    coord_t coord;
    Screen::get_console_size(&coord);

    Screen screen(coord.x, coord.y);


    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

    int back = 0;
    int fore = 4;

    WORD attr = (back << 4)| fore;
    //buffer of colour text would be printed like animation
    CHAR_INFO chars[20];

    for(int i = 0; i < 20; i++)
    {
        chars[i].Attributes = attr;
        chars[i].Char.AsciiChar = 'a' + i;
    }


    for(int i = 0; i < 40; i++)
    {
        setColor(0, 8);
        screen.fill('.');
        screen.show();

        COORD dwBufferSize = {4, 5};
        COORD dwBufferCoord = {0,0};
        SMALL_RECT WriteRegion = {0 + i,10,79,29};

        auto res = WriteConsoleOutput(handle, chars, dwBufferSize, dwBufferCoord, &WriteRegion);

        Sleep(150);
    }
}