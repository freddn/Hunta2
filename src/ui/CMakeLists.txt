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
    Button.cpp
    TextInputField.cpp
    TextInputBox.cpp
    TextBox.cpp
)

add_library(${UI_LIB} ${UI_SRC})
