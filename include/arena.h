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

        void get_overall_size(coord_t * s){memcpy(s, &overall_size, sizeof(coord_t)); }
        void get_floor_size(coord_t * s){memcpy(s, &floor_size, sizeof(coord_t)); }

    protected:

    private:
        coord_t floor_size;
        coord_t overall_size; //начало координат слева вверху
        void ** cells;
};

#endif // ARENA_H
