#include "unit.h"
#include <iostream>
#include <SFML/Audio.hpp>

unit::unit(int x, int y, std::string texture) : building(x, y, texture) {
    // Teg = teg;
    health = 300;
    std::cout << "Unit have been created" << '\n';
    damage = 100;
    if (!bothBuffer.loadFromFile("../Sound/both.wav")) {
        std::cerr << "Ошибка загрузки звука!" << std::endl;
    } else {
        bothSound.setBuffer(bothBuffer);
        bothSound.play();
    }
}
unit::~unit() {
    std::cout<<"Unit have been destroyed"<<'\n';
}

void unit::Action(int i) {
    if (i==1) {
        want_to_move = true;
    } else {
        want_to_move = false;
    }
}

bool unit::get_Action() const {
    return want_to_move;
}