#include "unit_tests.h"

#include "arena.h"
#include "gladiator.h"
#include "settings.h"
#include "screen.h"
#include "dice.h"
#include "ocean.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>

/**
* @brief create simple isle and check find way out
*/
void unit_test_search_way_out()
{
    coord_t c = {20,20};
    Ocean *ocean = new Ocean(c);

    area_t isle{
        {1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 1, 1, 0},
        {1, 1, 0, 0, 0, 1, 1, 1, 0},
        {1, 1, 0, 0, 0, 1, 1, 1, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0},
    };
    ocean->add_isle(1,2, isle);

    coord_t cursor_out;

    ocean->search_way_out(3, 7, cursor_out);

    if(ocean->get_cell(cursor_out) )
    {
        system("Color 0A");
        printf("TEST search_way_out() PASS");
    }
    else
    {
        system("Color 04");
        printf("TEST search_way_out() FAIL");
    }

    
    delete ocean;
}