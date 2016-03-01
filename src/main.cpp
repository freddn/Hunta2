/* Copyright (C) 2015  Fredrik Mörtberg <fredrikmo@hotmail.com>
 *
 * This file is a part of the Hunta2 project.
 *
 * Hunta2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Hunta2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hunta2.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Game.hpp"
#include "HelperFunctions.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    bool fullscreen = false;
    if(argc > 2) {
        HelperFunctions::log(HelperFunctions::WARNING,
                             "Wrong amount of arguments, run: ./hunta2 or ./hunta2 f");
        return 0;
    } else if(argc == 2) {
        if(*argv[1] == 'f')
            fullscreen = true;
    }

    if(!game::initVideo(fullscreen)) {
        HelperFunctions::log(HelperFunctions::ERROR,"Initializing of video failed.");
        game::close();
        return 1;
    } else if(!game::initTextureHandling()) {
        HelperFunctions::log(HelperFunctions::ERROR,"Initializing of texture handling failed.");
        game::close();
        return 1;
    }

    game::start();
    game::close();
    return 0;
}




