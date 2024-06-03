#pragma once

#include <ncurses.h>
#include <vector>

#include "consoleuiobject.h"
#include "popuphandler.h"
#include "menubutton.h"
#include "uitable.h"

class PopUpMenu : public TerminalUIObject
{
protected:
    std::vector<std::unique_ptr<MenuButton>> buttons;
    int selected = 0;
    PopUpHandler *popUpHandler;

public:
    PopUpMenu(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler)
        : TerminalUIObject(height, width, yPosition, xPosition), popUpHandler(popUpHandler)
    {
    }

    // this constructor turned out ugly, because it's the only way to call another constructor
    PopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, int height = 40, int width = 60)
        : PopUpMenu(height, width,
                    getbegy(background) + ((getmaxy(background) - height) / 2),
                    getbegx(background) + ((getmaxx(background) - width) / 2),
                    popUpHandler)
    {
    }

    void draw() override
    {
        box(window, 0, 0);
        for (auto &it : buttons)
        {
            it->draw();
        }
    }

    void moveUp()
    {
        buttons[selected]->deactivate();
        if (selected == 0)
            selected = buttons.size() - 1;
        else
            --selected;
        buttons[selected]->activate();
    }

    void moveDown()
    {
        buttons[selected]->deactivate();
        if (selected == (int)buttons.size() - 1)
            selected = 0;
        else
            ++selected;
        buttons[selected]->activate();
    }

    void buttonPressed()
    {
        buttons[selected]->pressed();
    }
};

class TablePopUpMenu : public PopUpMenu
{
    // using PopUpMenu::PopUpMenu;
    UITable table;

public:
    TablePopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, UITable &table, int height = 40, int width = 60)
        : PopUpMenu(background, popUpHandler, height, width), table(table)
    {
        // initialize buttons

        int buttonX = startX() + BUTTON_SIDE_OFFSET;
        int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

        buttons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, true));
        buttonY += BUTTON_HEIGHT;
        buttons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
        buttonY += BUTTON_HEIGHT;
        buttons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    }
};