#ifndef GLADIATOR_H
#define GLADIATOR_H

#include <unit.h>
#include "string.h"
#include "types.h"

class Gladiator_t : public Unit_t
{
    public:
        Gladiator_t(std::string _name);
        virtual ~Gladiator_t();

    private:
};

#endif // GLADIATOR_H
