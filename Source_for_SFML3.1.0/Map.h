#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Cell.h"
#include "Building_List.h"
#include "Available_Buildings.h"
#include "Health.h"

class Map{
    unsigned int Size;
    float SCALE;
    float ZERO_X;
    float ZERO_Y;
    float CELL_WIDTH;
    float CELL_HEIGHT;
    int PLAYER_NUMBER;
    Building_List* building_list;
    Available_Buildings* available_buildings;
    std::string BUILDING_TEXTURE; // Здание, которое мы хотим создать
    int BUILDING_COST;
    std::vector<int> MONEY;
    float Sprite_Flactuation[2];
    std::vector<Health*> healthDisplays; // Список для хранения Health

public:
    std::vector<std::vector<Cell*>> Cells_Data;
    Map(unsigned int Map_Size, std::string Map_Texture);
    ~Map();
    unsigned int Get_Size() const;
    std::vector<int> get_pressed_sell_position(int x, int y);
    void Pressed_Check(std::vector<int>* v);
    void set_scale(float scale);
    void set_zero_x(float x);
    void set_zero_y(float y);
    void set_cell_width(float w);
    void set_cell_height(float h);
    void set_BUILDING_TEXTURE(std::string texture);
    float get_scale();
    float get_zero_x();
    float get_zero_y();
    float get_cell_width();
    float get_cell_height();
    void Pressed_Check(std::vector<int> v);
    void set_building_list(Building_List* Building_list);
    void set_available_buildings(Available_Buildings* Available_buildings);
    Building_List* get_Building_list();
    Available_Buildings* get_Available_buildings();
    void Set_Sprite_Static_Position(sf::Sprite* Sprite, int x, int y);
    void Set_Sprite_Static_Position(sf::Sprite* Sprite, int x, int y, float flactuation);
    void Map_Scale(int delta, std::string Scale_Type, std::map<std::string, float>* Constants);
    void set_Player_Number();
    bool Check_Access(std::string teg);
    bool Create_Mines();
    int get_Money();
    void set_Cost(int money);
    void Stonks();
    int get_Current_Player();
    void Animation();
    void updateHealthDisplays(); // Обновить все Health
    void drawHealthDisplays(sf::RenderWindow& window); // Отрисовать все Health
};

#endif //MAP_H
