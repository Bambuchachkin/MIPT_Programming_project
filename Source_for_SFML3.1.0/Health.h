//
// Created by User on 11.05.2025.
//

#ifndef SOURCE_HEALTH_H
#define SOURCE_HEALTH_H

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
    void update(); // Обновляет позицию и текст
    void draw(sf::RenderWindow& window);
    building* getBuilding();
};


#endif //SOURCE_HEALTH_H
