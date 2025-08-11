#include "UI_Textures.h"
#include <iostream>

// Создание текстовых меток (добавьте в конструктор после загрузки шрифта)
void UI_Textures::createTitles() {
    if (!font.getInfo().family.empty()) {
        ui_title.clear();

        const std::vector<std::string> labels = {
            "Mine: You can't build it",
            "Barrks: Press 1 to select\nCost: 500",
            "Warrior: Press 2 to select\nCost: 200\nDamage: 100",
            "Miner: Press 3 to select\nCost: 500\nDamage: 40"
        };

        for (const auto& label : labels) {
            sf::Text text;
            text.setFont(font);
            // sf::Text text(font);
            // text.setFont(font);  // Устанавливаем шрифт
            text.setString(label); // Устанавливаем текст
            text.setCharacterSize(20);
            ui_title.push_back(text);
        }
        std::cout << "TITLES CREATED" << std::endl;
    }
}

void UI_Textures::set_winner_box() {
    sf::Text text;
    text.setFont(font);
    // sf::Text text(font);
    text.setString("You are winner!");
    text.setCharacterSize(50);
    text.setPosition({SCREEN_WIDTH/2.5f, SCREEN_HEIGHT/2.5f});
    winnerText.push_back(text);
    winnerBox.setFillColor(sf::Color(50, 50, 50, 180));
    winnerBox.setOutlineThickness(2);
    winnerBox.setOutlineColor(sf::Color::White);
    winnerBox.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    winnerBox.setPosition({0, 0});
}

