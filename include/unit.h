#ifndef UNIT_H
#define UNIT_H

#include "arena.h"
#include "types.h"

#include <iostream>
#include "string.h"
using namespace std;
class Arena;

class Unit
{
    public:
        Unit(string _name = "__unnamed__");

        virtual ~Unit();
        result_t set_place(Arena* _arena, unsigned _x, unsigned _y);
        string name;

    private:
        Arena* arena;
        unsigned x, y;
        int health;
        int stamina;


};

#endif // UNIT_H
