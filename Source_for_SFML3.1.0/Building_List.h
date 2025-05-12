#ifndef BUILDING_LIST_H
#define BUILDING_LIST_H
#include <string>
#include <vector>
#include <map>
#include "building.h"
#include <iostream>

// Словарь, содержащий сведения о всех постройках на карте.
// (Он знает координаты, текстуры и владельцев каждого объекта)
// Ключ элемента = номеру игрока
// Текстура хранится в качестве строки указывающий на место хранения текстуры (папка Textures)

class Building_List {
    // std::multimap<std::string, building*> Buildings;
    int PLAYER_NUMBER;
public:
    std::multimap<std::string, building*> Buildings;
    Building_List();
    ~Building_List();
    // Мы умеем добавлять новую постройку на карту
    bool Add_Building(int x, int y, std::string texture);
    // Мы умеем их удалять
    bool Destroy_Building(int x_coord, int y_coord, std::string key);
    // Если требуется обратиться к конкретному building снаружи, мы можем предоставить указатель на него
    building* Find_Building(int x_coord, int y_coord, std::string key);
    building* Find_Building(std::string key);
    bool Check_Health(int x_coord, int y_coord, std::string key);
    void Hit(int x_coord, int y_coord);
    bool Move(int x_coord, int y_coord, int PLAYER_NUMBER);
    bool Select_Building(int x_coord, int y_coord, std::string texture);
    int Count_Buildings(std::string key);
    int Stonks(int PLAYER_NUMBER);
    void Set_Global_Color();
    void Global_Diactivate();
    building* get_Sprite_Active_Unit();
    void set_PLAYER_NUMBER(int PLAYER_NUMBER);
    building* Find_Anamy(int x, int y);
    bool Hit (building* Building, int x, int y, int damage);
    bool contains(building* build); // Проверка существования здания в списке
    // void Check_Health(building* Building);
};



#endif //BUILDING_LIST_H