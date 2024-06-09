#pragma once
#include <ncurses.h>

class TerminalUIObject
{
protected:
    WINDOW *window;

public:
    TerminalUIObject() = default;
    TerminalUIObject(int height, int width, int yPosition, int xPosition);

    int startX();
    int startY();

    int endX();
    int endY();

    void repositionVerticaly(int deltaY);
    void setNewY(int newY);

    bool isCursorInWindow(int CursorY, int CursorX);

    WINDOW *getWindow();
    virtual void draw() = 0;

    virtual ~TerminalUIObject() = default;
};