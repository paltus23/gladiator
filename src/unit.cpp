#include "unit.h"
#include "types.h"

Unit::Unit(string _name):name(_name)
{
//ctor
}

Unit::~Unit()
{
    //dtor
}

result_t Unit::set_place(Arena* _arena, unsigned _x, unsigned _y)
{
    arena = _arena;
    x = _x;
    y = _y;

    return RESULT_OK;
}
