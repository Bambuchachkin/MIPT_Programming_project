#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "Texture_List.h"
#include "UI_Textures.h"

// Константы
unsigned int SCREEN_WIDTH = 0;
unsigned int SCREEN_HEIGHT = 0;
float SCAIL_SPEED = 0.015; // Скорость зума
float SPEED = 40; // Скорость перемещения по карте
int FRAME_RATE = 60;
std::map<std::string, float> CONSTANTS; // Словарь констант для использования в функциях
std::string BUILDING_TEXTURE = ""; // Текстура создаваемой сущности
static int turnNumber = 1;

int main() {
    // Запуск окна
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    SCREEN_WIDTH = desktop.width;
    SCREEN_HEIGHT = desktop.height;
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Game");

    // Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("../Font/font.ttf")) {
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
    Created_Map.set_cell_width(scaledBounds.width);
    Created_Map.set_cell_height(scaledBounds.height);

    // Создание фона
    sf::Texture sky_texture;
    if (!sky_texture.loadFromFile("../Textures/Sky.png")) {
        std::cerr << "Failed to load sky texture!" << std::endl;
        return 1;
    }
    sf::Sprite Sky_Sprite(sky_texture);
    sf::FloatRect ScaledBounds = (Sky_Sprite).getGlobalBounds();
    float Sky_WIDTH = ScaledBounds.width;
    Sky_Sprite.setScale({SCREEN_WIDTH/Sky_WIDTH,SCREEN_WIDTH/Sky_WIDTH});

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
            float width= scaledBounds.width;
            float height = scaledBounds.height;
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
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                float delta = event.mouseWheelScroll.delta;
                Created_Map.Map_Scale(delta, "Mouse", &CONSTANTS);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    Created_Map.get_pressed_sell_position(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) && (Created_Map.get_zero_x())<SCREEN_HEIGHT/1.0f+Created_Map.get_cell_height()) {
            // std::cout<<Created_Map.get_zero_x()<<std::endl;
            Created_Map.set_zero_x(Created_Map.get_zero_x() + Created_Map.get_scale()*SPEED);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && (Created_Map.get_zero_x()>Created_Map.get_scale()*Created_Map.get_cell_height()*0.577*(-1.0f)*Created_Map.Get_Size())){
            Created_Map.set_zero_x(Created_Map.get_zero_x() - Created_Map.get_scale()*SPEED);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && (Created_Map.get_zero_y()+Created_Map.get_scale()*Created_Map.get_cell_width()*Created_Map.Get_Size()/2>0)){
            Created_Map.set_zero_y(Created_Map.get_zero_y() - Created_Map.get_scale()*SPEED);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) && (Created_Map.get_zero_y()-Created_Map.get_scale()*Created_Map.get_cell_width()*Created_Map.Get_Size()/2<SCREEN_WIDTH)){
            Created_Map.set_zero_y(Created_Map.get_zero_y() + Created_Map.get_scale()*SPEED);
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
                Created_Map.set_BUILDING_TEXTURE("../Textures/Barracks.png");
                // std::cout<<Created_Map.get_Money()<<std::endl;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
            if (Created_Map.Check_Access("Warrior") && Created_Map.get_Money()>=200){
                Created_Map.set_Cost(200);
                Created_Map.set_BUILDING_TEXTURE("../Textures/Warrior.png");
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
            if (Created_Map.Check_Access("Miner") && Created_Map.get_Money()>=500){
                Created_Map.set_Cost(500);
                Created_Map.set_BUILDING_TEXTURE("../Textures/Miner.png");
            }
        }

        //Обновление UI
        uiTextures.updateInfoPanel(Created_Map.get_Money(), Created_Map.get_Current_Player(), turnNumber);
        Created_Map.updateHealthDisplays();

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
        for (size_t i = 0; i < titles->size(); ++i) {
            window.draw((*titles)[i]);
        }
        for (size_t i = 0; i < sprites->size(); ++i) {
            window.draw((*sprites)[i]);
        }

        window.draw(uiTextures.get_info_box()); // Фон
        for (const auto& text : uiTextures.get_info_texts()) { // Используем ссылку
            window.draw(text);
        }

        Created_Map.drawHealthDisplays(window);

        window.display();
        sf::sleep(sf::milliseconds(1000/FRAME_RATE));


        // std::cout<<MONEY<<'\n';
    }

    std::cout << "Yep!" << std::endl;
}