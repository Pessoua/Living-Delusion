#include "../LivingDelusion.h"

//Center texts thats passed through the parameter
void CenterText(const char * line){
    printf("%*s\n", ((GetTerminalSize("columns") - strlen(line)) / 2) + strlen(line), line);
    return;
}

//Same has function above but it puts it in the right side of the screen
void RightText(const char * line){
    printf("%*s\n", (GetTerminalSize("columns") - strlen(line)) + strlen(line), line);
    return;
}

//Same has above but X and Y arent random but are actually divided by 2 (and formated accordingly)
void MidScreenText(const char * line){
    for(int i = 0; i < (GetTerminalSize("rows") / 2); i ++)
        printf("\n");

    printf("%*s\n", ((GetTerminalSize("columns") - strlen(line)) / 2) + strlen(line), line);
    return;
}

//Same has function above but randomize X and Y value (and properly format them)
void RandText(const char * line){
    CLR;

    //Randomize X
    int rand_width = rand()% GetTerminalSize("columns") + 1;
    //Format X
    rand_width = (rand_width - strlen(line)) + strlen(line);

    //Randomize Y (no need for formating)
    int rand_rows = rand()% GetTerminalSize("rows") + 1;

    //Randomize number of lines
    const int numb_lines = rand()% 5 + 1;

    //Modify Y
    for(int i = 0; i < rand_rows; i ++)
        printf("\n");

    //Print result
    for(int i = 0; i < numb_lines; i ++)
        printf("%*s\n", rand_width, line);

    return;
}
