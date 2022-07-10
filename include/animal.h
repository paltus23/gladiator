#ifndef ANIMAL_H
#define ANIMAL_H

#include <Unit.h>


class Animal_t : public Unit_t
{
    public:
        Animal_t(std::string name);
        virtual ~Animal_t();

    private:
};

#endif // ANIMAL_H
