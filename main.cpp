#include "arena.h"
#include "gladiator.h"
#include "settings.h"
#include "screen.h"
#include "dice.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include "test_code.h"


//using namespace std;


int main()
{
    cout << "Start program!\n" << endl;

    dice_init();

//    test_create_isle();
//    test_search_way_out();
    test_print_colour_screen();
    return 0;
}


