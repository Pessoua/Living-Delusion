#include "../LivingDelusion.h"

//Used to get cur Terminal Size information (not mine, found here: https://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows/12642749#12642749)
u64 GetTerminalSize(const char * what){

    u64 columns = 0, rows = 0;

    switch(OS_NANE[0]){
        case 'L': {
                      struct winsize w;
                      ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

                      columns = (u64)w.ws_col;
                      rows = (u64)w.ws_row;

                      break;
                  }

        case 'W': {
                      CONSOLE_SCREEN_BUFFER_INFO csbi;
                      int columns, rows;

                      GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
                      columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                      rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

                      break;
                  }

        case 'A': {

                      break;
                  }
    }


    if(strcmp(what, "columns")== 0)
        return columns;

    else
        return rows;
}
