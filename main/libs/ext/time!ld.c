#include "../ext!ld.h"

u8 TimeCalc(const char *MODE, const i64 timer, const i32 hour, const i64 day){

    i32 bckpTimer = 0, h = 10;
    i64 t = 0, d = 0;

    //Change directory to "TIME"
    ChangeCurPath("TIME");

    //Get vars from file
    if(access("Time.txt", F_OK)== 0){
        FILE * ftime = fopen("Time.txt", "r");
        fscanf(ftime, "%lld", &t);
        fscanf(ftime, "%d", &h);
        fscanf(ftime, "%lld", &d);
        fclose(ftime);
    }

    if(strcmp(MODE, "CHECK")== 0){

        chdir("..");

        //Check what you want to know
        if(timer > 0)
            return t;

        else if(hour > 0)
            return h;

        else if(day > 0)
            return d;

    } else if(strcmp(MODE, "CALC")== 0 || strcmp(MODE, "CALC_EXT")== 0){

        char curloc[10] = { '\0' };

        ChangeCurPath("STORY.Locations");
        FILE * fcurloc = fopen("Current.txt", "r");
        fscanf(fcurloc, "%s", curloc);
        fclose(fcurloc);

        //Check if there is a chance to change cur weather
        if(strcmp(curloc, "NOT")!= 0){
            int bckp_h = h;
            h += hour;
            h -= bckp_h;

            int bckp_d = d;
            d += day;

            //Change weather
            if(h > 3 || d > bckp_d){
                TimeUpdate(h, d);
            }

            d = bckp_d;
            h = bckp_h;

            //Add it twice if its on pit (double time in pit)
            h += hour;
            t += timer;
            d += day;
        }

        //Add the new arguments to the old ones
        h += hour;
        t += timer;
        d += day;

        //Checks the calculations need to be made for both positive and negative values
        if(t >= 30){

            //Calculates POSITIVE day
            if(t >= 720){
                while(t >= 720){
                    d ++;
                    t -= 720;
                }
            }

            //Calculates POSITIVE hour
            if(t >= 30){
                while(t >= 30){
                    h ++;
                    t -= 30;
                }
            } 

        } else if(t <= -30){

            //Calculates NEGATIVE day
            if(t <= -720){
                while(t <= -720){
                    d --;
                    t += 720;
                }
            }

            //Calculates NEGATIVE hour
            if(t <= -30){
                while(t <= -30){
                    h --;
                    t += 30;    
                }
            }

        }

        bckpTimer = t;

        //Timer gets reset
        t = 0;
        t = bckpTimer;

        //Calculates the remaning hours after 24 hours pass [positive]
        if(h >= 24){
            while(h >= 24){
                d ++;
                h = 24 - h;
                h = abs(h);
            }
        }

    }

    ChangeCurPath("TIME");
    if(strcmp(MODE, "CALC_EXT")== 0){
        printf("EXTRAS ONLY, AFTER CALC?\n");

        printf("Timer? %lld\n", t);
        printf("Hour? %d\n", h);
        printf("Day? %lld\n", d);
    }

    //Save the time data on the file
    FILE * ftime = fopen("Time.txt", "w");
    fprintf(ftime, "%lld\n", t);
    fprintf(ftime, "%d\n", h);
    fprintf(ftime, "%lld\n", d);
    fclose(ftime);

    chdir("..");
    return 0;   //default exit (no err.)
}

void TimeUpdate(i32 h, i64 d){

    //Set Vars.
    char curWeather [10];

    ChangeCurPath("STORY");

    switch(rand()% 10 + 1){
        case 1 ... 4:
            strcpy(curWeather, "Rain");
            break;

        case 5:
            strcpy(curWeather, "Thunder");
            break;
            
        default:
            strcpy(curWeather, "Clear");
            break;
    }

    //Save Current Weather and Weather day in the weather file
    ChangeCurPath("STORY");
    FILE * fWeather = fopen("Weather.txt", "w");
    fprintf(fWeather, "%s\n", curWeather);
    fclose(fWeather);

    if(DEBUG_MODE){
        printf("[DEBUG] _> Current Weather? \"%s\"\n", curWeather);
        sleep(3);
        CLR;
    }

    //Checking for achemist potions
    ChangeCurPath("OTHER.activepots");

    i32 potHour = 0;
    i64 potDay = 0;
    char potName [25] = { '\0' };
    bool expired = false;

    //Cycling through all files that contain alchemist pots
    for(int i = 0; i < 10; i ++){

        expired = false;
        char fileName [6] = { '\0' };
        itoa(i, fileName, 10);
        strcat(fileName, ".txt");

        //Update all files that include active pots
        if(access(fileName, F_OK)== 0){

            FILE * fChangePotsActive = fopen(fileName, "r");
            fscanf(fChangePotsActive, "%d\n", &potHour);
            fscanf(fChangePotsActive, "%lld\n", &potDay);
            fgets(potName, 25, fChangePotsActive);
            fclose(fChangePotsActive);

            if(h >= potHour){
                if(d >= potDay)
                    expired = true; 
            }

            else if(d > potDay)
                expired = true;

            if(expired){
                remove(fileName);
                potName[strlen(potName) - 1] =  '\0';
                printf("Your \"%s\" expired!\n", potName);
                sleep(3);
                CLR;
            }
        }
    }


    return;
}
