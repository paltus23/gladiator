#ifndef OCEAN_H
#define OCEAN_H

#include "types.h"

#include <vector>
class Ocean
{
    public:
        Ocean(coord_t size);
        virtual ~Ocean();
        void create_random_isle(int num = 1, int cursor_x = -1, int cursor_y = -1);
        int add_isle(int x, int y, std::vector< std::vector<int> > isle);
    protected:
        coord_t Size;
        std::vector< std::vector<int> > Ocean_area;// it's not a dogma for write with or without spaces sometimes


    private:
        void search_way_out(int cur_x, int cur_y, coord_t& cursor_out);
};

#endif // OCEAN_H
