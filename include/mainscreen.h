#pragma once

#include "consoleuiobject.h"
#include "uitable.h"
#include <vector>

class MainScreen : public TerminalUIObject
{
private:
    std::vector<UITable> tables;

public:
    MainScreen(int height, int width, int positionY, int positionX);
    void addTables(UIRestaurant *restaurant);
    void draw() override;

    bool pressed(int cursorY, int cursorX, UITable *&pressedTable); // checks if table was pressed, if so retur n true
};
