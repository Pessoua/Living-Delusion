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
#include <stdint.h>

//extern vars

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
    #define CLR system("clear")https://stackoverflow.com/questions/5098558/float-vs-double-precision;
#endif

#endif

