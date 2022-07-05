#include "arena.h"
#include <stdlib.h>
#include "string.h"
Arena::Arena(int x, int y)
{
    size.x = x;
    size.y = y;
}

Arena::~Arena()
{
}
//�������� ����� �� �����
result_t Arena::place_unit(Unit* unit, int x, int y)
{
    if(x >= size.x)
        return RESULT_ERROR;
    if(y >= size.y)
        return RESULT_ERROR;

    unit->set_place(this,x,y);
    return RESULT_OK;
}

void Arena::print_units()
{
}
