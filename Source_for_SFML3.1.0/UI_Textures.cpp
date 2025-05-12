#include "UI_Textures.h"
#include <iostream>

// Создание текстовых меток (добавьте в конструктор после загрузки шрифта)
void UI_Textures::createTitles() {
    if (!font.getInfo().family.empty()) {
        ui_title.clear();

        const std::vector<std::string> labels = {
                "Mine: You can't build it",
                "Barrks: Press 1 to select\nCost: 500",
                "Warrior: Press 2 to select\nCost: 200",
                "Miner: Press 3 to select\nCost: 500"
        };

        for (const auto& label : labels) {
            sf::Text text(label, font, 20);
            ui_title.push_back(text);
        }
        std::cout << "TITLES CREATED" << std::endl;
    }
}

UI_Textures::UI_Textures() : SCREEN_WIDTH(2048.f), SCREEN_HEIGHT(1280.f) {
    if(font.loadFromFile("../Font/font.ttf")){
        createTitles();
    }
    std::vector<std::string> paths = {
            // "../Textures/Barracks.png",
            "../Textures/Mine.png",
            "../Textures/Barracks.png",
            "../Textures/Warrior.png",
            "../Textures/Miner.png"
    };

    // Загрузка текстур
    for (const auto& path : paths) {
        sf::Texture tex;
        if (tex.loadFromFile(path)) {
            tex_textures.push_back(tex);
        }
    }

    // Создание спрайтов
    for (const auto& tex : tex_textures) {
        ui_textures.emplace_back(tex);
    }
    std::cout<<"UI_TEXTURES CREATED"<<std::endl;
    // createTitles();
    infoTexts.resize(3);
    infoBox.setFillColor(sf::Color(50, 50, 50, 200));
    infoBox.setOutlineThickness(2);
    infoBox.setOutlineColor(sf::Color::White);
    texBox.setFillColor(sf::Color(50, 50, 50, 200));
    texBox.setOutlineThickness(2);
    texBox.setOutlineColor(sf::Color::White);
}

// bool UI_Textures::loadFont(const std::string& fontPath) {
//     std::cout<<"FONT LOADED"<<std::endl;
//     return font.openFromFile(fontPath);
// }

std::vector<sf::Sprite>* UI_Textures::get_ui_textures() {
    return &ui_textures;
}

// std::vector<sf::Sprite>* UI_Textures::get_ui_textures() {
// return &ui_textures;
// }

std::vector<sf::Text>* UI_Textures::get_ui_title() {
    return &ui_title;
}

std::vector<sf::Text>& UI_Textures::get_info_texts() {
    return infoTexts;
}

sf::RectangleShape& UI_Textures::get_info_box() {
    return infoBox;
}

sf::RectangleShape& UI_Textures::get_tex_box() {
    return texBox;
}

UI_Textures::~UI_Textures() {
    tex_textures.clear();
    ui_textures.clear();
    ui_title.clear();
}

void UI_Textures::set_transparency(int transparency) {
    for (auto& sprite : ui_textures) {
        sprite.setColor(sf::Color(255, 255, 255, transparency));
    }
}

void UI_Textures::set_position_textures() {
    if(ui_textures.size() < 4) return;
    // ui_textures[0].setPosition({20.f/2048.f * SCREEN_WIDTH, 20.f/1280.f * SCREEN_HEIGHT});
    // ui_textures[1].setPosition({20.f/2048.f * SCREEN_WIDTH, 330.f/1280.f * SCREEN_HEIGHT});
    // ui_textures[2].setPosition({1650.f/2048.f * SCREEN_WIDTH, 0.f/1280.f * SCREEN_HEIGHT});
    // ui_textures[3].setPosition({1550.f/2048.f * SCREEN_WIDTH, 200.f/1280.f * SCREEN_HEIGHT});
    ui_textures[0].setPosition({20.f/2048.f * SCREEN_WIDTH, 20.f/1280.f * SCREEN_HEIGHT});
    ui_textures[1].setPosition({20.f/2048.f * SCREEN_WIDTH, 416.f/1280.f * SCREEN_HEIGHT});
    ui_textures[2].setPosition({-100.f/2048.f * SCREEN_WIDTH, 642.f/1280.f * SCREEN_HEIGHT});
    ui_textures[3].setPosition({-200.f/2048.f * SCREEN_WIDTH, 920.f/1280.f * SCREEN_HEIGHT});
    ui_textures[2].setScale({1.5f, 1.5f});
    ui_textures[3].setScale({1.7f, 1.7f});


//    float maxHeight = 0;
//    for (const auto& text : ui_title) {
//        sf::Vector2f position = text.getPosition();
//        float y = position.y;
//        if (position.y > maxHeight) {
//            maxHeight = position.y;
//        }
//    }
    texBox.setSize(sf::Vector2f(350.f/2048.f * SCREEN_WIDTH, SCREEN_HEIGHT));
    texBox.setPosition(0, 0);

}

void UI_Textures::set_color_title() {
    for(auto& title : ui_title) {
        title.setFillColor(sf::Color::White);
    }
}

void UI_Textures::set_position_title() {
    if(ui_textures.size() < 4 || ui_title.size() < 4) return;
    ui_title[0].setPosition({ui_textures[0].getPosition().x,ui_textures[0].getPosition().y + 250.f/1280.f*SCREEN_HEIGHT});
    ui_title[1].setPosition({ui_textures[1].getPosition().x,ui_textures[1].getPosition().y + 180.f/1280.f*SCREEN_HEIGHT});
    ui_title[2].setPosition({ui_textures[2].getPosition().x + 120.f/2048.f*SCREEN_WIDTH,ui_textures[2].getPosition().y + 250.f/1280.f*SCREEN_HEIGHT});
    ui_title[3].setPosition({ui_textures[3].getPosition().x + 220.f/2048.f*SCREEN_WIDTH,ui_textures[3].getPosition().y + 250.f/1280.f*SCREEN_HEIGHT});
    std::cout<<"UI_TITLES POSITIONISED"<<std::endl;
}

void UI_Textures::set_screen_size(float width, float height) {
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    set_position_textures();
    set_transparency(255);
    set_position_title();
    set_color_title();
}

void UI_Textures::createInfoPanel() {
    for (auto& text : infoTexts) {
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
    }
}

void UI_Textures::updateInfoPanel(int money, int currentPlayer, int turnNumber) {
    infoTexts[0].setString("Money: " + std::to_string(money));
    infoTexts[1].setString("Player: " + std::to_string(currentPlayer));
    infoTexts[2].setString("Turn: " + std::to_string(turnNumber));

    const float padding = 20.0f;
    float yPos = 10.f;

    for (auto& text : infoTexts) {
        text.setPosition(SCREEN_WIDTH - text.getLocalBounds().width - padding, yPos);
        yPos += 40;
    }

    float maxWidth = 0;
    for (const auto& text : infoTexts) {
        if (text.getLocalBounds().width > maxWidth) {
            maxWidth = text.getLocalBounds().width;
        }
    }

    infoBox.setSize(sf::Vector2f(maxWidth + 2 * padding, 130));
    infoBox.setPosition(SCREEN_WIDTH - maxWidth - 1.5f * padding, 0);
}