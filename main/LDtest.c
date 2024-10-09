#include "LivingDelusion.h"

void DoFuniHere(void);
void DoFuniHereBckp(void);

//Testing functions when idk if my custom funcions work well or not (also testing other stuff)
void DoFuniHere(void){

    for(u8 i = 0; i < 255; i ++)
        printf("\x1b[38;5;%dmAre these enough colors? (%d)\x1b[0m\n", i, i);
   
    printf("\x1b[38;5;255mLast color?\x1b[0m\n");

    return;
}

void DoFuniHereBckp(void){

    //bip

    return;
}

int main(void){

    time_needed = clock();                              
    srand(time(NULL));                              
    setlocale(LC_ALL, "");                          
    system("title (test ver.) LIVING DELUSION [OPEN BETA 2]");

    DEBUG_MODE = true;

    DoFuniHere(); 
    //DoFuniHereBckp();

    return 0;
} 
