#ifndef UICONTROLLER_H
#define UICONTROLLER_H


#include "Inventory.hpp"

class UIController {
public:
    UIController();
    UIController( const UIController &obj);

    void init();
    void draw();
    void update();

    virtual ~UIController();
protected:
private:
    Texture tInterface;

    Inventory *inventory{nullptr};
    bool showInventory = false;
    const Uint8 *key = 0;
    int buf = 0;
};

#endif // UICONTROLLER_H
