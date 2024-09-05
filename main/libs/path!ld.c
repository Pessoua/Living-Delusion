#include "../LivingDelusion.h"

//Check if dir exists [Not made by me, thanks for whoever did it though]
bool ExistDiret(const char * path){
    struct stat stats;

    stat(path, &stats);

    if (S_ISDIR(stats.st_mode)){
        return true;
    }

    return false;
}
