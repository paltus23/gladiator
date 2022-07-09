#include "screen.h"
#include "windows.h"
#include <cmath>

/**
 * @brief show Screen_mem in console
 */
void Screen::show()
{
    COORD point = {0,0};
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // hide cursor
    const CONSOLE_CURSOR_INFO console_cursor_info = {1,false};
    SetConsoleCursorInfo(handle, &console_cursor_info);
    // print
    SetConsoleCursorPosition(handle, point);
    std::cout << Screen_mem;
}


/**
 * @brief draw rectangle in Screen_mem
 * @param in x - start x coord
 * @param in y - start y coord
 * @param in size_x - size on x coord
 * @param in size_y - size on y coord
 * @param ch - character will be print
 */
void Screen::draw_rectangle(int x, int y, size_t size_x, size_t size_y, char ch)
{
    int end_x = x + size_x;
    int end_y = y + size_y;

    for(int cur_y = y<0 ? 0 : y; cur_y<Size.y && cur_y<end_y; cur_y++)
    {
        for(int cur_x = x<0 ? 0 : x; cur_x<Size.x && cur_x<end_x; cur_x++)
        {
            Screen_array[cur_y][cur_x] = ch;
        }
    }
}
/**
 * @brief draw vertical line
 * @param in x - start x coord
 * @param in y - start y coord
 * @param in size - length of line
 * @param ch - character will be print
 */
void Screen::draw_vertical_line(int x, int y, size_t size, char ch)
{
    int end_y = y + size;
    for(int cur_y = y<0 ? 0 : y; cur_y<Size.y && cur_y<end_y; cur_y++)
    {
        Screen_array[cur_y][x] = ch;
    }
}
/**
 * @brief draw horizontal line
 * @param in x - start x coord
 * @param in y - start y coord
 * @param in size - length of line
 * @param ch - character will be print
 */
void Screen::draw_horizontal_line(int x, int y, size_t size, char ch)
{
    int end_x = x + size;
    for(int cur_x = x<0 ? 0 : x; cur_x<Size.x && cur_x<end_x; cur_x++)
    {
        Screen_array[y][cur_x] = ch;
    }
}


/**
 * @brief draw rectangle edge
 * @param in x - start x coord
 * @param in y - start y coord
 * @param in size_x - size on x coord
 * @param in size_y - size on y coord
 * @param ch - character will be print
 */
void Screen::draw_rectangle_edge(int x, int y, size_t size_x, size_t size_y, char ch)
{
    int end_x = x + size_x;
    int end_y = y + size_y;

    if(size_y < 1 || size_x < 1)
        return;

    draw_vertical_line(x, y, size_y, ch);
    draw_horizontal_line(x, y, size_x, ch);
    draw_vertical_line(x + size_x - 1, y, size_y, ch);
    draw_horizontal_line(x, y + size_y - 1, size_x, ch);

}
/**
 * @brief get size of console window in chars
 * @param out coord - size of console window
 */
void Screen::get_console_size(coord_t *coord)
{
    CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo;
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleScreenBufferInfo) )
    {
        coord->x = ConsoleScreenBufferInfo.srWindow.Right - ConsoleScreenBufferInfo.srWindow.Left + 1;
        coord->y = ConsoleScreenBufferInfo.srWindow.Bottom - ConsoleScreenBufferInfo.srWindow.Top + 1;
    }
}


//-------------------Old dummy methods---------------------
/**
 * @brief draw arena object
 *              WARNING don't have any checks of arguments!
 * 
 * 
 * */
void Screen::draw(int x, int y, Arena * arena)
{
    coord_t overall_size, floor_size;
    arena->get_size(&floor_size);
    overall_size.x = floor_size.x + 2;
    overall_size.y = floor_size.y + 2;


    draw_rectangle_edge(x, y, overall_size.x, overall_size.y, '#');
    draw_rectangle_edge(x + 1, y + 1, floor_size.x, floor_size.y, '.');
}

/** \brief CIRCLE
 * Circle is a discrete figure by pixels, so there have some points
 * 1. diameter = radius * 2 - 1
 * after that we have interesting circle when radius = 1
 */


/** \brief draw magic circle
 * d - diameter
 * align - where draw the circle
 * return
 */
void Screen::draw_magic_circle(int d, align_t align)
{
    switch(align)
    {
    case CENTER:
    {

        //dot on edge of circle is A
        //coordianate of A = center - r
        clear();
        int center_x = (Size.x)/2;
        int center_y = (Size.y)/2;
        int offset_x = center_x - d/2;
        int offset_y = center_y - d/2;
        if(offset_y < 0)
            offset_y = 0;

        if(d & 1)
        {// if diameter is odd
            for(int i = 0; i < d/2 + 1; i++)
            {//draw from center to edge on y axis
                double A_x = sqrt((d*d)/4.0d - (double)(i*i)  );
                int cur_x = center_x - (int)A_x;
                if(cur_x < 0)
                    cur_x = 0;
                for(int j = 0; j < ((int)(A_x*2) | 1 ) && cur_x + j < Size.x; j++)
                {
                    Screen_array[center_y - i][j + cur_x] = '%';
                    Screen_array[center_y + i][j + cur_x] = '%';

                }
            }
        }
        else
        {// if diameter is even
            for(int i = 0; i < d/2; i++)
            {
                double A_x = round(sqrt(d*d/4.0d - (i+0.5)*(i+0.5) ));
                int cur_x = center_x - (int)A_x;
                if(cur_x < 0)
                    cur_x = 0;
                for(int j = 0; j < ((int)(A_x*2.0)) && cur_x + j < Size.x; j++)
                {
                    Screen_array[center_y - i][j + cur_x] = '%';
                    Screen_array[center_y + i + 1][j + cur_x] = '%';

                }
            }


        }
        break;
    }
    case LEFT_UP:
        break;
    }

}


/**
 * @brief draw arena object
 *              WARNING don't have any checks of arguments!
 * Not for using in production
 * 
 * */
void Screen::draw(Arena * arena, align_t align)
{
    coord_t overall_size, floor_size;
    arena->get_size(&floor_size);
    overall_size.x = floor_size.x + 2;
    overall_size.y = floor_size.y + 2;

    switch(align)
    {
    case CENTER:
    {
        clear();
        int offset_x = (Size.x-overall_size.x)/2;
        int offset_y = (Size.y-overall_size.y)/2;

        //draw up wall
        memset(Screen_array[offset_y] + offset_x, '#', overall_size.x);

        for(int i = 0; i<floor_size.y; i++)
        {
            Screen_array[offset_y + i + 1][offset_x] = '#';
            memset(Screen_array[offset_y + 1 + i] + offset_x + 1, '.', floor_size.x);
            Screen_array[offset_y + i + 1][offset_x + floor_size.x + 1] = '#';
        }
        //draw down wall
        memset(Screen_array[offset_y + floor_size.y + 1] + offset_x, '#', overall_size.x);
        break;
    }
    case LEFT_UP:
        break;
    }
}



