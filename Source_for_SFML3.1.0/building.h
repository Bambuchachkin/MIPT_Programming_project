#ifndef BUILDING_H
#define BUILDING_H
#include <string>
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
// #include "Map.h"

class building {
protected:
    int x_coordinate;
    int y_coordinate;
    float Scale;
    sf::Sprite* Sprite;
    sf::Texture Texture;
    std::string Texture_Name;
    std::string Teg;
    int health;
    int owner_id; // здесь имеется в виду номер игрока или бота, необходимо для функции захвата
    bool ability_unit; // возможность создание юнитов
    bool ability_money; // наличие денег
    int damage;
public:
    building(int x, int y, std::string texture); // базовое здоровье = 100
    virtual ~building() = default;
    int get_x_coordinate() const;
    int get_y_coordinate() const;
    void set_x_coordinate(int value);
    void set_y_coordinate(int value);
    std::string get_Texture_Name() const;
    sf::Sprite* get_Sprite_Pointer() const;
    void set_Sprite_By_Texture(sf::Texture* building_texture);
    void set_Sprite_By_Texture(std::string building_texture_name);
    void set_Sprite_Origin(float x, float y);
    void set_Sprite_Position(float x, float y);
    void set_Sprite_Scale(float scale);
    void set_Sprite_Color(int r, int g, int b, int a);
    void set_health(int delta_health); // лечение/по ебалу получение
    void set_owner_id(int owner_id);
    int get_owner_id() const;
    int get_health() const;
    std::string get_Teg() const;
    virtual void Action(int i); // флаг в каком направлении делать действие
    virtual bool get_Action() const;
    sf::Color get_Color();
    int get_damage() const;

};



#endif //BUILDING_H