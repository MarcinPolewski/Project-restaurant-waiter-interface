#include "consoleuiobject.h"
#include <ncurses.h>

TerminalUIObject::TerminalUIObject(int height, int width, int yPosition, int xPosition)
{
    window = newwin(height, width, yPosition, xPosition);
}

int TerminalUIObject::startX()
{
    return getbegx(window);
}

int TerminalUIObject::startY()
{
    return getbegy(window);
}

int TerminalUIObject::endX()
{
    return getbegx(window) + getmaxx(window) - 1;
}

int TerminalUIObject::endY()
{
    return getbegy(window) + getmaxy(window) - 1;
}

void TerminalUIObject::repositionVerticaly(int deltaY)
{
    mvwin(window, startY() + deltaY, startX());
}

void TerminalUIObject::setNewY(int newY)
{
    mvwin(window, newY, startX());
}

bool TerminalUIObject::isCursorInWindow(int CursorY, int CursorX) // borders do not cound as window
{
    return (CursorX > startX() && CursorX < endX() && CursorY > startY() && CursorY < endY());
}
WINDOW *TerminalUIObject::getWindow()
{
    return window;
}
