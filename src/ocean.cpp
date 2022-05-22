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
* @brief
* @param in num - size of isle
* @param in cursor_x - start x cursor
* @param in cursor_y - start y cursor
*/
void Ocean::create_random_isle(int num, int cursor_x, int cursor_y)
{
    cursor_x = cursor_x == -1 ? dice(Size.x) - 1 : cursor_x;
    cursor_y = cursor_y == -1 ? dice(Size.y) - 1 : cursor_y;

    int area_size = dice(Size.x * Size.y / 5);

    Ocean_area[cursor_x][cursor_y] = num;
    area_size--;

    while(area_size)
    {

        int check_dir_possible[4]{0,0,0,0};
        int dice_cnt = 0;
        if( cursor_x < Size.x && Ocean_area[cursor_x + 1][cursor_y] == 0 ) // left
        {
            dice_cnt++;
            check_dir_possible[3 - dice_cnt] = 0;
        }
        if( cursor_x || Ocean_area[cursor_x - 1][cursor_y] == 0 ) // right
        {
            dice_cnt++;
            check_dir_possible[3 - dice_cnt] = 1;
        }
        if( cursor_y || Ocean_area[cursor_x][cursor_y - 1] == 0 ) // up
        {
            dice_cnt++;
            check_dir_possible[3 - dice_cnt] = 2;
        }
        if( cursor_y < Size.y || Ocean_area[cursor_x][cursor_y + 1] == 0 ) // down
        {
            dice_cnt++;
            check_dir_possible[3 - dice_cnt] = 3;
        }

        if(dice_cnt)
        {
            int dir = dice(dice_cnt) - 1;
            switch(check_dir_possible[dir])
            {
                case 0: //right
                {
                    cursor_x++;
                    break;
                }
                case 1: //left
                {
                    cursor_x--;
                    break;
                }
                case 2: //up
                {
                    cursor_y--;
                    break;
                }
                case 3: //down
                {
                    cursor_y++;
                    break;
                }
            }
            area_size--;
        }
        else // search way out from stuck
        {
            int dir = dice(4) - 1;
            int _cursor_x = cursor_x;
            int _cursor_y = cursor_y;
            switch(dir)
            {
                case 0: //right
                {
                    for(;_cursor_y < Size.y; _cursor_y++)
                    {
                        for(;_cursor_x < Size.x; _cursor_x++)
                        {
                            if(Ocean_area[_cursor_x][_cursor_y] == 0)
                            {
                                int _cursor_x = cursor_x;
                                int _cursor_y = cursor_y;
                                break;
                            }
                        }
                        _cursor_y++;
                        for(;_cursor_x >= 0; _cursor_x--)
                        {
                            if(Ocean_area[_cursor_x][_cursor_y] == 0)
                            {
                                int _cursor_x = cursor_x;
                                int _cursor_y = cursor_y;
                                break;
                            }
                        }
                        _cursor_x = 0;
                    }
                    break;
                }
                case 1: //left
                {
                    cursor_x--;
                    break;
                }
                case 2: //up
                {
                    cursor_y--;
                    break;
                }
                case 3: //down
                {
                    cursor_y++;
                    break;
                }
            }
        }
    }
}

/**
* @brief
* @param in cur_x - start x cursor
* @param in cur_y - start y cursor
* @param out cursor_out - finded nearby empty dot
*/
void Ocean::search_way_out(int cur_x, int cur_y, coord_t& cursor_out)
{
    auto check_coord = [this](int cur_x, int cur_y)
    {
        return !(cur_x < 0 || cur_x >= this->Size.x || cur_y < 0 || cur_y >= this->Size.y);
    };
    int side_size = 2;
    cur_y--;
    while(1)
    {
        for(int end_cursor_x = cur_x + side_size; cur_x < end_cursor_x; cur_x++ )
        {
            if(check_coord(cur_x, cur_y))
            {
                if(!Ocean_area[cur_x][cur_y])
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
                if(!Ocean_area[cur_x][cur_y])
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
                if(!Ocean_area[cur_x][cur_y])
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
                if(!Ocean_area[cur_x][cur_y])
                {
                    cursor_out.x = cur_x;
                    cursor_out.y = cur_y;
                    return;
                }
            }
        }
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

    for(int i = 0; i < isle.size() && (x + i) < Ocean_area.size(); i++)
    {
        for(int j = 0; j < isle[i].size() && (y + j) < Ocean_area[x + i].size(); j++)
        {
            Ocean_area[x + i][y + j] = isle[i][j];
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
    for(std::vector<int> x : ocean->Ocean_area)
    {
        for(int y : x)
        {
            printf("%d",y);
        }
        printf("\n");
    }

}