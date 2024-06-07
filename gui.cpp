#include <ncurses.h>

#include <string>
#include <vector>

#include <restaurant.h>

enum class aplicationState
{
    mainScreen,
    topBar,
    popUpMenu
};

int main()
{
    // ============= initialize screen, set up memory and clear screen
    initscr();
    noecho();    // do not write user input on screen
    cbreak();    // exit on cntr+c
    curs_set(0); // make cursor invisible (1-normal ; 2-highly visible )
    start_color();
    // raw();

    // ============= colors configuration
    // init_pair(COLOR_SELECT, COLOR_WHITE, COLOR_BLACK);
    // init_pair(COLOR_NORMAL, COLOR_BLACK, COLOR_WHITE);

    // attron(COLOR_PAIR(COLOR_NORMAL));
    // refresh();
    // ============= get max dimensions of terminal window
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // ============= initialize restaurant class
    Restaurant restaurant;

    // ============= initialize screen elements
    refresh();
    MainScreen mainscreen(yMax - TOPBARHEIGHT, xMax, TOPBARHEIGHT, 0);
    PopUpHandler popUpHandler(mainscreen.getWindow(), &restaurant);
    TopBar topbar(TOPBARHEIGHT, xMax, 0, 0, &popUpHandler, &restaurant);
    mainscreen.addTables(restaurant.getTables());

    keypad(stdscr, true);

    // ============= main program loop
    int userInput;
    int cursorX, cursorY;
    aplicationState state = aplicationState::topBar;
    aplicationState previousState;

    do
    {

        userInput = getch();

        // ========== handle user input
        if (userInput == 'q')
            break;

        if (state == aplicationState::topBar)
        {

            switch (userInput)
            {
            case KEY_RIGHT:
                topbar.moveRight();
                break;
            case KEY_LEFT:
                topbar.moveLeft();
                break;
            case KEY_DOWN:
                state = aplicationState::mainScreen;
                topbar.deactivate();

                cursorX = mainscreen.startX() + CURSORSPEED * COLUMN_TO_WIDTH_RATION; // getbegx(mainScreen) + 1;
                cursorY = mainscreen.startY() + CURSORSPEED;                          // getbegy(mainScreen) + 1;
                move(cursorY, cursorX);
                curs_set(1);
                break;
            case 10:
                if (topbar.pressed())
                {
                    previousState = state;
                    topbar.deactivate();

                    state = aplicationState::popUpMenu;
                }

                break;
            }
            topbar.draw();
        }
        else if (state == aplicationState::mainScreen)
        {
            switch (userInput)
            {
            case KEY_RIGHT:
                cursorX += CURSORSPEED * 2;
                if (cursorX >= mainscreen.endX())
                    cursorX = mainscreen.startX() + CURSORSPEED * COLUMN_TO_WIDTH_RATION;
                move(cursorY, cursorX);
                break;
            case KEY_LEFT:
                cursorX -= CURSORSPEED * 2;
                if (cursorX <= mainscreen.startX())
                {
                    // x must be a multiple of CURSORSPEED
                    cursorX = mainscreen.endX() - CURSORSPEED * COLUMN_TO_WIDTH_RATION;
                    cursorX -= cursorX % (CURSORSPEED * COLUMN_TO_WIDTH_RATION);
                }
                move(cursorY, cursorX);
                break;
            case KEY_DOWN:
                cursorY += CURSORSPEED;
                if (cursorY >= mainscreen.endY())
                    cursorY = mainscreen.startY() + CURSORSPEED;
                move(cursorY, cursorX);
                break;
            case KEY_UP:
                cursorY -= CURSORSPEED;
                if (cursorY <= mainscreen.startY())
                {
                    topbar.activate();
                    curs_set(0);
                    state = aplicationState::topBar;
                    topbar.draw();
                }
                move(cursorY, cursorX);
                break;
            case 10:
                UITable *pressedTable;
                if (mainscreen.pressed(cursorY, cursorX, pressedTable)) // returns true if table was pressed and returns table by reference
                {
                    curs_set(0);
                    if (pressedTable->getTable()->isOccupied()) // there is order assigned to this table
                    {
                        continue;
                        // popUpHandler.newLocalOrderPopUpMenu(pressedTable->table.order)
                    }
                    else
                    {
                        popUpHandler.newTableNoOrderPopUpMenu(pressedTable->getTable());
                    }
                    previousState = state;
                    state = aplicationState::popUpMenu;
                }
                break;
            }
        }
        else if (state == aplicationState::popUpMenu)
        {
            switch (userInput)
            {
            case KEY_UP:
                popUpHandler.moveUp();
                break;
            case KEY_DOWN:
                popUpHandler.moveDown();
                break;

            case 10:
                if (popUpHandler.buttonPressed())
                {
                    mainscreen.draw();
                    if (previousState == aplicationState::topBar)
                    {
                        topbar.activate();
                        topbar.draw();
                    }
                    else if (previousState == aplicationState::mainScreen)
                    {
                        curs_set(1);
                        move(cursorY, cursorX);
                    }
                    state = previousState;
                }
                break;
            }

            popUpHandler.draw();
        }
    } while (!restaurant.isClosed());

    // dealocate memory , deallocate memory
    endwin();
    return 0;
}

// refresh only updated elements after change
// do not change elements that have not changed !!
// if you getchar it will automatically refreesh
// draw only window with focus !!!
// refresh only things that have changed