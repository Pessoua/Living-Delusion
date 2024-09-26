#include "../LivingDelusion.h"

/* 
 * Instead of extras having the like scanf thing we make it so its a function that ONLY takes input like:
 * Extras(const char * command);
 * And also make it so extras IS the troubleshooting manual too (from ../../tools)
 */

extrasReturn * extras(char * watCommand){
    
    extrasReturn * funRet = malloc(sizeof(extrasReturn));
    funRet->errorType = 0;

    //CHANGE TO SAVE-1 FOR THE LOVE OF GOD!

    char * context1;
    char * context2;

    //do stuff with output (lul)
    char * command = strtok_r(watCommand, " ", &context1);

    //Use FOR loop to get the LINE where the command lives
    i16 watFunction = -1;
    u8 numFlags = 0, numArgs = 0;

    //These one are to store "passers" aka we store the information of the csv file here
    char * watFlags = (char *)malloc(sizeof(char) * 25);
    char * watArgumentType = (char *)malloc(sizeof(char) * 25);
    //Yes you are limited to 25 flags and 25 arguments.

    //USE FILE FROM config/ on LOCALAPPDATA
    FILE * fcmd = fopen("commands.csv", "r");

    /*
     * Heres a tiny example of what a line inside commands.csv will look like
     * command, T, Y, i, f, b
     *
     * [command_name], [flags (flags are ALWAYS in caps], [argument types (argument types are ALWAYS in lowercase)]
     */

    u16 curLine = 0;
    char nextCmdLine [1024] = "abc";

    while(fgets(nextCmdLine, 1024, fcmd) != NULL){
        curLine ++;

        char * tokenToCheck = strtok_r(nextCmdLine, ",", &context2);

        //Start getting flags and argument types from valid command
        if(strcmp(tokenToCheck, command)== 0){
            watFunction = curLine;
            while(tokenToCheck != NULL){
                tokenToCheck = strtok_r(NULL, ",", &context2);

                //Its a flag
                if(isupper(tokenToCheck[0])){
                    if(numFlags == 0)
                        strcpy(watFlags, tokenToCheck);

                    else
                        strcat(watFlags, tokenToCheck);

                    numFlags ++;

                //Its an argument
                } else {
                    if(numArgs == 0)
                        strcpy(watArgumentType, tokenToCheck);

                    else
                        strcat(watArgumentType, tokenToCheck);

                    numArgs ++;

                }
            }
        }
    }

    //Get parameters and flags
    
    fclose(fcmd);
    
    if(watFunction == -1){
        funRet->errorType = 1;
        return funRet;
    }

    //These one store the real user input thats gonna be used later
    char flags [numFlags];
    char * arguments [numArgs];
    u16 curFlag = 0, curArg = 0;

    //Continue with flag searchinG
    while(command != NULL){
        bool isValid = false;
        command = strtok_r(NULL, " ", &context1);

        //Is a flag.
        if(command[0] == '-'){

            //Too many flags!
            if(curFlag > numFlags){
                funRet->errorType = 4;
                return funRet;
            }

            //Obviously need to cycle through the valid flags to see if its valid or not, dufus
            for(int i = 0; i < numFlags; i ++){
                if(command[1] == watFlags[i]){
                    isValid = true;
                    break;
                }
            }

            //Add new flag            
            if(isValid){
                flags[curFlag] = command[1];
                curFlag ++;

                //Invalid Flag.
            } else {
                funRet->errorType = 2;
                return funRet;
            }

        //Its an argument
        } else {
            
            //too many arguments!
            if(curArg > numArgs){
                funRet->errorType = 4;
                return funRet;
            }

            bool isValidArg = true, reachedVoid = false;
            switch(watArgumentType[curArg]){
                case 'i':   //int

                    for(u16 i = 0; i < strlen(command); i ++){
                        if(!isdigit(command[i])){                   
                            if(i == 0){
                                if(command[0] != '-'){        
                                    isValidArg = false;
                                    break;
                                }

                            } else {
                                isValidArg = false;
                                break;
                            }
                        }
                    }

                    break;

                case 'c':   //char
                    
                    if(strlen(command)!= 1)
                        isValidArg = false;

                    break;

                case 's':   //string
                    //dont need to check for anything :P
                    break;

                case 'f':   //float
                    bool alreadyFoundPoint = false;
                            
                    for(u16 i = 0; i < strlen(command); i ++){
                        if(!isdigit(command[i])){                   
                            if(i == 0){
                                if(command[0] != '-'){        
                                    isValidArg = false;
                                    break;
                                }

                            } else if(command[i] == '.'){
                                if(alreadyFoundPoint){
                                    isValidArg = false;
                                    break;
                                }

                            } else {
                                isValidArg = false;
                                break;
                            }
                        }

                        if(command[i] == '.')
                            alreadyFoundPoint = true;
                    }

                    
                    break;

                case 'b':   //bool

                    if(strlen(command)== 1){    //Assuming this is either 1 or 0
                        if(command[0] != '0' || command[0] != '1')
                            isValidArg = false;

                    } else {                    //Assuming this is either true or false
                        if(strcmp(command, "false")== 0)
                            strcpy(command, "0");

                        else if(strcmp(command, "true")== 0)
                            strcpy(command,  "1");

                        else
                            isValidArg = false;

                    }

                    break;

                case 'v':   //void
                    reachedVoid = true; //dont pass through array
                    break;

                    //none
                default:
                    break;
            }

            //Invalid argument (not telling which one it is :P
            if(!isValidArg){
                funRet->errorType = 3;
                return funRet;

            } else if(!reachedVoid){
                strcpy(arguments[curArg], command);
                curArg ++;
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

    free(watFlags);
    free(watArgumentType);

    return funRet;
}
