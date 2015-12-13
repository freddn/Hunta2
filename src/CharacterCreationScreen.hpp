

#ifndef CHARACTERCREATIONSCREEN_HPP
#define CHARACTERCREATIONSCREEN_HPP

#include "Screen.hpp"

struct CharacterCreationScreen : public Screen {
public:
    CharacterCreationScreen();
    void init();
    void update();
    void draw();

    void createCharacter();
    virtual ~CharacterCreationScreen();
private:
    std::string characterName;
};


#endif //HUNTA2_CHARACTERCREATIONSCREEN_HPP
