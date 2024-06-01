#include <ncurses.h>

#include <string>
#include <vector>

#include <restaurant.h>

#define TOPBARHEIGHT 3
#define CURSORSPEED 9 // must be an odd number !!!!
#define COLUMN_TO_WIDTH_RATION 2

enum class aplicationState
{
    mainScreen,
    topBar,
    tablePopUpWindow
};

class TerminalUIObject
{
protected:
    WINDOW *window;

public:
    TerminalUIObject() = default;
    TerminalUIObject(int height, int width, int yPosition, int xPosition)
    {
        window = newwin(height, width, yPosition, xPosition);
        box(window, 0, 0);
        refresh();
        wrefresh(window);
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

class PopUpMenu : public TerminalUIObject
{

public:
    PopUpMenu(int height, int width, int yPosition, int xPosition) : TerminalUIObject(height, width, yPosition, xPosition)
    {
    }

    // PopUpMenu(WINDOW *background, int verticalOffset = 1, int horizontalOffset = 1 * COLUMN_TO_WIDTH_RATION)
    // {
    //     int height = getmaxy(background) - 2 * verticalOffset;
    //     int width = getmaxx(background) - 2 * horizontalOffset;

    //     PopUpMenu(height, width, verticalOffset + getbegy(background), horizontalOffset + getbegx(background));
    // }

    PopUpMenu(WINDOW *background, int height = 40, int width = 60)
    {
        // calculate offset
        int topLeftCornerX = getbegx(background) + ((getmaxx(background) - width) / 2);
        int topLeftCornerY = getbegy(background) + ((getmaxy(background) - height) / 2);

        PopUpMenu(height, width, topLeftCornerY, topLeftCornerX);
    }

    void draw() override
    {
    }
};

class TablePopUpMenu : public PopUpMenu
{
    using PopUpMenu::PopUpMenu;
};

class TopBar : public TerminalUIObject
{
    int selection = 0; // inx to currently pointed button
    std::vector<std::string> buttons;
    bool active = true;

public:
    TopBar(int height, int width, int positionY, int positionX) : TerminalUIObject(height, width, positionY, positionX)
    {
        buttons = {"Change Waiter", "Menu", "Remote Orders", "Local Orders", "Close Restarurant"};
        // draw();
    }

    WINDOW *getWindow()
    {
        return window;
    }

    void draw() override
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

class UITable : public TerminalUIObject
{
    int height = CURSORSPEED, width = COLUMN_TO_WIDTH_RATION * height - 1; // height and width mu
    int rawCoordinate, columnCoordinate;                                   // deteremine position of top left corner on the screen

    // ==== each table is printed so, that cursor always lands in the middle
    int howManyColumnsFromCeneter = (width - 1) / 2;
    int howManyRowsFromCenter = (height - 1) / 2;

    Table &table;

public:
    UITable(WINDOW *backgroundWindow, Table &table) : table(table)
    {
        rawCoordinate = (table.position.y) * CURSORSPEED - howManyRowsFromCenter;
        columnCoordinate = (table.position.x) * CURSORSPEED * COLUMN_TO_WIDTH_RATION - howManyColumnsFromCeneter;

        window = newwin(height, width, rawCoordinate + getbegy(backgroundWindow), columnCoordinate + getbegx(backgroundWindow));
        box(window, 0, 0);
        refresh();
        wrefresh(window);
    }

    void draw() override
    {
    }
    void activate();
    void deactivate();
    bool pressed(int yPos, int xPos)
    {
        return true;
    }
};

class MainScreen : public TerminalUIObject
{
public:
    enum class InternalState
    {
        cursorState,
        popUpMenuState
    };

private:
    std::unique_ptr<TablePopUpMenu> popUpMenu;
    std::vector<UITable> tables;
    InternalState internalState;

public:
    MainScreen(int height, int width, int positionY, int positionX, InternalState internalState = InternalState::cursorState) : TerminalUIObject(height, width, positionY, positionX), internalState(internalState)
    {
    }

    // ======= getters that return corner values of x,y
    void addTables(std::vector<Table> &tables)
    {

        for (auto &it : tables)
        {
            this->tables.push_back(UITable(window, it));
        }
    }

    void draw() override
    {
        for (auto &it : tables)
        {
            it.draw();
        }
    }

    bool pressed(int cursorY, int cursorX) // checks if table was pressed, if so retur n true
    {
        for (auto &it : tables)
        {
            if (it.isCursorInWindow(cursorY, cursorX))
            {
                // 1. create new window
                // popUpMenu.reset(new TablePopUpMenu(window));
                popUpMenu = std::make_unique<TablePopUpMenu>(window);
                internalState = InternalState::popUpMenuState;
                return true;
            }
        }
        return false;
    }

    InternalState getInternalState()
    {
        return internalState;
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
    // ============= get max dimensions of terminal window
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // ============= initialize restaurant class
    Restaurant restaurant;

    // ============= initialize screen elements
    TopBar topbar(TOPBARHEIGHT, xMax, 0, 0);
    MainScreen mainscreen(yMax - TOPBARHEIGHT, xMax, TOPBARHEIGHT, 0);
    mainscreen.addTables(restaurant.getTables());
    // PopUpMenu(mainscreen.getWindow());

    keypad(stdscr, true);

    // ============= main program loop
    bool runLoop = true;
    int userInput;
    int cursorX, cursorY;
    aplicationState state = aplicationState::topBar;
    do
    {
        // clear();
        // refresh();
        // ========== draw everything to screen
        topbar.draw();
        // mainscreen.draw();
        //  drawTables(mainScreen);

        refresh();

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
                // getyx(stdscr, cursorY, cursorX);
                // cursorY = getbegy(mainScreen) + 1;
                // move(cursorY, 2); // zrobić zeby przeskakiwalo pod guzik !!!!!!!!!!!!!!!!!!

                cursorX = mainscreen.startX() + CURSORSPEED * COLUMN_TO_WIDTH_RATION; // getbegx(mainScreen) + 1;
                cursorY = mainscreen.startY() + CURSORSPEED;                          // getbegy(mainScreen) + 1;
                move(cursorY, cursorX);
                curs_set(1);
                break;
            case 10:

                break;
            }
        }
        else if (state == aplicationState::mainScreen)
        {
            if (mainscreen.getInternalState() == MainScreen::InternalState::cursorState)
            {
                switch (userInput)
                {
                case KEY_RIGHT: // OK
                    cursorX += CURSORSPEED * 2;
                    if (cursorX >= mainscreen.endX())
                        cursorX = mainscreen.startX() + CURSORSPEED * COLUMN_TO_WIDTH_RATION;
                    move(cursorY, cursorX);
                    break;
                case KEY_LEFT: // NIE OK
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
                case 10:
                    if (mainscreen.pressed(cursorY, cursorX)) // returns true if table was pressed
                        curs_set(0);
                    break;
                }
            }
            else if (mainscreen.getInternalState() == MainScreen::InternalState::cursorState)
            {
            }
        }
    } while (runLoop);

    // dealocate memory , deallocate memory
    endwin();
    return 0;
}