set(UI_LIB
    ui
)

include_directories(
    ../
)


set(UI_SRC
    Icon.cpp
    MainMenu.cpp
    InGame.cpp
    Screen.cpp
    UIController.cpp
    CharacterCreationScreen.cpp
    SaveSlotSelection.cpp
)

#add_library(${UI_LIB} ${UI_SRC})
