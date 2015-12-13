//
// Created by fredrik on 12/13/15.
//

#ifndef HUNTA2_HELPERFUNCTIONS_HPP
#define HUNTA2_HELPERFUNCTIONS_HPP

#include <string>

/**
 * DEBUG = Print all messages and errors.
 * DEBUG_LESS = Print only errors and warnings.
 * NONE = Print nothing
 */
#define DEBUG
//#define DEBUG_LESS

namespace HelperFunctions {
    enum types {
        ERROR,
        MESSAGE,
        WARNING
    };
    int random(int from, int to, int seed);

    void log(std::string);
    void log(int, std::string);
}

#endif //HUNTA2_HELPERFUNCTIONS_HPP
