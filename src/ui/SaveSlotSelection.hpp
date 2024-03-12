
#ifndef HUNTA2_SAVESLOTSELECTION_HPP
#define HUNTA2_SAVESLOTSELECTION_HPP


#include "../components/Button.hpp"

class SaveSlotSelection {
public:
    SaveSlotSelection();
    void init();
    void draw();

    void update(SDL_Event *e);

    void setSlot(int slot, std::string name, int level);

    ~SaveSlotSelection();

private:
    Button slot1;
    Button slot2;
    Button slot3;
};


#endif //HUNTA2_SAVESLOTSELECTION_HPP
