cmake_minimum_required(VERSION 3.29)
project(MIPT_With_Source)

set(CMAKE_CXX_STANDARD 17)
set(SFML_INCLUDE_DIR "/usr/include")
set(SFML_LIBRARY_DIR "/usr/lib")


include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR})
add_executable(MIPT_With_Source Source/main.cpp
        Source/Cell.cpp
        Source/Map.cpp
        Source/Texture_List.cpp
        Source/building.cpp
        Source/Building_List.cpp
        Source/Available_Buildings.cpp)

find_package(SFML COMPONENTS System Window Graphics REQUIRED)
target_link_libraries(MIPT_With_Source sfml-graphics sfml-window sfml-system)

# Копируем Textures в папку сборки (чтобы пути к текстурам были простыми)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})