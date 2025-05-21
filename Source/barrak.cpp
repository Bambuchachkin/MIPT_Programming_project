#include "barrak.h"
#include <iostream>

barrak::barrak(int x, int y, std::string texture) : building(x, y, texture) {
    health = 500;
    ability_unit = true;
    want_to_create = false;
    std::cout<<"Barrak have been created"<<'\n';

    buffer.loadFromFile("../Sound/both.wav");
    sound.setVolume(20);
    sound.play();
}

barrak::~barrak() {
    delete Sprite;
    std::cout<<"Barrak have been destroyed"<<'\n';
}

void barrak::Action(int i) {
    if (i==1) {
        want_to_create = true;
    } else {
        want_to_create = false;
    }
}

bool barrak::get_Action() const {
    return want_to_create;
}


