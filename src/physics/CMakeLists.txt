set(PHYSICS_LIB
    physics
)

include_directories(
    ../
)


set(PHYSICS_SRC
    Body.cpp
    Collision.cpp
    Manifold.cpp
    PhysicsEngine.cpp
)

add_library(${PHYSICS_LIB} ${PHYSICS_SRC})
