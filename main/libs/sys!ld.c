#include "../LivingDelusion.h"

//Creates random words depending on the ammount of spaces inputted
char * EncryptedWordsV1(u8 numOfSpaces){

    u32 curWord = 0;
    char * finalStr = CharMalloc(555);

    for(u8 i = 0; i < numOfSpaces; i ++){
        u8 strSize = rand()% 10 + 3;
        strSize += 2;

        for(u32 j = 0; j < strSize; j ++){
            u8 randNum = rand()% 93 + 1;
            randNum += 32;
            finalStr[curWord] = randNum;
            curWord ++;
        }

        finalStr[curWord] = ' ';
        curWord ++;
    }

    return finalStr;
}

//Same has above but needs example string
char * EncryptedWordsV2(const char * exampleLine){

    char * finalStr = CharMalloc(555);

    u32 curChar = 0, breakVal = strlen(exampleLine);

    while(curChar < breakVal){
        while(exampleLine[curChar] != ' ' && curChar < breakVal){
            u8 randNum = rand()% 93 + 1;
            randNum += 32;

            finalStr[curChar] = randNum;
            curChar ++;
        }

        finalStr[curChar] = ' ';
        curChar ++;
    }

    return finalStr;
}

//Better way of getting string input and making it not case sensitive
void StrInp(void){
    printf("&/");
    scanf("%50s", Input);

    for(u8 i = 0; i < strlen(Input); i ++)
        Input[i] = tolower(Input[i]);

    CLR;
    return;
}

//Converting STR into INT (%d scanf with strings causes issues) 
i64 IntInp(void){
    i64 atoiReturn = 0, actualReturn = 0; 
    bool isZero = true;

    while(true){
        CLR;
        printf("&/");
        scanf("%50s", Input);

        CLR;

        for(u8 i = 0; i < strlen(Input); i ++){
            if(Input[i] != 0){
                isZero = false;
                break;
            }
        }

        atoiReturn = atoi(Input);
        if(isZero)
            atoiReturn ++;

        //Checking if the return has an error AND if its not a Zero
        if(atoiReturn == 0 && !isZero)
            return actualReturn;        
        else
            printf("\x1b[31m[ERROR] _> Oopsie! Invalid command, must be a NUMBER!\n");

    } 
    return actualReturn;
}

//Stuff for LD to run better (retuns false, means we made fresh new paths, returns true means its not new)
bool RunThisAtStart(void){
    if(OS_NAME[0] == 'U')
        ExitEarly(1, "Unknown / Non suported operating system. (STARTUP ERR.)");

    bool pathPreviouslyExist = false;
     
    //set up \x1b (windows only cuz windows big stupid)
    if(OS_NAME[0] == 'W'){
        //Stolen from somewhere (i forgor)
        HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD consoleMode;
        GetConsoleMode( handleOut , &consoleMode);
        consoleMode |= 0x0004;
        consoleMode |= 0x0008;            
        SetConsoleMode( handleOut , consoleMode );
    }

    //get paths and also get the return value to determin if its a new player or a reset
    pathPreviouslyExist = GetNeededPaths();
    
    //Some debug info
    if(DEBUG_MODE){
        printf("[DEBUG] _> OS Detected? ");

        switch(OS_NAME[0]){
            case 'W':
                printf("Windows\n");
                break;

            case 'L':
                printf("Linux\n");
                break;

            case 'A':
                printf("Apple\n");
                break;

            default:
                printf("Unknown / not suported, maybe misspelled it\n");
                break;
        }

        printf("[DEBUG]_> \x1b[31mFOREGROUND Red Color test\x1b[0m\n");
        printf("[DEBUG]_> \x1b[41mBACKGROUND Red Color test\x1b[0m\n");

        printf("\n[DEBUG] _> REGISTERED PATHS:\n");
        printf("[DEBUG] _> STARTER:\t %s\n", STARTING_PATH);
        printf("[DEBUG] _> LOCAL:\t %s\n", LOCAL_PATH);
        printf("[DEBUG] _> FULL:\t %s\n\n", FULL_PATH);
    }

    return pathPreviouslyExist;
}

//Crash, i guess?
void ExitEarly(u16 errCode, char * errMsg){

    CLR;
    if(DEBUG_MODE){
        printf("\x1b[31m[DEBUG] _> Exited with error code %d, with \"%s\" error message\n", errCode, errMsg);
        sleep(5);
    }
    CLR;

    //Adding the stupi ansi escape codes to make it red
    char newErrMsg [strlen(errMsg) + 15];
    strcpy(newErrMsg, "\x1b[31m");
    strcat(newErrMsg, errMsg);
    strcat(newErrMsg, "\x1b[0m");

    MidScreenText(newErrMsg);
    CenterText("\x1b[31mPress anything to crash the game!\x1b[0m");
    getch();

    //on logs -> (dd/mm/yyyy | hh:mm:ss) - 203, "Error happend!"
    
    chdir(LOCAL_PATH);
    char temp [25] = { '\0' };
    char date [25] = { '\0' }, fileTime [25] = { '\0' };

    //Open time struct
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);

    //Get time
    itoa(tm_struct->tm_hour, temp, 10);
    strcpy(fileTime, temp);
    strcat(fileTime, ":");
    memset(temp, '\0', sizeof(temp));
    itoa(tm_struct->tm_min, temp, 10);
    strcat(fileTime, temp);
    strcat(fileTime, ":");
    memset(temp, '\0', sizeof(temp));
    itoa(tm_struct->tm_sec, temp, 10);
    strcat(fileTime, temp);
    memset(temp, '\0', sizeof(temp));

    //Get date
    itoa(tm_struct->tm_mday, temp, 10);
    strcpy(date, temp);
    strcat(date, "/");
    memset(temp, '\0', sizeof(temp));
    itoa(tm_struct->tm_mon + 1, temp, 10);
    strcat(date, temp);
    strcat(date, "/");
    memset(temp, '\0', sizeof(temp));
    itoa(tm_struct->tm_year + 1900 , temp, 10);
    strcat(date, temp);
    memset(temp, '\0', sizeof(temp));

    //No need for error handling, its gonna crash soon anyways...
    FILE * fLogs = fopen("logs.txt", "a");
    fprintf(fLogs, "(%s | %s) - %d, \"%s\"\n", date, fileTime, errCode, errMsg);
    fclose(fLogs);

    exit(errCode);
}

//Safe way to free (stolen from "Using and Understanding C Pointers")
void SaferFree(void ** pointer){
    if(pointer != NULL && *pointer != NULL){
        free(*pointer);
        *pointer = NULL;
    }

    return;
}

//Allocating INT arrays
int * IntMalloc(size_t size){
    int * newInt = NULL;

    newInt = (int *)malloc(sizeof(int) * size);
    memset(newInt, 0, size);

    //Couldnt malloc? show error :D
    if(newInt == NULL){
        ExitEarly(101, "Ran out of memory!");
        return NULL;
    }

    return newInt;
}

//Allocating CHAR arrays (strings)
char * CharMalloc(size_t size){
    char * newChar = NULL;

    newChar = (char *)malloc(sizeof(char) * size);
    memset(newChar, '\0', size);

    //Couldnt malloc? show error :D
    if(newChar == NULL){
        ExitEarly(101, "Ran out of memory!");
        return NULL;
    }

    return newChar;
}
