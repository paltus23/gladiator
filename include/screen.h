#ifndef SCREEN_H
#define SCREEN_H

#include "arena.h"
#include "types.h"

class Screen_t
{
    public:

        char** Screen; //for working like 2d array. creatse array of pointers and then this pointers point to lines of Screen_mem
        char* Screen_mem;
        Screen_t(coord_t coord){ Screen_t(coord.x, coord.y); }
        Screen_t(int x, int y)
        {
            Size.x = x;
            Size.y = y;
            Screen = (char**)malloc(Size.y * sizeof(char*));
            Screen_mem = (char*)malloc(Size.x*Size.y+1);
            for (int i=0; i <Size.y; i++)
            {
                Screen[i] = Screen_mem + i*Size.x;
            }
            Screen_mem[Size.x*Size.y] = 0;
            clear();
        }
        ~Screen_t()
        {
            free(Screen);
            free(Screen_mem);
        }
        coord_t Size;


        void fill(char ch)
        {
            memset(Screen_mem, (int)ch, Size.x*Size.y);
        }
        void draw_rectangle(int x, int y, size_t size_x, size_t size_y, char ch);
        void draw_rectangle_edge(int x, int y, size_t size_x, size_t size_y, char ch);

        void draw_vertical_line(int x, int y, size_t size, char ch);
        void draw_horizontal_line(int x, int y, size_t size, char ch);

        void draw(int x, int y, Arena_t * arena);

        void show(); //Print Screen_mem to console
        void clear(){memset(Screen_mem, ' ', Size.x*Size.y);}; //Fill Screen_mem with spaces

        static void get_console_size(coord_t *coord);
};
#endif // SCREEN_H
