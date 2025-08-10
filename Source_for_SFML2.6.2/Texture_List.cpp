#include "Texture_List.h"
#include <random>

int get_random_number(int from, int to) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(from, to);
    return dist(gen);
}

Texture_List::Texture_List(Map* Created_Map, std::vector<std::string>& texture_names) {
    for (auto it = texture_names.begin(); it != texture_names.end(); it++) {
        Texture_Names.push_back(*it);
        Texture_Chances.push_back(1);
    }
    Map_Pointer = Created_Map;
}

Texture_List::Texture_List(Map* Created_Map, std::string Constructor_Type) {
    for (auto it = 0; it != 10; it++) {
        Texture_Chances.push_back(1);
    }
    Map_Pointer = Created_Map;
    // Чем больше одинаковых элементов, тем больше шанс его спавна
    Texture_Names.push_back("../Textures/MarsLendPattern.png");
    Texture_Names.push_back("../Textures/MarsLendPattern.png");
    Texture_Names.push_back("../Textures/MarsLendPattern.png");
    Texture_Names.push_back("../Textures/MarsLendPattern.png");
    Texture_Names.push_back("../Textures/MarsLendPattern.png");
    Texture_Names.push_back("../Textures/MarsMountainLendPattern.png");
    Texture_Names.push_back("../Textures/MarsMountainLendPattern.png");
    Texture_Names.push_back("../Textures/MarsHoulLendPattern.png");
    Texture_Names.push_back("../Textures/MarsHoulLendPattern.png");
    Texture_Names.push_back("../Textures/MarsHoulLendPattern.png");
}

Texture_List::~Texture_List() {}

std::string Texture_List::creat_Random_Texture_Name(int x_coord, int y_coord) {
    // Пробегаемся по вектору и проверяем соседние для нашей клеточки клеточки
    for (int i = 0; i != Texture_Names.size(); i++) {
        if (x_coord > 0) {
            if ((*Map_Pointer).Cells_Data[x_coord-1][y_coord]->get_Texture_Name() == Texture_Names[i]) {
                Texture_Chances[i]++;
            }
        } else if (y_coord > 0) {
            if ((*Map_Pointer).Cells_Data[x_coord][y_coord-1]->get_Texture_Name() == Texture_Names[i]) {
                Texture_Chances[i]++;
            }
        }
    }
    // Вычисление шанса
    int sum = 0;
    for (auto it = Texture_Chances.begin(); it != Texture_Chances.end(); it++) {
        sum += Texture_Chances[*it];
    }
    int i = 0;
    int number = get_random_number(1,100);
    while (number > 0) {
        number-=(Texture_Chances[i]*100.0f/sum);
        i++;
    }
    std::string texture_name = Texture_Names[i-1];
    if (texture_name.length() > 0 && texture_name.length() < 100) {
        // std::cout << texture_name << std::endl;
        return texture_name;
    }
    return "ABOBA";
}


