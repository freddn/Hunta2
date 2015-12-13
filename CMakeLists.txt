cmake_minimum_required(VERSION 3.3)
project(Hunta2)

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-std=c++11 -I/usr/include/lua5.1 -Wall -pedantic")

SET(CMAKE_EXE_LINKER_FLAGS "-llua5.1 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf")


set(SOURCE_FILES
    src/Camera.cpp
    src/Camera.hpp
    src/Character.cpp
    src/Character.hpp
    src/CreateMap.lua
    src/Editor.cpp
    src/Editor.hpp
    src/Enemy.cpp
    src/Enemy.hpp
    src/EntitySystem.cpp
    src/EntitySystem.hpp
    src/Environment.cpp
    src/Environment.hpp
    src/Game.cpp
    src/Game.hpp
    src/Global.cpp
    src/Global.hpp
    src/GPhysics.cpp
    src/GPhysics.hpp
    src/Health.cpp
    src/Health.hpp
    src/Icon.cpp
    src/Icon.hpp
    src/InGame.cpp
    src/InGame.hpp
    src/Inventory.cpp
    src/Inventory.hpp
    src/InventoryFunctions.lua
    src/Item.cpp
    src/Item.hpp
    src/ItemManager.cpp
    src/ItemManager.hpp
    src/KeyboardController.cpp
    src/KeyboardController.hpp
    src/LoadInventory.lua
    src/LoadMap.lua
    src/LTimer.cpp
    src/LTimer.hpp
    src/LuaInterface.cpp
    src/LuaInterface.hpp
    src/main.cpp
    src/MainMenu.cpp
    src/MainMenu.hpp
    src/Map.cpp
    src/Map.hpp
    src/MapController.cpp
    src/MapController.hpp
    src/Melee.cpp
    src/Melee.hpp
    src/MouseController.cpp
    src/MouseController.hpp
    src/PlayerController.cpp
    src/PlayerController.hpp
    src/Position.cpp
    src/Position.hpp
    src/Projectile.cpp
    src/Projectile.hpp
    src/Ranged.cpp
    src/Ranged.hpp
    src/SaveChar.lua
    src/Screen.cpp
    src/Screen.hpp
    src/Shape.cpp
    src/Shape.hpp
    src/Sound.cpp
    src/Sound.hpp
    src/Texture.cpp
    src/Texture.hpp
    src/TextureManager.cpp
    src/TextureManager.hpp
    src/Tile.cpp
    src/Tile.hpp
    src/UIController.cpp
    src/UIController.hpp
    src/Weapon.cpp
    src/Weapon.hpp src/EnemyDataController.cpp src/EnemyDataController.hpp src/CharacterCreationScreen.cpp src/CharacterCreationScreen.hpp src/HelperFunctions.cpp src/HelperFunctions.hpp)

add_executable(Hunta2 ${SOURCE_FILES})
target_link_libraries(Hunta2 ${FREETYPE_LIBRARIES})