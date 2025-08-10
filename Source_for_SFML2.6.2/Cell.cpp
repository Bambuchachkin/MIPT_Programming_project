#include "Cell.h"

#include <iostream>

Cell::Cell(int x, int y, std::string Map_Texture) {
    x_coordinate = x;
    y_coordinate = y;
    Scale = 1;
    Texture.loadFromFile(Map_Texture);
    Sprite = new sf::Sprite(Texture);
    Texture_Name = Map_Texture;
    Potencial = 0;
}

Cell::~Cell() {
    delete Sprite;
}

int Cell::get_x_coordinate() const{
    return x_coordinate;
}

int Cell::get_y_coordinate() const{
    return y_coordinate;
}

std::string Cell::get_Texture_Name() const {
    return Texture_Name;
}

sf::Sprite* Cell::get_Sprite_Pointer() const{
    return Sprite;
}

void Cell::set_Sprite_By_Texture(sf::Texture* cell_texture) {
    Texture = *cell_texture;
    delete Sprite;
    Sprite = new sf::Sprite(Texture);
}

void Cell::set_Sprite_By_Texture(std::string cell_texture_name) {
    Texture.loadFromFile(cell_texture_name);
    delete Sprite;
    Sprite = new sf::Sprite(Texture);
}


void Cell::set_Sprite_Origin(float x, float y) {
    (*Sprite).setOrigin({x, y});
}

void Cell::set_Sprite_Position(float x, float y) {
    (*Sprite).setPosition({x, y});
}

void Cell::set_Scale_Sprite(float scale) {
    (*Sprite).setScale({scale, scale});
}

void Cell::set_Texture_Name(std::string texture_name) {
    // std::cout << texture_name.length() << std::endl;
    Texture_Name = texture_name+" ";
}