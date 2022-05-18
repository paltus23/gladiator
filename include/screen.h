#ifndef SCREEN_H
#define SCREEN_H

#include "arena.h"
#include "types.h"

class Screen
{
    public:
        typedef enum{CENTER, LEFT_UP} align_t;

        char** screen; //for working like 2d array
        char* screen_mem;
        Screen(int x, int y)
        {
            Size.x = x;
            Size.y = y;
            screen = (char**)malloc(Size.y * sizeof(char*));
            screen_mem = (char*)malloc(Size.x*Size.y+1);
            for (int i=0; i <Size.y; i++)
            {
                screen[i] = screen_mem + i*Size.x;
            }
            screen_mem[Size.x*Size.y] = 0;
            clear();
        }
        ~Screen()
        {
            free(screen);
            free(screen_mem);
        }
        coord_t Size;


        void fill(char ch)
        {
            memset(screen_mem, (int)ch, Size.x*Size.y);
        }
        void draw(Arena * arena, align_t align = Screen::CENTER);
        void draw_magic_circle(int d, align_t align = Screen::CENTER);
        void draw_rectangle(int x, int y, size_t size_x, size_t size_y, char ch);

        void show()/*{ cout << screen_mem; }*/;
        void clear(){memset(screen_mem, ' ', Size.x*Size.y);};
};
#endif // SCREEN_H
