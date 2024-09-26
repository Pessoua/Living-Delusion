#include "LivingDelusion.h"

void DoFuniHere(void);

//Testing functions when idk if my custom funcions work well or not (also testing other stuff)
void DoFuniHere(void){ 

    char * str = (char *)malloc(sizeof(char) * 25);
 
    strcpy(str, "hello");
    strcat(str, " world");

    printf("%lld\n", sizeof(str));

    char * newStr = (char *)realloc(str, sizeof(char) * strlen(str));
    str = newStr;

    printf("%lld\n", sizeof(str));

    printf("str -> %s\n", str);


    free(str);

    return;
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
