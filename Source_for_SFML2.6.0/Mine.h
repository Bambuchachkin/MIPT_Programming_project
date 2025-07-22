#ifndef MINE_H
#define MINE_H
#include "building.h"


class Mine:public building{
    bool give_money;
public:
    Mine(int x, int y, std::string texture);
    ~Mine() override;
    void Action(int i) override;
    bool get_Action() const override;
};



#endif //MINE_H
