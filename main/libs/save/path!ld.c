#include "../save!ld.h"

//Check if dir exists [Not made by me, thanks for whoever did it though]
bool ExistDiret(const char * path){
    struct stat stats;

    stat(path, &stats);

    if (S_ISDIR(stats.st_mode)){
        return true;
    }

    return false;
}

//Get current path w error handling
void GetCurPath(path newPath){

    memset(newPath, '\0', PATH_MAX_LEN);

    if(getcwd(newPath, PATH_MAX_LEN) == NULL)
        ExitEarly(204, "Failed to get home path on ReadFromFile, getcwd returned NULL");

    return;
}

//Changes cur path based on FULL_PATH
void ChangeCurPath(const char * changeToThis){
    char * finalPath = (char *)malloc(PATH_MAX_LEN);
    memset(finalPath, '\0', PATH_MAX_LEN);

    char * argCopy = CharMalloc(strlen(changeToThis) + 5);   
    strcpy(argCopy, changeToThis);

    strcpy(finalPath, FULL_PATH);
    strcat(finalPath, "\\");

    //Seperate paremeters
    char delim [2] = ".";
    char * curCatLine;
    curCatLine = strtok(argCopy, delim);
    if(curCatLine == NULL){
        chdir(finalPath);
        return;
    }

    strcat(finalPath, curCatLine);
    strcat(finalPath, "\\");

    //Continue untill end
    while(curCatLine != NULL){
        curCatLine = strtok(NULL, delim); 
        if(curCatLine == NULL)
            break;

        strcat(finalPath, curCatLine);
        strcat(finalPath, "\\");
    }

    chdir(finalPath);
    free(finalPath);
    free(argCopy);

    return;
}

bool GetNeededPaths(void){

    //We asume that this is only run at start
    GetCurPath(STARTING_PATH);

    //Getting LOCAL_PATH and FULL_PATH
    switch(OS_NAME[0]){
        case 'L':
            break;

        case 'W':
            break;

        case 'A':
            break;
    }

    return true;
}

