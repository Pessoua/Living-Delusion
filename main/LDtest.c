#include "LivingDelusion.h"

void DoFuniHere(const char * argStr, ...);
void DoFuniHereBckp(void);

//Testing functions when idk if my custom funcions work well or not (also testing other stuff)
void DoFuniHere(const char * argStr, ...){  

    return;
}

void DoFuniHereBckp(void){

    //I HATE STRINGS!!!!!!!!!!    

    return;
}

int main(void){

    time_needed = clock();                              
    srand(time(NULL));                              
    setlocale(LC_ALL, "");                          
    system("title (test ver.) LIVING DELUSION [OPEN BETA 2]");

    DEBUG_MODE = true;

    DoFuniHere("0123456789bcsp", 0, 1, 2, 3, 4, 5, 6, 7, 8.00, 9.00, true, 'a', "string", "C:/LOCAL/IDK"); 
    //DoFuniHereBckp();

    return 0;
} 
