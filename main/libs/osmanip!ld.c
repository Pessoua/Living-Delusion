#include "../LivingDelusion.h"

//Used to get cur Terminal Size information (not mine, found here: https://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows/12642749#12642749)
int GetTerminalSize(const char * what){
CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    if(strcmp(what, "columns")== 0)
        return columns;

    else
        return rows;
}
