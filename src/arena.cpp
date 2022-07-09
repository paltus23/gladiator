#include "arena.h"
#include <stdlib.h>
#include "string.h"
Arena::Arena(int x, int y)
{
    Size.x = x;
    Size.y = y;
}

Arena::~Arena()
{
}
//Place unit on arena
result_t Arena::place_unit(Unit* unit, int x, int y)
{
    if(x >= Size.x)
        return RESULT_ERROR;
    if(y >= Size.y)
        return RESULT_ERROR;

    unit->set_place(this,x,y);
    return RESULT_OK;
}

void Arena::print_units()
{
}
