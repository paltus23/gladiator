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
        Arena(int _x, int _y);
        virtual ~Arena();

        result_t place_unit(Unit* unit, int x, int y);
        void print_units();

        void get_size(coord_t * s){memcpy(s, &size, sizeof(coord_t)); }
        void get_coord(coord_t * s){memcpy(s, &coord, sizeof(coord_t)); }

    protected:

    private:
        coord_t coord; /// coordinate of left top cell
        coord_t size;
};

#endif // ARENA_H
