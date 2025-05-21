#include "Hall.h"
#include <iostream>

Hall::Hall(int x, int y, std::string texture) : building(x, y, texture) {
    health = 1000;
    ability_unit = true;
    want_to_create = false;
    std::cout<<"Hall have been created"<<'\n';

    buffer.loadFromFile("../Sound/Hall.wav");
    sound.setVolume(600);
    sound.play();
}

Hall::~Hall() {
    delete Sprite;
    std::cout<<"Hall have been destroyed"<<'\n';
}

void Hall::Action(int i) {
    if (i==1) {
        want_to_create = true;
    } else {
        want_to_create = false;
    }
}

bool Hall::get_Action() const {
    return want_to_create;
}
