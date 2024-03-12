

# Link with external libs
set(CMAKE_EXE_LINKER_FLAGS "-llua5.1 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf")

include_directories(
    common/
    components/
    physics/
    scripting/
    tools/
    ui/
)

set(GAME_LIBS
    common
    physics
    #${UI_LIB}
    #${SCRIPTING_LIB}
    #${EDITOR_LIB}
    #${PHYSICS_LIB}
)

set(COMPONENTS_SRC
    components/Button.cpp
    components/Camera.cpp
    components/Character.cpp
    components/Enemy.cpp
    components/EntitySystem.cpp
    components/Environment.cpp
    components/GPhysics.cpp
    components/Health.cpp
    components/Item.cpp
    components/ItemManager.cpp
    components/KeyboardController.cpp
    components/Melee.cpp
    components/MouseController.cpp
    components/Position.cpp
    components/Projectile.cpp
    components/Ranged.cpp
    components/Sound.cpp
    components/TextBox.cpp
    components/TextInputBox.cpp
    components/TextInputField.cpp
    components/Texture.cpp
    components/TextureManager.cpp
    components/Tile.cpp
    components/Weapon.cpp
)

set(UI_SRC
    scripting/LuaInterface.cpp
    tools/Editor.cpp
    ui/Icon.cpp
    ui/MainMenu.cpp
    ui/InGame.cpp
    ui/Screen.cpp
    ui/UIController.cpp
    ui/CharacterCreationScreen.cpp
    ui/SaveSlotSelection.cpp
)

# Source files to build
set(SRC_FILES
    Game.cpp
    Global.cpp
    Inventory.cpp
    Main.cpp
    Map.cpp
    MapController.cpp
    PlayerController.cpp
    EnemyManager.cpp
)

add_executable(hunta2 ${SRC_FILES} ${UI_SRC} ${COMPONENTS_SRC})
target_link_libraries(hunta2 ${CMAKE_EXE_LINKER_FLAGS} ${GAME_LIBS})
