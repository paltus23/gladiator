#ifndef ANIMAL_H
#define ANIMAL_H

#include <Unit.h>


class Animal : public Unit
{
    public:
        Animal(string _name);
        virtual ~Animal();

    private:
};

#endif // ANIMAL_H
