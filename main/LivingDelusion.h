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
#include <Windows.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#include <sys/stat.h> 
#include <errno.h>
#include <stdint.h>

//OS specific garbo
#ifdef _WIN32
    #define OS "windows"
    #define PATH_MAX_LEN 520
    #define CLR system("cls");
#else
    #define PATH_MAX_LEN 4096
    #define CLR system("clear");
#endif


#ifdef _WIN32
    #define OS "windows"
#elif defined __linux__
    #define OS "linux"
#elif defined(__APPLE__)
    #define OS "mac"
#else
    #define OS "unsuported"
#endif
                                

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
extern path STARTING_PATH, FULL_PATH, LOCAL_PATH;
extern bool DEBUG_MODE;
extern char Input [50]; 

//extern libs here
#include "libs/style!ld.h"       //Text formating + Making things look better
#include "libs/art!ld.h"         //Ascii art display handlrs and more                                          (SPLIT)
#include "libs/path!ld.h"        //Helper path functions
#include "libs/save!ld.h"        //Main save files handler + file I/O helper :3                                 (SPLIT)
#include "libs/extras!ld.h"      //Main extras handler (depends on most libs)
#include "libs/sys!ld.h"         //Mostly system helper functions / functions "outside" the game itself
#include "libs/osmanip!ld.h"     //Functions that require interacting with the OS in any way                    (SPLIT)
#include "libs/games!ld.h"       //Main handler for EVERYTHING about the games (and some locations)             (SPLIT)
#include "libs/local!ld.h"      //Main handler for location related functions                                  (SPLIT)
#include "libs/nina!ld.h"        //Main NINA API handler                                                        (SPLIT)

//Functions with "(SPLIT)" mean they have their own directory with sub-sub libraries
//(because the functions are too long for one file)

//external tests (also dependant on LD.h and NINA API works on it)
#include "../tools/tests!ld.h"

//INCLUDE TOOLS??
// #include "../tools/ascii!ld.h" oopsie (does not exist yet)

#endif /* LDMAIN_H */

