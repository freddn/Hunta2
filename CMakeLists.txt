cmake_minimum_required(VERSION 3.3)
project(Hunta2)

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-std=c++11 -I/usr/include/lua5.1 -Wall -pedantic")

SET(CMAKE_EXE_LINKER_FLAGS "-llua5.1 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf")


set(SOURCE_FILES
        src/components/Camera.cpp
        src/components/Camera.hpp
        src/components/Character.cpp
        src/components/Character.hpp
        src/lua/CreateMap.lua
        src/tools/Editor.cpp
        src/tools/Editor.hpp
        src/components/Enemy.cpp
        src/components/Enemy.hpp
    src/EntitySystem.cpp
    src/EntitySystem.hpp
        src/components/Environment.cpp
        src/components/Environment.hpp
    src/Game.cpp
    src/Game.hpp
    src/Global.cpp
    src/Global.hpp
        src/components/GPhysics.cpp
        src/components/GPhysics.hpp
        src/components/Health.cpp
        src/components/Health.hpp
        src/ui/Icon.cpp
        src/ui/Icon.hpp
        src/ui/InGame.cpp
        src/ui/InGame.hpp
    src/Inventory.cpp
    src/Inventory.hpp
        src/lua/InventoryFunctions.lua
        src/components/Item.cpp
        src/components/Item.hpp
    src/ItemManager.cpp
    src/ItemManager.hpp
    src/KeyboardController.cpp
    src/KeyboardController.hpp
        src/lua/LoadInventory.lua
        src/lua/LoadMap.lua
    src/LTimer.cpp
    src/LTimer.hpp
        src/lua/LuaInterface.cpp
        src/lua/LuaInterface.hpp
    src/Main.cpp
        src/ui/MainMenu.cpp
        src/ui/MainMenu.hpp
    src/Map.cpp
    src/Map.hpp
    src/MapController.cpp
    src/MapController.hpp
        src/components/Melee.cpp
        src/components/Melee.hpp
    src/MouseController.cpp
    src/MouseController.hpp
    src/PlayerController.cpp
    src/PlayerController.hpp
        src/components/Position.cpp
        src/components/Position.hpp
        src/components/Projectile.cpp
        src/components/Projectile.hpp
        src/components/Ranged.cpp
        src/components/Ranged.hpp
        src/lua/SaveChar.lua
        src/ui/Screen.cpp
        src/ui/Screen.hpp
    src/Sound.cpp
    src/Sound.hpp
        src/components/Texture.cpp
        src/components/Texture.hpp
    src/TextureManager.cpp
    src/TextureManager.hpp
        src/components/Tile.cpp
        src/components/Tile.hpp
        src/ui/UIController.cpp
        src/ui/UIController.hpp
        src/components/Weapon.cpp
        src/components/Weapon.hpp
        src/EnemyManager.cpp
        src/EnemyManager.hpp
        src/ui/CharacterCreationScreen.cpp
        src/ui/CharacterCreationScreen.hpp
        src/HelperFunctions.cpp
        src/HelperFunctions.hpp
        src/ui/SaveSlotSelection.cpp
        src/ui/SaveSlotSelection.hpp
        src/ui/Button.cpp
        src/ui/Button.hpp
        src/ui/TextInputField.cpp
        src/ui/TextInputField.hpp
        src/ui/TextInputBox.cpp
        src/ui/TextInputBox.hpp
        src/lua/LuaLoadFunctions.hpp
        src/lua/LuaInGameFunctions.hpp
        src/lua/LuaGeneralFunctions.hpp
        src/Enums.hpp
        src/ui/TextBox.cpp
        src/ui/TextBox.hpp
        src/physics/Body.cpp
        src/physics/Body.hpp
        src/physics/PhysicsEngine.cpp
        src/physics/PhysicsEngine.hpp
        src/physics/Manifold.cpp
        src/physics/Manifold.hpp
        src/physics/Shape.hpp
        src/physics/Vec2.hpp
        src/physics/Math.h
        src/physics/Collision.cpp
        src/physics/Collision.hpp)

add_executable(Hunta2 ${SOURCE_FILES})
target_link_libraries(Hunta2 ${FREETYPE_LIBRARIES})