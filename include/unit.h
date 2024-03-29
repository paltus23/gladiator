#ifndef UNIT_H
#define UNIT_H

#include "room.h"
#include "types.h"

#include <iostream>
#include "string.h"

class Room_t;

class Unit_t
{
    public:
        Unit_t(std::string _name = "__unnamed__");
        virtual ~Unit_t();

        void set_place(Room_t* room, int x, int y);   ///> place unit in room
        std::string Name;                               ///> name of unit
        virtual bool move(coord_t *coord);              ///> move unit to new coordinate
        int X, Y;                                       ///> coordinate of unit
    protected:
        Room_t* Room;                                 ///> which room have unit
        int Health;                                     ///> health point of unit
        int Stamina;                                    ///> stamina points of unit


};

#endif // UNIT_H
