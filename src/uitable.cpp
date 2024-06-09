#include "uitable.h"

UITable::UITable(WINDOW *backgroundWindow, Table &table)
    : table(table)
{
    rawCoordinate = (table.position.y) * CURSORSPEED - howManyRowsFromCenter;
    columnCoordinate = (table.position.x) * CURSORSPEED * COLUMN_TO_WIDTH_RATION - howManyColumnsFromCeneter;

    window = newwin(height, width, rawCoordinate + getbegy(backgroundWindow), columnCoordinate + getbegx(backgroundWindow));
    box(window, 0, 0);
    wrefresh(window);
}

Table *UITable::getTable()
{
    return &table;
}

void UITable::draw()
{
    box(window, 0, 0);
    wrefresh(window);
}
