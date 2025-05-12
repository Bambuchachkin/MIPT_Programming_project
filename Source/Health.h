#ifndef HEALTH_H
#define HEALTH_H

#include <SFML/Graphics.hpp>
#include "building.h"
#include <vector>
#include <string>

class Health {
private:
    std::vector<sf::Text> health_building;
    building* Building;
    static sf::Font font;
    bool fontLoaded = false; // Флаг загрузки шрифта
public:
    Health(building* build);
    void update(float SCALE); // Обновляет позицию и текст
    void draw(sf::RenderWindow& window);
    building* getBuilding();
};


#endif //HEALTH_H
