#include "../art!ld.h"

//Soo, callerTopic determines the name of the file and typeWanted is the cache value :D
//For reference, 1 plant stage is the 1st type of the Topic plant, 2 plant stage is the 2nd type of the Topic plant
//They all stop of either EOF or when "ART_TYPE_END" is reached
u32 Art(const char * callerTopic, u8 typeWanted, ArtOptions * ArtModifiers){

    bool enableInternalModif = false;
    u8 colorPallet [17];
    u32 expectedRowSize = 0;
    char fileName [strlen(callerTopic) + 4], * artContext = NULL, contextBckp [2048];
    
    memset(fileName, '\0', strlen(callerTopic) + 4);

    for(u8 i = 0; i < 17; i ++)
        colorPallet[i] = i;

    //Set home path
    path homePath;
    GetCurPath(homePath);

    if(ArtModifiers != NULL)
        enableInternalModif = true;

    //TODO: uncomment this
    //chdir(LOCAL_PATH);
    //chdir("art");

    strcpy(fileName, callerTopic);
    strcat(fileName, ".txt");

    //error handling file related things
    if(access(fileName, F_OK)!= 0)
        ExitEarly(401, "Expected to find an art file to display some art, file not found");

    char artLine [2048];

    FILE * fThisArt = fopen(fileName, "r");
    if(fThisArt == NULL)
        ExitEarly(401, "Art file pointer returned NULL");

    //set pointer to start of art with the cached pointer
    SeekToCached(fThisArt, typeWanted);

    //Set up the extra arguments
    if(enableInternalModif){
        //No filter? Use the pallet provided
        if(strcmp(ArtModifiers->filter, "none")== 0)
            for(u8 i = 0; i < 17; i ++)
                colorPallet[i] = ArtModifiers->pallet[i];

        else if(strcmp(ArtModifiers->filter, "gray")== 0){
            //grayscale or smt (232 to 255 but only even numbers)
            for(u8 i = 232, j = 0; i < 255; i ++){
                if(i % 2 == 0){
                    colorPallet[j] = i;
                    j ++;
                }
            }
        }
        
    }

    //So we only want to stop reading when EOF is reached or "ART_TYPE_END\n" is called
    while(true){

        if(fgets(artLine, 2048, fThisArt)== NULL)
            break;

        if(strcmp(artLine, "ART_TYPE_END\n")== 0)
            break;
        
        u8 displacement = 0;

        char * safeLine = strtok(artLine, "|/");

        //printf("artContext ->%s\n", artContext);

        if(safeLine == NULL)
            printf("%s", artLine);        

        //Getting colors
        while(true){
            //strcpy(contextBckp, artContext);

            if(safeLine == NULL)
                break;

            displacement += (u8)strlen(safeLine) + 2;
            printf("%s", safeLine);
            u16 formatCode = artLine[displacement];

            /*printf("artContext? %s\n", artContext);

            //Also ignore code
            for(u16 i = strlen(safeLine); i < strlen(artLine); i ++)
                contextBckp[i] = artContext[i + 1];

            artContext = contextBckp;
            printf("artContext? %s\n", artContext);
            printf("contextBckp? %s\n", contextBckp);*/

            switch(formatCode){
               
                case 48 ... 57:
                case 97 ... 109:
                    printf(" __DEFAULT COLOR CODE__ ");
                    break;

                default:
                    printf("\x1b[0m");
                    break;
            }

            safeLine = strtok(NULL, "|/");
        }
    }

    //TODO: remove tis
    printf("\n");

    //end.
    printf("\x1b[0m");
    fclose(fThisArt);
    chdir(homePath);

    return expectedRowSize;
}

