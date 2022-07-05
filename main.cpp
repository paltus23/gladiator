#include "user_control.h"
#include "arena.h"
#include "gladiator.h"
#include "settings.h"
#include "screen.h"
#include "dice.h"
#include "test_code.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <iostream>


//using namespace std;


int main()
{
    cout << "Start program!\n" << endl;

    dice_init();

//    test_create_isle();
//    test_search_way_out();

    // test_print_colour_screen();

    //test_user_control();;
    test_fast_screen_show();

    return 0;
}


