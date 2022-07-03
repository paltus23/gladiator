#ifndef OCEAN_H
#define OCEAN_H

#include "types.h"
#include <iostream>

/// Ocean is rectangle object, which store islands. Water is 0 and islands is positive numbers.
/// Origin of coordinates is left-up corner
class Ocean
{
    public:
        Ocean(coord_t size);
        virtual ~Ocean();
        void create_random_isle(int num = 1, int cursor_x = -1, int cursor_y = -1, size_t area_size = 0);
        int add_isle(int x, int y, area_t isle);

        static void print(Ocean * ocean);
        void search_way_out(int cur_x, int cur_y, coord_t& cursor_out);

        inline int get_cell(int x, int y) {return Ocean_area[y][x];};
        inline void set_cell(int x, int y, int v) {Ocean_area[y][x] = v; /*printf("set_cell num = %d x = %2d y = %2d\n", v, x, y);*/}

        inline int get_cell(coord_t c) {return Ocean_area[c.y][c.x];};
        inline void set_cell(coord_t c, int x) {Ocean_area[c.y][c.x] = x;}
        
    protected:
        coord_t Size;
        area_t Ocean_area;// it's not a dogma for write with or without spaces sometimes


    private:
        void set_ocean_area(int x, int y, int v);
        int get_ocean_area(int x, int y);
};

#endif // OCEAN_H
