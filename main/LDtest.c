#include "LivingDelusion.h"

void DoFuniHere(void);
void DoFuniHereBckp(void);

//Testing functions when idk if my custom funcions work well or not (also testing other stuff)
void DoFuniHere(void){

    Art("test", 1, NULL);  

    return;
}

void DoFuniHereBckp(void){

    char * a = "this line";

    for(u8 i = 0; a[i + 1]; i ++)
        a[i] = a[i + 1];

    printf("\n");

    return;
}

int main(void){

    time_needed = clock();                              
    srand(time(NULL));                              
    setlocale(LC_ALL, "");                          
    system("title (test ver.) LIVING DELUSION [OPEN BETA 2]");

    DEBUG_MODE = true;

    //DoFuniHere(); 
    DoFuniHereBckp();

    return 0;
} 
