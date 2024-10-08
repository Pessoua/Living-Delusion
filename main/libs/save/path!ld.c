#include "../save!ld.h"

//Check if dir exists [Not made by me, thanks for whoever did it though]
bool ExistDiret(const char * path){
    struct stat stats;

    stat(path, &stats);

    if (S_ISDIR(stats.st_mode)){
        return true;
    }

    return false;
}

//Get current path w error handling
void GetCurPath(path newPath){

    memset(newPath, '\0', PATH_MAX_LEN);

    if(getcwd(newPath, PATH_MAX_LEN) == NULL)
        ExitEarly(204, "Failed to get home path on ReadFromFile, getcwd returned NULL");

    return;
}

//Changes cur path based on FULL_PATH
void ChangeCurPath(const char * changeToThis){
    char * finalPath = (char *)malloc(PATH_MAX_LEN);
    memset(finalPath, '\0', PATH_MAX_LEN);

    char * argCopy = CharMalloc(strlen(changeToThis) + 5);   
    strcpy(argCopy, changeToThis);

    strcpy(finalPath, FULL_PATH);
    strcat(finalPath, "\\");

    //Seperate paremeters
    char delim [2] = ".";
    char * curCatLine;
    curCatLine = strtok(argCopy, delim);
    if(curCatLine == NULL){
        chdir(finalPath);
        return;
    }

    strcat(finalPath, curCatLine);
    strcat(finalPath, "\\");

    //Continue untill end
    while(curCatLine != NULL){
        curCatLine = strtok(NULL, delim); 
        if(curCatLine == NULL)
            break;

        strcat(finalPath, curCatLine);
        strcat(finalPath, "\\");
    }

    chdir(finalPath);
    free(finalPath);
    free(argCopy);

    return;
}
