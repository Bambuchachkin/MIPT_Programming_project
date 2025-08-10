#include "bot.h"

bot::bot(Map* MAP){
    map = MAP;
    money = map->get_Money();
    building_list = map->get_Building_list();
    available_buildings = map->get_Available_buildings();

}

bot::~bot() {

}

void bot::SuperFunction() {


}