#include "room.h"
#include <stdlib.h>
#include "string.h"
/**
 * @brief constructor of Room_t
 * @param in x - size of x
 * @param in y - size of y
*/
Room_t::Room_t(int x, int y) : Size((coord_t){x,y})
{
    Cells = (cell_t**)malloc(Size.x * sizeof(cell_t*));
    for(auto i = 0; i < Size.x; i++)
    {
        Cells[i] = (cell_t*)malloc(Size.y * sizeof(cell_t));
        if(Cells[i])
            memset(Cells[i], NOTHING, Size.y * sizeof(cell_t));
        else
            break;
    }

    Cells2.resize(Size.x);
    ///@todo
    //what happpend if OS do not allocate memory for vector??
    for(auto i = 0; i < Size.x; i++)
    {
        Cells2[i].resize(Size.y, NOTHING);
    }

}
/// Destructor
Room_t::~Room_t()
{
}
/**
 * @brief Place unit in room
 * @param in unit - pointer to unit
 * @param in x - unit's x coordinate
 * @param in y - unit's y coordinate
*/
result_t Room_t::place_unit(Unit_t* unit, int x, int y)
{
    if(x >= Size.x)
        return RESULT_ERROR;
    if(y >= Size.y)
        return RESULT_ERROR;

    unit->set_place(this,x,y);
    return RESULT_OK;
}

void Room_t::print_units()
{
}
/**
 * @brief construct rectangle room with walls using all space
*/
void Room_t::simple_construct()
{
    //left and right walls
    for(auto i = 0; i < Size.y; i++)
    {
        Cells2[0][i] = WALL;
        Cells2.back()[i] = WALL;
    }
    //up and down walls
    for(auto i = 0; i < Size.x; i++)
    {
        Cells2[i][0] = WALL;
        Cells2[i].back() = WALL;
    }
    //floor
    for(auto i = 1; i < Size.x - 1; i++)
    {
        for(auto j = 1; j < Size.y - 1; j++)
        {
            Cells2[i][j] = FLOOR;
        }
    }
}


/**
 * @brief create random room with walls using all space
*/
void Room_t::create_random(RandomSpace2d::type_t type)
{
    //left and right walls
    switch(type)
    {
    case (RandomSpace2d::DEFAULT_RANDOM):
    {
        create_random_default();
        break;
    }
    default:break;
    }
}

#include <ctime>
#include <cstdlib>
void Room_t::create_random_default()
{
    auto time = std::time(0);
    printf("                           Time %d", time);
    std::srand(time); //use current time as seed for random generator
    std::rand();

    bool field[Size.x][Size.y];
    /// fill with "false"
    for(auto i = 0; i < Size.x; i++)
    {
        memset(field[i], false, Size.y*sizeof(bool));
    }
    
    for(auto i = 1; i < Size.x - 1; i++)
    {
        for(auto j = 1; j < Size.y - 1; j++)
        {
            field[i][j] = (std::rand() > RAND_MAX/2);
        }
    }

    decimate_field( (bool*)field, Size.x, Size.y);

    for(auto i = 0; i < Size.x; i++)
    {
        for(auto j = 0; j < Size.y; j++)
        {

            if(field[i][j])
            {
                Cells2[i][j] = FLOOR;
            }
            else
            {
                int val = field[i-1][j] + field[i+1][j] 
                + field[i][j-1] + field[i][j+1]
                + field[i-1][j-1] + field[i+1][j-1] 
                + field[i+1][j+1] + field[i-1][j+1];
                if(val)
                    Cells2[i][j] = WALL;
                else
                    Cells2[i][j] = NOTHING;
            }

        }
    }

}

void Room_t::decimate_field(bool *field, int x, int y)
{
    bool new_field[x][y];

    for(int i = 1; i < x - 1; i++)
    {
        for(int j = 1; j < y - 1; j++)
        {
            int val = field[(i-1)*y + j] + field[ (i+1)*y + j] 
                    + field[ (i)*y + j-1] + field[ (i)*y + j+1]
                    + field[ (i-1)*y + j-1] + field[ (i+1)*y + j-1] 
                    + field[ (i+1)*y + j+1] + field[ (i-1)*y + j+1];
            if( val > 2 && val < 6)
                new_field[x][y] = true;
            else
                new_field[x][y] = false;
        }
    }

    memcpy(field, new_field, sizeof(bool)*x*y);


}
