#include "../LivingDelusion.h"

/* 
 * Instead of extras having the like scanf thing we make it so its a function that ONLY takes input like:
 * Extras(const char * command);
 * And also make it so extras IS the troubleshooting manual too (from ../../tools)
 */

extrasReturn * extras(char * watCommand){
    
    extrasReturn * funRet = malloc(sizeof(extrasReturn));
    funRet->errorType = 0;

    printf("PASSED 1\n");

    //CHANGE TO SAVE-1 FOR THE LOVE OF GOD!

    char *context1 = NULL, *context2 = NULL, *command; 

    //do stuff with output (lul)
    command = strtok_r(watCommand, " ", &context1); //strtok has an error btw

    if (command == NULL) {

        printf("strtok_r error: %s\n", strerror(errno));

        // Handle error
    }

    //Use FOR loop to get the LINE where the command lives
    i16 watFunction = -1;
    u8 numFlags = 0, numArgs = 0;

    //These one are to store "passers" aka we store the information of the csv file here
    char watFlags [25] = { '\0' };
    char watArgumentType [25] = { '\0' };
    //Yes you are limited to 25 flags and 25 arguments.

    //USE FILE FROM config/ on LOCALAPPDATA
    FILE * fcmd = fopen("commands.csv", "r");
    if(fcmd == NULL){
        //handle file err.
    }
    
    /*
     * Heres a tiny example of what a line inside commands.csv will look like
     * command, T, Y, i, f, b
     *
     * [command_name], [flags (flags are ALWAYS in uppercase], [argument types (argument types are ALWAYS in lowercase)]
     */
    
    u16 curLine = 0;
    char nextCmdLine [1024] = "abc";

    printf("PASSED 2\n");

    while(fgets(nextCmdLine, 1024, fcmd) != NULL){
        nextCmdLine[strlen(nextCmdLine) - 1] = '\0';
        curLine ++;

        char * tokenToCheck = strtok_r(nextCmdLine, ",", &context2);

        //Start getting flags and argument types from valid command
        if(strcmp(tokenToCheck, command)== 0){
            watFunction = curLine;
            while(tokenToCheck != NULL){
                tokenToCheck = strtok_r(NULL, ",", &context2); 

                if(tokenToCheck == NULL)
                    break;

                //Its a flag
                if(isupper(tokenToCheck[0])){
                    watFlags[numFlags] = tokenToCheck[0];
                    numFlags ++;

                //Its an argument
                } else {
                    watArgumentType[numArgs] = tokenToCheck[0];
                    numArgs ++;

                }
            }
            free(tokenToCheck);
            break;
        }
    }

    printf("PASSED 3\n");

    //Get parameters and flags
    
    fclose(fcmd);
    
    if(watFunction == -1){
        funRet->errorType = 1;
        return funRet;
    }

    //These one store the real user input thats gonna be used later
    char flags [numFlags];
    char * arguments [numArgs];
    for(int i = 0; i < numArgs; i ++)
        arguments[i] = NULL;

    u16 curFlag = 0, curArg = 0;

    printf("PASSED 4\n");

    //Continue with flag searchinG
    while(true){
        bool isValid = false;   
        command = strtok_r(NULL, " ", &context1);

        if(command == NULL)
            break;

        printf("command -> %s\n", command);

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

            printf("PASSED NEXT ARG\n");
            printf("watArgumentType[curArg]? %c\n", watArgumentType[curArg]);

            //too many arguments!
            if(curArg > numArgs){
                funRet->errorType = 4;
                return funRet;
            }

            bool isValidArg = true, reachedVoid = false;
            switch(watArgumentType[curArg]){
                case 'i':   //int

                    for(u16 i = 0; i < strlen(command); i ++){
                        printf("PASSED L1\n");
                        if(!isdigit(command[i])){
                            printf("PASSED L2\n");
                            if(i == 0){
                                printf("PASSED L3\n");
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
                    
                    printf("PASSED L BREAK\n");
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
                printf("PASSED reachedVoid check\n");
                arguments[curArg] = command;
                curArg ++;
                printf("passed increment + strcpy\n");
            }

        }
        printf("NEXT LOOP\n");
    }
	
    printf("PASSED 5\n");

    //Parsing this command with the csv line
    switch(watFunction){
        case 1:
            break;

        default:
            break;
    }

    printf("watFlags -> %s\n", watFlags);
    printf("watArgumentType -> %s\n", watArgumentType);

    for(int i = 0; i < numArgs; i ++)
        printf("arguments[i]? %s\n", arguments[i]);


    return funRet;
}
