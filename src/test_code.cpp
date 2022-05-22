#include "test_code.h"

#include "arena.h"
#include "gladiator.h"
#include "settings.h"
#include "screen.h"
#include "dice.h"
#include "ocean.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>


//using namespace std;

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


    system("Color 0A");
    for(int i = 0; i < 100; i++)
    {

        system("cls");
        int color = i%16;

        char s[100] ;
        sprintf(s,"Color 0%x", color );
        system(s);

        screen.draw_magic_circle(i%24);

        screen.show();

        Sleep(1000/100);
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

void test_create_isle()
{

}


/**
* @brief create simple isle and check find way out
*/
void test_search_way_out()
{
    coord_t c = {20,20};
    Ocean *ocean = new Ocean(c);

    area_t isle{
        {0, 1, 1},
        {0, 1, 0},
        {1, 1, 0}
    };
    printf("add isle\n");

    ocean->add_isle(1,1, isle);

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
