

# Link with external libs
set(CMAKE_EXE_LINKER_FLAGS "-llua5.1 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf")

include_directories(


)

set(GAME_LIBS
    ${COMPONENTS_LIB}
    ${UI_LIB}
    ${SCRIPTING_LIB}
    ${EDITOR_LIB}
    ${PHYSICS_LIB}
) 

# Source files to build
set(SOURCE_FILES
    Game.cpp
    Global.cpp
    Inventory.cpp
    ItemManager.cpp
    KeyboardController.cpp
    LTimer.cpp
    Main.cpp
    Map.cpp
    MapController.cpp
    MouseController.cpp
    PlayerController.cpp
    TextureManager.cpp
    EnemyManager.cpp
    HelperFunctions.cpp
)

add_executable(hunta2 ${SOURCE_FILES})
target_link_libraries(hunta2 ${CMAKE_EXE_LINKER_FLAGS} ${GAME_LIBS})
