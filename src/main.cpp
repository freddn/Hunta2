
#include "Game.hpp"
#include "EntitySystem.hpp"


int main(int argc, char *argv[])
{
    if(!game::init_game())
    {
        std::cerr << "Init failed." << std::endl;
        game::close();
    }

    game::start();
    game::close();

    return 0;
}




