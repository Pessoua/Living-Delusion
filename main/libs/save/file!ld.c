#include "../save!ld.h"

char * ReadFromFile(const char * wotPath, const char * fileName, u64 whatFileLine){
    
    //Change cur path
    if(strcmp(wotPath, "Local")== 0)
        chdir(LOCAL_PATH);

    else if(strcmp(wotPath, "App")== 0)
        chdir(FULL_PATH);

    else if(ExistDiret(wotPath))
        chdir(wotPath);

    else
        ExitEarly(203, "Path for \"ReadFromFile\" not found");
    
    char * thisLine = CharMalloc(2048);

    //File dosent even exist
    if(access(fileName, F_OK)!= 0)
        ExitEarly(303, "File not found for \"ReadFromFile\"");

    //Open original file to read from and check if it opened right
    FILE * fOrigin = fopen(fileName, "r");
    if(fOrigin == NULL)
        ExitEarly(301, "Tried to open file to read, pointer was NULL");

    //displace fOrigin pointer till we reach the desired line
    for(u64 i = 0; i < whatFileLine - 1; i ++)
        fgets(thisLine, 2048, fOrigin);

    memset(thisLine, '\0', 2048);
    fgets(thisLine, 2048, fOrigin);

    //if last char is \n, cut it out
    if(thisLine[strlen(thisLine) - 1] == 10)
        thisLine[strlen(thisLine) - 1] = '\0';    
    
    fclose(fOrigin);

    return thisLine;
}

void WriteToFile(int num_args, const char * wotPath, const char * fileName, u64 whatFileLine, ...){

    bool startWrite = false;

    //NOTE: If we can set wotPath to Local and then set the fileName to ext/fileName
        
    //Change cur path
    if(strcmp(wotPath, "Local")== 0)
        chdir(LOCAL_PATH);

    else if(strcmp(wotPath, "App")== 0)
        chdir(FULL_PATH);

    else if(ExistDiret(wotPath))
        chdir(wotPath);

    else
        ExitEarly(203, "Path for \"WriteToFile\" not found");

    //File dosent even exist
    if(access(fileName, F_OK)!= 0)
        ExitEarly(303, "File not found for \"WriteToFile\"");

    //Open original file to read from and check if it opened right
    FILE * fOrigin = fopen(fileName, "r");
    if(fOrigin == NULL)
        ExitEarly(301, "Tried to open file to read, pointer was NULL");

    //Open temporary to write to and check if it opened right
    FILE * fTemp = fopen("__temp.txt", "w");
    if(fTemp == NULL)
        ExitEarly(306, "Couldnt make temporary file (__temp)");
    
    char * thisLine = CharMalloc(2048);

    for(u64 i = 0; ; i ++){
    
        if(fgets(thisLine, 2048, fOrigin)== NULL)
            break;

        if(i == whatFileLine)
            startWrite = true;

        if(startWrite){
             printf("PLACEHOLDER!\n");

        } else
            fprintf(fTemp, "%s\n", thisLine);

        if(startWrite && i == (whatFileLine + num_args))
            startWrite = false;

        //we assume that
        //whatFileLine is the starting line
        //we get the arguments
        //i ++ for each unique argument untill its done
        //std arg shit

        memset(thisLine, '\0', 2048);
    }

    SafeFree(thisLine);

    fclose(fOrigin);
    fclose(fTemp);

    remove(fileName);
    rename("__temp.txt", fileName);

    return;
}
