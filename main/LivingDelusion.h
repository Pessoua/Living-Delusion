#ifndef LDMAIN_H
#define LDMAIN_H

/*
 *
 * MAIN LIBRARY FOR Living Delusion
 *
 * Includes ALL of the sub-libraries that will be used (and the sub-sub libraries inside the sub libraries)
 * Also includes some global macros, variables, typedefs from stdint
 *
 */

//standart libs here
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include <stdbool.h>
#include <sys/stat.h> 
#include <stdint.h>
#include <stdarg.h> //for file!ld.h

//OS specific garbo
#if defined(_WIN32) || defined(_WIN64) 
    #include <Windows.h>
    #include <conio.h>

    #define PATH_MAX_LEN 520
    #define CLR system("cls");

    #define SmallStop   printf("[SYSTEM] _> Press anything to continue\n"); \
                        getch(); \
                        CLR;

#else
    #define PATH_MAX_LEN 4096
    #define CLR system("clear");

    #include <termios.h>

    //STOLEN FROM: https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux/7469410#7469410
    void initTermios(int echo) 
    {
        tcgetattr(0, &old);
        current = old; 
        current.c_lflag &= ~ICANON; 
        if (echo) {
            current.c_lflag |= ECHO; 
        } else {
            current.c_lflag &= ~ECHO; 
        }
        tcsetattr(0, TCSANOW, &current); 
    }

    void resetTermios(void) 
    {
        tcsetattr(0, TCSANOW, &old);
    }

    char getch_(int echo) 
    {
        char ch;
        initTermios(echo);
        ch = getchar();
        resetTermios();
        return ch;
    }

    char getch(void) 
    {
        return getch_(0);
    }

    //SURELY IT WORKS
    #define SmallStop   printf("[SYSTEM] _> Press anything to continue\n"); \
                        getch(); \
                        CLR;
    //Linux specifics
    #ifdef __linux__

    //Apple specifics
    #elif defined(__APPLE__) || defined(__MACH__)

    #else
        //dont define anything
    #endif

#endif

//Sorry if the OS names are kinda weird, im just lazy
#if defined(_WIN32) || defined(_WIN64)  
    #define OS_NAME "W"
#elif defined(__linux__)  
    #define OS_NAME "L"
#elif defined(__APPLE__) || defined(__MACH__)  
    #define OS_NAME "A"
#else  
    #define OS_NAME "U"
#endif  

//Macros that arent OS dependant
#define Error   CLR; \
                printf("\x1b[31m[ERROR] _> Oopsie! Not a valid command\x1b[0m\n"); \
                sleep(1); \
                CLR;

#define SafeFree(p) SaferFree((void **)&(p));   //function pointers are scary! (also stolen from "Using and Understanding C Pointers")
                                
//VERY temporary thing
#define dark_blue     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
#define green          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
#define light_blue     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
#define red        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
#define purple         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
#define yellow         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
#define white          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
#define gray       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
#define mid_blue   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
#define light_green    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
#define light_aqua     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
#define light_red  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
#define light_purple SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
#define light_yellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
#define  bright_white SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

//typedefs go here (YES I STOLE THESE TYPEDEFS!)
typedef int8_t      i8;         //From (-128 to 127)
typedef uint8_t     u8;         //From (0 - 255)
typedef int16_t     i16;        //From (-32 768 to 32 767)
typedef uint16_t    u16;        //From (0 to 65 535)
typedef int32_t     i32;        //From (-2 147 483 648 to 2 147 483 647)
typedef uint32_t    u32;        //From (0 to 4 294 967 295)
typedef int64_t     i64;        //From (-9 223 372 036 854 775 808 to 9 223 372 036 854 775 807)
typedef uint64_t    u64;        //From (0 to 18 446 744 073 709 551 615)
                                
typedef float       f6;         //Example: 3.141593
typedef double      f18;        //Example: 3.141592653589793116
//^Examples for float and double stolen from here - (https://stackoverflow.com/questions/5098558/float-vs-double-precision)

typedef char path[PATH_MAX_LEN];      //PATH! (depends on the OS)

//extern variables
//sys styff
extern path STARTING_PATH, FULL_PATH, LOCAL_PATH;
extern bool DEBUG_MODE;
extern char Input [50];
extern clock_t time_needed;
extern i64 INT_Input;

//settings
extern char game_set [15], dificulty[50];
extern bool skip_intro, show_user_turn, display_all_tut_once, skip_tut_display, force_tut_display, show_tut_cutscene;
extern bool display_tip, div_inv_sect, limit_inv, arr_limit_inv [6];

//extern libs here
#include "libs/style!ld.h"       //Text formating + Making things look better
#include "libs/art!ld.h"         //Ascii art display handlrs and more                                           (SPLIT)
#include "libs/save!ld.h"        //Main save files handler + file I/O helper :3                                 (SPLIT)
#include "libs/extras!ld.h"      //Main extras handler (depends on most libs)
#include "libs/sys!ld.h"         //Mostly system helper functions / functions "outside" the game itself
#include "libs/ext!ld.h"         //Same has sys but the functions used are more related to the game             (SPLIT)
#include "libs/osmanip!ld.h"     //Functions that require interacting with the OS in any way                    (SPLIT)
#include "libs/games!ld.h"       //Main handler for EVERYTHING about the games (and some locations)             (SPLIT)
#include "libs/local!ld.h"       //Main handler for location related functions                                  (SPLIT)
#include "libs/nina!ld.h"        //Main NINA API handler                                                        (SPLIT)

//Functions with "(SPLIT)" mean they have their own directory with sub-sub libraries
//(because the functions are too long for one file)

//external tests (also dependant on LD.h and NINA API works on it)
#include "../tools/tests!ld.h"

//INCLUDE TOOLS??
// #include "../tools/textimg!ld.h" oopsie (does not exist yet)

#endif /* LDMAIN_H */

