set(COMPONENTS_LIB
    components
)

include_directories(
    ../
)


set(COMPONENTS_SRC
    Button.cpp
    Camera.cpp
    Character.cpp
    Enemy.cpp
    EntitySystem.cpp
    Environment.cpp
    GPhysics.cpp
    Health.cpp
    Item.cpp
    ItemManager.cpp
    KeyboardController.cpp
    Melee.cpp
    MouseController.cpp
    Position.cpp
    Projectile.cpp
    Ranged.cpp
    Sound.cpp
    TextBox.cpp
    TextInputBox.cpp
    TextInputField.cpp
    Texture.cpp
    TextureManager.cpp
    Tile.cpp
    Weapon.cpp
)

#add_library(${COMPONENTS_LIB} ${COMPONENTS_SRC})
