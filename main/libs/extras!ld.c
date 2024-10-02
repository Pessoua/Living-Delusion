#include "../LivingDelusion.h"

/* 
 * Instead of extras having the like scanf thing we make it so its a function that ONLY takes input like:
 * extras(thisCommand);
 * And also make it so extras IS the troubleshooting manual too (from ../../tools)
 */

extrasReturn * extras(char * watCommand){
    
    bool debugMode = false, isContext3Update = true;

    extrasReturn * funRet = malloc(sizeof(extrasReturn));
    funRet->errorType = 0;

    printf("PASSED 1\n");

    //CHANGE TO SAVE-1 FOR THE LOVE OF GOD!

    char *context1 = NULL, *context2 = NULL, *context3 = NULL, *context4 = NULL, *command; 

    //do stuff with output (lul)
    command = strtok_r(watCommand, " ", &context1);

    if(command == NULL){
        funRet->errorType = 5;
        return funRet;
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
    if(fcmd == NULL)
        ExitEarly(701, "Couldnt find commands.csv, please re-make your LOCALAPPDATA"); 
    
    /*
     * Heres a tiny example of what a line inside commands.csv will look like
     * command, T, Y, i, f, b
     *
     * [command_name], [flags (flags are ALWAYS in uppercase], [argument types (argument types are ALWAYS in lowercase)]
     */
    
    u16 curLine = 0;
    char nextCmdLine [1024] = "abc";

    printf("PASSED 2\n");

    //Entering file and getting stuff to check
    while(fgets(nextCmdLine, 1024, fcmd) != NULL){
        nextCmdLine[strlen(nextCmdLine) - 1] = '\0';
        curLine ++;

        char * tokenToCheck = strtok_r(nextCmdLine, ",", &context2);

        //Start getting flags and argument types from valid command
        if(strcmp(tokenToCheck, command)== 0){
            watFunction = curLine;
            while(tokenToCheck != NULL){
                tokenToCheck = strtok_r(NULL, ",", &context2); 

                //TODO: does not detect the full string!

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
            break;

        }
    }

    printf("PASSED 3\n");

    fclose(fcmd);
    
    if(watFunction == -1){
        funRet->errorType = 1;
        return funRet;
    }

    //These one store the real user input thats gonna be used later
    char flags [numFlags];
    char arguments [numArgs] [4096];

    //TODO: remove this shit lol
    numArgs = 6;

    u8 curFlag = 0, curArg = 0;

    printf("PASSED 4\n");

    //Optional arg stuff
    u8 optArgsCount = 1;
    char * optionalArgs = (char *)malloc(sizeof(char));

    //Continue with flag / argument searching
    while(true){
        bool isValid = false;  

        //check if its a possible start of a string (dont displace context buffer if it is)
        if(context1[0] != '\"' || watArgumentType[curArg] != 's'){
            command = strtok_r(NULL, " ", &context1);

            printf("whats inside context1? %s\n", context1);

            if(command == NULL)
                break;

            printf("command -> %s\n", command);

        } else {
            context4 = (char *)malloc(sizeof(char) * strlen(context1));
            strcpy(context4, context1);
            command = strtok_r(NULL, " ", &context4);
        }

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

            //Is global
            if(command[1] == '!'){
                //Global flags dont count has flags because they dont interact with the functions themselfs
                switch(command[2]){
                    case 'D':   //Debug mode
                        debugMode = true;
                        printf("[EXT DEBUG] _> debug mode activated\n");
                        break;

                    case 'O':  //Optional Arguments
                        //Get what argument to make optional
                        command = strtok_r(NULL, " ", &context1);

                        //check if int is valid for argument number
                        for(u16 i = 0; i < strlen(command); i ++){
                            if(!isdigit(command[i])){
                                funRet->errorType = 6;                            
                                return funRet;
                            }
                        }

                        //Set (new) optional argument
                        char * optionalArgsBckp = (char *)realloc(optionalArgs, sizeof(char) * (optArgsCount + strlen(command) + 1));
                        strcat(optionalArgsBckp, ",");
                        strcat(optionalArgsBckp, command);

                        optionalArgs = optionalArgsBckp;
                        free(optionalArgsBckp);

                        optArgsCount ++;
                        break;

                    default:
                        funRet->errorType = 2;
                        return funRet;
                        break;
                }

            } else {
                //Add new flag            
                if(isValid){
                    flags[curFlag] = command[1];
                    curFlag ++;

                    //Invalid Flag.
                } else {
                    funRet->errorType = 2;
                    return funRet;
                }
                
            }
        
        //Its an argument
        } else {

            /*if(watArgumentType[curArg] == 's'){
                if(isContext3Update){
                    strtok_r(watCommand, "\"", &context3);
                    isContext3Update = false;
                } else
                    strtok_r(NULL, "\"", &context3);
            }*/

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
                    //needs to be like "string" lol

                    //Checking if str is valid (start)
                    
                    printf("context1? %s\n", context1);

                    char * getStr = strtok_r(context1, "\"", &context3);
                    printf("getStr? %s\n", getStr);

                    if(getStr[strlen(getStr) - 1] != '\"')
                        isValidArg = false;
  
                    else 
                         strcpy(arguments[curArg], getStr);

                    printf("arguments[curArg]? %s\n", arguments[curArg]);

                        /*char * nextStr = strtok_r(NULL, "\"", &context3); //context3 is only for strings lol

                        printf("PASSED ISVALID CHECK\n");

                        if(nextStr == NULL){
                            isValidArg = false;
                            break;

                        } else {
                            arguments[curArg] = (char *)nextStr;
                        }

                        printf("PASSED isValidArg check 1!\n");
                        //Holds the whole string to then pass into arguments[curArg]
                        char * reallocedArg = (char *)malloc(sizeof(char) * strlen(command) + 1);
                        for(u32 i = 1; i < (u32) strlen(command); i ++)    //dont want the starting '"'
                            reallocedArg[i - 1] = command[i];

                        //strtok everything lol
                        while(true){
                            printf("INSIDE true loop\n");
                            printf("reallocedArg -> %s|\n\n", reallocedArg);
                            //Valid end
                            if(reallocedArg[strlen(reallocedArg) - 1] == '\"'){
                                reallocedArg[strlen(reallocedArg) - 1] = '\0'; //dont want the ending '"'
                                printf("PASSING TO STRCPY\n");
                                arguments[curArg] = *reallocedArg; //this? bad. 
                                break;
                            }

                            printf("GOING TO STRTOK_R!\n");
                            command = strtok_r(NULL, " ", &context1);

                            printf("GOING TO NULL CHECK!\n");
                            printf("command -> %s\n", command);
                            //no string end lol
                            if(command == NULL){
                                isValidArg = false;
                                break;
                            }

                            printf("GOING TO REALLOC!\n");
                            printf("reallocedArg -> %s|\n\n", reallocedArg);
                            printf("strlen(reallocedArg) -> %lld / strlen(command) -> %lld\n", strlen(reallocedArg), strlen(command));
                            //Scary, but we resize the array that holds the string inputted
                            char * tempReallocedArg = (char *)realloc(reallocedArg, sizeof(char) * (u32)(strlen(reallocedArg) + strlen(command) + 1));
                            strcat(tempReallocedArg, " ");
                            strcat(tempReallocedArg, command);
                            printf("tempReallocedArg -> %s\n", tempReallocedArg);
                            reallocedArg = NULL;
                            reallocedArg = tempReallocedArg;
                            free(tempReallocedArg);
                            tempReallocedArg = NULL;
                        }*/

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

                //We already modify the arguments array inside the string case so no need for this
                if(watArgumentType[curArg] != 's')
                    strcpy(arguments[curArg], command);

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
            //Parse flags
            
            //Parse arguments

            //Call funtion
            break;

        default:
            break;
    }

    free(optionalArgs);

    printf("watFlags -> %s\n", watFlags);
    printf("watArgumentType -> %s\n", watArgumentType);

    if(debugMode)
        for(int i = 0; i < numArgs; i ++)
            printf("[EXT DEBUG] _> arguments[i]? %s\n", arguments[i]);

    return funRet;
}
