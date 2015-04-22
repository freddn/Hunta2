VERSION = 0.1

PREFIX = /usr/local
MANPREFIX = ${PREFIX}/man

INCS = `freetype-config --cflags` -I/usr/include/lua5.1 -I/usr/include/GL
LIBS = `freetype-config --libs` -llua5.1 -lGL -lGLU \
       -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

CPPFLAGS = -DVERSION=\"${VERSION}\"
CFLAGS += -g -Wall -O0 -std=c++11 ${INCS} ${CPPFLAGS}
LDFLAGS += -g ${LIBS}

CC = g++
