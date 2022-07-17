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
/**
 * @brief move unit in room
 * @param coord in/out - coordinate of new position
 * @return if the move happened, return true
*/
bool Unit_t::move(coord_t *coord)
{
    coord_t arena_size;
    Arena->get_size(&arena_size);

    if(coord->x >= 0 &&
    coord->y >= 0 &&
    coord->x < arena_size.x &&
    coord->y < arena_size.y )
    {
        auto cell = Arena->Cells2[coord->x][coord->y];
        if(cell != Arena_t::NOTHING && cell != Arena_t::WALL)
        {
            X = coord->x; 
            Y = coord->y;
            return true;
        }
    }
    coord->x = X; 
    coord->y = Y;
    return false;
};