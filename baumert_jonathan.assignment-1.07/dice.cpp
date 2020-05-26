#ifndef DICE_H
#define DICE_H

#include <cstdlib>
#undef swap
#include "utils.h"
#include <stdint.h>
#include <iostream>
#include "dims.h"
class dice
{
  public:
    int32_t base;
    uint32_t number, sides;

    inline void set_dice(int32_t base, uint32_t number, uint32_t sides)
    {
        this->base = base;
        this->number = number;
        this->sides = sides;
    }
    int32_t roll(void) const
    {
        int32_t roll_value;
        roll_value = base;
        uint32_t i;

        for (i = 0; i < number; i++)
        {
            roll_value += rand_range(1, sides);
        }
        return roll_value;
    }
};

// int32_t dice::roll(void) const
// {
//     int32_t roll_value;
//     roll_value = base;
//     uint32_t i;

//     for (i = 0; i < number; i++)
//     {
//         roll_value += rand_range(1, sides);
//     }
//     return roll_value;
// }
 #endif