#include "hit_combos.h"

/**
 * everu hit map consists of three types of cells.
 * player cell is 0
 * hit cells is positive numbers. They reflect to order of steps
 * empty cell is -1
*/

typedef std::vector< std::vector<int> > hit_map_t;

const hit_map_t straight_hit
{
    {0,1}
};

const hit_map_t left_hit
{
    {0, 3},
    {1, 2}
};


Hit_combos_t::Hit_combos_t()
{
    
}

Hit_combos_t::~Hit_combos_t()
{
    
}