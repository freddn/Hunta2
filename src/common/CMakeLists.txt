set(COMMON_LIB
    common
)

include_directories(
)


set(COMMON_SRC
    HelperFunctions.cpp
    LTimer.cpp
)

add_library(${COMMON_LIB} ${COMMON_SRC})
