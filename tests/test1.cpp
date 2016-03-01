#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/Texture.hpp"
#include "../src/Game.hpp"


unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}



TEST_CASE( "Texture loading" ) {
    game::initVideo(false);
    game::initTextureHandling();
    Texture texture;
    texture.loadFromFile("tests/hat.png");

    REQUIRE(texture.getImgPath() == "tests/hat.png");
    game::close();
}

#include "../src/LuaInterface.hpp"
#include "../src/Global.hpp"

TEST_CASE( "Testing loading of tiles" ) {
    game::initVideo(false);
    game::initTextureHandling();

    LuaInterface lInterface;
    lInterface.initLua();
    lInterface.loadFile("tests/maps.lua");
    game::getTextureMapController()->init(&lInterface);

    REQUIRE(game::getTextureMapController()->mapExists(1));

    lInterface.loadFile("tests/tiles.lua");

    REQUIRE(game::getTextureMapController()->getMap(1)->getTileCount() == 64*64);


}





