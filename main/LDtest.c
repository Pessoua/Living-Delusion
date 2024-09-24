#include "LivingDelusion.h"

typedef struct {
    u8 strSize;
    char * str;
} yes;

void DoFuniHere(void);
u16 GetStrlenOfANSI(const char * line);
yes * testfun(void);


//Testing functions when idk if my custom funcions work well or not (also testing other stuff)
void DoFuniHere(void){ 
    yes * test = NULL;
    test = testfun();

    yes temp;

    temp.strSize = 9;
    temp.str = (char *) malloc(sizeof(char) * temp.strSize);

    strcpy(temp.str, "12345678");

    printf("%s\n", temp.str);
    printf("%p\n", test);

    printf("%d\n", test->strSize);
    printf("%s\n", test->str);

    free(test);

    return;
}

yes * testfun(void){
    
    yes * yesObject = malloc(sizeof(yes));

    yesObject->strSize = 2;
    yesObject->str = "test";

    return yesObject;
}

int main(void){

    time_needed = clock();                              
    srand(time(NULL));                              
    setlocale(LC_ALL, "");                          
    system("title (test ver.) LIVING DELUSION [OPEN BETA 2]");

    DEBUG_MODE = true;

    DoFuniHere();

    return 0;
} 
