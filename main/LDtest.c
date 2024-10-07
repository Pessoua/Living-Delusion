#include "LivingDelusion.h"

void DoFuniHere(void);
void DoFuniHereBckp(void);

//Testing functions when idk if my custom funcions work well or not (also testing other stuff)
void DoFuniHere(void){

    //TODO: Test ShowDialogueMsg

    FILE * fTestThat = fopen("test.txt", "r");

    SeekToCached(fTestThat, 1);

    char lineSeekedTo [50];
    fgets(lineSeekedTo, 50, fTestThat);
    lineSeekedTo[strlen(lineSeekedTo) - 1] = '\0';
    printf("Line seeked to? %s / ftell Val? %ld\n", lineSeekedTo, ftell(fTestThat) - (i32)strlen(lineSeekedTo));

    fclose(fTestThat);

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

    //DEBUG_MODE = true;

    DoFuniHere(); 
    //DoFuniHereBckp();

    return 0;
} 
