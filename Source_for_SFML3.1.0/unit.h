#ifndef UNIT_H
#define UNIT_H
#include "building.h"
#include <SFML/Audio.hpp>


class unit:public building {
    int want_to_move;
    sf::SoundBuffer bothBuffer;
    sf::Sound bothSound;
public:
    unit(int x, int y, std::string texture);
    ~unit() override;
    void Action(int i) override;
    bool get_Action() const override;
};



#endif //UNIT_H
