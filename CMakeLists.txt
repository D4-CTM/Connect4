cmake_minimum_required (VERSION 3.0)
project (Connect4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Game)
include_directories(${CMAKE_SOURCE_DIR}/TextConsole)

add_executable(${PROJECT_NAME}  TextConsole/TextConsole.cpp
                                Game/Scenes/Connect4_Game/BoardRenderer.hpp
                                Game/Scenes/Connect4_Game/ReviewMode.cpp
                                Game/Scenes/Connect4_Game/Tiles.cpp
                                Game/Scenes/Connect4_Game/Game.cpp
                                Game/Scenes/Menu/Menu.cpp
                                Game/Scenes/SceneManager.cpp
                                Game/Scenes/Ranking/RankingManager.cpp
                                Game/Scenes/Ranking/RankingScene.cpp
                                Game/Scenes/ResultScreen/ResultScene.cpp
                                Game/Scenes/Timer/Timer.cpp
                                Game/Connect4.cpp
                                Game/Main.cpp
              )

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} -lpthread)
target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++)