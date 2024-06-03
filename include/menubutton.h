#pragma once
#include <ncurses.h>
#include <string>

#include "consoleuiobject.h"
// #include "popuphandler.h"

class PopUpHandler;

class MenuButton : public TerminalUIObject
{
protected:
    std::string title;
    bool selected = false;

public:
    MenuButton(int height, int width, int yPosition, int xPosition, std::string title, bool selected = false) // not passed by reference due to nature of initialization of buttons
        : TerminalUIObject(height, width, yPosition, xPosition), title(title), selected(selected)
    {
        draw();
    }
    void draw() override
    {
        box(window, 0, 0);
        if (selected)
            wattr_on(window, A_REVERSE, nullptr);
        mvwprintw(window, 1, 1, title.c_str());
        wattr_off(window, A_REVERSE, nullptr);

        wrefresh(window);
    }
    void activate()
    {
        selected = true;
    }

    void deactivate()
    {
        selected = false;
    }

    virtual void pressed() = 0;
};

class CloseButton : public MenuButton
{
    PopUpHandler *popUpHandler;

public:
    CloseButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, bool selected = false)
        : MenuButton(height, width, yPosition, xPosition, std::string("Close"), selected),
          popUpHandler(popUpHandler) {}

    void pressed() override
    {
        printw("babsababa");
    }
};