#include "ocean.h"
#include "dice.h"
#include <iostream>

Ocean::Ocean(coord_t size):Size(size)
{
    Ocean_area.resize(Size.x, std::vector<int>(Size.y));
    for(int i = 0; i < Size.x; i++)
    {
        for(int j = 0; j < Size.y; j++)
        {
            Ocean_area[i][j] = 0;
        }
    }
}

Ocean::~Ocean()
{
    //dtor
}

/**
* @brief create isle random form with area equals num
* @param in num - id of isle
* @param in cur_x - start x cursor
* @param in cur_y - start y cursor
*/
void Ocean::create_random_isle(int num, int cur_x, int cur_y, size_t area_size)
{
    cur_x = cur_x == -1 ? dice(Size.x) - 1 : cur_x;
    cur_y = cur_y == -1 ? dice(Size.y) - 1 : cur_y;

    if(area_size == 0)
        area_size = dice(Size.x * Size.y / 5);

    set_cell(cur_x, cur_y, num);
    area_size--;

    while(area_size)
    {
        //check available directions at this step
        int check_dir_possible[4]{0,0,0,0};
        int dice_cnt = 0;
        
        if( cur_x < (Size.x - 1) && get_cell(cur_x + 1,cur_y) == 0 ) // left
        {
            check_dir_possible[dice_cnt] = 0;
            dice_cnt++;
        }
        if( cur_x && get_cell(cur_x - 1,cur_y) == 0 ) // right
        {
            check_dir_possible[dice_cnt] = 1;
            dice_cnt++;
        }
        if( cur_y && get_cell(cur_x, cur_y - 1) == 0 ) // up
        {
            check_dir_possible[dice_cnt] = 2;
            dice_cnt++;
        }
        if( cur_y < (Size.y - 1) && get_cell(cur_x, cur_y + 1) == 0 ) // down
        {
            check_dir_possible[dice_cnt] = 3;
            dice_cnt++;
        }

        if(dice_cnt)
        {
            int dir = dice(dice_cnt) - 1;
            switch(check_dir_possible[dir])
            {
                case 0: //right
                {
                    cur_x++;
                    break;
                }
                case 1: //left
                {
                    cur_x--;
                    break;
                }
                case 2: //up
                {
                    cur_y--;
                    break;
                }
                case 3: //down
                {
                    cur_y++;
                    break;
                }
            }
            set_cell(cur_x, cur_y, num);
            area_size--;
        }
        else // search way out from stuck
        {
            coord_t cur_out;
            search_way_out(cur_x, cur_y, cur_out);
            cur_x = cur_out.x;
            cur_y = cur_out.y;
            set_cell(cur_x, cur_y, num);
            area_size--;
        }
    }
    return;
}

/**
* @brief find empty cell of isle
* @param in cur_x - start x cursor
* @param in cur_y - start y cursor
* @param out cursor_out - finded nearby empty cell
*/
void Ocean::search_way_out(int cur_x, int cur_y, coord_t& cursor_out)
{
    // does cursor is in available area
    auto check_coord = [this](int cur_x, int cur_y)
    {
        return !(cur_x < 0 || cur_x >= this->Size.x || cur_y < 0 || cur_y >= this->Size.y);
    };

    // Check first cell
    if(check_coord(cur_x, cur_y))
    {
        if(!get_cell(cur_x, cur_y))
        {
            cursor_out.x = cur_x;
            cursor_out.y = cur_y;
            return;
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
                if(!get_cell(cur_x, cur_y))
                {
                    cursor_out.x = cur_x;
                    cursor_out.y = cur_y;
                    return;
                }
            }
        }
        cur_x--;
        cur_y++;
        for(int end_cursor_y = cur_y + side_size; cur_y < end_cursor_y; cur_y++ )
        {
            if(check_coord(cur_x, cur_y))
            {
                if(!get_cell(cur_x, cur_y))
                {
                    cursor_out.x = cur_x;
                    cursor_out.y = cur_y;
                    return;
                }
            }
        }
        cur_y--;
        cur_x--;
        for(int end_cursor_x = cur_x - side_size; cur_x > end_cursor_x; cur_x-- )
        {
            if(check_coord(cur_x, cur_y))
            {
                if(!get_cell(cur_x, cur_y))
                {
                    cursor_out.x = cur_x;
                    cursor_out.y = cur_y;
                    return;
                }
            }
        }
        cur_y--;
        cur_x++;
        for(int end_cursor_y = cur_y - side_size; cur_y > end_cursor_y; cur_y-- )
        {
            if(check_coord(cur_x, cur_y))
            {
                if(!get_cell(cur_x, cur_y))
                {
                    cursor_out.x = cur_x;
                    cursor_out.y = cur_y;
                    return;
                }
            }
        }
        side_size++;
    }
}
/**
* @brief
* @param in x is left coordinate of isle object in ocean
* @param in y is top coordinate of isle object in ocean
* @param in isle object of adding isle
* @return -1 if isle not added else 1 if added
*/
int Ocean::add_isle(int x, int y, area_t isle)
{
    if(x < 0 || y < 0 || x >= Size.x || y >= Size.y) return -1;

    for(int i = 0; i < isle.size() && (y + i) < Ocean_area.size(); i++)
    {
        for(int j = 0; j < isle[i].size() && (x + j) < Ocean_area[y + i].size(); j++)
        {
            Ocean_area[y + i][x + j] = isle[i][j];
        }
    }

    return 1;
}

/**
 * @brief
 * @param 
 */
void Ocean::print(Ocean * ocean)
{
    for(std::vector<int> y : ocean->Ocean_area)
    {
        for(int x : y)
        {
            printf("%d",x);
        }
        printf("\n");
    }

}


