set(SCRIPTING_LIB
    scripting
)

include_directories(
    ../
    ${PROJECT_SOURCE_DIR}/include
)


set(SCRIPTING_SRC
    LuaInterface.cpp
)

#add_library(${SCRIPTING_LIB} ${SCRIPTING_SRC})
