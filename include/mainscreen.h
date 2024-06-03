#pragma once

#include "consoleuiobject.h"
#include "uitable.h"
#include <vector>

class MainScreen : public TerminalUIObject
{
public:
private:
    std::vector<UITable> tables;

public:
    MainScreen(int height, int width, int positionY, int positionX) : TerminalUIObject(height, width, positionY, positionX)
    {
    }

    // ======= getters that return corner values of x,y
    void addTables(std::vector<Table> &tables)
    {

        for (auto &it : tables)
        {
            this->tables.push_back(UITable(window, it));
        }
    }

    void draw() override
    {
        box(window, 0, 0);
        wrefresh(window);
        for (auto &it : tables)
        {
            it.draw();
        }
        wrefresh(window);
    }

    bool pressed(int cursorY, int cursorX, UITable *&pressedTable) // checks if table was pressed, if so retur n true
    {

        for (auto &it : tables)
        {
            if (it.isCursorInWindow(cursorY, cursorX))
            {
                pressedTable = &it;
                // 1. create new window
                // popUpMenu.reset(new TablePopUpMenu(window));
                // pointerToMenu.reset(new TablePopUpMenu(window));
                return true;
            }
        }
        return false;
    }
};
