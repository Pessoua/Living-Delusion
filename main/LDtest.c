#include "LivingDelusion.h"

void DoFuniHere(void);
void DoFuniHereBckp(void);

//Testing functions when idk if my custom funcions work well or not (also testing other stuff)
void DoFuniHere(void){ 

    extrasReturn * catchNextExtras;

    //need to do tis else it wont malloc the str and the str will be READ ONLY
    char *cmd = strdup("cmd1 -!D -Y \"THIS IS A STRING\" 12");
    catchNextExtras = extras(cmd); 

    //We are finished.
    
    printf("Error -> %d\n", catchNextExtras->errorType); 

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

    DoFuniHere(); 
    //DoFuniHereBckp();

    return 0;
} 
