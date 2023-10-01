#include <ctime>
#include <cstdlib>
#include "dice.h"

void dice_init()
{
    std::srand(std::time(0)); //use current time as seed for random generator
    std::rand();
}

/** \brief  make a roll of a dice
* \param [in] how many edges have dice
* \return result of roll in range from 1 to *base*
*/
int dice(int base)
{
    /** here we have a problem with not equal probability for different cases in dice.
    * Let's say what rand() have uniform distribution. Then we divide range of possible
    * numbers into equal ranges. But since we work with range integers, after divide and round,
    * this ranges have different count of numbers.
    * So we have different probability for different ranges.
    * For avoid this case we decrease of possible cases and save it in variable actual_rand_max
    */
    int actual_rand_max = RAND_MAX - (RAND_MAX + 1) % base;

    int random_variable;
    while( (random_variable = std::rand()) > actual_rand_max);
        
    random_variable = random_variable%base + 1;

    return random_variable;
}

