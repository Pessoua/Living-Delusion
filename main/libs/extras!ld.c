#include "../LivingDelusion.h"

/* 
 * Instead of extras having the like scanf thing we make it so its a function that ONLY takes input like:
 * Extras(const char * command);
 * And also make it so extras IS the troubleshooting manual too (from ../../tools)
 */

extrasReturn * extras(const char * watCommand){
    
    extrasReturn funRet = malloc(sizeof(extrasReturn));
    funRet->errorType = 0;

    //CHANGE TO SAVE-1 FOR THE LOVE OF GOD!

    //do stuff with output (lul)
    char * command = strtok(thisCommand, " ");

    //Check if main command exists
    //Get parameters and flags
    
    u8 numFlags = 1;

    //USE FILE FROM config/ on LOCALAPPDATA

    char watFlags [numFlags], char arguments [numArgs] [2];

    char * flags = (char *)malloc(sizeof(char));
    u16 curFlag = 0;

    //Continue with flag searchinG
    while(command != NULL){
        bool isValid = false;
        command = strtok(NULL, " ");

        //Is a flag.
        if(command[0] == '-'){
            for(u8 i = 0; i < numFlags; i ++){
                if(command[1] == watFlags[i]){
                    isValid = true;
                    break;
                }
            }

            //Add new flag + dynamicly expand the array
            if(isValid){
                flags[curFlag] = command[1];
                curFlag ++;

                newFlags = realloc(flags, sizeof(char) * curFlag + 1);
                flags = newFlags;

                //Invalid Flag.
            } else {
                funRet->errorType = 1;
                return funRet;
            }

        //Its an argument
        } else {
            for(u8 i = 0; i < numArgs; i ++){
                switch(arguments[i][0]){
                    case 'i':
                        //can also be something like "ip" making it int pointer


                    //none
                    default:
                        break;
                }
            }
        }
    }

    //Parsing this command with the csv line
    switch(watFunction){
        case 1:
            break;

        default:
            break;
    }

    free(flags);
    return funRet;
}
