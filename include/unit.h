#ifndef UNIT_H
#define UNIT_H

#include "arena.h"
#include "types.h"

#include <iostream>
#include "string.h"

class Arena_t;

class Unit_t
{
    public:
        Unit_t(std::string _name = "__unnamed__");

        virtual ~Unit_t();
        result_t set_place(Arena_t* arena, unsigned x, unsigned y);
        std::string Name;
        virtual bool move(coord_t *coord);
        unsigned X, Y;
    private:
        Arena_t* Arena;
        int Health;
        int Stamina;


};

#endif // UNIT_H
