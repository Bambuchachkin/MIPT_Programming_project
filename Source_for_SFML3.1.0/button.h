//
// Created by User on 11.05.2025.
//

#ifndef SOURCE_BUTTON_H
#define SOURCE_BUTTON_H
class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color defaultColor;
    sf::Color hoverColor;

    Button(const std::string& btnText, const sf::Font& font, float width, float height) {
        // Настройка формы кнопки
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(sf::Color(100, 100, 100)); // Серый цвет

        // Настройка текста кнопки
        text.setString(btnText);
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);

        // Цвета для состояний
        defaultColor = sf::Color(100, 100, 100);
        hoverColor = sf::Color(150, 150, 150);
    }

    void setPosition(float x, float y) {
        shape.setPosition(x, y);
        // Центрирование текста на кнопке
        text.setPosition(
                x + (shape.getGlobalBounds().width - text.getGlobalBounds().width) / 2,
                y + (shape.getGlobalBounds().height - text.getGlobalBounds().height) / 2 - 5
        );
    }

    bool isMouseOver(const sf::RenderWindow& window) const {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return shape.getGlobalBounds().contains(mousePos);
    }

    void update(const sf::RenderWindow& window) {
        if (isMouseOver(window)) {
            shape.setFillColor(hoverColor);
        } else {
            shape.setFillColor(defaultColor);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }
};
#endif //SOURCE_BUTTON_H
