#ifndef ARENA_H
#define ARENA_H

#include "unit.h"
#include "types.h"
#include <stdlib.h>
#include "string.h"

class Unit;

class Arena
{
    public:
        Arena(int x, int y);
        virtual ~Arena();

        result_t place_unit(Unit* , int, int);
        void print_units();

        void get_size(coord_t * s){memcpy(s, &Size, sizeof(coord_t)); }
        void get_coord(coord_t * s){memcpy(s, &Coord, sizeof(coord_t)); }

    private:
        coord_t Coord; /// coordinate of left top cell
        coord_t Size;
};

#endif // ARENA_H
