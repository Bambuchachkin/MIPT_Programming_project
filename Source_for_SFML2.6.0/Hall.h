#ifndef HALL_H
#define HALL_H
#include "building.h"


class Hall:public building{
    bool want_to_create;
public:
    Hall(int x, int y, std::string texture);
    ~Hall() override;
    void Action(int i) override;
    bool get_Action() const override;
};



#endif //HALL_H
