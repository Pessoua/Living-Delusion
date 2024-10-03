#include "../LivingDelusion.h"

/* 
 * Instead of extras having the like scanf thing we make it so its a function that ONLY takes input like:
 * extras(thisCommand);
 * And also make it so extras IS the troubleshooting manual too (from ../../tools)
 */

extrasReturn * extras(char * watCommand){
    
    bool debugMode = false;

    extrasReturn * funRet = malloc(sizeof(extrasReturn));
    funRet->errorType = 0;

    //TODO: CHANGE TO SAVE-1 FOR THE LOVE OF GOD!

    char *context1 = NULL, *context2 = NULL, *context3 = NULL, *context4 = NULL, *command; 

    //do stuff with output (lul)
    command = strtok_r(watCommand, " ", &context1);

    //empty string lol
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

    fclose(fcmd);
   
    //funtion not found
    if(watFunction == -1){
        funRet->errorType = 1;
        return funRet;
    }

    //These one store the real user input thats gonna be used later
    char flags [numFlags];
    char arguments [numArgs] [4096];
    for(int i = 0; i < numArgs; i ++)
        arguments[i][0] = '\0';

    u8 curFlag = 0, curArg = 0;

    //Continue with flag / argument searching
    while(true){
        bool isValid = false, passingOptional = false;  

        if(context1 == NULL)
            break;

        //check if its a possible start of a string (dont displace context buffer if it is)
        if(context1[0] != '\"' || watArgumentType[curArg] != 's'){
            command = strtok_r(NULL, " ", &context1);

            if(command == NULL)
                break;

        } else {
            context4 = (char *)malloc(sizeof(char) * strlen(context1));
            strcpy(context4, context1);
            command = strtok_r(NULL, " ", &context4);

            if(command == NULL)
                break;
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
 
                    //invalid (global) flag
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

            //too many arguments!
            if(curArg > numArgs){
                funRet->errorType = 4;
                return funRet;
            }

            //optional argument case
            char watArgumentTypeCOPY = watArgumentType[curArg];

            //optional arg detected, skip it
            if(strlen(command)== 1 && command[0] == '?'){
                watArgumentTypeCOPY = 'l';  //dont want to modify the char array itself but the char thats processed by the switch (l case dosent exist, still passes with no error though!)
                passingOptional = true;

            }
                
            bool isValidArg = true, reachedVoid = false;
            switch(watArgumentTypeCOPY){
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
                    
                    //hmm yes yes chars.
                    if(strlen(command)!= 3 && command[0] == '\'' && command[2] == '\'')
                        isValidArg = false;

                    //getting rid of the ' '
                    command[0] = command[1];
                    command[1] = '\0';

                    break;

                case 's':   //string
                    //needs to be like "string" lol     

                    //char getStr [strlen(context1)];
                    char * getStr = strtok_r(context1, "\"", &context3); 

                    //Checking if str is valid (checking for starting " and ending ")
                    if(context1[strlen(getStr) - 1] != '\"' && context1[0] != '\"')
                        isValidArg = false;
  
                    else {
                        //We use for loop here because im scared of strcpy :D
                        for(u16 i = 0; i < (u16)strlen(getStr); i ++)
                            arguments[curArg][i] = getStr[i];

                        arguments[curArg][strlen(getStr)] = '\0';

                    }

                    //Update context cause we dont want the program yelling at us for fucked up context
                    strcpy(context1, context3);
 
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
                //We already modify the arguments array inside the string case so no need for this
                if(watArgumentType[curArg] != 's')
                    strcpy(arguments[curArg], command);

                //Overwriting previous if it is a string type
                if(passingOptional && watArgumentType[curArg] == 's')
                    strcpy(arguments[curArg], command);

                curArg ++;
            }

        }
    }

    //Parsing this command with the csv line
    switch(watFunction){
        //TODO: dont forget optional arguments are with '?'  

        case 1:
            //Parse flags
            
            //Parse arguments

            //Call funtion
            break;

        default:
            break;
    }

    if(debugMode)
        for(u8 i = 0; i < numArgs; i ++)
            printf("[EXT DEBUG] _> arguments[%d]? %s\n", i, arguments[i]);

    return funRet;
}
