#include "Health.h"
#include <string> // Добавьте эту строку
#include <iostream>

sf::Font Health::font;

Health::Health(building* build) : Building(build) {
    if (!fontLoaded) {
        if (!font.openFromFile("../Font/font.ttf")) {
            std::cerr << "Ошибка загрузки шрифта!\n";
        }
        fontLoaded = true;
    }

    sf::Text text(font);
    // text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    health_building.push_back(text);
}

void Health::update(float SCALE) {
    if (health_building.empty()) return;

    // Обновляем текст
    std::string healthStr = std::to_string(Building->get_health());
    health_building[0].setString(healthStr);

    // Позиционируем текст над зданием
    sf::Sprite* sprite = Building->get_Sprite_Pointer();
    sf::FloatRect bounds = sprite->getGlobalBounds();
    health_building[0].setPosition({bounds.size.x/4 + sprite->getPosition().x, sprite->getPosition().y - bounds.size.y/1});
    // Центрируем текст
    sf::FloatRect textBounds = health_building[0].getLocalBounds();
    health_building[0].setOrigin({textBounds.size.x / 2, 0});
    for (auto it = health_building.begin(); it != health_building.end(); it++) {
        it->setCharacterSize(20*SCALE);
        it->setOutlineThickness(2*SCALE);
        it->setOutlineColor(sf::Color::Black);
    }
}

void Health::draw(sf::RenderWindow& window) {
    for (auto& text : health_building) {
        window.draw(text);
        // std::string textString = text.getString();
        // std::cout<<"DRAW: "<<textString<<'\n';
    }
}

building *Health::getBuilding() {
    return Building;
}
