# Hunta2
Game in very early stages. SDL/C++/(Lua)

## Keys
 - Main Menu, 2
 - Leveleditor, 4
 - Back to game/save, 1
 - Inventory, i
 - Shoot, left mouse button

## Using
 - Lua 5.1 (liblua5.1-0 liblua5.1-dev)
 - SDL 2.0 (libsdl2-dev libsdl2-image-dev libsdl-ttf2.0-dev)

## How to build
Either use the Code::Blocks project file or run `make'.

## Settings for windows in Code::Blocks
Project->Build Options->Linker Settings->Other linker options:</br>
-lSDL2main -lSDL2 -lSDL2\_image -lSDL2_ttf -llua51

Project->Build Options->Search directories->Compiler:</br>
include

Project->Build Options->Search directories->Linker:</br>
lib\x86 or lib\x64 (x64 not tested)
lib\lua
