#include "../LivingDelusion.h"

//Creates random words depending on the ammount of spaces inputted
char * EncryptedWordsV1(u8 * numOfSpaces){

    u32 curWord = 0;
    char * finalStr = (char *) malloc(sizeof(char) * 555);
    memset(finalStr, '\0', 555);

    for(u8 i = 0; i < * numOfSpaces; i ++){
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

    char * finalStr = (char *)malloc(sizeof(char) * 555);
    memset(finalStr, '\0', 555);

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

//Stuff for LD to run better
bool RunThisAtStart(void){
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
    //pathPreviouslyExist = GetNeededPaths();
    
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
                printf("Unknown, maybe misspelled it\n");
                break;
        }

        printf("[DEBUG]_> \x1b[31mFOREGROUND Red Color test\x1b[0m\n");
        printf("[DEBUG]_> \x1b[41mBACKGROUND Red Color test\x1b[0m\n");

        SmallStop;
    }

    return pathPreviouslyExist;
}
