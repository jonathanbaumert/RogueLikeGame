#ifndef DESCRIPTION_H
#define DESCRIPTION_H
#include <stdint.h>
#undef swap
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include "dims.h"
//#include "npc.h"
#include "dice.cpp"
# include <stdint.h>
#include <iostream>
//class dungeon_t;
class dice;
// class npc_t;
class npc_description
{
public:
    dice speed, hitpoints, damage;
    std::string name, description, color, next;
    uint32_t abilities, rarity;
    int speed_count, hit_count, damage_count, name_count,description_count, color_count, abilities_count, rarity_count, symbol_count;
    
    char symbol;
    //npc_t npc;
    void set_description(const std::string &name, 
                         const std::string &description,
                         const std::string &color,
                         const dice speed,
                         const uint32_t abilities,
                         const dice hitpoints,
                         const dice damage,
                         const char symbol,
                         const uint32_t rarity);
    
     
};
void read_monster(npc_description *desc, std::ifstream &stream);
void print_monster(npc_description *desc);
void read_name(npc_description *desc, std::ifstream &stream);
void read_description(npc_description *desc, std::ifstream &stream);
void read_color(npc_description *desc, std::ifstream &stream);
void read_hitpoints(npc_description *desc, std::ifstream &stream);
void read_damage(npc_description *desc, std::ifstream &stream);
void read_symbol(npc_description *desc, std::ifstream &stream);
void read_rarity(npc_description *desc, std::ifstream &stream);
void read_speed(npc_description *desc, std::ifstream &stream);
void read_abilities(npc_description *desc, std::ifstream &stream);
void delete_spaces(npc_description *desc, std::ifstream &stream);
void read_dice(npc_description *desc, dice *dice, std::ifstream &stream);

#endif