/*
bool GetNeededPaths(void){

    bool appdata_done = true;

    //get the directory the program has been iniciated on
    getcwd(STARTING_PATH, MAX_PATH);                

    char * temp = (char *)malloc(MAX_PATH);
    memset(temp, '\0', sizeof(temp));
    strcpy(temp, STARTING_PATH);
    strcat(temp, "//NEEDED");
    //Fucking this name up for some reason

    memset(LOCAL_PATH, '\0', sizeof(LOCAL_PATH));

    //Register LOCAL appdata path
    const char *md = "LOCALAPPDATA";
    char *localappdata = getenv(md);
    strcpy(LOCAL_PATH, localappdata);

    //Move to local appdata and rename it to living delusion
    if(ExistDiret(temp)){
        system("move NEEDED %LOCALAPPDATA%");
        strcpy(temp, localappdata);
        strcat(temp, "\\NEEDED");

        char * temp1 = (char *)malloc(MAX_PATH);
        strcpy(temp1, localappdata);
        strcat(temp1, "\\LIVING_DELUSION");
        rename(temp, temp1);
        strcpy(LOCAL_PATH, temp1);
        free(temp1);
        appdata_done = false;

    } else {
        strcat(LOCAL_PATH, "\\LIVING_DELUSION");

        if(!ExistDiret(LOCAL_PATH)){
            //Error msg (crash)
            CLR;
            red;
            MidScreenText("LOCAL APPDATA HAS BEEN MODIFED");
            CenterText("PLEASE CHECK %LOCALAPPDATA% FOR ANY MODIFIED DIRECTORIES RELATED TO LIVING DELUSION");
            CenterText("PRESS ANYTHING TO CRASH GAME");
            getch();
            white;
            exit(1);
        }
    }

    free(temp);

    bool there_is_dir = true;
    memset(FULL_PATH, '\0', sizeof(FULL_PATH));

    GetAppResources("Path (if exists)");

    //Check if theres a custom path made
    if(access("path.txt", F_OK)== 0){
        //Make assist var
        char final_dir [MAX_PATH];
        memset(final_dir, '\0', sizeof(final_dir));

        //Get the (valid) dir inside the file
        FILE * fdir = fopen("path.txt", "r");
        fgets(final_dir, MAX_PATH, fdir);
        fclose(fdir);

        bool valid_dir = true;

        //Cheking if its under or over allowed ASCII value
        for(int i = 0; i < sizeof(final_dir); i ++){
            int checking_char = final_dir[i];

            //Switch to default save if yes
            if(checking_char > 127 || checking_char < 0){
                const char *md = "APPDATA";
                char *appdata = getenv(md);

                strcpy(FULL_PATH, appdata);
                chdir(FULL_PATH);

                //Error msg (non computable dir)
                CLR;
                red;
                printf("Your path.txt folder has an invalid directory on it (OVER ASCII LIMIT), please change it in the settings\n");
                printf("Check your local directory: %s\\Resources\\Path (if it exists)\n", LOCAL_PATH);
                printf("In the mean time the save file will be in your %%APPDATA%% folder, (%s)\n", FULL_PATH);
                SmallStop;
                white;

                valid_dir = false;
                break;
            } 
        }

        //Check if dosent dir exist
        if(valid_dir && ExistDiret(final_dir)== 0){
            //Swich back to default save if yes
            const char *md = "APPDATA";
            char *appdata = getenv(md);

            strcpy(FULL_PATH, appdata);
            chdir(FULL_PATH);

            //Error msg (non existant dir)
            CLR;
            red;
            printf("Your path.txt folder has an invalid directory on it (NON EXISTANT), please change it in the settings\n");
            printf("Check your starting directory: %s\\Resources\\Path (if it exists)\n", LOCAL_PATH);
            printf("In the mean time the save file will be in your %%APPDATA%% folder, (%s)\n", FULL_PATH);
            SmallStop;
            white;

            valid_dir = false;
        }

        //Directory is actually right
        if(valid_dir){
            //Change the dir!
            chdir(final_dir);

            //Also modify "FULL_PATH" for saving the other stuff
            strcpy(FULL_PATH, final_dir);
        }

        //If theres no custom save, go to appdata instead
    } else {
        //Default save lul
        const char *md = "APPDATA";
        char *appdata = getenv(md);

        strcpy(FULL_PATH, appdata);
        chdir(FULL_PATH);
    }

    //Check if dir exists and switch to it
    char check_dir [MAX_PATH];
    strcpy(check_dir, FULL_PATH);
    strcat(check_dir, "\\LIVING_DELUSION");

    chdir(FULL_PATH);

    //Mk new dir
    if(!ExistDiret(check_dir)){

        there_is_dir = false;
        strcat(FULL_PATH, "\\LIVING_DELUSION");
        mkdir("LIVING_DELUSION");
        chdir(FULL_PATH);

        //Boop, extra stuff saved bettewn acts
        mkdir(".out");
        chdir(".out");

        //Register save and act
        FILE * fsave = fopen(".save.txt", "w");
        fprintf(fsave, "%s\n", current_save);
        fprintf(fsave, "1\n");
        fclose(fsave);

        //Used ltr down the line
        FILE * fmore = fopen(".more.txt", "w");
        fprintf(fmore, "0:0:0:0\n");
        fclose(fmore);

        //Warning :>
        FILE * fwarn = fopen(".warning.txt", "w");
        fputs("BE CAREFULL WHEN MODIFING SAVE FILES\n", fwarn);
        fputs("THESE FILES ARE VERY SENSITIVE AND CAN LEAD TO EXTREME GAME CHANGES\n", fwarn);
        fputs("ONLY MODIFY THIS IF YOU READ THE SOURCE CODE (or if you want to break all of your saves)\n", fwarn);
        fclose(fwarn);

    } else
        strcat(FULL_PATH, "\\LIVING_DELUSION");

    chdir(FULL_PATH);

    if(DEBUG_MODE){
        CLR;
        printf("[DEBUG] _> REGISTERED PATHS:\n\n");
        printf("[DEBUG] _> STARTER:\t %s\n", STARTING_PATH);
        printf("[DEBUG] _> LOCAL:\t %s\n", LOCAL_PATH);
        printf("[DEBUG] _> ROAMING:\t %s\n\n", FULL_PATH);
        SmallStop;
    }

    if(!there_is_dir && !appdata_done)
        return false;

    return true;
}
*/
