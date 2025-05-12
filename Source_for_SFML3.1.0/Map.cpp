#include "Map.h"
#include <random>

std::string extract_filename_M(const std::string& path) {
    size_t start = path.find_last_of("/\\") + 1;
    size_t end = path.find_last_of('.');
    if (end == std::string::npos) end = path.length();
    // std::cout<<path.substr(start, end - start)<<'\n';
    return path.substr(start, end - start);
}
int get_random_number_M(int from, int to) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(from, to);
    return dist(gen);
}


Map::Map(unsigned int Map_Size, std::string Map_Texture) {
    if (Map_Size<4) {
        Map_Size = 4;
    }
    // Создаем словарь доступных для разных игроков сущностей
    Available_Buildings *Available_buildings = new Available_Buildings();
    // Создаем вектор сущностей и добавляем в него рамку
    Building_List *Building_list = new Building_List();

    Size = Map_Size;
    for (int i=0; i < Size; i++) {
        std::vector<Cell*> Vector;
        for (int j=0; j < Size; j++) {
            Cell* New_Cell = new Cell(i, j, Map_Texture);
            Vector.push_back(New_Cell);
        }
        Cells_Data.push_back(Vector);
    }
    MONEY = {1500, 1500};
    SCALE = 1;
    ZERO_X = 0;
    ZERO_Y = 0;
    CELL_WIDTH = 0;
    CELL_HEIGHT = 0;
    PLAYER_NUMBER = 1;
    building_list = Building_list;
    available_buildings = Available_buildings;
    BUILDING_TEXTURE = "";
    Sprite_Flactuation[0] = 0; //величина смещения
    Sprite_Flactuation[1] = -1; //показывает направление роста координаты
}

Map::~Map() {
    for (unsigned int i=0; i < Size; i++) {
        for (unsigned int j=0; j < Size; j++) {
            delete Cells_Data[i][j];
        }
    }
    Cells_Data.clear();
    // building_list->~Building_List();
    delete building_list;
    // available_buildings->~Available_Buildings();
    delete available_buildings;
    //Очистка здоровья
    for (auto& health : healthDisplays) {
        delete health;
    }
    healthDisplays.clear();
}

unsigned int Map::Get_Size() const {
    return Size;
}

void Map::set_scale(float scale) {
    SCALE = scale;
}

void Map::set_zero_y(float y) {
    ZERO_Y = y;
}

void Map::set_zero_x(float x) {
    ZERO_X = x;
}

void Map::set_cell_width(float w) {
    CELL_WIDTH = w;
}

void Map::set_cell_height(float h) {
    CELL_HEIGHT = h;
}

float Map::get_scale() {
    return SCALE;
}

float Map::get_zero_x() {
    return ZERO_X;
}

float Map::get_zero_y() {
    return ZERO_Y;
}

float Map::get_cell_width() {
    return CELL_WIDTH;
}

float Map::get_cell_height() {
    return CELL_HEIGHT;
}

void Map::set_building_list(Building_List* Building_list) {
    building_list = Building_list;
}

void Map::set_available_buildings(Available_Buildings* Available_buildings) {
    available_buildings = Available_buildings;
}

Building_List* Map::get_Building_list() {
    return building_list;
}

Available_Buildings *Map::get_Available_buildings() {
    return available_buildings;
}

void Map::set_Player_Number() {
    PLAYER_NUMBER +=1;
    if (PLAYER_NUMBER>2) {
        PLAYER_NUMBER = 1;
    }
    building_list->Set_Global_Color();
    building_list->Global_Diactivate();
    building_list->set_PLAYER_NUMBER(PLAYER_NUMBER);
}



void Map::Set_Sprite_Static_Position(sf::Sprite* Sprite, int x, int y) {
    float vector_x[2] = {0.5,-0.866};
    float vector_y[2] = {0.5,0.866};
    float k = 1/2.0f/0.88; // рассчет расстояния между клетками. Угол наклона = 30 градусов. На ширину спрайта домножаем ниже
    (*Sprite).setPosition({ZERO_Y+CELL_WIDTH*(x*vector_x[1]*k + y*vector_y[1]*k)*SCALE, ZERO_X+CELL_HEIGHT*(x*vector_x[0]*k + y*vector_y[0]*k)*SCALE});
}

