#include "LivingDelusion.h"

void DoFuniHere(void);

//Testing functions when idk if my custom funcions work well or not (also testing other stuff)
void DoFuniHere(void){ 

    extrasReturn * catchNextExtras;

    //need to do tis else it wont malloc the str and the str will be READ ONLY
    char *cmd = strdup("cmd1 -!D -Y 2 12.1");
    catchNextExtras = extras(cmd); 

    //TODO: flags with arguments: "-!O 2" (!O - Global Optional flag, 2 - what arguments to be optional (AKA, reset argument 2 to its DEFAULT value)) 
    
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
