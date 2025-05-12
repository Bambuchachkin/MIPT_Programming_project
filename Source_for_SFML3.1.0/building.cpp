#include "building.h"

std::string extract_filename_b(const std::string& path) {
    size_t start = path.find_last_of("/\\") + 1;
    size_t end = path.find_last_of('.');
    if (end == std::string::npos) end = path.length();
    // std::cout<<path.substr(start, end - start)<<'\n';
    return path.substr(start, end - start);
}

// Экспресс тур в понятие спрайта
// Спрайт - это прямоуголььник у которого есть своя текстура (картинка png),
// свои размеры, корневая точка и ее координаты
// Именно этот объект отрисовывает SFML
building::building(int x, int y, std::string Building_Texture)  {
    x_coordinate = x;
    y_coordinate = y;
    Scale = 1;
    health = 100;
    Teg = "";
    owner_id = 0;
    ability_unit = false;
    ability_money = false;
    // Создаем объект текстуры
    Texture.loadFromFile(Building_Texture);
    // Создаем спрайт в динамической памяти и запоминаем указатель на него
    Sprite = new sf::Sprite(Texture);
    Texture_Name = Building_Texture;
    Teg = extract_filename_b(Texture_Name);
    damage = 0;
}

// building::~building() {
    // delete Sprite;
// }

int building::get_x_coordinate() const{
    return x_coordinate;
}

int building::get_y_coordinate() const{
    return y_coordinate;
}

void building::set_x_coordinate(int value){
    x_coordinate = value;
}

void building::set_y_coordinate(int value){
    y_coordinate = value;
}

std::string building::get_Texture_Name() const {
    return Texture_Name;
}

sf::Sprite* building::get_Sprite_Pointer() const{
    return Sprite;
}

void building::set_Sprite_By_Texture(sf::Texture* building_texture) {
    Texture = *building_texture;
    delete Sprite;
    Sprite = new sf::Sprite(Texture);
}

void building::set_Sprite_By_Texture(std::string building_texture_name) {
    Texture.loadFromFile(building_texture_name);
    delete Sprite;
    Sprite = new sf::Sprite(Texture);
}


void building::set_Sprite_Origin(float x, float y) {
    (*Sprite).setOrigin({x, y});
}

void building::set_Sprite_Position(float x, float y) {
    (*Sprite).setPosition({x, y});
}

void building::set_Sprite_Scale(float scale) {
    (*Sprite).setScale({scale, scale});
}

void building::set_Sprite_Color(int r, int g, int b, int a) {
    sf::Color color = sf::Color(r, g, b, a);
    (*Sprite).setColor(color);
}
void building::set_health(int delta_health){
    health += delta_health;
    if (health < 0) health = 0;
}
int building::get_health() const {
    return health;
}
void building::set_owner_id(int Owner_id){
    owner_id = Owner_id;
}
int building::get_owner_id() const{
    return owner_id;
}
std::string building::get_Teg() const {
    return Teg;
}

void building::Action(int i) {
    return;
}

bool building::get_Action() const {
    return false;
}

sf::Color  building::get_Color() {
    return Sprite->getColor();
}

int building::get_damage() const {
    return damage;
}
