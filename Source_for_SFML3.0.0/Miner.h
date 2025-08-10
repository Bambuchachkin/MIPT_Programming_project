#ifndef MINER_H
#define MINER_H
#include "building.h"


class Miner:public building {
    int want_to_move;
public:
    Miner(int x, int y, std::string texture);
    ~Miner() override;
    void Action(int i) override;
    bool get_Action() const override;
};



#endif //MINER_H
