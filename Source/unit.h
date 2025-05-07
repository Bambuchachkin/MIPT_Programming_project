#ifndef UNIT_H
#define UNIT_H
#include "building.h"


class unit:public building {
    int whant_to_move;
public:
    unit(int x, int y, std::string texture);
    ~unit() override;
    void Action(int i) override;
    bool get_Action() const override;
};



#endif //UNIT_H
