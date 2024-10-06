#include "../save!ld.h"

char * ReadFromFile(const char * wotPath, const char * fileName, u64 whatFileLine, u32 cacheCode){

    //Store homepath to return to it LTR
    path homePath;
    memset(homePath, '\0', PATH_MAX_LEN);

    if(getcwd(homePath, PATH_MAX_LEN) == NULL)
        ExitEarly(204, "Failed to get home path on ReadFromFile, getcwd returned NULL");

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
        ExitEarly(301, "File not found for \"ReadFromFile\"");

    //Open original file to read from and check if it opened right
    FILE * fOrigin = fopen(fileName, "r");
    if(fOrigin == NULL)
        ExitEarly(302, "Tried to open file to read, pointer was NULL");

    //Fast search with cache   
    if(cacheCode != 0)
        SeekToCached(fOrigin, cacheCode);

    //displace fOrigin pointer till we reach the desired line
    for(u64 i = 0; i < whatFileLine - 1; i ++)
        if(fgets(thisLine, 2048, fOrigin)== NULL)
            ExitEarly(303, "Couldn't displace pointer, fgets returned NULL");

    memset(thisLine, '\0', 2048);
    if(fgets(thisLine, 2048, fOrigin)== NULL)
        ExitEarly(303, "Couldn't read from file, fgets returned NULL");

    //if last char is \n, cut it out
    if(thisLine[strlen(thisLine) - 1] == 10)
        thisLine[strlen(thisLine) - 1] = '\0';    
    
    fclose(fOrigin);

    chdir(homePath);

    return thisLine;
}

void WriteToFile(const char * wotPath, const char * fileName, u64 whatFileLine, const char * argSequence, ...){

    bool startWrite = false;

    //Start strarg stuff for later
    va_list args;    
    va_start(args, argSequence);

    //NOTE: If we can set wotPath to Local and then set the fileName to ext/fileName
        
    //Store homepath to return to it LTR
    path homePath;
    memset(homePath, '\0', PATH_MAX_LEN);

    if(getcwd(homePath, PATH_MAX_LEN) == NULL)
        ExitEarly(204, "Failed to get home path on ReadFromFile, getcwd returned NULL");

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
        ExitEarly(301, "File not found for \"WriteToFile\"");

    //Open original file to read from and check if it opened right
    FILE * fOrigin = fopen(fileName, "r");
    if(fOrigin == NULL)
        ExitEarly(302, "Tried to open file, pointer was NULL");

    //Open temporary to write to and check if it opened right
    FILE * fTemp = fopen("__temp.txt", "w");
    if(fTemp == NULL)
        ExitEarly(307, "Couldnt make temporary file (__temp)");
    
    char * thisLine = CharMalloc(2048);

    //in this context, i is the current file line
    for(u64 i = 0; ; i ++){
        //Reached EOF (end of file)
        if(fgets(thisLine, 2048, fOrigin)== NULL)
            break;

        if(i == whatFileLine)
            startWrite = true;

        if(startWrite){
            char curChar = argSequence[0];

            //Go through ALL arguments
            for(u32 j = 0; j < (u32)strlen(argSequence); j ++, curChar = argSequence[i]){
                //Always want to displace pointer AND update line counter
                fgets(thisLine, 2048, fOrigin);  
                i ++;
               
                /*
                 * Boop. This is a list of the arguments that this function takes :> (for argSequence)
                 *
                 * Integers
                 * 0 - i8
                 * 1 - u8
                 * 2 - i16
                 * 3 - u16
                 * 4 - i32
                 * 5 - u32
                 * 6 - i64
                 * 7 - u64
                 *
                 * Factorials
                 * 8 - f6
                 * 9 - f18
                 *
                 * Other
                 * b - bool
                 * c - char
                 * s - string (array of chars)
                 *
                 * Typedef
                 * p - path
                 *
                 * Pointers not allowed (nor structs)!!
                 */

                //Pls ignore, i think it all works
                switch(curChar){
                    case '0': //i8
                        fprintf(fTemp, "%hi\n", (i8)va_arg(args, int));
                        break;

                    case '1': //u8
                        fprintf(fTemp, "%hu\n", (u8)va_arg(args, int));
                        break;

                    case '2': //i16
                        fprintf(fTemp, "%hi\n", (i16)va_arg(args, int));
                        break;

                    case '3': //u16
                        fprintf(fTemp, "%hu\n", (u16)va_arg(args, int));
                        break;

                    case '4': //i32
                        fprintf(fTemp, "%d\n", va_arg(args, i32));
                        break;

                    case '5': //u32
                        fprintf(fTemp, "%u\n", va_arg(args, u32));
                        break;

                    case '6': //i64
                        fprintf(fTemp, "%lld\n", (i64)va_arg(args, int)); 
                        break;

                    case '7': //u64
                        fprintf(fTemp, "%llu\n", (u64)va_arg(args, int));
                        break;

                    case '8': //f6
                        fprintf(fTemp, "%f\n", (f6)va_arg(args, double));
                        break;

                    case '9': //f18
                        fprintf(fTemp, "%lf\n", va_arg(args, f18));
                        break;

                    case 'b': //bool
                        fprintf(fTemp, "%d\n", va_arg(args, int));
                        break;

                    case 'c': //char
                        fprintf(fTemp, "%c\n", (char)va_arg(args, int));
                        break;

                    case 's': //string (array of chars)
                        fprintf(fTemp, "%s\n", va_arg(args, char *));
                        break;

                    case 'p': //path
                        fprintf(fTemp, "%s\n", va_arg(args, path));
                        break;
                }
            }
            startWrite = false;

        } else
            fprintf(fTemp, "%s\n", thisLine);

        memset(thisLine, '\0', 2048);
    }

    SafeFree(thisLine);

    fclose(fOrigin);
    fclose(fTemp);

    //end args
    va_end(args);

    remove(fileName);
    rename("__temp.txt", fileName);

    chdir(homePath);

    return;
}

