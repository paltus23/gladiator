#ifndef ROOM_H
#define ROOM_H

#include "unit.h"
#include "types.h"
#include <stdlib.h>
#include <list>
#include "string.h"

class Unit_t;

class RandomSpace2d
{
    public:
    enum type_t
    {
        DEFAULT_RANDOM
    };

};


class Room_t
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
        std::vector< std::vector<Room_t::cell_t> > Cells2;
        std::list<Unit_t*> Unit_list;

        Room_t(int x, int y);
        virtual ~Room_t();


        result_t place_unit(Unit_t* , int, int);
        void print_units();

        void get_size(coord_t * s){memcpy(s, &Size, sizeof(coord_t)); }
        void get_coord(coord_t * s){memcpy(s, &Coord, sizeof(coord_t)); }
        void simple_construct();
        void create_random(RandomSpace2d::type_t type = RandomSpace2d::DEFAULT_RANDOM);

        void create_random_default();
    private:
        coord_t Coord; // coordinate of left top cell
        const coord_t Size;

        void decimate_field(bool *field, int x, int y);
        void construct_from_bool_field(bool * field, int x, int y);
};

#endif // ROOM_H
