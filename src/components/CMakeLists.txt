set(COMPONENTS_LIB
    components
)

include_directories(
    ../
)


set(COMPONENTS_SRC
    EntitySystem.cpp
    Camera.cpp
    Character.cpp
    Enemy.cpp
    Environment.cpp
    GPhysics.cpp
    Health.cpp
    Item.cpp
    Melee.cpp
    Position.cpp
    Projectile.cpp
    Ranged.cpp
    Texture.cpp
    Tile.cpp
    Weapon.cpp
)

add_library(${COMPONENTS_LIB} ${COMPONENTS_SRC})
