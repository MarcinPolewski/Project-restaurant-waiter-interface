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
    UITable(WINDOW *backgroundWindow, Table &table);

    Table *getTable();

    void draw() override;
};