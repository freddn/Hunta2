

#ifndef CHARACTERCREATIONSCREEN_HPP
#define CHARACTERCREATIONSCREEN_HPP

#include "Screen.hpp"

// TODO Make struct/class with slot information..
// TODO !! Make so that records in saveslots replaces their old one !!

struct CharacterCreationScreen : public Screen {
public:
    CharacterCreationScreen();
    void init();
    void update(SDL_Event *e);
    void draw();

    int getSaveSlot(std::string);

    void saveSlot(int slot, std::string name, int level);

    void createCharacter();
    virtual ~CharacterCreationScreen();
private:
    std::string inputText;
    SDL_Color textColor;
    unsigned int maxlen = 14;

    Texture text;
    Texture desc;

    bool saveslot1 = false;
    bool saveslot2 = false;
    bool saveslot3 = false;

    std::string name1 = "No saved game";
    std::string name2 = "No saved game";
    std::string name3 = "No saved game";

    int level1 = 0;
    int level2 = 0;
    int level3 = 0;

    std::map<std::string, int> nameOnSlot;
};


#endif //HUNTA2_CHARACTERCREATIONSCREEN_HPP
