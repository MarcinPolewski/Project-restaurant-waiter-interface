#pragma once

#include <ncurses.h>
#include <vector>
#include "consoleuiobject.h"

class TopBar : public TerminalUIObject
{
    int selection = 0; // inx to currently pointed button
    std::vector<std::string> buttons;
    bool active = true;

public:
    TopBar(int height, int width, int positionY, int positionX) : TerminalUIObject(height, width, positionY, positionX)
    {
        buttons = {"Change Waiter", "Menu", "Remote Orders", "Local Orders", "Close Restarurant", "flaskdjflaksdj"};
        draw();
    }

    void draw() override
    {
        int width = getmaxx(window);
        int widthPerButton = width / buttons.size();

        // ============== draw buttons to window
        int cursorX = 1;
        int cursorY = 1;

        for (int i = 0; i < (int)buttons.size(); i++)
        {

            // calculate button position offset from the left
            int offset = (widthPerButton - buttons[i].size()) / 2;

            if (active && i == selection) // print menu as selected if neccessary
                wattr_on(window, A_REVERSE, nullptr);
            mvwprintw(window, cursorY, cursorX + offset, buttons[i].c_str());

            wattr_off(window, A_REVERSE, nullptr);
            cursorX += widthPerButton;
            if (i != (int)buttons.size() - 1)
                mvwprintw(window, cursorY, cursorX - 1, "|");
        }
        wrefresh(window);
    }
    void activate()
    {
        active = true;
    }
    void deactivate()
    {
        active = false;
    }
    void moveLeft()
    {
        if (selection == 0)
            selection = buttons.size() - 1;
        else
            --selection;
    }
    void moveRight()
    {
        if (selection == (int)buttons.size() - 1)
            selection = 0;
        else
            ++selection;
    }
};