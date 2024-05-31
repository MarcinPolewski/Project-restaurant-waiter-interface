#include <ncurses.h>

#include <string>
#include <vector>

// #include <restaurant.h>

#define COLOR_NORMAL 1
#define COLOR_SELECT 2
#define TOPBARHEIGHT 3
#define CURSORSPEED 5

enum class aplicationState
{
    mainScreen,
    topBar
};

class TopBar
{
    WINDOW *window;
    int selection = 0; // inx to currently pointed button
    std::vector<std::string> buttons;
    bool active = true;

public:
    TopBar(int height, int width, int positionY, int positionX)
    {
        window = newwin(height, width, positionY, positionX);
        box(window, 0, 0);
        buttons = {"Change Waiter", "Menu", "Remote Orders", "Local Orders", "Close Restarurant"};
        draw();
    }

    void draw()
    {
        int width = getmaxx(window);
        int widthPerButton = width / buttons.size();

        // ============== draw buttons to window
        int cursorX = 1;
        int cursorY = 1;

        for (int i = 0; i < (int)buttons.size(); i++)
        {

            // calculate button position offset from the left
            int offset = (widthPerButton - buttons[i].size()) / 2;

            if (active && i == selection) // print menu as selected if neccessary
                wattr_on(window, A_REVERSE, nullptr);
            mvwprintw(window, cursorY, cursorX + offset, buttons[i].c_str());

            wattr_off(window, A_REVERSE, nullptr);
            cursorX += widthPerButton;
            if (i != (int)buttons.size() - 1)
                mvwprintw(window, cursorY, cursorX - 1, "|");
        }
        wrefresh(window);
    }
    void activate()
    {
        active = true;
    }
    void deactivate()
    {
        active = false;
    }
    void moveLeft()
    {
        if (selection == 0)
            selection = buttons.size() - 1;
        else
            --selection;
    }
    void moveRight()
    {
        if (selection == (int)buttons.size() - 1)
            selection = 0;
        else
            ++selection;
    }
};

void drawTables(WINDOW *tableScreen)
{
    // ============ get dimensions

    // wprintw(tableScreen, "==")
}

int main(int argc, char **argv)
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
    // ============= get max dimensions of terminal
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // ============= initialize windows
    TopBar topbar(TOPBARHEIGHT, xMax, 0, 0);

    WINDOW *mainScreen = newwin(yMax - TOPBARHEIGHT, xMax, TOPBARHEIGHT, 0);
    box(mainScreen, 0, 0);
    refresh();
    wrefresh(mainScreen);
    // =========== initialize tables
    // WINDOW *tableWindow = newwin(4, 8, getbegy(mainScreen) + 5, getbegx(mainScreen) + 5);
    // box(tableWindow, 0, 0);
    // refresh();
    // wrefresh(tableWindow);
    // ============= initialize buttons

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
        topbar.draw();
        drawTables(mainScreen);

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
                topbar.moveRight();
                break;
            case KEY_LEFT:
                topbar.moveLeft();
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
                //++cursorX;
                cursorX += CURSORSPEED * 2;
                if (cursorX >= getbegx(mainScreen) + getmaxx(mainScreen) - 1)
                    cursorX = getbegx(mainScreen) + 1;
                move(cursorY, cursorX);
                break;
            case KEY_LEFT:
                //--cursorX;
                cursorX -= CURSORSPEED * 2;
                if (cursorX <= getbegx(mainScreen))
                    cursorX = getbegx(mainScreen) + getmaxx(mainScreen) - 2;
                move(cursorY, cursorX);
                break;
            case KEY_DOWN:
                //++cursorY;
                cursorY += CURSORSPEED;
                if (cursorY >= getbegy(mainScreen) + getmaxy(mainScreen) - 1)
                    cursorY = getbegy(mainScreen) + 1;
                move(cursorY, cursorX);
                break;
            case KEY_UP:
                //--cursorY;
                cursorY -= CURSORSPEED;
                if (cursorY <= getbegy(mainScreen))
                {
                    // cursorY = getbegy(mainScreen) + getmaxy(mainScreen) - 2;
                    curs_set(0);
                    state = aplicationState::topBar;
                }
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