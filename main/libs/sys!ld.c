#include "../LivingDelusion.h"

//Creates random words depending on the ammount of spaces inputted
char * EncryptedWordsV1(short int * numOfSpaces){

    short int curWord = 0;
    char * finalStr = (char *) malloc(sizeof(char) * 555);
    memset(finalStr, '\0', 555);

    for(int i = 0; i < * numOfSpaces; i ++){
        int strSize = rand()% 10 + 3;
strSize += 2;

        for(int j = 0; j < strSize; j ++){
            int randNum = rand()% 93 + 1;
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

    short int curChar = 0, breakVal = strlen(exampleLine);

    while(curChar < breakVal){
        while(exampleLine[curChar] != ' ' && curChar < breakVal){
            int randNum = rand()% 93 + 1;
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
    char Input [50];

    printf("&/");
    scanf("%s", Input);

    for(int i = 0; i < strlen(Input); i ++)
        Input[i] = tolower(Input[i]);

    CLR;
    return;
}

//Converting STR into INT (%d scanf with strings causes issues) 
int IntInp(void){
    char Input [50];

    printf("&/");
    scanf("%s", Input);
    
    CLR;
    return atoi(Input);
}
