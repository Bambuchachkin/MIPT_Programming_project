#ifndef TEXTURE_LIST_H
#define TEXTURE_LIST_H
#include <string>
#include <vector>
#include "Map.h"


class Texture_List {
    std::vector<int> Texture_Chances;
    std::vector<std::string> Texture_Names;
    Map* Map_Pointer;
public:
    Texture_List(Map* Created_Map, std::vector<std::string>&);
    Texture_List(Map* Created_Map,  std::string Constructor_Type);
    ~Texture_List();
    std::string creat_Random_Texture_Name(int x_coord, int y_coord);
};



#endif //TEXTURE_LIST_H
