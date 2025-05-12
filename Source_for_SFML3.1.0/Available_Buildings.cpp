#include "Available_Buildings.h"

// Каждый ключ соответствует своему игроку и дает ему доступ к сущности

// ВНИМАНИЕ! Этодж метод пишется вручную
// Сюда мы добавляем все возможные во время постройки
// Т.е. программист заранее вписывает, какому игроку, что можно кдет строить
// Пример: Buildings.insert(std::pair<int, std::string>(1, "../grass.png"));
// Таким образом: мы добавили в словарь элемент "../grass.png", которому присвоили ключ 1
// Это значит что игрок с номером 1 может создавать building с текстурой "../grass.png"
Available_Buildings::Available_Buildings() {
    Buildings.insert(std::pair<int, std::string>(1, "Barracks"));
    // Buildings.insert(std::pair<int, std::string>(1, "grass"));
    Buildings.insert(std::pair<int, std::string>(1, "Warrior"));
    Buildings.insert(std::pair<int, std::string>(1, "Miner"));

    Buildings.insert(std::pair<int, std::string>(2, "Barracks"));
    Buildings.insert(std::pair<int, std::string>(2, "Warrior"));
    Buildings.insert(std::pair<int, std::string>(2, "Miner"));
}

Available_Buildings::~Available_Buildings() {
    Buildings.clear();
}


// Чтобы проверить доступ к элементу, т.е. узнать, можно ли мне его поставить,
// Нужно сообщить свой номер (ключ) и имя текстуры постройки, которую мы хотим создать
bool Available_Buildings::Check_Access(int Player_Number, std::string building_name) {
    auto range = Buildings.equal_range(Player_Number);
    // if (building_name == "Miner") {
    //     for (auto it = range.first; it != range.second; it++) {
    //         if (it->second == building_name) {
    //             Buildings.erase(it);
    //             return true;
    //         }
    //     }
    // }
    for (auto it = range.first; it != range.second; it++) {
        if (it->second == building_name) {
            return true;
        }
    }
    return false;
}

