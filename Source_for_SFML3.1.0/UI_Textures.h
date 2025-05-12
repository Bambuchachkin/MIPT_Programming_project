#ifndef BUILDING_H_UI_TEXTURES_H
#define BUILDING_H_UI_TEXTURES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class UI_Textures {
    sf::Font font;
    std::vector<sf::Texture> tex_textures;
    std::vector<sf::Sprite> ui_textures;
    std::vector<sf::Text> ui_title;
    float SCREEN_WIDTH;
    float SCREEN_HEIGHT;
    std::vector<sf::Text> infoTexts;
    sf::RectangleShape infoBox;
    sf::RectangleShape texBox;

    void createTitles();

public:
    UI_Textures();
    ~UI_Textures();

    std::vector<sf::Sprite>* get_ui_textures();
    std::vector<sf::Text>* get_ui_title();
    std::vector<sf::Text>& get_info_texts();
    sf::RectangleShape& get_info_box();
    sf::RectangleShape& get_tex_box();

    void set_screen_size(float width, float height);
    void set_position_textures();
    void set_position_title();
    void set_color_title();
    void set_transparency(int transparency);

    void createInfoPanel();
    void updateInfoPanel(int money, int currentPlayer, int turnNumber);
};

#endif