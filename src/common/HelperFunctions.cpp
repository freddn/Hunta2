#include "HelperFunctions.hpp"

#include <time.h>
#include <stdlib.h>

#if defined(DEBUG) || defined(DEBUG_LESS)
#include <iostream>
#endif
namespace HelperFunctions {

    int random(int from, int to, int seed) {
        srand (seed);
        return (rand()%(to-from+1)) + from;

    }
#if defined(DEBUG_LESS)
    void log(std::string str) {
            log(MESSAGE,str);
    }
    void log(int type, std::string str) {
        if(type == ERROR)
            std::cerr << " ERROR " << str << std::endl;
        else if(type == WARNING)
            std::cerr << " WARNING " << str << std::endl;
    }

#elif defined(DEBUG)
    void log(std::string str) {
        log(MESSAGE,str);
    }
    void log(int type, std::string str) {
        if(type == ERROR)
            std::cerr << "ERROR: " << str << std::endl;
        else if(type == WARNING)
           std::cerr << "WARNING: " << str << std::endl;
        else
            std::cerr << "MESSAGE: " << str << std::endl;
    }

#else
    void log(std::string str) { }

    void log(int type, std::string str) { }
#endif

}