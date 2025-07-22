cmake_minimum_required(VERSION 3.31)
project(MIPT_Programming_project)

set(CMAKE_CXX_STANDARD 20)

# Добавляем аудиомодуль в REQUIRED COMPONENTS
find_package(SFML 2.6 COMPONENTS system window graphics audio REQUIRED)

add_executable(MIPT_With_Source
        Source_for_SFML2.6.0/main.cpp
        Source_for_SFML2.6.0/Cell.cpp
        Source_for_SFML2.6.0/Map.cpp
        Source_for_SFML2.6.0/Texture_List.cpp
        Source_for_SFML2.6.0/building.cpp
        Source_for_SFML2.6.0/Building_List.cpp
        Source_for_SFML2.6.0/Available_Buildings.cpp
        Source_for_SFML2.6.0/UI_Textures.cpp
        Source_for_SFML2.6.0/Health.cpp
        Source_for_SFML2.6.0/Miner.cpp
        Source_for_SFML2.6.0/unit.cpp
        Source_for_SFML2.6.0/barrak.cpp
        Source_for_SFML2.6.0/Hall.cpp
)

# Добавляем sfml-audio в линковку
target_link_libraries(MIPT_With_Source PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})