/*int Art(const char *CALLER, const int Parameter){

    //Change to needed dir
    GetAppResources("Art");
    CatCurPath(CALLER);

    //Declare some vars
    char * temp_str = (char *)malloc(25);
    char * ARTLINE = (char *)malloc(256); 
    char temp_char = '\0';
    int needed_row_size = 0;

    if(strcmp(CALLER, "BIRD")== 0){
        //Set starting vars
        char temp[4] = { '\0' }, file[3] [6] = { '\0' };

        itoa(Parameter, temp, 10);

        //Set file names
        if(temp[0] == '1')
            strcpy(file[2], "6.txt");

        else
            strcpy(file[2], "3.txt");

        if(temp[1] == '1')
            strcpy(file[1], "5.txt");

        else
            strcpy(file[1], "2.txt");

        if(temp[2] == '1')
            strcpy(file[0], "4.txt");

        else
            strcpy(file[0], "1.txt");

        FILE * fbirdhouse[3];

        //Declare starting file pointers
        fbirdhouse[0] = fopen(file[0], "r");
        fbirdhouse[1] = fopen(file[1], "r");
        fbirdhouse[2] = fopen(file[2], "r");

        //Copy of the code bellow but it switches bettewn the 3 file outputs and formats them acordingly
        while(fgets(ARTLINE, 256, fbirdhouse[0])!= NULL){
            ARTLINE[strlen(ARTLINE) - 1] = '\0';

            //change this constant or ill jump off a bridge
            printf("%*c", 50, temp_char);

            for(int k = 0; k < 3; k ++){
                //Format spaces (the color formating things wont be used so we gotta format it again)
                for(int i = 0; i < strlen(ARTLINE); i ++){
                    if(ARTLINE[i] == '/' && isdigit(ARTLINE[i + 1]) && ARTLINE[i + 2] == '/'){
                        for(int j = 0; j < 3; j ++)
                            printf(" ");
                    }
                }

                //Putting color on the output depending on what code we detect
                for(int i = 0; i < strlen(ARTLINE); i ++){

                    if(ARTLINE[i] == '/' && isdigit(ARTLINE[i + 1]) && ARTLINE[i + 2] == '/'){

                        //Hex color
                        if(isalpha(ARTLINE[i + 1]) != 0)
                            ChangeToThisColor(0, ARTLINE[i + 1]);

                        int color = (int)ARTLINE[i + 1];
                        color -= 48;

                        //Remove the intruding "/[COLOR]/" from the output
                        i += 3;

                        ChangeToThisColor(color, '.');
                    }
                    printf("%c", ARTLINE[i]);

                }

                if(k != 2){
                    memset(ARTLINE, '\0', sizeof(ARTLINE));
                    fgets(ARTLINE, 256, fbirdhouse[k + 1]); 
                }
            }

            memset(ARTLINE, '\0', sizeof(ARTLINE));
            printf("\n");
        }

        fclose(fbirdhouse[0]);
        fclose(fbirdhouse[1]);
        fclose(fbirdhouse[2]);

        return 0;
    }

    itoa(Parameter, temp_str, 10);
    strcat(temp_str, ".txt");

    if(access(temp_str, F_OK)!= 0)  //Error code
        return -1;

    //Extract the needed info from the file
    FILE * facessedart = fopen(temp_str, "r");

    while(fgets(ARTLINE, 256, facessedart)!= NULL){
        ARTLINE[strlen(ARTLINE) - 1] = '\0';    //Prevent fgets from putting \n at the end

        //Git good text formating
        printf("%*c", ((GetTerminalSize("columns") - strlen(ARTLINE)) / 2), temp_char);

        //Format spaces (the color formating things wont be used so we gotta format it again)
        for(int i = 0; i < strlen(ARTLINE); i ++){
            if(ARTLINE[i] == '/' && isdigit(ARTLINE[i + 1]) && ARTLINE[i + 2] == '/'){
                for(int j = 0; j < 3; j ++)
                    printf(" ");
            }
        }

        //Putting color on the output depending on what code we detect
        for(int i = 0; i < strlen(ARTLINE); i ++){

            if(ARTLINE[i] == '/' && isdigit(ARTLINE[i + 1]) && ARTLINE[i + 2] == '/'){

                //Hex color
                if(isalpha(ARTLINE[i + 1]) != 0)
                    ChangeToThisColor(0, ARTLINE[i + 1]);

                int color = (int)ARTLINE[i + 1];
                color -= 48;

                //Remove the intruding "/[COLOR]/" from the output
                i += 3;

                ChangeToThisColor(color, '.');
            }
            printf("%c", ARTLINE[i]);

        }
        printf("\n");
        needed_row_size ++;
    }

    //We done
    fclose(facessedart);
    free(temp_str);
    free(ARTLINE);
    white;

    return needed_row_size;
}*/
