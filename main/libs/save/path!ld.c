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

//this is to get the constant paths, STARTING_PATH, FULL_PATH and LOCAL_PATH with error handling
bool GetNeededPaths(void){

    //Set 'em all to nulls for safety
    memset(STARTING_PATH, '\0', PATH_MAX_LEN);
    memset(FULL_PATH, '\0', PATH_MAX_LEN);
    memset(LOCAL_PATH, '\0', PATH_MAX_LEN);

    //We asume that this is only run at start
    GetCurPath(STARTING_PATH);

    bool returnWhat = true, alreadyDefinedFp = false;
    path tempPath;
    memset(tempPath, '\0', PATH_MAX_LEN);    

    //Getting LOCAL_PATH and FULL_PATH
    switch(OS_NAME[0]){
        case 'L':
            break;

        case 'W': {

                //Checking if LOCALAPPDATA is real or not
                const char *md = "LOCALAPPDATA";
                char * getEnvVar = getenv(md);
                strcpy(LOCAL_PATH, getEnvVar);

                chdir(LOCAL_PATH);
                strcat(LOCAL_PATH, "\\LIVING_DELUSION");

                //Local path does not exist
                if(!ExistDiret(LOCAL_PATH)){
                    chdir(STARTING_PATH);

                    strcpy(tempPath, STARTING_PATH);
                    strcat(tempPath, "\\NEEDED");

                    //This means that LOCAL path does NOT exist and theres no replacement (NEEDED/), so show error
                    if(!ExistDiret(tempPath))
                        ExitEarly(002, "Local path missing and did NOT find replacement. (STARTUP ERR.)");
                    
                    //If it exists, we do the operations needed to move it back to LOCALAPPDATA
                    system("move NEEDED %LOCALAPPDATA%");

                    LOCAL_PATH[strlen(LOCAL_PATH) - 16] = '\0';
                    chdir(LOCAL_PATH);

                    system("rename NEEDED LIVING_DELUSION");

                    strcat(LOCAL_PATH, "\\LIVING_DELUSION");

                    returnWhat = false;

                } else {
                    //See if path.txt exists
                    chdir(LOCAL_PATH);
                    chdir("extern");

                    //path.txt exists
                    if(access("path.txt", F_OK) == 0){
                        FILE * fGetAppPath = fopen("path.txt", "r");
                        fgets(tempPath, PATH_MAX_LEN, fGetAppPath);
                        fclose(fGetAppPath);

                        //user defined APPDATA does not exist
                        if(!ExistDiret(tempPath))
                            ExitEarly(003, "User defined APPDATA path does not exist. (STARTUP ERR.)");

                        strcpy(FULL_PATH, tempPath);
                        alreadyDefinedFp = true;
                    }
                }

                //Define FULL_PATH if its not already defined by LOCAL_PATH/extern/path.txt
                if(!alreadyDefinedFp){
                    memset(tempPath, '\0', PATH_MAX_LEN);
                        
                    const char *newMd = "APPDATA";
                    char * getEnvVarFULL = getenv(newMd);
                    strcpy(FULL_PATH, getEnvVarFULL);

                    //LOCAL PATH does not exist :(
                    if(!ExistDiret(FULL_PATH)){
                        mkdir("LIVING_DELUSION");
                        chdir("LIVING_DELUSION");
                        mkdir(".out");
                    }

                    strcat(FULL_PATH, "\\LIVING_DELUSION");
                    chdir(FULL_PATH);
                }

                break;
            }

        case 'A':
            break;
    }

    return returnWhat;
}
