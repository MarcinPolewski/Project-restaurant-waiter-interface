#pragma once

#include <ncurses.h>

#include "table.h"
#include "uitable.h"
#include "constants.h"
#include "consoleuiobject.h"

class UITable : public TerminalUIObject
{
    int height = CURSORSPEED, width = COLUMN_TO_WIDTH_RATION * height - 1; // height and width mu
    int rawCoordinate, columnCoordinate;                                   // deteremine position of top left corner on the screen

    // ==== each table is printed so, that cursor always lands in the middle
    int howManyColumnsFromCeneter = (width - 1) / 2;
    int howManyRowsFromCenter = (height - 1) / 2;

    Table &table;

public:
    UITable(WINDOW *backgroundWindow, Table &table) : table(table)
    {
        rawCoordinate = (table.position.y) * CURSORSPEED - howManyRowsFromCenter;
        columnCoordinate = (table.position.x) * CURSORSPEED * COLUMN_TO_WIDTH_RATION - howManyColumnsFromCeneter;

        window = newwin(height, width, rawCoordinate + getbegy(backgroundWindow), columnCoordinate + getbegx(backgroundWindow));
        box(window, 0, 0);
        wrefresh(window);
    }

    Table *getTable()
    {
        return &table;
    }

    void draw() override
    {
        box(window, 0, 0);
        wrefresh(window);
    }
    void activate();
    void deactivate();
};