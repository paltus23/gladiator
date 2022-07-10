#include "arena.h"
#include <stdlib.h>
#include "string.h"
Arena_t::Arena_t(int x, int y)
{
    Size.x = x;
    Size.y = y;
}

Arena_t::~Arena_t()
{
}
//Place unit on arena
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
