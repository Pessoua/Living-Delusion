#include "../LivingDelusion.h"

//yeah it also returns errors :sunglasses:
u8 FormatText(Format * extraArgs){
    
    /*
     * using this struct btw! (declared in style!ld.h)
     *
     * typedef struct {
     *    char * msg;
     *    bool newLine;
     *    u16 repeatTimes, displaceX, displaceY, modeId;
     * } Format;
     */

    //Git strlen
    u16 finalStrlen = strlen(extraArgs->msg) + GetStrlenOfANSI(extraArgs->msg);

    //Rand mode has a dependency for diplaceX
    if(extraArgs->displaceX == 0 && extraArgs->modeId == 3)
        extraArgs->displaceX = ((rand()% GetTerminalSize("columns") + 1) - finalStrlen) + finalStrlen;

    //Mode dependencies for Y formatting
    if(extraArgs->displaceY == 0 && extraArgs->modeId == 2)
        extraArgs->displaceY = GetTerminalSize("rows") / 2;

    else if(extraArgs->displaceY == 0 && extraArgs->modeId == 3)
        extraArgs->displaceY = rand()% GetTerminalSize("rows") + 1;

    //Displace Y
    if(extraArgs->displaceY != 0){
        for(u16 i = 0; i < extraArgs->displaceY; i ++)
            printf("\n");
    }

    //Rand mode has a dependency for repeatTimes too
    if(extraArgs->repeatTimes == 0 && extraArgs->modeId == 3)
        extraArgs->repeatTimes = rand()% 5 + 1;

    if(extraArgs->repeatTimes == 0)
        extraArgs->repeatTimes ++;

    //Repeat ... times
    for(u16 i = 0; i < extraArgs->repeatTimes; i ++){
        switch(extraArgs->modeId){
            //Center and Mid
            case 0:
            case 2:
                printf("%*s", (((GetTerminalSize("columns") - finalStrlen) / 2) + finalStrlen) + extraArgs->displaceX, extraArgs->msg);
                break;

                //Right
            case 1:
                printf("%*s", ((GetTerminalSize("columns") - strlen(extraArgs->msg)) + finalStrlen) + extraArgs->displaceX, extraArgs->msg);
                break;

                //Rand
            case 3:
                printf("%*s", extraArgs->displaceX, extraArgs->msg);
                break;

            //Return error (no mode given)
            default:
                return 1;
                break;
        }

        //need 2 have a newline for each iteration of the loop if we are doing a loop lol
        if(i < extraArgs->repeatTimes - 1)
            printf("\n");
    }

    //New line?
    if(extraArgs->newLine)
        printf("\n");

    return 0;
}

//Center texts thats passed through the parameter
void CenterText(const char * line){
    u16 actualStrlen = strlen(line) + GetStrlenOfANSI(line);
    printf("%*s\n", ((GetTerminalSize("columns") - actualStrlen) / 2) + actualStrlen, line);
    return;
}

//Same has function above but it puts it in the right side of the screen
void RightText(const char * line){
    u16 actualStrlen = strlen(line) + GetStrlenOfANSI(line);
    printf("%*s\n", (GetTerminalSize("columns") - strlen(line)) + actualStrlen, line);
    return;
}

//Same has above but X and Y arent random but are actually divided by 2 (and formated accordingly)
void MidScreenText(const char * line){
    for(u16 i = 0; i < (GetTerminalSize("rows") / 2); i ++)
        printf("\n");

    u16 actualStrlen = strlen(line) + GetStrlenOfANSI(line);
    printf("%*s\n", ((GetTerminalSize("columns") - actualStrlen) / 2) + actualStrlen, line);
    return;
}

//Same has function above but randomize X and Y value (and properly format them)
void RandText(const char * line){
    CLR;
    u16 actualStrlen = strlen(line) + GetStrlenOfANSI(line);

    //Randomize X
    int rand_width = rand()% GetTerminalSize("columns") + 1;
    //Format X
    rand_width = (rand_width - actualStrlen) + actualStrlen;

    //Randomize number of lines
    u8 numb_lines = rand()% 5 + 1;

    //Modify Y
    for(u16 i = 0; i < (rand()% GetTerminalSize("rows") + 1); i ++)
        printf("\n");

    //Print result
    for(u8 i = 0; i < numb_lines; i ++)
        printf("%*s\n", rand_width, line);

    return;
}

//Helper function cuz ANSI escape codes normaly fuck up the formating lol
u16 GetStrlenOfANSI(const char * line){

    u16 ansiSize = 0, ansiSizeAdd = 0;

    for(u32 i = 0; i < strlen(line); i ++){
        if(line[i] == '['){
            ansiSize += 2;
            ansiSizeAdd = 0;

            while(line[i + ansiSizeAdd] != 'm')
                ansiSizeAdd ++;

            ansiSize += ansiSizeAdd;
        }
    }

    return ansiSize;
}

