#ifndef LD_OSMANIP_H
#define LD_OSMANIP_H

int GetTerminalSize(const char * what);

/*
 * instead of using "#ifdef" crap i would rather just have LD choose what commands to use lol
 * makes it WAYYY eazier to do stuff this way
 */

#include "../LivingDelusion.h"

#include "os/linux!ld.h"
#include "os/windows!ld.h"

#endif /* LD_OSMANIP_H */
