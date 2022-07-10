#include "unit.h"
#include "types.h"

Unit_t::Unit_t(std::string name):Name(name)
{
//ctor
}

Unit_t::~Unit_t()
{
    //dtor
}

result_t Unit_t::set_place(Arena_t* arena, unsigned x, unsigned y)
{
    Arena = arena;
    X = x;
    Y = y;

    return RESULT_OK;
}
