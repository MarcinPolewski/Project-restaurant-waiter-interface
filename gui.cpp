#include <ncurses.h>

#include <string>
#include <vector>

#define COLOR_NORMAL 1
#define COLOR_SELECT 2
#define TOPBARHEIGHT 3

enum class aplicationState
{
    mainScreen,
    topBar
};

void drawTopBar(WINDOW *topBarWindow, std::vector<std::string> buttons, int selection)
{
    // if (selection >= buttons.size() || selection < 0)
    //     throw ::std::runtime_error("unable to draw selection, out of range");

    // ============= get dimensions
    int width = getmaxx(topBarWindow);
    int widthPerButton = width / buttons.size();

    // ============== draw buttons to window
    int cursorX = 1;
    int cursorY = 1;

    for (int i = 0; i < buttons.size(); i++)
    {

        // calculate button position offset from the left
        int offset = (widthPerButton - buttons[i].size()) / 2;

        if (i == selection) // print menu as selected if neccessary
            wattr_on(topBarWindow, A_REVERSE, nullptr);
        mvwprintw(topBarWindow, cursorY, cursorX + offset, buttons[i].c_str());

        wattr_off(topBarWindow, A_REVERSE, nullptr);
        cursorX += widthPerButton;
        if (i != buttons.size() - 1)
            mvwprintw(topBarWindow, cursorY, cursorX - 1, "|");
    }
    wrefresh(topBarWindow);
}

void drawTables(WINDOW *tableScren)
{
    // ============ get dimensions
}

int main(int argc, char **argv)
{
    // ============= initialize screen, set up memory and clear screen
    initscr();
    noecho();    // do not write user input on screen
    cbreak();    // exit on cntr+c
    curs_set(0); // make cursor invisible (1-normal ; 2-highly visible )
    start_color();

    // ============= colors configuration
    // init_pair(COLOR_SELECT, COLOR_WHITE, COLOR_BLACK);
    // init_pair(COLOR_NORMAL, COLOR_BLACK, COLOR_WHITE);

    // attron(COLOR_PAIR(COLOR_NORMAL));
    // refresh();
    // ============= get max dimensions of terminal
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // ============= initialize windows
    WINDOW *topBarWindow = newwin(TOPBARHEIGHT, xMax, 0, 0);
    box(topBarWindow, 0, 0);
    refresh();
    wrefresh(topBarWindow);

    WINDOW *mainScreen = newwin(yMax - TOPBARHEIGHT, xMax, TOPBARHEIGHT, 0);
    box(mainScreen, 0, 0);
    refresh();
    wrefresh(mainScreen);

    std::vector<std::string> buttons = {"Change Waiter", "Menu", "Remote Orders", "Local Orders", "Close Restarurant"};

    // keypad(mainScreen, true); // turn on, now we can use KEY_UP, KEY_DOWNn .. ; must be before wgetch()
    // keypad(topBarWindow, true);
    keypad(stdscr, true);

    // ============= main program loop
    bool runLoop = true;
    int userInput;
    int topBarSelection = 0;
    int cursorX, cursorY;
    aplicationState state = aplicationState::topBar;
    do
    {
        // ========== draw everything to screen
        drawTopBar(topBarWindow, buttons, topBarSelection);
        // drawTables(mainScreen);

        refresh();

        userInput = getch();
        // ======== handle user input

        if (userInput == 10)
            runLoop = false;

        if (state == aplicationState::topBar)
        {
            switch (userInput)
            {
            case KEY_RIGHT:
                topBarSelection++;
                if (topBarSelection == buttons.size())
                    topBarSelection = 0;
                break;
            case KEY_LEFT:
                topBarSelection--;
                if (topBarSelection == -1)
                    topBarSelection = buttons.size() - 1;
                break;
            case KEY_DOWN:
                state = aplicationState::mainScreen;
                // getyx(stdscr, cursorY, cursorX);
                // cursorY = getbegy(mainScreen) + 1;
                // move(cursorY, 2); // zrobić zeby przeskakiwalo pod guzik !!!!!!!!!!!!!!!!!!
                cursorX = getbegx(mainScreen) + 1;
                cursorY = getbegy(mainScreen) + 1;
                move(cursorY, cursorX);
                curs_set(1);
                break;
            case 10:
                runLoop = false;
                break;
            }
        }
        else if (state == aplicationState::mainScreen)
        {
            switch (userInput)
            {
            case KEY_RIGHT:
                ++cursorX;
                if (cursorX >= getbegx(mainScreen) + getmaxx(mainScreen) - 1)
                    cursorX = getbegx(mainScreen) + 1;
                move(cursorY, cursorX);
                break;
            case KEY_LEFT:
                --cursorX;
                if (cursorX <= getbegx(mainScreen))
                    cursorX = getbegx(mainScreen) + getmaxx(mainScreen) - 2;
                move(cursorY, cursorX);
                break;
            case KEY_DOWN:
                ++cursorY;
                if (cursorY >= getbegy(mainScreen) + getmaxy(mainScreen) - 1)
                    cursorY = getbegy(mainScreen) + 1;
                move(cursorY, cursorX);
                break;
            case KEY_UP:
                --cursorY;
                if (cursorY <= getbegy(mainScreen))
                    cursorY = getbegy(mainScreen) + getmaxy(mainScreen) - 2;
                move(cursorY, cursorX);
                break;
            }
        }
    } while (runLoop);

    // wait for user input
    getch();
    // dealocate memory , deallocate memory
    endwin();
    return 0;
}