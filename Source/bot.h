#ifndef BOT_H
#define BOT_H

#include "Map.h"

class bot {
    int money;
    Map* map;
    Building_List* building_list;
    Available_Buildings* available_buildings;

public:
    bot(Map* MAP);
    ~bot();
    void SuperFunction();
};



#endif //BOT_H
