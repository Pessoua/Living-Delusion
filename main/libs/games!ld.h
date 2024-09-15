#ifndef LD_GAMES_H
#define LD_GAMES_H

/*
 * void Crop(const short int Crop1_ID, bool is_tut);
 * void Fish(const short int Fish1_ID, const char *what_pond, bool is_tut);
 * void Tree(bool is_invasive, const char *num_spot, const short int Log1_ID, const short int special_tree_ID, bool is_tut);
*/

/*
 * Yes, games HAVE a sub directory because most of the games have a lot of code and its just eazier to manage them if they each have a single file
 *
 * See the code on games/
 */ 

#include "../LivingDelusion.h"

//This will probably come in handy later
typedef struct {
    i8 x, y;
} coords;

#include "games/animal!ld.h"
#include "games/crop!ld.h"
#include "games/fish!ld.h"
#include "games/tree!ld.h"

#endif /* LD_GAMES_H */
