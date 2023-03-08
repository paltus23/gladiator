#include "unit.h"
#include "types.h"

Unit_t::Unit_t(std::string name):
    Name(name),
    Room(nullptr),
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
 * @brief place unit in room
 * @param in room - 
 * @param in x - coordinate x of unit
 * @param in y - coordinate y of unit
*/
void Unit_t::set_place(Room_t* room, int x, int y)
{
    Room = room;
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
    coord_t room_size;
    Room->get_size(&room_size);

    if(coord->x >= 0 &&
    coord->y >= 0 &&
    coord->x < room_size.x &&
    coord->y < room_size.y )
    {
        auto cell = Room->Cells2[coord->x][coord->y];
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