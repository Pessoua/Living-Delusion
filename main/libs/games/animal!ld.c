#include "../../LivingDelusion.h"

u8 Animal(bool is_tut){
    
    //Note to reader: This is a backup of the "game_set" global setting, used for the display and movements in minigames table types, 
    //makes you able to alter your gameset to whatever you want without actually altering it
    char tut_game_set [5];
    strcpy(tut_game_set, game_set);

    bool changed_game_set = true, do_key3 = false;

    short int i_table_pos_[26];
    short int i_table_pos_50;
    char c_table_pos_[26] [10];
    char c_table_pos_50 [10];

    bool animal_action = false, animal_lead = false, animal_move = false, lure_placed = false, lure_interest = false, remove_lure = false;
    bool Leave = false, Animal_lead = false, Ended = false, tradded_dimentions = false, is_pit = false, is_beehive = false;

    short int animal_pos = rand()% 25 + 1, next_animal_move;
    u8 animal_got = 0;

    coords player;
    player.x = 0;
    player.y = 0;

    if(DEBUG_MODE)
        printf("[DEBUG] _> Starting animal pos? %d\n", animal_pos);

    short int X, Y, AX, AY, SX, SY, L, user_pos, seed_pos = 0, stored_move, limit_moves_taken, moves_taken = 0, times_ran_away = 0, ran_away_limit, bckp_user_pos = 13;
    short int next_move, needed_updates, got_updates = 0, seeds_needed, seeds_got = 0, lead_chance, patience = 0, patience_limit = -1, patience_limit_reached = 0, path = 0;

    //Tutorial Skipping stuff :>
    if(is_tut){
        if(display_all_tut_once){
            ChangeCurPath("OTHER.tutorials");
            if(access("Animal.txt", F_OK)== 0)
                return 0;
        }
        if(skip_tut_display)
            return 0;
    }

    //Check for key 3 stuff
    ChangeCurPath("OTHER.triggers.story");
    if(access("key3.txt", F_OK)== 0){
        char hint_loc [50] = { '\0' }, hint_minigame [50] = { '\0' };
        ChangeCurPath("STORY.Key3");
        FILE * fcurinfo = fopen("Cur.HintInfo.txt", "r");
        fscanf(fcurinfo, "%s\n", hint_minigame);
        fscanf(fcurinfo, "%s\n", hint_loc);
        fclose(fcurinfo);

        //Check if its right mini-game
        if(strcmp(hint_minigame, "Animal")== 0){
            ChangeCurPath("STORY.Locations");
            char cur_loc [50] = { '\0' };

            FILE * fcurloc = fopen("Current.txt", "r");
            fscanf(fcurloc, "%s\n", cur_loc);
            fclose(fcurloc);

            //Check if its right location
            if(strcmp(cur_loc, hint_loc)== 0)
                do_key3 = true;
        }
    }

    char * curloc = (char *)malloc(10);

    //Check for locations   
    ChangeCurPath("STORY.Locations");
    FILE * fcurloc = fopen("Current.txt", "r");
    fscanf(fcurloc, "%s", curloc);
    fclose(fcurloc);

    if(strcmp(curloc, "NOT")!= 0){
        is_pit = true;
        if(strcmp(curloc, "Blossom")== 0){
            is_beehive = true;
        } 
    } 

    free(curloc);

    //Set up limits for seed or lead depending on where user is
    if(strcmp(dificulty, "Lucid")== 0){

        needed_updates = 5;
        seeds_needed = 1;
        patience_limit = 7;
        lead_chance = 1;
        limit_moves_taken = 12;
        ran_away_limit = 3;

    } else if(strcmp(dificulty, "False")== 0){

        needed_updates = 10;
        seeds_needed = 2;
        patience_limit = 5;
        lead_chance = 2;
        limit_moves_taken = 10;
        ran_away_limit = 2;

    } else if(strcmp(dificulty, "Vivid")== 0){

        needed_updates = 15;
        seeds_needed = 2;
        patience_limit = 3;
        lead_chance = 3; 
        limit_moves_taken = 7; 
        ran_away_limit = 2;

    } else {

        needed_updates = 20;
        seeds_needed = 3;
        patience_limit = 1;
        lead_chance = 4; 
        limit_moves_taken = 5; 
        ran_away_limit = 1; 

    }

    printf("Starting Grid:\n");

    if(animal_pos == 13){
        while(true){

            if(DEBUG_MODE){
                printf("[DEBUG] _> Animal is in the same position has user in starting spawn!!! (Very bad!!!)\n");
                sleep(1);
                CLR;
            }

            animal_pos = rand()% 25 + 1;

            if(animal_pos != 13)
                break;
        }
    }

    //Shows starting table
    if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
        printf("[0] [0] [0] [0] [0]\n");
        printf("[0] [0] [1] [0] [0]\n");
        printf("[0] [2] [9] [3] [0]\n");
        printf("[0] [0] [4] [0] [0]\n");
        printf("[0] [0] [0] [0] [0]\n");
        printf("        [7]\n");
    } else {
        printf("[NONE] [NONE] [NONE] [NONE] [NONE]\n");
        printf("[NONE] [NONE] [UP] [NONE] [NONE]\n");
        printf("[NONE] [LEFT] [YOU] [RIGHT] [NONE]\n");
        printf("[NONE] [NONE] [DOWN] [NONE] [NONE]\n");
        printf("[NONE] [NONE] [NONE] [NONE] [NONE]\n");

        //Show STABLE or BOX depending if its pit or not
        if(!is_pit)
            printf("             [STABLE]\n");

        else
            printf("              [BOX]\n");
    }

    X = 3, Y = 3;

    while(true){    
        if(changed_game_set && is_tut){
            changed_game_set = false;

            if((strcmp(tut_game_set, "Int")== 0 && is_tut)){
                printf("Listen up, this is important\n");
                printf("Type 1 to go Up a Square, 2 to go left, 3 to go right and 4 to go down\n");
                printf("Type 9 to leave WITHOUT collecting animals and 0 to stay in the same spot\n");
                printf("Type 8 to switch \"game_set\" types, aka if you are playing with \"INT\" it switches to \"CHAR\" and vice versa (tutorial only command)\n");
                printf("Now, this gametype works diferently depending if you are in Village or Pit, now i will show how you beat the game in BOTH ways\n\n");

                printf("IF you ARE in VILLAGE, type 5 to try to put a lead on the animal, only works if you are close enough\n");
                printf("To win, you need to enter the stable WHILE you have the animal on a lead, (Appears has \"7\" in the map)\n\n");

                printf("IF you ARE in PIT, type 5 to put a \"Lure\" on the spot you are standing on\n");
                printf("Also type 6 to remove the lure while you are on top of it\n");
                printf("To win, you need to make the animal walk a lot and feed him a lot of lures\n\n");

                printf("Also also, you can switch bettewn VILLAGE and PIT by typing 7 (tutorial only command)\n");
                printf("Understood? You better...\n\n");
            } else {
                printf("Listen up, this is important\n");
                printf("Type \"Up\" to go Up a Square, \"Left\" to go left, \"Right\" to go right and \"Down\" to go down\n");
                printf("Type \"Leave\" or \"Back\" to leave WITHOUT collecting animals and \"stay\" to stay in the same spot\n");
                printf("Type \"Game\" to switch \"game_set\" types, aka if you are playing with \"INT\" it switches to \"CHAR\" and vice versa (tutorial only command)\n");
                printf("Now, this gametype works diferently depending if you are in Village or Pit, now i will show how you beat the game in BOTH ways\n\n");

                printf("IF you ARE in VILLAGE, type \"Lead\" to try to put a lead on the animal, only works if you are close enough\n");
                printf("To win, you need to enter the stable WHILE you have the animal on a lead, (Appears has \"STABBLE\" in the map)\n\n");

                printf("IF you ARE in PIT, type \"Lure\" to put a \"Lure\" on the spot you are standing on\n");
                printf("Also type \"Remove\" to remove the lure while you are on top of it\n");
                printf("To win, you need to make the animal walk a lot and feed him a lot of lures\n\n");

                printf("Also also, you can switch bettewn VILLAGE and PIT by typing \"Switch\" (tutorial only command)\n");
                printf("Understood? You better...\n\n");
            }

            SmallStop;       
        }

        printf("Next move?\n");

        if((strcmp(game_set, "Char")== 0 && !is_tut) || (strcmp(tut_game_set, "Char")== 0 && is_tut)){

            StrInp(); 

            //Happends cause lead is for animal barn thing and lure is for wild animals in the montain
            //and the whole trust system thing

            //Movements
            if(strcmp(Input, "up")== 0){
                Y -= 1; stored_move = 1; }

            else if(strcmp(Input, "left")== 0){
                X -= 1; stored_move = 2; }

            else if(strcmp(Input, "right")== 0){
                X += 1; stored_move = 3; }

            else if(strcmp(Input, "down")== 0){
                Y += 1; stored_move = 4; }

            else if(strcmp(Input, "lead")== 0 || strcmp(Input, "lure")== 0 || strcmp(Input, "remove")== 0){
                bool inv_animal_action = false; //Just for fun

                if(strcmp(Input, "lead")== 0){
                    if(!is_pit)
                        animal_action = true;

                    else
                        inv_animal_action = true;

                } else if(strcmp(Input, "lure")== 0){
                    if(is_pit)
                        animal_action = true;

                    else
                        inv_animal_action = true;

                } else {
                    if(is_pit)
                        remove_lure = true;

                    else
                        inv_animal_action = true;

                }

                if(inv_animal_action){
                    red;
                    CLR;
                    printf("Wrong place\n");
                    sleep(1);
                    CLR;
                    white;
                }
            }

            else if(strcmp(Input, "stay")== 0){ }

            else if(strcmp(Input, "switch")== 0 && is_tut){
                if(!is_pit)
                    is_pit = true;

                else
                    is_pit = false;

                tradded_dimentions = true;

                got_updates = 0;
                seeds_got = 0; 
                patience = 0; 
                times_ran_away = 0; 
                moves_taken = 0;
                path = 0;

                green;
                if(is_pit)
                    printf("Changed to Pit!\n");

                else
                    printf("Changed to Not Pit!\n");
                white;

            } else if(strcmp(Input, "game")== 0 && is_tut){
                changed_game_set = true;

                if((strcmp(tut_game_set, "Int")== 0 && is_tut))
                    strcpy(tut_game_set, "Char");

                else
                    strcpy(tut_game_set, "Int");

                green;
                printf("Changed game type!\n");
                white;

            } else if(strcmp(Input, "leave")== 0 || strcmp(Input, "back")== 0){

                Leave = true; break;

            } else { Error; }

        } else {

            //Also using "string_Input" cause if the user mistaked it for a char input it would bug out but with this nothing happends so the user is safe
            StrInp();

            //Int movements
            if(strcmp(Input, "1")== 0){
                Y -= 1; stored_move = 1; }

            else if(strcmp(Input, "2")== 0){
                X -= 1; stored_move = 2; }

            else if(strcmp(Input, "3")== 0){
                X += 1; stored_move = 3; }

            else if(strcmp(Input, "4")== 0){
                Y += 1; stored_move = 4; }

            else if(strcmp(Input, "5")== 0)
                animal_action = true;

            else if(strcmp(Input, "6")== 0){
                if(is_pit)
                    remove_lure = true;

                else {
                    red;
                    CLR;
                    printf("Wrong place\n");
                    sleep(1);
                    CLR;
                    white;
                }
            }

            else if(strcmp(Input, "0")== 0){ }

            else if(strcmp(Input, "7")== 0 && is_tut){
                if(!is_pit)
                    is_pit = true;

                else
                    is_pit = false;

                got_updates = 0;
                seeds_got = 0; 
                patience = 0; 
                times_ran_away = 0; 
                moves_taken = 0;
                path = 0;

                green;
                if(is_pit)
                    printf("Changed to Pit!\n");

                else
                    printf("Changed to Not Pit!\n");
                white;

            } else if(strcmp(Input, "8")== 0 && is_tut){
                changed_game_set = true;

                if((strcmp(tut_game_set, "Int")== 0 && is_tut))
                    strcpy(tut_game_set, "Char");

                else
                    strcpy(tut_game_set, "Int");

                green;
                printf("Changed game type!\n");
                white;

            } else if(strcmp(Input, "9")== 0){

                Leave = true; break;

            } else { Error; }

        } 

        while(true){
            //Check if user tries to go out of bounds 
            if (X >= 6){ printf("Outside playing field\n"); sleep(1); X = 5; CLR; }
            else if (X <= 0){ printf("Outside playing field\n"); sleep(1); X = 1; CLR; }
            else if (Y <= 0){ printf("Outside playing field\n"); sleep(1); Y = 1; CLR; }
            else if (Y >= 7){ printf("Outside playing field\n"); sleep(1); user_pos = 28; Y = 6; CLR; }

            //Calculate L with this simple formula
            L = (Y * 5) - 5;

            //Calculating table position
            user_pos = X + L;

            //Check if user is trying to move out of bounds when he isnt inside of stable AND when he is
            if(user_pos == 26 || user_pos == 27 || user_pos == 29 || user_pos == 30){
                printf("Outside playing field\n"); sleep(1);

                if(bckp_user_pos == 28){
                    Y = 6; X = 3; 
                }

                else
                    Y = 5;

                CLR;
            }

            //Calculate L with this simple formula
            L = (Y * 5) - 5;

            user_pos = X + L;
            bckp_user_pos = user_pos;

            //If user tries to go inside animal in the next position just revert him back to previous pos
            if(user_pos == animal_pos){
                if(stored_move == 1)
                    Y += 1;
                else if(stored_move == 2)
                    X += 1;
                else if(stored_move == 3)
                    X -= 1;
                else 
                    Y -= 1;

            } else 
                break;


        } //End of loop checking and repositioning user to proper location if they try to go somewhere they shouldnt be

        if(DEBUG_MODE)
            printf("[DEBUG] _> User X? %d / Y? %d / L? %d / Pos? %d / Bckp Pos? %d\n", X, Y, L, user_pos, bckp_user_pos);

        if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){

            //Reseting all positions to nothing to be modified has playing field
            memset(i_table_pos_, 0, sizeof(i_table_pos_));
            i_table_pos_50 = 7;

            //Displays the user and animal position
            if(user_pos == 28)
                i_table_pos_50 = 9;

            else
                i_table_pos_[user_pos] = 9;

            i_table_pos_[animal_pos] = 8;
            i_table_pos_[seed_pos] = 6;

        } else {

            //Reseting all positions to nothing to be modified has playing field
            for(int i = 1; i < 26; i ++)
                strcpy(c_table_pos_[i], "NONE");

            if(!is_pit)
                strcpy(c_table_pos_50, "STABLE");

            else
                strcpy(c_table_pos_50, "BOX");

            //Displays the user position 
            if(user_pos == 28)
                strcpy(c_table_pos_50, "YOU");

            else
                strcpy(c_table_pos_[user_pos], "YOU");

            strcpy(c_table_pos_[animal_pos], "ANIMAL");
            strcpy(c_table_pos_[seed_pos], "LURE");

        }

        //See if removing seed is possible
        if(remove_lure){
            remove_lure = false;

            if(user_pos == seed_pos){
                printf("You removed the lure!\n");
                seed_pos = 0;
                i_table_pos_[user_pos] = 9;
                path = 0;
                SX = 0; SY = 0;
                lure_placed = false;
                lure_interest = false;
            } else {
                red;
                printf("You cannot remove the seed / lure since you are not standing on top of it.\n");
                white;
            }

        }

        //Place seed down / put the lead on the animal
        if(animal_action){
            animal_action = false;

            //Lead mechanics
            if(!is_pit){
                path = 0;

                //I think its clear what this does
                short int distance_from_user_to_animal = animal_pos - user_pos;
                distance_from_user_to_animal = abs(distance_from_user_to_animal);

                if(distance_from_user_to_animal == 1 || distance_from_user_to_animal == 5){

                    //Randomize chance
                    short int animal_lead_rand = rand()% lead_chance + 1;

                    if(DEBUG_MODE)
                        printf("[DEBUG] _> Animal lead rand? %d\n", animal_lead_rand);

                    if(animal_lead_rand == 1){
                        //Sucess putting the animal on a lead!
                        Animal_lead = true;
                        moves_taken = 0;
                        yellow;
                        printf("You got the animal on lead.\n");
                        white;

                    } else {
                        //Failed putting the animal on a lead
                        red;
                        printf("You couldnt put a lead on the animal.\n");
                        white;

                    }

                } else {
                    red;
                    printf("Too far from animal to put a lead on it.\n");
                    white;
                }

            } else {
                //Seed mechanics
                if(!lure_placed){
                    path = rand()% 3 + 1;
                    seed_pos = user_pos;
                    lure_placed = true;
                    lure_interest = true;
                    SX = X;
                    SY = Y;
                    if(DEBUG_MODE){
                        printf("[DEBUG] _> SX? %d / SY? %d / Seed pos? %d\n", SX, SY, seed_pos);
                        printf("[DEBUG] _> Path chosen? %d\n", path);
                    }

                } else {
                    red;
                    printf("You cannot place annother seed down.\n");
                    white;

                }
            }

        }

        //Lead movement following user
        if(Animal_lead && !is_pit){

            if(moves_taken > limit_moves_taken){
                //Too much walking
                animal_move = false;
                Animal_lead = false;
                red;
                printf("The animal escaped the lead!\n");
                white;
                moves_taken = 0;
                times_ran_away ++;

            } else {

                //Animal follows user
                next_animal_move = stored_move;
                animal_move = true;
                moves_taken ++;
            }

            if(DEBUG_MODE){
                printf("[DEBUG] _> Moves taken? %d\n", moves_taken);
                printf("[DEBUG] _> Times ran away? %d\n", times_ran_away);
            }
        }

        //Ai for if seed is placed down or not and pathfind to it
        if(lure_interest){
            short int distance_diference;

            if(DEBUG_MODE)
                printf("[DEBUG] _> Distance Diference? %d\n", distance_diference);

            //Coordenate AY with SY and then coordenate AX with SX
            if(path == 1){

                //Coordante AY
                distance_diference = SY - AY;

                if(distance_diference > 0){
                    next_animal_move = 4;
                    got_updates ++;
                } else if(distance_diference < 0){
                    next_animal_move = 1;
                    got_updates ++;
                }

                //If AY is coordenated, X is coordenated next
                else {
                    distance_diference = SX - AX;

                    if(distance_diference > 0){
                        next_animal_move = 3; 
                        got_updates ++;
                    } else if(distance_diference < 0){
                        next_animal_move = 2;
                        got_updates ++;
                    }   
                }

                //Coordenate AX with SX and then coordenate AY with SY  
            } else if(path == 2){

                //Coordante AX
                distance_diference = SX - AX;

                if(distance_diference > 0){
                    next_animal_move = 3; 
                    got_updates ++;
                } else if(distance_diference < 0){
                    next_animal_move = 2;
                    got_updates ++;
                }

                //If AX is coordenated, Y is coordenated next
                else {
                    distance_diference = SY - AY;

                    if(distance_diference > 0){
                        next_animal_move = 4;
                        got_updates ++;
                    } else if(distance_diference < 0){
                        next_animal_move = 1;
                        got_updates ++;
                    }

                }

                //Ladder style coordenation, Y then X and then again until seed is reached  
            } else { //Path 3

                //Update Y
                if(got_updates % 2 == 0){

                    distance_diference = SX - AX;

                    if(distance_diference > 0){
                        next_animal_move = 3; 
                        got_updates ++;
                    } else if(distance_diference < 0){
                        next_animal_move = 2;
                        got_updates ++;
                    } else {

                        //If AX and SX are the same, just update Y
                        distance_diference = SY - AY;

                        if(distance_diference > 0){
                            next_animal_move = 4;
                            got_updates ++;
                        } else if(distance_diference < 0){
                            next_animal_move = 1;
                            got_updates ++;
                        }

                    }

                } 

                //Update X
                else if(got_updates % 2 != 0){
                    distance_diference = SY - AY;

                    if(distance_diference > 0){
                        next_animal_move = 4;
                        got_updates ++;
                    } else if(distance_diference < 0){
                        next_animal_move = 1;
                        got_updates ++;
                    } else {

                        //If AY and SY are the same, just update X
                        distance_diference = SX - AX;

                        if(distance_diference > 0){
                            next_animal_move = 3; 
                            got_updates ++;
                        } else if(distance_diference < 0){
                            next_animal_move = 2;
                            got_updates ++;
                        }

                    }

                }

            }

            if(animal_pos == seed_pos){

                //Checks if animal ACTUALLY wants the lure
                if(lure_interest){
                    //Update stats
                    seeds_got ++;
                    next_animal_move = 0;
                    seed_pos = 0;
                    path = 0;
                    SX = 0; SY = 0;
                    lure_placed = false;
                    lure_interest = false;
                    animal_move = false;

                    if(DEBUG_MODE)
                        printf("[DEBUG] _> Seeds got? %d / Got updates? %d\n", seeds_got, got_updates);

                    //Update map
                    if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut))
                        i_table_pos_[animal_pos] = 8;

                    else
                        strcpy(c_table_pos_[animal_pos], "ANIMAL");

                } else {
                    //Nothin happends
                }

            }

            animal_move = true;

            if(DEBUG_MODE)
                printf("[DEBUG] _> Next animal move? %d\n", next_animal_move);

        }

        //Idle movement if no path is being taken
        //And if its not on a lead
        if(path == 0 && !Animal_lead){

            //bettewn 0 and 4
            next_animal_move = rand()% 5 + 0;
            if(DEBUG_MODE)
                printf("[DEBUG] _> Next animal move chosen? %d\n", next_animal_move);

            animal_move = true;         
        }

        //is next move valid or not? also updates the new vars
        if(animal_move){
            short int bckp_animal_pos = animal_pos;
            bool valid_animal_position = false, inside_user_pos = false, out_of_bounds_pos = false;

            //Convert into smaller values
            if(bckp_animal_pos <= 5){
                AY = 1; AX = bckp_animal_pos;
            } else if(bckp_animal_pos <= 10){
                AY = 2; AX = bckp_animal_pos - 5;
            } else if(bckp_animal_pos <= 15){
                AY = 3; AX = bckp_animal_pos - 10;
            } else if(bckp_animal_pos <= 20){
                AY = 4; AX = bckp_animal_pos - 15;
            } else {
                AY = 5; AX = bckp_animal_pos - 20;
            }

            //Test position
            if(next_animal_move == 0)
                bckp_animal_pos += 0;

            else if(next_animal_move == 1){
                AY -= 1;  

                if(Animal_lead)
                    //Lead iniciated 
                    bckp_animal_pos = user_pos + 5;

                else
                    //Pathfinding iniciated
                    bckp_animal_pos -= 5; 
            }

            else if(next_animal_move == 2){ 
                AX -= 1; 

                if(Animal_lead)
                    bckp_animal_pos = user_pos + 1;

                else
                    bckp_animal_pos -= 1; 
            }

            else if(next_animal_move == 3){ 
                AX += 1; 

                if(Animal_lead)
                    bckp_animal_pos = user_pos - 1;

                else
                    bckp_animal_pos += 1;  
            }

            else if(next_animal_move == 4){ 
                AY += 1;

                if(Animal_lead)
                    bckp_animal_pos = user_pos - 5;

                else
                    bckp_animal_pos += 5;
            }

            //Special charecter stored?
            else 
                bckp_animal_pos += 0;

            //if future animal position is INSIDE user, say no
            if(bckp_animal_pos == user_pos){
                //Animal cant lose patience if its in idle mode
                if(path != 0)
                    patience += 1;

                inside_user_pos = true;

                if(DEBUG_MODE)
                    printf("[DEBUG] _> Patience value? %d\n", patience);
            }

            //Same tests has user to make sure animal does not teleport through walls
            if (AX >= 6){ out_of_bounds_pos = true;  AX = 5; }
            else if (AY >= 6){ out_of_bounds_pos = true; AY = 5; }
            else if (AX <= 0){ out_of_bounds_pos = true; AX = 1; }
            else if (AY <= 0){ out_of_bounds_pos = true; AY = 1; }
            else
                out_of_bounds_pos = false;

            if(!out_of_bounds_pos && !inside_user_pos)
                valid_animal_position = true;

            if(DEBUG_MODE){
                printf("[DEBUG] _> Valid animal position value? %d [Boolean value]\n", valid_animal_position);
                printf("[DEBUG] _> AX? %d / AY? %d / Animal Pos? %d\n", AX, AY, animal_pos);
            }

            //If all tests pass
            if(valid_animal_position)
                animal_pos = bckp_animal_pos; 

            //Reset animal and user pos
            if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
                memset(i_table_pos_, 0, sizeof(i_table_pos_));
                i_table_pos_50 = 7;

                if(user_pos == 28)
                    i_table_pos_50 = 9;

                else
                    i_table_pos_[user_pos] = 9;

                i_table_pos_[seed_pos] = 6;
                i_table_pos_[animal_pos] = 8;

            } else {
                for(int i = 1; i < 26; i ++)
                    strcpy(c_table_pos_[i], "NONE");

                if(!is_pit)
                    strcpy(c_table_pos_50, "STABLE");

                else
                    strcpy(c_table_pos_50, "BOX");

                if(user_pos == 28)
                    strcpy(c_table_pos_50, "YOU");

                else
                    strcpy(c_table_pos_[user_pos], "YOU");

                strcpy(c_table_pos_[seed_pos], "LURE");
                strcpy(c_table_pos_[animal_pos], "ANIMAL");
            }

        }

        //Animal lost patience and went away
        if(patience_limit_reached == 3 || times_ran_away == ran_away_limit){
            red;
            if(!is_pit)
                printf("The animal decided to run away!\n");

            else
                printf("The animal lost patience and went away!\n");
            white;

            Leave = true; break;
        }

        //When animal patience runs out he loses interest in the seed / lure
        if(patience == patience_limit){
            red;
            printf("The animal lost interest in the lure!\n");
            white;

            lure_interest = false;
            animal_move = false;
            patience_limit_reached ++;
            patience = 0;
            path = 0;

            if(DEBUG_MODE)
                printf("[DEBUG] _> Patience limit reached? %d\n", patience_limit_reached);

        }

        //Objective complete on village side
        //This is VIllage side ending
        if(user_pos == 28 && Animal_lead){
            if(is_pit)
                printf("[WHY ARE YOU HERE] _> How the fuck?\n");

            yellow;
            printf("You put the animal back in the stable!\n");
            white;

            Ended = true;
        }

        //Objective complete on pit side
        //This is pit side ending
        if(seeds_got >= seeds_needed && got_updates >= needed_updates){
            if(!is_pit)
                printf("[WHY ARE YOU HERE] _> How the fuck?\n");

            yellow;
            printf("The animal trust you and you took it with you!\n");
            white;

            Ended = true;
        }

        if(Ended){
            short int choosing_animal = rand()% 10 + 1;

            if(DEBUG_MODE)
                printf("[DEBUG] Choosing Animal? %d\n", choosing_animal);

            if(!is_tut){
                if(choosing_animal >= 1 && choosing_animal <= 7)
                    animal_got = 1;

                else if(choosing_animal >= 8 && choosing_animal <= 9)
                    animal_got = 2;

                else
                    animal_got = 3;

            } else {
                if(choosing_animal >= 1 && choosing_animal <= 7)
                    printf("Got a TUTORIAL_ANIMAL_1 [70%%]!\n");

                else if(choosing_animal >= 8 && choosing_animal <= 9)
                    printf("Got a TUTORIAL_ANIMAL_2 [20%%]!\n");

                else
                    printf("Got a TUTORIAL_ANIMAL_3 [10%%]!\n");

            }

            sleep(2);
            break;
        }

        //Display ending table
        if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
            for(int i = 1; i < 26; i ++){
                printf("[%d] ", i_table_pos_[i]);

                if(i % 5 == 0)
                    printf("\n");

                if(i == 25)
                    printf("        [%d]\n", i_table_pos_50);
            }

        } else {
            for(int i = 1; i < 26; i ++){
                printf("[%s] ", c_table_pos_[i]);

                if(i % 5 == 0)
                    printf("\n");

                if(i == 25){

                    if(!is_pit)
                        printf("             [%s]\n", c_table_pos_50);

                    else
                        printf("              [%s]\n", c_table_pos_50);
                }
            }
        }

    } //Loop end

    if(is_tut){
        //Register tutorial has done
        if(display_all_tut_once){
            ChangeCurPath("OTHER.tutorials");
            FILE * ftutdisp = fopen("Animal.txt", "w");
            fclose(ftutdisp);
        }

        while(true){
            CLR;
            printf("Tutorial done!\n");
            printf("Again? [Y/N]\n");

            StrInp();

            if(strcmp(Input, "y")== 0){
                Animal(true);
                break;
            }   

            else if(strcmp(Input, "n")== 0)
                break;

            else 
                Error;

        }

    } else {
        if(Leave)
            animal_got = 0;

        //TimeCalc("CALC", 0, 1, 0);

        //Key 3 hint stuff
        if(!Leave && do_key3 && rand()% 2 + 1 == 1){
            CLR;
            //Get hint
            ChangeCurPath("STORY.Key3");
            char * hint = (char *)malloc(555);
            system("attrib -h hiddenkey.txt");
            FILE * fhidkey = fopen("hiddenkey.txt", "r");
            fgets(hint, 555, fhidkey);
            fclose(fhidkey);
            system("attrib +h hiddenkey.txt");

            //Prevent the "\n" from showing
            hint[strlen(hint) - 1] = '\0';

            //Display hint
            yellow;
            CenterText("KEY 3 HINT");
            white;
            CenterText(hint);
            CenterText("[HELP] _> Hint has been registered in the book");

            //Register new thing in the fuckin thing and shit
            ChangeCurPath("OTHER.books");
            FILE * key3b = fopen("Key3Book.txt", "w");
            fprintf(key3b, "[HINT] ");
            fprintf(key3b, "%s\n", hint);
            fclose(key3b);

            SmallStop; 
            free(hint);
            CLR;
        }
    }

    return animal_got;
}
