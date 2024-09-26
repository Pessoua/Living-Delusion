#include "LivingDelusion.h"

void DoFuniHere(void);

//Testing functions when idk if my custom funcions work well or not (also testing other stuff)
void DoFuniHere(void){ 

    extrasReturn * catchNextExtras;

    catchNextExtras = extras("cmd1 -Y"); 

    printf("Error -> %d\n", catchNextExtras->errorType); 

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
