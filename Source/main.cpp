#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "Texture_List.h"
#include "UI_Textures.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
sf::SoundBuffer buffer;
sf::Sound sound(buffer);


// Константы
unsigned int SCREEN_WIDTH = 0;
unsigned int SCREEN_HEIGHT = 0;
float SCAIL_SPEED = 0.015; // Скорость зума
float SPEED = 40; // Скорость перемещения по карте
int FRAME_RATE = 60;
std::map<std::string, float> CONSTANTS; // Словарь констант для использования в функциях
std::string BUILDING_TEXTURE = ""; // Текстура создаваемой сущности
static int turnNumber = 1;
bool STILL_GAME = true;
bool STILL_MUSIC = true;


int main() {
    // Music
    sf::SoundBuffer buffer;
    sf::Sound sound(buffer);
    sf::Music music;
    if (!music.openFromFile("../Sound/Music.wav"))
        return -1; // error
    music.setVolume(300);
    music.setLoopPoints({sf::milliseconds(500), sf::seconds(35)});
    music.setLooping(true);
    music.play();


    // Запуск окна
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    SCREEN_WIDTH = desktop.size.x;
    SCREEN_HEIGHT = desktop.size.y;
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Game");

    // Загрузка шрифта
    sf::Font font;
    if (!font.openFromFile("../Font/font.ttf")) {
        std::cerr << "Font not found!" << std::endl;
    }
    // Создание UI

    // Создание карты
    std::string texture_name = "../Textures/BasicLendPattern.png";
    Map Created_Map(20, texture_name);
    Created_Map.set_zero_x((SCREEN_HEIGHT/20)*8.0f);
    Created_Map.set_zero_y((SCREEN_WIDTH/2)*1.0f);
    CONSTANTS.insert({"SCAIL_SPEED", SCAIL_SPEED});
    CONSTANTS.insert({"SCREEN_HEIGHT", SCREEN_HEIGHT});
    CONSTANTS.insert({"SCREEN_WIDTH", SCREEN_WIDTH});

    // Создаем эталонный спрайт мир для установки глобальных констант
    sf::Texture cell_texture;
    if (!cell_texture.loadFromFile("../Textures/BasicLendPattern.png")) {
        std::cerr << "Failed to load cell texture!" << std::endl;
        return 1;
    }
    sf::Sprite Sprite(cell_texture);
    sf::FloatRect scaledBounds = (Sprite).getGlobalBounds();
    Created_Map.set_cell_width(scaledBounds.size.x);
    Created_Map.set_cell_height(scaledBounds.size.y);

    // Создание фона
    sf::Texture sky_texture;
    if (!sky_texture.loadFromFile("../Textures/Sky.png")) {
        std::cerr << "Failed to load sky texture!" << std::endl;
        return 1;
    }
    sf::Sprite Sky_Sprite(sky_texture);
    sf::FloatRect ScaledBounds = (Sky_Sprite).getGlobalBounds();
    float Sky_WIDTH = ScaledBounds.size.x;
    Sky_Sprite.setScale({1.8f*SCREEN_WIDTH/Sky_WIDTH,1.8f*SCREEN_WIDTH/Sky_WIDTH});
    Sky_Sprite.setOrigin({0.5f*Sky_WIDTH,0.3f*Sky_WIDTH});
    Sky_Sprite.setPosition({1.0f*Sky_WIDTH,0.5f*Sky_WIDTH});
    // Sky_Sprite.setPosition({-0.5f*Sky_WIDTH,-0.3f*Sky_WIDTH});

    // UI Текстуры
    UI_Textures uiTextures;
    uiTextures.set_screen_size(SCREEN_WIDTH, SCREEN_HEIGHT);
    std::vector<sf::Text>* titles = uiTextures.get_ui_title();
    std::vector<sf::Sprite>* sprites = uiTextures.get_ui_textures();
    uiTextures.createInfoPanel(); // Инициализация элементов интерфейса

    // Настраиваем игровые объекты
    Texture_List texture_list(&Created_Map, "Standart");
    Created_Map.get_Building_list()->Add_Building(0,0,"../Textures/FramePattern.png");
    Created_Map.get_Building_list()->Find_Building("FramePattern")->set_Sprite_Origin(Created_Map.get_cell_width()/2.0f, Created_Map.get_cell_height()*1.0f);
    Created_Map.get_Building_list()->Find_Building("FramePattern")->set_Sprite_Color(255, 255, 255, 150);

    // Приступаем к переопределению клеточек
    for (unsigned int i = 0; i < Created_Map.Get_Size(); i++) {
        for (unsigned int j = 0; j < Created_Map.Get_Size(); j++) {
            texture_name = texture_list.creat_Random_Texture_Name(i, j);
            Created_Map.Cells_Data[i][j]->set_Sprite_By_Texture(texture_name);
            scaledBounds = Created_Map.Cells_Data[i][j]->get_Sprite_Pointer()->getGlobalBounds();
            // Установка корневой точки
            float width= scaledBounds.size.x;
            float height = scaledBounds.size.y;
            Created_Map.Cells_Data[i][j]->set_Sprite_Origin(width/2.0f, height*1.0f);
            Created_Map.Cells_Data[i][j]->set_Texture_Name(texture_name);
            // Установка позиции спрайта
            Created_Map.Set_Sprite_Static_Position(Created_Map.Cells_Data[i][j]->get_Sprite_Pointer(),i,j);
        }
    }
    Created_Map.Create_Mines();

    while (window.isOpen())
    {
        // Обработка ввода
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                Created_Map.Map_Scale(mouseWheelScrolled->delta, "Mouse", &CONSTANTS);
            }
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    uiTextures.handleClick(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
                    Created_Map.get_pressed_sell_position(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
                }
            }
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) && (Created_Map.get_zero_x())<SCREEN_HEIGHT/1.0f+Created_Map.get_cell_height()) {
            // std::cout<<Created_Map.get_zero_x()<<std::endl;
            Created_Map.set_zero_x(Created_Map.get_zero_x() + Created_Map.get_scale()*SPEED);
            Sky_Sprite.setPosition({Sky_Sprite.getPosition().x, Sky_Sprite.getPosition().y + 1/Created_Map.get_scale()*SPEED/100});
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && (Created_Map.get_zero_x()>Created_Map.get_scale()*Created_Map.get_cell_height()*0.577*(-1.0f)*Created_Map.Get_Size())){
            Created_Map.set_zero_x(Created_Map.get_zero_x() - Created_Map.get_scale()*SPEED);
            Sky_Sprite.setPosition({Sky_Sprite.getPosition().x, Sky_Sprite.getPosition().y - 1/Created_Map.get_scale()*SPEED/100});
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && (Created_Map.get_zero_y()+Created_Map.get_scale()*Created_Map.get_cell_width()*Created_Map.Get_Size()/2>0)){
            Created_Map.set_zero_y(Created_Map.get_zero_y() - Created_Map.get_scale()*SPEED);
            Sky_Sprite.setPosition({Sky_Sprite.getPosition().x - 1/Created_Map.get_scale()*SPEED/100, Sky_Sprite.getPosition().y});
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) && (Created_Map.get_zero_y()-Created_Map.get_scale()*Created_Map.get_cell_width()*Created_Map.Get_Size()/2<SCREEN_WIDTH)){
            Created_Map.set_zero_y(Created_Map.get_zero_y() + Created_Map.get_scale()*SPEED);
            Sky_Sprite.setPosition({Sky_Sprite.getPosition().x + 1/Created_Map.get_scale()*SPEED/100, Sky_Sprite.getPosition().y});
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) && (Created_Map.get_scale()<1)) {
            Created_Map.Map_Scale(1, "Keyboard", &CONSTANTS);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) && (Created_Map.get_scale()>0.2)) {
            Created_Map.Map_Scale(-1, "Keyboard", &CONSTANTS);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))) {
            Created_Map.Stonks();
            Created_Map.set_Player_Number();
            int playersMoved = Created_Map.get_Current_Player();
            if (playersMoved == 1) {
                turnNumber++;
            }
            sf::sleep(sf::milliseconds(10*1000/FRAME_RATE));
        }

        // Обработка выбора сущности
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
            if (Created_Map.Check_Access("Barracks") && Created_Map.get_Money()>=500){
                Created_Map.set_Cost(500);
                if (Created_Map.get_Current_Player() == 1) {
                    Created_Map.set_BUILDING_TEXTURE("../Textures/Barracks.png");
                } else {
                    Created_Map.set_BUILDING_TEXTURE("../Textures/2/Barracks.png");
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
            if (Created_Map.Check_Access("Warrior") && Created_Map.get_Money()>=200){
                Created_Map.set_Cost(200);
                // Created_Map.set_BUILDING_TEXTURE("../Textures/Warrior.png");
                if (Created_Map.get_Current_Player() == 1) {
                    Created_Map.set_BUILDING_TEXTURE("../Textures/Warrior.png");
                } else {
                    Created_Map.set_BUILDING_TEXTURE("../Textures/2/Warrior.png");
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
            if (Created_Map.Check_Access("Miner") && Created_Map.get_Money()>=500){
                Created_Map.set_Cost(500);
                // Created_Map.set_BUILDING_TEXTURE("../Textures/Miner.png");
                if (Created_Map.get_Current_Player() == 1) {
                    Created_Map.set_BUILDING_TEXTURE("../Textures/Miner.png");
                } else {
                    Created_Map.set_BUILDING_TEXTURE("../Textures/2/Miner.png");
                }
            }
        }

        // Отрисовка
        window.clear(sf::Color::Black);
        // Отрисовка фона
        window.draw(Sky_Sprite);
        // Отрисовка клеточек
        for (unsigned int i = 0; i < Created_Map.Get_Size(); i++) {
            for (unsigned int j = 0; j < Created_Map.Get_Size(); j++) {
                Created_Map.Set_Sprite_Static_Position(Created_Map.Cells_Data[i][j]->get_Sprite_Pointer(), i, j);
                Created_Map.Cells_Data[i][j]->set_Scale_Sprite(Created_Map.get_scale());
                window.draw(*(Created_Map.Cells_Data[i][j]->get_Sprite_Pointer()));
            }
        }

        // Отрисовка элементов из Building_List
        for (auto it = Created_Map.get_Building_list()->Buildings.begin(); it!= Created_Map.get_Building_list()->Buildings.end(); it++) {
            it->second->set_Sprite_Scale(Created_Map.get_scale());
            Created_Map.Set_Sprite_Static_Position(it->second->get_Sprite_Pointer(), it->second->get_x_coordinate(), it->second->get_y_coordinate());
            Created_Map.Animation();
            window.draw(*(it->second->get_Sprite_Pointer()));
        }

        // Отрисовка UI
        window.draw(uiTextures.get_tex_box());
        // window.draw(uiTextures.get_help_box());
        for (size_t i = 0; i < titles->size(); ++i) {
            window.draw((*titles)[i]);
        }
        for (size_t i = 0; i < sprites->size(); ++i) {
            window.draw((*sprites)[i]);
        }
        //Обновление UI
        uiTextures.updateInfoPanel(Created_Map.get_Money(), Created_Map.get_Current_Player(), turnNumber);
        Created_Map.updateHealthDisplays();

        window.draw(uiTextures.get_info_box()); // Фон
        for (const auto& text : uiTextures.get_info_texts()) { // Используем ссылку
            window.draw(text);
        }

        Created_Map.drawHealthDisplays(window);

        window.draw(uiTextures.get_toggle_button());
        window.draw(*uiTextures.get_ttext()->begin());
        if (uiTextures.isPanelVisible) {
            window.draw(uiTextures.get_popup_window());
            window.draw(uiTextures.get_ttext()->back());
        }

        if (!Created_Map.Check_Halls()) {
            STILL_GAME = false;
            if (STILL_MUSIC) {
                buffer.loadFromFile("../Sound/Barracks.wav");
                sound.setVolume(80);
                sound.play();
                STILL_MUSIC = false;
            }

        }

        if (!STILL_GAME) {
            window.draw(uiTextures.get_winner_box());
            if (uiTextures.get_winner_text()) {
                window.draw(*uiTextures.get_winner_text()->begin());
            }
        }

        window.display();
        sf::sleep(sf::milliseconds(1000/FRAME_RATE));

        // std::cout<<MONEY<<'\n';
    }

    std::cout << "Yep!" << std::endl;
}