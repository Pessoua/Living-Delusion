#ifndef LDMAIN_H
#define LDMAIN_H

//intern libs here
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

//extern libs here
#include "libs/style!ld.h"       //Text formating + Making things look better
#include "libs/art!ld.h"         //Ascii art display handlers and more
#include "libs/path!ld.h"        //Helper path functions
#include "libs/file!ld.h"        //Helper file I/O functions
#include "libs/extras!ld.h"      //Main extras handler (depends on most libs)
#include "libs/sys!ld.h"         //System helper functions
#include "libs/osmanip!ld.h"     //Functions that require interacting with the OS in any way
#include "libs/games!ld.h"       //Main handler for EVERYTHING about the games
#include "libs/nina!ld.h"        //Main NINA API handler

//INCLUDE TESTS???
//INCLUDE TOOLS??

#endif
