#ifndef LDMAIN_H
#define LDMAIN_H

//standart libs here
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#include <sys/stat.h> 
#include <errno.h>

//extern vars


//extern libs here
#include "libs/style!ld.h"       //Text formating + Making things look better
#include "libs/art!ld.h"         //Ascii art display handlers and more
#include "libs/path!ld.h"        //Helper path functions
#include "libs/save!ld.h"        //Main save files handler + file I/O helper :3
#include "libs/extras!ld.h"      //Main extras handler (depends on most libs)
#include "libs/sys!ld.h"         //Mostly system helper functions / functions "outside" the game itself
#include "libs/osmanip!ld.h"     //Functions that require interacting with the OS in any way
#include "libs/games!ld.h"       //Main handler for EVERYTHING about the games (and some locations)
#include "libs/nina!ld.h"        //Main NINA API handler

//external tests (also dependant on LD.h and NINA API works on it)
#include "../tools/tests!ld.h"

//INCLUDE TOOLS??
// #include "../tools/ascii!ld.h" oopsie (does not exist yet)

//macros :3
#ifdef _WIN32
    #define CLR system("cls");
#else
    #define CLR system("clear");
#endif

#endif

