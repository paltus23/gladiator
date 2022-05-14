#include "arena.h"
#include <stdlib.h>
#include "string.h"
Arena::Arena(int x, int y)
{
    floor_size.x = x;
    floor_size.y = y;
    cells = (void**)malloc(sizeof(void*)*floor_size.x*floor_size.y);
    memset(cells, 0, sizeof(void*)*floor_size.x*floor_size.y);
    overall_size.x = floor_size.x + 2;
    overall_size.y = floor_size.y + 2;
}

Arena::~Arena()
{
    free(cells);
}
//Помещает юнита на арену
result_t Arena::place_unit(Unit* unit, int x, int y)
{
    if(x >= floor_size.x)
        return RESULT_ERROR;
    if(y >= floor_size.y)
        return RESULT_ERROR;

    void ** cell = &cells[x + y*floor_size.x];
    if(*cell)
        return RESULT_ERROR;
    *cell = unit;

    unit->set_place(this,x,y);
    return RESULT_OK;
}

void Arena::print_units()
{
    string cc("Print names\n");
    cout << cc;
    for(void ** cell = cells; cell<&cells[floor_size.x*floor_size.y] ; cell++)
    {
        if(*cell)
        {
            Unit* unit = (Unit*)(*cell);
            cout << unit->name << "\n";
        }
    }
}
