#ifndef ARENA_H
#define ARENA_H

#include "unit.h"
#include "types.h"
#include <stdlib.h>
#include "string.h"

class Unit;
//представляет из себя прямоугольное поле указателей на объекты-юниты
//пробегаясь по этому полю можно быстро выяснять кто есть на арене и печатать имена
class Arena
{
    public:
        Arena(int _x, int _y);
        virtual ~Arena();

        result_t place_unit(Unit* unit, int x, int y);
        void print_units();

        void get_overall_size(coord_t * s){memcpy(s, &overall_size, sizeof(coord_t)); }
        void get_floor_size(coord_t * s){memcpy(s, &floor_size, sizeof(coord_t)); }
        void get_coord(coord_t * s){memcpy(s, &coord, sizeof(coord_t)); }

    protected:

    private:
        coord_t coord; /// coordinate of left top cell
        coord_t floor_size;
        coord_t overall_size; //начало координат слева вверху
        void ** cells;
};

#endif // ARENA_H
