# Hunta v0.1
[![Build Status](https://travis-ci.org/freddn/Hunta2.svg)](https://travis-ci.org/freddn/Hunta2)

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
 - Lua 5.1
 - SDL2
 - C++11

## Requirements
On Debian-derived systems make sure you have `build-essential` installed.

## Dependencies
`liblua5.1-dev libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libfreetype6-dev`

## How to build on BSD/Linux
Either use the Code::Blocks project file or run `make system', where system is one of the following:
 - linux
 - slackware
 - freebsd
 - dragonfly
 - openbsd

## How to build on Windows
Use the Code::Blocks project file. In Code::Blocks, change the build target to "Debug Windows" when compiling.
