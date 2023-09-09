#include "utils.h"


/**
* @brief find exit from stuck
* @param in cur_x - start x cursor
* @param in cur_y - start y cursor
* @param in size_x - size of area x
* @param in size_y - size of area y
* @param out cursor_out - finded nearby empty cell. return false is cell is free
*/
bool search_way_out(void* obj, int cur_x, int cur_y, int size_x, int size_y, coord_t& cursor_out, bool (*get_cell)(int,int, void*) )
{
    // does cursor is in available area
    auto check_coord = [&](int cur_x, int cur_y)
    {
        return !(cur_x < 0 || cur_x >= size_x || cur_y < 0 || cur_y >= size_y);
    };

    // Check first cell
    if(check_coord(cur_x, cur_y))
    {
        if(!get_cell(cur_x, cur_y, obj))
        {
            cursor_out.x = cur_x;
            cursor_out.y = cur_y;
            return true;
        }
    }

    // set size of side of search square
    int side_size = 2;
    cur_y--;
    while(1)
    {
        for(int end_cursor_x = cur_x + side_size; cur_x < end_cursor_x; cur_x++ )
        {
            if(check_coord(cur_x, cur_y))
            {
                if(!get_cell(cur_x, cur_y, obj))
                {
                    cursor_out.x = cur_x;
                    cursor_out.y = cur_y;
                    return true;
                }
            }
        }
        cur_x--;
        cur_y++;
        for(int end_cursor_y = cur_y + side_size; cur_y < end_cursor_y; cur_y++ )
        {
            if(check_coord(cur_x, cur_y))
            {
                if(!get_cell(cur_x, cur_y, obj))
                {
                    cursor_out.x = cur_x;
                    cursor_out.y = cur_y;
                    return true;
                }
            }
        }
        cur_y--;
        cur_x--;
        for(int end_cursor_x = cur_x - side_size; cur_x > end_cursor_x; cur_x-- )
        {
            if(check_coord(cur_x, cur_y))
            {
                if(!get_cell(cur_x, cur_y, obj))
                {
                    cursor_out.x = cur_x;
                    cursor_out.y = cur_y;
                    return true;
                }
            }
        }
        cur_y--;
        cur_x++;
        for(int end_cursor_y = cur_y - side_size; cur_y > end_cursor_y; cur_y-- )
        {
            if(check_coord(cur_x, cur_y))
            {
                if(!get_cell(cur_x, cur_y, obj))
                {
                    cursor_out.x = cur_x;
                    cursor_out.y = cur_y;
                    return true;
                }
            }
        }
        side_size+=2;
        //simple check if this area didn't find free cell
        if(side_size > size_x*2 && side_size > size_y*2 )
        {
            return false;
        }
    }
}