UI_Textures::UI_Textures() : SCREEN_WIDTH(2048.f), SCREEN_HEIGHT(1280.f) {
    set_winner_box();
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
    texBox.setFillColor(sf::Color(50, 50, 50, 200));
    texBox.setOutlineThickness(2);
    texBox.setOutlineColor(sf::Color::White);

    // Настройка текста кнопки
    sf::Text ttext;
    ttext.setFont(font);
    // sf::Text ttext(font);
    ttext.setString("Help ->");
    ttext.setCharacterSize(24);
    ttext.setPosition({SCREEN_WIDTH - 70.f, 150.f/1280.f * SCREEN_HEIGHT});
    ttext.setFillColor(sf::Color::White);
    TText.push_back(ttext);
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
    ui_textures[1].setPosition({20.f/2048.f * SCREEN_WIDTH, 340.f/1280.f * SCREEN_HEIGHT});
    ui_textures[2].setPosition({-100.f/2048.f * SCREEN_WIDTH, 545.f/1280.f * SCREEN_HEIGHT});
    ui_textures[3].setPosition({-140.f/2048.f * SCREEN_WIDTH, 800.f/1280.f * SCREEN_HEIGHT});
    ui_textures[2].setScale({1.5f, 1.5f});
    ui_textures[3].setScale({1.7f, 1.7f});
    texBox.setSize(sf::Vector2f(390.f/2048.f * SCREEN_WIDTH, SCREEN_HEIGHT));
    texBox.setPosition({0, 0});
    // helpBox.setSize(sf::Vector2f(390.f/2048.f * SCREEN_WIDTH, SCREEN_HEIGHT));
    // helpBox.setPosition({SCREEN_WIDTH - 390.f/2048.f * SCREEN_WIDTH, 0});

    // Настройка кнопки-рамки
    toggleButton.setSize(sf::Vector2f(50.f/2048.f * SCREEN_WIDTH, 50.f/1280.f * SCREEN_HEIGHT));
    // toggleButton.setFillColor(sf::Color(30, 30, 30, 10));
    toggleButton.setFillColor(sf::Color(50, 50, 50, 200));
    toggleButton.setOutlineThickness(2);
    toggleButton.setOutlineColor(sf::Color::White);
    // Настройка всплывающего окна
    popupWindow.setSize(sf::Vector2f(1300.f/2048.f * SCREEN_WIDTH + 169, SCREEN_HEIGHT * 5.95f));
    popupWindow.setFillColor(sf::Color(50, 50, 50, 200));
    popupWindow.setOutlineThickness(2);
    popupWindow.setOutlineColor(sf::Color::White);
    // Настройка текста окна
    sf::Text tex_1;
    tex_1.setFont(font);
    // sf::Text tex_1(font);
    tex_1.setCharacterSize(24);
    tex_1.setFillColor(sf::Color::White);
    tex_1.setString("Welcome to the game COSMOTOPIA\n\n Here's how to play:\n\n"
"MOVEMENT:\n"
"- Use W, A, S, D keys to move the camera around the map.\n"
"\n"
"UNIT SELECTION:\n"
"- Click on a unit or building with your mouse to select it.\n"
"\n"
"BUILDING CREATION:\n"
"- To create a BARRACKS: Select a Miner and press '1'.\n"
"- To create a SOLDIER: Select a Barracks and press '2'.\n"
"- To create a MINER: Select a Barracks (or Mine on the first turn) and press '3'.\n"
"\n"
"ECONOMY:\n"
"- Earn money by placing a Miner on a Mine.\n"
"\n"
"UNIT ACTIONS:\n"
"- To MOVE a unit: Click on it, then click on an adjacent tile.\n"
"- To ATTACK: Select your unit, then click on an enemy unit or building.\n"
"\n"
"WIN CONDITION:\n"
"- Destroy the enemy Town Hall to win the game!\n");
    // Позиция кнопки в правом верхнем углу
    toggleButton.setPosition({SCREEN_WIDTH - 53.f, 150.f/1280.f * SCREEN_HEIGHT});
    // Позиция окна рядом с кнопкой
    popupWindow.setPosition({SCREEN_WIDTH/2.f - 650/2048.f * SCREEN_WIDTH + 18, -5.0f});
    tex_1.setPosition({popupWindow.getPosition().x + 20.f, popupWindow.getPosition().y + 20.f/1280.f * SCREEN_HEIGHT});
    TText.push_back(tex_1);
    // Позиционируем текст по центру кнопки
    sf::FloatRect buttonBounds = toggleButton.getGlobalBounds();
    // TText[0].setPosition({(buttonBounds.size.x - TText[0].getLocalBounds().size.x) / 2, (buttonBounds.size.y - TText[0].getLocalBounds().size.y) / 2});
    // TText[0].setOrigin({9999,9999});
    TText[0].setPosition({SCREEN_WIDTH - 140.f, 160.f/1280.f * SCREEN_HEIGHT});
    TText[1].setOrigin({9999,9999});
    // popupWindow.setOrigin({999,999});
    sf::Color color_1(255,255,255, 0);
    popupWindow.setOutlineColor(color_1);
    popupWindow.setFillColor(color_1);
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
    ui_title[3].setPosition({ui_textures[3].getPosition().x + 160.f/2048.f*SCREEN_WIDTH,ui_textures[3].getPosition().y + 270.f/1280.f*SCREEN_HEIGHT});
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

// UI_Textures.cpp
void UI_Textures::createInfoPanel() {
    infoTexts.clear();
    // Создаем 3 текстовых элемента
    for(int i = 0; i < 3; ++i) {
        sf::Text text;
        text.setFont(font);
        // sf::Text text(font);
        // text.setFont(font);  // Важно: font должен быть уже загружен
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        infoTexts.push_back(text);
    }
    // Устанавливаем начальные значения
    infoTexts[0].setString("Money: 0");
    infoTexts[1].setString("Player: 1");
    infoTexts[2].setString("Turn: 1");
    // Инициализация прямоугольника
    infoBox.setFillColor(sf::Color(50, 50, 50, 200));
    infoBox.setOutlineThickness(2);
    infoBox.setOutlineColor(sf::Color::White);
    // helpBox.setFillColor(sf::Color(50, 50, 50, 200));
    // helpBox.setOutlineThickness(2);
    // helpBox.setOutlineColor(sf::Color::White);
}

void UI_Textures::updateInfoPanel(int money, int currentPlayer, int turnNumber) {
    // Проверка инициализации текстов
    if(infoTexts.size() < 3) {
        createInfoPanel();
        return;
    }
    // Обновляем только текст
    infoTexts[0].setString("Money: " + std::to_string(money));
    infoTexts[1].setString("Player: " + std::to_string(currentPlayer));
    infoTexts[2].setString("Turn: " + std::to_string(turnNumber));
    // Позиционирование
    const float padding = 20.0f;
    float yPos = 10.0f;
    float maxWidth = 0;
    for(auto& text : infoTexts) {
        const float textWidth = text.getLocalBounds().getSize().x;
        text.setPosition({SCREEN_WIDTH - textWidth - padding, yPos});
        yPos += 40;
        if(textWidth > maxWidth) maxWidth = textWidth;
    }
    // Обновляем инфо-бокс
    infoBox.setSize(sf::Vector2f(maxWidth + 2 * padding, 130));
    infoBox.setPosition({SCREEN_WIDTH - maxWidth - 1.5f * padding, padding * 0.0f});
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
sf::RectangleShape& UI_Textures::get_winner_box() {
    return winnerBox;
}
std::vector<sf::Text>* UI_Textures::get_winner_text() {
    return &winnerText;
}
// sf::RectangleShape& UI_Textures::get_help_box() {
    // return helpBox;
// }

void UI_Textures::handleClick(int mouseX, int mouseY) {
    // Проверка клика по кнопке
    if (toggleButton.getGlobalBounds().contains({mouseX*1.0f, mouseY*1.0f})) {
        isPanelVisible = !isPanelVisible;
        sf::Color color(255,255,255, 180);
        sf::Color color_1(255,255,255, 0);
        if (toggleButton.getFillColor() == color) {
            // TText[0].setOrigin({9999,9999});
            TText[1].setOrigin({9999,9999});
            toggleButton.setFillColor(sf::Color(50, 50, 50, 200));
            popupWindow.setOutlineColor(color_1);
            popupWindow.setFillColor(color_1);
        } else {
            // TText[0].setOrigin({0,0});
            TText[1].setOrigin({0,0});
            toggleButton.setFillColor(color);
            popupWindow.setOutlineColor(sf::Color::White);
            popupWindow.setFillColor(sf::Color(50, 50, 50, 200));;
        }
        // std::cout<<"UI_TITLES POSITIONISED"<<std::endl;
    }
}

void UI_Textures::update_ttext(std::string& text, std::string& text_1) {
    TText[0].setString(text);
    TText[1].setString(text_1);
    set_position_textures();
}
// void UI_Textures::updatePopupText(const std::string& text) {
    // popupText.setString(text);
// }

// void UI_Textures::updateButtonLabel(const std::string& text) {
    // buttonLabel.setString(text);
    // set_position_textures();
// }