#ifndef LD_SAVE_H
#define LD_SAVE_H

void ChangeFileLine(const char *fileName, const char *line, int lineToModify);

#include "../LivingDelusion.h"

#include "save/file!ld.h"           //File I/O helper functions
#include "save/make!ld.h"           //Functions that makes new save files
#include "save/exit!ld.h"           //Functions to save progress when user leaves
#include "save/check!ld.h"	        //Functions to check if everything is OK with local and normal (high lvl view)
#include "save/path!ld.h"           //Functions to help with path management stuff

#endif /* LD_SAVE_H */
