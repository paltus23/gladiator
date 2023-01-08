#ifndef SCREEN_H
#define SCREEN_H

#include "arena.h"
#include "types.h"
#include "windows.h"
#include "menu.h"

// typedef struct _CHAR_INFO {
//   union {
//     WCHAR UnicodeChar;
//     CHAR  AsciiChar;
//   } Char;
//   WORD  Attributes;
// } CHAR_INFO, *PCHAR_INFO;


class Screen_t
{
    public:
        enum COLOURS
        {
            BLACK   = 0,
            BLUE    = 0x1,
            GREEN   = 0x2,
            CYAN    = 0x3,
            RED     = 0x4,
            YELLOW  = 0x5,
            MAGENTA = 0x6,
            WHITE   = 0x7,

            BRIGHT_BLACK   = BLACK   + 0x08,
            BRIGHT_BLUE    = BLUE    + 0x08,
            BRIGHT_GREEN   = GREEN   + 0x08,
            BRIGHT_CYAN    = CYAN    + 0x08,
            BRIGHT_RED     = RED     + 0x08,
            BRIGHT_YELLOW  = YELLOW  + 0x08,
            BRIGHT_MAGENTA = MAGENTA + 0x08,
            BRIGHT_WHITE   = WHITE   + 0x08
        };

        CHAR_INFO** Screen; //for working like 2d array. creatse array of pointers and then this pointers point to lines of Screen_mem
        CHAR_INFO* Screen_mem;
        Screen_t(coord_t coord){ Screen_t(coord.x, coord.y); }
        Screen_t(int x, int y)
        {
            //@todo add clear output
            Size.x = x;
            Size.y = y;
            Screen = (CHAR_INFO**)malloc(Size.y * sizeof(CHAR_INFO*));
            Screen_mem = (CHAR_INFO*)malloc( (Size.x*Size.y+1) * sizeof(CHAR_INFO));
            for (int i=0; i <Size.y; i++)
            {
                Screen[i] = Screen_mem + i*Size.x;
            }
            Screen_mem[Size.x*Size.y].Char.AsciiChar = (CHAR)0;

            //clear Screen
            clear();

            // hide cursor
            auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
            const CONSOLE_CURSOR_INFO console_cursor_info = {1,false};
            SetConsoleCursorInfo(handle, &console_cursor_info);
        }
        ~Screen_t()
        {
            free(Screen);
            free(Screen_mem);
        }
        coord_t Size;       ///size of screen

        void print(int x, int y, char* chars);
        void fill(char _ch, int color_fore = WHITE, int color_back = BLACK) 
        {
            CHAR_INFO ch;
            ch.Char.AsciiChar = _ch;
            ch.Attributes = (color_back << 4) | color_fore; 
            fill(ch); 
        }

        void fill(CHAR_INFO ch) { std::fill(Screen_mem, Screen_mem + Size.x*Size.y, ch);}
        void draw_char(int x, int y, char ch, int color_fore = WHITE, int color_back = BLACK);
        void draw_char(int x, int y, CHAR_INFO ch);
        void draw_rectangle(int x, int y, size_t size_x, size_t size_y, char ch);
        void draw_rectangle_edge(int x, int y, size_t size_x, size_t size_y, char ch);

        void draw_vertical_line(int x, int y, size_t size, char ch);
        void draw_horizontal_line(int x, int y, size_t size, char ch);

        void draw(Room_t& arena, int start_x = 0, int start_y = 0);
        void draw(int x, int y, Room_t * arena);
        void draw(Menu_t &menu, int x, int y, int color_fore = WHITE, int color_back = BLACK);

        void show(); //Print Screen_mem to console
        void clear(); //Fill Screen_mem with spaces

        static void get_console_size(coord_t *coord);
};
#endif // SCREEN_H
