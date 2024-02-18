set(PHYSICS_LIB
    physics
)

include_directories(
    ../
)


set(PHYSICS_SRC
    Body.cpp
    PhysicsEngine.cpp
    Manifold.cpp
    Collision.cpp
)

add_library(${PHYSICS_LIB} ${PHYSICS_SRC})
