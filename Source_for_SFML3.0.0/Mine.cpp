#include "Mine.h"
#include <iostream>

Mine::Mine(int x, int y, std::string texture) : building(x, y, texture) {
    health = 99999;
    ability_money = true;
    give_money = false;
    std::cout<<"Mine have been created"<<'\n';
}

Mine::~Mine() {
    delete Sprite;
    std::cout<<"Mine have been destroyed"<<'\n';
}

void Mine::Action(int i) {
    if (i==1) {
        give_money = true;
    } else {
        give_money = false;
    }
}

bool Mine::get_Action() const {
    return give_money;
}