void Map::Set_Sprite_Static_Position(sf::Sprite* Sprite, int x, int y, float flactuation) {
    float vector_x[2] = {0.5,-0.866};
    float vector_y[2] = {0.5,0.866};
    float k = 1/2.0f/0.88; // рассчет расстояния между клетками. Угол наклона = 30 градусов. На ширину спрайта домножаем ниже
    (*Sprite).setPosition({ZERO_Y+CELL_WIDTH*(x*vector_x[1]*k + y*vector_y[1]*k)*SCALE, ZERO_X+CELL_HEIGHT*(x*vector_x[0]*k + y*vector_y[0]*k)*SCALE + flactuation});
}

void Map::Pressed_Check(std::vector<int>* v) {
    int x = (*v)[0];
    int y = (*v)[1];
    // Устанавливаем рамку над нажатой клеточкой
    // building_list->Select_Building(x,y);
    Set_Sprite_Static_Position(building_list->Find_Building("FramePattern")->get_Sprite_Pointer(), building_list->Find_Building("FramePattern")->get_x_coordinate(), building_list->Find_Building("FramePattern")->get_y_coordinate());
    building_list->Find_Building("FramePattern")->set_x_coordinate(x);
    building_list->Find_Building("FramePattern")->set_y_coordinate(y);
    // Обрабатываем строительство
    if (BUILDING_TEXTURE != "") { // Доступ к сущности уже был проверен перед вызовом
        if (building_list->Add_Building(x, y, BUILDING_TEXTURE)) {
            building_list->Find_Building(x, y, extract_filename_M(BUILDING_TEXTURE))->set_Sprite_Origin(CELL_WIDTH / 2.0f, CELL_HEIGHT * 1.0f);
            building_list->Find_Building(x, y, extract_filename_M(BUILDING_TEXTURE))->set_owner_id(PLAYER_NUMBER);
            MONEY[PLAYER_NUMBER-1]-=BUILDING_COST;
            std::cout << "Player Number: "<<PLAYER_NUMBER<<std::endl;
            std::cout << "Money: "<< MONEY[PLAYER_NUMBER-1] << std::endl;
            std::cout << std::endl;
            building* newBuilding = building_list->Find_Building(x, y, extract_filename_M(BUILDING_TEXTURE));
            if (newBuilding) { // Проверка на nullptr
                Health* healthDisplay = new Health(newBuilding);
                healthDisplays.push_back(healthDisplay);
            }
        } /*else {
            building_list->Select_Building(x, y, BUILDING_TEXTURE);
            building_list->Find_Building(x, y, extract_filename_M(BUILDING_TEXTURE))->set_Sprite_Origin(CELL_WIDTH / 2.0f, CELL_HEIGHT * 1.0f);
            building_list->Find_Building(x, y, extract_filename_M(BUILDING_TEXTURE))->set_owner_id(PLAYER_NUMBER);
            // BUILDING_TEXTURE = "";
            //функция для создания юнитов и других подвижных сущностей// Доделать определение ключа текстуры
        }*/
    } else {
        // building_list->Hit(x,y);
        if (Cells_Data[x][y]->get_Texture_Name() != "../Textures/MarsHoulLendPattern.png ") {
            // std::cout<<Cells_Data[x][y]->get_Texture_Name()<<"eljjnejjnvlek"<<'\n';
            building_list->Move(x,y, PLAYER_NUMBER);
        } else {
            building_list->Global_Diactivate();
        }
    }
    BUILDING_TEXTURE = "";
}

std::vector<int> Map::get_pressed_sell_position(int x, int y) {
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j <Size; j++) {
            float vector_x[2] = {0.5,-0.866};
            float vector_y[2] = {0.5,0.866};
            float k = 1/2.0f/0.88;
            int cell_x = ZERO_Y+CELL_WIDTH*(i*vector_x[1]*k + j*vector_y[1]*k)*SCALE;
            int cell_y = ZERO_X+CELL_HEIGHT*(i*vector_x[0]*k + j*vector_y[0]*k)*SCALE;
            if ((abs(cell_x - x) < CELL_WIDTH/2*SCALE*0.7) && (cell_y - y < CELL_HEIGHT*SCALE) && (cell_y - y > CELL_HEIGHT*SCALE*0.5)) {
                std::vector<int> Return;
                Return.push_back(i);
                Return.push_back(j);
                Pressed_Check(&Return);
                return Return;
            }
        }
    }
    std::vector<int> Return;
    Return.push_back(-1);
    Return.push_back(-1);
    return Return;
}

