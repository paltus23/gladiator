#pragma once
#include "types.h"
/**
* @brief find exit from stuck
* @param in obj - object in which searching
* @param in cur_x - start x cursor
* @param in cur_y - start y cursor
* @param in size_x - size of area x
* @param in size_y - size of area y
* @param in get_cell - function to check cell in area
* @param in,out cursor_out - finded nearby empty cell
*/
bool search_way_out(void* obj,
                    int cur_x, 
                    int cur_y, 
                    int size_x, 
                    int size_y, 
                    coord_t& cursor_out, 
                    bool (*get_cell)(int,int, void*) );