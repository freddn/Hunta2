# Hunta v0.1
[![Build Status](https://travis-ci.org/freddn/Hunta2.svg)](https://travis-ci.org/freddn/Hunta2)

Game in very early stages. SDL2/C++/Lua


## Keys
 - Main Menu, 2
 - Leveleditor, 4
 - Back to game/save, 1
 - Inventory, i
 - Shoot, left mouse button
 - Attack, space
 - Change tile in editor, mousescroll
 - Place tile, left mouse button
 - Move, arrow keys

## Using
 - Lua 5.1 (liblua5.1-dev)
 - SDL2 (libsdl2-dev libsdl2-image-dev libsdl-ttf2.0-dev)
 - C++11

## How to build on BSD/Linux
Either use the Code::Blocks project file or run `make system', where system is one of the following:
 - linux
 - slackware
 - freebsd
 - dragonfly 

## How to build on Windows
Use the Code::Blocks project file. In Code::Blocks, change the build target to "Debug Windows" when compiling.
