#include "LivingDelusion.h"

void DoFuniHere(void);
u16 GetStrlenOfANSI(const char * line);

//Testing functions when idk if my custom funcions work well or not (also testing other stuff)
void DoFuniHere(void){ 
    Format test;

    printf("erm what");

    test.msg = "\x1b[31mBeep boop\x1b[0m";
    test.newLine = true;
    test.repeatTimes = 0;
    test.displaceX = -8;
    test.displaceY = 0;
    test.modeId = 1;
   
    //everything works :D

    FormatText(&test);

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
