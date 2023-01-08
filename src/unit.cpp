#include "unit.h"
#include "types.h"

Unit_t::Unit_t(std::string name):
    Name(name),
    Arena(nullptr),
    X(-1),
    Y(-1)
{
//ctor
}

Unit_t::~Unit_t()
{
    //dtor
}
/**
 * @brief place unit in arena
 * @param in arena - 
 * @param in x - coordinate x of unit
 * @param in y - coordinate y of unit
*/
void Unit_t::set_place(Room_t* arena, int x, int y)
{
    Arena = arena;
    X = x;
    Y = y;

    return;
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
        if(cell != Room_t::NOTHING && cell != Room_t::WALL)
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