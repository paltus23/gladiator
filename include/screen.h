#ifndef SCREEN_H
#define SCREEN_H

#include "arena.h"
#include "types.h"

class Screen
{
    public:
        typedef enum{CENTER, LEFT_UP} align_t;

        char** Screen_array; //for working like 2d array. creatse array of pointers and then this pointers point to lines of Screen_mem
        char* Screen_mem;
        Screen(int x, int y)
        {
            Size.x = x;
            Size.y = y;
            Screen_array = (char**)malloc(Size.y * sizeof(char*));
            Screen_mem = (char*)malloc(Size.x*Size.y+1);
            for (int i=0; i <Size.y; i++)
            {
                Screen_array[i] = Screen_mem + i*Size.x;
            }
            Screen_mem[Size.x*Size.y] = 0;
            clear();
        }
        ~Screen()
        {
            free(Screen_array);
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

        void draw(int x, int y, Arena * arena);

        void show(); //Print Screen_mem to console
        void clear(){memset(Screen_mem, ' ', Size.x*Size.y);}; //Fill Screen_mem with spaces

        static void get_console_size(coord_t *coord);
//-------------------Old dummy methods---------------------
        void draw(Arena * arena, align_t align = Screen::CENTER);
        void draw_magic_circle(int d, align_t align = Screen::CENTER);
};
#endif // SCREEN_H
