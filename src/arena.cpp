#include "arena.h"
#include <stdlib.h>
#include "string.h"
/**
 * @brief constructor of Arena_t
 * @param in x - size of x
 * @param in y - size of y
*/
Arena_t::Arena_t(int x, int y) : Size((coord_t){x,y})
{
    Cells = (cell_t**)malloc(Size.x * sizeof(cell_t*));
    for(auto i = 0; i < Size.x; i++)
    {
        Cells[i] = (cell_t*)malloc(Size.y * sizeof(cell_t));
        if(Cells[i])
            memset(Cells[i], NOTHING, Size.y * sizeof(cell_t));
        else
            break;
    }

    Cells2.resize(Size.x);
    //what happpend if OS do not allocate memory for vector??
    for(auto i = 0; i < Size.x; i++)
    {
        Cells2[i].resize(Size.y, NOTHING);
    }

}

Arena_t::~Arena_t()
{
}
/**
 * @brief Place unit on arena
 * @param in unit - pointer to unit
 * @param in x - unit's x coordinate
 * @param in y - unit's y coordinate
*/
result_t Arena_t::place_unit(Unit_t* unit, int x, int y)
{
    if(x >= Size.x)
        return RESULT_ERROR;
    if(y >= Size.y)
        return RESULT_ERROR;

    unit->set_place(this,x,y);
    return RESULT_OK;
}

void Arena_t::print_units()
{
}
/**
 * @brief construct rectangle room with walls using all space
*/
void Arena_t::simple_construct()
{
    //left and right walls
    for(auto i = 0; i < Size.y; i++)
    {
        Cells2[0][i] = WALL;
        Cells2.back()[i] = WALL;
    }
    //up and down walls
    for(auto i = 0; i < Size.x; i++)
    {
        Cells2[i][0] = WALL;
        Cells2[i].back() = WALL;
    }
    //floor
    for(auto i = 1; i < Size.x - 1; i++)
    {
        for(auto j = 1; j < Size.y - 1; j++)
        {
            Cells2[i][j] = FLOOR;
        }
    }
}