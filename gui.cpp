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
    TopBar topbar(TOPBARHEIGHT, xMax, 0, 0);
    MainScreen mainscreen(yMax - TOPBARHEIGHT, xMax, TOPBARHEIGHT, 0);
    mainscreen.addTables(restaurant.getTables());
    PopUpHandler popUpHandler(mainscreen.getWindow(), &restaurant);

    keypad(stdscr, true);

    // ============= main program loop
    bool runLoop = true;
    int userInput;
    int cursorX, cursorY;
    aplicationState state = aplicationState::topBar;
    aplicationState previousState;

    do
    {
        // ========== draw everything to screen
        // jak to się właczy to przestaje się wyświtlać !!!!
        //  refresh();
        //   refresh();
        //     drawTables(mainScreen);

        // refresh();

        userInput = getch();

        // ======== handle user input
        if (userInput == 'q')
            runLoop = false;

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
                }
                move(cursorY, cursorX);
                break;
            case 10:
                UITable *pressedTable;
                if (mainscreen.pressed(cursorY, cursorX, pressedTable)) // returns true if table was pressed and returns table by reference
                {
                    curs_set(0);
                    popUpHandler.newTablePopUpMenu(*pressedTable);
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
                    state = previousState;
                    if (state == aplicationState::mainScreen)
                    {
                        mainscreen.draw();
                        curs_set(1);
                        move(cursorY, cursorX);
                    }
                }
                break;

            case 'a':
                // printw("jasflkjdsalfkjasdlk");
                // exit menu
                popUpHandler.closePopUpMenu();
                state = previousState;
                wclear(mainscreen.getWindow()); // czyścimy ekran tylko gdy menu znika !!!, ale potem trzeba
                // wrefresh(mainscreen.getWindow());
                mainscreen.draw();
                move(cursorY, cursorX);
                curs_set(1);
                break;
            }

            popUpHandler.draw();
        }
    } while (runLoop);

    getchar();
    // dealocate memory , deallocate memory
    endwin();
    return 0;
}

// refresh only updated elements after change
// do not change elements that have not changed !!
// if you getchar it will automatically refreesh
// draw only window with focus !!!
// refresh only things that have changed