//The diference bettewn "ShowDialogueMsg" and "GetDialogueMsg" is quite literaly just the return value lol 

//Neeeds an extra argument for "NPC name" to display the NPC name when doing the printf lmao
void ShowDialogueMsg(const char * whatTopic, u64 startLine, u64 followUpLines, u32 cacheCode, bool showTopic){
   
    //for loop needs to execute at least once.
    if(followUpLines < 1)
        followUpLines = 1;

    char fileName [50] = { '\0' };

    //fileName is kinda like: (whatTopic.'-'.lang.".txt") Ex: "Start-en.txt"
    strcpy(fileName, whatTopic);
    strcat(fileName, "-");
    strcat(fileName, lang);
    strcat(fileName, ".txt");

    if(access(fileName, F_OK)!= 0)
        ExitEarly(301, "Language file not found for \"ShowDialogueMsg\"");

    //Open language file to extract contents
    FILE * fDialogue = fopen(fileName, "r");
    if(fDialogue == NULL)
        ExitEarly(302, "Tried to open language file, pointer returned NULL");

    //Fast search with cache   
    if(cacheCode != 0)
        SeekToCached(fDialogue, cacheCode);

    //TODO: get rid of GetDialogueMsg, put the code here and call it a day

    char * dialogueLine = CharMalloc(2048); 

    //displace pointer
    for(u64 i = 0; i < startLine; i ++)
        fgets(dialogueLine, 2048, fDialogue);

    //Start displaying correct lines
    for(u64 i = 0; i < followUpLines; i ++){
        fgets(dialogueLine, 2048, fDialogue);

        //this "showTopic" is when an NPC is talking
        if(showTopic)
            printf("[NPC] %s: \"", whatTopic);
        
        printf("%s", dialogueLine);

        if(showTopic)
            printf("\"");

        printf("\n");
    }

    SafeFree(dialogueLine);
    fclose(fDialogue);

    return;
}

//Here we dont care about followUpLines cuz it would make this worse for the receiving end
char * GetDialogueMsg(u64 startLine, u32 returnMany, FILE * fThisFile){

    bool closeThisFile = false;

    if(returnMany < 1)
        returnMany = 1;

    /*
     * How lang cache works:
     *
     * We have a few lines reserved to every "topic" thats on Living Delusion and each "topic" has an ftell value
     * So when i select a specific "topic" i can quickly fseek into it by just looking at its ftell value
     * (hopefully that made sense)
     */

    /*
     * Argument interperter i guess?
     * Check lang (char lang [2])     
     * Set PTR pos
     * Get the dialogue part?
     * need 2 think deeply ab this i cant fuck this up lol
     */

    char fileName [10] = "lang";

    //change to lang directory
    chdir(LOCAL_PATH);
    chdir("lang");

    //LD caller (Fp is NULL if its not called by ShowDialogueMsg)
    if(fThisFile == NULL){
        closeThisFile = true;

        if(access(fileName, F_OK)!= 0)
            ExitEarly(301, "Language file not found for \"GetDialogueMsg\"");

        //Open original file to read from and check if it opened right
        fThisFile = fopen(fileName, "r");
        if(fThisFile == NULL)
            ExitEarly(302, "Tried to open language file, pointer returned NULL");
            
    }

    //Git the char *'s
    char * thisLine = CharMalloc(2048);
    char * nextDialogueLine = CharMalloc(10240);
    
    //strcat thisLine if returnMany allows.

    if(closeThisFile)
        fclose(fThisFile);

    SafeFree(thisLine);

    return nextDialogueLine;
}

//Helper function (used by other FILE I/O functions), automaticly displaces pointer to the requied position! 
void SeekToCached(FILE * fThisFile, u32 contentLine){ 

    //very clean function, im proud

    i64 displaceVal = 0;

    if(contentLine < 1)
        contentLine = 1;

    //File pointer is faulty (probably wouldnt happend but you never know)
    if(fThisFile == NULL)
        ExitEarly(301, "Tried to open file to get cache value, pointer was NULL");

    //displace ptr untill the line that contains the cache value
    for(u32 i = 0; i < contentLine; i ++)
        if(fscanf(fThisFile, "%lld", &displaceVal)== EOF)
            ExitEarly(308, "Couldn't displace pointer untill cache value nor could read the cache value, fscanf returned EOF");

    //profit.
    if(fseek(fThisFile, displaceVal, SEEK_SET) != 0)
        ExitEarly(309, "Couldn't displace pointer to cached value, cached value was faulty, fseek returned NON 0");

    return;
}
