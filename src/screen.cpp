#include "screen.h"
#include "windows.h"
#include <cmath>


void Screen::show()
{
    COORD point;
    for(point.X = 0; point.X < Size.x; point.X++)
    {
        for(point.Y = 0; point.Y < Size.y; point.Y++)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
            std::cout << screen[point.Y][point.X];
        }
    }

}
/**
 * @brief draw arena object
 *              WARNING don't have any checks of arguments!
 * 
 * 
 * */
void Screen::draw(Arena * arena, align_t align)
{
    coord_t overall_size, floor_size;
    arena->get_overall_size(&overall_size);
    arena->get_floor_size(&floor_size);

    switch(align)
    {
    case CENTER:
    {
        clear();
        int offset_x = (Size.x-overall_size.x)/2;
        int offset_y = (Size.y-overall_size.y)/2;

        //draw up wall
        memset(screen[offset_y] + offset_x, '#', overall_size.x);

        for(int i = 0; i<floor_size.y; i++)
        {
            screen[offset_y + i + 1][offset_x] = '#';
            memset(screen[offset_y + 1 + i] + offset_x + 1, '.', floor_size.x);
            screen[offset_y + i + 1][offset_x + floor_size.x + 1] = '#';
        }
        //draw down wall
        memset(screen[offset_y + floor_size.y + 1] + offset_x, '#', overall_size.x);
        break;
    }
    case LEFT_UP:
        break;
    }
}

/**
 * @brief draw rectangle
 * 
 */
void Screen::draw_rectangle(int x, int y, size_t size_x, size_t size_y, char ch)
{
    int end_x = x + size_x;
    int end_y = x + size_y;

    for(int cur_y = y<0 ? 0 : y; cur_y<Size.y && cur_y<end_y; cur_y++)
    {
        for(int cur_x = x<0 ? 0 : x; cur_x<Size.x && cur_x<end_x; cur_x++)
        {
            
            screen[cur_y][cur_x] = ch;
        }
    }
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
                    screen[center_y - i][j + cur_x] = '%';
                    screen[center_y + i][j + cur_x] = '%';

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
                    screen[center_y - i][j + cur_x] = '%';
                    screen[center_y + i + 1][j + cur_x] = '%';

                }
            }


        }
        break;
    }
    case LEFT_UP:
        break;
    }

}
