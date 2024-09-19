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

//Copy cat of the function above but modified to navigate the "OTHER" dir instead
void ChangeCurPath(const char * changeToThis){
    char * finalPath = (char *)malloc(PATH_MAX_LEN);
    memset(finalPath, '\0', PATH_MAX_LEN);

    char * argCopy = (char *)malloc(strlen(changeToThis) * sizeof(char) + 5);
    memset(argCopy, '\0', sizeof(argCopy));
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

