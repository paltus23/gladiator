#ifndef ARENA_H
#define ARENA_H

#include "unit.h"
#include "types.h"
#include <stdlib.h>
#include <list>
#include "string.h"

class Unit_t;

class Arena_t
{
    public:

        enum cell_t
        {
            NOTHING,
            FLOOR,
            WALL
        };

        cell_t **Cells;
        cell_t *Cells_cols;
        std::vector< std::vector<Arena_t::cell_t> > Cells2;
        std::list<Unit_t*> Unit_list;

        Arena_t(int x, int y);
        virtual ~Arena_t();


        result_t place_unit(Unit_t* , int, int);
        void print_units();

        void get_size(coord_t * s){memcpy(s, &Size, sizeof(coord_t)); }
        void get_coord(coord_t * s){memcpy(s, &Coord, sizeof(coord_t)); }
        void simple_construct();

    private:
        coord_t Coord; // coordinate of left top cell
        const coord_t Size;
};

#endif // ARENA_H
