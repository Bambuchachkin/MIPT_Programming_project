#ifndef BARRAK_H
#define BARRAK_H
#include "building.h"


class barrak:public building{
    bool want_to_create;
public:
    barrak(int x, int y, std::string texture);
    ~barrak() override;
    void Action(int i) override;
    bool get_Action() const override;
};



#endif //BARRAK_H
