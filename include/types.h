#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <vector>

enum result_t
{
    RESULT_OK,
    RESULT_ERROR
};

struct coord_t
{
    int x,y;
};

typedef std::vector< std::vector<int> > area_t;
#endif // TYPES_H_INCLUDED
