#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "description.h"
using namespace std;

void read_monster(npc_description *desc, std::ifstream &stream){
    desc->name_count = desc->description_count = 0;
    desc->color_count = desc->speed_count = 0;
    desc->abilities_count = desc->hit_count = 0;
    desc->damage_count = desc->symbol_count = 0;
    desc->rarity_count = 0;

    if(desc->next!="BEGIN"){
        do
        {
        stream >> desc->next;
        } while (desc->next != "BEGIN" && stream.peek() != EOF);
    }

    if(stream.peek() == EOF){return;}

    stream >> desc->next;

    if(desc->next!="MONSTER"){return;}

    int i;
    for(stream>>desc->next, i = 0; i<9; i++){
        if(desc->next=="NAME"){
            read_name(desc, stream);
        }
        else if(desc->next=="DESC"){
            read_description(desc, stream);
        }
        else if(desc->next=="COLOR"){
            read_color(desc, stream);
        }
        else if(desc->next=="SPEED"){
            read_speed(desc, stream);
        }
        else if(desc->next=="ABIL"){
            read_abilities(desc, stream);
        }
        else if(desc->next=="HP"){
            read_hitpoints(desc, stream);
        }
        else if(desc->next=="DAM"){
            read_damage(desc, stream);
        }
        else if(desc->next=="SYMB"){
            read_symbol(desc, stream);
        }
        else if(desc->next=="RRTY"){
            read_rarity(desc, stream);
        }
        else{
            //error
            return;
        }
        
    }    
    if(desc->next!="END"){
        return;
    }

    print_monster(desc);
}

void read_name(npc_description *desc, std::ifstream &stream){
    //if(desc->next == "NAME"){
        getline(stream, desc->name);
        delete_spaces(desc, stream);
        stream >> desc->next;
    //}
    //else{
    //    return;
    //}
}
void read_description(npc_description *desc, std::ifstream &stream){
    //if(desc->next == "DESC"){
        getline(stream, desc->name);
        delete_spaces(desc, stream);
        stream >> desc->next;
        desc->description_count++;
    // }
    // else{
    //     return;
    // }
}
void read_color(npc_description *desc, std::ifstream &stream){
    //if(desc->next == "COLOR"){
        getline(stream, desc->color);
        delete_spaces(desc, stream);
        stream >> desc->next;
        desc->color_count++;
    // }
    // else{
    //     return;
    // }
}
void read_hitpoints(npc_description *desc, std::ifstream &stream){
    //if(desc->next == "HITPOINTS"){
        read_dice(desc, &(desc->hitpoints), stream);
        delete_spaces(desc, stream);
        stream >> desc->next;
        desc->hit_count++;
    // }
    // else{
    //     return;
    // }
}
void read_damage(npc_description *desc, std::ifstream &stream){
    // if(desc->next == "DAM"){
        read_dice(desc, &(desc->damage), stream);
        delete_spaces(desc, stream);
        stream >> desc->next;
        desc->damage_count++;
    // }
    // else{
    //     return;
    // }
}
void read_symbol(npc_description *desc, std::ifstream &stream){
    // if(desc->next == "SYMB"){
        desc->symbol = stream.get();
        delete_spaces(desc, stream);
        stream >> desc->next;
        desc->symbol_count++;
    // }
    // else{
    //     return;
    // }
}
void read_rarity(npc_description *desc, std::ifstream &stream){
    // if(desc->next == "RRTY"){
        stream >> desc->next;
        // std::string *pt;
        // *pt = desc->next;
        sscanf((&(desc->next))->c_str(), "%u", &(desc->rarity));
        desc->rarity_count++;
        delete_spaces(desc, stream);
        stream >> desc->next;
    // }
    // else{
    //     return;
    // }
}
void read_speed(npc_description *desc, std::ifstream &stream){
    //if(desc->next == "SPEED"){
        read_dice(desc, &(desc->speed), stream);
        delete_spaces(desc, stream);
        stream >> desc->next;
        desc->speed_count ++;
    // }
    // else{
    //     return;
    // }
}
void read_abilities(npc_description *desc, std::ifstream &stream){
    //if(desc->next == "ABIL"){
        stream >> desc->next;
        // std::string *pt;
        // *pt = desc->next;
        sscanf((&(desc->next))->c_str(), "%u", &(desc->abilities));
        delete_spaces(desc, stream);
        stream >> desc->next;
        desc->abilities_count++;
    // }
    // else{
    //     return;
    // }
}
void read_dice(npc_description *desc, dice *dice, std::ifstream &stream){
    int32_t base;
    uint32_t number, sides;
    delete_spaces(desc, stream);
    if(stream.peek()=='\n'){return;}
    stream >> desc->next;
    // std::string *pt = new std::string;
    // *pt = desc->next;
    if(sscanf((&(desc->next))->c_str(), "%d+%ud%u", &base, &number, &sides)!=3){return;}
    dice->set_dice(base,number,sides);
    //delete pt;
}
void delete_spaces(npc_description *desc, std::ifstream &stream){
    while(isblank(stream.peek())){stream.get();}
}
void print_monster(npc_description *desc){
    if((desc->name_count==1)&&(desc->description_count==1)&&(desc->color_count==1)&&(desc->speed_count==1)&&(desc->abilities_count==1)&&(desc->hit_count==1)&&(desc->damage_count==1)&&(desc->symbol_count==1)&&(desc->rarity_count==1))
    {
        cout<<desc->name<<endl;
        cout<<desc->description<<endl;
        cout<<desc->color<<endl;
        cout<<desc->speed.base<<"+"<<desc->speed.number<<"d"<<desc->speed.sides<<endl;
        cout<<desc->description<<endl;
        cout<<desc->hitpoints.base<<"+"<<desc->hitpoints.number<<"d"<<desc->hitpoints.sides<<endl;
        cout<<desc->damage.base<<"+"<<desc->damage.number<<"d"<<desc->damage.sides<<endl;
        cout<<desc->symbol<<endl;
        cout<<desc->rarity<<endl;
        
    }
}