void Map::Map_Scale(int delta, std::string Scale_Type, std::map<std::string, float>* Constants) {
    float SCAIL_SPEED = (*Constants)["SCAIL_SPEED"];
    // std::cout << "SCAIL_SPEED: " << SCAIL_SPEED << std::endl;
    float SCREEN_HEIGHT = (*Constants)["SCREEN_HEIGHT"];
    // std::cout << "SCREEN_HEIGHT: " << SCREEN_HEIGHT << std::endl;
    float SCREEN_WIDTH = (*Constants)["SCREEN_WIDTH"];
    // std::cout << "SCREEN_WIDTH: " << SCREEN_WIDTH << std::endl;
    if (Scale_Type == "Mouse") {
        delta*=5;
    }
    if ((delta > 0) && (SCALE<1)) {
        SCALE += SCAIL_SPEED*abs(delta);
        ZERO_X -= (SCREEN_HEIGHT/2-ZERO_X)*SCAIL_SPEED/SCALE*abs(delta);
        ZERO_Y -= (SCREEN_WIDTH/2-ZERO_Y)*SCAIL_SPEED/SCALE*abs(delta);
    }
    if ((delta < 0) && (SCALE>0.2)){
        SCALE -= SCAIL_SPEED*abs(delta);
        ZERO_X += (SCREEN_HEIGHT/2-ZERO_X)*SCAIL_SPEED/SCALE*abs(delta);
        ZERO_Y += (SCREEN_WIDTH/2-ZERO_Y)*SCAIL_SPEED/SCALE*abs(delta);
    }
}

void Map::set_BUILDING_TEXTURE(std::string texture) {
    BUILDING_TEXTURE = texture;
    std::vector<int> Zochem;
    Zochem.push_back(building_list->Find_Building("FramePattern")->get_x_coordinate());
    Zochem.push_back(building_list->Find_Building("FramePattern")->get_y_coordinate());
    Pressed_Check(&Zochem);
}

bool Map::Check_Access(std::string teg){
    return available_buildings->Check_Access(PLAYER_NUMBER , teg);
}

int Map::get_Current_Player() {
    return PLAYER_NUMBER;
}

bool Map::Create_Mines() {
    int x =0;
    int y =0;
    int number = Size*Size/40;
    for (int i = 0; i < number; i++) {
        x = get_random_number_M(0, Size-2);
        y = get_random_number_M(0, Size-2);
        if (building_list->Add_Building(x,y,"../Textures/Mine.png")) {
            if (Cells_Data[x][y]->get_Texture_Name() == "../Textures/MarsHoulLendPattern.png " || Cells_Data[x][y]->get_Texture_Name() == "../Textures/MarsMountainLendPattern.png ") {
                if (building_list->Destroy_Building(x, y, "Mine")) {
                    std::cout<<"DESTROY MINE"<<std::endl;
                }
            } else {
                building_list->Find_Building(x, y, extract_filename_M("../Textures/Mine.png"))->set_Sprite_Origin(CELL_WIDTH / 1.7f, CELL_HEIGHT * 1.3f);
            }
        }
    }
    return true;
}

int Map::get_Money() {
    return MONEY[PLAYER_NUMBER-1];
}

void Map::set_Cost(int money) {
    BUILDING_COST = money;
}

void Map::Stonks() {
    MONEY[PLAYER_NUMBER-1] += building_list->Stonks(PLAYER_NUMBER) * 100;
    std::cout<<"PLayer: "<<PLAYER_NUMBER<<" Stonks: "<< MONEY[PLAYER_NUMBER-1]<<std::endl;
}
void Map::Animation() {
    float max_flactuation = 10.0;
    if (abs(Sprite_Flactuation[0]) > max_flactuation) {
        Sprite_Flactuation[1] = - Sprite_Flactuation[1];
    }
    Sprite_Flactuation[0] += Sprite_Flactuation[1]*(max_flactuation/20.0f/3.5f);
    if (building_list->get_Sprite_Active_Unit()) {
        building* Unit = building_list->get_Sprite_Active_Unit();
        Set_Sprite_Static_Position(Unit->get_Sprite_Pointer(), Unit->get_x_coordinate(), Unit->get_y_coordinate(), Sprite_Flactuation[0]);
        // std::cout<<"ANIMATION"<<std::endl;
    }
}

void Map::updateHealthDisplays() {
    auto it = healthDisplays.begin();
    while (it != healthDisplays.end()) {
        Health* health = *it;
        building* build = health->getBuilding();
        // Провекра на существование, если здания нет, то здоровье очиститься
        if (!building_list->contains(build) || build->get_health() <= 0) {
            delete health;
            it = healthDisplays.erase(it);
        } else {
            health->update();
            ++it;
        }
    }
}

void Map::drawHealthDisplays(sf::RenderWindow& window) {
    for (auto& health : healthDisplays) {
        if (health) {
            health->draw(window);
        }
    }
}