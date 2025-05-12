#include "Miner.h"
#include <iostream>

Miner::Miner(int x, int y, std::string texture) : building(x, y, texture) {
    // Teg = teg;
    health = 1000;
    std::cout<<"Unit have been created"<<'\n';
    damage = 1000;
}

Miner::~Miner() {
    std::cout<<"Unit have been destroyed"<<'\n';
}

void Miner::Action(int i) {
    if (i==1) {
        want_to_move = true;
    } else {
        want_to_move = false;
    }
}

bool Miner::get_Action() const {
    return want_to_move;
}