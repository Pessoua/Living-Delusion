#include "../LivingDelusion.h"

//Literaly just change a file line
void ChangeFileLine(const char *fileName, const char *line, int lineToModify){   
    FILE * fReadLines = fopen(fileName, "r");
    FILE * fTemp = fopen("__temp.txt", "w");

    int curLine = 0;
    char readLine [5000] = { '\0' };

    while(fgets(readLine, 5000, fReadLines)!= NULL){
        if(lineToModify == curLine)
            fprintf(fTemp, "%s\n", line);

        else
            fprintf(fTemp, "%s", readLine);    

        curLine ++;
        memset(readLine, '\0', sizeof(readLine));
    }

    fclose(fReadLines);
    fclose(fTemp);

    remove(fileName);
    rename("__temp.txt", fileName);

    return;
}
