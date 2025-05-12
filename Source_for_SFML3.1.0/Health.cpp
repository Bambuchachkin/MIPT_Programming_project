#include "Health.h"
#include <string> // Добавьте эту строку
#include <iostream>

sf::Font Health::font;

Health::Health(building* build) : Building(build) {
    if (!fontLoaded) {
        if (!font.loadFromFile("../Font/font.ttf")) {
            std::cerr << "Ошибка загрузки шрифта!\n";
        }
        fontLoaded = true;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::Green);
    health_building.push_back(text);
}

void Health::update() {
    //Проверка существовния здания, что оно не умерло
    if (!Building || Building->get_health() <= 0) return;

    //Проверка существования здания, что оно есть
    if (health_building.empty()) return;

    // Обновляем текст
    std::string healthStr = std::to_string(Building->get_health());
    health_building[0].setString(healthStr);

    // Позиционируем текст над зданием
    sf::Sprite* sprite = Building->get_Sprite_Pointer();
    sf::FloatRect bounds = sprite->getGlobalBounds();
    health_building[0].setPosition(
            bounds.left + bounds.width / 2,
            bounds.top - 20
    );
    // Центрируем текст
    sf::FloatRect textBounds = health_building[0].getLocalBounds();
    health_building[0].setOrigin(textBounds.width / 2, 0);
}

void Health::draw(sf::RenderWindow& window) {
    for (auto& text : health_building) {
        window.draw(text);
    }
}
building* Health::getBuilding(){
    return Building;
}