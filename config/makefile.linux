INCS = `freetype-config --cflags` -I/usr/include/lua5.1 -I/usr/include/GL
LIBS = `freetype-config --libs` -llua5.1 -lGL -lGLU \
       -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

CFLAGS += -g -Wall -O0 -std=c++11 ${INCS} ${CPPFLAGS}
LDFLAGS += -g ${LIBS}

CC = g++

SRC = src/Character.cpp \
      src/Editor.cpp \
      src/Enemy.cpp \
      src/EntityCreator.cpp \
      src/EntitySystem.cpp \
      src/Environment.cpp \
      src/Game.cpp \
      src/GPhysics.cpp \
      src/InGame.cpp \
      src/Inventory.cpp \
      src/Item.cpp \
      src/LoadMapData.cpp \
      src/LTimer.cpp \
      src/LuaInterface.cpp \
      src/LuaState.cpp \
      src/main.cpp \
      src/MainMenu.cpp \
      src/MapClass.cpp \
      src/MapCreator.cpp \
      src/Position.cpp \
      src/Renderer.cpp \
      src/Screen.cpp \
      src/Texture.cpp \
      src/Tile.cpp

OBJ = ${SRC:.cpp=.o}

all: options hunta2

options:
	@echo hunta2 build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.cpp.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $< -o $@

hunta2: ${OBJ}
	@echo runnin CC -o $@
	@${CC} -o $@ ${SRC} ${CFLAGS} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f hunta2
	@rm src/*.o

.PHONY: all hunta2 options clean
