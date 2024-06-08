#pragma once
#include <ncurses.h>

class TerminalUIObject
{
protected:
    WINDOW *window;

public:
    TerminalUIObject() = default;
    TerminalUIObject(int height, int width, int yPosition, int xPosition)
    {
        window = newwin(height, width, yPosition, xPosition);
        // box(window, 0, 0);
        // wrefresh(window);
    }

    int startX()
    {
        return getbegx(window);
    }

    int startY()
    {
        return getbegy(window);
    }

    int endX()
    {
        return getbegx(window) + getmaxx(window) - 1;
    }

    int endY()
    {
        return getbegy(window) + getmaxy(window) - 1;
    }

    void repositionVerticaly(int deltaY)
    {
        mvwin(window, startY() + deltaY, startX());
    }

    void setNewY(int newY)
    {
        mvwin(window, newY, startX());
    }

    bool isCursorInWindow(int CursorY, int CursorX) // borders do not cound as window
    {
        return (CursorX > startX() && CursorX < endX() && CursorY > startY() && CursorY < endY());
    }
    WINDOW *getWindow()
    {
        return window;
    }

    virtual void draw() = 0;

    virtual ~TerminalUIObject() = default;
};