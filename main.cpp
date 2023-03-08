#include "user_control.h"
#include "game.h"
#include "room.h"
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
    std::cout << "Start game GLADIATOR!\n" << std::endl;

    dice_init();

//    test_create_isle();
//    test_search_way_out();

    // test_print_colour_screen();

    //test_user_control();;
    // test_fast_screen_show();
    // test_print_simple_colour_rect();
    // test_creating_vectors();
    // system("cls");

    while(1)
    {
        if(Game.Do())
            break;
    }
    std::cout << "End game GLADIATOR!\n" << std::endl;
    return 0;
}


