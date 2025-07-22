#ifndef AVAILABLE_BUILDINGS_H
#define AVAILABLE_BUILDINGS_H

#include <string>
#include <map>

// Словарь который не содержит дубликатов
// Чем то он похож на магащин в котором мы выбираем покупки
// Каждый игрок моджет обратиться в массив к элементам, которые он может "купить"
// Делает он это при помощи ключа (своего номера)
class Available_Buildings {
public:
    std::multimap<int, std::string> Buildings;
    Available_Buildings();
    ~Available_Buildings();
    // Эта функция смотрит на баланс игрока и на его номер
    // После, она находит нужную постройку, и говорит, можно ее тебе строить или нет
    bool Check_Access(int Player_Number, std::string);
};



#endif //AVAILABLE_BUILDINGS_H
