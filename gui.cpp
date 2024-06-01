#include <ncurses.h>

#include <string>
#include <vector>

#include <restaurant.h>

#define COLOR_NORMAL 1
#define COLOR_SELECT 2
#define TOPBARHEIGHT 3
#define CURSORSPEED 9 // must be even number ???
#define WIDTH_TO_RAW_RATIO 2

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
        refresh();
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

// to do : -zmienić, tera UITable zawiera wskazanie na talbe - dodać układ siatkowy, skacząc wskaźnikiem zawsze lądujemy w środku kwadratu !!

class UITable
{
    int height = CURSORSPEED, width = WIDTH_TO_RAW_RATIO * height - 1; // height and width mu
    int rawCoordinate, columnCoordinate;                               // deteremine position of top left corner on the screen

    // ==== each table is printed so, that cursor always lands in the middle
    int howManyColumnsFromCeneter = (width - 1) / 2;
    int howManyRowsFromCenter = (height - 1) / 2;

    WINDOW *tableWindow;
    Table &table;

public:
    UITable(WINDOW *backgroundWindow, Table &table) : table(table)
    {
        rawCoordinate = (table.position.y) * CURSORSPEED - howManyRowsFromCenter;
        columnCoordinate = (table.position.x) * CURSORSPEED * WIDTH_TO_RAW_RATIO - howManyColumnsFromCeneter;

        tableWindow = newwin(height, width, rawCoordinate + getbegy(backgroundWindow), columnCoordinate + getbegx(backgroundWindow));
        box(tableWindow, 0, 0);
        refresh();
        wrefresh(tableWindow);
    }
    void draw();
    void activate();
    void deactivate();
    void pressed(); // ??
    bool isCursoreIn(int yPos, int xPos);
};

class MainScreen
{
    WINDOW *window;
    std::vector<UITable> tables;

public:
    MainScreen(int height, int width, int positionY, int positionX)
    {
        window = newwin(height, width, positionY, positionX);
        box(window, 0, 0);
        refresh();
        wrefresh(window);
    }

    // ======= getters that return corner values of x,y
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

    void addTables(std::vector<Table> &tables)
    {

        for (auto &it : tables)
        {
            this->tables.push_back(UITable(window, it));
        }
    }

    void draw()
    {
        for (auto &it : tables)
        {
            it.draw();
        }
    }
};

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

    Restaurant restaurant;

    // ============= initialize windows
    TopBar topbar(TOPBARHEIGHT, xMax, 0, 0);
    MainScreen mainscreen(yMax - TOPBARHEIGHT, xMax, TOPBARHEIGHT, 0);
    mainscreen.addTables(restaurant.getTables());

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
    int cursorX, cursorY;
    aplicationState state = aplicationState::topBar;
    do
    {
        // ========== draw everything to screen
        topbar.draw();
        // mainscreen.draw();
        //  drawTables(mainScreen);

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
                topbar.deactivate();
                // getyx(stdscr, cursorY, cursorX);
                // cursorY = getbegy(mainScreen) + 1;
                // move(cursorY, 2); // zrobić zeby przeskakiwalo pod guzik !!!!!!!!!!!!!!!!!!

                cursorX = mainscreen.startX() + CURSORSPEED * WIDTH_TO_RAW_RATIO; // getbegx(mainScreen) + 1;
                cursorY = mainscreen.startY() + CURSORSPEED;                      // getbegy(mainScreen) + 1;
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
            case KEY_RIGHT: // OK
                cursorX += CURSORSPEED * 2;
                if (cursorX >= mainscreen.endX())
                    cursorX = mainscreen.startX() + CURSORSPEED * WIDTH_TO_RAW_RATIO;
                move(cursorY, cursorX);
                break;
            case KEY_LEFT: // NIE OK
                cursorX -= CURSORSPEED * 2;
                if (cursorX <= mainscreen.startX())
                {
                    // x must be a multiple of CURSORSPEED
                    cursorX = mainscreen.endX() - CURSORSPEED * WIDTH_TO_RAW_RATIO;
                    cursorX -= cursorX % (CURSORSPEED * WIDTH_TO_RAW_RATIO);
                }
                move(cursorY, cursorX);
                break;
            case KEY_DOWN:
                //++cursorY;
                cursorY += CURSORSPEED;
                if (cursorY >= mainscreen.endY())
                    cursorY = mainscreen.startY() + CURSORSPEED;
                move(cursorY, cursorX);
                break;
            case KEY_UP: // OK
                //--cursorY;
                cursorY -= CURSORSPEED;
                if (cursorY <= mainscreen.startY())
                {
                    // cursorY = getbegy(mainScreen) + getmaxy(mainScreen) - 2;
                    topbar.activate();
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