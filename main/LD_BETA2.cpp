#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#include <sys/stat.h> 
#include <errno.h>


/*
Directory Notes:

ChangeCurPath
	Made for ONLY appdata
	Information in appdata is always changing
	
GetAppResources
	Made for ONLY localappdata
	Information / Resources in localappdata never change
*/

//Better way of clearing the screen
#define CLR system("cls");

//if Input is incorect
#define Error CLR; 											\
			  red;										 	\
			  printf("[ERROR] _> Not a valid command.\n\n");\
			  sleep(1); 									\
			  CLR; 											\
			  white;

//If theres too much dialogue
#define Small_stop	printf("[SYSTEM] _> Press anything to continue\n");	\
                    getch(); 											\
                    CLR;

//Better way of getting string input and making it not case sensitive
#define String_Input printf("&/");							\
					 scanf("%s", Input);					\
					 for(int i = 0; i < strlen(Input); i ++)\
					 Input[i] = tolower(Input[i]); 			\
					 CLR;

//Converting STR into INT (%d scanf with strings causes issues) 
#define INT_Protocol printf("&/");								\
					 scanf("%s", Input);						\
					 bool is_valid = true;						\
					 for(int i = 0; i < strlen(Input); i ++){	\
						 if(isalpha(Input[0])!= 0){				\
						 	 is_valid = false;					\
						 	 break;								\
						 }										\
					 }											\
					 if(is_valid)								\
					 INT_Input = atoi(Input);					\
					 else										\
					 INT_Input = 0;

//Colors (SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), [COLOR]))
#define dark_blue 	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
#define green 		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
#define light_blue 	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
#define red 		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
#define purple 		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
#define yellow 		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
#define white 		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
#define gray 		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
#define mid_blue	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
#define light_green	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
#define light_aqua	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
#define light_red	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
#define light_purple SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
#define light_yellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
#define	bright_white SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

//Global Vars. (Remove LTR)
char User_Name [50], Input [25];
long long int INT_Input = 0;
int backup1_skip_cp; int skip_in_vil; char wiz_inp [15] = "\0"; char Inv_call [5];
char User_input [10], user_input1 [10], Df [15], help1[3]; char dificulty [15] = "Nightmare"; int hotel_1_t = 0; int animal_cap_day = -1; char SECRET_BOOK [5] = "NO"; char oracle_inp [10];
int Nightmare_check; int Cp1_puzzle_trigger = 0; char back_bedroom [15] = "NO"; int pot_h = -1; char pod_order [15] = "NO"; char book_1st_time [5] = "YES";
int Inv_books; int alch_knowlege; int X; int Y; int L; char New_Day [15]; int Day_Check = -1; int animal_day = -1; char pt_brewing [15] = "NONE"; char secret_b_again [5] = "NO";
int chest_items = 0; int slots_av = 100; char usr_animal [15] = "\0"; char Animals_Stable [15] = "EMPTY"; int final_p_dev = 0; char l_secret_1st_time [5] = "YES";

//Funcion declarations go here :>
//Locations	
void Teller(void);
void Center(void);
void Garden(void);
void Wizard(void);
void Library(void);
void Hotel(void);
void Mountain(const char * what);							
int Act1();
void Pit(void);

//Mini games and other global locations
int Animal(bool is_tut);
void Crop(const short int Crop1_ID, bool is_tut);
void Fish(const short int Fish1_ID, const char *what_pond, bool is_tut);
void Tree(bool is_invasive, const char *num_spot, const short int Log1_ID, const short int special_tree_ID, bool is_tut);
void Key(const char *Caller);
void SpecialLocations(const char * Caller);

//Format text / Usefull stuff
void ReadTextFile(const char *FileName, const char *specifications);
void ChangeFileLine(const char * file_name, const char * line, int line_to_modify);
bool MakeSaveFiles(const char * what);
bool ExistDiret(const char *path);
void CenterText(const char *line);
void RightText(const char *line);
void RandText(const char *line);
void MidScreenText(const char *line);
void FormatTextEXT(const char * mode, const char * line, bool new_line, int skip_starting_displacement, const char * wantedcolors, bool has_var_port, int only_do_THIS_number_of_lines, int repeat_THIS_many_times);
char * EncryptedWordsV1(short int *num_of_spaces);
char * EncryptedWordsV2(const char * line);
void ChangeCurPath(const char * please_change_to_this_line);
void CatCurPath(const char * cat_this_line);
int DisplayAllSpecialItems(void);
int DisplayCenterList(const char * wat_mer);
HWND WINAPI GetConsoleWindowNT(void);

//Get
bool GetNeededPaths(void);
int GetTimeSpent(void);
int GetTerminalSize(const char * what);
void GetAppResources(const char * please_change_to_this_line);
char * GetItemName(int ID);
int GitItem(void);		//This one is trying its best

//Art Related + scary stuff ish
void SomethingHasGoneWrong(); 
int Art(const char *CALLER, const int Parameter);
void ChangeToThisColor(int INT_color, char CHAR_color);

void Help(); void Credits(); void Settings(); void TipOfTheDay(); int EndOfBeta();
void Game_Start(void); int Dificulty(); int Extras(); 
int TimeCalc(const char *MODE, const long int timer, const int hour, const long int day); 
int StartingScreen(); 
int Inventory(const char *Inv_call, const int ID, const int Quantity);
void Chest(void);

//Global Settings
char game_set [15] = "Int";
bool skip_intro = true, show_user_turn = false; 
bool display_all_tut_once = false, skip_tut_display = false, force_tut_display = true, show_tut_cutscene = false;
bool display_tip = true;
bool div_inv_sect = true, limit_inv = false, arr_limit_inv [6] = { true, true, true, true, true, true };

//Inventory
long int money = 1000000; int chos_itm; char center_leave [5] = "NO"; int itm_quant; int bckp_money;

char sell_again [1], sell_again_t [5] = "YES";
int Overflow_Value = 0, CAN_GO = 1, ALL_INV_ITM_BCKP;
//Achivments stuff
int plant_water; int check_p_day = -1; int LET_IT_GROW = 0;
//Quest trigger
char P1_quest [15] = "NO"; char P2_quest [15] = "NO"; char P3_quest [15] = "NO";
char P1_q_status [15] = "NOTDONE"; char P2_q_status [15] = "NOTDONE"; char P3_q_status [15] = "NOTDONE";
char mint_q [15] = "NO"; int num_quest_active = 0;
//Story line triggers
char Talked_to_pit_wiz [5] = "NO"; char knows_ab_goal [5];
//Crop Stash
int STASH_CROP_ITM[6];
char STASH_CROP [5] = "NO", STASH_CROP_DONE [5] = "NO", STASH_CROP_STATUS [10] = "NOTFULL", stash_crop_choice [10];
//Merchant Stash
int MERCHANT_STASH_QUANTITY, MERCHANT_STASH_ID;
char ALLOW_TRADING [5] = "YES", MERCHANT_STASH_INPUT [15];
//Alchemist Stash
char ALLOW_BREWING [10] = "YES", alch_stash_inp [10];
int ALCH_STASH_ID;
//Animal Stash
char ANIMAL_STASH_INPUT [10], ANIMAL_STASH_STATUS [10] = "NOTFULL";
int ANIMAL_STASH_ID, ANIMAL_STASH_QUANTITY;

//Dir stuff (MAX_PATH is a constant from the windows.h library i think)
char STARTING_PATH [MAX_PATH] = { '\0' }, FULL_PATH [MAX_PATH] = { '\0' }, LOCAL_PATH[MAX_PATH] = { '\0' }, current_save [2];
//Debug mode enable / disable
bool DEBUG_MODE = true;
//Calc time
clock_t time_needed;

void SomethingHasGoneWrong(void){
	CLR;
	red;
	printf("\a");
	printf("SOFTWARE STOPPED WORKING\n");
	printf("LIVING DELUSION ERROR [INVALID_ACCESS_PERMITION]\n");
	printf("ERROR CODE: Tm90IEFsb25l\n\n");
	printf("PRESS ANY KEY TO REBOOT SYSTEM\n");
	getch();
	CLR;
	
	for(int i = 0; i < 15; i ++){
		printf("your machine has been infected :>.\n");
		usleep(20000);
	}

	CLR;
	white;
	
	StartingScreen();
}

//Display tip :>
void TipOfTheDay(void){
	
    yellow;
    
    short int tip = rand() % 10 + 1; 
    
	CLR;
    
	if (tip == 1){ MidScreenText("This is not a tip, its a fact! Living Delusion was started in 9/10/2023 :>"); }
    else if (tip == 2){ MidScreenText("The best way to start a colecting mini game is to stay still in the first input!"); }
    else if (tip == 3){ MidScreenText("Explore the mountain to the fullest!"); }
    else if (tip == 4){ MidScreenText("Gotta get 100%!"); }
    else if (tip == 5){ MidScreenText("Use CTRL + SCROLL WHEEL to zoom in and out!"); }
    else if (tip == 6){ MidScreenText("Every special item is usefull in some way"); }
    else if (tip == 7){ MidScreenText("Start every key when you can!"); }
    else if (tip == 8){ MidScreenText("PLACEHOLDER (8)"); }
    else if (tip == 9){ MidScreenText("PLACEHOLDER (9)"); }
    else { MidScreenText("Report bugs!"); }
    
   	white;
    
}

int main(void){
	
	time_needed = clock();							// start clock
	srand(time(NULL));								// srand(time(NULL)) makes it so all randoms in the program are always randomized even if its executed twice or more times
	setlocale(LC_ALL, "");							// makes it able to put stuff like "á" or "õ"
	system("title LIVING DELUSION [OPEN BETA 2]"); 	// makes the window name has "LIVING DELUSION [OPEN BETA 2]"
	
	if(!GetNeededPaths()){
		printf("LIVING DELUSION, PUBLIC BETA [2]\n");
		printf("Hi, this is a C/C++ project made while learning the C language!\n");
		printf("Keep in mind, this is a BETA BUILD of this project so everything you see if subject to change!\n");
		printf("The source code is in my Github [@Pessoua] or in the .zip file\n");
		printf("[English isnt my first language so there might be small spelling mistakes]\n\n");
		
		Small_stop;
		
		yellow;
		MidScreenText("Have fun :)");
		for(int i = 0; i < (GetTerminalSize("rows") /2) - 1; i ++)
		printf("\n");
		
		white;
		sleep(2);
	}
	
	StartingScreen();
	
	return 0;
}

int StartingScreen(){
	
    while(true){
		CLR;
	    	
	    printf("0000000000000000000000000000000000000000000000000000000000000000000000\n");
	    printf("044 4     44 4 4      4      4    4 44       4      4  4  55 55 55   0\n");
	    printf("04 4 4  4   4 4 4 4444  4  4    44 4 4   4 44  44    4  55 5  5 5    0\n");
	    printf("04444444444    4    44444444  4             444444 4444 44  55 5  5  0\n");
	    printf("0   0       44444444444        4444444444444444     444  55   55  5  0\n");
	    printf("0   0      4      0   444         4       44       4    55  55 5     0\n");
	    printf("0   0             0                                  55  555         0\n");
	    printf("0   0             0                               5555 5  555        0\n");
	    printf("0 ,_?_____________?_,                            5   55    5         0\n");
	    printf("0 | Living          |                                  55            0\n");
	    printf("0 |        Delusion |              9                                 0\n");
	    printf("0 \\_!_____________!_/         1   91 1    9 9                        0\n");
	    printf("0   0       0                  999111119999                          0\n");
	    printf("0   0       0                  1   99999                             0\n");
	    printf("0 ,_?_______?_,                1911    1991                          0\n");
	    printf("0 |   >Start  |                   9    1                             0\n");
	    printf("0 \\_!_______!_/                   1    1                             0\n");
	    printf("0   0       0                     1    1                             0\n");
	    printf("0 ,_?_______?_,             11119991111111199111                     0\n");
	    printf("0 |   >Help   |             9         991   999                      0\n");
	    printf("0 \\_!_______!_/             1   9991     9191                        0\n");
	    printf("0   0       0               1   1111199911111                        0\n");
	    printf("0 ,_?_______?_,             19  1 1    1                             0\n");
	    printf("0 |  >Credits |             9111  1111 1                             0\n");
	    printf("0 \\_!_______!_/                      111                             0\n");
	    printf("0   0       0                     11  1                              0\n");
	    printf("0 ,_?_______?_,                   1 111                              0\n");
	    printf("0 |   >Quit   |                   1    1                             0\n");
	    printf("0 \\_!_______!_/                   1    1                             0\n");
	    printf("0   0       0                     1    1                             0\n");
	    printf("0   0       0                     1    1                             0\n");
	    printf("0   0                             1 11 1                             0\n");
	    printf("0                                 11  11                             0\n");
	    printf("0                                    1 1                             0\n");
	    printf("0                                  1  1                              0\n");
	    printf("0                                  1   1                             0\n");
	    printf("0             777  7              11   1           777               0\n");
	    printf("0                77    77         1 1111    77   77                  0\n");
	    printf("0   ,___,            77777        11   1     7 77                    0\n");
	    printf("0   |   |        7   77           1    1     77  77        77     77 0\n");
	    printf("0   | E |         7     7    3333333333333333 7              77 777  0\n");
	    printf("0   | x |           3333333 33             33333         777 77      0\n");
	    printf("0   | t |        333     33   33          333    33333333   7  77    0\n");
	    printf("0   | r |      33      33               333  33       33 3333        0\n");
	    printf("0   | a |  33333           333          33                  33333    0\n");
	    printf("0   | s 33       33           333    33        333  33     3    333  0\n");
	    printf("0000000000000000000000000000000000000000000000000000000000000000000000\n");
	    printf("ATENTION, YOU ARE PLAYING THE BETA OF THIS \"GAME\", PLEASE INFORM PESSOUA OF ANY BUGS OR CHANGES THAT SHOULD BE MADE\n");
        printf("Enter command [&/]\n");
        String_Input;

        if(strcmp(Input, "start")== 0)
            Game_Start();

        else if(strcmp(Input, "help")== 0)
            Help();

        else if(strcmp(Input, "quit")== 0)
            exit(0);

        else if(strcmp(Input, "credits")== 0)
            Credits();

        else if(strcmp(Input, "extras")== 0)
            Extras();

        else {
	        
		    while(true){
			    printf("[Error] _> Not a valid command, need help? [Yes] [No]\n");
			    String_Input
			    
			    if(strcmp(Input, "yes")== 0){
			
			        printf("You see the stuff writen on the signs on the image? Those are \"Main Commands\", that means you need to write whats on the \">\" to do starting screen things.\n");
			        Small_stop;
			        break;
					
			    } else if(strcmp(Input, "no")== 0){
			    	
			        printf("Okay :>\n\n");
			        sleep(1); CLR; break;
			        
			    } else { Error; }
			
			}
	
		}

	}

    return 0;
}

//Selecting saves, creating saves and acessing the settings (file management 101)
void Game_Start(void){
	CLR;
	bool achiv_type = false, leave = false, Exist_Save[3], there_is_save = false;
	memset(Exist_Save, false, sizeof(Exist_Save));
	
	short int numb_saves_found = 0;
	
	char * tempsave = (char *)malloc(MAX_PATH);
	char * temp = (char *)malloc(1);
	
	//If its inside a save, go back
    while(FULL_PATH[strlen(FULL_PATH) - 1]!= 'N')
    FULL_PATH[strlen(FULL_PATH) - 1] = '\0';
    
    chdir(FULL_PATH);
	
	//Checking for saves (and registing them)
	for(int i = 0; i < 3; i ++){
		strcpy(tempsave, FULL_PATH);
		strcat(tempsave, "\\SAVE");
		itoa((i + 1), temp, 10);
		strcat(tempsave, temp);
		if(ExistDiret(tempsave)){
			numb_saves_found ++;
			Exist_Save[i] = true;
		}
		
	}
	
	free(tempsave);
	free(temp);
	
	if(numb_saves_found > 0)
	there_is_save = true;
	
	chdir(FULL_PATH);
	
	while(true){
	    printf("Welcome! [Back?]\n");
	    printf(">Start a new game [Start]\n");
	    
	    //If theres a dir, there prob is a save
	    if(there_is_save)
	    printf(">Continue last game [Continue]\n");
	    
	    printf(">Go to the settings [Settings]\n");
	    printf(">Back\n");
	    String_Input;
	   	
		if(strcmp(Input, "back?")== 0){
			printf("[ACHIVEMENT] _> Is this an option? (Actually type out the welcome back) (Will apear when you select your save)\n");
			achiv_type = true;
			sleep(2);
			
			chdir(FULL_PATH);
			FILE * fnewachiv = fopen("ACHIVEMENTDONE.txt", "w");
			fclose(fnewachiv);
	   		
		} else if(strcmp(Input, "start")== 0 || strcmp(Input, "continue")== 0){
			bool new_save = false;
			
			if(strcmp(Input, "start")== 0)
			new_save = true;
	        
	        while(true){
	        	//Possible Errors
	        	if(new_save){
	        		if(Exist_Save[0] && Exist_Save[1] && Exist_Save[2]){
	        			red;
	        			printf("Save limit reached, delete saves to make more\n");
	        			white;
	        			Small_stop;
	        			CLR;
	        			break;
					}
				} else {
					if(!Exist_Save[0] && !Exist_Save[1] && !Exist_Save[2]){
	        			red;
	        			printf("You have no saves to continue your progress\n");
	        			white;
	        			Small_stop;
	        			CLR;
	        			break;
					}
				}
	        	
				if(new_save)
		        printf("Starting new game\n");
		        
		        else
		       	printf("Choose a save\n");
				
				//Printf saves that user dosent have (or has)
				for(int i = 0; i < 3; i ++){
					if(new_save){
						if(!Exist_Save[i])
						printf(">Save %d [%d]\n", i + 1, i + 1);
					} else {
						if(Exist_Save[i])
						printf(">Save %d [%d]\n", i + 1, i + 1);
					}
					
				}
				
		        printf(">Back\n");
		        
		        String_Input;
		        
		        if(strcmp(Input, "1")== 0 || strcmp(Input, "2")== 0 || strcmp(Input, "3")== 0){
		        	
		        	bool is_valid_save = false;
		        	char cur_save_dir [6] = "SAVE";
		        	int cur_save = atoi(Input);
		        	
		        	//Check the diferent requirements in both continue and new cases
		        	if(new_save){
			        	if(!Exist_Save[cur_save - 1])
			        	is_valid_save = true;
			        	
						else {
							Error;
						}
						
					} else {
						if(Exist_Save[cur_save - 1])
			        	is_valid_save = true;
			        		
						else {
							Error;
						}
						
					}
					
					//Needed stuff for both of these
					if(is_valid_save){
						char * temp_dir = (char *)malloc(MAX_PATH);
					    strcpy(temp_dir, FULL_PATH);
					    strcat(temp_dir, "\\.out");
					    
					    //Change this when SAVE 0 is implemented lul
					    chdir(temp_dir);
						FILE * fout = fopen(".save.txt", "w");
						fprintf(fout, "%d\n1", cur_save);
						fclose(fout);
						chdir("..");
						free(temp_dir);
						
						strcat(FULL_PATH, "\\SAVE");
						strcat(FULL_PATH, Input);
						
						//Make new save dir and switch to MakeSaveFiles to handle the rest
						if(new_save){
							printf("Preparing save %d. Please await...\n", cur_save);
							sleep(1);
							strcat(cur_save_dir, Input);
							mkdir(cur_save_dir);
							MakeSaveFiles("new");
							
						//Select Save dir and switch to MakeSaveFiles to handle the rest
						} else {
							printf("Selected save %d. Please await...\n", cur_save);
							sleep(1);
							MakeSaveFiles("load");
							
						}
						
					}
					
				} else if(strcmp(Input, "back")== 0){
					CLR; break;
			
				} else { Error; }
			
			}
			
		} else if (strcmp(Input, "settings")== 0){ 
	        printf("Redirecting to 'Settings'\n");
	    	sleep(1); Settings(); }
	    
	    else if (strcmp(Input, "back")==0){
	        CLR; leave = true; break;  }
	        
	    else { Error; } 
    
	}
		
}

//Developer Console i guess
int Extras(){
    char Extras_Input [25];
    
    //If its inside a save, go back
    while(FULL_PATH[strlen(FULL_PATH) - 1]!= 'N')
    FULL_PATH[strlen(FULL_PATH) - 1] = '\0';
    
    chdir(FULL_PATH);
    char * temp_dir = (char *)malloc(MAX_PATH);
    strcpy(temp_dir, FULL_PATH);
    strcat(temp_dir, "\\.out");
    
    //Handle SAVE-1 (extras only save)
    chdir(FULL_PATH);
    strcat(FULL_PATH, "\\SAVE-1");
    
    chdir(temp_dir);
	FILE * fout = fopen(".save.txt", "w");
	fprintf(fout, "-1\n1");
	fclose(fout);
	chdir("..");
	
	free(temp_dir);
    
    if(!ExistDiret(FULL_PATH)){
    	mkdir("SAVE-1");
    	chdir(FULL_PATH);
    	MakeSaveFiles("new");
	}
	
	chdir(FULL_PATH);
	
    while(true){
    CLR;
	printf("%s>", STARTING_PATH);
	scanf("%s", Extras_Input);
	
	for(int i = 0; i < 25; i ++) 
	Extras_Input[i] = tolower(Extras_Input[i]); 
	
	CLR;
	
	//All IF statements bellow are ordered the same way it shows up in "help"
	
	if (strcmp(Extras_Input, "help")== 0){
		
		yellow;
		CenterText("Notes");
		white;
		CenterText("Your save is now -1 (Testing Save)");
		CenterText("Functions that need arguments will have \"ARG\" tag (You will only see that tag here)");
		
		printf("CORE\n\n");
		printf("\tBack\t\t - Returns to the main screen\n");
		printf("\tChest\t\t - Test the \"Chest\" function\n");
		printf("\tDebug\t\t - Reveals the inner workings of the system (Aka a whole lot of information)\n");
		printf("\tDir\t\t - Check current Directory (cmd command)\n");
		printf("\tEnd\t\t - Test out the planned ending for the game (will crash the .exe)\n");
		printf("\tExtrasHelp\t - Redirects to the help files\n");
		printf("\tItemName\t - Gives you the name of an item depending on the ID provided\n");
		printf("\tGitItem\t\t - Calls the \"GitItem\" function (the function to use items and stuff)\n");
		printf("\tKillSelf\t - return 1. (kills the program)\n");
		printf("\tHelp\t\t - Gives you the list of all commands\n");
		printf("ARG\tInventory\t - Inventory function options\n");
		printf("ARG\tKey\t\t - Calls the function that handles the keys\n");
		printf("\tSettings\t - Redirects to \"Settings\"\n");
		printf("ARG\tSpecialLoc\t - Class the function that handles the Special Locations\n");
		printf("ARG\tTime\t\t - Acess the Time function and manage time too\n");
		printf("\tGetTime\t\t - Get time spent since start (in seconds)\n");
		printf("ARG\tRandWords\t - Randomize a string of text (Password generator or smt lol)\n");
		printf("ARG\tRandWordsV2\t - Slightly diferent from RandWords (slightly)\n");
		
		printf("\n\nART\n\n");
		printf("\tForceError\t - Forces the Error cutscene to happend\n");
		
		printf("\n\nPATH RELATED\n\n");
		printf("ARG\tChangeAppPath\t - Change current path (starting from appdata directory)\n");
		printf("ARG\tChangeLocalPath\t - Change current path (starting from localappdata directory)\n");
		printf("ARG\tCatToCurPath\t - Add to current path (starting from current path)\n");
		
		printf("\n\nLOCATIONS\n\n");
		printf("\tCenter\t\t - Go to the Village Center (Will return to extras after)\n");
		printf("\tGarden\t\t - Go to the Garden (Will return to extras after)\n");
		printf("\tHotel\t\t - Go to the Hotel (Will return to extras after)\n");
		printf("\tLibrary\t\t - Go to the Library (Will return to extras after)\n");
		printf("ARG\tMountain\t - Access ALL of the montain (All zones and everything related to it) (Recomended to change locations before hand)\n");
		printf("\tPit\t\t - Starts the game in the pit with whatever dificulty you have\n");
		printf("\tStart\t\t - Starts the game with whatever dificulty you have\n");
		printf("\tTeller\t\t - Go to the Teller (Will return to extras after)\n");
		printf("\tWizard\t\t - Go to the Wizard (Will return to extras after)\n");
		
		printf("\n\nMINI-GAMES\n\n");
		printf("ARG\tAnimal\t\t - Animal Mini-game\n");
		printf("ARG\tCrop\t\t - Crop Mini-game\n");
		printf("ARG\tFish\t\t - Fish Mini-game\n");
		printf("ARG\tTree\t\t - Tree Mini-game\n");
		printf("ARG\tTutorials\t - Shows all tutorials (Will auto-skip if you have show tutorial off)\n");
		
		printf("\n\nTEXT FORMATING\n\n");
		printf("ARG\tCenterText\t - Centers the text put by argument\n");
		printf("ARG\tRightText\t - Puts the text by argument on the max X axis\n");
		printf("ARG\tRandomText\t - Puts the text put by argument randomy on the Y or X axis, prints it a random number of times and formats the color bettewn red and white\n");
		printf("ARG\tMidText\t\t - Puts the text by argument on the middle of the screen\n");
		printf("ARG\tFormatTextEXT\t - The extended formating function, many arguments\n");
		
		printf("\n\n");
		Small_stop;	
	}
		
	//CORE
	else if (strcmp(Extras_Input, "back")== 0)
	StartingScreen();
	
	else if (strcmp(Extras_Input, "chest")== 0)
	Chest();
	
	else if(strcmp(Extras_Input, "debug")== 0){
		
		CLR;
		
		//Register if debug mode is active or not in the "SETTINGS" directory
		ChangeCurPath("SETTINGS");
		FILE * fdebug = fopen("Debugmode.txt", "w");
		
		if(DEBUG_MODE){
			DEBUG_MODE = false;
			red;
			printf("Disabled debug mode!\n");
			fprintf(fdebug, "NO");
				
		} else {
			DEBUG_MODE = true;
			green;
			printf("Enabled debug mode!\n");
			fprintf(fdebug, "YES");
			
		}
		
		fclose(fdebug);
		chdir("..");
		
		sleep(2);
		CLR;
		white;
		
	}
		
	else if(strcmp(Extras_Input, "change_path")== 0){
		printf("Arguments\n");
		printf("New path?\n");
		String_Input;
		for(int i = 0; i < 50; i++)
		Input[i] = toupper(Input[i]);
		
		CLR;
		ChangeCurPath(Input);
		green;
		printf("Changed path! [Will be changed to original though]\n");
		Small_stop; 
		white;
	}
	
	else if(strcmp(Extras_Input, "dir")== 0){
		system("dir"); 
		Small_stop;
	}
	
	else if(strcmp(Extras_Input, "end")== 0)
	EndOfBeta();
	
	else if(strcmp(Extras_Input, "extrashelp")== 0){
		printf("Go to %s\\Help Notes\n\n", LOCAL_PATH);
		Small_stop;
	}
	
	else if(strcmp(Extras_Input, "itemname")== 0){
		int wanted_id = 0;
		
		while(true){
			CLR;
			printf("What item id?\n");
			printf("? _>");
			scanf("%d", &wanted_id);
			
			if(wanted_id < 1){
				red;
				printf("Invalid ID :>\n");
				white;
			} else
			break;	
		}
		
		CLR;
		char * catch_item_id = GetItemName(wanted_id);
		
		printf("Item name? %s\n", catch_item_id);
		free(catch_item_id);
		Small_stop;
	}
	
	else if(strcmp(Extras_Input, "gititem")== 0)
	GitItem();
	
	else if(strcmp(Extras_Input, "killself")== 0)
	exit(1);
	
	else if(strcmp(Extras_Input, "inventory")== 0){
		
		char extras_inventory [10];
		int inv_return = 0;
		
		while(true){ 
		printf("What argument do you want to use? [SHOW] [CALC] [ID] [CHECK]\n");
		String_Input;
		
		//Argument "SHOW"
		if(strcmp(Input, "show")== 0){
		inv_return = Inventory("SHOW", 0, 0); break;
		
		//Argument "CALC"
		} else if(strcmp(Input, "calc")== 0){
			int ext_id, ext_quant;
			
			//User testing values
			while(true){
				printf("Item Id? \n&/");
				scanf("%d", &ext_id);
				if((ext_id >= 1 && ext_id <= 135) || (ext_id >= 200 && ext_id <= 215))
				break;
				
				else {
					red;
					printf("Invalid id. (Must be bettewn 1 and 135)\n");
					white;
					sleep(3);
					CLR;
				}
			}
			
			CLR;
			printf("Quantity? \n&/");
			scanf("%d", &ext_quant);
			CLR;
			
			inv_return = Inventory("CALC", ext_id, ext_quant);
			
			CLR;
			
			printf("Return values. [1 = YES / 0 = NO]\n");
			
			//Diferent output depending if its full or not
			if(inv_return == 0)
			printf("Inventory full? -> NO\n");
			
			else 
			printf("Inventory full? -> YES\n");
			
			if(inv_return > 0 || inv_return < 0)
			printf("Overflow value? -> %d\n", (int) inv_return);
			
			Small_stop;
			break;
		}
		
		//Argument "ID"
		else if(strcmp(Input, "id")== 0){
		inv_return = Inventory("ID", 0, 0); break;
		
		//Argument "CHECK"
		} else if(strcmp(Input, "check")== 0){
			int ext_id, ext_quant;
			
			//User testing values
			while(true){
				printf("Item Id?\n&/");
				scanf("%d", &ext_id);
				if((ext_id >= 1 && ext_id <= 135) || (ext_id >= 200 && ext_id <= 215))
				break;
				
				else {
					red;
					printf("Invalid id. (Must be bettewn 1 and 135)\n");
					white;
					sleep(3);
					CLR;
				}
			}
			
			CLR;
			while(true){
				printf("Quantity? \n&/");
				scanf("%d", &ext_quant);
				if(ext_quant < 0)
				break;
				
				else {
					red;
					printf("Invalid quantity. (Must be negative)\n");
					white;
					sleep(3);
					CLR;
				}
			}
			
			inv_return = Inventory("CHECK", ext_id, ext_quant);
				
			if(inv_return == 1)
			printf("User HAS that item!\n");
			
			else
			printf("User does not have that item!\n");
			
			Small_stop;
			break;
			
		} else { Error; }
		
		}
		
	}		
	
	else if(strcmp(Extras_Input, "key")== 0){
		while(true){
			printf("What Location? (Must be a valid Location)\n");
			String_Input;
			
			if(strcmp(Input, "forest")== 0 || strcmp(Input, "cascade")== 0 || strcmp(Input, "fungi")== 0
			|| strcmp(Input, "geysers")== 0 || strcmp(Input, "blossom")== 0 || strcmp(Input, "peak")== 0){
			
			Input[0] = toupper(Input[0]);
			Key(Input);
			break;
			
			} else { Error; }
			
		}
		
	}
	
	else if (strcmp(Extras_Input, "settings")== 0)
	Settings(); 
	
	else if (strcmp(Extras_Input, "specialloc")== 0){
		while(true){
			printf("What Location? (Must be a valid Location)\n");
			String_Input;
			
			if(strcmp(Input, "forest")== 0 || strcmp(Input, "cascade")== 0 || strcmp(Input, "fungi")== 0
			|| strcmp(Input, "geysers")== 0 || strcmp(Input, "blossom")== 0 || strcmp(Input, "peak")== 0){
			
			Input[0] = toupper(Input[0]);
			SpecialLocations(Input);
			break;
			
			} else { Error; }
			
		}
	}
	
	else if (strcmp(Extras_Input, "time")== 0){
		
		long int ext_timer, ext_day;
		int ext_hour;
		char ext_time_mode[6];
		
		while(true){
			printf("Argument 1 - [CHECK] / [CALC]\n");
			String_Input;
			
			if(strcmp(Input, "check")== 0 || strcmp(Input, "calc")== 0)
			break;
			
			else
			Error;
		}
		
		for(int i = 0; i < 6; i ++)
		Input[i] = toupper(Input[i]);
		
		strcpy(ext_time_mode, Input);
		
		if(strcmp(ext_time_mode, "CHECK")== 0){
			
			while(true){

				printf("What parameter do you want to check? [Timer] [Hour] [Day]\n");
				String_Input;
				
				if(strcmp(Input, "timer")== 0){
					ext_timer = 1; ext_day = 0; ext_hour = 0;
					break;
					
				} else if(strcmp(Input, "hour")== 0){
					ext_timer = 0; ext_day = 0; ext_hour = 1;
					break;
					
				} else if(strcmp(Input, "day")== 0){
					ext_timer = 0; ext_day = 1; ext_hour = 0;
					break;
					
				} else 
				Error;
					
			}
			
			CLR;
			
			int ret_val = TimeCalc("CHECK", ext_timer, ext_hour, ext_day);
			
			printf("Value Returned? %d\n", ret_val);
			
		} else if(strcmp(ext_time_mode, "CALC")== 0){
			
			printf("Timer? (can be negative)\n");
			printf("&/");
			scanf("%d", &ext_timer);
			
			while(true){
				printf("Hour? (cant be negative)\n");
				printf("&/");
				scanf("%d", &ext_hour);
				
				if(ext_hour >= 0)
				break;
				
				else
				Error;
			}
			
			printf("Day? (can be negative)\n");
			printf("&/");
			scanf("%d", &ext_day);
			
			CLR;
			
			TimeCalc("CALC_EXT", ext_timer, ext_hour, ext_day);
		}
		
		Small_stop;
		
	}
	
	else if(strcmp(Extras_Input, "gettime")== 0){
		printf("Seconds spent? %d\n", GetTimeSpent());
		Small_stop;
	}
	
	else if (strcmp(Extras_Input, "randwords")== 0){
		short int num_spaces;
		
		printf("Arguments (Return value can only be 555 chars long at max)\n\n");
		printf("Number of Spaces?\n");
		printf("&/");
		scanf("%d", &num_spaces);
		
		char *returned_string = EncryptedWordsV1(&num_spaces);
		
		CLR;
		printf("Returned string? %s\n", returned_string);
		
		free(returned_string);
		
		Small_stop;
	}
	
	else if(strcmp(Extras_Input, "randwordsv2")== 0){
		char temp [555] = { '\0' };
		
		printf("Arguments (Return value can only be 555 chars long at max)\n\n");
		printf("String to \"Encrypt\"?\n");
		printf("&/");
		
		fflush(stdin);
		fgets(temp, 555, stdin);
		temp[strlen(temp) - 1] = '\0';
		
		char * catch_the_return_value = EncryptedWordsV2(temp);
		
		printf("Returned string? %s\n", catch_the_return_value);
		free(catch_the_return_value);
		Small_stop;
	}
	
	//ART
	else if (strcmp(Extras_Input, "forceerror")== 0)
	SomethingHasGoneWrong();
	
	//PATH RELATED
	else if(strcmp(Extras_Input, "cattocurpath")== 0 || strcmp(Extras_Input, "changelocalpath")== 0 || strcmp(Extras_Input, "changeapppath")== 0){
		
		printf("Change Current path, recomended argument to be:\n");
		printf("<subdir1>.<subdir2>.<subdir3>\n");
		String_Input;
		
		if(strcmp(Extras_Input, "changeapppath")== 0)
		ChangeCurPath(Input);
		
		else if(strcmp(Extras_Input, "changelocalpath")== 0)
		GetAppResources(Input);
		
		else if(strcmp(Extras_Input, "cattocurpath")== 0)
		CatCurPath(Input);	
	}
	
	//LOCATIONS
	else if (strcmp(Extras_Input, "center")== 0)
	Center();
	
	else if (strcmp(Extras_Input, "garden")== 0)
	Garden();
	
	else if (strcmp(Extras_Input, "hotel")== 0)
	Hotel();
	
	else if (strcmp(Extras_Input, "library")== 0)
	Library();
	
	else if (strcmp(Extras_Input, "mountain")== 0){
		printf("What argument do you want?\n");
		String_Input;
		
		Mountain(Input);
	}
	
	else if (strcmp(Extras_Input, "pit")== 0){
		//Get current pit_jumps in diferent situations
		int pit_jumps = 0;
		ChangeCurPath("ACHIVEMENTS.Progress");
		if(access("PitJumps.txt", F_OK)== 0){
			FILE * fpitj = fopen("PitJumps.txt", "r");
			fscanf(fpitj, "%d", &pit_jumps);
			fclose(fpitj);
		} else {
			ChangeCurPath("ACHIVEMENTS.Done");
			if(access("PitJumps.txt", F_OK)== 0){
				FILE * fpitj = fopen("PitJumps.txt", "r");
				fscanf(fpitj, "%d", &pit_jumps);
				fclose(fpitj);
			} else {
				FILE * fpitj = fopen("PitJumps.txt", "w");
				fprintf(fpitj, "0");
				fclose(fpitj);
			}
		}
		
		//Gib 1 more pit jump 
		pit_jumps ++;
		
		FILE * fpitj = fopen("PitJumps.txt", "w");
		fprintf(fpitj, "%d", pit_jumps);
		fclose(fpitj);
		
		Pit();
	}
	
	else if (strcmp(Extras_Input, "start")== 0)
	Act1();
	
	else if (strcmp(Extras_Input, "teller")== 0)
	Teller();
	
	else if (strcmp(Extras_Input, "wizard")== 0)
	Wizard();
	
	//MINI-GAMES
	else if (strcmp(Extras_Input, "animal")== 0 || strcmp(Extras_Input, "animals")== 0){
		printf("Settings Arguments\n");
		
		short int is_p;
		while(true){
			printf("Is Pit? [Boolean Vaue]\n");
			printf("&/");
			scanf("%d", &is_p);
			if(is_p == 0 || is_p == 1)
			break;
			
			else {
				printf("Needs to be 0 or 1\n");
				sleep(2);
				CLR;
			}
		}
		bool is_pit = is_p;
		
		short int is_b;
		
		if(is_p){
			while(true){
				printf("Is Beehive? [Boolean Vaue]\n");
				printf("&/");
				scanf("%d", &is_b);
				if(is_b == 0 || is_b == 1)
				break;
				
				else {
					printf("Needs to be 0 or 1\n");
					sleep(2);
					CLR;
				}
			}
		} else 
		is_b == 0;
		
		bool is_beehive = is_b;
		
		ChangeCurPath("STORY.Locations");
		FILE * fcur = fopen("Current.txt", "w");
		
		if(is_pit){
			if(is_beehive)
			fprintf(fcur, "Blossom\n");
			
			else
			fprintf(fcur, "Cascade\n");
		} else {
			fprintf(fcur, "NOT\n");
		}
		fclose(fcur);
		
		CLR;
		printf("Animal got? %d\n", Animal(false));
		sleep(3);
		//Animal_got // 1 - rarity + / 2 - rarity ++ / 3 - rarity +++
		
	} else if (strcmp(Extras_Input, "crop")== 0){
		printf("Settings Arguments\n");
		short int crop_id;
		
		printf("Crop id argument?\n");
		printf("&/");
		scanf("%d", &crop_id);
		
		Crop(crop_id, false);
		
	} else if (strcmp(Extras_Input, "fish")== 0){
		printf("Settings Arguments\n");
		short int fish_id;
		
		printf("Fish id argument?\n");
		printf("&/");
		scanf("%d", &fish_id);
		
		Fish(fish_id, "1", false);
		
	} else if (strcmp(Extras_Input, "tree")== 0){
		printf("Settings Arguments\n");
		
		short int is_inv;
		while(true){
			printf("Is Invasive? [Boolean Vaue]\n");
			printf("&/");
			scanf("%d", &is_inv);
			if(is_inv == 0 || is_inv == 1)
			break;
			
			else {
				printf("Needs to be 0 or 1\n");
				sleep(2);
				CLR;
			}
		}
		bool is_invasive = is_inv;
		short int log_id, spc_tree_id;
		
		printf("Log ID?\n");
		printf("&/");
		scanf("%d", &log_id);
		
		printf("Special ID?\n");
		printf("&/");
		scanf("%d", &spc_tree_id);
		
		Tree(is_invasive, "1", log_id, spc_tree_id, false);
		
	} else if (strcmp(Extras_Input, "tutorials")== 0 || strcmp(Extras_Input, "tutorial")== 0){
		printf("Settings Arguments\n");
		short int temp = 0;
		
		while(true){
			printf("What tutorial?\n");
			String_Input;
			
			if(strcmp(Input, "tree")== 0 || strcmp(Input, "animal")== 0 || strcmp(Input, "animals")== 0 || strcmp(Input, "fish")== 0 || strcmp(Input, "crop")== 0){
				break;
				
			} else {
			CLR;
			red;
			printf("Must be tree, animal(s), fish, crop or puzzle 1 - 3\n");
			white;
			sleep(2);
			CLR;
			
			}
		} 
		
		if(strcmp(Input, "crop")== 0)
		Crop(temp, true);		
				
		else if(strcmp(Input, "animal")== 0 || strcmp(Input, "animals")== 0)
		Animal(true);
		
		else if(strcmp(Input, "fish")== 0)
		Fish(temp, "1", true);
		
		else
		Tree(false, "1", temp, temp, true);
	} 
	
	else if(strcmp(Extras_Input, "centertext")== 0){
		char * line = (char *)malloc(555);
		printf("Line Argument? (limit is 555)\n");
		printf("&/");
		//fflush(stdin);
		fgets(line, 555, stdin);
		line[strlen(line) - 1] = '\0';
		CLR;
		
		CenterText(line);
		Small_stop;
		free(line);
	}
	
	else if(strcmp(Extras_Input, "righttext")== 0){
		char * line = (char *)malloc(555);
		printf("Line Argument? (limit is 555)\n");
		printf("&/");
		fflush(stdin);
		fgets(line, 555, stdin);
		line[strlen(line) - 1] = '\0';
		CLR;
		
		RightText(line);
		Small_stop;
		free(line);
	}
	
	
	else if(strcmp(Extras_Input, "randomtext")== 0){
		char * line = (char *)malloc(555);
		printf("Line Argument? (limit is 555)\n");
		printf("&/");
		fflush(stdin);
		fgets(line, 555, stdin);
		line[strlen(line) - 1] = '\0';
		CLR;
		
		RandText(line);
		Small_stop;
		free(line);
	}
	
	else if(strcmp(Extras_Input, "midtext")== 0){
		char * line = (char *)malloc(555);
		printf("Line Argument? (limit is 555)\n");
		printf("&/");
		fflush(stdin);
		fgets(line, 555, stdin);
		line[strlen(line) - 1] = '\0';
		CLR;
		
		MidScreenText(line);
		Small_stop;
		free(line);
	}
	
	else if(strcmp(Extras_Input, "formattextext")== 0){
		
		char * mode = (char *)malloc(25);
		memset(mode, '\0', sizeof(mode));
		
		while(true){
			printf("Mode Argument? [Center / Right / Middle / Rand]\n");
			printf("&/");
			scanf("%s", mode);
			for(int i = 0; i < strlen(mode); i ++)
			mode[i] = tolower(mode[i]);
			CLR;
			
			if(strcmp(mode, "center")== 0 || strcmp(mode, "right")== 0 || strcmp(mode, "middle")== 0 || strcmp(mode, "rand")== 0)
			break;
			
			else {
				red;
				printf("Invalid Argument\n");
				white;
				Small_stop;
			}	
		}
		
		char * line = (char *)malloc(555);
		memset(line, '\0', sizeof(line));
		printf("Line Argument? (limit is 555)\n");
		printf("&/");
		fflush(stdin);
		fgets(line, 555, stdin);
		line[strlen(line) - 1] = '\0';
		CLR;
		
		bool new_l = false;
		printf("New line Argument? (boolean argument)\n");
		printf("&/");
		scanf("%d", &new_l);
		CLR;
		
		int starting_disp = 0;
		printf("Skip Starting Displacement Argument?\n");
		printf("&/");
		scanf("%d", &starting_disp);
		if(starting_disp < 0)
		starting_disp = 0;
		CLR;
		
		char wanted_colors [555] = { '\0' };
		printf("Wanted Colors Argument? (Encoded String)\n");
		printf("&/");
		scanf("%s", wanted_colors);
		CLR;
		
		int force_number_of_lines = 0;
		printf("Force THIS number of lines Argument?\n");
		printf("&/");
		scanf("%d", &force_number_of_lines);
		if(force_number_of_lines < 0)
		force_number_of_lines = 0;
		CLR;
		
		int repeat_number_of_lines = 0;
		printf("Repeat THIS number of lines Argument?\n");
		printf("&/");
		scanf("%d", &repeat_number_of_lines);
		if(repeat_number_of_lines < 0)
		repeat_number_of_lines = 0;
		CLR;
		
		FormatTextEXT(mode, line, new_l, starting_disp, wanted_colors, false, force_number_of_lines, repeat_number_of_lines);
		printf("\n");
		Small_stop;
		free(line);
		free(mode);
	}
	
	else {
		
		red;
		printf("[SYSTEM] _> Invalid commmand, type \"Help\" for help or \"Back\" to go back to the main screen.\n");
		Small_stop;
		
	}

CLR;
white;

} //Loop ends

}

void Help(){
    
    while(true){
    CLR;
    printf("Info\n\n"); 
    printf("Please select.\n");
    printf(">Input (The commands you write)\n");
    printf(">Output (The commands the code gives you)\n");
    printf(">Saves (How the save system works)\n");
    printf(">Table Movement [Table] (Insides in the movement on the pit and mini games)\n");
    printf(">Bug Fixes [Bug] (Program broke? Try these!)\n");
    printf(">Back (Takes you back to the main menu)\n");
    String_Input;
    
    if (strcmp(Input, "input")== 0){
    	
        printf("Input.\n");
        printf("\"&/\"this is a command line\n");
        printf("And inside this command line you write commands to interact with my code\n");
        printf("The commands you write in here should be very simple and are generaly actions and fight interactions and interactions with puzzles\n");
        printf("Here is the sintax of how an input should be\n\n");
        printf("Leave now![Normal npc dialogue]\n");
        printf(">Run away![Action]\n");
        printf("&/Run\n\n");
        printf("In this example you only need to write Run in the command line\n");
        printf("This rule is aplied to every comand you need to write in order to make an action\n");
        printf("And the action choices you can make will have a '>' outside them\n");
        printf("Also if the action choise is longer than 2 words a \"[]\" will apear after the action and you MUST write whatever is inside of it or it wont work\n");
        printf("End.\n\n");
        
        Small_stop;

    } else if (strcmp(Input, "output")== 0){
    	
        printf("There may be or may not be a few small visual bugs when the program is transitioning bettewn code\n");
		printf("This is very normal and it shouldnt affect your overall experience at all\n");
		printf("Also the program has a few color commands and some text formating stuff so keep in mind it wont work unless its the right operating system\n");
		printf("Theres a version for Linux / Windows / Linux\n");
		printf("End.\n\n");
		
		Small_stop;
		
	} else if (strcmp(Input, "saves")== 0){
    	
        printf("Save system is initiated in the beginning of the game (depending on the save you choose) for example:\n");
        printf("[%appdata%]\\LIVING_DELUSION\\SAVE?] This is the path that keeps all your information on that save (if you dont have a custom path)\n");
        printf("Custom paths just go like [[PATH]\\LIVING_DELUSION\\SAVE?], but it does make a file called \"path.txt\" that contains the custom path :>\n");
        printf("Uhh dont delete the \"path.txt\" thing and the save system shouldnt break :> if it does, make a new custom path and remove the old one\n");
        printf("The LIVING_DELUSION Folder contains the Saves 1 to 3 and they contain the usefull information on what you have done on that save\n");
        printf("You can modify that information [But thats cheating] but you need to know what you are doing or else the system may break!\n");
        printf("You can modify your save path on the \"Settings\"\n\n");
		
		Small_stop;
		 
	} else if (strcmp(Input, "table")== 0){
    	
    	printf("Tables.\n");
    	printf("The following is an indept explanation of how the table system works, MADE TO ERASE EXISTING QUESTIONS\n");
    	printf("So, has we know theres 2 types of Tables \"Int\" and \"Char\"\n");
    	printf("The way they work is the same, the only thing changing its the display of the table\n");
    	printf("For Example:\n");
    	printf("3x3 INT TABLE EXAMPLE\n");
    	printf("0 1 0\n");
    	printf("2 9 3\n");
    	printf("0 4 0\n\n");
    	printf("3x3 CHAR TABLE EXAMPLE\n");
    	printf("NONE UP NONE\n");
    	printf("LEFT YOU RIGHT\n");
    	printf("NONE DOWN NONE\n\n");
    	printf("The only thing that (really) changes bettewn the two is the display and the input, everything else is the same.\n");
    	printf("Also, if u dont remember, here it is:\n");
    	printf("INT TYPE COMMANDS\n");
    	printf("\"1\" to go up, \"2\" to go left, \"3\" to go right, \"4\" to go down and \"0\" to stay in the same place. \"5\" is used for SPECIAL ACTIONS depending on the mini game / interaction\n\n");
    	printf("CHAR TYPE COMMANDS\n");
    	printf("\"Up\" to go up, \"Left\" to go left, \"Right\" to go right, \"Down\" to go down and \"Stay\" to stay in the same place. \"Lead...(etc)\" is used for SPECIAL ACTIONS depending on the mini game / interaction\n\n");
    	printf("So, Movement done, this table system works on a (X,Y) position calculation, AKA if u go up it adds 1 to Y / go down and it takes away 1 to Y / go left and it takes away 1 to X / go right and it adds 1 to X\n");
    	printf("The program runs a bunch of calculations before it shows you your current position so it may lead to \"Visual Bugs\", i cant really do anything about it (i think) so its very normal to see your postion slightly out of place\n");
    	printf("If you are struggling with interacting with objects inside the table, heres a guide\n");
    	printf("Ill be using a 3x3 INT Table for example\n");
    	printf("0 1 0\n");
    	printf("5 9 3\n");
    	printf("0 4 0\n\n");
    	printf("In this case, pressing the special command \"5\" will allow you to interact with the object displayed has \"5\" inside the table (if you are 1 move away from it that is else it will let you know you cant reach it)\n");
    	printf("Well that (should) be it for Table movement and interactions\n");
    	printf("Hope you dont have any more questions\n");
    	printf("End.\n\n");
    	
    	Small_stop;

	} else if (strcmp(Input, "bug")== 0){
		
		while(true){
			CLR;
			printf("Bug Fixes\n\n");
			printf(">Save files apearing in the starting directory / Program not detecting the custom directory [Dir]\n");
			printf(">Permanently delete all LIVING_DELUSION files [Remove]\n");
			printf(">Back\n");
			
			String_Input;
					
			if(strcmp(Input, "dir")== 0){
				printf("-> Check if \"path.txt\" file is in the same folder has the .exe file\n");
				printf("-> Move the .exe file and \"path.txt\" to annother location\n");
				printf("-> Check if the directory inside \"path.txt\" exists AND has characters inside the ASCII table, ignore charecters like \"á\" or \"ó\"\n");
				printf("-> Change the code and compile it yourself if nothing works\n");
				printf("[NOTE]: If it still does not work, check if it has permitions to make files inside of THAT directory\n");
				printf("Make sure to run the .exe file with admin permitions to make sure its not a permitions issue\n");
				Small_stop;
				
			} else if(strcmp(Input, "remove")== 0){
				printf("-> Check your %%APPDATA%% (&& %%LOCALAPPDATA%%) file for a LIVING_DELUSION folder and just delete it\n");
				printf("-> Also check the path thats on \"path.txt\" in the same dir has the .exe file\n");
				printf("-> It is recommended to check both %%APPDATA%% and \"path.txt\"\n");
				printf("[NOTE]: You can do this on the settings\n");
				Small_stop;
				
			} else if(strcmp(Input, "back")== 0){
				break;
				
			} else { Error; }
			
		}
		
	}
    else if (strcmp(Input, "back")== 0){
       CLR; break;
    }    
    
    else { Error; }
    
	}

	StartingScreen();

}

void Credits(){ //Possibly add more
    CLR;
    CenterText("Living Delusion by @pessoua\n\n");
    CenterText("Creator -> \"Pessoua\"\n");
    CenterText("Code -> \"Pessoua\"\n");
    CenterText("Art -> \"Pessoua\"\n");
    CenterText("Dev. Team -> \"Pessoua\"\n");
    CenterText("Story Line -> \"Pessoua\"\n");
    CenterText("Play Testers -> \"Pessoua, \"Afro\"[and more]\n");
    
    CenterText("(Some) Pictures came from https://pixabay.com/ and were comverted to ascii using https://www.asciiart.eu/image-to-ascii\n");
	CenterText("KEY 4 MONST 1 -> EXPORTED FROM \"https://pixabay.com/photos/skull-human-head-skeleton-bone-765477/\"");
	CenterText("KEY 4 MONST 2 -> EXPORTED FROM \"https://pixabay.com/photos/eye-iris-sight-eyebrows-detailed-2681783/\"");
	CenterText("KEY 4 MONST 3 -> EXPORTED FROM \"https://pixabay.com/photos/mask-carnival-costume-party-venice-1161392/\"");
	CenterText("KEY 4 MONST 4 -> EXPORTED FROM \"https://pixabay.com/photos/line-eye-corn-snake-dandruff-1446008/\"");
	CenterText("KEY 4 MONST 5 -> EXPORTED FROM \"https://pixabay.com/illustrations/voodoo-doll-toy-childhood-6910868/\"\n");
    
	CenterText("KEY 4 PUZZLE 1 -> EXPORTED FROM \"https://pixabay.com/vectors/gear-wheel-gearwheel-gear-cogs-310906/\"");
	CenterText("KEY 4 PUZZLE 2 -> EXPORTED FROM \"https://pixabay.com/illustrations/boxes-wood-transparent-crates-6831626/\"");
	CenterText("KEY 4 PUZZLE 3 -> EXPORTED FROM \"https://pixabay.com/vectors/document-paper-sheet-written-lined-38200/\"");
    
    CenterText("Thanks for playing! I hope you enjoyed my small C/C++ project :D\n\n");
    Small_stop;
}

void Settings(){
	
	if(isdigit(FULL_PATH[strlen(FULL_PATH) - 1])!= 1){
		CLR;
		red;
		printf("Select a save before trying to mess with the settings\n");
		white;
		sleep(3);
		CLR;
		return;
	}
	
    char settings_input [20];
    
    while(true){
    CLR;
    ChangeCurPath("SETTINGS");
    
    printf("Settings\n\n");
    printf("Topics to change\n");
    printf(">Intro\n");
    printf(">Mini Games [Mini]\n");
    printf(">Tutorials\n");
    printf(">Display Tip [Tip]\n");
    printf(">Custom Save Path [Path]\n");
    printf(">Inventory Organization [Inventory]\n");
    printf(">Delete Data [Data]\n");
    printf(">Back\n");
    printf("Change?\n");
   	String_Input;
    
    if(strcmp(Input, "intro")== 0){
	    
	    while(true){
	    	CLR;
	    	printf("Intro\n");
		    if(skip_intro)
		    printf("Skip Intro current value? -> YES\n");
		    
		    else
		    printf("Skip Intro current value? -> NO\n");
	    	
		    printf("Want to change Skip Intro value?\n");
		    printf(">Yes\n");
		    printf(">No\n");
		    String_Input;
		    
		    if(strcmp(Input,"yes")== 0){
		        
		        if(skip_intro){
		        	printf("Changing Skip Intro value to \"NO\"\n");
		        	skip_intro = false;
				} else {
					printf("Changing Skip Intro value to \"YES\"\n");
		        	skip_intro = true;
				}
		        
		    } else if (strcmp(Input, "no")== 0){
		        
		        //Register change in file
		    	FILE * fintros = fopen("IntroSet.txt", "w");
		    	fprintf(fintros, "%d\n", skip_intro);
		    	fclose(fintros);
			        
		        CLR; break;
		        
		    } else { Error; }
	    }
    
	} else if (strcmp(Input, "mini")== 0){
	
	    while(true){
		    CLR;
		    printf("Mini Games.\n");
		    
		    printf("Current Game Set value? -> %s\n", game_set);
		    printf("[INT means integers EX. 2 and 9 / CHAR means charecters EX. Left and Right]\n\n");
		    
		    if(show_user_turn)
		    printf("Show User Turn value? -> YES\n");
		    
		    else
		    printf("Show User Turn value? -> NO\n");
		    
		    printf("What to change?\n");
		    printf(">Game Set [Game]\n");
		    printf(">Show User Turn [Turn]\n");
		    printf(">Back\n");
		    String_Input;
		    
		    if(strcmp(Input, "game")== 0){
		        
		        if(strcmp(game_set, "Char")== 0){
			        printf("Changing Game Set value to \"Int\"\n");
			        strcpy(game_set, "Int");
		    	} else {
		    		printf("Changing Game Set value to \"Char\"\n");
		    		strcpy(game_set, "Char");
				}
				
				sleep(1);
				CLR;
		        
		    } else if(strcmp(Input, "turn")== 0){
				
				if(show_user_turn){
					printf("Changing Show User Turn value to \"NO\"\n");
					show_user_turn = false;
				} else {
					printf("Changing Show User Turn value to \"YES\"\n");
					show_user_turn = true;
				}
				
				sleep(1);
				CLR;
				
			} else if (strcmp(Input, "back")== 0){
		        
		        //Register new settings inside file
			    FILE * fMiniGames = fopen("MiniGamesSet.txt", "w");
			    fprintf(fMiniGames, "%s\n", game_set);
			    fprintf(fMiniGames, "%d\n", show_user_turn);
			    fclose(fMiniGames);
		        CLR; break;
		        
		    } else { Error; }
		    
	    }
    
	} else if (strcmp(Input, "tutorials")== 0){
	
	    while(true){
		    CLR;
		    printf("Tutorials\n");
		    printf("\n[!] BE AWARE, TUTORIALS GIVE YOU A LOT OF IMPORTANT INFORMATION, ESPECIALLY IF YOU ARE A BEGINNER [!]\n\n");
		    if(display_all_tut_once)
		    printf("Display Tutorials once? YES\n");
		    
		    else
		    printf("Display Tutorials once? NO\n");
		    
		    if(force_tut_display)
		    printf("Force Tutorial display? YES\n");
		    
		    else
		    printf("Force Tutorial display? NO\n");
		    
		    if(skip_tut_display)
		    printf("Skip Tutorial display? YES\n\n");
		    
		    else
		    printf("Skip Tutorial display? NO\n\n");
		    
		    if(show_tut_cutscene)
		    printf("Show Tutorial Cutscene? YES\n\n");
		    
		    else
		    printf("Show Tutorial Cutscene? NO\n\n");
		    
		    printf("Change tutorial?\n");
		    printf(">Display once? [Display]\n");
		    printf(">Force all? [Force]\n");
		    printf(">Skip all? [Skip]\n");
		    printf(">Show Cutscene? [Cutscene]\n");
		    printf(">Back\n\n");
		    printf("Change to?\n");
		    String_Input;
		    
		    if (strcmp(Input, "display")== 0){
		        
		        if(!display_all_tut_once){
			        printf("Changing Display [All] tutorials once to \"YES\"\n");
			        display_all_tut_once = true;
			        force_tut_display =  false;
			        skip_tut_display = false;
		    	} else 
		    	printf("Already on \"YES\"\n");
		    	
		    	sleep(1);
		        CLR;
		        
		    } else if (strcmp(Input, "force")== 0){
		        
		        if(!force_tut_display){
			        printf("Changing Force [All] tutorials to \"YES\"\n");
			        display_all_tut_once = false;
			        force_tut_display =  true;
			        skip_tut_display = false;
		    	} else 
		        printf("Already on \"YES\"\n");
		        
		        sleep(1);
		        CLR;
		        
		    } else if (strcmp(Input, "skip")== 0){
		        
		        if(!skip_tut_display){
			        printf("Changing Skip [All] tutorials to \"YES\"\n");
			        display_all_tut_once = false;
			        force_tut_display =  false;
			        skip_tut_display = true;
		    	} else 
		    	printf("Already on \"YES\"\n");
		        
		        sleep(1);
		        CLR;
		        
		    } else if (strcmp(Input, "Cutscene")== 0){
		    	
		    	if(show_tut_cutscene){
			    	printf("Changing Show [All] Tutorial Cutscenes to \"NO\"\n");
			    	show_tut_cutscene = false;
		    	} else {
		    		printf("Changing Show [All] Tutorial Cutscenes to \"YES\"\n");
			    	show_tut_cutscene = true;
				}
		    	
		    	sleep(1);
		    	CLR;
			
			} else if (strcmp(Input, "back")== 0){
		        
		        //Register changes in tutorial settings file
			    FILE * fTutorials = fopen("TutorialSet.txt", "w");
			    fprintf(fTutorials, "%d\n", display_all_tut_once);
			    fprintf(fTutorials, "%d\n", force_tut_display);
			    fprintf(fTutorials, "%d\n", skip_tut_display);
			    fprintf(fTutorials, "%d\n", show_tut_cutscene);
			    fclose(fTutorials);
		       	CLR; break;
		        
		    } else { Error; }
	    
	    }
	    
	} else if(strcmp(Input, "tip")== 0){
	
		while(true){
			CLR;
			printf("Tip\n");
			if(display_tip)
			printf("Current Display Tip value? \"YES\"\n");
			
			else
			printf("Current Display Tip value? \"NO\"\n");
			
			printf("Want to change Display Tip value?\n");
			printf(">Yes\n");
			printf(">No\n");
			String_Input;
			
			if(strcmp(Input, "yes")== 0){
				
				if(display_tip){
					printf("Changing Display Tip value to \"NO\"\n");
					display_tip = false;
				} else {
					printf("Changing Display Tip value to \"YES\"\n");
					display_tip = true;
				}
				
				sleep(1);
				CLR;
				
			} else if (strcmp(Input, "no")== 0){
				
				//Register new changes inside file
				FILE * fdisplaytip = fopen("DisplayTipSet.txt", "w");
				fprintf(fdisplaytip, "%d\n", display_tip);
				fclose(fdisplaytip);	
				CLR; break;
				
			} else { Error; }
			
		}

	} else if(strcmp(Input, "path")== 0){
		char CUSTOM_PATH [MAX_PATH];
		bool invalid_ascii = false, invalid_dir = false;
		
		while(true){
			CLR;
			invalid_ascii = false, invalid_dir = false;
			
			//Prevent inf loop
			memset(CUSTOM_PATH, '\0', sizeof(CUSTOM_PATH));
			
			//Errors have a brain fart here
			printf("Please do not insert a directory that contains \"á\" or \"ó\", respect the ASCII values bettewn 0 and 127.\n");
			printf("Insert the path where you want the save file to be created [WILL BREAK IF FOLDERS ARE DELETED FROM SAVES]\n");
			printf("&/");
			scanf("%s", CUSTOM_PATH);
			
			//Invalid char like "á" or "ó"
			for(int i = 0; i < sizeof(CUSTOM_PATH); i ++){
				int checking_char = CUSTOM_PATH[i];
				if(checking_char > 127 || checking_char < 0){
					red;
					printf("Invalid Directory! (Does not respect ASCII limit bettewn 0 and 127)\n");
					sleep(3);
					white;
					invalid_ascii = true;
					break;
				}
			}
			
			//2 errors is kinda annoying
			if(!invalid_ascii){
				//Dir dosent exist
				if(ExistDiret(CUSTOM_PATH) == 0){
					red;
					printf("Invalid Directory! (Does not exist)\n");
					sleep(3);
					white;
					invalid_dir = true;
				}
			}
			
			if(!invalid_ascii && !invalid_dir)
			break;
		}
		
		//Save new path in a file called path.txt in the starting dir
		GetAppResources("Path (if exists)"); 
		FILE * fpath = fopen("path.txt", "w");
		fprintf(fpath, "%s", CUSTOM_PATH);
		fclose(fpath);
		
		//change custom path sligthy
		strcat(CUSTOM_PATH, "\\LIVING_DELUSION");
		
		CLR;
		printf("The save file will be created in \"%s\".", CUSTOM_PATH);
		printf("Keep in mind, if the .exe file is moved from its location it will make a new one on the %%appdata%% folder\n");
		printf("If the file \"path.txt\" is deleted (or moved) it will make a new one on the %%appdata%%\n");
		printf("To safely move the .exe file AND keep the custom directory, move BOTH path.txt AND the .exe file to the SAME DIRECTORY (otherwise the program will not detect the file)\n");
		printf("If the custom directory suffers any alterations, it may cause the system to break\n");
		printf("If it creates annother save on the %%appdata%%, your progress is not lost\n");
		printf("Just make annother custom path or replace the %%appdata%% save with the old one and it will work fine [IF ITS NOT MODIFIED]\n");
		printf("BE AWARE: CUSTOM PATH WILL NOT WORK IF MAKING DIRECTORIES IN THE CHOOSEN DIRECTORY REQUIRES ADMINISTRATOR ACCESS\n");
		printf("Game will crash now.\n");
		
		chdir(CUSTOM_PATH);
		strcpy(FULL_PATH, CUSTOM_PATH);
		Small_stop;
		exit(0);
		
	} else if (strcmp(Input, "inventory")== 0){
	
		while(true){
			CLR;
			printf("Inventory [Will only show up when showing inventory or selecting an item]\n");
			if(div_inv_sect)
			printf("Divide into sections? YES\n");
			
			else
			printf("Divide into sections? NO\n");
			
			if(limit_inv)
			printf("Limit inventory? YES\n");
			
			else
			printf("Limit inventory? NO\n");
			
			printf("Change inventory?\n");
			printf(">Divide into section [Divide]\n");
			printf(">Limit inventory [Limit]\n");
			printf(">Back\n");
			String_Input;
			
			if(strcmp(Input, "divide")== 0){
				
				//Change divide inv set
				if(div_inv_sect){
					printf("Changing divide inventory to \"NO\"\n");
					div_inv_sect = false;
					limit_inv = true;
					
					printf("VISUAL EXAMPLE (Inventory will apear has:) (Limited for example ONLY)\n");
					printf("Livestock items [0]\n\n");
		
					printf("[FROM: HERB GARDEN] _> 36.Egg? 0 / 37. Wool? 0 / 38. Milk? 0\n");
					printf("[FROM: BIRDHOUSES] _> 39.Flight Feather? 0 / 40. Down Feather? 0 / 41. Tail Feather? 0\n");
					printf("[FROM: BEHIVE] _> 43.Honey? 0 / 44. Pollen? 0 / 45. Beeswax? 0\n");
					
				} else {
					printf("Changing divide inventory to \"YES\"\n");
					div_inv_sect = true;
					limit_inv = false;
					
					printf("VISUAL EXAMPLE (Inventory will apear has:)\n");
					printf("What category do you want to see?\n");
					printf(">Farming\n");
					printf(">Livestock\n");
					printf(">Fishing\n");
					printf(">Foraging\n");
					printf(">Alchemy\n");
					printf(">Extras\n");
					printf("&/\n");
				}
				
				printf("\n\n");
				Small_stop;
				
			} else if(strcmp(Input, "limit")== 0){
				
				if(div_inv_sect){
					printf("[SETTINGS] _> Please turn off divide inventory before trying to change this paremeter!\n");
					Small_stop;
						
				} else {
		
					short int aur = -1;
					
					while(true){
						CLR;
						aur = -1;
						printf("What do you want to show up? [Requires you to have divide inventory disabled]\n");
						printf(">Farming? %s\n", arr_limit_inv[0]);
						printf(">Livestock? %s\n", arr_limit_inv[1]);
						printf(">Fishing? %s\n", arr_limit_inv[2]);
						printf(">Foraging? %s\n", arr_limit_inv[3]);
						printf(">Alchemy? %s\n", arr_limit_inv[4]);
						printf(">Extras? %s\n", arr_limit_inv[5]);
						printf(">Back\n");
						
						printf("Please select what you want to change\n");
						String_Input;
						
						if(strcmp(Input, "farming")== 0)
						aur = 0;
						
						else if(strcmp(Input, "livestock")== 0)
						aur = 1;
						
						else if(strcmp(Input, "fishing")== 0)
						aur = 2;
						
						else if(strcmp(Input, "foraging")== 0)
						aur = 3;
						
						else if(strcmp(Input, "alchemy")== 0)
						aur = 4;
						
						else if(strcmp(Input, "extras")== 0)
						aur = 5;
						
						else if(strcmp(Input, "back")== 0){
							
							CLR; break;
							
						} else { Error; aur = -1; }
						
						if(aur != -1){
							if(arr_limit_inv[aur]){
								printf("Changing to \"NO\"\n");
								arr_limit_inv[aur] = false;
								sleep(2); CLR;
								
							} else {
								printf("Changing to \"YES\"\n");
								arr_limit_inv[aur] = true;
								sleep(2); CLR;
								
							}
							
						}
					
					}
					
					}
				
			} else if(strcmp(Input, "back")== 0){
				
				//Register new settings
				FILE * finventoryset = fopen("InventorySet.txt", "w");
				fprintf(finventoryset, "%d\n", div_inv_sect);
				fprintf(finventoryset, "%d\n", limit_inv);
				for(int i = 0; i < 6; i++)
				fprintf(finventoryset, "%d\n", arr_limit_inv[i]);
				fclose(finventoryset);
				
				CLR; break;
				
			} else { Error; }
		
		}
		
		
	} else if(strcmp(Input, "data")== 0){
		
		while(true){
			printf("What do you want to delete?\n");
			printf("[PLEASE MAKE SURE ANY OUTSIDE OF THE GAME FOLDERS NAMES DO NOT CONTAIN: \"LIVING_DELUSION\" OR THEY WILL BE WIPED]\n");
			printf(">Save\n");
			printf(">All saves [All] ([!]Will cause a game crash[!])\n");
			printf(">Everything related to LIVING DELUSION [Everything]\n");
			printf(">Back\n");
			String_Input;
			
			if(strcmp(Input, "save")== 0){
				
				char * temp_dir = (char *)malloc(MAX_PATH);
				strcpy(temp_dir, FULL_PATH);
				
				//Extras save has 1 more charecter that we need to remove
				if(FULL_PATH[strlen(FULL_PATH) - 2] == '-'){
					temp_dir[strlen(temp_dir) - 1] = '\0';
				}
				
				temp_dir[strlen(temp_dir) - 1] = '\0';
					
				printf("What save do you want to delete?\n");
				for(int i = 0; i < 3; i ++){
					char temp [2];
					itoa((i + 1), temp, 10);
					strcat(temp_dir, temp);
					if(ExistDiret(temp_dir))
					printf(">Save %d [%d]\n", i + 1, i + 1);
					temp_dir[strlen(temp_dir) - 1] = '\0';
				}
				
				strcat(temp_dir, "-1");
				if(ExistDiret(temp_dir))
				printf(">Save -1 [-1]\n");
				
				temp_dir[strlen(temp_dir) - 1] = '\0';
				temp_dir[strlen(temp_dir) - 1] = '\0';
				
				String_Input;
				
				if(strcmp(Input, "1")== 0 || strcmp(Input, "2")== 0 || strcmp(Input, "3")== 0 || strcmp(Input, "-1")== 0){
						
						char * save_to_be_deleted = (char *)malloc(3);
						strcpy(save_to_be_deleted, Input);
						
						while(true){
							strcat(temp_dir, save_to_be_deleted);
							if(!ExistDiret(temp_dir)){
								Error;
								free(save_to_be_deleted);
								break;
							}
							
							if(strcmp(temp_dir, FULL_PATH)== 0){
								red;
								printf("Cannot delete save you are currently in. (NO_DIR_REM_EROR)\n");
								white;
								sleep(3);
								CLR;
								free(save_to_be_deleted);
								break;
							}
							
							red;
							printf("Are you sure you want to delete SAVE%s? (All your progress on that save file will be lost) [Yes] [No]\n", save_to_be_deleted);
							white;
							String_Input;
							
							if(strcmp(Input, "yes")== 0){
								//Security check! (No way!!)
								bool passed_security_check = false;
								
								char * security_check_path = (char *)malloc(MAX_PATH);
								chdir(STARTING_PATH);
								
								if(access("path.txt", F_OK)== 0){
									FILE * fpath = fopen("path.txt", "r");
									fscanf(fpath, "%s\n", security_check_path);
									fclose(fpath);
									
								} else {
									const char *md = "APPDATA";
									char *appdata = getenv(md);
									strcpy(security_check_path, appdata);
									
								}
								
								strcat(security_check_path, "\\LIVING_DELUSION");
								
								chdir(FULL_PATH);
								chdir("..");
								
								//Git cur_path
								char * SEC_PATH = (char *)malloc(MAX_PATH);
								getcwd(SEC_PATH, MAX_PATH);
								
								//Check if we on the right path :>
								if(strcmp(security_check_path, SEC_PATH)== 0)
								passed_security_check = true;
								
								free(SEC_PATH);
								free(security_check_path);
								
								if(passed_security_check){
									if(strcmp(save_to_be_deleted, "1")== 0)
									system("rmdir /s /q SAVE1");
									
									else if(strcmp(save_to_be_deleted, "2")== 0)
									system("rmdir /s /q SAVE2");
									
									else if(strcmp(save_to_be_deleted, "3")== 0)
									system("rmdir /s /q SAVE3");
									
									else if(strcmp(save_to_be_deleted, "-1")== 0)
									system("rmdir /s /q SAVE-1");
									
									chdir(FULL_PATH);
									free(save_to_be_deleted); CLR; break;
									
								} else {
									//Smol thing to make sure we dont delete any files OUTSIDE of living delusion
									red;
									CenterText("Save was not deleted due to a vulnerability detected");
									CenterText("If this error persists, please visit this folder and check for anything out of place:");
									
									char * SEC_PATH = (char *)malloc(MAX_PATH);
									getcwd(SEC_PATH, MAX_PATH);
									
									CenterText(SEC_PATH);
									white;
									
									free(SEC_PATH);
									Small_stop;
									
								}
								
							} else if(strcmp(Input, "no")== 0){
								
								free(save_to_be_deleted); CLR; break;
								
							} else {
								Error; 
							}
							
						}
						
				} else if(strcmp(Input, "back")== 0){
					
					free(temp_dir); break; CLR;
					
				} /*else if(strcmp(Input, "0")== 0){
					
					red;
					MidScreenText("Administrator access required.");
					white;
					sleep(3);
					CLR;
					
				}*/ else {
					Error;
				}
				
			} else if(strcmp(Input, "all")== 0){
				
				while(true){
					red;
					printf("Are you sure you want to delete all SAVES? (All your progress will be lost) [Yes] [No]\n");
					printf("WARNING: This action will crash your game!\n");
					white;
					String_Input;
								
					if(strcmp(Input, "yes")== 0){
						while(FULL_PATH[strlen(FULL_PATH) - 1] != 'N')
						FULL_PATH[strlen(FULL_PATH) - 1] = '\0';		
						
						//Security check! (No way!!)
						bool passed_security_check = false;
						
						char * security_check_path = (char *)malloc(MAX_PATH);
						chdir(STARTING_PATH);
						
						if(access("path.txt", F_OK)== 0){
							FILE * fpath = fopen("path.txt", "r");
							fscanf(fpath, "%s\n", security_check_path);
							fclose(fpath);
							
						} else {
							const char *md = "APPDATA";
							char *appdata = getenv(md);
							strcpy(security_check_path, appdata);
							
						}
						
						chdir(FULL_PATH);
						chdir("..");
						
						//Git cur_path
						char * SEC_PATH = (char *)malloc(MAX_PATH);
						getcwd(SEC_PATH, MAX_PATH);
						
						//Check if we on the right path :>
						if(strcmp(security_check_path, SEC_PATH)== 0)
						passed_security_check = true;
						
						free(SEC_PATH);
						free(security_check_path);
						
						if(passed_security_check){
							system("rmdir /s /q LIVING_DELUSION");
							exit(1);
							
						} else {
							//Smol thing to make sure we dont delete any files OUTSIDE of living delusion
							red;
							CenterText("All saves were not deleted due to a vulnerability detected");
							CenterText("If this error persists, please visit this folder and check for anything out of place:");
							
							char * SEC_PATH = (char *)malloc(MAX_PATH);
							getcwd(SEC_PATH, MAX_PATH);
							
							CenterText(SEC_PATH);
							white;
							
							free(SEC_PATH);
							Small_stop;
							
						}
						
					} else if(strcmp(Input, "no")== 0){
						
						CLR; break;
						
					} else {
						Error; 
					}
					
				}
				
			} else if(strcmp(Input, "everything")== 0){
				
				bool leave = false;
				
				while(true){
					red;
					printf("Are you sure you want to delete EVERYTHING? (Everything will be lost) [Yes] [No]\n");
					printf("WARNING: This action will lock you out of the game (Download the game again if you want to play again)!\n");
					printf("NOTE: .exe file and other files will need to be manually deleted though\n");
					white;
					String_Input;
					
					if(strcmp(Input, "yes")== 0){
						while(true){
							red;
							printf("Final warning, this process cannot be reverted.\n");
							printf("[Continue] [Nevermind]\n");
							white;
							String_Input;
							
							if(strcmp(Input, "continue")== 0){
								
								while(FULL_PATH[strlen(FULL_PATH) - 1] != 'N')
								FULL_PATH[strlen(FULL_PATH) - 1] = '\0';		
								
								//Security check! (No way!!)
								bool passed_security_check1 = false, passed_security_check2 = false;
								
								char * security_check_path = (char *)malloc(MAX_PATH);
								chdir(STARTING_PATH);
								
								if(access("path.txt", F_OK)== 0){
									FILE * fpath = fopen("path.txt", "r");
									fscanf(fpath, "%s\n", security_check_path);
									fclose(fpath);
									
								} else {
									const char *md = "APPDATA";
									char *appdata = getenv(md);
									strcpy(security_check_path, appdata);
									
								}
								
								chdir(FULL_PATH);
								chdir("..");
								
								//Git cur_path
								char * SEC_PATH = (char *)malloc(MAX_PATH);
								getcwd(SEC_PATH, MAX_PATH);
								
								//Check if we on the right path :>
								if(strcmp(security_check_path, SEC_PATH)== 0)
								passed_security_check1 = true;
								
								chdir(LOCAL_PATH);
								chdir("..");
								
								//Git cur_path
								memset(SEC_PATH, '\0', strlen(SEC_PATH));
								getcwd(SEC_PATH, MAX_PATH);
								
								const char *md = "LOCALAPPDATA";
								char *localappdata = getenv(md);
								strcpy(security_check_path, localappdata);
								
								//Check if we on the right path :>
								if(strcmp(security_check_path, SEC_PATH)== 0)
								passed_security_check2 = true;
								
								free(SEC_PATH);
								free(security_check_path);
								
								chdir(FULL_PATH);
								chdir("..");
								
								if(passed_security_check1 && passed_security_check2){
									system("rmdir /s /q LIVING_DELUSION");
									
									chdir(LOCAL_PATH);
									chdir("..");
									system("rmdir /s /q LIVING_DELUSION");
									
									yellow;
									MidScreenText("Bye :>");
									white;
									sleep(2);
									exit(0);
									
								} else {
									//Error handling goes brrrrrrrrrr
									red;
									CenterText("Some files were not deleted due to a vulnerability detected");
									CenterText("If this error persists, please visit this folder(s) and check for anything out of place:");
									
									char * SEC_PATH = (char *)malloc(MAX_PATH);
									
									//Depends on the cur situation lul
									if(!passed_security_check1){
										const char *md = "APPDATA";
										char *appdata = getenv(md);
										strcpy(SEC_PATH, appdata);
										CenterText(SEC_PATH);
										
									} else if(!passed_security_check2){
										const char *md = "LOCALAPPDATA";
										char *localappdata = getenv(md);
										strcpy(SEC_PATH, localappdata);
										CenterText(SEC_PATH);
										
									} else {
										const char *md = "APPDATA";
										char *appdata = getenv(md);
										strcpy(SEC_PATH, appdata);
										CenterText(SEC_PATH);
										
										const char *md2 = "LOCALAPPDATA";
										char *localappdata = getenv(md2);
										strcpy(SEC_PATH, localappdata);
										CenterText(SEC_PATH);
										
									}
									
									white;
									free(SEC_PATH);
									Small_stop;
								}
								
							} else if(strcmp(Input, "nevermind")== 0){
								leave = true; break;
								
							} else {
								Error;
							}
						
						}
						
					} else if(strcmp(Input, "no")== 0){
						CLR; break;
						
					} else {
						Error;
					}
					
					if(leave)
					break;

				}
				
			} else if(strcmp(Input, "back")== 0){
				
			} else {
				Error;
			}
			
		}
		
	} else if (strcmp(Input, "back")== 0){
	    CLR; break;
	    
	} else { Error; }
	
	}

}

int Act1(){
    CLR;
    
    char chap1_input1 [20], chap1_input2 [20], chap1_mini_input1 [1];
    
    //story line vars
    char sent_by_wizard [5];
    
    if (!skip_intro){
    	yellow;
	    MidScreenText("Distant Worlds");
	    white;
	    sleep(5);
	    Art("Act1", 0);
	    sleep(5);
	    Small_stop;
	    
	    while(true){
		    printf("You wake up deep in the water, the light is getting smaller and smaller by the second\n");
		    printf("What are you going to do?\n");
		    printf(">Swim\n");
		    printf(">Stay\n");
		    String_Input;
		    
		    if (strcmp(Input, "swim")== 0){
		        printf("You swam back to the surface"); break;
		        
		    } else if (strcmp (Input, "stay")== 0){
		        printf("You decide to stay for some time to just enjoy the view but get bored and swim up\n"); break;
		        
		    } else { Error; } 
			
		}
    
    } else if (skip_intro){ }
    
    printf("You look around and find yourself in a cave with a small Village a Bottomless pit and 3 Statues\n");
    sleep(3);
    while(true){
        CLR;
        printf("Where are you going?\n");
        printf(">Village\n");
        printf(">Pit\n");
        printf(">Statues\n");
        String_Input;
        
        if (strcmp(Input, "pit")== 0){
        
        while (true){
        CLR;
        chap1_mini_input1 [1] = '\0'; 
        printf("You set foot and not while after you reach the Pit\n");
        printf("There is a voice from inside you saying \"JUMP OFF, JUMP OFF\"\n");
        printf("Do it?\n");
        printf("[Y] [N]\n");
        String_Input;
        
        if(strcmp (Input, "y")== 0){
           
		   	//Get current pit_jumps in diferent situations
			int pit_jumps = 0;
			ChangeCurPath("ACHIVEMENTS.Progress");
			if(access("PitJumps.txt", F_OK)== 0){
				FILE * fpitj = fopen("PitJumps.txt", "r");
				fscanf(fpitj, "%d", &pit_jumps);
				fclose(fpitj);
			} else {
				ChangeCurPath("ACHIVEMENTS.Done");
				if(access("PitJumps.txt", F_OK)== 0){
					FILE * fpitj = fopen("PitJumps.txt", "r");
					fscanf(fpitj, "%d", &pit_jumps);
					fclose(fpitj);
				} else {
					FILE * fpitj = fopen("PitJumps.txt", "w");
					fprintf(fpitj, "0");
					fclose(fpitj);
				}
			}
			
			//Gib 1 more pit jump 
			pit_jumps ++;
			
			FILE * fpitj = fopen("PitJumps.txt", "w");
			fprintf(fpitj, "%d", pit_jumps);
			fclose(fpitj);
		   	
		   	//Achivement on 25 pit jumps
            if(pit_jumps == 25){ 
            	yellow;
				printf("[ACHIVEMENT] _> \"Ah sh*t here we go again\" (Jump in the pit 25 times)\n"); 
				white;
				
				//Remove progress file because its no longer needed
				remove("PitJumps.txt");
				
				//Register pit jumps lul
				ChangeCurPath("ACHIVEMENTS.Done");
				FILE * fpitj = fopen("PitJumps.txt", "w");
				fprintf(fpitj, "%d\n", pit_jumps);
				fclose(fpitj);
			}
			
            printf("You jumped and...\n");
            sleep(2); CLR; 
            
			Pit();
			break;
        
        } else if (strcmp(Input, "n")== 0){
            
            printf("You decided not to jump, yet\n"); break;
            
        } else { Error; } 
		
		}
        
    } else if (strcmp(Input, "village")== 0){
    	
        CLR;
		
		//Let us know what day and hour rn
        short int crt_hour = TimeCalc("CHECK", 0, 1, 0);

        long int crt_day = TimeCalc("CHECK", 0, 0, 1);
        
        while(true){
	        CLR;
			printf("You walk towards the village and encounter various signs pointing to-\n");
	        printf(">Oracle [Teller]\n");
	        //printf(">Village Square [Center]\n");
	        printf(">Herb Garden [Garden]\n");
	        printf(">Magicians Chambers [Wizard]\n");
	        printf(">Scriptorium [Library]\n");
	        printf(">Tavern [Hotel]\n");
	        printf(">Back\n");
	        printf("Where to?\n");
	        String_Input;
	        
	        if (strcmp(Input,"teller")== 0 || strcmp(Input, "sw")== 0){
	        	
	        	Teller();
	        
	        } else if (strcmp(Input,"garden")== 0 || strcmp(Input, "nnw")== 0){
	            
	            Garden();
	                    
	        } else if (strcmp (Input,"wizard")== 0 || strcmp(Input, "se")== 0){
	            
	            Wizard();
	        
	        } else if (strcmp (Input, "library")== 0 || strcmp(Input, "nne")== 0){
	            
	            Library();
	        
	        } else if (strcmp(Input, "hotel")== 0 || strcmp(Input, "wsw")== 0){
	        	
	        	Hotel();
	    
			} else if(strcmp(Input, "back")== 0)
				break;
				
			else { Error; }
	        
        }
        
    } else if (strcmp(Input, "statues")== 0){
        	
        CLR;
        printf("Some type of ritual, creepy\n");
        
        //Get custom glitched name for the ritual god or smt
        short int num_spaces = 1;
        char *returned_string = EncryptedWordsV1(&num_spaces);
        printf("[NPC] %s: \"Prove your worth\"\n", returned_string);
        free(returned_string);
        
        while(true){
	        printf(">Prove\n");
	        printf(">Do not [Back]\n");
	        String_Input;
	        
	        if(strcmp(Input, "prove")== 0){
	        	printf("Implemented in BETA 3 (sorry)\n");
	        	Small_stop;
	        	break;
	        	
			} else if(strcmp(Input, "back")== 0){
				CLR; break;
				
			} else { Error; }
	        
    	}
    	
    } else { Error; }
    
} 

}

//Village Locations bellow 
void Teller(void){
	CLR;
	
	//Check if location is supost to be closed or not
	if(TimeCalc("CHECK", 0, 1, 0) >= 9 && TimeCalc("CHECK", 0, 1, 0) < 19){
	
		while(true){
			CLR;
		    printf("You enter the Oracle\n");
		    printf("[NPC] Futaba: \"Hello Adventurer, please put yours hands in the crystal ball\"\n");
		    printf("[NPC] Futaba: \"What do you wish to know?\"\n");
		    printf(">My goal [Goal]\n"); 
		    printf(">My quests [Quests]\n"); 
		    printf(">Inventory\n");
		    printf(">Completion\n"); 
		    printf(">Nevermind [Leave]\n"); 
		    String_Input;
		    
		    if(strcmp(Input, "Leave")!= 0){
		    	
		    	printf("[NPC] Futaba: \"Let the ball talk to you, focus your mind\"\n");
		    	sleep(1);
		    	
			}
			
		    if(strcmp(Input, "goal")== 0){
		    	
		    	//GET FROM FILE 
		    	
			} else if(strcmp(Input, "quests")== 0){
				
				printf("[???]: \"Active quests:\"\n"); sleep(1);
				
				if(strcmp(P1_quest, "YES")== 0){
					
					printf("[???]: \"Fix painting \"Rooten Skies\" is currently active.\"\n"); sleep(1);
					
				} if(strcmp(P2_quest, "YES")== 0){
					
					printf("[???]: \"Fix painting \"Dirty Kings\" is currently active.\"\n"); sleep(1);
					
				} if(strcmp(P3_quest, "YES")== 0){
					
					printf("[???]: \"Fix painting \"Falling\" is currently active.\"\n"); sleep(1);
					
				} if(strcmp(mint_q, "YES")== 0){
					
					printf("[???]: \"Give the wizard a mint \"potion\" quest is currently active\"\n"); sleep(1);
				}				
					
				if(num_quest_active == 0){
					
					printf("[???]: \"No quests active\"\n"); sleep(1);
					
				}
				
				
			} else if(strcmp(Input, "inventory")== 0){
				
				printf("[???]: \"Heres your inventory\"\n");
				sleep(1); 
				Inventory("SHOW", 0, 0);
				
			} else if(strcmp(Input, "completion")== 0){
				
				
				printf("[SYSTEM] _> NOT AVAILABLE IN BETA 2 (GAME NOT COMPLETE)\n");
				printf("[SYSTEM] _> Press anything to leave\n");
				getch();
				CLR;
				
			} else if(strcmp(Input, "leave")== 0){
				
				printf("[NPC] Futaba: \"I understand, you must go your way, take care\"\n"); sleep(2); CLR; break;
				
			} else { Error; }
		    
		}	//END LOOP HERE
	
	//Location closed
	} else {
		printf("[???]: \"Closed for now...\"");
		sleep(2);
		CLR;
	}
	
	CLR;
}

void Center(void){
	
	/*
	Note to reader:
	
	This function basicly calls annother function to display the items (DisplayCenterList)
	And that function returns the ID that the user wants
	with that ID we can get the BUY value and the SELL value (just open the file and display the pointer) 
	*/
	
	CLR;
	if(TimeCalc("CHECK", 0, 1, 0) < 13 && TimeCalc("CHECK", 0, 1, 0) >= 7){
		
		int Item_Id = 0, Item_Quant = 0, Item_Buy = 0, Item_Sell = 0, what_npc = 0;
		bool cant_skip = false, bought_item = true, can_pass = true;
		char temp_name [15];
		
		while(true){
			if(!bought_item || what_npc == 0){
				printf("What do you wish to buy?\n");
				printf(">Farming\n");
				printf(">Animal\n");
				printf(">Fish\n");
				printf(">Foraging\n");
				printf(">Extras\n");
				printf(">Leave\n");
				String_Input;
				what_npc = 0;
			}
			
			ChangeCurPath("STASH.Merchants");
			bought_item = true;
			
			if(strcmp(Input, "farming")== 0)
			what_npc = 1;
			
			else if(strcmp(Input, "animal")== 0)
			what_npc = 2;
			
			else if(strcmp(Input, "fish")== 0)
			what_npc = 3;
			
			else if(strcmp(Input, "foraging")== 0)
			what_npc = 4;
			
			else if(strcmp(Input, "extras")== 0)
			what_npc = 5;
			
			else if(strcmp(Input, "leave")== 0 || strcmp(Input, "back")== 0){
				
				printf("Back to the signs...\n"); sleep(2); CLR; break;
				
			} else {
				Error; bought_item = false; can_pass = false;
			}
			
			if(can_pass){
				
				/*
				Note to reader:
				
				Sorry this is kind of a mess with all the switch statements to get the desired output (npc dependant)
				*/
				
				Art("MERCHANT", what_npc);	
				
				char stash_file [10] = { '\0' }, temp_CHAR [2] = { '\0' };
				
				strcpy(stash_file, "Mer");
				itoa(what_npc, temp_CHAR, 10);
				strcat(stash_file, temp_CHAR);
				strcat(stash_file, ".txt");
				
				//1st greeting (no stash)
				if(access(stash_file, F_OK)!= 0){
					switch(what_npc){
						case 1:
							CenterText("[NPC] Anfigo: \"Here is what i buy and sell:\""); break;
						
						case 2:
							CenterText("[NPC] Synist: \"Here is the list of items that i buy and sell:\""); break;
							
						case 3:
							CenterText("[NPC] Lavist: \"Bellow lies a list of what i trade:\""); break;
							
						case 4:
							CenterText("[NPC] Firment: \"Welcome, please take a look at the list of items i trade:\""); break;
							
						case 5:
							CenterText("[NPC] Maidiste: \"I awaited you, see what i trade in this list:\""); break;
							
						default:
							break;
					}
					Small_stop;
				}
				
				while(true){
					//Has stash
					if(access(stash_file, F_OK)== 0){
						int mer_id, mer_quant;
						char * mer_itm_name;
						bool no_trades = true;
						
						mer_itm_name = GetItemName(mer_id);
						
						FILE * fmerstash = fopen(stash_file, "r");
						fscanf(fmerstash, "%d\n", &mer_id);
						fscanf(fmerstash, "%d\n", &mer_quant);
						fclose(fmerstash);
						
						while(true){
							switch(what_npc){
								case 1:
									printf("[NPC] Anfigo: \"I still have your %s (%dx) from earlier\"\n", mer_itm_name, mer_quant);
									printf("[NPC] Anfigo: \"What should i do with them?\"\n"); break;
								
								case 2:
									printf("[NPC] Synist: \"Hey, still have your %s (%dx) that you couldnt claim\"\n", mer_itm_name, mer_quant); 
									printf("[NPC] Synist: \"What should i do?\"\n"); break;
									
								case 3:
									printf("[NPC] Lavist: \"Please, i still have your %s (%dx) from our last meeting\"\n", mer_itm_name, mer_quant);
									printf("[NPC] Lavist: \"What do you wish to do with them?\"\n"); break;
									
								case 4:
									printf("[NPC] Firment: \"Hey friend, i still have your %s (%dx) from when we last meet\"\n", mer_itm_name, mer_quant);
									printf("[NPC] Firment: \"What should i do with these?\"\n"); break;
									
								case 5:
									printf("[NPC] Maidiste: \"Myself is still holding onto your %s (%dx).\"\n", mer_itm_name, mer_quant);
									printf("[NPC] Maidiste: \"I want knowledge on what to do now\"\n"); break;
								
								default:
									break;
							}
							printf("[Trash] [Hold] [Claim]\n");
							String_Input;
							
							//Delete file and forget ab stash
							if(strcmp(Input, "trash")== 0){
								switch(what_npc){
									case 1:
										printf("[NPC] Anfigo: \"More stock for me\"\n"); break;
									
									case 2:
										printf("[NPC] Synist: \"No need to replenish stock now\"\n"); break;
										
									case 3:
										printf("[NPC] Lavist: \"Very well. I will keep these for myself\"\n"); break;
										
									case 4:
										printf("[NPC] Firment: \"I will keep these for my stock, thank you very much\"\n"); break;
										
									case 5:
										printf("[NPC] Maidiste: \"Will keep.\"\n"); break;
										
									default:
										break;
								}
								
								ChangeCurPath("STASH.Merchants");
								remove(stash_file);
								
								free(mer_itm_name);
								no_trades = false;
								sleep(3);
								break;
							
							//Wait for stash claim and dont show menu
							} else if(strcmp(Input, "hold")== 0){
								switch(what_npc){
									case 1:
										printf("[NPC] Anfigo: \"Sure\"\n"); break;
									
									case 2:
										printf("[NPC] Synist: \"Ill wait for you\"\n"); break;
										
									case 3:
										printf("[NPC] Lavist: \"I will await you\"\n"); break;
										
									case 4:
										printf("[NPC] Firment: \"Very well, see you later\"\n"); break;
										
									case 5:
										printf("[NPC] Maidiste: \"I will await our next meeting\"\n"); break;
										
									default:
										break;
								}
								
								bought_item = false;
								what_npc = 0;
								sleep(2);
								free(mer_itm_name);
								break;
								
							} else if(strcmp(Input, "claim")== 0){
								switch(what_npc){
									case 1:
										printf("[NPC] Anfigo: \"Alright then...\"\n"); break;
									
									case 2:
										printf("[NPC] Synist: \"Lets try it then\"\n"); break;
										
									case 3:
										printf("[NPC] Lavist: \"Do you have the storage for it?\"\n"); break;
										
									case 4:
										printf("[NPC] Firment: \"Can you store it, friend?\"\n"); break;
										
									case 5:
										printf("[NPC] Maidiste: \"Will you be able to hold it?\"\n"); break;
										
									default:
										break;
								}
								sleep(2);
								
								int over = Inventory("CALC", mer_id, mer_quant);
								
								ChangeCurPath("STASH.Merchants");
								if(over > 0){
									switch(what_npc){
										case 1:
											printf("[NPC] Anfigo: \"Still have some left...\"\n"); break;
										
										case 2:
											printf("[NPC] Synist: \"Not quite enough\"\n"); break;
											
										case 3:
											printf("[NPC] Lavist: \"Not yet\"\n"); break;
											
										case 4:
											printf("[NPC] Firment: \"Sorry to tell you, thats not quite enough space\"\n"); break;
											
										case 5:
											printf("[NPC] Maidiste: \"Not.\"\n"); break;
											
										default:
											break;
									}
									
									//Update stash
									FILE * fmerstash = fopen(stash_file, "w");
									fprintf(fmerstash, "%d\n", mer_id);
									fprintf(fmerstash, "%d\n", over);
									fclose(fmerstash);
									
									bought_item = false;
									what_npc = 0;
									sleep(3);
									free(mer_itm_name);
									break;
												
								} else {
									remove(stash_file);
									switch(what_npc){
										case 1:
											printf("[NPC] Anfigo: \"You claimed the rest of your stash\"\n"); break;
										
										case 2:
											printf("[NPC] Synist: \"You claimed it!\"\n"); break;
											
										case 3:
											printf("[NPC] Lavist: \"Congratulations.\"\n"); break;
											
										case 4:
											printf("[NPC] Firment: \"Thats enough! Congrats!\"\n"); break;
											
										case 5:
											printf("[NPC] Maidiste: \"Enough.\"\n"); break;
											
										default:
											break;
									}
									
									no_trades = false;
									sleep(3);
									free(mer_itm_name);
									break;	
									
								}
								
							} else {
								Error;
							}
						
						}
						
						CLR;
						if(no_trades)
						break;
					}
				
					//Display stuff and get ID returned
					long int mer_day = -1;
					char cur_merchant [5] = { '\0' }, temp_char_again [2] = { '\0' };
					strcpy(cur_merchant, "mer");
					itoa(what_npc, temp_char_again, 10);
					strcat(cur_merchant, temp_char_again);
					
					//Get prices if they are saved in save file
					ChangeCurPath("OTHER.merprices");
					CatCurPath(cur_merchant);
					
					if(access("Day.txt", F_OK)== 0){
						FILE * fday = fopen("Day.txt", "r");
						fscanf(fday, "%d", &mer_day);
						fclose(fday);
						
						//Make new random buy and sell prices
						if(mer_day != TimeCalc("CHECK", 0, 0, 1)){
							FILE * fsetbuy = fopen("Buy.txt", "w");
							FILE * fsetsell = fopen("Sell.txt", "w");
							
							switch(what_npc){
								case 1: {
									for(int i = 0; i < 35; i ++){
										int next_buy = 0, next_sell = 0, temp_rand = rand()% 5 + 1;
										
										next_buy = (((i / 5) + 1) * 10) + temp_rand;
										temp_rand = rand()% 5 + 1;
										next_sell = next_buy - (temp_rand + 3);
									
										fprintf(fsetbuy, "%d\n", next_buy);
										fprintf(fsetsell, "%d\n", next_sell);
									}
									
									break;
								}
									
								case 2: {
									
									for(int i = 0; i < 9; i ++){
										int next_buy = 0, next_sell = 0, temp_rand = rand()% 5 + 1;
										
										next_buy = (((i / 3) + 1) * 20) + temp_rand;
										temp_rand = rand()% 5 + 1;
										next_sell = next_buy - (temp_rand + 12);	
															
										fprintf(fsetbuy, "%d\n", next_buy);
										fprintf(fsetsell, "%d\n", next_sell);
									}
									
									break;
								}
									
								case 3: {
									
									for(int i = 0; i < 48; i ++){
										int next_buy = 0, next_sell = 0, temp_rand = rand()% 5 + 1;
										
										next_buy = (((i / 6) + 1) * 10) + temp_rand;	
															
										//High rarity fish
										if((i + 1) % 5 == 0 || (i + 1) % 6 == 0)
										next_buy += 25;						
										
										temp_rand = rand()% 5 + 1;
										next_sell = next_buy - (temp_rand + 8);
										
										if(next_sell < 1)
										next_sell = 3;					
										
										fprintf(fsetbuy, "%d\n", next_buy);
										fprintf(fsetsell, "%d\n", next_sell);
									}
									
									break;
								}
									
								case 4: {
									
									for(int i = 0; i < 14; i ++){
										int next_buy = 0, next_sell = 0, temp_rand = rand()% 5 + 1;
										
										next_buy = (((i / temp_rand) + 1) * 7) + temp_rand;
										
										//Stick (lmao)
										if(i == 0)
										next_buy = 5;
										
										//Special Items
										if(i == 6 || i == 8 || i == 11 || i == 13)
										next_buy += 50;
										
										temp_rand = rand()% 5 + 1;
										next_sell = next_buy - (temp_rand + 8);
										
										if(next_sell < 1)
										next_sell = 3;
										
										if(i == 0)
										next_sell = 2;
										
										fprintf(fsetbuy, "%d\n", next_buy);
										fprintf(fsetsell, "%d\n", next_sell);
									}
									
									break;
								}
									
								case 5: {
									
									for(int i = 0; i < 8; i ++){
										int next_buy = 0, next_sell = 0, temp_rand = rand()% 5 + 1;
										
										next_buy = (i +  25) + temp_rand;
										
										//Leaves
										if(i == 0 || i == 7)
										next_buy = 60 - temp_rand;
										
										temp_rand = rand()% 5 + 1;
										next_sell = next_buy - (temp_rand + 8);
										
										if(next_sell < 1)
										next_sell = 3;
										
										fprintf(fsetbuy, "%d\n", next_buy);
										fprintf(fsetsell, "%d\n", next_sell);
									}
									
									break;
								}
									
								default:
									break;
							}
							
							fclose(fsetbuy);
							fclose(fsetsell);
						}
					}
					
					int returned_value = DisplayCenterList(cur_merchant);
					Item_Id = returned_value;
					
					if(returned_value == 0){
						switch(what_npc){
							case 1:
								CenterText("[NPC] Anfigo: \"Ok then, no items\""); break;
							
							case 2:
								CenterText("[NPC] Synist: \"No items then?\""); break;
							
							case 3:
								CenterText("[NPC] Lavist: \"Understood\"."); break;
								
							case 4:
								CenterText("[NPC] Firment: \"No items it is, have a good day\"\n"); break;
								
							case 5:
								CenterText("[NPC] Maidiste: \"I will wait for your return\"...\n"); break;
								
							default:
								break;
						}
						
						sleep(3);
						bought_item = false;
						what_npc = 0;
						CLR;
						
					}
				
				}
			}
			
			/*if(strcmp(Input, "farming")== 0 || what_npc == 1){
				Art("MERCHANT", 1);
				
				if(what_npc != 1 && access("Mer1.txt", F_OK)!= 0){
					CenterText("[NPC] Anfigo: \"Here is what i buy and sell:\"");
					Small_stop;
				}
				
				while(true){
					
					//Has stash
					if(access("Mer1.txt", F_OK)== 0){
						int mer_id, mer_quant;
						bool no_trades = true;
						
						FILE * fmerstash = fopen("Mer1.txt", "r");
						fscanf(fmerstash, "%d\n", &mer_id);
						fscanf(fmerstash, "%d\n", &mer_quant);
						fclose(fmerstash);
						
						while(true){
							//Decode unwanted ids
							printf("[NPC] Anfigo: \"I still have your %s (%dx) from earlier\"\n", GetItemName(mer_id - 1), mer_quant);
							printf("[NPC] Anfigo: \"What should i do with them?\"\n");
							printf("[Trash] [Hold] [Claim]\n");
							String_Input;
							
							//Delete file and forget ab stash
							if(strcmp(Input, "trash")== 0){
								printf("[NPC] Anfigo: \"More stock for me\"\n");
								
								ChangeCurPath("STASH.Merchants");
								remove("Mer1.txt");
								
								no_trades = false;
								sleep(3);
								break;
							
							//Wait for stash claim and dont show menu
							} else if(strcmp(Input, "hold")== 0){
								printf("[NPC] Anfigo: \"Sure\"\n");
								
								bought_item = false;
								what_npc = 0;
								sleep(2);
								break;
								
							} else if(strcmp(Input, "claim")== 0){
								printf("[NPC] Anfigo: \"Alright then...\"\n");
								sleep(2);
								
								int over = Inventory("CALC", mer_id, mer_quant);
								
								ChangeCurPath("STASH.Merchants");
								if(over > 0){
									printf("[NPC] Anfigo: \"Still have some left...\"\n");
									
									//Update stash
									FILE * fmerstash = fopen("Mer1.txt", "w");
									fprintf(fmerstash, "%d\n", mer_id);
									fprintf(fmerstash, "%d\n", over);
									fclose(fmerstash);
									
									bought_item = false;
									what_npc = 0;
									sleep(3);
									break;
												
								} else {
									remove("Mer1.txt");
									printf("[NPC] Anfigo: \"You claimed the rest of your stash\"\n");
									
									no_trades = false;
									sleep(3);
									break;	
									
								}
								
							} else {
								Error;
							}
						
						}
						
						CLR;
						if(no_trades)
						break;
					}
					
					long int mer_day = -1;
					
					//Get prices if they are saved in save file
					ChangeCurPath("OTHER.merprices.mer1");
					if(access("Day.txt", F_OK)== 0){
						FILE * fday = fopen("Day.txt", "r");
						fscanf(fday, "%d", &mer_day);
						fclose(fday);
						
						//Make new random buy and sell prices
						if(mer_day != TimeCalc("CHECK", 0, 0, 1)){
							FILE * fsetbuy = fopen("Buy.txt", "w");
							FILE * fsetsell = fopen("Sell.txt", "w");
							
							for(int i = 0; i < 35; i ++){
								int next_buy = 0, next_sell = 0, temp_rand = rand()% 5 + 1;
								
								next_buy = (((i / 5) + 1) * 10) + temp_rand;
								temp_rand = rand()% 5 + 1;
								next_sell = Item_Buy - (temp_rand + 3);
							
								fprintf(fsetbuy, "%d\n", next_buy);
								fprintf(fsetsell, "%d\n", next_sell);
							}
							
							fclose(fsetbuy);
							fclose(fsetsell);
						}
					}
					
					int returned_value = DisplayCenterList("mer1");
					Item_Id = returned_value;
					what_npc = 1;
					
					if(returned_value == 0){
						CenterText("[NPC] Anfigo: \"Ok then, no items\"");
						sleep(3);
						bought_item = false;
						what_npc = 0;
						CLR;
						
					} else {
						
					}
					
					if(!cant_skip)
					break;
					
				}
				
			} else if(strcmp(Input, "animal")== 0 || what_npc == 2){
				Art("MERCHANT", 2);
				if(what_npc != 2 && access("Mer2.txt", F_OK)!= 0){
					CenterText("[NPC] Synist: \"Here is the list of items that i buy and sell:\"");
					Small_stop;
				}
				
				char Animal_Names [9] [25] = {
					"Egg", "Wool", "Milk",
					"Flight Feather", "Down Feather", "Tail Feather",
					"Honey", "Pollen", "Beeswax"
				};
				
				bool has_spare_lines = true, has_spare_cols = true;
				
				//Git spare lines
				int spare_lines = GetTerminalSize("rows") - 15;
				if(spare_lines <= 0)
				has_spare_lines = false;
				
				//Git spare cols
				int spare_cols = GetTerminalSize("columns") - 52;
				spare_cols /= 2;
				if(spare_cols <= 0)
				has_spare_cols = false;
				
				//Arrays for later
				int Buy_Price [9], Sell_Price[9];
				char simple_names [9] [25];
				memset(simple_names, '\0', sizeof(simple_names));
				memset(Buy_Price, 0, sizeof(Buy_Price));
				memset(Sell_Price, 0, sizeof(Sell_Price));
				
				while(true){
					//Has stash
					if(access("Mer2.txt", F_OK)== 0){
						int mer_id, mer_quant;
						bool no_trades = true;
						
						FILE * fmerstash = fopen("Mer2.txt", "r");
						fscanf(fmerstash, "%d\n", &mer_id);
						fscanf(fmerstash, "%d\n", &mer_quant);
						fclose(fmerstash);
						
						while(true){
							//Decode unwanted ids
							if(mer_id < 42)
							printf("[NPC] Synist: \"Hey, still have your %s (%dx) that you couldnt claim\"\n", Animal_Names[mer_id - 36], mer_quant);
							
							else
							printf("[NPC] Synist: \"Hey, still have your %s (%dx) that you couldnt claim\"\n", Animal_Names[mer_id - 37], mer_quant);
							
							printf("[NPC] Synist: \"What should i do?\"\n");
							printf("[Trash] [Hold] [Claim]\n");
							String_Input;
							
							//Delete file and forget ab stash
							if(strcmp(Input, "trash")== 0){
								printf("[NPC] Synist: \"No need to replenish stock now\"\n");
								
								ChangeCurPath("STASH.Merchants");
								remove("Mer2.txt");
								
								no_trades = false;
								sleep(3);
								break;
							
							//Wait for stash claim and dont show menu
							} else if(strcmp(Input, "hold")== 0){
								printf("[NPC] Synist: \"Ill wait for you\"\n");
								
								bought_item = false;
								what_npc = 0;
								sleep(2);
								break;
								
							} else if(strcmp(Input, "claim")== 0){
								printf("[NPC] Synist: \"Lets try it then\"\n");
								sleep(2);
								
								int over = Inventory("CALC", mer_id, mer_quant);
								
								ChangeCurPath("STASH.Merchants");
								if(over > 0){
									printf("[NPC] Synist: \"Not quite enough\"\n");
									
									//Update stash
									FILE * fmerstash = fopen("Mer2.txt", "w");
									fprintf(fmerstash, "%d\n", mer_id);
									fprintf(fmerstash, "%d\n", over);
									fclose(fmerstash);
									
									bought_item = false;
									what_npc = 0;
									sleep(3);
									break;
												
								} else {
									remove("Mer2.txt");
									printf("[NPC] Synist: \"You claimed it!\"\n");
									
									no_trades = false;
									sleep(3);
									break;
									
								}
								
							} else {
								Error;
							}
						
						}
						
						CLR;
						if(no_trades)
						break;
					}
					
					char space = ' ', spare_char;
					int strlen_dif;
					
					//Starting stuff
					if(has_spare_lines){
						spare_lines /= 2;
						if(spare_lines % 2 != 0)
						spare_lines --;
					} else {
						spare_lines = 0;
					}
					
					if(!has_spare_cols){
						spare_cols = 0;
					}
					
					for(int z = 0; z < spare_lines; z ++)
					printf("\n");
					
					if(spare_cols % 2 == 0)
					spare_char = '\0';
					
					else
					spare_char = ' ';
					
					for(int z = 0; z < spare_lines; z ++)
					printf("\n");
					
					//%*c , spare_cols, spare_char
					printf("%*c|--------------------------------------------------|\n", spare_cols, spare_char);
					printf("%*c| [ID] | [NAME]    | [FULL NAME]    | [SELL / BUY] |\n", spare_cols, spare_char);
					printf("%*c|--------------------------------------------------|\n", spare_cols, spare_char);
					
					long int mer_day = -1;
					
					//Get prices if they are saved in save file
					ChangeCurPath("OTHER.merprices.mer2");
					if(access("Day.txt", F_OK)== 0){
						FILE * fday = fopen("Day.txt", "r");
						fscanf(fday, "%d", &mer_day);
						fclose(fday);
						
						FILE * fbuy = fopen("Buy.txt", "r");
						for(int i = 0; i < 9; i ++)
						fscanf(fbuy, "%d\n", &Buy_Price[i]);
						fclose(fbuy);
						
						FILE * fsell = fopen("Sell.txt", "r");
						for(int i = 0; i < 9; i ++)
						fscanf(fsell, "%d\n", &Sell_Price[i]);
						fclose(fsell);
					}
					
					for(int i = 0; i < 9; i ++){
						//Get 1st name of the crop
						char * after_conv = strchr(Animal_Names[i], space);
						
						if(after_conv != NULL)
						strlen_dif = strlen(Animal_Names[i]) - strlen(after_conv);
						
						else 
						strlen_dif = 0;
						
						memset(temp_name, '\0', sizeof(temp_name));
						
						if(strlen_dif > 0)
						strncpy(temp_name, Animal_Names[i], strlen_dif);
						
						else
						strcpy(temp_name, Animal_Names[i]);
						
						
						//Format to middle
						printf("%*c", spare_cols, spare_char);
						
						printf("| [0%d] |", i + 1);
						
						printf(" [%s]", temp_name);
						
						for(int j = 0; j < strlen(temp_name); j ++)
						temp_name[j] = tolower(temp_name[j]);
						
						strcpy(simple_names[i], temp_name);
						
						//Format stuff
						int numb_spaces = strlen(temp_name) - 8;
						numb_spaces = abs(numb_spaces);
						
						for(int j = 0; j < numb_spaces; j ++)
						printf(" ");
						
						printf("|");
												
						printf(" %s", Animal_Names[i]);
						
						//Get correct formating 
						numb_spaces = strlen(Animal_Names[i]) - 15;
						numb_spaces = abs(numb_spaces);
						
						for(int j = 0; j < numb_spaces; j ++)
						printf(" ");
						
						printf("|");
						
						if(mer_day != TimeCalc("CHECK",0 ,0, 1)){
							//Make prices (Slightly bad)
							int temp_rand = rand()% 5 + 1; 
							Item_Buy = (((i / 3) + 1) * 20) + temp_rand;
							temp_rand = rand()% 5 + 1;
							int temp_sell = Item_Buy - (temp_rand + 12);
							
							Buy_Price[i] = Item_Buy;
							Sell_Price[i] = temp_sell;
							
							if(temp_sell < 10)
							printf(" [0%d] | ", temp_sell);
							
							else
							printf(" [%d] | ", temp_sell);
							
							if(Item_Buy < 10)
							printf(" [0%d] |", Item_Buy);
							
							else
							printf(" [%d] |", Item_Buy);
						
						} else {
							if(Sell_Price[i] < 10)
							printf(" [0%d] | ", Sell_Price[i]);
							
							else
							printf(" [%d] | ", Sell_Price[i]);
							
							if(Buy_Price[i] < 10)
							printf(" [0%d] |", Buy_Price[i]);
							
							else
							printf(" [%d] |", Buy_Price[i]);
							
						}
						
						printf("\n");
					}
					printf("%*c|--------------------------------------------------|\n", spare_cols, spare_char);
					printf("%*c|       [Type Name or Item ID to select it]        |\n", spare_cols, spare_char);
					printf("%*c|--------------------------------------------------|\n", spare_cols, spare_char);
					
					for(int z = 0; z < spare_lines - 1; z ++)
					printf("\n");
					
					cant_skip = false;
					String_Input;
					
					short int hit_index;
					bool is_valid_arg = false;
					int * temp_int = (int *)malloc(2);
					
					//Is a digit?
					if(isdigit(Input[0])== 1){
						*temp_int = atoi(Input);
						//Check if its within limits
						if(*temp_int >= 1 && *temp_int <= 9)
						is_valid_arg = true;
						hit_index = *temp_int - 1;
						
					//Isnt a digit?
					} else {
						//Check if its a valid str inside arr
						for(int i = 0; i < 9; i ++){
							//Hit!
							if(strcmp(Input, simple_names[i])== 0){
								is_valid_arg = true;
								hit_index = i;
								break;
							}
						}
					}
					
					//Because ID 7 (aka 42) is invalid
					if(hit_index > 5)
					hit_index ++;
					
					free(temp_int);
					
					//Uhhh, register price in files (ur not getting cheaper prices LLLLLLLLLLLLL)
					if(mer_day != TimeCalc("CHECK",0 ,0, 1)){
						ChangeCurPath("OTHER.merprices.mer2");
						FILE * fday = fopen("Day.txt", "w");
						fprintf(fday, "%d\n", TimeCalc("CHECK", 0, 0, 1));
						fclose(fday);
						
						//(Cause i called TimeCalc) and it auto switched to TIME path, need to change again
						ChangeCurPath("OTHER.merprices.mer2");
						
						FILE * fbuy = fopen("Buy.txt", "w");
						for(int i = 0; i < 9; i ++)
						fprintf(fbuy, "%d\n", Buy_Price[i]);
						fclose(fbuy);
						
						FILE * fsell = fopen("Sell.txt", "w");
						for(int i = 0; i < 9; i ++)
						fprintf(fsell, "%d\n", Sell_Price[i]);
						fclose(fsell);
					}
					
					//Is valid? Set up arguments to buy or sell items selected
					if(is_valid_arg){
						what_npc = 2;
						Item_Buy = Buy_Price[hit_index];
						Item_Sell = Sell_Price[hit_index];
						Item_Id = hit_index + 36;
						break;
					}
					
					if(strcmp(Input, "back")== 0 || strcmp(Input, "leave")== 0){
						CenterText("[NPC] Synist: \"No items then?\"");
						sleep(3);
						bought_item = false;
						what_npc = 0;
						CLR;
					} else {
						cant_skip = true; red;
						CenterText("[NPC] Synist: \"Type the id or the name of the item you want\" [Type \"back\" to leave]");
						white;
						Small_stop;
					}
					
					if(!cant_skip)
					break;
					
				}
				
			} else if(strcmp(Input, "fish")== 0 || what_npc == 3){
				Art("MERCHANT", 3);
				if(what_npc != 3 && access("Mer3.txt", F_OK)!= 0){
					CenterText("[NPC] Lavist: \"Bellow lies a list of what i trade:\"");
					Small_stop;
				}
				
				char Fish_Names [48] [25] = {
					"? Trout", "Not a Trout", "Strange Trout", "Undefined Trout", "Lost Trout", "Unknown Trout",
					"Medium Bass", "Atomic Bass", "Enormous Bass", "Half Bass", "Big Bass", "Small Bass",
					"Lilac Carp", "Coral Carp", "Lime Carp", "Lavender Carp", "Rainbow Carp", "Fulvous Carp",
					"Wise Catfish", "Dumb Catfish", "Thinking Catfish", "Curious Catfish", "Happy Catfish", "Frowning Catfish",
					"Horizontal Shiner", "Vertical Shiner", "Oblique Shiner", "Non-Linear Shiner", "Upside-down Shiner", "Downside-up Shiner",
					"Fat Snapper", "Skinny Snapper", "Smooth Snapper", "Stiff Snapper", "Soft Snapper", "Rough Snapper",
					"Fast Tuna", "Slow Tuna", "Quick Tuna", "Dull Tuna", "Speedy Tuna", "Delayed Tuna",
					"Commun Salmon", "Uncommun Salmon", "Rare Salmon", "Epic Salmon", "Legendary Salmon", "Mythical Salmon",
				};
				
				bool has_spare_lines = true, has_spare_cols = true;
				
				//Git spare lines
				int spare_lines = GetTerminalSize("rows") - 54;
				if(spare_lines <= 0)
				has_spare_lines = false;
				
				//Git spare cols
				int spare_cols = GetTerminalSize("columns") - 61;
				spare_cols /= 2;
				if(spare_cols <= 0)
				has_spare_cols = false;
				
				//Arrays for later
				int Buy_Price [48], Sell_Price[48];
				char simple_names [48] [25];
				memset(simple_names, '\0', sizeof(simple_names));
				memset(Buy_Price, 0, sizeof(Buy_Price));
				memset(Sell_Price, 0, sizeof(Sell_Price));
				
				while(true){
					//Has stash
					if(access("Mer3.txt", F_OK)== 0){
						int mer_id, mer_quant;
						bool no_trades = true;
						
						FILE * fmerstash = fopen("Mer3.txt", "r");
						fscanf(fmerstash, "%d\n", &mer_id);
						fscanf(fmerstash, "%d\n", &mer_quant);
						fclose(fmerstash);
						
						while(true){
							//Decode unwanted ids
							if(mer_id < 52)
							printf("[NPC] Lavist: \"Please, i still have your %s (%dx) from our last meeting\"\n", Fish_Names[mer_id - 47], mer_quant);
							
							else {
								int inv_id_calc = (mer_id - 47) / 6;
								printf("[NPC] Lavist: \"Please, i still have your %s (%dx) from our last meeting\"\n", Fish_Names[(mer_id - inv_id_calc) - 47], mer_quant);
							}
							
							printf("[NPC] Lavist: \"What do you wish to do with them?\"\n");
							printf("[Trash] [Hold] [Claim]\n");
							String_Input;
							
							//Delete file and forget ab stash
							if(strcmp(Input, "trash")== 0){
								printf("[NPC] Lavist: \"Very well. I will keep these for myself\"\n");
								
								ChangeCurPath("STASH.Merchants");
								remove("Mer3.txt");
								
								no_trades = false;
								sleep(3);
								break;
							
							//Wait for stash claim and dont show menu
							} else if(strcmp(Input, "hold")== 0){
								printf("[NPC] Lavist: \"I will await you\"\n");
								
								bought_item = false;
								what_npc = 0;
								sleep(2);
								break;
								
							} else if(strcmp(Input, "claim")== 0){
								printf("[NPC] Lavist: \"Do you have the storage for it?\"\n");
								sleep(2);
								
								int over = Inventory("CALC", mer_id, mer_quant);
								
								ChangeCurPath("STASH.Merchants");
								if(over > 0){
									printf("[NPC] Lavist: \"Not yet\"\n");
									
									//Update stash
									FILE * fmerstash = fopen("Mer3.txt", "w");
									fprintf(fmerstash, "%d\n", mer_id);
									fprintf(fmerstash, "%d\n", over);
									fclose(fmerstash);
									
									bought_item = false;
									what_npc = 0;
									sleep(3);
									break;
												
								} else {
									remove("Mer3.txt");
									printf("[NPC] Lavist: \"Congratulations.\"\n");
									
									no_trades = false;
									sleep(3);
									break;
									
								}
								
							} else {
								Error;
							}
						
						}
						
						CLR;
						if(no_trades)
						break;
					}
					
					char space = ' ', spare_char;
					int strlen_dif;
					
					//Starting stuff
					if(has_spare_lines){
						spare_lines /= 2;
						if(spare_lines % 2 != 0)
						spare_lines --;
					} else {
						spare_lines = 0;
					}
					
					if(!has_spare_cols){
						spare_cols = 0;
					}
					
					for(int z = 0; z < spare_lines; z ++)
					printf("\n");
					
					if(spare_cols % 2 == 0)
					spare_char = '\0';
					
					else
					spare_char = ' ';
					
					for(int z = 0; z < spare_lines - 1; z ++)
					printf("\n");
					
					printf("%*c|-----------------------------------------------------------|\n", spare_cols, spare_char);
					printf("%*c| [ID] | [NAME]        | [FULL NAME]        | [SELL / BUY]  |\n", spare_cols, spare_char);
					printf("%*c|-----------------------------------------------------------|\n", spare_cols, spare_char);
					
					long int mer_day = -1;
					
					//Get prices if they are saved in save file
					ChangeCurPath("OTHER.merprices.mer3");
					if(access("Day.txt", F_OK)== 0){
						FILE * fday = fopen("Day.txt", "r");
						fscanf(fday, "%d", &mer_day);
						fclose(fday);
						
						FILE * fbuy = fopen("Buy.txt", "r");
						for(int i = 0; i < 48; i ++)
						fscanf(fbuy, "%d\n", &Buy_Price[i]);
						fclose(fbuy);
						
						FILE * fsell = fopen("Sell.txt", "r");
						for(int i = 0; i < 48; i ++)
						fscanf(fsell, "%d\n", &Sell_Price[i]);
						fclose(fsell);
					}
					
					for(int i = 0; i < 48; i ++){
						//Get 1st name of the crop
						char * after_conv = strchr(Fish_Names[i], space);
						
						if(after_conv != NULL)
						strlen_dif = strlen(Fish_Names[i]) - strlen(after_conv);
						
						else 
						strlen_dif = 0;
						
						memset(temp_name, '\0', sizeof(temp_name));
						
						if(strlen_dif > 0)
						strncpy(temp_name, Fish_Names[i], strlen_dif);
						
						else
						strcpy(temp_name, Fish_Names[i]);
						
						//Format to middle
						printf("%*c", spare_cols, spare_char);
						
						if(i < 9)
						printf("| [0%d] |", i + 1);
						
						else
						printf("| [%d] |", i + 1);
						
						printf(" [%s]", temp_name);
						
						for(int j = 0; j < strlen(temp_name); j ++)
						temp_name[j] = tolower(temp_name[j]);
						
						strcpy(simple_names[i], temp_name);
						
						//Format stuff 
						int numb_spaces = strlen(temp_name) - 12;
						numb_spaces = abs(numb_spaces);
						
						for(int j = 0; j < numb_spaces; j ++)
						printf(" ");
						
						printf("|");
												
						printf(" %s", Fish_Names[i]);
						
						//Get correct formating 
						numb_spaces = strlen(Fish_Names[i]) - 19;
						numb_spaces = abs(numb_spaces);
						
						for(int j = 0; j < numb_spaces; j ++)
						printf(" ");
						
						printf("|");
						
						if(mer_day != TimeCalc("CHECK",0 ,0, 1)){
							//Make prices (Slightly bad)
							int temp_rand = rand()% 5 + 1; 
							Item_Buy = (((i / 6) + 1) * 10) + temp_rand;
							
							//High rarity fish
							if((i + 1) % 5 == 0 || (i + 1) % 6 == 0)
							Item_Buy += 25;
							
							temp_rand = rand()% 5 + 1;
							int temp_sell = Item_Buy - (temp_rand + 8);
							
							if(temp_sell < 1)
							temp_sell = 3;
							
							Buy_Price[i] = Item_Buy;
							Sell_Price[i] = temp_sell;
							
							if(temp_sell < 10)
							printf(" [00%d] |", temp_sell);
							
							else if(temp_sell < 100)
							printf(" [0%d] |", temp_sell);
							
							else
							printf(" [%d] |", temp_sell);
							
							if(Item_Buy < 10)
							printf(" [00%d] |", Item_Buy);
							
							else if(Item_Buy < 100)
							printf(" [0%d] |", Item_Buy);
							
							else
							printf(" [%d] |", Item_Buy);
						
						} else {
							if(Sell_Price[i] < 10)
							printf(" [00%d] |", Sell_Price[i]);
							
							else if(Sell_Price[i] < 100)
							printf(" [0%d] |", Sell_Price[i]);
							
							else
							printf(" [%d] |", Sell_Price[i]);
							
							if(Buy_Price[i] < 10)
							printf(" [00%d] |", Buy_Price[i]);
							
							else if(Buy_Price[i] < 100)
							printf(" [0%d] |", Buy_Price[i]);
							
							else
							printf(" [%d] |", Buy_Price[i]);
								
						}
						
						printf("\n");
					}
					
					printf("%*c|-----------------------------------------------------------|\n", spare_cols, spare_char);
					printf("%*c|  [Type the ID or the Name of the item you want to select] |\n", spare_cols, spare_char);
					printf("%*c|-----------------------------------------------------------|\n", spare_cols, spare_char);
					
					for(int z = 0; z < spare_lines - 1; z ++)
					printf("\n");
					
					cant_skip = false;
					String_Input;
					
					short int hit_index;
					bool is_valid_arg = false;
					int * temp_int = (int *)malloc(2);
					
					//Is a digit?
					if(isdigit(Input[0])== 1){
						*temp_int = atoi(Input);
						//Check if its within limits
						if(*temp_int >= 1 && *temp_int <= 48)
						is_valid_arg = true;
						hit_index = *temp_int - 1;
						
					//Isnt a digit?
					} else {
						//Check if its a valid str inside arr
						for(int i = 0; i < 48; i ++){
							//Hit!
							if(strcmp(Input, simple_names[i])== 0){
								is_valid_arg = true;
								hit_index = i;
								break;
							}
						}
					}
					
					free(temp_int);
					
					//Uhhh, register price in files (ur not getting cheaper prices LLLLLLLLLLLLL)
					if(mer_day != TimeCalc("CHECK",0 ,0, 1)){
						ChangeCurPath("OTHER.merprices.mer3");
						FILE * fday = fopen("Day.txt", "w");
						fprintf(fday, "%d\n", TimeCalc("CHECK", 0, 0, 1));
						fclose(fday);
						
						//(Cause i called TimeCalc) and it auto switched to TIME path, need to change again
						ChangeCurPath("OTHER.merprices.mer3");
						
						FILE * fbuy = fopen("Buy.txt", "w");
						for(int i = 0; i < 48; i ++)
						fprintf(fbuy, "%d\n", Buy_Price[i]);
						fclose(fbuy);
						
						FILE * fsell = fopen("Sell.txt", "w");
						for(int i = 0; i < 48; i ++)
						fprintf(fsell, "%d\n", Sell_Price[i]);
						fclose(fsell);
					}
					
					//Calculate if cur index is part of the list of invalids (5 / 11 / 17 / 23 / 29 / 35 / 41)
					int inv_index = hit_index / 6;
					
					//Is valid? Set up arguments to buy or sell items selected
					if(is_valid_arg){
						what_npc = 3;
						Item_Buy = Buy_Price[hit_index];
						Item_Sell = Sell_Price[hit_index];
						//Add decoder id for blacklisted items
						Item_Id = hit_index + 47 + inv_index;
						break;
					}
					
					if(strcmp(Input, "back")== 0 || strcmp(Input, "leave")== 0){
						CenterText("[NPC] Lavist: \"Understood\".");
						sleep(3);
						bought_item = false;
						what_npc = 0;
						CLR;
					} else {
						cant_skip = true; red;
						CenterText("[NPC] Lavist: \"I cannot understand what you want, type the ID or the Name of the item you wish\" [Type \"back\" to leave]");
						white;
						Small_stop;
					}
					
					if(!cant_skip)
					break;
				}
				
			} else if(strcmp(Input, "foraging")== 0 || what_npc == 4){
				Art("MERCHANT", 4);
				if(what_npc != 4 && access("Mer4.txt", F_OK)!= 0){
					CenterText("[NPC] Firment: \"Welcome, please take a look at the list of items i trade:\"");
					Small_stop;
				}
				
				char Foraging_Names [14] [25] = {
					"Stick",
					"Pine Log", "Hickory Log", "Birch Log",
					"Ash Log", "Willow Log",
					"Bird Nest",
					"Mapple Log",
					"Pinecone",
					"Acacia Log", "Oak Log",
					"Medronhos Fruit",
					"Mimosa Log",
					"Jackfruit"
				};
				
				bool has_spare_lines = true, has_spare_cols = true;
				
				//Git spare lines
				int spare_lines = GetTerminalSize("rows") - 20;
				if(spare_lines <= 0)
				has_spare_lines = false;
				
				//Git spare cols
				int spare_cols = GetTerminalSize("columns") - 56;
				spare_cols /= 2;
				if(spare_cols <= 0)
				has_spare_cols = false;

				//Arrays for later
				int Buy_Price [14], Sell_Price[14];
				char simple_names [14] [25];
				memset(simple_names, '\0', sizeof(simple_names));
				memset(Buy_Price, 0, sizeof(Buy_Price));
				memset(Sell_Price, 0, sizeof(Sell_Price));
				
				while(true){
					//Has stash
					if(access("Mer4.txt", F_OK)== 0){
						int mer_id, mer_quant;
						bool no_trades = true;
						
						FILE * fmerstash = fopen("Mer4.txt", "r");
						fscanf(fmerstash, "%d\n", &mer_id);
						fscanf(fmerstash, "%d\n", &mer_quant);
						fclose(fmerstash);
						
						while(true){
							//Decode unwanted ids
							printf("[NPC] Firment: \"Hey friend, i still have your %s (%dx) from when we last meet\"\n", Foraging_Names[mer_id - 102], mer_quant);
							printf("[NPC] Firment: \"What should i do with these?\"\n");
							printf("[Trash] [Hold] [Claim]\n");
							String_Input;
							
							//Delete file and forget ab stash
							if(strcmp(Input, "trash")== 0){
								printf("[NPC] Firment: \"I will keep these for my stock, thank you very much\"\n");
								
								ChangeCurPath("STASH.Merchants");
								remove("Mer4.txt");
								
								no_trades = false;
								sleep(3);
								break;
							
							//Wait for stash claim and dont show menu
							} else if(strcmp(Input, "hold")== 0){
								printf("[NPC] Firment: \"I will await you\"\n");
								
								bought_item = false;
								what_npc = 0;
								sleep(2);
								break;
								
							} else if(strcmp(Input, "claim")== 0){
								printf("[NPC] Firment: \"Can you store it, friend?\"\n");
								sleep(2);
								
								int over = Inventory("CALC", mer_id, mer_quant);
								
								ChangeCurPath("STASH.Merchants");
								if(over > 0){
									printf("[NPC] Firment: \"Sorry to tell you, thats not quite enough space\"\n");
									
									//Update stash
									FILE * fmerstash = fopen("Mer4.txt", "w");
									fprintf(fmerstash, "%d\n", mer_id);
									fprintf(fmerstash, "%d\n", over);
									fclose(fmerstash);
									
									bought_item = false;
									what_npc = 0;
									sleep(3);
									break;
												
								} else {
									remove("Mer4.txt");
									printf("[NPC] Firment: \"Thats enough! Congrats!\"\n");
									
									no_trades = false;
									sleep(3);
									break;
									
								}
								
							} else {
								Error;
							}
						
						}
						
						CLR;
						if(no_trades)
						break;
					}
					
					char space = ' ', spare_char;
					int strlen_dif;
					
					//Starting stuff
					if(has_spare_lines){
						spare_lines /= 2;
						if(spare_lines % 2 != 0)
						spare_lines --;
					} else {
						spare_lines = 0;
					}
					
					if(!has_spare_cols){
						spare_cols = 0;
					}
					
					for(int z = 0; z < spare_lines; z ++)
					printf("\n");
					
					if(spare_cols % 2 == 0)
					spare_char = '\0';
					
					else
					spare_char = ' ';
					
					for(int z = 0; z < spare_lines; z ++)
					printf("\n");
					
					printf("%*c|------------------------------------------------------|\n", spare_cols, spare_char);
					printf("%*c| [ID] | [NAME]      | [FULL NAME]     | [SELL / BUY]  |\n", spare_cols, spare_char);
					printf("%*c|------------------------------------------------------|\n", spare_cols, spare_char);
					
					long int mer_day = -1;
					
					//Get prices if they are saved in save file
					ChangeCurPath("OTHER.merprices.mer4");
					if(access("Day.txt", F_OK)== 0){
						FILE * fday = fopen("Day.txt", "r");
						fscanf(fday, "%d", &mer_day);
						fclose(fday);
						
						FILE * fbuy = fopen("Buy.txt", "r");
						for(int i = 0; i < 14; i ++)
						fscanf(fbuy, "%d\n", &Buy_Price[i]);
						fclose(fbuy);
						
						FILE * fsell = fopen("Sell.txt", "r");
						for(int i = 0; i < 14; i ++)
						fscanf(fsell, "%d\n", &Sell_Price[i]);
						fclose(fsell);
					}
					
					for(int i = 0; i < 14; i ++){
						//Get 1st name of the crop
						char * after_conv = strchr(Foraging_Names[i], space);
						
						if(after_conv != NULL)
						strlen_dif = strlen(Foraging_Names[i]) - strlen(after_conv);
						
						else 
						strlen_dif = 0;
						
						memset(temp_name, '\0', sizeof(temp_name));
						
						if(strlen_dif > 0)
						strncpy(temp_name, Foraging_Names[i], strlen_dif);
						
						else
						strcpy(temp_name, Foraging_Names[i]);
						
						//Format to middle
						printf("%*c", spare_cols, spare_char);
						
						if(i < 9)
						printf("| [0%d] |", i + 1);
						
						else
						printf("| [%d] |", i + 1);
						
						printf(" [%s]", temp_name);
						
						for(int j = 0; j < strlen(temp_name); j ++)
						temp_name[j] = tolower(temp_name[j]);
						
						strcpy(simple_names[i], temp_name);
						
						//Format stuff 
						int numb_spaces = strlen(temp_name) - 10;
						numb_spaces = abs(numb_spaces);
						
						for(int j = 0; j < numb_spaces; j ++)
						printf(" ");
						
						printf("|");
												
						printf(" %s", Foraging_Names[i]);
						
						//Get correct formating 
						numb_spaces = strlen(Foraging_Names[i]) - 16;
						numb_spaces = abs(numb_spaces);
						
						for(int j = 0; j < numb_spaces; j ++)
						printf(" ");
						
						printf("|");
						
						if(mer_day != TimeCalc("CHECK",0 ,0, 1)){
							//Make prices (Slightly bad)
							int temp_rand = rand()% 5 + 1; 
							Item_Buy = (((i / temp_rand) + 1) * 7) + temp_rand;
							
							//Stick (lmao)
							if(i == 0)
							Item_Buy = 5;
							
							//Special Items
							if(i == 6 || i == 8 || i == 11 || i == 13)
							Item_Buy += 50;
							
							temp_rand = rand()% 5 + 1;
							int temp_sell = Item_Buy - (temp_rand + 8);
							
							if(temp_sell < 1)
							temp_sell = 3;
							
							if(i == 0)
							temp_sell = 2;
							
							Buy_Price[i] = Item_Buy;
							Sell_Price[i] = temp_sell;
							
							if(temp_sell < 10)
							printf(" [00%d] |", temp_sell);
							
							else if(temp_sell < 100)
							printf(" [0%d] |", temp_sell);
							
							else
							printf(" [%d] |", temp_sell);
							
							if(Item_Buy < 10)
							printf(" [00%d] |", Item_Buy);
							
							else if(Item_Buy < 100)
							printf(" [0%d] |", Item_Buy);
							
							else
							printf(" [%d] |", Item_Buy);
							
						} else {
							if(Sell_Price[i] < 10)
							printf(" [00%d] |", Sell_Price[i]);
							
							else if(Sell_Price[i] < 100)
							printf(" [0%d] |", Sell_Price[i]);
							
							else
							printf(" [%d] |", Sell_Price[i]);
							
							if(Buy_Price[i] < 10)
							printf(" [00%d] |", Buy_Price[i]);
							
							else if(Buy_Price[i] < 100)
							printf(" [0%d] |", Buy_Price[i]);
							
							else
							printf(" [%d] |", Buy_Price[i]);
								
						}
						
						printf("\n");
					}
					printf("%*c|------------------------------------------------------|\n", spare_cols, spare_char);
					printf("%*c|         [Type Name or Item ID to select it]          |\n", spare_cols, spare_char);
					printf("%*c|------------------------------------------------------|\n", spare_cols, spare_char);
					
					for(int z = 0; z < spare_lines - 1; z ++)
					printf("\n");
					
					cant_skip = false;
					String_Input;
					
					short int hit_index;
					bool is_valid_arg = false;
					int * temp_int = (int *)malloc(2);
					
					//Is a digit?
					if(isdigit(Input[0])== 1){
						*temp_int = atoi(Input);
						//Check if its within limits
						if(*temp_int >= 1 && *temp_int <= 14)
						is_valid_arg = true;
						hit_index = *temp_int - 1;
						
					//Isnt a digit?
					} else {
						//Check if its a valid str inside arr
						for(int i = 0; i < 14; i ++){
							//Hit!
							if(strcmp(Input, simple_names[i])== 0){
								is_valid_arg = true;
								hit_index = i;
								break;
							}
						}
					}
					
					free(temp_int);
					
					//Uhhh, register price in files (ur not getting cheaper prices LLLLLLLLLLLLL)
					if(mer_day != TimeCalc("CHECK",0 ,0, 1)){
						ChangeCurPath("OTHER.merprices.mer4");
						FILE * fday = fopen("Day.txt", "w");
						fprintf(fday, "%d\n", TimeCalc("CHECK", 0, 0, 1));
						fclose(fday);
						
						//(Cause i called TimeCalc) and it auto switched to TIME path, need to change again
						ChangeCurPath("OTHER.merprices.mer4");
						
						FILE * fbuy = fopen("Buy.txt", "w");
						for(int i = 0; i < 14; i ++)
						fprintf(fbuy, "%d\n", Buy_Price[i]);
						fclose(fbuy);
						
						FILE * fsell = fopen("Sell.txt", "w");
						for(int i = 0; i < 14; i ++)
						fprintf(fsell, "%d\n", Sell_Price[i]);
						fclose(fsell);
					}
					
					//Is valid? Set up arguments to buy or sell items selected
					if(is_valid_arg){
						what_npc = 4;
						Item_Buy = Buy_Price[hit_index];
						Item_Sell = Sell_Price[hit_index];
						Item_Id = hit_index + 102;
						break;
					}
	
					
					if(strcmp(Input, "back")== 0 || strcmp(Input, "leave")== 0){
						CenterText("[NPC] Firment: \"No items it is, have a good day\"\n");
						sleep(3);
						bought_item = false;
						what_npc = 0;
						CLR;
					} else {
						cant_skip = true; red;
						CenterText("[NPC] Firment: \"Hey, just type the ID or the Name of the item you want to get!\" [Type \"back\" to leave]");
						white;
						Small_stop;
					}
					
					if(!cant_skip)
					break;
				}
				
			} else if(strcmp(Input, "extras")== 0 || what_npc == 5){
				Art("MERCHANT", 5);
				if(what_npc != 5 && access("Mer5.txt", F_OK)!= 0){
					CenterText("[NPC] Maidiste: \"I awaited you, see what i trade in this list:\"");
					Small_stop;
				}
				
				char Extras_Names [8] [25] = {
					"Leaves", "Algae", "Duckweed", "Water Lily",
					"Snail", "Toad", "Frog", "Shrimp"
				};
				
				//Arrays for later
				int Buy_Price [8], Sell_Price[8];
				char simple_names [8] [25];
				memset(simple_names, '\0', sizeof(simple_names));
				memset(Buy_Price, 0, sizeof(Buy_Price));
				memset(Sell_Price, 0, sizeof(Sell_Price));
				
				bool has_spare_lines = true, has_spare_cols = true;
				
				//Git spare lines
				int spare_lines = GetTerminalSize("rows") - 14;
				if(spare_lines <= 0)
				has_spare_lines = false;
				
				//Git spare cols
				int spare_cols = GetTerminalSize("columns") - 50;
				spare_cols /= 2;
				if(spare_cols <= 0)
				has_spare_cols = false;
				
				while(true){
					//Has stash
					if(access("Mer5.txt", F_OK)== 0){
						int mer_id, mer_quant;
						bool no_trades = true;
						
						FILE * fmerstash = fopen("Mer5.txt", "r");
						fscanf(fmerstash, "%d\n", &mer_id);
						fscanf(fmerstash, "%d\n", &mer_quant);
						fclose(fmerstash);
						
						while(true){
							//Decode unwanted ids
							printf("[NPC] Maidiste: \"Myself is still holding onto your %s (%dx).\"\n", Extras_Names[mer_id - 126], mer_quant);
							printf("[NPC] Maidiste: \"I want knowledge on what to do now\"\n");
							printf("[Trash] [Hold] [Claim]\n");
							String_Input;
							
							//Delete file and forget ab stash
							if(strcmp(Input, "trash")== 0){
								printf("[NPC] Maidiste: \"Will keep.\"\n");
								
								ChangeCurPath("STASH.Merchants");
								remove("Mer5.txt");
								
								no_trades = false;
								sleep(3);
								break;
							
							//Wait for stash claim and dont show menu
							} else if(strcmp(Input, "hold")== 0){
								printf("[NPC] Maidiste: \"I will await our next meeting\"\n");
								
								bought_item = false;
								what_npc = 0;
								sleep(2);
								break;
								
							} else if(strcmp(Input, "claim")== 0){
								printf("[NPC] Maidiste: \"Will you be able to hold it?\"\n");
								sleep(2);
								
								int over = Inventory("CALC", mer_id, mer_quant);
								
								ChangeCurPath("STASH.Merchants");
								if(over > 0){
									printf("[NPC] Maidiste: \"Not.\"\n");
									
									//Update stash
									FILE * fmerstash = fopen("Mer5.txt", "w");
									fprintf(fmerstash, "%d\n", mer_id);
									fprintf(fmerstash, "%d\n", over);
									fclose(fmerstash);
									
									bought_item = false;
									what_npc = 0;
									sleep(3);
									break;
												
								} else {
									remove("Mer5.txt");
									printf("[NPC] Maidiste: \"Enough.\"\n");
									
									no_trades = false;
									sleep(3);
									break;
									
								}
								
							} else {
								Error;
							}
						
						}
						
						CLR;
						if(no_trades)
						break;
					}
					
					char space = ' ', spare_char;
					int strlen_dif;
					
					//Starting stuff
					if(has_spare_lines){
						spare_lines /= 2;
						if(spare_lines % 2 != 0)
						spare_lines --;
					} else {
						spare_lines = 0;
					}
					
					if(!has_spare_cols){
						spare_cols = 0;
					}
					
					for(int z = 0; z < spare_lines; z ++)
					printf("\n");
					
					if(spare_cols % 2 == 0)
					spare_char = '\0';
					
					else
					spare_char = ' ';
					
					for(int z = 0; z < spare_lines; z ++)
					printf("\n");
					
					printf("%*c|------------------------------------------------|\n", spare_cols, spare_char);
					printf("%*c| [ID] | [NAME]     | [FULL NAME]| [SELL / BUY]  |\n", spare_cols, spare_char);
					printf("%*c|------------------------------------------------|\n", spare_cols, spare_char);
					
					long int mer_day = -1;
					
					//Get prices if they are saved in save file
					ChangeCurPath("OTHER.merprices.mer5");
					if(access("Day.txt", F_OK)== 0){
						FILE * fday = fopen("Day.txt", "r");
						fscanf(fday, "%d", &mer_day);
						fclose(fday);
						
						FILE * fbuy = fopen("Buy.txt", "r");
						for(int i = 0; i < 8; i ++)
						fscanf(fbuy, "%d\n", &Buy_Price[i]);
						fclose(fbuy);
						
						FILE * fsell = fopen("Sell.txt", "r");
						for(int i = 0; i < 8; i ++)
						fscanf(fsell, "%d\n", &Sell_Price[i]);
						fclose(fsell);
					}
					
					for(int i = 0; i < 8; i ++){
						//Get 1st name of the crop
						char * after_conv = strchr(Extras_Names[i], space);
						
						if(after_conv != NULL)
						strlen_dif = strlen(Extras_Names[i]) - strlen(after_conv);
						
						else 
						strlen_dif = 0;
						
						memset(temp_name, '\0', sizeof(temp_name));
						
						if(strlen_dif > 0)
						strncpy(temp_name, Extras_Names[i], strlen_dif);
						
						else
						strcpy(temp_name, Extras_Names[i]);
						
						//Format to middle
						printf("%*c", spare_cols, spare_char);
						
						printf("| [0%d] |", i + 1);
						
						printf(" [%s]", temp_name);
						
						//Format stuff 
						int numb_spaces = strlen(temp_name) - 9;
						numb_spaces = abs(numb_spaces);
						
						for(int j = 0; j < numb_spaces; j ++)
						printf(" ");
						
						printf("|");
												
						printf(" %s", Extras_Names[i]);
						
						for(int j = 0; j < strlen(temp_name); j ++)
						temp_name[j] = tolower(temp_name[j]);
						
						strcpy(simple_names[i], temp_name);
						
						//Get correct formating 
						numb_spaces = strlen(Extras_Names[i]) - 11;
						numb_spaces = abs(numb_spaces);
						
						for(int j = 0; j < numb_spaces; j ++)
						printf(" ");
						
						printf("|");;
						
						if(mer_day != TimeCalc("CHECK",0 ,0, 1)){
						//Make prices (Slightly bad)
						int temp_rand = rand()% 5 + 1; 
						Item_Buy = (i +  25) + temp_rand;
						
						//Leaves
						if(i == 0 || i == 7)
						Item_Buy = 60 - temp_rand;
						
						temp_rand = rand()% 5 + 1;
						int temp_sell = Item_Buy - (temp_rand + 8);
						
						if(temp_sell < 1)
						temp_sell = 3;
						
						Buy_Price[i] = Item_Buy;
						Sell_Price[i] = temp_sell;
						
						if(temp_sell < 10)
						printf(" [00%d] |", temp_sell);
						
						else if(temp_sell < 100)
						printf(" [0%d] |", temp_sell);
						
						else
						printf(" [%d] |", temp_sell);
						
						if(Item_Buy < 10)
						printf(" [00%d] |", Item_Buy);
						
						else if(Item_Buy < 100)
						printf(" [0%d] |", Item_Buy);
						
						else
						printf(" [%d] |", Item_Buy);
						
						} else {
							if(Sell_Price[i] < 10)
							printf(" [00%d] |", Sell_Price[i]);
							
							else if(Sell_Price[i] < 100)
							printf(" [0%d] |", Sell_Price[i]);
							
							else
							printf(" [%d] |", Sell_Price[i]);
							
							if(Buy_Price[i] < 10)
							printf(" [00%d] |", Buy_Price[i]);
							
							else if(Buy_Price[i] < 100)
							printf(" [0%d] |", Buy_Price[i]);
							
							else
							printf(" [%d] |", Buy_Price[i]);
								
						}
						
						printf("\n");

					}
					printf("%*c|------------------------------------------------|\n", spare_cols, spare_char);
					printf("%*c|      [Type Name or Item ID to select it]       |\n", spare_cols, spare_char);
					printf("%*c|------------------------------------------------|\n", spare_cols, spare_char);
					
					for(int z = 0; z < spare_lines - 1; z ++)
					printf("\n");
					
					cant_skip = false;
					String_Input;
					
					short int hit_index;
					bool is_valid_arg = false;
					int * temp_int = (int *)malloc(2);
					
					//Is a digit?
					if(isdigit(Input[0])== 1){
						*temp_int = atoi(Input);
						//Check if its within limits
						if(*temp_int >= 1 && *temp_int <= 8)
						is_valid_arg = true;
						hit_index = *temp_int - 1;
						
					//Isnt a digit?
					} else {
						//Check if its a valid str inside arr
						for(int i = 0; i < 8; i ++){
							//Hit!
							if(strcmp(Input, simple_names[i])== 0){
								is_valid_arg = true;
								hit_index = i;
								break;
							}
						}
					}
					
					free(temp_int);
					
					//Uhhh, register price in files (ur not getting cheaper prices LLLLLLLLLLLLL)
					if(mer_day != TimeCalc("CHECK",0 ,0, 1)){
						ChangeCurPath("OTHER.merprices.mer5");
						FILE * fday = fopen("Day.txt", "w");
						fprintf(fday, "%d\n", TimeCalc("CHECK", 0, 0, 1));
						fclose(fday);
						
						//(Cause i called TimeCalc) and it auto switched to TIME path, need to change again
						ChangeCurPath("OTHER.merprices.mer5");
						
						FILE * fbuy = fopen("Buy.txt", "w");
						for(int i = 0; i < 8; i ++)
						fprintf(fbuy, "%d\n", Buy_Price[i]);
						fclose(fbuy);
						
						FILE * fsell = fopen("Sell.txt", "w");
						for(int i = 0; i < 8; i ++)
						fprintf(fsell, "%d\n", Sell_Price[i]);
						fclose(fsell);
					}
					
					//Is valid? Set up arguments to buy or sell items selected
					if(is_valid_arg){
						what_npc = 5;
						Item_Buy = Buy_Price[hit_index];
						Item_Sell = Sell_Price[hit_index];
						Item_Id = hit_index + 126;
						break;
					}
					
					if(strcmp(Input, "back")== 0 || strcmp(Input, "leave")== 0){
						CenterText("[NPC] Maidiste: \"I will wait for your return\"...\n");
						sleep(3);
						bought_item = false;
						what_npc = 0;
						CLR;
					} else {
						cant_skip = true; red;
						CenterText("[NPC] Maidiste: \"Type the ID or the Name of the item you want\"...");
						white;
						Small_stop;
					}
					
					if(!cant_skip)
					break;
				}
				
			} else if(strcmp(Input, "leave")== 0 || strcmp(Input, "back")== 0){
				
				printf("Back to the signs...\n"); sleep(2); CLR; break;
				
			} else {
				Error; bought_item = false;
			}*/
			
			//Had some trouble figuring out item ids by myself :sob:
			if(DEBUG_MODE)
			printf("[DEBUG] _> Item_Id? %d\n", Item_Id);
			
			if(bought_item){
				
				while(true){
					printf("How many items?\n");
					printf("&/");
					scanf("%d", &Item_Quant);
					
					CLR;
					
					if(Item_Quant <= 0){
						red;
						printf("Quantity must be positive. (and above 0)\n");
						white;
						sleep(2);
						CLR;
					} else {
						break;
					}
					
				}
				
				while(true){
					printf("Do you want to Buy or Sell?\n");
					String_Input;
					
					//Check the prices on the temp file put up by the display function
					ChangeCurPath("OTHER.temp");
					if(access("MerPriceInfo.txt", F_OK)== 0){
						FILE * fgetbuyandsell = fopen("MerPriceInfo.txt", "r");
						fscanf(fgetbuyandsell, "%d\n", &Item_Sell);			
						fscanf(fgetbuyandsell, "%d\n", &Item_Buy);
						fclose(fgetbuyandsell);	
						
						remove("MerPriceInfo.txt");
					}
					
					if(strcmp(Input, "buy")== 0){
						
						//Check for moni
						money -= Item_Buy * Item_Quant; 
						
						if(money >= 0){
							int pos_overflow = Inventory("CALC", Item_Id, Item_Quant);
							
							//Stash
							if(pos_overflow > 0){
								ChangeCurPath("STASH.Merchants");
								char temp_file [10] = "Mer";
								char temp_num [2] = {'\0'};
								itoa(what_npc, temp_num, 10);
								strcat(temp_file, temp_num);
								strcat(temp_file, ".txt");
								
								FILE * fmerstash = fopen(temp_file , "w");
								fprintf(fmerstash, "%d\n", Item_Id);
								fprintf(fmerstash, "%d\n", Item_Quant);
								fclose(fmerstash);
								
								red;
								printf("Not enough inventory space, will go to stash\n");
								white;
								bought_item = false;
								Small_stop;
								
							} else {
								yellow;
								printf("Bought.\n");
								white;
								Small_stop;
							}
							
						} else {
							red;
							printf("Not enough money.\n");
							money += Item_Buy * Item_Quant;
							white;
							Small_stop;
							
						}
						
						break;
						
					} else if(strcmp(Input, "sell")== 0){
						
						//SELL CASE
						bool has_items;
						Item_Quant = -Item_Quant;
						has_items = Inventory("CHECK", Item_Id, Item_Quant);
						
						//Has the items needed
						if(has_items){
							Inventory("CALC", Item_Id, Item_Quant);
							money += Item_Sell * abs(Item_Quant);
							yellow;
							printf("Sold.\n");
							white;
							Small_stop;
													
						//Dosent have the items needed	
						} else {
							red;
							printf("Not enough items.\n");
							white;
							Small_stop;
							
						}
						break;
						
					} else {
						Error;
					}
				
				}
				
				yellow;
				char temp_line [55] = "Money left? ";
				char money_temp [20];
				itoa(money, money_temp, 10);
				strcat(temp_line, money_temp);
				printf("%*s\n", ((GetTerminalSize("columns") - strlen(temp_line)) / 2) + strlen(temp_line), temp_line);
				white;
				Small_stop;	
			
			}
		}
		
	//Overtime 
	} else {
		printf("[NOTE]: \"We open up tomorrow at 7 again\"\n"); 
		sleep(1); 
		CLR; 
	}
}

void Garden(void){
	//Call Time function here
	CLR;
	
	if(TimeCalc("CHECK", 0, 1, 0) < 18 && TimeCalc("CHECK", 0, 1, 0) >= 6){
		
	    printf("You go to the Garden\n");
	    printf("The garden is a large area filled with crop fields and farm animals\n");
	    
	    while(true){
		    CLR;
		    printf("[NPC] Herman: \"Hello there, are you looking for something?\"\n");
		    printf(">I want to farm some crops [Crops]\n");
		    printf(">I want to get some animals [Animals]\n");
		    printf(">I want to visit the Stable [Stable]\n");
		    printf(">Nevermind [Back]\n");
		    String_Input;
		    
		    if(strcmp(Input, "crops")== 0){
		    	
				bool tut_needed = false;
				
				if(show_tut_cutscene){
					printf("STARTING TUTORIAL...\n\n");
					sleep(2);
				}
				CLR;
				
				//Call file to see if tutorial is alr done 
				ChangeCurPath("OTHER.tutorials");
				
				//Assit getting boolean values out of files
				short int * temp = (short int*)malloc(1);
				
				FILE * ftut = fopen("Crop.txt", "r");
				fscanf(ftut, "%d\n", temp);
				tut_needed = *temp;
				fclose(ftut);
				
				free(temp);
				
				if(!tut_needed)
				Crop(1, true);
				
				if(show_tut_cutscene){
					CLR;
					printf("STARTING MINI-GAME...\n\n");
					sleep(2);
				}
				
				CLR;
				Crop(1, false);
		        
			} else if (strcmp(Input, "animals")== 0){
				
				/*
				Inside StableInfo.txt:
				
				animal_day				[Integer]
				stable_has_stash		[Boolean] (True = Yes / False = No)
				has_animal				[Boolean] (True = Yes / False = No)
				animal_got				[Integer]
				animal_stash_id			[Integer]
				animal_stash_quantity 	[Integer]
				
				*/
				
				bool stable_has_stash, has_animal;
				short int animal_got;
				
				//making a teporary variable to assist getting the boolean values out of the file
				short int * temp = (short int*)malloc(1);
				
				//Check for stash
				ChangeCurPath("STASH.Animals");
				FILE * fstableinfo = fopen("StableInfo.txt", "r");
				fscanf(fstableinfo, "%d\n", &animal_day);
				fscanf(fstableinfo, "%d\n", temp);
				stable_has_stash = *temp;
				fscanf(fstableinfo, "%d\n", temp);
				has_animal = *temp;
				fclose(fstableinfo);
							
				//Checking if user alr colected an animal today
				if((animal_day != TimeCalc("CHECK", 0, 0, 1)) && !stable_has_stash && !has_animal){
					animal_day = TimeCalc("CHECK", 0, 0, 1);
					
					bool tut_needed = false;
					
					if(show_tut_cutscene){
						printf("STARTING TUTORIAL...\n\n");
						sleep(2);
					}
					
					CLR;
					
					//Call file to see if tutorial is alr done 
					ChangeCurPath("OTHER.tutorials");
					FILE * ftut = fopen("Animal.txt", "r");
					fscanf(ftut, "%d\n", temp);
					tut_needed = *temp;
					fclose(ftut);
					
					if(!tut_needed)
					Animal(true);
					
					//Start animal function with required arguments for Stable Animal type function
					if(show_tut_cutscene){
						printf("STARTING MINI-GAME...\n\n");
						sleep(2);
					}
					CLR;
					
					//Call function to begin mini game
					animal_got = Animal(false);
					
					if(animal_got == 1)
					strcpy(usr_animal, "Chicken");
					
					else if(animal_got == 2)
					strcpy(usr_animal, "Sheep");
					
					else if(animal_got == 3)
					strcpy(usr_animal, "Cow");
					
					else
					strcpy(usr_animal, "[UNDEFINED]");
					
					CLR;
					
					if(animal_got != 0){
						animal_day = TimeCalc("CHECK", 0, 0, 1);
					    printf("[NPC] Herman: \"You got a %s in the Stable! Good Job!\"\n", usr_animal);
					} else {
						printf("[NPC] Herman: \"Better luck next time i guess...\"\n");
					}
				    Small_stop;
					
					ChangeCurPath("STASH.Animals");
					fopen("StableInfo.txt", "w");
					rewind(fstableinfo);
					fprintf(fstableinfo, "%d\n", animal_day);
					fprintf(fstableinfo, "0\n");
					
					if(animal_got != 0)
					fprintf(fstableinfo, "1\n");
					else
					fprintf(fstableinfo, "0\n");
					
					fprintf(fstableinfo, "%d\n", animal_got);
					fprintf(fstableinfo, "0\n");
					fprintf(fstableinfo, "0\n");
					fclose(fstableinfo);
				
				//Possible errors
				} else {
					CLR;
					red;
					if(animal_day == TimeCalc("CHECK", 0, 0, 1))
					printf("You already got an Animal today!\n"); 
					
					else if(stable_has_stash)
					printf("You still have an item to pick up over at the stable!\n");
					
					else if(has_animal)
					printf("There is still an animal at the stable!\n");
					
					else
					printf("[SYSTEM] _> FILE ERR.");
					
					sleep(2);
					CLR;
					white;
				}
				
				free(temp);
		        //Animals input ends here
		        
		    } else if (strcmp(Input, "stable")== 0 ){
		    	
		    	int animal_day, animal_got, animal_stash_id, animal_stash_quantity;
		    	bool stable_has_stash, has_animal;
		    	
		    	//making a teporary variable to assist getting the boolean values out of the file
				short int * temp = (short int*)malloc(1);
		    	
		    	ChangeCurPath("STASH.Animals");
				FILE * fstableinfo = fopen("StableInfo.txt", "r");
				fscanf(fstableinfo, "%d\n", &animal_day);
				fscanf(fstableinfo, "%d\n", temp);
				stable_has_stash = *temp;
				fscanf(fstableinfo, "%d\n", temp);
				has_animal = *temp;
				fscanf(fstableinfo, "%d\n", &animal_got);
				fscanf(fstableinfo, "%d\n", &animal_stash_id);
				fscanf(fstableinfo, "%d\n", &animal_stash_quantity);
				fclose(fstableinfo);
				
				if(DEBUG_MODE){
					printf("[DEBUG] _> Animal day? %d\n", animal_day);
					printf("[DEBUG] _> Stable status? %d\n", stable_has_stash);
					printf("[DEBUG] _> Has animal? %d\n", has_animal);
					printf("[DEBUG] _> Animal got? %d\n", animal_got);
					printf("[DEBUG] _> Animal stash id? %d\n", animal_stash_id);
					printf("[DEBUG] _> Animal stash quantity? %d\n\n", animal_stash_quantity);
				}
		    	
		    	//If full (stable_has_stash = has stash and !has_animal = no animal inside)
		    	if(stable_has_stash && !has_animal && animal_stash_id != 0 && animal_stash_quantity != 0){
		    		while(true){
		    			CLR;
		    			
		    			if(animal_stash_id == 36)
		    			printf("[NPC] Herman: \"I still have your eggs\"\n");
		    			
		    			else if(animal_stash_id == 37)
						printf("[NPC] Herman: \"I still have your wool\"\n");
						
						else
						printf("[NPC] Herman: \"I still have your milk\"\n");
						 
					 
		    			printf("[NPC] Herman: \"So what do i do with them? [Leave] [Wait] [Colect]\"\n");
						String_Input;
								
						if(strcmp(Input, "leave")== 0){
									
							printf("[NPC] Herman: \"Hmm sure ill keep these for myself then\"\n");
							sleep(3);
							animal_stash_id = 0;
							animal_stash_quantity = 0;
							stable_has_stash = false;
							break;
									
						} else if(strcmp(Input, "wait")== 0){
									
							printf("[NPC] Herman: \"Alright, ill hold onto them for you\"\n");
							sleep(3);
							break;
									
						} else if(strcmp(Input, "colect")== 0){
							
							short int inv_overflow = Inventory("CALC", animal_stash_id, animal_stash_quantity);
							
							if(inv_overflow > 0){
								printf("[NPC] Herman: \"Looks like you couldnt fit the items in your inventory\"\n");
								sleep(3);
								animal_stash_quantity = inv_overflow;
								break;
									
							} else {
								printf("[NPC] Herman: \"Oh hey, you claimed the rest of the stash! Now you can continue getting animals\"\n");
								sleep(3);
								stable_has_stash = false;
								animal_stash_id = 0;
								animal_stash_quantity = 0;
								break;
								
							}
							
						} else { Error; }
						
					}
				
				ChangeCurPath("STASH.Animals");
				//Register new stuff in files
				FILE * fstableinfo = fopen("StableInfo.txt", "w");
				fprintf(fstableinfo, "%d\n", animal_day);
				fprintf(fstableinfo, "%d\n", stable_has_stash);
				fprintf(fstableinfo, "%d\n", has_animal);
				fprintf(fstableinfo, "%d\n", animal_got);
				fprintf(fstableinfo, "%d\n", animal_stash_id);
				fprintf(fstableinfo, "%d\n", animal_stash_quantity);
				fclose(fstableinfo);
		    	
				//Stash end	
				} else {
				
		    	if(!stable_has_stash && !has_animal){
		    		
		    		printf("[NPC] Herman: \"You do know you dont have any Animals to pick up here, right? But since we are here ill tell you about this\"\n");
		    		printf("[NPC] Herman: \"In this world, Animals are VERY limited so we dont kill them, we use the products they can give us and trow them back into the wild\"\n");
		    		printf("[NPC] Herman: \"So you colect Animals for us and we treat them and release them back into the wild, worry not though, we will give you items has a reward when we release them\"\n");
		    		printf("[NPC] Herman: \"Maybe come back when you get some Animals in here!\"\n\n");
		    		Small_stop;
				} else {
					
					//Items
					printf("[NPC] Herman: \"Oh hey, you came here to see your animal?\"\n");
					printf("You nod and follow Herman\n");
					
					if(animal_day != TimeCalc("CHECK", 0, 0, 1)){
						
						has_animal = false;
						printf("[NPC] Herman: \"We released your animal after a day or two but since you got it for us, heres part of what it gave us\"\n");
						
						animal_stash_id = 35 + animal_got;
						
						//Diferent msg dending on animal
						if(animal_got == 1){
							printf("[NPC] Herman: \"Here, 2 eggs for your efforts\"\n");
							animal_stash_quantity = 2;
							
						} else if(animal_got == 2){
							printf("[NPC] Herman: \"Here, 3 wools for your efforts\"\n");
							animal_stash_quantity = 3;
							
						} else if(animal_got == 3){
							printf("[NPC] Herman: \"Here, 2 jars of milk for your efforts\"\n");
							animal_stash_quantity = 2;
							
						}
						sleep(2);
						
						short int inv_overflow = Inventory("CALC", animal_stash_id, animal_stash_quantity);
						
						if(inv_overflow > 0){
							printf("[NPC] Herman: \"Looks like your inventory was full, ill hold onto these for now\"\n");
							sleep(3);
							animal_stash_quantity = inv_overflow;
							stable_has_stash = true;
							CLR;
					
						} else {
							printf("[NPC] Herman: \"Enjoy the items and see you later then!\"\n");
							printf("You nod and leave\n");
							stable_has_stash = false;
							sleep(3); 
							CLR;
							
					    }
						
						//Animal is no longer with us 
						animal_got = 0;
						ChangeCurPath("STASH.Animals");
						//Register new stuff in files
						FILE * fstableinfo = fopen("StableInfo.txt", "w");
						fprintf(fstableinfo, "%d\n", animal_day);
						fprintf(fstableinfo, "%d\n", stable_has_stash);
						fprintf(fstableinfo, "%d\n", has_animal);
						fprintf(fstableinfo, "%d\n", animal_got);
						fprintf(fstableinfo, "%d\n", animal_stash_id);
						fprintf(fstableinfo, "%d\n", animal_stash_quantity);
						fclose(fstableinfo);
							
					} else {
						printf("[NPC] Herman: \"So your animal is still here, we havent found an oportunity to release it so, maybe next day\"\n");
						printf("You nod and go back\n");
						sleep(3); 
						CLR;
						
					}
					
				}
				
			}
			
			free(temp);
				
			} else if (strcmp(Input, "back")== 0){
		        
		        char skip_vil [2];
		        printf("[NPC] Herman: \"See you soon then!\"\n");
		        printf("You go back to the signs.\n");
		        break;
		        
		    } else { Error; }
	    			
	    }
	   
	//Overtime 
	} else { 
		printf("[NOTE] :\"Sorry we are closed, come back at 6 next day\"\n"); 
		sleep(1); 
		CLR; 
	}	
}

void Wizard(void){
	CLR;
	
	if(TimeCalc("CHECK", 0, 1, 0) >= 22 || TimeCalc("CHECK", 0, 1, 0) < 6){
        
        bool wiz_1st_time, mint_q_done, has_secret_book = false;
        
        //Checking triggers
        ChangeCurPath("OTHER.triggers.other");
        
        //Check if file DOSENT exist
        if(access("Wizard.txt", F_OK)!= 0){
        	//1st time going here? Set it up for save
			FILE * fwiztrig = fopen("Wizard.txt", "w");
			fprintf(fwiztrig, "0\n");
			fprintf(fwiztrig, "1\n");
			fclose(fwiztrig);
			wiz_1st_time = true;
			
			//Set up quest too
			ChangeCurPath("QUESTS.Main");
			FILE * fwizquest = fopen("Wizard.txt", "w");
			fprintf(fwizquest, "0");
			fclose(fwizquest);
			mint_q_done = false;
			
		} else {
			short int * temp = (short int*)malloc(1);
			//Get trigger status
			FILE * fwiztrig = fopen("Wizard.txt", "r");
			fscanf(fwiztrig, "%d\n", temp);
			wiz_1st_time = *temp;
			fclose(fwiztrig);
			
			//Get current story quest status
			ChangeCurPath("QUESTS.Main");
			FILE * fwizquest = fopen("Wizard.txt", "r");
			fscanf(fwizquest, "%d", temp);
			mint_q_done = *temp;
			fclose(fwizquest);
			free(temp);
		}
		
		//Check if user has secret book from library
		ChangeCurPath("OTHER.books");	
		if(access("SecretLib.txt", F_OK)== 0){
			FILE * fsctbook = fopen("SecretLib.txt", "r");
			fscanf(fsctbook, "%d\n", &has_secret_book);
			fclose(fsctbook);
		}
		
        CLR;
        if(wiz_1st_time){
        	
	        printf("You set foot for the so called \"Magicians Chambers\"\n");
	        printf("Inside, you find a an old man wispering something while reading a book\n");
	        printf("You aproach him and...\n");
	        printf("[NPC] Boise: \"Oh hello there, im a little bit sick, could you bring me a Mint tea? Ill anwser your questions after\"\n");// (Mint tea should be underlined)
	        printf("You nod and leave\n");
	        wiz_1st_time = false;
	        Small_stop;  
			
			//Register started quest
	 		ChangeCurPath("QUESTS.Started");
	 		FILE * fnewq = fopen("Wizard.txt", "w");
	 		fprintf(fnewq, "-");
	 		fclose(fnewq);
     		
   		} else {
    	
    		//Call inv.
	    	if(!mint_q_done){
	    		
	    		//boolean
	    		bool has_mint_tea = Inventory("CHECK", 117, -1);
	    		
	    		if(has_mint_tea){
	    			//Ask if user wants to give
	    			while(true){
	    				CLR;
		    			printf("You have a mint tea, do you want to give it to Boise? [YES] [NO]\n");
		    			String_Input;
		    			
		    			if(strcmp(Input, "yes")== 0)
		    			break;
		    			
		    			else if(strcmp(Input, "no")== 0)
		    			return;
		    			
		    			else
		    			Error;
					}
	    			
	    			Inventory("CALC", 117, -1);
	    			printf("You give the mint tea to Boise...\n");
	    			printf("[NPC] Boise: \"Ah thanks, i knew i count on you\"\n");
	    			mint_q_done = true; 
	    			
	    			//Quest done so get em out of here
	    			ChangeCurPath("QUESTS.Started");
	    			remove("Wizard.txt");
				} else {
					
					printf("[NPC] Boise: \"Mint Tea, dont forget...\"\n");
					printf("[HELP] _> (The alchemist in the Library Sells it)\n");
				}
				
				Small_stop;
			} else {
				
				while(true){
					printf("[NPC] Boise: \"What do you need?\"\n");
					printf(">About the pit... [Pit]\n");
					//FUNCTION TO CHECK IF USER HAS MEET WIZARDS BROTHER
					//STORY LINE CHECKS
					if(has_secret_book)
					printf(">About this book i found... [Book]\n");					
					
					printf(">Nevermind [Back]\n");
					String_Input;
					
					if(strcmp(Input, "pit")== 0){
						
						printf("[NPC] Boise: \"Oh the pit?\"\n");
						printf("[NPC] Boise: \"Its basicly an expantion to the cave but time tends to get 2 times faster inside, so we opted to stay here rather than there\"\n");
						printf("[NPC] Boise: \"Although its an expantion of our cave, it has a beautifull ecosystem, but because of the time speeding up inside it we dont dare to enter it\"\n");
						printf("[NPC] Boise: \"But ill get you in on a little secret, my long lost brother was an explorer and he decided to enter the pit, \"For a few days!\", he said but he never came back\"\n");
						printf("[NPC] Boise: \"Im comfident he is still alive because i casted him a spell to make him age 5 times slower but, the pit is a dangerous place\"\n");
						printf("[NPC] Boise: \"I wont try to stop you, my brother even promissed to help newcomers traverse the pit, if you decide to jump, look for a house there and tell him i sent you\"\n");
						printf("[NPC] Boise: \"Good luck! (If you dare to go in, that is)\"\n");
						
						Small_stop;
						
						//Register change in file (no need for variable)
						ChangeCurPath("OTHER.triggers.story");
						FILE * fwizstory = fopen("WizardSpecifics.txt", "w");
						fprintf(fwizstory, "1");
						fclose(fwizstory);
						
					} else if(strcmp(Input, "book")== 0){
						
						if(has_secret_book){
							
							CLR;
							printf("[NPC] Boise: \"A book you say? Show me, ill try to figure it out if you cant\"\n");
							printf("[NPC] Boise: \"Oh...its Celestia again, what a name, she was a powerfull wizard, and my first love...time change, well now that you reminded me i might has well give you some backstory\"\n");
							printf("[NPC] Boise: \"Celestia was an interesting person, she always had a sponge brain and loved to learn about all sorts of things\"\n");
							printf("[NPC] Boise: \"She was my friend and she started asking me about wizard and magic stuff\"\n");
							printf("[NPC] Boise: \"And like the dumbass i was at the time i took her to the library section all about magic, even lended her some of my notes\"\n");
							printf("[NPC] Boise: \"Slowly, she started learning magic and we became lovers but in a heated discussion she decided to use what she learned for bad\"\n");
							printf("[NPC] Boise: \"She went to the bottom of the pit with a \"master plan\" in mind\"\n");
							printf("[NPC] Boise: \"Now i do not remember what this master plan was but she was talking about \"breaking out of this game\" i do not know what she was on about\"\n");
							printf("[NPC] Boise: \"That could very well be a sign of insanity or a sign that she learned something that the others dont\"\n");
							printf("[NPC] Boise: \"My point being, try not to aproach her, she is very dangerous, even more with the powers she learned over the years studying\"\n");
							printf("[NPC] Boise: \"But, if you feel the need to be suicidal and try to end her \"master plan\" i can try to help you, whoever you need to know a little more, go explore the pit or something\"\n");
							printf("[NPC] Boise: \"I hope you arent crazy enough to go after her but we never know, adventurers are always such dumb humans, hehe, go explore the world\"\n\n");
							Small_stop;
						
						}
						
					} else if (strcmp(Input, "back")== 0){
						
						printf("Going back..."); sleep(1); CLR; break;
						
					} else { Error; }
				
			}
				
			}
		
		}
		
		//Register progress made in file
      	ChangeCurPath("OTHER.triggers.other");
	  	FILE * fwiztrig = fopen("Wizard.txt", "w");
		fprintf(fwiztrig, "%d\n", wiz_1st_time);
		fclose(fwiztrig);
		
		//Register quest progress
		ChangeCurPath("QUESTS.Main");
		FILE * fwizquest = fopen("Wizard.txt", "w");
		fprintf(fwizquest, "%d", mint_q_done);
		fclose(fwizquest);
			
    } else { printf("[NPC] Arche: \"Sorry, Boise is asleep right now, he only works during the night\"\n"); sleep(1); CLR; }
}

void Library(void){
	CLR;

    //Limit hours you can enter here
    if(TimeCalc("CHECK", 0, 1, 0) >= 10 && TimeCalc("CHECK", 0, 1, 0) < 20){
    bool Lib_tut = false;
    
    //Check if alr done
    ChangeCurPath("OTHER.triggers.other");
    if(access("LibraryDone.txt", F_OK)== 0){
    	FILE * flibdone = fopen("LibraryDone.txt", "r");
    	fscanf(flibdone, "%d", &Lib_tut);
    	fclose(flibdone);
	}
    
    if(!Lib_tut){
	    while(true){
		    CLR;
		    printf("You enter the Scriptorium and are stumbled with huge bookshelfs\n");
		    printf("Pick one at random? [Y] [N]\n");
		    String_Input;
		    
	        if(strcmp(Input, "y")== 0){
	            
	            if (rand()% 2 + 1 == 1){
	                
	                printf("You got the book!\n");
	                printf("You open it up and it starts like:\n");
	                printf("\"Once upon a time, there was a flower girl named Lily. She had a magical ability to make flowers bloom with just a touch. Every day, she would wander through the meadows, spreading beauty and joy with"); 
	                printf("her enchanting gift. People from all around would come to see her, amazed by the vibrant colors and sweet fragrances that filled the air. The flowers loved Lily as much as she loved them, and together, they created a world of endless beauty.\"\n");
	                printf("Eventually you get bored and ask the Librarian, Sarah for something to read\n\n");
	                printf("[NPC] Sarah: \"Hmm, something to read? Im not sure what you like but i can take you to a place\"\n");
	                printf("You follow her into the Monastic Cell\n");
	                printf("[NPC] Sarah: \"There are tons of books here so pick a few of your liking, see you around\"\n");
	                Lib_tut = true; break;
	                
	            } else {
	                
	                printf("You fell down and got back up with the help of the Librarian, Sarah\n");
	                printf("[NPC] Sarah: \"You took quite the fall, are you ok?\"\n");
	                printf("You awnser \"Yes im fine, i will be more carefull next time\"\n");
	                printf("She replies,\"Go to the book noot, maybe you will find what you need there\"\n");
	                printf("You nod and go to the book noot\n");
	                Lib_tut = true; break;
	            
	            } 
	            
	        } else if (strcmp(Input, "n")== 0){
	            
	            printf("You decide not to and aproach the Librarian, Sarah, for help\n\n");
	            printf("[NPC] Sarah: \"Where to find books? You dont seem much of a book worm to me but sure, follow me\"\n");
	            printf("You follow her to the Monastic Cell\n");
	            printf("[NPC] Sarah: \"Well here we are, pick a book of your liking, ill see you around\"\n");
	            Lib_tut = true; break;
	            
	        } else { Error; }
		    
	    }
	    
	    Small_stop;
	    
	    while(true){
	    	CLR;
	        printf("You go trough some of the books and find some titles that perk your eyes.\n");
	        printf(">\"The Enchanted Garden\" [Garden]\n");
	        printf(">\"Whispers of the Wind\" [Wind]\n");
	        printf(">\"The Secret Library\" [Library]\n");
	        printf(">\"Shadows of Imagination\" [Imagination]\n");
	        printf(">\"Pages of Destiny\" [Destiny]\n");
	        String_Input;
	        
	        if(strcmp(Input, "garden")== 0){
	            
	            printf("You picked up \"The Enchanted Garden\"\n");
	            printf("A whimsical sanctuary where nature's magic unfolds, captivating hearts and sparking imaginations. Within its enchanting embrace, \n");
	            printf("vibrant blooms and mystical creatures create a tapestry of wonder, inviting all to explore and dream. The air is alive with the sweet melodies of birdsong, \n");
	            printf("as if nature herself is serenading those who wander through this ethereal realm.\n");
	            break;
	            
	        } else if(strcmp(Input, "wind")== 0){
	            
	            printf("You picked up \"Whispers of the Wind\"\n");
	            printf("In a forgotten corner of the world, nestled among ancient trees, lies the mystical realm of \"Whispers of the Wind.\" \n");
	            printf("Here, gentle breezes carry secrets and tales untold, whispering through the leaves and guiding wanderers on their path. \n");
	            printf("Those who listen closely may hear the wind's ancient wisdom, a symphony of whispers that dances through the air, leaving a sense of wonder in its wake.\n");
	            break;
	            
	        } else if(strcmp(Input, "library")== 0){
	            
	            printf("You picked up \"The Secret Library\"\n");
	            printf("In the \"Secret Library,\" hidden within the depths of an ancient castle, forgotten knowledge awaits.\n");
	            printf("Dusty shelves hold countless books, their pages whispering tales of forgotten worlds and untold wisdom. \n");
	            printf("Those who dare to enter this sanctuary of knowledge may unlock the secrets that have been lost to time.\n");
	            printf("Has they say, only the Librarian has the key...\"SECRET\"\n");
	            break;
	            
	        } else if(strcmp(Input, "imagination")== 0){
	            
	            printf("You picked up \"Shadows of Imagination\"\n");
	            printf("In the \"Shadows of Imagination,\" where darkness and light intertwine, elusive figures emerge from the depths, shaping the dreams and fantasies of those who dare to explore.\n");
	            printf("Within this enigmatic space, shadows hold the power to transport us to unimaginable places, allowing us to experience the extraordinary and embrace the magic that lies within.\n");
	            break;
	            
	        } else if(strcmp(Input, "destiny")== 0){
	            
	            printf("You picked up \"Pages of Destiny\"\n");
	            printf("In the mystical \"Pages of Destiny,\" ancient tomes hold the secrets of fate, with each page revealing a unique chapter of one's journey.\n");
	            printf("As the pages turn, destinies intertwine, weaving a tapestry of choices, challenges, and triumphs.\n");
	            printf("Within these hallowed pages, the power to shape one's own narrative lies, waiting to be discovered by those who dare to seek their true path.\n");
	            break;
	            
	        } else { Error; }
	    }
	    
	    //Register inside trigger
	    ChangeCurPath("OTHER.triggers.other");
	    FILE * flibdone = fopen("LibraryDone.txt", "w");
	    fprintf(flibdone, "%d\n", Lib_tut);
	    fclose(flibdone);
	    
	    Small_stop;
	    
    }

    	while(true){
            CLR;
            printf("[NPC] Sarah: \"Where should i take you?\"\n");
            printf(">Scriptorium [Scriptorium]\n");
            printf(">Tapestry Room [Tapestry]\n");
            printf(">Alchemist's Corner [Alchemist]\n");
            printf(">Monastic Cell [Cell]\n");
            printf(">Back [Back]\n");
            String_Input;
            
            if(strcmp(Input, "scriptorium")== 0){
            	
                printf("[NPC] Sarah: \"Scriptorium? Im not sure why you would want to go there but ok\"\n\n");
                printf("You follow her into the Scriptorium\n\n");
                printf("[NPC] Sarah: \"Everything here is written by the monks, dont disturb the peace\"\n\n");
                printf("You look around and find theres nothing to be done here\n");
                printf("You decide to go back since it was just a bunch of monks writing\n\n");
                Small_stop;
                
            } else if(strcmp(Input, "tapestry")== 0){
                
                CLR;
                bool done_paintings[3], has_rq_itm_final = false, has_rq_itm[3], always_rq_itm, started_paint_q[3], file_removed = false;
                
                //Change dir
                ChangeCurPath("QUESTS.Other");
                
                //Check cur. quests done
                if(access("Paintings.txt", F_OK)== 0){
	                short int * temp = (short int*)malloc(1);
	                FILE * fpaintings = fopen("Paintings.txt", "r");
	                for(int i = 0; i < 3; i ++){
		                fscanf(fpaintings, "%d\n", temp);
		                done_paintings[i] = *temp;
	            	}
	            	fclose(fpaintings);
	            	free(temp);
            	}
                            
                //Git current started quest status :>
               	ChangeCurPath("QUESTS.Started");
               	if(access("Paintings.txt", F_OK)== 0){
	               	char temp_char [2];
	               	FILE * fnewq = fopen("Paintings.txt", "r");
	               	for(int i = 0; i < 3; i ++){
	               		fscanf(fnewq, "%s\n", &temp_char);
	               		if(temp_char[0] == '-')
	               		started_paint_q[i] = true;
	               		
	               		else
	               		started_paint_q[i] = false;
	            	}
	                fclose(fnewq);
            	} else 
            	memset(started_paint_q, false, sizeof(started_paint_q));
                
                //(All paintings check for 2 wools) (Refer to List of Quests) 
                //Set up 2 temp variables to check items
                
                //Check for 3 sticks / 5 mints 
                has_rq_itm[0] = Inventory("CHECK", 102, -3);
                has_rq_itm[1] = Inventory("CHECK", 3, -5);
                always_rq_itm = Inventory("CHECK", 37, -2);
                
                if(has_rq_itm[0] && has_rq_itm[1] && always_rq_itm)
                has_rq_itm_final = true;
                
                if(!done_paintings[0] && has_rq_itm_final && started_paint_q[0]){
						
					while(true){
						CLR;
						printf("[NPC] Sarah: \"Oh? You have enough items to finish the \"Rotten Skies\" art\"\n");
						printf("[NPC] Sarah: \"Do you want to finish it? [Y] [N]\n");
						String_Input;
						
						if(strcmp(Input, "y")== 0){
							Art("PAINT", 1);
							Small_stop;
							printf("[NPC] Sarah: \"Well then\"\n");
							printf("[NPC] Sarah: \"Here is your reward on the behalf of the monks\"\n");
							printf("+ 250 coins!\n");
							
							//Say bai bai to ur items :>
							Inventory("CALC", 102, -3);
							Inventory("CALC", 3, -5);
							Inventory("CALC", 37, -2);
							
							done_paintings[0] = true;
							money += 250; 
							printf("[INVENTORY] _> Items Updated!\n");
							Small_stop;
							break;
							
						} else if(strcmp(Input, "n")== 0){
							
							printf("[NPC] Sarah: \"I understand\"\n"); break;
							
						} else { Error; }
						
					}
                	
				}
				
				has_rq_itm_final = false;
				
				//Check for 3 Mapple Logs / 2 Pinecones and 1 Rainbow Carp
                has_rq_itm[0] = Inventory("CHECK", 109, -3);
                has_rq_itm[1] = Inventory("CHECK", 110, -2);
                has_rq_itm[2] = Inventory("CHECK", 65, -1);
                always_rq_itm = Inventory("CHECK", 37, -2);
                
                if(has_rq_itm[0] && has_rq_itm[1] && has_rq_itm[2] && always_rq_itm)
                has_rq_itm_final = true;
				
				if(!done_paintings[1] && has_rq_itm_final && started_paint_q[1]){
						
					while(true){
						CLR;
						printf("[NPC] Sarah: \"Oh? You have enough items to finish the \"Dirty Kings\" art\"\n");
						printf("[NPC] Sarah: \"Do you want to finish it? [Y] [N]\n");
						String_Input;
						
						if(strcmp(Input, "y")== 0){
							Art("PAINT", 2);
							Small_stop;
							printf("[NPC] Sarah: \"Well then\"\n");
							printf("[NPC] Sarah: \"Here is your reward on the behalf of the monks\"\n");
							printf("+ 1000 coins!\n");
							
							//Say bai bai to ur items :>
							Inventory("CALC", 109, -3);
							Inventory("CALC", 110, -2);
							Inventory("CALC", 65, -1);
							Inventory("CALC", 37, -2);
							
							done_paintings[1] = true;
							money += 1000; 
							printf("[INVENTORY] _> Items Updated!\n");
							Small_stop;
							break;
							
						} else if(strcmp(Input, "n")== 0){
							
							printf("[NPC] Sarah: \"I understand\"\n"); break;
							
						} else { Error; }
						
					}
					
				} 
				
				has_rq_itm_final = false;
				
				//Check for 3 Fast Tunas / 3 Epic Salmon and 2 Algae
                has_rq_itm[0] = Inventory("CHECK", 89, -3);
                has_rq_itm[1] = Inventory("CHECK", 99, -3);
                has_rq_itm[2] = Inventory("CHECK", 127, -2);
                always_rq_itm = Inventory("CHECK", 37, -2);
                
                if(has_rq_itm[0] && always_rq_itm)
                has_rq_itm_final = true;
				
				if(!done_paintings[2] && has_rq_itm_final && started_paint_q[2]){
						
					while(true){
						CLR;
						printf("[NPC] Sarah: \"Oh? You have enough items to finish the \"Falling\" art\"\n");
						printf("[NPC] Sarah: \"Do you want to finish it? [Y] [N]\n");
						String_Input;
						
						if(strcmp(Input, "y")== 0){
							Art("PAINT", 3);
							Small_stop;
							printf("[NPC] Sarah: \"Well then\"\n");
							printf("[NPC] Sarah: \"Here is your reward on the behalf of the monks\"\n");
							printf("+ 5000 coins!\n");
							
							//Say bai bai to ur items :>
							Inventory("CALC", 89, -3);
							Inventory("CALC", 99, -3);
							Inventory("CALC", 127, -2);
							Inventory("CALC", 37, -2);
							
							done_paintings[2] = true;
							money += 5000; 
							printf("[INVENTORY] _> Items Updated!\n");
							Small_stop;
							break;
							
						} else if(strcmp(Input, "n")== 0){
							
							printf("[NPC] Sarah: \"I understand\"\n"); break;
							
						} else { Error; }
						
					}
					
				} 
                
                ChangeCurPath("QUESTS.Other");
                
                //Register paitings done
                FILE * fpaintings = fopen("Paintings.txt", "w");
                for(int i = 0; i < 3; i ++)
	            fprintf(fpaintings, "%d\n", done_paintings[i]);
            	fclose(fpaintings);
                
                //Remove file of started quests if its alr done (space management)
                ChangeCurPath("QUESTS.Started");
                if(done_paintings[0] && done_paintings[1] && done_paintings[2]){
                	remove("Paintings.txt");
                	file_removed = true;
            	}
                
                CLR;
                printf("[NPC] Sarah: \"Tapestry? Hmm you like art?\"\n\n");
                printf("You nod and let her lead the way\n\n");
                printf("[NPC] Sarah: \"Some of these painting are nice decorations for your house, you can even try to get something done by them!\"\n\n");
                printf("You tour the place for a few minutes and quickly find a section with LOOTS of paintings\n");
                printf("There are some that are unfinished\n\n");
                
                while(true){
                	
                	//Add started quests stuff here :>
                    printf("Theres a small note on each one of them\n\n");
                    printf("[NOTE] _> \"2x Wools are required for each one of them\"\n");
                    printf("\"Rooten Skies\" - 3x Sticks & 5x Mints\n");
                    printf("\"Dirty Kings\" - 3x Maple logs & 2x Pinecones & 1x Rainbow Carp\n");
                    printf("\"Falling\" - 3x Fast Tuna & 3x Epic Salmon & 2x Algae\n");
                    printf("You think to yourself: \"Well these are materials that are pretty eazy to get (most of them)\"\n\n");
                    printf("Start painting quest(s)? [YES] [NO]\n");
                    String_Input;
                    
                    if(strcmp(Input, "yes")== 0){
                    	
                        while(true){
                            printf("What panting(s)? [Skies] [Kings] [Falling] [ALL] [Back]\n");
                            String_Input;
                            
                            if(strcmp(Input, "skies")== 0){
                            	
	                            if(started_paint_q[0]){
	                            	printf("You already started that quest!\n"); 
									sleep(1); 
									CLR; 
									break;
	                            		
								} else if (done_paintings[0]){
									printf("You already finished that quest!\n"); 
									sleep(1); 
									CLR; 
									break;
									
								} else {
		                            printf("Started the \"Rotten Skies\" Art quest!\n"); 
									started_paint_q[0] = true;
									sleep(2); 
									CLR; 
									break;
	                            }
                            
							} else if(strcmp(Input, "kings")== 0){
							
								if(started_paint_q[1]){
	                            	printf("You already started that quest!\n"); 
									sleep(1); 
									CLR;
									break;
	                            		
								} else if (done_paintings[1]){
									printf("You already finished that quest!\n"); 
									sleep(1); 
									CLR; 
									break;
									
								} else {
								    printf("Started the \"Dirty Kings\" Art quest!\n");
									started_paint_q[1] = true;
									sleep(2); 
									CLR; 
									break;
										
								}
								 
							} else if(strcmp(Input, "falling")== 0){
								
								if(started_paint_q[2]){
									printf("You already started that quest!\n"); 
									sleep(1); 
									CLR; 
									break;
									
								} else if (done_paintings[2]){
									printf("You already finished that quest!\n"); 
									sleep(1); 
									CLR; 
									break;
									
								} else {
									printf("Started the \"Falling\" Art quest!\n"); 
									started_paint_q[2] = true;
									sleep(2); 
									CLR; 
									break; 
								
								}
							
							} else if(strcmp(Input, "all")== 0){
								
								if(started_paint_q[0] && started_paint_q[1] && started_paint_q[2]){
									printf("You already started all quests!\n"); 
									sleep(1); 
									CLR; 
									break;
									
								} else if(done_paintings[0] && done_paintings[1] && done_paintings[2]){
									printf("You already all quests!\n"); 
									sleep(1); 
									CLR; 
									break;
									
								} else {
									printf("Started all painting quests!\n"); 
									for(int i = 0; i < 3; i ++)
									started_paint_q[i] = true;
									sleep(2); 
									CLR; 
									break; 
								
								}
								
							} else if(strcmp(Input, "back")== 0){
								printf("Going back...\n");
								sleep(1);
								CLR;
								break;
							
							} else { Error; }
                            
                    	}
                    
                    } else if(strcmp(Input, "no")== 0){
                        
                        printf("Maybe next time\n");
                        sleep(1);
                        break;
                        
                    } else { Error; }
                    
                }
                
                //Register new changes here :>
                if(!file_removed){
	                ChangeCurPath("QUESTS.Started");
	               	FILE * fnewq = fopen("Paintings.txt", "w");
	               	rewind(fnewq);
	               	for(int i = 0; i < 3; i ++){
	               		if(started_paint_q[i])
	               		fprintf(fnewq, "-\n");
	               		
	               		else
	               		fprintf(fnewq, "_\n");
	            	}
	                fclose(fnewq);
            	}
                
            } else if (strcmp(Input, "alchemist")== 0){
            	
                CLR;
                printf("Sarah takes you to the Alchemist's Corner\n");
                printf("[NPC] Sarah: \"Good luck out there, ive heard hes grummpy sometimes\"\n");
                printf("You nod and aproach the Alchemist\n");
                Small_stop;
                
                while(true){
                	bool wants_to_leave = false;
                	
                	CLR;
                    printf("[NPC] Grimold (Alchemist): \"HELLO??? WHO ARE YOU??\"\n");
                    printf(">I have a question about potions [Ask]\n");
                    printf(">I need help with potions [Pots]\n");
                    printf(">Sorry, wrong place [Back]\n");
                    String_Input
                    
                    if(strcmp(Input, "ask")== 0){
                    	
						while(true){
							printf("[NPC] Grimold: \"GO ON, ASK AWAY.\"\n");
							printf(">How long do potions normaly last? [Time]\n");
							printf(">Why are the items required to make a potion so specific? [Items]\n");
							printf(">Can you list me the effects of each potion? [Effects]\n");
							printf(">Nevermind [Back]\n");
							String_Input;
							
							if(strcmp(Input, "time")== 0){
								printf("[NPC] Grimold: \"POTIONS NORMALY LAST FOR A DAY, THERE IS NO OTHER WAY TO SURPASS THAT TIME.\"\n");
								Small_stop;
								
							} else if(strcmp(Input, "items")== 0){
								printf("[NPC] Grimold: \"BECAUSE I HAVE TO COMPRESS THE ITEMS INTO A FINE FORM, \"\n");
								printf("[NPC] Grimold: \"REACH THE REQUIRED CELULAR LEVEL TO BE SAFE, \"\n");
								printf("[NPC] Grimold: \"MIX IT WITH WATER, \"\n");
								printf("[NPC] Grimold: \"AND FEED MY CAT.\"\n");
								printf("[NPC] Grimold: \"(LAST STEP IS THE MOST IMPORTANT)\"\n");
								Small_stop;
								
							} else if(strcmp(Input, "effects")== 0){
								printf("[NPC] Grimold: \"LIST:\"\n\n");
								printf("Refresher \t\t| N/E (No effects)\n");
		                        printf("Mint Tea \t\t| PLACEHOLDER\n");
		                        printf("Woods Water \t\t| Rain and Thunder specific items are more commun\n");
		                        printf("Hidden Bush \t\t| 25%% chance to get double crops while playing the crop minigame\n");
		                        printf("Time Decline \t\t| Time is 50%% slower\n");
		                        printf("Happy Acident \t\t| Skip 2 hours\n");
		                        printf("Early Grave \t\t| Traps take LESS time to catch fish\n");
		                        printf("Lots of Fish Bones \t| PLACEHOLDER\n");
		                        printf("High Risk, Low Reward \t| 1/4 chance to begin thundering or else it rains\n");
		                        printf("Im Special! \t\t| Your dungeon statistics are buffered to max + 10\n\n");
								Small_stop;
								
							} else if(strcmp(Input, "back")== 0){
								
								CLR; break;
								
							} else {
								Error;
							}
							
						}
						
					} else if(strcmp(Input, "pots")== 0){
                    	
                    	int pot_id, temp, temp1;
						char pot_name [23];
						bool has_pot_stash = false, has_order_ready = false;
                    	
                    	ChangeCurPath("STASH.Potions");
                    	if(access("NotCollected.txt", F_OK)== 0)
                    	has_pot_stash = true;
                    	
                    	if(has_pot_stash){
                    		//Stash.
                    		//Get info from file
                    		FILE * fpotstash = fopen("NotCollected.txt", "r");
                    		fscanf(fpotstash, "%d\n", &pot_id);	//ID
                    		fgets(pot_name, 23, fpotstash);		//NAME
                    		fclose(fpotstash);
                    	
	                		while(true){
	                			CLR;
	                    		printf("[NPC] Grimold: \"I STILL HAVE YOUR \"%s\" POTION\"\n", pot_name);
	                    		printf("[NPC] Grimold: \"WANT IT?\" [Trash] [Hold] [Claim]\n");
	                    		String_Input;
	                    		
	                    		if(strcmp(Input, "trash")== 0){
	                    			//User dont want? We get rid of it :>
	                    			printf("[NPC] Grimold: \"STASH TRASHED.\"\n");
	                    			sleep(2);
	                    			ChangeCurPath("STASH.Potions");
	                    			remove("NotCollected.txt");
	                    			break;
	                    			
								} else if(strcmp(Input, "hold")== 0){
									//Hold onto it? (do nothing)
									printf("[NPC] Grimold: \"ILL WAIT.\"\n");
									sleep(2);
									break;
									
								} else if(strcmp(Input, "claim")== 0){
									printf("[NPC] Grimold: \"YOU WANT TO TRY AND CLAIM IT NOW?\"\n");
									sleep(2);
									
									temp1 = 1;
									int pos_overflow = Inventory("CALC", pot_id, temp1);
									
									//Didnt have space
									if(pos_overflow > 0){
										printf("[NPC] Grimold: \"INVENTORY IS FULL...\"\n");
										sleep(2);
										break;
										
									//Has space
									} else {
										printf("[NPC] Grimold: \"STASH HAS BEEN CLAIMED.\"\n");
										sleep(2);
										ChangeCurPath("STASH.Potions");
	                    				remove("NotCollected.txt");
										break;
									}
									
								} else { Error; }
	                		
	                		}
	                	
	                	//Does not have stash (checking for done pots)
						} else {
							ChangeCurPath("STASH.Potions");
							bool prob_has_pot_ready = false;
							
							if(access("Making.txt", F_OK)== 0)
							prob_has_pot_ready = true;
							
							if(prob_has_pot_ready){
								//Check if has a potion alr on the making
		                    	FILE * fmake = fopen("Making.txt", "r");
		                    	fscanf(fmake, "%d\n", &pot_id);		//ID
		                    	fscanf(fmake, "%d\n", &temp);		//HOUR
		                    	fscanf(fmake, "%d\n", &temp1);		//DAY
		                    	fgets(pot_name, 23, fmake);			//NAME
								fclose(fmake);						
								
								//Checking hour
								if(temp > TimeCalc("CHECK", 0, 1, 0)){
									//Checking day (hour failed)
									if(temp1 < TimeCalc("CHECK", 0, 0, 1))
									has_order_ready = true;
								} else {
								has_order_ready = true;
								}
								
															
								//Has cur order ready
		                        if(has_order_ready){	
									printf("[NPC] Grimold: \"POTION FINISHED BREWING (%s).\"\n", pot_name);
									sleep(2);
									int pos_overflow = Inventory("CALC", pot_id, 1);
									
									//Does not have space
									if(pos_overflow > 0){
										printf("[NPC] Grimold: \"INVENTORY FULL, IT WILL GO TO STASH.\"\n");
										sleep(1);
										
										//Register stuff in the stash file lul
										ChangeCurPath("STASH.Potions");
										FILE * fpotstash = fopen("NotCollected.txt", "w");
			                    		fprintf(fpotstash, "%d\n", pot_id);		//ID
			                    		fprintf(fpotstash, "%s", pot_name);		//NAME
			                    		fclose(fpotstash);
			                    		remove("Making.txt");	
										
									//Has space
									} else {
										printf("[NPC] Grimold: \"CLAIMED.\"\n");
										sleep(1);
										ChangeCurPath("STASH.Potions");
										remove("Making.txt");	
									}
									CLR;
									
								}
							}
	                    }
	                  
					CLR;     
	                //Wont make 2 pots at once
	                ChangeCurPath("STASH.Potions");
	                if(access("Making.txt", F_OK)!= 0 && access("NotCollected.txt", F_OK)!= 0){
	                    printf("[NPC] Grimold: \"POTIONS\"??? SURE I CAN MAKE SOME BUT IT WONT COME CHEAP, PLEASE CHECK THE LIST OVER THERE AND CHOOSE.\"\n");
	                        
	                    while(true){
	                        CLR;
	                        printf("Here is the list:\n\n");
	                        
	                        //Information that the "if" statements bellow give to the file
	                        char pot_name [23];
	                        int pot_id, num_dif_ing, time_taken, pot_itm_id_[5], pot_itm_quant_[5];
	                        bool no_check = false;
	                        
	                        //Bug fix atempt - if the for loop does 1 extras the user wont be affected
	                        memset(pot_itm_id_, 0, sizeof(pot_itm_id_));
	                        memset(pot_itm_quant_, 0, sizeof(pot_itm_quant_));
	                        
	                        //Ignore the absulute /t spam lol
	                        printf(">Refresher \t\t| 1x Milk \t\t\t\t\t\t\t\t\t\t| 2 Hours\n");
	                        printf(">Mint Tea \t\t| 2x Basil + 1x Mint\t\t\t\t\t\t\t\t\t| 3 Hours\n");
	                        printf(">Woods Water \t\t| 1x Chicken of the Woods + 2x Honey Mushroom\t\t\t\t\t\t| 6 Hours\n");
	                        printf(">Hidden Bush \t\t| 2x Black Berry + 3x Milkweed\t\t\t\t\t\t\t\t| 7 Hours\n");
	                        printf(">Time Decline \t\t| 2x Honey + 1x Milk + 3x Stick\t\t\t\t\t\t\t\t| 10 Hours\n");
	                        printf(">Happy Acident \t\t| 5x Medronhos Fruit + 2x Jackfruit + 1x Egg\t\t\t\t\t\t| 14 Hours\n");
	                        printf(">Early Grave \t\t| 1x Rainbow Carp + 1x Mythical Salmon + 1x Lime Carp + 1x Frowning Catfish\t\t| 20 Hours\n");
	                        printf(">Lots of Fish Bones \t| 2x Delayed Tuna + 3x Upside-down Shiner + 2x Non-Linear Shiner + 1x Skinny Snapper\t| 22 Hours\n");
	                        printf(">High Risk, Low Reward \t| 3x Honey + 2x Tail Feather + 2x Wool\t\t\t\t\t\t\t| 26 Hours\n");
	                        printf(">Im Special! \t\t| 3x Poopies + 5x Sunflower + 4x Allium + 3x Milkweed + 3x Beebalms\t\t\t| 30 Hours\n\n");
	                        
	                        printf("You say \"I want..\" ");
	                        printf("[Refresher] [Mint] [Woods] [Hidden] [Time] [Happy] [Early] [Fish] [Risk] [Special] [NONE]\n");
	                        String_Input;
	                        
	                        if(strcmp(Input, "none")== 0 || strcmp(Input, "back")== 0){
	                            
	                            printf("[NPC] Grimold: \"NOTHING?? REALLY? OKAY THEN\"\n");
	                            sleep(1); CLR; wants_to_leave = true; break;
	                            
	                        //We give information needed here
	                        } else if (strcmp(Input, "refresher")== 0){
	                        	//Give information like potion name, potion id, number of ingredients, time taken (in hours)
	                        	strcpy(pot_name, "Refresher");
	                        	pot_id = 116;
	                        	num_dif_ing = 1;
	                        	time_taken = 2;
	                        	
	                        	//Checking for this info
	                        	pot_itm_id_[0] = 38;
	                        	pot_itm_quant_[0] = -1;
	                        	
							} else if (strcmp(Input, "mint")== 0){
	                        	//Give information like potion name, potion id, number of ingredients, time taken (in hours)
	                        	strcpy(pot_name, "Mint Tea");
	                        	pot_id = 117;
	                        	num_dif_ing = 2;
	                        	time_taken = 3;
	                        	
	                        	//Checking for this info
	                        	pot_itm_id_[0] = 1;
	                        	pot_itm_id_[1] = 3;
	                        	pot_itm_quant_[0] = -2;
	                        	pot_itm_quant_[1] = -1;
	                        
							} else if (strcmp(Input, "woods")== 0){
								//Give information like potion name, potion id, number of ingredients, time taken (in hours)
	                        	strcpy(pot_name, "Woods Water");
	                        	pot_id = 118;
	                        	num_dif_ing = 2;
	                        	time_taken = 6;
	                        	
	                        	//Checking for this info
	                        	pot_itm_id_[0] = 18;
	                        	pot_itm_id_[1] = 16;
	                        	pot_itm_quant_[0] = -1;
	                        	pot_itm_quant_[1] = -2;
								
							} else if (strcmp(Input, "hidden")== 0){
								//Give information like potion name, potion id, number of ingredients, time taken (in hours)
	                        	strcpy(pot_name, "Hidden Bush");
	                        	pot_id = 119;
	                        	num_dif_ing = 2;
	                        	time_taken = 7;
	                        	
	                        	//Checking for this info
	                        	pot_itm_id_[0] = 26;
	                        	pot_itm_id_[1] = 33;
	                        	pot_itm_quant_[0] = -2;
	                        	pot_itm_quant_[1] = -3;
								
							} else if (strcmp(Input, "time")== 0){
								//Give information like potion name, potion id, number of ingredients, time taken (in hours)
	                        	strcpy(pot_name, "Time Decline");
	                        	pot_id = 120;
	                        	num_dif_ing = 3;
	                        	time_taken = 10;
	                        	
	                        	//Checking for this info
	                        	pot_itm_id_[0] = 43;
	                        	pot_itm_id_[1] = 38;
	                        	pot_itm_id_[2] = 102;
	                        	pot_itm_quant_[0] = -2;
	                        	pot_itm_quant_[1] = -1;
	                        	pot_itm_quant_[2] = -3;
								
							} else if (strcmp(Input, "happy")== 0){
								//Give information like potion name, potion id, number of ingredients, time taken (in hours)
	                        	strcpy(pot_name, "Happy Accident");
	                        	pot_id = 121;
	                        	num_dif_ing = 3;
	                        	time_taken = 14;
	                        	
	                        	//Checking for this info
	                        	pot_itm_id_[0] = 113;
	                        	pot_itm_id_[1] = 115;
	                        	pot_itm_id_[2] = 36;
	                        	pot_itm_quant_[0] = -5;
	                        	pot_itm_quant_[1] = -2;
	                        	pot_itm_quant_[2] = -1;
								
							} else if (strcmp(Input, "early")== 0){
								//Give information like potion name, potion id, number of ingredients, time taken (in hours)
	                        	strcpy(pot_name, "Early Grave");
	                        	pot_id = 122;
	                        	num_dif_ing = 4;
	                        	time_taken = 20;
	                        	
	                        	//Checking for this info
	                        	pot_itm_id_[0] = 65;
	                        	pot_itm_id_[1] = 101;
	                        	pot_itm_id_[2] = 63;
	                        	pot_itm_id_[3] = 73;
	                        	pot_itm_quant_[0] = -1;
	                        	pot_itm_quant_[1] = -1;		
	                        	pot_itm_quant_[2] = -1;
	                        	pot_itm_quant_[3] = -1;
								
							} else if (strcmp(Input, "fish")== 0){
								//Give information like potion name, potion id, number of ingredients, time taken (in hours)
	                        	strcpy(pot_name, "Lots of Fish Bones");
	                        	pot_id = 123;
	                        	num_dif_ing = 4;
	                        	time_taken = 22;
	                        	
	                        	//Checking for this info
	                        	pot_itm_id_[0] = 94;
	                        	pot_itm_id_[1] = 79;
	                        	pot_itm_id_[2] = 78;
	                        	pot_itm_id_[3] = 83;
	                        	pot_itm_quant_[0] = -2;
	                        	pot_itm_quant_[1] = -3;
	                        	pot_itm_quant_[2] = -2;
	                        	pot_itm_quant_[3] = -1;
								
							} else if (strcmp(Input, "risk")== 0){
								//Give information like potion name, potion id, number of ingredients, time taken (in hours)
	                        	strcpy(pot_name, "High Risk, Low Reward");
	                        	pot_id = 124;
	                        	num_dif_ing = 3;
	                        	time_taken = 26;
	                        	
	                        	//Checking for this info
	                        	pot_itm_id_[0] = 43;
	                        	pot_itm_id_[1] = 41;
	                        	pot_itm_id_[2] = 37;
	                        	pot_itm_quant_[0] = -3;
	                        	pot_itm_quant_[1] = -2;
	                        	pot_itm_quant_[2] = -2;
								
							} else if (strcmp(Input, "special")== 0){
								//Give information like potion name, potion id, number of ingredients, time taken (in hours)
	                        	strcpy(pot_name, "Im Special!");
	                        	pot_id = 125;
	                        	num_dif_ing = 5;
	                        	time_taken = 30;
	                        	
	                        	//Checking for this info
	                        	pot_itm_id_[0] = 34;
	                        	pot_itm_id_[1] = 31;
	                        	pot_itm_id_[2] = 32;
	                        	pot_itm_id_[3] = 33;
	                        	pot_itm_id_[4] = 35;
	                        	pot_itm_quant_[0] = -3;
	                        	pot_itm_quant_[1] = -5;
	                        	pot_itm_quant_[2] = -4;
	                        	pot_itm_quant_[3] = -3;
	                        	pot_itm_quant_[4] = -3;
								
							} else { Error; no_check = true; }
	                        
	                        //Set up a boolean to check ingredients and the trigger to see if user has the items needed
	                        bool has_potion_items[num_dif_ing], has_items = false;
	                        memset(has_potion_items, false, sizeof(has_items));
	                        
	                        //Check if user has items
	                        for(int i = 0; i < num_dif_ing; i ++)
	                       	has_potion_items[i] = Inventory("CHECK", pot_itm_id_[i], pot_itm_quant_[i]);
							
							//if every index of "has_potion_items" is true, then "has_items" is true
							if(memchr(has_potion_items, false, sizeof(has_potion_items))== NULL)
							has_items = true;
	                        
	                        //Case of error
	                        if(no_check)
	                        has_items = false;
	                        
	                        if(has_items){
	                        	
	                        	//Make order
	                        	while(true){
		                        	printf("[NPC] Grimold: \"I SEE YOU HAVE THE ITEMS, DO WE HAVE A DEAL? [YES] [NO]\"\n");
		                        	String_Input;
		                        	
		                        	if(strcmp(Input, "yes")== 0){
		                        		//Checking stuff for potion
			                        	int final_h;			
			                    		long int final_d; 	
		                        		
		                        		for(int i = 0; i < num_dif_ing; i ++)
		                        		Inventory("CALC", pot_itm_id_[i], pot_itm_quant_[i]);
		                        		
		                        		final_h = TimeCalc("CHECK", 0, 1, 0);
		                        		final_d = TimeCalc("CHECK", 0, 0, 1);
			                        	final_h += time_taken;
			                        	
			                        	//Slightly change it (add 1 to day and sub 24 from hour)
			                        	if(final_h >= 24){
			                        		final_h -= 24;
			                        		final_d += 1;
										}
										
										//CAN Happend twice lol
										if(final_h >= 24){
			                        		final_h -= 24;
			                        		final_d += 1;
										}
										
										//Register final information on file
										ChangeCurPath("STASH.Potions");
										FILE * fpotstats = fopen("Making.txt", "w");
						                fprintf(fpotstats, "%d\n", pot_id);		//ID
										fprintf(fpotstats, "%d\n", final_h);	//HOUR
										fprintf(fpotstats, "%d\n", final_d);	//DAY
										fprintf(fpotstats, "%s", pot_name); 	//NAME  		
		                        		fclose(fpotstats);
		                        		
		                        		wants_to_leave = true;
		                        		printf("[NPC] Grimhold: \"COME BACK LATER, I WILL MAKE YOUR POTION NOW\"\n");
		                        		sleep(2);
		                        		
		                        		break;
		                        		
									} else if(strcmp(Input, "no")== 0){
										wants_to_leave = true;
										printf("[NPC] Grimold: \"CHANGED YOUR MIND? OK THEN...\"\n");
										sleep(2);
										break;
										
									} else
									Error;
								}
							//Case of no items
							} else {
								//Let it not apear if error
								if(!no_check){
									printf("[NPC] Grimold: \"NO ITEMS, NO POTION.\"\n");
									Small_stop;
								}
							}
	                    }
						
						if(wants_to_leave)
						break;
						
					} else {
						printf("[NPC] Grimold: \"I WILL NOT MAKE 2 POTIONS AT ONCE.\"\n");
						Small_stop;
					}
            		
                    } else if (strcmp(Input, "back")== 0){
                        
                        printf("You go back to Sarah\n");
                        sleep(1);
                        break;
                        
                    } else { Error; }
                	
                	}	
                	
            } else if (strcmp(Input, "cell")== 0){
        
        while(true){
        CLR;
        printf("You go back to the Monastic Cell, what do you want to read?\n");
        printf(">\"The Enchanted Garden\" [Garden]\n");
        printf(">\"Whispers of the Wind\" [Wind]\n");
        printf(">\"The Secret Library\" [Library]\n");
        printf(">\"Shadows of Imagination\" [Imagination]\n");
        printf(">\"Pages of Destiny\" [Destiny]\n");
        String_Input;
        
        if (strcmp(Input, "garden")== 0){
            
            printf("You picked up \"The Enchanted Garden\"\n");
            printf("A whimsical sanctuary where nature's magic unfolds, captivating hearts and sparking imaginations. Within its enchanting embrace, \n");
            printf("vibrant blooms and mystical creatures create a tapestry of wonder, inviting all to explore and dream. The air is alive with the sweet melodies of birdsong, \n");
            printf("as if nature herself is serenading those who wander through this ethereal realm.\n");
            break;
             
        } else if (strcmp(Input, "wind")== 0){
             
            printf("You picked up \"Whispers of the Wind\"\n");
            printf("In a forgotten corner of the world, nestled among ancient trees, lies the mystical realm of \"Whispers of the Wind.\" \n");
            printf("Here, gentle breezes carry secrets and tales untold, whispering through the leaves and guiding wanderers on their path. \n");
            printf("Those who listen closely may hear the wind's ancient wisdom, a symphony of whispers that dances through the air, leaving a sense of wonder in its wake.\n");
            break;
            
        } else if (strcmp(Input, "library")== 0){
              
            printf("You picked up \"The Secret Library\"\n");
            printf("In the \"Secret Library,\" hidden within the depths of an ancient castle, forgotten knowledge awaits.\n");
            printf("Dusty shelves hold countless books, their pages whispering tales of forgotten worlds and untold wisdom. \n");
            printf("Those who dare to enter this sanctuary of knowledge may unlock the secrets that have been lost to time.\n");
            printf("Has they say, only the Librarian has the key...\"SECRET\"\n");
            break;
            
        } else if (strcmp(Input, "imagination")== 0){
              
            printf("You picked up \"Shadows of Imagination\"\n");
            printf("In the \"Shadows of Imagination,\" where darkness and light intertwine, elusive figures emerge from the depths, shaping the dreams and fantasies of those who dare to explore.\n");
            printf("Within this enigmatic space, shadows hold the power to transport us to unimaginable places, allowing us to experience the extraordinary and embrace the magic that lies within.\n");
            break;
           
        } else if (strcmp(Input, "destiny")== 0){
            
            printf("You picked up \"Pages of Destiny\"\n");
            printf("In the mystical \"Pages of Destiny,\" ancient tomes hold the secrets of fate, with each page revealing a unique chapter of one's journey.\n");
            printf("As the pages turn, destinies intertwine, weaving a tapestry of choices, challenges, and triumphs.\n");
            printf("Within these hallowed pages, the power to shape one's own narrative lies, waiting to be discovered by those who dare to seek their true path.\n");
            break;
            
        } else { Error; }
        
        }
        
        Small_stop;
        
        while(true){
        	CLR;
            printf("Read annother? [Y] [N]\n");
            String_Input;
            
            if (strcmp(Input, "y")== 0){
                
            } else if (strcmp(Input, "n")== 0){

                printf("You stop decide not to read annother and move towards Sarah\n");
                break;
                
            } else { Error; }
   		}
    		
            } else if (strcmp(Input, "secret")== 0){
                
                bool l_secret_1st_time = true;
                
                //Check trigger :>
                ChangeCurPath("OTHER.triggers.other");
                FILE * fbooktrig = fopen("LibBook.txt", "r");
                fscanf(fbooktrig, "%d\n", &l_secret_1st_time);
                fclose(fbooktrig);
                
                printf("[NPC] Sarah: \"So you read the book then..\"\n");
                printf("[NPC] Sarah: \"Fine ill take you there\"\n\n");
                printf("She opens the bookshelf and crawls inside\n\n");
                printf("[NPC] Sarah: \"You coming or what?\"\n\n");
                printf("You nod and follow deep into the man made hole\n");
                printf("Eventually you reach a Oval room, very similar to a Bird cage\n\n");
                printf("[NPC] Sarah: \"Well, this is the inner workings of the Library\"\n");
                printf("[NPC] Sarah: \"I dont know what you want to do here but here we are\"\n\n");
                
	            if(l_secret_1st_time){	
	                printf("You explore around old books and find one Titled: \"How to Wizard, the best guide!\"\n");
	                printf("Upon Opening it you see, \"BORROWED BY CELESTIA THE GREAT WIZARD\"\n");
	                printf("[Like its not going to be important later]\n");
	                printf("The book is writen in a weird Language you dont understand, even Sarah cant help you\n");
	                l_secret_1st_time = false;
	                printf("You take the book for safe keeping and leave\n\n");
	                
	                //Register new thing
	                FILE * fbooktrig = fopen("LibBook.txt", "w");
	                fprintf(fbooktrig, "%d\n", l_secret_1st_time);
	                fclose(fbooktrig);
	                
	                //Register that got book :> (yes)
	                ChangeCurPath("OTHER.books");
	                FILE * flibbook = fopen("SecretLib.txt", "w");
	                fprintf(flibbook, "1\n");
	                fclose(flibbook);
	                
	            } else {
	            	printf("You find nothing of use so you leave\n\n");
				}
				
				Small_stop;
                
            } else if (strcmp(Input, "back")== 0){
                
                printf("You go back to the hanging signs\n"); sleep(1); CLR; break;  
                
   			} else { Error; }
    
}

} else { printf("[SIGN]: \"The library is currently closed and only opens at 10!\"\n"); sleep(1); CLR; }

}

void Hotel(void){
	CLR;
	ChangeCurPath("OTHER.triggers.other");
	
	//Check if user alr saw this dialogue
	if(access("HotelDone.txt", F_OK)!= 0){
		printf("You go to the Tavern, seeking a place to rest\n");
		printf("Inside you find a man cleaning the tables and he speaks\n"); 
		printf("[NPC] Blanverth: \"Hello adventurer, i see you are seeking for a place to rest, i will let you stay here free of charge! (we dont have many customers)\"\n");
		printf("[NPC] Blanverth: \"Also the food is good but paid, speak to me if you want some food or just a little chat, enjoy your room.\"\n");
    	
    	//Make file for new dialogue
    	FILE * fhoteldone = fopen("HotelDone.txt", "w");
    	fclose(fhoteldone);
    	
    	Small_stop;
    } else {
    	short int hotel_recep_rand = rand()% 3 + 1;
    	
    	if(hotel_recep_rand == 1)
    	printf("[NPC] Blanverth: \"Hello again!\"\n");
    	else if(hotel_recep_rand == 2)
    	printf("[NPC] Blanverth: \"Welcome back!\"\n");
    	else 
    	printf("[NPC] Blanverth: \"Back again?\"\n");
    	
    	sleep(1);
    	CLR;
	}
	
	while(true){
		bool alr_chated_w_recp = false, debt_payed = false;
		
		//Change path and check if the other 2 options are valid
		ChangeCurPath("ACHIVEMENTS.Extra");
		if(access("DebtPayed.txt", F_OK)== 0)
		debt_payed = true;
		
		ChangeCurPath("OTHER.triggers.other");
		if(access("ChatWithRecep.txt", F_OK)== 0)
		alr_chated_w_recp = true;
		
		Art("RECEP_HOT", 0);
		printf("[NPC] Blanverth: \"Looking for anything?\"\n");
		printf(">Im gonna go to my bedroom...[Bedroom]\n");
		printf(">Lets chat! [Chat]\n");
		
		if(alr_chated_w_recp && !debt_payed)
		printf(">I want to pay your debt [Debt]\n");
		
		printf(">Ill see you around! [Back]\n");
		String_Input;
		
		if(strcmp(Input, "bedroom")== 0){
			while(true){
				Art("BEDROOM", 0);
			    printf("What now?\n");
			    printf(">Check time [Time]\n");
			    printf(">Sleep\n"); 
			    printf(">Sit and Wait [Sit]\n");
			    printf(">Water the plant [Water]\n");    
			    printf(">Store Items [Store]\n"); 
			    printf(">Leave\n");
			    String_Input;
			    
			    if(strcmp(Input, "time")== 0){
			    	
			    	printf("Whats the time? Its %d\n", TimeCalc("CHECK", 0, 1, 0));
			    	Small_stop;
			    	
				} else if(strcmp(Input, "sleep")== 0){
			    	int sleep_hour; 
			    	
			    	while(true){
				    	printf("How many hours? (must be bettewn 6 and 12)\n");
				    	printf("&/");
				    	scanf("%d", &sleep_hour);
				    	CLR;
				    	
				    	//Valid sleep hour
				    	if(sleep_hour <= 12 && sleep_hour >= 6){
				    		sleep(5);
				    		
				    		if(display_tip)							//Display tip if settings say so
							TipOfTheDay();
							
				    		sleep(5);
				    		CLR;
							TimeCalc("CALC", 0, sleep_hour, 0);	//Add number of hours slept
							break;
				    		
						} else { red; printf("Please provide an hour BETTEWN 6 AND 12\n"); white; sleep(2); CLR; }
						
					}
				
					printf("You slept for %d hours!\n", sleep_hour);
					printf("Back to figuring out this place we go :)\n");
					Small_stop;
					
				} else if (strcmp(Input, "sit")== 0){
					//Same thing has "sleep" but its randomized bettewn 1 and 4 hours
					int time_sitting = rand()% 4 + 1;
					
					CLR;
			    	sleep(5);
			    	if(display_tip)
					TipOfTheDay();
		
			    	sleep(5);
			    	CLR;
					TimeCalc("CALC", 0, time_sitting, 0);
			    	
			    	printf("You sat for %d hours!\n", time_sitting);
					printf("Back to figuring out this place we go :)\n");
					Small_stop;
					
				} else if (strcmp(Input, "water")== 0){
					long int plant_day, plant_water = 0; 
					
					//Check file
					ChangeCurPath("ACHIVEMENTS.Progress");
					if(access("PlantWater.txt", F_OK)== 0){
						FILE * fplantwater = fopen("PlantWater.txt", "r");
						fscanf(fplantwater, "%d\n", &plant_water);
						fscanf(fplantwater, "%d\n", &plant_day);
						fclose(fplantwater);
					} else {
						//Take day from achivement done file because progress has been deleted.
						ChangeCurPath("ACHIVEMENTS.Done");
						if(access("PlantWater.txt", F_OK)== 0){
							FILE * fplantwater = fopen("PlantWater.txt", "r");
							fscanf(fplantwater, "%d\n", &plant_day);
							fclose(fplantwater);
							plant_water = 99;
						}
					}
					
					//Valid day to water the plant?
					if(plant_day < TimeCalc("CHECK", 0, 0, 1)){
						printf("You water the plant.\n"),
						printf("It seems happy to get some water and you feel better for doing it\n");
						plant_day = TimeCalc("CHECK", 0, 0, 1); 
						plant_water ++;
						
						//Diferent plant tages
						if (plant_water >= 1 && plant_water <= 3)
						Art("PLANT", 1);
							
						else if (plant_water >= 4 && plant_water <= 6)
						Art("PLANT", 2);
							
						else if (plant_water >= 7 && plant_water <= 9)
						Art("PLANT", 3);
							
						else
						Art("PLANT", 4);
						
						//Check if achiv is not done
						ChangeCurPath("ACHIVEMENTS.Done");
						if(access("PlantWater.txt", F_OK)!= 0){
							//Register progress in file
							ChangeCurPath("ACHIVEMENTS.Progress");
							FILE * fplantwater = fopen("PlantWater.txt", "w");
							fprintf(fplantwater, "%d\n", plant_water);
							fprintf(fplantwater, "%d\n", plant_day);
							fclose(fplantwater);
						} else {
							//Register day in achivement done file
							FILE * fplantwater = fopen("PlantWater.txt", "w");
							fprintf(fplantwater, "%d\n", plant_day);
							fclose(fplantwater);
						}
						
					} else { printf("You already waterred the Plant today!\n"); }
					
					//Got Achivement :>
					if(plant_water == 10){ 
						yellow;
						printf("[ACHIVEMENT] _> LET IT GROW! (Water the plant 10 times in diferent days)\n");
						white;
						ChangeCurPath("ACHIVEMENTS.Done");
						FILE * fplantwater = fopen("PlantWater.txt", "w");
						fprintf(fplantwater, "%d\n", plant_day);
						fclose(fplantwater);
						
						//Remove progress file because its no longer needed
						ChangeCurPath("ACHIVEMENTS.Progress");
						remove("PlantWater.txt");
					}
					
					Small_stop;
					
				} else if (strcmp(Input, "store")== 0){
					
					Chest();
				
				} else if (strcmp(Input, "leave")== 0){
					
					printf("You go back to the Reception room\n");
					sleep(1); CLR; break;
					
				} else { Error; }
				
		    }
		    
		} else if(strcmp(Input, "chat")== 0){
			//Seperate chat if its the 1st time chatting
			ChangeCurPath("OTHER.triggers.other");
			if(access("ChatWithRecep.txt", F_OK)!= 0){
				printf("[NPC] Blanverth: \"You wanna chat? Sure!\"\n");
				printf("[NPC] Blanverth: \"Life is kinda boring just standing here and helping people out\"\n");
				printf("[NPC] Blanverth: \"Its nice to have a break from time to time, dont you think?\"\n");
				printf("[NPC] Blanverth: \"Just a few days ago i was reminded of my debt\"\n");
				printf("[NPC] Blanverth: \"Pretty tough life\"\n");
				printf("[NPC] Blanverth: \"Oh sorry that got a little bit depressing didnt it?\"\n");
				printf("[NPC] Blanverth: \"Sometimes i talk a little too much and end up saying things i didnt mean to\"\n");
				
				//Register has alr chatted with him
				FILE * ftrigchat = fopen("ChatWithRecep.txt", "w");
				fclose(ftrigchat);
				
			} else {
				//Randomize bettewn 3 chats
				short int chat_chosen = rand()% 5 + 1;
				if(chat_chosen == 1){
					printf("[NPC] Blanverth: \"So, how is the weather?\"\n");
					printf("[NPC] Blanverth: \"Pretty nice right now, right?\"\n");
					printf("[NPC] Blanverth: \"I have noticed that it dosent rain a lot, nor anything else\"\n");
					printf("[NPC] Blanverth: \"But when it does, its the stalagmites on the ceiling that do it\"\n");
					printf("[NPC] Blanverth: \"How do you feel about a Village just being in a enormous cave in here?\"\n");
					printf("[NPC] Blanverth: \"Must be at least somewhat weird, right?\"\n");
					printf("[NPC] Blanverth: \"Maybe im just overthinking it...\"\n");
					printf("[NPC] Blanverth: \"I wonder how the stalagmites get that water...\"\n");
					
				} else if(chat_chosen == 2){
					printf("[NPC] Blanverth: \"Where did you come from adventurer?\"\n");
					printf("[NPC] Blanverth: \"Huh, you dont know?\"\n");
					printf("[NPC] Blanverth: \"Hmm, ill give it to you this time because i dont even know if this place has an entrance\"\n");
					printf("[NPC] Blanverth: \"I was just born here and never questioned anything, but now that im older there are things that dont match up...\"\n");
					printf("[NPC] Blanverth: \"You understand me?\"\n");
					printf("[NPC] Blanverth: \"I should write books to organize my thoughts\"\n");
					printf("[NPC] Blanverth: \"The world is full of mysteries...\"\n");
									
				} else if(chat_chosen == 3){
					printf("[NPC] Blanverth: \"Would you read my rambles if i put them all into a book?\"\n");
					printf("[NPC] Blanverth: \"It would be funny, just a book about my thoughts\"\n");
					printf("[NPC] Blanverth: \"Ok perhaps it wouldnt be funny\"\n");
					printf("[NPC] Blanverth: \"Thinking i need to find a way to think LESS and work MORE\"\n");
					printf("[NPC] Blanverth: \"But work is kinda boring\"\n");
					printf("[NPC] Blanverth: \"My head is confusing me\"\n");
					printf("[NPC] Blanverth: \"I should get a cat...\"\n");
					
				} else if(chat_chosen == 4){
					printf("[NPC] Blanverth: \"Do i talk a lot?\"\n");
					printf("[NPC] Blanverth: \"I mean, all i do is ask a question to myself and come up with answers\"\n");
					printf("[NPC] Blanverth: \"Well. on the other side it improves my thinking\"\n");
					printf("[NPC] Blanverth: \"You know, i think a lot\"\n");
					printf("[NPC] Blanverth: \"All of us do\"\n");
					printf("[NPC] Blanverth: \"Ugh, my brain...\"\n");
					
				} else {
					printf("[NPC] Blanverth: \"Do you find the freezing temperatures to be a annoying too?\"\n");
					printf("[NPC] Blanverth: \"The temperature dosent change much but it gets kinda annoying\"\n");
					printf("[NPC] Blanverth: \"I guess many of us get used to it overtime\"\n");
					printf("[NPC] Blanverth: \"But what about adventurers like you?\"\n");
					printf("[NPC] Blanverth: \"I know the temperate must be something thats bothering you\"\n");
					printf("[NPC] Blanverth: \"Not that i can do anything about it but\"\n");
					printf("[NPC] Blanverth: \"I think the deeper you get the hotter it will be\"\n");
					printf("[NPC] Blanverth: \"Thats what the wizard told us anyways\"\n");
					printf("[NPC] Blanverth: \"I dont know why, there isnt even a way to go farther down...\"\n");
					
				}
				
			}
			
			printf("[NPC] Blanverth: \"Thank you for listening to my rambles\"\n\n");
			Small_stop;
			
		} else if(strcmp(Input, "debt")== 0 && alr_chated_w_recp && !debt_payed){
			while(true){
				printf("[NPC] Blanverth: \"What? You cant be serious, right?\"\n");
				printf("[NPC] Blanverth: \"Well, my debt is around ~100k, sooo\"\n");
				printf("[NPC] Blanverth: \"Still want to pay it? [Yes] [No] (Your current money is %d)\"\n", money);
				String_Input;
				
				if(strcmp(Input, "yes")== 0){
					money -= 100000;
					if(money >= 0){
						printf("[NPC] Blanverth: \"Oh, wow, thank you so much\"\n");
						printf("[NPC] Blanverth: \"I didnt think you would actually do it...\"\n");
						
						//Add achivement to the list of extra achivements
						yellow;
						printf("[(Extra) ACHIVEMENT] _> TAKE IT ALL! (Pay Blanverth's Debt)\n");
						white;
						ChangeCurPath("ACHIVEMENTS.Extra");
						FILE * fdebtpayed = fopen("DebtPayed.txt", "w");
						fclose(fdebtpayed);
						
					} else {
						money += 100000;
						printf("[NPC] Blanverth: \"I knew it was too much for you...\"\n");
					}
					
					Small_stop;
					break;
					
				} else if(strcmp(Input, "no")== 0){
					printf("[NPC] Blanverth: \"Ah, dont scare me like that i tought you were serious for a moment\"\n");
					printf("[NPC] Blanverth: \"(Im going to have a heart attack with this guy around some day)\"\n");
					Small_stop;
					break;
					
				} else {
					Error;
				}
			}
			
		} else if(strcmp(Input, "back")== 0){
			printf("Back to the signs...");
			sleep(1);
			CLR;
			break;
		
		} else {
			Error;
		}
    
	}
}

void Chest(void){
	CLR;
		
	const unsigned int CHEST_LIMIT = 1000;
	int CUR_CHEST_ITM = 0, c_farm_itm_c = 0, c_livestock_itm_c = 0, c_fishing_itm_c = 0, c_foraging_itm_c = 0, c_alch_itm_c = 0, c_extra_itm_c = 0;
	int Quantity, ID;
	char bckp_chest_inp [6];
	
	static int C_List_Quantities[136];
	memset(C_List_Quantities, 0, sizeof(C_List_Quantities));
	
	ChangeCurPath("CHEST_INVENTORY");
	
	//Check if there is alr a save done
	if(access("Crops.txt", F_OK)== 0){
		int i;
		
		//Save the chest invntory in the files set in the CHEST dir
		FILE * fcrop = fopen("Crops.txt", "r");
		for(i = 1; i < 36; i ++)
		fscanf(fcrop, "%d\n", &C_List_Quantities[i]);
		fclose(fcrop);
		
		FILE * fanimal = fopen("Animals.txt", "r");
		for(i = 36; i < 46; i ++)
		fscanf(fanimal, "%d\n", &C_List_Quantities[i]);
		fclose(fanimal);
		
		FILE * ffish = fopen("Fish.txt", "r");
		for(i = 46; i < 102; i ++)
		fscanf(ffish, "%d\n", &C_List_Quantities[i]);
		fclose(ffish);
		
		FILE * fforaging = fopen("Foraging.txt", "r");
		for(i = 102; i < 116; i ++)
		fscanf(fforaging, "%d\n", &C_List_Quantities[i]);
		fclose(fforaging);
		
		FILE * falchemy = fopen("Alchemy.txt", "r");
		for(i = 116; i < 126; i ++)
		fscanf(falchemy, "%d\n", &C_List_Quantities[i]);
		fclose(falchemy);
		
		FILE * fextras = fopen("Extras.txt", "r");
		for(i = 126; i < 135; i ++);
		fscanf(fextras, "%d\n", &C_List_Quantities[i]);
		fclose(fextras);
		
		FILE * futility = fopen("Utility.txt", "r");
		fscanf(futility, "%d\n", &C_List_Quantities[135]);
		fclose(futility);
	}
	
	for(int i = 1; i <= 35; i ++)
	c_farm_itm_c += C_List_Quantities[i];
	
	for(int i = 36; i <= 47; i ++)
	c_livestock_itm_c += C_List_Quantities[i];
	
	for(int i = 48; i <= 101; i ++)
	c_fishing_itm_c += C_List_Quantities[i];
	
	for(int i = 102; i <= 115; i ++)
	c_foraging_itm_c += C_List_Quantities[i];
	
	for(int i = 116; i <= 125; i ++)
	c_alch_itm_c += C_List_Quantities[i];
	
	for(int i = 126; i <= 134; i ++)
	c_extra_itm_c += C_List_Quantities[i];
		
	//Check current inv space
	CUR_CHEST_ITM = c_farm_itm_c + c_livestock_itm_c + c_fishing_itm_c + c_foraging_itm_c + c_alch_itm_c + c_extra_itm_c;
	
	printf("You open the chest...\n");
	while(true){
		CLR;
		printf("What now?\n");
		printf(">Store Items [Store]\n");  
		printf(">Take out Items [Take]\n"); 
		printf(">View Storage [View]\n"); 
		printf(">Not now [Back]\n");
		String_Input;
		
		strcpy(bckp_chest_inp, Input);
		
		if(strcmp(bckp_chest_inp, "store")== 0){
			CLR;
			
			//Call inventory with "ID" argument to known what user wants and how much of it
			int inv_return = Inventory("ID", 0, 0);
			if(inv_return == 0){
				printf("Nothing? Ok\n");
				sleep(2);
				CLR;
			}
			
			int bckp_inv_return = inv_return;
			
			//Special error value in case inv has no items :)
			if(inv_return == -99999){
				CLR;
				red;
				printf("Empty Inventory!\n");
				white;
				Small_stop;
				
			} else {
			
				//Decode returning value
				Quantity = inv_return / 1000;
				bckp_inv_return -= (Quantity * 1000);
				ID = bckp_inv_return;
				
				int bckp_quantity = Quantity;
				Quantity = -Quantity;
				
				//Remove value from main inv
				Inventory("CALC", ID, Quantity);
				
				Quantity = bckp_quantity;
				
				//Add to chest inv
				bool chest_overflow = false;
				
				if(CUR_CHEST_ITM == CHEST_LIMIT){
				
				CLR;
				printf("Chest Full.\n");
				Overflow_Value = Quantity;
				sleep(1);
				
				chest_overflow = true;
				
				} else {
						
					ALL_INV_ITM_BCKP = CUR_CHEST_ITM;
					CUR_CHEST_ITM += Quantity;
						
					if(CUR_CHEST_ITM <= CHEST_LIMIT)
						chest_overflow = false;
						
					else {
						
						Overflow_Value = CUR_CHEST_ITM - CHEST_LIMIT; //Overflow Value
						chest_overflow = true;
						
					}
					
				}
				
				if(!chest_overflow){
					C_List_Quantities[ID] += Quantity;
					Overflow_Value = 0;
				} else 
				C_List_Quantities[ID] += CHEST_LIMIT - ALL_INV_ITM_BCKP;
				
				CLR;
				//Chest full :>
				if(Overflow_Value > 0){
					Quantity = Overflow_Value;
					Inventory("CALC", ID, Quantity);
					red;
					printf("The chest is full!\n");
					white;
					sleep(2);
				} else {
					green;
					printf("You deposited the items in your chest!\n");
					white;
					sleep(2);
				}
			
			}
			
		//Same has Inventory "CALC" argument :>
		} else if(strcmp(bckp_chest_inp, "take")== 0 || strcmp(bckp_chest_inp, "view")== 0){
			
		//declare assisting vars to organize inv
		bool crops[7], animals[3], ponds[8], trees[4], Alchemy = false, Extras = false, leave_inv = false;
		memset(crops, false, sizeof(crops));
		memset(animals, false, sizeof(animals));
		memset(ponds, false, sizeof(ponds));
		memset(trees, false, sizeof(trees));
				
		//Check crop quantity
		for(int i = 0; i < 7; i ++){
			for(int j = 0; j < 5; j ++){
				if(C_List_Quantities[(j + 1) * (i + 1)] > 0){
					crops[i] = true;
					break;
				}
			}
		}
		
		//Check livestock quantity
		for(int i = 0; i < 3; i ++){
			for(int j = 0; j < 3; j ++){
				if(C_List_Quantities[((j + 1) * (i + 1) + 35)] > 0){
					animals[i] = true;
					break;
				}
			}
		}
		
		//Check fishing quantity
		for(int i = 0; i < 8; i ++){
			for(int j = 0; j < 6; j ++){
				if(C_List_Quantities[((j + 2) * (i + 1) + 45)] > 0){
					ponds[i] = true;
					break;
				}
			}
		}
		
		//Checking for trees
		//tree 1
		for(int i = 103; i <= 108; i ++){
			if(C_List_Quantities[i] > 0){
				trees[0] = true;
				break;
			}
		}
		
		//tree 2
		for(int i = 109; i <= 110; i ++){
			if(C_List_Quantities[i] > 0){
				trees[1] = true;
				break;
			}
		}
		
		//tree 3
		for(int i = 111; i <= 113; i ++){
			if(C_List_Quantities[i] > 0){
				trees[2] = true;
				break;
			}
		}
		
		//tree 4
		for(int i = 114; i <= 115; i ++){
			if(C_List_Quantities[i] > 0){
				trees[3] = true;
				break;
			}
		}
		
		//Check alchemy quantity
		for(int i = 116; i < 126; i ++){
			if(C_List_Quantities[i] > 0){
				Alchemy = true;
				break;
			}
		}
		
		//Check for extras quantity
		for(int i = 126; i < 135; i ++){
			if(C_List_Quantities[i] > 0){
				Extras = true;
				break;
			}
		}
		
		bool break_all = false;
		while(true){
			
		CLR;
		
		short int cnt = 0;
		
		for(int i = 0; i < 136; i ++){
			if(C_List_Quantities[i] <= 0)
			cnt++;
		}		
		
		if(cnt == 136){
			red;
			printf("\n\nNothing but spider webs here\n\n");
			white;
			Small_stop;
			break;
		} else {
			if(div_inv_sect){
				
				while(true){
					bool no_break = false;	
					
					printf("What category do you want to see?\n");
					printf(">Farming\n");
					printf(">Livestock\n");
					printf(">Fishing\n");
					printf(">Foraging\n");
					printf(">Alchemy\n");
					printf(">Extras\n");
					printf(">Leave\n");
					String_Input;
					
					for(int i = 0; i < 6; i ++)
					arr_limit_inv[i] = false;
					
					if(strcmp(Input, "farming")== 0)
					arr_limit_inv[0] = true;
					
					else if(strcmp(Input, "livestock")== 0)
					arr_limit_inv[1] = true;
					
					else if(strcmp(Input, "fishing")== 0)
					arr_limit_inv[2] = true;
					
					else if(strcmp(Input, "foraging")== 0)
					arr_limit_inv[3] = true;
					
					else if(strcmp(Input, "alchemy")== 0)
					arr_limit_inv[4] = true;
					
					else if(strcmp(Input, "extras")== 0)
					arr_limit_inv[5] = true;
					
					else if(strcmp(Input, "leave")== 0){
						break_all = true; break;
					
					} else { Error; no_break = true; }
					
					
					if(!no_break)
					break;
					
				}
			}
		}
		
		if(break_all)
		break;
		
		if(arr_limit_inv[0]){
			
			//FARMING	
			if(memchr(crops, true, sizeof(crops)) != NULL)
			printf("\nFarming items [%d]\n\n", c_farm_itm_c);
			
			//CROP 1
			if(crops[0]){
				printf("[FROM: HERB GARDEN] _> 1.Basil? %d / 2. Oregano? %d / 3. Mint? %d / 4. Thyme? %d / 5. Worm? %d\n", 
				C_List_Quantities[1], C_List_Quantities[2], C_List_Quantities[3], C_List_Quantities[4], C_List_Quantities[5]);
			}
			
			//CROP 2
			if(crops[1]){
				printf("[FROM: FLOREST] _> 6.Potato? %d / 7. Carrot? %d / 8. Wheat? %d / 9. Rice? %d / 10. Cabbage? %d\n", 
				C_List_Quantities[6], C_List_Quantities[7], C_List_Quantities[8], C_List_Quantities[9], C_List_Quantities[10]);
			}
			
			//CROP 3
			if(crops[2]){
				printf("[FROM: FUNGI (1)] _> 11.Tomato? %d / 12. Cucumber? %d / 13. Lettuce? %d / 14. Pepper? %d / 15. Bean? %d\n", 
				C_List_Quantities[11], C_List_Quantities[12], C_List_Quantities[13], C_List_Quantities[14], C_List_Quantities[15]);
			}
			
			//CROP 4
			if(crops[3]){
				printf("[FROM: FUNGI (2)] _> 16.Honey Mushroom? %d / 17. Hedgehog Mushroom? %d / 18. Chicken of the Woods? %d / 19. Hen of the Woods? %d / 20. Abortive Entoloma? %d\n", 
				C_List_Quantities[16], C_List_Quantities[17], C_List_Quantities[18], C_List_Quantities[19], C_List_Quantities[20]);
			}
			
			//CROP 5
			if(crops[4]){
				printf("[FROM: FUNGI (3)] _> 21.Corn? %d / 22. Onion? %d / 23. Pea? %d / 24. Asparagus ? %d / 25. Broccoli? %d\n", 
				C_List_Quantities[21], C_List_Quantities[22], C_List_Quantities[23], C_List_Quantities[24], C_List_Quantities[25]);
			}
			
			//CROP 6
			if(crops[5]){
				printf("[FROM: GERSYERS]_> 26.Blackberry? %d / 27. Blueberry? %d / 28. Strawberry? %d / 29. Cape Gooseberry? %d / 30. Raspberry? %d\n", 
				C_List_Quantities[26], C_List_Quantities[27], C_List_Quantities[28], C_List_Quantities[29], C_List_Quantities[30]);	
			}
			
			//CROP 7
			if(crops[6]){
				printf("[FROM: BLOSSOM] _> 31.Sunflower? %d / 32. Allium? %d / 33. Milkweed? %d / 34. Poppies? %d / 35. Beebalms? %d\n\n", 
				C_List_Quantities[31], C_List_Quantities[32], C_List_Quantities[33], C_List_Quantities[34], C_List_Quantities[35]);
			}
			
		} 
		
		if(arr_limit_inv[1]){
		
			//LIVESTOCK
			if(memchr(animals, true, sizeof(animals)) != NULL)
			printf("\nLivestock items [%d]\n\n", c_livestock_itm_c);
			
			//ANIMAL 1
			if(animals[0]){
				printf("[FROM: HERB GARDEN] _> 36.Egg? %d / 37. Wool? %d / 38. Milk? %d\n", 
				C_List_Quantities[36], C_List_Quantities[37], C_List_Quantities[38]);
			}
				
			//ANIMAL 2
			if(animals[1]){
				printf("[FROM: BIRDHOUSES] _> 39.Flight Feather? %d / 40. Down Feather? %d / 41. Tail Feather? %d\n", 
				C_List_Quantities[39], C_List_Quantities[40], C_List_Quantities[41]);
			}
			
			//ANIMAL 3
			if(animals[2]){
				printf("[FROM: BEHIVE] _> 43.Honey? %d / 44. Pollen? %d / 45. Beeswax? %d\n\n", 
				C_List_Quantities[43], C_List_Quantities[44], C_List_Quantities[45]);
			}
		
		} 
		
		if(arr_limit_inv[2]){
		
			//FISHING
			if(memchr(ponds, true, sizeof(ponds)) != NULL)
			printf("\nFishing items [%d]\n\n", c_fishing_itm_c);
			
			//POND 1
			if(ponds[0]){
				printf("[FROM: TROUT POND] _> 47. ? Trout? %d / 48. Not a Trout? %d / 49. Strange Trout? %d / ", 
				C_List_Quantities[47], C_List_Quantities[48], C_List_Quantities[49]);
				printf("50. Undefined Trout? %d / 51. Lost Trout? %d / 52. Unknown Trout? %d\n", 
				C_List_Quantities[50], C_List_Quantities[51], C_List_Quantities[52]);
			}
			
			//POND 2
			if(ponds[1]){
				printf("[FROM: BASS POND] _> 54. Medium Bass? %d / 55. Atomic Bass? %d / 56. Enormous Bass? %d / ", 
				C_List_Quantities[54], C_List_Quantities[55], C_List_Quantities[56]);
				printf("57. Half Bass? %d / 58. Big Bass? %d / 59. Small Bass? %d\n", 
				C_List_Quantities[57], C_List_Quantities[58], C_List_Quantities[59]);
			}
			
			//POND 3
			if(ponds[2]){
				printf("[FROM: CARP POND] _> 61. Lilac Carp? %d / 62. Coral Carp? %d / 63. Lime Carp? %d / ", 
				C_List_Quantities[61], C_List_Quantities[62], C_List_Quantities[63]);
				printf("64. Lavender Carp? %d / 65. Rainbow Carp? %d / 66. Fulvous Carp? %d\n", 
				C_List_Quantities[64], C_List_Quantities[65], C_List_Quantities[66]);
			}
			
			//POND 4
			if(ponds[3]){
				printf("[FROM: CATFISH POND] _> 68. Wise Catfish? %d / 69. Dumb Catfish? %d / 70. Thinking Catfish? %d / ", 
				C_List_Quantities[68], C_List_Quantities[69], C_List_Quantities[70]);
				printf("71. Curious Catfish? %d / 72. Happy Catfish? %d / 73. Frowning Catfish? %d\n", 
				C_List_Quantities[71], C_List_Quantities[72], C_List_Quantities[73]);
			}
			
			//POND 5
			if(ponds[4]){
				printf("[FROM: SHINER POND] _> 75. Horizontal Shiner? %d / 76. Vertical Shiner? %d / 77. Oblique Shiner? %d / ", 
				C_List_Quantities[75], C_List_Quantities[76], C_List_Quantities[77]);
				printf("78. Non-Linear Shiner? %d / 79. Upside-down Shiner? %d / 80. Downside-up Shiner? %d\n", 
				C_List_Quantities[78], C_List_Quantities[79], C_List_Quantities[80]);
			}
			
			//POND 6
			if(ponds[5]){
				printf("[FROM: SNAPPER POND] _> 82. Fat Snapper? %d / 83. Skinny Snapper? %d / 84. Smooth Snapper? %d / ", 
				C_List_Quantities[82], C_List_Quantities[83], C_List_Quantities[84]);
				printf("85. Stiff Snapper? %d / 86. Soft Snapper? %d / 87. Rough Snapper? %d\n", 
				C_List_Quantities[85], C_List_Quantities[86], C_List_Quantities[87]);
			}
			
			//POND 7
			if(ponds[6]){
				printf("[FROM: TUNE POND] _> 89. Fast Tuna? %d / 90. Slow Tuna? %d / 91. Quick Tuna? %d / ", 
				C_List_Quantities[89], C_List_Quantities[90], C_List_Quantities[91]);
				printf("92. Dull Tuna? %d / 93. Speedy Tuna? %d / 94. Delayed Tuna? %d\n", 
				C_List_Quantities[92], C_List_Quantities[93], C_List_Quantities[94]);
			}
			
			//POND 8
			if(ponds[7]){
				printf("[FROM: SALMON POND] _> 96. Commun Salmon? %d / 97. Uncommun Salmon? %d / 98. Rare Salmon? %d / ", 
				C_List_Quantities[96], C_List_Quantities[97], C_List_Quantities[98]);
				printf("99. Epic Salmon? %d / 100. Legendary Salmon? %d / 101. Mythical Salmon? %d\n", 
				C_List_Quantities[99], C_List_Quantities[100], C_List_Quantities[101]);
			}
		
		} 
		
		if(arr_limit_inv[3]){
		
			//FORAGING
			if(memchr(trees, true, sizeof(trees)) != NULL)
			printf("\nForaging items [%d]\n\n", c_foraging_itm_c);
			
			if(C_List_Quantities[102] > 0)
			printf("[FROM: EVERYWHERE] _> 102. Stick? %d\n", C_List_Quantities[102]);
			
			//TREE 1
			if(trees[0]){
				printf("[FROM: FLOREST] _> 103. Pine Log? %d / 104. Hickory Log? %d / 105. Birch Log? %d / ", 
				C_List_Quantities[103], C_List_Quantities[104], C_List_Quantities[105]);
				printf("106. Ash Log? %d / 107. Willow Log? %d / ", 
				C_List_Quantities[106], C_List_Quantities[107]);
				printf("108. Bird nest? %d\n", C_List_Quantities[108]);
			}
			
			//TREE 2
			if(trees[1])
			printf("[FROM: CASCADE] _> 109. Mapple Log? %d / 110. Pinecone? %d\n", C_List_Quantities[109], C_List_Quantities[110]);
			
			
			//TREE 3
			if(trees[2]){
				printf("[FROM: GEYSERS] _> 111.Acacia Log? %d / ", C_List_Quantities[111]);
				printf("112. Oak Log? %d / 113. Medronhos Fruit? %d\n", C_List_Quantities[112], C_List_Quantities[113]);
			}
			
			//TREE 4
			if(trees[3])
			printf("[FROM: BLOSSOM] _> 114. Mimosa Log? %d / 115. Jackfruit? %d\n", C_List_Quantities [114], C_List_Quantities[115]);
			
		} 
		
		if(arr_limit_inv[4]){
					
			//ALL ALCHEMY
			if(Alchemy){
				printf("\nAlchemy items [%d]\n\n", c_alch_itm_c);
				
				printf("[ALCHEMY ITEMS (1)] _> 116. Refresher? %d / 117. Mint Tea? %d / 118. Woods Water? %d\n", 
				C_List_Quantities[116], C_List_Quantities[117], C_List_Quantities[118]);
				printf("[ALCHEMY ITEMS (2)] _> 119. Hidden Bush? %d / 120. Time Decline? %d / 121. Happy Acident? %d\n", 
				C_List_Quantities[119], C_List_Quantities[120], C_List_Quantities[121]);
				printf("[ALCHEMY ITEMS (3)] _> 122. Early Grave? %d / 123. Lots of Fish Bones? %d / 124. High risk, Low reward? %d / 125. Im Special! %d\n", 
				C_List_Quantities[122], C_List_Quantities[123], C_List_Quantities[124], C_List_Quantities[125]);
			}
		
		} 
		
		if(arr_limit_inv[5]){
		
			//ALL EXTRAS
			if(Extras){
				printf("\nExtra items [%d]\n\n", c_extra_itm_c);
				
				printf("[EXTRA ITEMS (1)] _> 126. Leaves? %d / 127. Algae? %d / 128. Japanese Iris? %d\n", 
				C_List_Quantities[126], C_List_Quantities[127], C_List_Quantities[128]);
				printf("[EXTRA ITEMS (2)] _> 129. Water Lily? %d / 130. Apple Snail? %d / 131. Mediterranean Tree Frog? %d\n", 
				C_List_Quantities[129], C_List_Quantities[130], C_List_Quantities[131]);
				printf("[EXTRA ITEMS (3)] _> 132. Iberian Water Frog? %d / 133. Giant Freshwater Prawn (Shrimp)? %d / 134. Golden Fish? %d\n", 
				C_List_Quantities[132], C_List_Quantities[133], C_List_Quantities[134]);
			}
		
		} 
		
		printf("\n");
			
		if(strcmp(bckp_chest_inp, "view")== 0){
		Small_stop;
		
		} else if(strcmp(bckp_chest_inp, "take")== 0){
			int call_id, call_quantity;
			
			while(true){
				printf("\nPlease select the ID of the item\n");
				printf("&/");
				scanf("%d", &call_id);
				
				if((call_id < 1 || call_id > 135) && C_List_Quantities[call_id] <= 0)
				printf("\n\nInvalid ID, dosent exist OR quantity of that ID is 0\n\n");
				
				else
				break;
			}
			
			while(true){
				printf("\nPlease select the QUANTITY of the item\n");
				printf("&/");
				scanf("%d", &call_quantity);
				
				if(call_quantity > C_List_Quantities[call_id])
				printf("\n\nInvalid QUANTITY, the quantity you are asking for is above the one you have :>\n\n");
				
				else
				break;
			}
			
			int returned_val = Inventory("CALC", call_id, call_quantity);
			
			if(returned_val == 0){
				green;
				printf("\n\nYou took out the items with no problem!\n\n");
				white;
				Small_stop;
			} else {
				C_List_Quantities[call_id] += returned_val;
				red;
				printf("\n\nYour inventory filled up, returning overflow items to your chest...\n\n");
				white;
				Small_stop;
			}
			
			break;
		}
		
		}
		
		CLR;
			
		} else if(strcmp(Input, "back")== 0){
			
			printf("You close the chest\n");
			sleep(2);
			break;
			
		} else { Error; } 
		
	}
	
	//After Inventory function is called, it retuns back to [PATH] \ LIVING DELUSION \ ACT1 \ SAVE?
	ChangeCurPath("CHEST_INVENTORY");
	
	int i;
	//Save the chest invntory in the files set in the CHEST dir
	FILE * fcrop = fopen("Crops.txt", "w");
	for(i = 1; i < 36; i ++)
	fprintf(fcrop, "%d\n", C_List_Quantities[i]);
	fclose(fcrop);
	
	FILE * fanimal = fopen("Animals.txt", "w");
	for(i = 36; i < 46; i ++)
	fprintf(fanimal, "%d\n", C_List_Quantities[i]);
	fclose(fanimal);
	
	FILE * ffish = fopen("Fish.txt", "w");
	for(i = 46; i < 102; i ++)
	fprintf(ffish, "%d\n", C_List_Quantities[i]);
	fclose(ffish);
	
	FILE * fforaging = fopen("Foraging.txt", "w");
	for(i = 102; i < 116; i ++)
	fprintf(fforaging, "%d\n", C_List_Quantities[i]);
	fclose(fforaging);
	
	FILE * falchemy = fopen("Alchemy.txt", "w");
	for(i = 116; i < 126; i ++)
	fprintf(falchemy, "%d\n", C_List_Quantities[i]);
	fclose(falchemy);
	
	FILE * fextras = fopen("Extras.txt", "w");
	for(i = 126; i < 135; i ++);
	fprintf(fextras, "%d\n", C_List_Quantities[i]);
	fclose(fextras);
	
	FILE * futility = fopen("Utility.txt", "w");
	fprintf(futility, "%d\n", C_List_Quantities[135]);
	fclose(futility);
	
	chdir("..");
	
}

void Pit(void){
	//Story line vars
	char knows_ab_pit [5];
	
	//Other vars
	char tut_pit_input [10]; 
	int name_lengt;
	
    CLR;
    
    int pit_jumps = 69;
    
    ChangeCurPath("ACHIVEMENTS.Progress");
    if(access("PitJumps.txt", F_OK)== 0){
	    FILE * fpitj = fopen("PitJumps.txt", "r");
	    fscanf(fpitj, "%d", pit_jumps);
	    fclose(fpitj);
    }
    
    //Checking if its the first time here or not
    if(pit_jumps == 1){
    	
	    //1st time custom dialogue
	    strcpy(Talked_to_pit_wiz, "YES");
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
		printf("You got knocked out from the fall\n");
		printf("[NPC] Severus: \"What the hell? Annother one?\"\n");
		printf("You feel the strange man pick you up with caution\n");
		printf("You wake up in a strange house\n");
		printf("[NPC] Severus: \"Ah, you're finnaly awake\"\n");
		printf("[NPC] Severus: \"Tell me, stranger, what is your name?\"\n");
		printf("My name is...\n");
		
		while(true){
			printf("[HELP] _> Only 50 charecters long allowed and no special charecters\n");
			printf("&/");
			scanf("%s", User_Name);
			
			CLR;
			
			name_lengt = strlen(User_Name);
			
			if(name_lengt > 50){
				red;
				printf("Name too long :(\n");
				white;
				sleep(1);
			} else {
				break;
			}
			
		}
		
		printf("[NPC] Severus: \"Oh nice to meet you, %s, tell me, what brings you here?\"\n", User_Name);
		
		while(true){
			bool sent_by_wizard = false, knows_ab_pit = false;
			
			//Get Triggers
			ChangeCurPath("OTHER.triggers.story");
			if(access("WizardSpecifics.txt", F_OK)== 0){
				FILE * fwizstory = fopen("WizardSpecifics.txt", "r");
				fscanf(fwizstory, "%d", &sent_by_wizard);
				fclose(fwizstory);
			}
			
			if(access("KnowsPit.txt", F_OK)== 0){
				FILE * fknows = fopen("KnowsPit.txt", "r");
				fscanf(fknows, "%d", &knows_ab_pit);
				fclose(fknows);
			}
			
			printf(">About the pit [Pit]\n");
			
			if(sent_by_wizard)
			printf(">I was sent here by Boise [Boise]\n");
			
			if(knows_ab_pit)
			printf(">Im going to explore around...[Explore]\n");
			
			printf(">I want to go back [Back]\n");
			String_Input;
			
			if (strcmp(Input, "pit")== 0){
				
				printf("[NPC] Severus: \"I still dont know why they call it the pit, but, forget everything you heard about the \"Pit\" because everything you think you knows its probably wrong\n");
				printf("[NPC] Severus: \"Well, we are actually just inside a big mountain, outside this house its a smaller cave that has exit to the main mountain, go explore the cave and the entrance to the outside!\"\n");
				Small_stop;
				knows_ab_pit = true;
				
			} else if (strcmp(Input, "boise")== 0){
				
				printf("[NPC] Severus: \"Oh my old brother sent you? Haha, i knew he was still alive.\"\n");
				printf("[NPC] Severus: \"Ill make sure to give him a visit soon, just let him know im still alive\"\n");
				printf("[NPC] Severus: \"You know, he used to explore the mountain too with some girl\"\n");
				Small_stop;
				
			} else if (strcmp(Input, "explore")== 0){
				
				if(knows_ab_pit){
					
					printf("[NPC] Severus: \"Go explore a little bit, ill tell you our main objective and tell you more about the montain when you come back\"\n");
					printf("You exit the small but cosy house and found yourself at a very small cave, with one big exit\n");
					printf("The exit looks natural, very big hole in the wall, giving access to the montain\n");
					printf("Not long after you go back to the cosy house\n");
					Small_stop;
					int keys = 0;
					Mountain("day");
				
				} else {
					printf("[HELP] _> You need to know a bit more about the Pit first!\n");
					sleep(3);
				}
				
			} else if(strcmp(Input, "back")== 0){
			
				printf("[NPC] Severus: \"Alright, ill see you later then...\"\n");
				sleep(3); CLR; break;
			
			} else { Error; }
			
			CLR;
			
			//Register trigger
			FILE * fknows = fopen("KnowsPit.txt", "w");
			fprintf(fknows, "%d", knows_ab_pit);
			fclose(fknows);
			
		} //Loop end
	
	}
	
	int Keys = 0;
	
	ChangeCurPath("STORY");
	short int * temp = (short int*)malloc(1);
	//Get trigger status
	FILE * fkeysdone = fopen("Keysdone.txt", "r");
	fscanf(fkeysdone, "%d\n", temp);
	if(*temp >= 1)
	Keys ++;
	fclose(fkeysdone);
	
	bool knows_ab_goal = false;
	//Get Triggers
	ChangeCurPath("OTHER.triggers.story");
	if(access("KnowsAboutGoal.txt", F_OK)== 0){
		FILE * fknows = fopen("KnowsAboutGoal.txt", "r");
		fscanf(fknows, "%d", &knows_ab_goal);
		fclose(fknows);
	}
	
	while(true){
		//dialogue after 1st time 
			
		printf("[NPC] Severus: \"So? What should we discuss?\"\n");
		printf(">(Our) Goal [Goal]\n");
		printf(">About the mountain [Mountain]\n");
		
		if(knows_ab_goal){
			printf(">How to get the keys [Keys]\n");
			printf(">How to climb the top[Top]\n");
		}
		
		printf(">Im going to explore now, bai bai [Leave]\n");
		printf(">I want to go back up [Up]\n");
		
		String_Input;
		
		if(strcmp(Input, "goal")== 0){
			
			printf("[NPC] Severus: \"So, our goal is to collect ");
			yellow;
			printf("KEYS");
			white;
			printf(" hidden in the mountain, for example, they usually hide in caves inside the mountain and outside the surface\"\n");
			printf("[NPC] Severus: \"So, exploring the mountain should be our top priority BUT, you cant go to the Peak yet, its very dangerous you will probably freeze to death\"\n");
			printf("[NPC] Severus: \"You should avoid the Peak and just collect matherials to complete the puzzles and get the ");
			yellow;
			printf("KEYS");
			white;
			printf(" also, there are around 6 keys we need, so good luck!\"\n");
			printf("[NPC] Severus: \"Ill be here if you need help to get back up to the cave or want to talk about your progress\"\n");
			printf("[NPC] Severus: \"Now that i have someone that is willing to help me save this world i will put double the time into researching how to survive the Peak!\"\n");
				
			Small_stop;
			
			knows_ab_goal = true;
			
		} else if(strcmp(Input, "mountain")== 0){
			
			printf("Map pixel art go here\n\n");
			
			printf("[NPC] Severus: \"So, there are 7 places we NEED to explore, those being:\"\n");
			printf("[NPC] Severus: \"[List of locations here]\"\n");
			printf("[NPC] Severus: \"All these locations have a teleporter attached to them but you need to activate them\"\n");
			printf("[NPC] Severus: \"What are teleporters? Well my wizzard bother made them for me so i can travel around the montain easier\"\n");
			printf("[NPC] Severus: \"I havent used them in a while, so you might need to fix them, but they should work fine afterwards\"\n");
			printf("[NPC] Severus: \"EVERY, BUT I MEAN EVERY location we need to explore has one, so, use them.\"\n");
			Small_stop;
			
		} else if(strcmp(Input, "keys")== 0){
			
			if(!knows_ab_goal){
			Error;
			
			} else { 
				
				//Diferent Hints depending on number of keys found
				switch(Keys){
					
					//Initiating key hunt, AKA getting the user to know they need to find "rituals" and do puzzles for the keys
					case 0:
						printf("[NPC] Severus: \"Oh the keys? Right, i think they have to be done in a specific order or something\"\n");
						printf("[NPC] Severus: \"In my times of exploring, there where roman numbers on top of the ritual entrances where you can solve puzzles for the keys\"\n");
						printf("[NPC] Severus: \"Just look up and do them in order and it should be fine, at least i hope so\"\n");
						printf("[NPC] Severus: \"Let me know if you need help finding the rituals locations, i have a small diary from someone named \"Celestia\" i found down there with cryptic notes\"\n");
						printf("[NPC] Severus: \"Maybe i can help you find the next ritual(s) location(s), but the puzzles are up to you, im too old for it, haha...\"\n");
						
						Small_stop;
				}
			
			}
			
		} else if(strcmp(Input, "top")== 0){
			
			if(!knows_ab_goal){
			Error;
			
			} else { 
				
				if(Keys != 5)
				printf("[NPC] Severus: \"Why are you asking my about the top? Just go get the other keys there is still a lot i need to figure out before we can start exploring it\"\n");
				
				else {
					//Dialogue to get to the top
				}
				
			}
			
		} else if(strcmp(Input, "leave")== 0){
		
			printf("[NPC] Severus: \"See you later then, if you come back alive, that is\"\n");
			sleep(3);
			CLR;
			break;
			
		} else if(strcmp(Input, "up")== 0){
			
			printf("[NPC] Severus: \"Alright, you're going to fall again though, see ya\"\n");
			sleep(3);
			CLR;
			Act1();
			break;
			
		} else { Error; }
		
		CLR;
		
	} //Outside loop

	//Register possible changes done
	ChangeCurPath("OTHER.triggers.story");
	FILE * fknows = fopen("KnowsAboutGoal.txt", "w");
	fprintf(fknows, "%d", knows_ab_goal);
	fclose(fknows);
		
	//Change to the story dir
	ChangeCurPath("STORY.Locations");
	
	//Change where ur supost to go
	char cur_loc [7] = "Forest";
	FILE * floc = fopen("Current.txt", "w");
	fprintf(floc, "Forest");
	fclose(floc);
	
	Mountain("new");
	Mountain("move");
	
	/*
	shet we need for THIS function still:
	
	Entry is Pit (Make pit a more movable thing)
	like 3 rooms so user can learn the basics of the mountain
	
	Note for when user gets sign compass
	
	printf("[NPC] Severus: \"You seem to be ready\"\n");
	printf("[NPC] Severus: \"It is very eazy to get lost in the mountain\"\n");
	printf("[NPC] Severus: \"Like i told you though, there are some signs and a book in each \"layer\"\"\n");
	printf("[NPC] Severus: \"If you get lost, use this compass to guide yourself back to the signs!\"\n");
	printf("[NPC] Severus: \"This compass ALWAYS points to the signs, wherever you are\"\n");
	printf("[NPC] Severus: \"Have fun exploring the mountain!\"\n\n");
	
	yellow;
	printf("[HELP] _> Type \"item\" to use an item or drink a potion!\n\n");
	white;
	
	Small_stop;
	*/
}

//Scary function, please ignore
void Mountain(const char * what){
	
	//Variables we ALWAYS need
	static bool is_in_signs = false, is_in_key = false, is_in_special_loc = false, is_in_story_loc = false, is_in_minigame = false; 
	static bool is_in_ladder = false, is_in_bridge = false, is_in_pit = false, normal_movement = true, movement_fail = false;
	static bool is_following_signs = false, is_following_key = false, is_following_special = false, is_following_minigame = false, is_following_exit = false;
	static char Movement_Made [10] = { '\0' };
	static int prt_displacement = 0, passes_made = 0, cur_Y = 0, cur_X = 0, last_item_code_used = 0, INT_minigame_type = 0;
	
	char current_location [10] = { '\0' };
	int INT_current_location = 0;
	const char All_Locations [7] [8] = { "Entry", "Forest", "Cascade", "Fungi", "Geysers", "Blossom", "Peak" };
	
	//Get location
	ChangeCurPath("STORY.Locations");
	FILE * fcurloc = fopen("Current.txt", "r");
	fscanf(fcurloc, "%s", current_location);
	fclose(fcurloc);
	
	//Change to location path for specific things in files
	ChangeCurPath("STORY.Locations");
	CatCurPath(current_location);
	
	//Get INT value for current location (used in later calculations)
	for(int i = 0; i < 7; i ++){
		if(strcmp(current_location, All_Locations[i])== 0)
		INT_current_location = i;
	}
	
	if(strcmp(what, "move")== 0){
	
		if(access("LastPositionRecorded.txt", F_OK)== 0){
			//Getting stuff needed
			int * temp = (int *)malloc(2);
			
			//Check for LOCKED IN positions
			FILE * fisuserinspecialspots = fopen("LastPositionRecorded.txt", "r");
			fscanf(fisuserinspecialspots, "%d\n", temp);
			is_in_signs = *temp;
			
			fscanf(fisuserinspecialspots, "%d\n", temp);
			is_in_key = *temp;
			
			fscanf(fisuserinspecialspots, "%d\n", temp);
			is_in_special_loc = *temp;	
			
			fscanf(fisuserinspecialspots, "%d\n", &cur_X);
			
			fscanf(fisuserinspecialspots, "%d\n", &cur_Y);
			
			free(temp);
			fclose(fisuserinspecialspots);
			
			remove("LastPositionRecorded.txt");
		}
		
		if(cur_X == 0 && cur_Y == 0)
		is_in_signs = true;
		
		static int randomized_thing = 0, special_loc_INT = 0;
		
		//Assisting variable for ART to show new art
		if(!movement_fail){
			randomized_thing = rand()% 10 + 1;
			special_loc_INT = rand()% 15 + 1;
		}	
	
		//(what the fuck do we display) Arts lmfao
		//Normal art display (ignore the condition)
		if(normal_movement && !is_in_key && !is_in_story_loc && !is_in_signs && !is_in_special_loc &&
		!is_in_ladder && !is_in_pit && !is_in_bridge && !is_in_minigame)
		Art(current_location, randomized_thing);
		
		else if(is_in_special_loc)				//Display special loc entrance (code -2 says its special loc)
		Art(current_location, -2);
		
		else if(is_in_key)						//Display key entrance (code -1 says its key)
		Art(current_location, -1);
		
		else if(is_in_signs)					//Display signs (code 0 says its signs)
		Art(current_location, 0);			
		
		else if(is_in_minigame){				//Display minigame depending on the code gotten
			/*
			TABLE OF VALUES:
			
			-10 = Crop
			-9 	= Animal
			-8	= Fish
			-15 = Tree (Non Invasive)
			-14 = Tree (Invasive)
			*/
			
			int temp_INT = INT_minigame_type - 10;
			if(INT_minigame_type >= 30)
			temp_INT -= 35;
			
			Art(current_location, temp_INT);
		}
		
		else if(is_in_story_loc)				//Display story related location
		Art("GLOBALLOCS", special_loc_INT);
		
		else if(is_in_ladder)					//Display Ladder
		Art("GLOBALLOCS", 0);
		
		else if(is_in_pit)						//Display Pit
		Art("GLOBALLOCS", -1);
		
		else if(is_in_bridge)					//Display Bridge
		Art("GLOBALLOCS", -2);
	
		else {
			if(!DEBUG_MODE){
				red;
				MidScreenText("ERROR ON DISPLAYING ART [ERR. ART]\n");
				white;
				
			} else {
				printf("[DEBUG] _> normal_movement? %d\n", normal_movement);
				printf("[DEBUG] _> is_in_key? %d\n", is_in_key);
				printf("[DEBUG] _> is_in_story_loc? %d\n", is_in_story_loc);
				printf("[DEBUG] _> is_in_signs? %d\n", is_in_signs);
				printf("[DEBUG] _> is_in_special_loc? %d\n", is_in_special_loc);
				printf("[DEBUG] _> is_in_ladder? %d\n", is_in_ladder);
				printf("[DEBUG] _> is_in_pit? %d\n", is_in_pit);
				printf("[DEBUG] _> is_in_bridge? %d\n", is_in_bridge);
				printf("[DEBUG] _> is_in_minigame? %d\n", is_in_minigame);	
			}
		}
		
		ChangeCurPath("STORY.Locations");
		CatCurPath(current_location);
		
		//Display next compass position if it wants to display a new one
		if(is_following_signs || is_following_minigame)
		Mountain("newcompassloc");
	
		//REMOVE LATER
		is_in_minigame = true;
	
		String_Input;
		
		memset(Movement_Made, '\0', sizeof(Movement_Made));
		strcpy(Movement_Made, Input);
	
		//Story location information
		if(is_in_story_loc){
			ChangeCurPath("STORY.Locations");
			CatCurPath(current_location);
			FILE * fstorylocinfo = fopen("IsInStoryLoc.txt", "w");
			fprintf(fstorylocinfo, "%d", special_loc_INT);
			fclose(fstorylocinfo);
		} 
	
		movement_fail = false;
		Mountain("getinput");
		
		//This is to randomize story locations
		if(!is_following_signs && !is_following_key && !is_following_special && !is_following_minigame && !is_following_exit &&
		!movement_fail && !is_in_key && !is_in_story_loc && !is_in_signs && !is_in_special_loc && !is_in_minigame &&
		!is_in_ladder && !is_in_pit && !is_in_bridge){
			if(rand()% 15 + 1 == 1){
				int random_location = rand()% 3 + 1;
				
				if(strcmp(current_location, "Fungi")!= 0)
				random_location = rand()% 2 + 1;
				
				if(random_location == 1)
				is_in_story_loc = true;
				
				if(random_location == 2){
					Mountain("newminigame");
					is_in_minigame = true;	
				}
					
				normal_movement = false;
				
			} else
			normal_movement = true;
		} else
		normal_movement = true;
		
		Mountain("move");
	
	} else if(strcmp(what, "newcompassloc")== 0){			//generate new path for mini game with compass
	
		/*
		Here is the compass ID list:
		
		0 -> Signs
		1 -> Crop
		2 -> Animal
		3 -> Fish
		4 -> Tree
		
		And Here is inside CompassListOfMovements.txt:
		[Compass X Pos]
		[Compass Y Pos]
		*/
		
		//If we alr have user following something we need to give bro the next position predicted
		if(access("CompassFinalLocation.txt", F_OK)== 0 && (is_following_signs || is_following_minigame)){
			char compass_predicted_location [15] = { '\0' };  
			const char all_movements [5] [15] = { "\0" , "Backward", "Right", "Left", "Foward" }; 
			
			int temp_pos1 = 0, temp_pos2 = 0, comp_X = 0, comp_Y = 0;
			bool try_X = false, try_Y = false;
			
			FILE * fgetcompassfinalpos = fopen("CompassFinalLocation.txt", "r");
			fscanf(fgetcompassfinalpos, "%d", &comp_X);
			fscanf(fgetcompassfinalpos, "%d", &comp_Y);
			fclose(fgetcompassfinalpos);
			
			//Lets PREDICT the next movement
			if(rand()% 2 + 1 == 1){
				if(cur_X == comp_X)
				try_Y = true;
				
				else
				try_X = true;
				
			} else {
				if(cur_Y == comp_Y)
				try_X = true;
				
				else
				try_Y = true;
			}
			
			//Calc next displacement
			if(try_X){
				if((cur_X + 1) - comp_X <= 0)
				strcpy(compass_predicted_location, all_movements[2]);
				
				else
				strcpy(compass_predicted_location, all_movements[3]);
				
			} else if(try_Y){
				if((cur_Y + 1) - comp_Y <= 0)
				strcpy(compass_predicted_location, all_movements[4]);
				
				else
				strcpy(compass_predicted_location, all_movements[1]);
				
			}
			
			yellow;
			
			ChangeCurPath("OTHER.temp");
			FILE * fsetformatingvars = fopen("FormatingVarTemp.txt", "w");
			fprintf(fsetformatingvars, "24\n");
			fprintf(fsetformatingvars, "%s\n", compass_predicted_location);
			fclose(fsetformatingvars);
			
			FormatTextEXT("center", "The compass is pointing !", true, 0, ".", true, 0, 0);
			white;
			
			ChangeCurPath("STORY.Locations");
			CatCurPath(current_location);
			return;
		}
		
		if(is_following_minigame || is_following_signs){
			red;
			printf("You are already using another compass!\n");
			white;
			return;
		}
		
		if(last_item_code_used == 51)
		is_following_signs = true;
		
		else if(last_item_code_used >= 52 && last_item_code_used <= 56)
		is_following_minigame = true;
		
		char temp_buffer [10] = { '\0' };
		int check = 0, compass_X = 0, compass_Y = 0;
		
		//Checking if minigame exists in this position
		char * temp_path_saver = (char *)malloc(MAX_PATH);
		memset(temp_path_saver, '\0', sizeof(temp_path_saver));
		
		getcwd(temp_path_saver, MAX_PATH);
		GetAppResources("Usefull Files.Mountain");
		
		char temp_file [15] = { '\0' };
		strcpy(temp_file, current_location);
		strcat(temp_file, ".txt");
				
		FILE * fcheckifminigameexists = fopen(temp_file, "r");
		
		for(int i = 0; i < last_item_code_used - 52; i ++)
		fgets(temp_buffer, 10, fcheckifminigameexists);
		
		fscanf(fcheckifminigameexists, "%d\n", &check);
		fclose(fcheckifminigameexists);
		
		//Move to last dir again
		chdir(temp_path_saver);
		free(temp_path_saver);
		
		if(check == 0){
			is_following_minigame = false;
			CLR;
			red;
			CenterText("Your compass is spinning in circles! It couldnt find that structure!");
			white;
			Small_stop;
			return;
		}
		
		if(is_following_signs){
			compass_X = 0, compass_Y = 0;
		
		//Getting compass position (We need to do probability calculations with this)
		} else {
			ChangeCurPath("INVENTORY");
			char expected_minigame [15];
			
			FILE * fgetcompasspointingto = fopen("SpecialStats.txt", "r");
			fscanf(fgetcompasspointingto, "%s", expected_minigame);
			fclose(fgetcompasspointingto);
			
			ChangeCurPath("STORY.Locations");
			CatCurPath(current_location);
			
			//Register the fuckin minigame :yippie:
			FILE * fforcethisminigamepls = fopen("CompassMinigame.txt", "w");
			
			//Turn what minigame we are on into a INT constant
			if(strcmp(expected_minigame, "CROP")== 0)
			fprintf(fforcethisminigamepls, "0\n");
			
			else if(strcmp(expected_minigame, "ANIMAL")== 0)
			fprintf(fforcethisminigamepls, "1\n");
			
			else if(strcmp(expected_minigame, "FISH")== 0)
			fprintf(fforcethisminigamepls, "2\n");
			
			else if(strcmp(expected_minigame, "TREE")== 0)
			fprintf(fforcethisminigamepls, "3\n");
			
			fclose(fforcethisminigamepls);
			
			while(true){
				bool valid = true;
				
				//Calc compass X
				if(rand()% 2 + 1 == 1)
				compass_X = cur_X + (rand()% 12 + 1);
					
				else
				compass_X = cur_X - (rand()% 12 + 1);
				
				//Calc compass Y
				if(rand()% 2 + 1 == 1)
				compass_Y = cur_Y + (rand()% 12 + 1);
				
				else
				compass_Y = cur_Y - (rand()% 12 + 1);
				
				int loc1_X = 0, loc2_X = 0, loc1_Y = 0, loc2_Y = 0;
				
				FILE * ffinallocations = fopen("FinalLocations.txt", "r");
				fscanf(ffinallocations, "%d\n", &loc1_X);			
				fscanf(ffinallocations, "%d\n", &loc1_Y);			
				fscanf(ffinallocations, "%d\n", &loc2_X);				
				fscanf(ffinallocations, "%d\n", &loc2_Y);				
				fclose(ffinallocations);
				
				if((compass_X == loc1_X && compass_Y == loc1_Y) ||
				   (compass_X == loc2_X && compass_Y == loc2_Y))
				valid = false;
				
				if(valid)
				break;
			}			
			
		}
		
		//Register final X/Y position
		if(access("CompassFinalLocation.txt", F_OK)!= 0){
			FILE * fcompasslocations = fopen("CompassFinalLocation.txt", "w");
			fprintf(fcompasslocations, "%d\n", compass_X);
			fprintf(fcompasslocations, "%d\n", compass_Y);
			fclose(fcompasslocations);	
		}
	
		last_item_code_used = 0;
		return;
		
	} else if(strcmp(what, "new")== 0){				//generate new paths
		
		//Idk if peak has movement (?)
													//This one is temporary, prob gn delete soon
		if(strcmp(current_location, "Entry")!= 0 && strcmp(current_location, "Peak")!= 0 && access(current_location, F_OK)!= 0){
			//Create new																//(^ this one also checks if the directory does NOT exist)
			mkdir(current_location);
			ChangeCurPath("STORY.Locations");
			CatCurPath(current_location);
			
			int special_X = 0, special_Y = 0, key_X = 0, key_Y = 0;
			
			//Make needed files and stuff
			while(true){
				key_Y = 0, key_X = 1;
				FILE * fkeypath = fopen("KeyPath.txt", "w");
				fprintf(fkeypath, "right\n");
				
				//Generate new path
				for(int i = 0; i < 15; i ++){
					int next_placement = rand()% 4 + 1;
					switch(next_placement){
						case 1:
							fprintf(fkeypath, "forward\n");
							key_Y ++;
							break;
							
						case 2:
							fprintf(fkeypath, "left\n");
							key_X --;
							break;
							
						case 3:
							fprintf(fkeypath, "right\n");
							key_X ++;
							break;
							
						case 4:
							fprintf(fkeypath, "backward\n");
							key_Y --;
							break;
							
						default:
							break;
					}	
				}
				
				fclose(fkeypath);
				
				if(DEBUG_MODE && key_X == 0 && key_Y == 0)
				printf("[DEBUG] _> Key location is in spawn! (0,0)\n");
				
				else if(key_X != 0 && key_Y != 0)
				break;
			}
			
			while(true){
				special_Y = 0, special_X = -1;
				FILE * fspecialpath = fopen("SpecialPath.txt", "w");
				fprintf(fspecialpath, "left\n");
				
				//Generate new path
				for(int i = 0; i < 15; i ++){
					int next_placement = rand()% 4 + 1;
					switch(next_placement){
						case 1:
							fprintf(fspecialpath, "forward\n");
							special_Y ++;
							break;
							
						case 2:
							fprintf(fspecialpath, "left\n");
							special_X --;
							break;
							
						case 3:
							fprintf(fspecialpath, "right\n");
							special_X ++;
							break;
							
						case 4:
							fprintf(fspecialpath, "backward\n");
							special_Y --;
							break;
							
						default:
							break;
					}	
				}
				
				fclose(fspecialpath);
				
				if(DEBUG_MODE && special_X == key_X && special_Y == key_Y)
				printf("[DEBUG] _> Special Location next to key location! (%d,%d)\n", special_X, special_Y);
				
				else if(special_X != 0 && special_Y != 0)
				break;
			}
			
			/*
			Inside LastPositionRecorded.txt:
			
			[IsInSigns] 	- Boolean Value
			[IsInKey] 		- Boolean Value
			[IsInSpecLoc]	- Boolean Value
			[UserXPos]		- Int Value
			[UserYPos]		- Int Value
			*/
			
			FILE * flastposrec = fopen("LastPositionRecorded.txt", "w");
			
			//Get user X position
			while(true){
				cur_X = rand()% 10 + 1;
				cur_X -= 5;
				
				if(cur_X != special_X && cur_X != key_X)
				break;	
			}
			
			//Get user Y position
			while(true){
				cur_Y = rand()% 10 + 1;
				cur_Y -= 5;
				
				if(cur_Y != special_Y && cur_Y != key_Y)
				break;	
			}
			
			if(cur_X == 0 && cur_Y == 0)
			fprintf(flastposrec, "1\n0\n0\n");
			
			else
			fprintf(flastposrec, "0\n0\n0\n");
			
			fprintf(flastposrec, "%d\n%d\n", cur_X, cur_Y);
			fclose(flastposrec);
			
			FILE * ffinallocations = fopen("FinalLocations.txt", "w");
			fprintf(ffinallocations, "%d\n", key_X);					//key X
			fprintf(ffinallocations, "%d\n", key_Y);					//key Y
			fprintf(ffinallocations, "%d\n", special_X);				//special X
			fprintf(ffinallocations, "%d\n", special_Y);				//special Y
			fclose(ffinallocations);
			
		}
		
		return;
		
	} else if(strcmp(what, "getinput")== 0){			//if user is interacting with specific stuff
		
		if(strcmp(Movement_Made, "forward")== 0 ||
		strcmp(Movement_Made, "left")== 0 ||
		strcmp(Movement_Made, "right")== 0 ||
		strcmp(Movement_Made, "backward")== 0){
			
			//Get user X/Y position
			if(strcmp(Movement_Made, "forward")== 0)
			cur_Y ++;
			
			else if(strcmp(Movement_Made, "left")== 0)
			cur_X --;
			
			else if(strcmp(Movement_Made, "right")== 0)
			cur_X ++;
			
			else
			cur_Y --;
			
			if(DEBUG_MODE)
			printf("[DEBUG] _> User X? %d / User Y? %d\n", cur_X, cur_Y);
			
			//Check starter path
			if(strcmp(Movement_Made, "left")== 0 && is_in_signs){
				prt_displacement = 0;
				is_following_special = true;
			}
			
			else if(strcmp(Movement_Made, "right")== 0 && is_in_signs){
				prt_displacement = 0;
				is_following_key = true;
			}
			
			else if(strcmp(Movement_Made, "backward")== 0 && is_in_signs){
				prt_displacement = 0;
				is_following_exit = true;
			}
			
			//Leave current location if you arent interacting with it
			if(is_in_signs)
			is_in_signs = false;
			
			if(is_in_story_loc)
			is_in_story_loc = false;
			
			if(is_in_special_loc)
			is_in_special_loc = false;
			
			if(is_in_key)
			is_in_key = false;
		
			if(is_in_ladder)
			is_in_ladder = false;
			
			if(is_in_pit)
			is_in_pit = false;
			
			if(is_in_bridge)
			is_in_bridge = false;
			
			if(is_in_minigame)
			is_in_minigame = false;
			
			//Check if user is in constant locations or not
			int temp_X = 0, temp1_X = 0, temp_Y = 0, temp1_Y = 0;
			
			FILE * fgetconstpositions = fopen("FinalLocations.txt", "r");
			fscanf(fgetconstpositions, "%d\n", &temp_X);
			fscanf(fgetconstpositions, "%d\n", &temp_Y);
			fscanf(fgetconstpositions, "%d\n", &temp1_X);
			fscanf(fgetconstpositions, "%d\n", &temp1_Y);
			fclose(fgetconstpositions);
		
			if(cur_X == 0 && cur_Y == 0){
				is_in_signs = true;
				//Need to stop compass (if user is using compass)
				if(is_following_signs){
					remove("CompassFinalLocation.txt");
					is_following_signs = false;
				}	
			}
			
			else if(cur_X == temp_X && cur_Y == temp_Y)
			is_in_key = true;
			
			else if(cur_X == temp1_X && cur_Y == temp1_Y)
			is_in_special_loc = true;
			
			//Check if user is in the right minigame position
			if(is_following_minigame){
				FILE * fgetfinalcompasspos = fopen("CompassFinalLocation.txt", "r");
				fscanf(fgetfinalcompasspos, "%d\n", &temp_X);
				fscanf(fgetfinalcompasspos, "%d\n", &temp_Y);
				fclose(fgetfinalcompasspos);
				
				if(cur_X == temp_X && cur_Y == temp_Y){
					is_in_minigame = true;
					Mountain("newminigame");
					is_following_minigame = false;	
					remove("CompassFinalLocation.txt");
				}
			}
			
			//Check if user is still going in the right path
			if(is_following_special){
				char check_move_made [10] = { '\0' };
				FILE * fnextspecialpos = fopen("SpecialPath.txt", "r");
				
				fseek(fnextspecialpos, prt_displacement, SEEK_SET);
				fscanf(fnextspecialpos, "%s\n", check_move_made);
				
				int temp = ftell(fnextspecialpos); 
				prt_displacement += temp;
				
				if(strcmp(Movement_Made, check_move_made)== 0)
				passes_made ++;
				
				else {
					is_following_special = false;
					passes_made = 0;
					prt_displacement = 0;
				}
				
				//Arrived at ur destination
				if(passes_made >= 15){
					is_in_special_loc = true;
					is_following_special = false;
					passes_made = 0;
					prt_displacement = 0;
				}
				
				fclose(fnextspecialpos);
				
			} else if(is_following_key){
				char check_move_made [10] = { '\0' };
				FILE * fnextkeypos = fopen("KeyPath.txt", "r");
				
				fseek(fnextkeypos, prt_displacement, SEEK_SET);
				fscanf(fnextkeypos, "%s\n", check_move_made);
				
				int temp = ftell(fnextkeypos); 
				prt_displacement = temp;
				
				if(strcmp(Movement_Made, check_move_made)== 0)
				passes_made ++;
				
				else {
					is_following_key = false;
					passes_made = 0;
					prt_displacement = 0;
				}
				
				//Arrived at ur destination
				if(passes_made >= 15){
					is_in_key = true;
					is_following_key = false;
					passes_made = 0;
					prt_displacement = 0;
				}
				
				fclose(fnextkeypos);
				
			} else if(is_following_exit){
				GetAppResources("Usefull Files.Mountain");
				
				char check_move_made [10] = { '\0' };
				FILE * fnextkeypos = fopen("ExitPath.txt", "r");
				
				fseek(fnextkeypos, prt_displacement, SEEK_SET);
				fscanf(fnextkeypos, "%s\n", check_move_made);
				
				int temp = ftell(fnextkeypos); 
				prt_displacement = temp;
				
				if(strcmp(Movement_Made, check_move_made)== 0)
				passes_made ++;
				
				else {
					is_following_exit = false;
					passes_made = 0;
					prt_displacement = 0;
				}
				
				//Arrived at ur destination
				if(passes_made >= 7){
					//Randomize what exit type it is
					if(rand()% 2 + 1 == 1){
						if(strcmp(current_location, "Blossom")!= 0)
						is_in_pit = true;	
						
						if(strcmp(current_location, "Blossom")== 0)
						is_in_bridge = true;
						
					} else {
						if(strcmp(current_location, "Geysers")!= 0)
						is_in_ladder = true;
						
						if(strcmp(current_location, "Geysers")== 0)
						is_in_bridge = true;	
					}
				
					is_following_exit = false;
					passes_made = 0;
					prt_displacement = 0;
				}
				
				fclose(fnextkeypos);
			}
			
		} else if(strcmp(Movement_Made, "read")== 0 && is_in_signs){
			
			CLR;
			while(true){
				white;
				printf("Before you, there are 2 signs telling the directions of the key and the special location\n");
				printf("What location do you seek?\n");
				printf(">Key\n");
				printf(">Special Location [Special]\n");
				String_Input;
				
				char next_path [30] = { '\0' };
				printf("You read the sign:\n");
				printf("Follow the directions carefully or you might get lost:\n\n");
				
				//Extract the information thats in file
				gray;
				if(strcmp(Input, "key")== 0){
					FILE * fpath = fopen("KeyPath.txt", "r");
					
					while(fscanf(fpath, "%s\n", next_path)!= EOF){
						CenterText(next_path);
						memset(next_path, '\0', sizeof(next_path));	
					}
					
					fclose(fpath);
					break;
					
				} else if(strcmp(Input, "special")== 0){
					FILE * fpath = fopen("SpecialPath.txt", "r");
					
					while(fscanf(fpath, "%s\n", next_path)!= EOF){
						CenterText(next_path);
						memset(next_path, '\0', sizeof(next_path));	
					}
					
					fclose(fpath);
					break;
					
				} else {
					Error;
				}
			}
			
			white;
			
			printf("\n");
			Small_stop;
			Mountain("move");
			
		} else if(strcmp(Movement_Made, "book")== 0 && is_in_signs){	//Book lol
			
			if(access("HasBookUnlocked.txt", F_OK)!= 0 && last_item_code_used == 0){
				red; 			printf("This book is currently out-of-order.\n"); //Modify const value bellow
				char * getthis = GetItemName(211 + INT_current_location);
				green; 	printf("Go fetch a \"%s\" to fix this book!\n", getthis);
				free(getthis);	
				yellow;			printf("[HELP] _> Ask the Wizard for help on how to the item!\n\n");
				white;
				Small_stop;
				
			} else if(last_item_code_used == 11 + INT_current_location){
				
				FILE * funlockedbook = fopen("HasBookUnlocked.txt", "w");
				fclose(funlockedbook);
				
				yellow;
				printf("Congrats, you fixed the book!\n");
				white;
				Small_stop;
				
				Mountain("book");
				
			} else
			Mountain("book");
			
		} else if(strcmp(Movement_Made, "?")== 0 && is_in_story_loc){	//Read story paper depending on WHAT we want
			
			//Get 
			char WANTEDFILENAME [15] = { '\0' }, temp [2] = { '\0' };
			int special_loc_INT = 0;
			FILE * fstorylocinfo = fopen("IsInStoryLoc.txt", "r");
			fscanf(fstorylocinfo, "%d", &special_loc_INT);
			fclose(fstorylocinfo);
			
			itoa(special_loc_INT, temp, 10);
			
			strcpy(WANTEDFILENAME, "Mount.");
			strcat(WANTEDFILENAME, temp);
			strcat(WANTEDFILENAME, ".txt");
			
			remove("IsInStoryLoc.txt");
			
			GetAppResources("Notes");
			ReadTextFile(WANTEDFILENAME, "none.");
		
		} else if(strcmp(Movement_Made, "explore")== 0 && is_in_special_loc){	//Special loc action
			
			SpecialLocations(current_location);
			
		} else if(strcmp(Movement_Made, "enter")== 0 && is_in_key){	//Key action
			
			Key(current_location);
			
		} else if(strcmp(Movement_Made, "up")== 0 && is_in_ladder){	//Moving UP the mountain to a new place
															
			INT_current_location --;
			strcpy(current_location, All_Locations[INT_current_location]);
			Mountain("dispnewarea");
			
		} else if(strcmp(Movement_Made, "down")== 0 && is_in_pit){	//Moving DOWN the mountain to a new place
			
			INT_current_location ++;
			strcpy(current_location, All_Locations[INT_current_location]);
			Mountain("dispnewarea");
			
		} else if(strcmp(Movement_Made, "bridge")== 0 && is_in_bridge){	//Moving bettewn Geysers and Blossom
			
			if(strcmp(current_location, "Geysers")== 0)
			INT_current_location ++;
			
			else
			INT_current_location --;
			
			strcpy(current_location, All_Locations[INT_current_location]);
			Mountain("dispnewarea");
			
		} else if(strcmp(Movement_Made, "item")== 0){
			
			//Get Last Item Code and decrypt it (used for Compass)
			CLR;
			last_item_code_used = GitItem();
			
			if(last_item_code_used > 50)
			Mountain("newcompassloc");
			
		} else if(strcmp(Movement_Made, "collect")== 0 && is_in_minigame){
			
			INT_minigame_type = 2;
			
			int lines_wanted = 0, current_minigame_limit = 0, temp_INT = 0;
			char temp [10] = { '\0' };
			
			//Tree type
			if(INT_minigame_type == 30)
			lines_wanted = 3;
			
			else if(INT_minigame_type == 31)
			lines_wanted = 4;
			
			else
			lines_wanted = INT_minigame_type;
			
			GetAppResources("Usefull Files.Mountain");
			//Getting possible limits here
			for(int i = 0; i < INT_current_location + 1; i ++){
				char temp_FileName [15] = { '\0' };
				strcpy(temp_FileName, All_Locations[i]);
				strcat(temp_FileName, ".txt");
				
				FILE * fgetminigamelimit = fopen(temp_FileName, "r");
			
				for(int j = 0; j < lines_wanted; j ++)
				fgets(temp, 10, fgetminigamelimit);
				
				fscanf(fgetminigamelimit, "%d\n", &temp_INT);
				current_minigame_limit += temp_INT;
				fclose(fgetminigamelimit);	
			}
			
			//This is to get function arguments and stuff
			current_minigame_limit -= temp_INT;
			int what_pos_do_we_want = rand()% temp_INT + 1;
			
			if(INT_minigame_type == 30)
			INT_minigame_type = 3;
			
			else if(INT_minigame_type == 31)
			INT_minigame_type = 4;
			
			switch(INT_minigame_type){
				case 0:
					Crop((current_minigame_limit * 5) + (what_pos_do_we_want * 5) + 1, false);
					break;
					
				case 1:
					Animal(false);
					break;
					
				case 2: {
					char temp_chr[2] = { '\0' };
					itoa(what_pos_do_we_want + current_minigame_limit, temp_chr, 10);
					Fish((current_minigame_limit * 7) + (what_pos_do_we_want * 7) + 40, temp_chr, false);	
					break;
				}
					
				case 3 ... 4: {
					bool is_invasive_lol = false;
					int special_ID = 0, adding_to_ID = 0; 
					
					//Getting "is_invasive" value (function arg)
					if(INT_minigame_type == 4)
					is_invasive_lol = true;
					
					//Get 1st Item ID :> & special ID (both depend on location to calculate) (&& set new what_pos_do_we_want)
					if(INT_current_location == 1){
						//Invasive FOREST
						if(is_invasive_lol){
							what_pos_do_we_want += what_pos_do_we_want;
							what_pos_do_we_want -= 1;
							
							adding_to_ID = what_pos_do_we_want / 2;	
						}
						
						//Non Invasive FOREST
						else {
							what_pos_do_we_want += what_pos_do_we_want;
							
							adding_to_ID = 2;
							adding_to_ID += what_pos_do_we_want / 2;
						}
						
						special_ID = 108;
						
					} else if(INT_current_location == 2){
						what_pos_do_we_want += 3;
						adding_to_ID = 6;
						special_ID = 110;
						
					} else if(INT_current_location == 4){
						what_pos_do_we_want += 3;
						
						if(is_invasive_lol)
						adding_to_ID = 8;
						
						else {
							what_pos_do_we_want += 1;
							adding_to_ID = 9;
						}
												
						special_ID = 113;
						
					} else {
						what_pos_do_we_want += 4;
						adding_to_ID = 11;
						special_ID = 115;
						
					}
					
					char temp_chr[2] = { '\0' };
					itoa(what_pos_do_we_want + current_minigame_limit, temp_chr, 10);
					Tree(is_invasive_lol, temp_chr, 103 + adding_to_ID, special_ID, false);
						
					break;
				}
					
				default:
					break;
					
			}
			
		} else {
			movement_fail = true;
			Error;	
		}
		
		return;
		
	} else if(strcmp(what, "newminigame")== 0){		//Generate a new minigame depending on location
	
		/*
		Inside minigamelimits.txt ig? (NOT REAL NAME)
		
		[Crop Limit]
		[Animal Limit]
		[Fish Limit]
		[Non Invasive Tree Limit]
		[Invasive Tree Limit]
		
		INT_minigame_type list
		0  -> Crop
		1  -> Animal
		2  -> Fish
		30 -> Normal Tree
		31 -> Invasive Tree
		*/
	
		int mini_game_limits [5] = { 0 }, mini_game_choosen = 0;
	
		//Get the mini game limit for each one lol
		GetAppResources("Usefull Files.Mountain");
		
		char temp [15] = { '\0' };
		strcpy(temp, current_location);
		strcat(temp, ".txt");
		
		FILE * fgetminigamelimit = fopen(temp, "r");
		
		for(int i = 0; i < 5; i ++)
		fscanf(fgetminigamelimit, "%d\n", &mini_game_limits[i]);
		
		fclose(fgetminigamelimit);
		
		ChangeCurPath("STORY.Locations");
		CatCurPath(current_location);
		while(true){
			mini_game_choosen = rand()% 4 + 1;
			mini_game_choosen --;
			
			//Check if we are using compass or not
			if(is_following_minigame){
				FILE * fforcethisminigamepls = fopen("CompassMinigame.txt", "r");
				fscanf(fforcethisminigamepls, "%d\n", &mini_game_choosen);
				fclose(fforcethisminigamepls);
			}
			
			//Sucess
			if(mini_game_choosen != 3 && mini_game_limits[mini_game_choosen] > 0)
			break;
				
			//Tree Sucess
			else if(mini_game_choosen == 3 && (mini_game_limits[3] > 0 || mini_game_limits[4] > 0))
			break;
			
		}
		
		//Forest types
		if(mini_game_choosen == 3){
			mini_game_choosen *= 10;
			
			//Randomize rates lul
			if(mini_game_limits[3] > 0 && mini_game_limits[4] > 0){
				int total_trees = mini_game_limits[3] + mini_game_limits[4];
				
				int pos_choosen = rand()% total_trees + 1;
				
				//Is Invasive!
				if(pos_choosen > mini_game_limits[3])
				mini_game_choosen ++;
			}
			
			//Checking for non invasive
			if(mini_game_limits[3] == 0)
			mini_game_choosen ++;
			
			//Non Invasive = 30
			//Invasive = 31
		}
		
		//Remove the constant
		if(is_following_minigame && access("CompassMinigame.txt", F_OK)== 0)
		remove("CompassMinigame.txt");
		
		INT_minigame_type = mini_game_choosen;
		return;
	
	} else if(strcmp(what, "dispnewarea")== 0){		//Display new area traveled to
		
		int needed_lines = GetTerminalSize("rows") / 2;
		int needed_cols = (GetTerminalSize("columns") - (strlen(current_location) + 17)) / 2; 
		
		for(int i = 0; i < needed_lines; i ++)
		printf("\n");
		
		char temp_char = '\0';
		
		//This is to display NEW area if its inside mountain
		if(strcmp(current_location, "NOT")!= 0){
			yellow;
			printf("%*cNow Entering %s", needed_cols, temp_char, current_location);
			white;
			
			for(int i = 0; i < needed_lines - 1; i ++)
			printf("\n");
			
			sleep(3);	
		}
		
		CLR;
		
		//Update current location
		ChangeCurPath("STORY.Locations");
		FILE * fupdatecurloc = fopen("Current.txt", "w");
		fprintf(fupdatecurloc, "%s", current_location);
		fclose(fupdatecurloc);
		
		if(strcmp(current_location, "Entry")== 0)
		Pit();
		
		//weird case were location we are traveling to dosent have needed files yet
		if(access(current_location, F_OK)!= 0)
		Mountain("new");
		
		Mountain("move");
		return;
		
	} else if(strcmp(what, "book")== 0){		//use the teleport book to teleport to next location
	
		CLR;
	
		//BTW this was a full on function but i decided to get rid of the function instead lol so now theres this
		char Unknown_Locations [7] [8], Cur_Location [8], Next_Location[8], TRY_LOCATION [15];
		short int Current_Error = -1;
		
		//Change to the story dir
		ChangeCurPath("STORY.Locations");
		
		//Git Unknown locations
		for(int i = 0; i < 7; i ++){
			bool is_unknown = false;
			
			if(access(All_Locations[i], F_OK)== 0){
				ChangeCurPath("STORY.Locations");
				CatCurPath(All_Locations[i]);
			
				if(access("HasBookUnlocked.txt", F_OK)!= 0)
				is_unknown = true;
				
				chdir("..");	
				
			} else
			is_unknown = true;
			
			if(is_unknown)
			strcpy(Unknown_Locations[i], All_Locations[i]);
		}
		
		FILE * fcurrent = fopen("Current.txt", "r");
		fscanf(fcurrent, "%s", Cur_Location);
		fclose(fcurrent);
		
		//Setting up stuff for proper formating
		char quick_formating = '\0';
		
		int cols_needed = (GetTerminalSize("columns") - 45) / 2;
		if(cols_needed % 2 == 0)
		quick_formating = ' ';
		
		int lines_needed = (GetTerminalSize("rows") - 20) / 2;
		
		//KNOWN = !UNKNOWN 
		
		for(int z = 0; z < 2; z ++){
			for(int i = 0; i < lines_needed; i ++)
			printf("\n");
			
			//1st part of le book
			Art("TPBOOK", 1);
			
			//2nd part of le book depending on progression
			for(int i = 0; i < 7; i++){
				
				//Check for non activated books
				bool is_cur_loc_valid = true;
				for(int j = 0; j < 7; j ++){
					if(strcmp(All_Locations[i], Unknown_Locations[j])== 0){
						is_cur_loc_valid = false;
						break;
					}
				}
				
				//Current Area gets replaced by "YOU ARE HERE"
				if(strcmp(Cur_Location, All_Locations[i])== 0){
				printf("%*c0    You Are Here   4   4 ", cols_needed, quick_formating);
				
				//Show "NOT FOUND" has non activated books	
				} else if(!is_cur_loc_valid){
					printf("%*c0    Not Found      4   4 ", cols_needed, quick_formating);
					
				//Print normaly in book	
				} else {
					printf("%*c0    %s", cols_needed, quick_formating, All_Locations[i]);
                    int spaces_needed = strlen(All_Locations[i]) - 15;
                    spaces_needed = abs(spaces_needed);
					for(int j = 0; j < spaces_needed; j ++)
					printf(" ");
					
					printf("4   4 ");
				}
				
				//Switch case for the message on the side [The whole boise warning thing]
				switch(i){
					case 0:
						printf(" Boise is not     0\n");
						break;
					
					case 1:
						printf(" responsible for  0\n");
						break;
						
					case 2:
						printf(" any damage       0\n");
						break;
						
					case 3:
						printf(" caused by using  0\n");
						break;
						
					case 4:
						printf(" the book         0\n");
						break;
						
					case 5:
						printf(" teleport system  0\n");
						break;
						
					case 6:
						printf("                  0\n");
						break;
						
					default:
						break;
						
				}
				
			} //Loop end
			
			//last part of le book
			printf("%*c0                   4   4                   0\n", cols_needed, quick_formating);
			
			if(z == 0){
				Art("TPBOOK", 2);
				
				for(int i = 0; i < lines_needed - 2; i ++)
				printf("\n");
				
				printf("Where to? [Max 13 chars]\n");
				printf("&/");
				scanf("%s", TRY_LOCATION);
				
				//Lower case input for comparing
				for (int i = 0; TRY_LOCATION[i]; i++) 
			    TRY_LOCATION[i] = tolower(TRY_LOCATION[i]);
			
				CLR;
				
				//If its over 13 the book would deformat the book thing
				if(strlen(TRY_LOCATION) <= 13){
					
					//Format for next check
					TRY_LOCATION[0] = toupper(TRY_LOCATION[0]);
					
					//Check if location is valid
					bool is_valid_loc = false;
					for(int j = 0; j < 7; j ++){
						if(strcmp(TRY_LOCATION, All_Locations[j])== 0){
							is_valid_loc = true;
							break;
						}
					}
					
					//Check if location is known
					bool is_known_loc = true;
					for(int j = 0; j < 7; j ++){
						if(strcmp(TRY_LOCATION, Unknown_Locations[j])== 0){
							is_known_loc = false;
							break;
						}
					}
					
					if(!is_known_loc)
					Current_Error = 1; 	//Unknown
					
					//Do other checks if it IS valid
					if(is_valid_loc && is_known_loc){
						if(strcmp(TRY_LOCATION, Cur_Location)!= 0){
							strcpy(Next_Location, TRY_LOCATION);
							Current_Error = 0;	//No Error
						} else {
							Current_Error = 2;	//Same
						}
					} else {
						Current_Error = 3;	//Invalid
					}
					
					
				} else { CLR; red; printf("Too many chareters :(\n"); CLR; white; strcpy(Next_Location, "SAME"); } 
				
			} else {
				
				if(Current_Error == 3){			//Invalid location Error
					
					printf("%*c0  Teleporting to?  4   4  Error:           0\n", cols_needed, quick_formating);
					
					printf("%*c0  ? _>%s", cols_needed, quick_formating, TRY_LOCATION);
                    int spaces_needed = strlen(TRY_LOCATION) - 13;
                    spaces_needed = abs(spaces_needed);
					for(int j = 0; j < spaces_needed; j ++)
					printf(" "); 
					
					printf("4   4  Invalid Location 0\n");
					
					strcpy(Next_Location, "SAME");
				
				} else if(Current_Error == 0){	//No Error
				
					printf("%*c0  Teleporting to?  4   4  Teleporting to:  0\n", cols_needed, quick_formating);
					printf("%*c0  ? _>%s", cols_needed, quick_formating, TRY_LOCATION);
                    int spaces_needed = strlen(TRY_LOCATION) - 13;
                    spaces_needed = abs(spaces_needed);
                    for(int j = 0; j < spaces_needed; j ++)
					printf(" ");
					printf("4   4  %s",Next_Location);
                    spaces_needed = strlen(TRY_LOCATION) - 17;
                    spaces_needed = abs(spaces_needed);
                    for(int j = 0; j < spaces_needed; j ++)
                    printf(" ");
					
					printf("0\n");
				
				} else if(Current_Error == 1){	//Unknown location Error
					
					printf("%*c0  Teleporting to?  4   4  Error:           0\n", cols_needed, quick_formating);
					
					printf("%*c0  ? _>%s", cols_needed, quick_formating, TRY_LOCATION);
                    int spaces_needed = strlen(TRY_LOCATION) - 13;
                    spaces_needed = abs(spaces_needed);
                    for(int j = 0; j < spaces_needed; j ++)
					printf(" "); 
					
					printf("4   4  Unknown Location 0\n");
					
					strcpy(Next_Location, "SAME");
					
				} else {						//Same location Error
					
					printf("%*c0  Teleporting to?  4   4  Error:           0\n", cols_needed, quick_formating);
					
					printf("%*c0  ? _>%s", cols_needed, quick_formating, TRY_LOCATION);
                    int spaces_needed = strlen(TRY_LOCATION) - 13;
                    spaces_needed = abs(spaces_needed);
                    for(int j = 0; j < spaces_needed; j ++)
					printf(" "); 
					
					printf("4   4  Same Location    0\n");
					
					strcpy(Next_Location, "SAME");
				} 
				
				Art("TPBOOK", 3);
			}
	
		}	//END OF MAIN LOOP
		
		for(int i = 0; i < lines_needed - 1; i ++)
		printf("\n");
		
		Small_stop;
		
		//Register new location if no error occured
		if(strcmp(Next_Location, "SAME")!= 0){
			FILE * fcurrent = fopen("Current.txt", "w");
			fprintf(fcurrent, "%s", Next_Location);
			fclose(fcurrent);
		}
		
		Mountain("dispnewarea");
		return;
	
	} else {
		red; printf("Invalid argument on function \"Mountain\" (bozo)\n"); Small_stop; white;
	}
	
}

//Use items and stuff
int GitItem(void){
	int ITEM_CODE = -1;
	
	while(true){
		ITEM_CODE = -1;
		CLR;
		printf("What do you want to do?\n");
		printf(">Use a utility item [Item]\n");
		printf(">Drink a potion [Potion]\n");
		
		ChangeCurPath("OTHER.books");
		if(access("Key3Book.txt", F_OK)== 0)
		printf(">Check Hint Book [Book]\n"); 
		
		else if(access("CurPage.txt", F_OK)== 0)
		printf(">Register in the Book [Book]\n");
		
		printf(">Nevermind [Back]\n");
		String_Input;
		
		if(strcmp(Input, "item")== 0){ 
			
			/*
			Notes for Item Code:
			
			50 + (1 - 6) - Universal Compass with pointing to Location
			
			If its 1 to 26 its normal
			*/
			
			bool catched_error = false, user_left = false;
			while(true){
				
				//Call the display function and handle the return value
				catched_error = false, user_left = false;
				int cur_line = DisplayAllSpecialItems();
				
				if(cur_line == 0){
					Error;
					catched_error = true;
					ITEM_CODE = 0;
					
				} else if(cur_line == -1){
					user_left = true;
					break;
					
				} else {
					bool is_view_only = false, is_craft_only = false, is_configure_only = false, is_use_only = false, is_discard_only = false;
					
					//Set atributes
					switch(cur_line){
						case 1:
							is_view_only = true;
							break;
							
						case 2:
							is_use_only = true;
							break;
							
						case 3:
							is_view_only = true;
							break;
							
						case 4:
							is_configure_only = true;
							break;
							
						case 5:
							is_view_only = true;
							break;
							
						case 6:
							is_view_only = true;
							break;
							
						case 7:
							is_view_only = true;
							break;
							
						case 8:
							is_view_only = true;
							break;
							
						case 9:
							is_view_only = true;
							break;
							
						case 10:
							is_view_only = true;
							break;
							
						case 11:
							is_craft_only = true;
							break;
							
						case 12:
							is_discard_only = true;
							break;
							
						case 13:
							is_discard_only = true;
							break;
							
						case 14:
							is_discard_only = true;
							break;
							
						case 15:
							is_discard_only = true;
							break;
							
						case 16:
							is_discard_only = true;
							break;
							
						case 17:
							is_discard_only = true;
							break;
							
						case 18:
							is_craft_only = true;
							break;
							
						case 19:
							is_view_only = true;
							break;
							
						case 20:
							is_craft_only = true;
							break;
							
						case 21:
							is_use_only = true;
							break;
							
						case 22:
							is_configure_only = true;
							break;
							
						case 23:
							is_configure_only = true;
							break;
							
						case 24:
							is_view_only = true;
							break;
							
						case 25:
							is_use_only = true;
							break;
							
						case 26:
							is_use_only = true;
							break;
					}
					
					//Show the item and give him the options
					while(true){
						ITEM_CODE = 0;
						Art("SITEM", cur_line);
						
						//Catch name of the item selected
						char * catch_full_itm_name = (char *)malloc(50);
						memset(catch_full_itm_name, '\0', sizeof(catch_full_itm_name));
						
						catch_full_itm_name = GetItemName(200 + cur_line);
						
						ChangeCurPath("OTHER.temp");
						FILE * fsetformatvars = fopen("FormatingVarTemp.txt", "w");
						
						//SET DELIMS
						if(is_view_only)
						fprintf(fsetformatvars, "6\n");
						
						else if(is_craft_only)
						fprintf(fsetformatvars, "12\n");
						
						else if(is_configure_only)
						fprintf(fsetformatvars, "11\n");
						
						else if(is_use_only)
						fprintf(fsetformatvars, "5\n");
						
						else if(is_discard_only)
						fprintf(fsetformatvars, "9\n");
						
						fprintf(fsetformatvars, "%s\n", catch_full_itm_name);
						fclose(fsetformatvars);
						free(catch_full_itm_name);
						
						//Format needed texts
						if(is_view_only)
						FormatTextEXT("center", "<View ?>", true, 0, ".", true, 0, 0);
						
						else if(is_craft_only)
						FormatTextEXT("center", "<Craft With ?>", true, 0, ".", true, 0, 0);
							
						else if(is_configure_only)
						FormatTextEXT("center", "<Configure ?>", true, 0, ".", true, 0, 0);
							
						else if(is_use_only)
						FormatTextEXT("center", "<Use ?>", true, 0, ".", true, 0, 0);
							
						else if(is_discard_only)
						FormatTextEXT("center", "<Discard ?>", true, 0, ".", true, 0, 0);	
						
						//Get Input (Yes or No)
						CenterText("(Y/N)");
						FormatTextEXT("center", "&/", false, 0, ".", false, 0, 0);
						scanf("%s", Input);
						for(int i = 0; i < strlen(Input); i ++)
						Input[i] = tolower(Input[i]);
						CLR;
						
						if(strcmp(Input, "y")== 0){
							
							//Every item is diferent so...
							switch(cur_line){
								case 1:
									GetAppResources("Notes");
									ReadTextFile("SecretBook.txt", ".");
									break;
									
								case 2: {
									char cur_loc [50] = { '\0' };
									
									ChangeCurPath("STORY.Locations");
									FILE * fgetcurrentpos = fopen("Current.txt", "r");
									fscanf(fgetcurrentpos, "%s\n", cur_loc);
									fclose(fgetcurrentpos);
									
									if(strcmp(cur_loc, "NONE")== 0 || strcmp(cur_loc, "Entry")== 0){
										red; CenterText("You can only use this item in the Mountain."); white;
										ITEM_CODE = -2; 
										break;
									}
									
									int cur_hour = TimeCalc("CHECK", 0, 1, 0);
									if(cur_hour < 18 && cur_hour > 10){
										red; CenterText("You can only use this item when the hour is bettewn 18 (6pm) and 10 (10am)"); white;
										ITEM_CODE = -2;
										break;
									}	
									
									yellow; CenterText("Used Portable Bed!"); white;	
									break;
								}
									
								case 3:
									GetAppResources("Notes");
									ReadTextFile("WizardsNote.txt", ".");
									break;
									
								case 4: {
									int catch_id_returned = 0;
									while(true){
										light_aqua; CenterText("Please select an item to configure the Universal Compass with..."); white;
										catch_id_returned = DisplayAllSpecialItems();
										if(catch_id_returned == 0){
											Error;	
											
										} else
										break;
									}
									
									ChangeCurPath("INVENTORY");
									if((catch_id_returned < 5 || catch_id_returned > 9) && catch_id_returned != 24){
										red; CenterText("It seems the compass cannot hold that item..."); white;
										ChangeFileLine("SpecialStats.txt", "NONE", 0);
										ITEM_CODE = -2;
										break;
									}
									
									//Change Compass pointing to and tell user
									switch(catch_id_returned){
										case 5:
											green; CenterText("The compass is now pointing to the signs"); white;
											ChangeFileLine("SpecialStats.txt", "SIGNS", 0);
											ITEM_CODE = 51;
											break;
											
										case 6:
											green; CenterText("The compass is now pointing to the nearest CROP matherial zone"); white;
											ChangeFileLine("SpecialStats.txt", "CROP", 0);
											ITEM_CODE = 52;
											break;
											
										case 7:
											green; CenterText("The compass is now pointing to the nearest ANIMAL matherial zone"); white;
											ChangeFileLine("SpecialStats.txt", "ANIMAL", 0);
											ITEM_CODE = 53;
											break;
											
										case 8:
											green; CenterText("The compass is now pointing to the nearest FISH matherial zone"); white;
											ChangeFileLine("SpecialStats.txt", "FISH", 0);
											ITEM_CODE = 54;
											break;
											
										case 9:
											green; CenterText("The compass is now pointing to the nearest TREE matherial zone"); white;
											ChangeFileLine("SpecialStats.txt", "TREE", 0);
											ITEM_CODE = 55;
											break;
											
										case 24:
											green; CenterText("The compass is now pointing to the nearest STAR zone"); white;
											ChangeFileLine("SpecialStats.txt", "STAR", 0);
											ITEM_CODE = 56;
											break;
									}
									
									break;
								}
									
								case 5:
									light_blue; CenterText("A small rock with the word 'S' carved onto it"); white;
									break;
									
								case 6:
									light_blue; CenterText("A weird looking grass that seems to be pointing north at all times"); white;
									break;
									
								case 7:
									light_blue; CenterText("A bug stuck inside a bottle, there are small holes so it can "); white;
									break;
									
								case 8:
									light_blue; CenterText("A small rock with the word 'S' carved onto it"); white;
									break;
									
								case 9:
									light_blue; CenterText("A small rock with the word 'S' carved onto it"); white;
									break;
									
								case 10:
									CenterText("FISHING PERMIT");
									CenterText("THE OWNER OF THS PERMIT CAN PLACE 1 MORE TRAP THAN THE LIMIT ALLOWS");
									CenterText("DISTRIBUTED BY FISHERMAN IN TRADE OF A GOLDEN FISH");
									break;
									
								case 11: {
									if(Inventory("CHECK", 218, 1)){
										red; CenterText("You already fixed the clock!"); white;	
										ITEM_CODE = -2;
										break;
									}
									
									int catch_id_returned = 0;
									while(true){
										light_aqua; CenterText("Please select an item to combine the Shattered Clock with..."); white;
										catch_id_returned = DisplayAllSpecialItems();
										if(catch_id_returned == 0){
											Error;	
											
										} else
										break;
									}
									
									if(catch_id_returned != 18){
										red; CenterText("You cant combine this item with the Shattered Clock!"); white;
										ITEM_CODE = -2;
										break;
										
									} else {
										ChangeCurPath("INVENTORY");
										light_green; CenterText("Got a Working Clock!"); white;
										ChangeFileLine("Specials.txt", "1", 18);
										
									}
								
									break;
								}
									
								case 12:
									CenterText("You Dicarded the Small Wooden Bird Statue...");
									break;
									
								case 13:
									CenterText("You Dicarded the Broken River Shell...");
									break;
									
								case 14:
									CenterText("You Dicarded the Variating Magnifying Glass...");
									break;
									
								case 15:
									CenterText("You Dicarded the Glowing Red Gemstone...");
									break;
									
								case 16:
									CenterText("You Dicarded the Nice Smelling Black Rose...");
									break;
									
								case 17:
									CenterText("You Dicarded the Forgotten Snow Spear...");
									break;
									
								case 18: {
									if(Inventory("CHECK", 218, 1)){
										red; CenterText("You already fixed the clock!"); white;
										ITEM_CODE = -2;
										break;
									}
									
									int catch_id_returned = 0;
									while(true){
										light_aqua; CenterText("Please select an item to combine the Rusty Gear with..."); white;
										catch_id_returned = DisplayAllSpecialItems();
										if(catch_id_returned == 0){
											Error;	
											
										} else
										break;
									}
									
									if(catch_id_returned != 11){
										red; CenterText("You cant combine this item with the Rusty Gear!"); white;
										ITEM_CODE = -2;
										break;
										
									} else {
										ChangeCurPath("INVENTORY");
										light_green; CenterText("Got a Working Clock!"); white;
										ChangeFileLine("Specials.txt", "1", 18);
										
									}
									break;
								}
									
								case 19:
									printf("Current time\n\n");
									printf("Timer ->%d\n", TimeCalc("CHECK", 1, 0, 0));
									printf("Hour ->%d\n", TimeCalc("CHECK", 0, 1, 0));
									printf("Day ->%d\n", TimeCalc("CHECK", 0, 0, 1));
									break;
									
								case 20: {
									if(Inventory("CHECK", 222, 1)){
										red; CenterText("You already fixed the Strange Wave Transmiter!"); white;
										ITEM_CODE = -2;
										break;
									}
									
									int catch_id_returned = 0;
									while(true){
										light_aqua; CenterText("Please select an item to combine the Weird Mechanism with..."); white;
										catch_id_returned = DisplayAllSpecialItems();
										if(catch_id_returned == 0){
											Error;	
											
										} else
										break;
									}
									
									if(catch_id_returned != 22){
										red; CenterText("You cant combine this item with the Weird Mechanism!"); white;
										ITEM_CODE = -2;
										break;
										
									} else {
										ChangeCurPath("INVENTORY");
										light_green; CenterText("Got a Strange Wave Transmiter!"); white;
										ChangeFileLine("Specials.txt", "1", 22);
										
									}
									break;
								}
									
								case 21:
									light_yellow; CenterText("[HELP] _> The Special Book has its own section!"); white;	
									break;
									
								case 22: {
									char * signal_generated = (char *)malloc(10);
									memset(signal_generated, '\0', sizeof(signal_generated));
									
									light_yellow; CenterText("Generating new Signal to expand..."); white;	
									sleep(2);
									
									if(rand()% 10 + 1 == 1)
									strcpy(signal_generated, "E9AR5");
									
									signal_generated = EncryptedWordsV2("AAAAA");
									
									ChangeCurPath("OTHER.temp");
									FILE * fsetformatvars = fopen("FormatingVarTemp.txt", "w");
									fprintf(fsetformatvars, "23\n");
									fprintf(fsetformatvars, "%s\n", signal_generated);
									fclose(fsetformatvars);
																		
									light_aqua; FormatTextEXT("center", "New signal generated - ", true, 0, ".", true, 0, 0); white;
									
									ChangeCurPath("INVENTORY");
									ChangeFileLine("SpecialStats.txt", signal_generated, 1);
									free(signal_generated);
									
									break;
								}
									
								case 23:
									while(true){
										light_yellow; CenterText("Please type a new Signal to switch to... (5 chars ONLY)"); white;
										FormatTextEXT("center", "&/", false, 0, ".", false, 0, 0);
										scanf("%s", Input);
										CLR;
										
										if(strlen(Input) != 5){
											red;
											CenterText("This signal is not 5 charecters long.");
											CenterText("ERR: (SIGNAL_SIZE_UNDEF)");
											white;
											Small_stop;
											
										} else {
											ChangeCurPath("OTHER.temp");
											FILE * fsetformatvars = fopen("FormatingVarTemp.txt", "w");
											fprintf(fsetformatvars, "20\n");
											fprintf(fsetformatvars, "%s\n", Input);
											fclose(fsetformatvars);
											
											light_aqua; FormatTextEXT("center", "Changed to Signal - ", true, 0, ".", true, 0, 0); white;
											
											ChangeCurPath("INVENTORY");
											ChangeFileLine("SpecialStats.txt", Input, 1);
											
											break;
										}	
									}
									
									break;
									
								case 24:
									light_blue; CenterText("A glowing rock that fell from space"); white;
									break;
									
								case 25:
									yellow; CenterText("Used Pocket Telescope!"); white;
									break;
									
								case 26:	
									ChangeCurPath("INVENTORY");
									int cur_pol = 0;
									char templine [10] = { '\0' };
									
									FILE * fgetspecialstats = fopen("SpecialStats.txt", "r");
									fgets(templine, 10, fgetspecialstats);
									memset(templine, '\0', sizeof(templine));
									fgets(templine, 10, fgetspecialstats);
									memset(templine, '\0', sizeof(templine));
									fscanf(fgetspecialstats, "%d\n", &cur_pol);
									fclose(fgetspecialstats);
									
									if(cur_pol == 1){
										light_blue; CenterText("Changed to NEGATIVE polarity and amplied to this zone."); white;
										cur_pol = 0;
										
									} else {
										light_blue; CenterText("Changed to POSITIVE polarity and amplied to this zone."); white;
										cur_pol = 1;
										 	
									}
									
									itoa(cur_pol, templine, 10);
									ChangeFileLine("SpecialStats.txt", templine, 2);
									
									break;
							}
							
							if(ITEM_CODE / 50 != 1 && ITEM_CODE != -2)
							ITEM_CODE = cur_line;
							
							Small_stop;
							break;
							
						} else if(strcmp(Input, "n")== 0){
							ITEM_CODE = 0;
							break;
							
						} else {
							Error;
						}
					}
				}
				
				if(ITEM_CODE != 0 && ITEM_CODE != -2)
				break;
			}
			
			if(!catched_error && !user_left)
			return ITEM_CODE;
			
		} else if(strcmp(Input, "potion")== 0){
			char * short_pot_name;
			
			char all_potion_names [10] [22] = {
			"Refresher", "Mint Tea", "Woods Water", 
			"Hidden Bush", "Time Decline", "Happy Acident",
			"Early Grave", "Lots of Fish Bones", 
			"High Risk, Low Reward", "Im Special"};
			
			while(true){
				bool error = false;
				printf("What potion do you want to use?\n");
				//Get the potions the user has
				for(int i = 0; i < 10; i ++){
					all_potion_names[i][0] = toupper(all_potion_names[i][0]);
					
					//Display all potions that user has
					if(Inventory("CHECK", 116 + i, -1)== 1){
						if(i == 0)
						strcpy(short_pot_name, all_potion_names[i]);
						
						else {
							char delim [2] = " ";
							char temp_str [22] = { '\0' };
							strcpy(temp_str, all_potion_names[i]);
							short_pot_name = strtok(temp_str, delim);
						}
						
						printf(">%s [%s]\n", all_potion_names[i], short_pot_name);
						memset(short_pot_name, '\0', sizeof(short_pot_name));
					}
				}
				printf(">Back\n");
				String_Input;
				
				if(strcmp(Input, "back")== 0)
				break;
				
				//Check if input is correct and get index (for array)	
				int index = -1;
				for(int i = 0; i < 10; i ++){
					all_potion_names[i][0] = tolower(all_potion_names[i][0]);
					if(Input[0] == all_potion_names[i][0] && Input[1] == all_potion_names[i][1]){
						//Special case (duped)
						if(Input[0] == 'h' && Input[1] == 'i'){
							if(Input[2] == 'd')
							index = 3;
							
							else
							index = 8;
							
						} else
						index = i;
					}	
				}
				
				if(index == -1){
					Error;
					error = true;
				}
				
				//Make a new file on "activepots" for the effects to activate
				if(Inventory("CHECK", 116 + index, -1) == 1 && !error){
					all_potion_names[index][0] = toupper(all_potion_names[index][0]);
					
					//Git file name
					char FileName [5] = { '\0' };
					itoa(index, FileName, 10);
					strcat(FileName, ".txt");
					
					int numb_hours_active = rand()% 7 + 1;
					numb_hours_active += 3;
					
					//Get day and hour to register them in a file ltr
					short int cur_hour = TimeCalc("CHECK", 0, 1, 0);
					long int cur_day = TimeCalc("CHECK", 0, 0, 1);
					cur_hour += numb_hours_active;
					
					if(cur_hour >= 24){
						cur_hour -= 24;
						cur_day ++;
					}
					
					ChangeCurPath("OTHER.activepots");	
					FILE * factivepot = fopen(FileName, "w");
					fprintf(factivepot, "%d\n", cur_hour);
					fprintf(factivepot, "%d\n", cur_day);
					fprintf(factivepot, "%s\n", all_potion_names[index]);
					fclose(factivepot);
					
					//Take out 1 potion
					Inventory("CALC", 116 + index, -1);
					
					all_potion_names[index][0] = toupper(all_potion_names[index][0]);
					printf("Drank \"%s\"!\n", all_potion_names[index]);
					sleep(3);
					break;
						
				} else if(!error){
					Error;
				}
			}
			
		} else if(strcmp(Input, "book")== 0){
			ChangeCurPath("OTHER.books");
			
			//None of the books are found? paink.
			if(access("Key3Book.txt", F_OK)!= 0 && access("CurPage.txt", F_OK)!= 0){
				Error;
			
			} else {
				//Hint book
				if(access("Key3Book.txt", F_OK)== 0){
					char * line = (char *)malloc(555);
					
					//Read the book normaly
					FILE * fkey3b = fopen("Key3Book.txt", "r");
					while(fgets(line, 555, fkey3b) != NULL){
						line[strlen(line) - 1] = '\0';
						printf("%s\n", line);
					}
					fclose(fkey3b);
					
					free(line);
					
					Small_stop;
				
				} else {
					/*
					Users Book:
					
					I hate this book
					I hate this book
					I hate this book
					I hate this book
					I hate this book
					
					(1 week on a project that was supost to be small .-.)
					
					howdafuckdoimakethe50lineperpagelimit
					*/
					
					int cur_line = 0, Line_Lim = 0, line_affected = 0;
					short int changed_lines = 0, temp_curline = 0;	//temp_curline is to make the /L/ copy less anoying
					char * FileName = (char *)malloc(10);
					char * wanted_declarations = (char *)malloc(100);
					
					//Get current file name page
					FILE * fcurpage = fopen("CurPage.txt", "r");
					fscanf(fcurpage, "%s", FileName);
					fclose(fcurpage);
					
					//Get current line number :>
					FILE * fgetline = fopen(FileName, "r");
					fscanf(fgetline, "%d\n", &Line_Lim);
					fscanf(fgetline, "%s\n", wanted_declarations);
					fclose(fgetline);
					
					cur_line = Line_Lim;
					
					char * THISLINE = (char *)malloc(1000);
					
					while(true){
						//Display file
						ReadTextFile("UsersBook.dir", wanted_declarations);
						
						changed_lines = 0; line_affected = 0;			//Sorry about the confusing name bellow (used on /L/ copy)
						bool exit_editing = false, hit_something = false, reverse_cur_line = false;
						memset(THISLINE, '\0', sizeof(THISLINE));
						
						white;
						printf("\n\nEdit current line: (Type /H/ for help)\n");
						if(cur_line > 50){
							printf("Woops! The line limit per page is 50!\n");
							cur_line = 50;	
						}
						
						printf("L%d: ", cur_line);
						
						//Stdin acumulated some trash values and it would cause fgets to apear twice and checkpoint once, weird bug
						fflush(stdin);
						
						fgets(THISLINE, 1000, stdin);
						CLR;
						
						//Check every char for a possible command
						for(int i = 0; i < strlen(THISLINE); i ++){
							//Needs formating then
							if(THISLINE[i] == '/' && THISLINE[i + 2] == '/'){
								char wotchar = THISLINE[i + 1];
								changed_lines = 0; line_affected = 0;
								
								switch(wotchar){
									case 'H': {
										GetAppResources("switchbacktomain.Help Notes");
										ReadTextFile("Writing in the book.txt", "showformating.slowread10000");
										ChangeCurPath("OTHER.books");
										Small_stop;
										hit_something = true;
										break;
									}
										
									case 'E': {
										CLR;
										exit_editing = true;
										hit_something = true;
										break;
									}
									
									case 'C': {
										char temp_line [10];
										
										//Get Line to edit next
										int index = 0;
										while(isdigit(THISLINE[i + 4 + index])){
											if(THISLINE[index + i + 4] == ' ' || THISLINE[index + i + 4] == '\0')
											break;
											
											temp_line [index] = THISLINE[i + 4 + index];
											index ++;
										}
										
										if(THISLINE[0] == ' ' || THISLINE[0] == '\0'){
											CLR;
											red;
											printf("Missing main argument on change line command (ARGUMENT_MISSING)\n");
											white;
											Small_stop;
											hit_something = true;
											break;
										}
										
										if(atoi(temp_line) < 1 || atoi(temp_line) > Line_Lim){
											CLR;
											red;
											printf("Error on change line command argument (LINE_UNKNOWN)\n");
											white;
											Small_stop;
											hit_something = true;
											break;
										}
										
										cur_line = atoi(temp_line);
										hit_something = true;
										break;
									}
											
									case 'L': {
										//Warning: Mess bellow :>	//Array couldnt be turned into int using atoi so im doing this instead.
										char action [15] = { '\0' }, line_affected1 [3] = { '\0' }, line_affected2 [3] = { '\0' }, line_affected3 [3] = { '\0' };
										int index = 0;
										bool make_changes = true;
										
										//Get what user wants to do
										while(THISLINE[i + 4 + index] != ' '){
											if(THISLINE[index + i + 4] == ' ' || THISLINE[index + i + 4] == '\0')
											break;
											
											action[index] = tolower(THISLINE[index + i + 4]);
											index ++;
										}
										
										if(action[0] == ' ' || action[0] == '\0'){
											CLR;
											red;
											printf("Missing main argument on line related command (ARGUMENT_MISSING)\n");
											white;
											Small_stop;
											hit_something = true;
											break;
										}
										
										//Get 1st Line Affected
										index = 0;
										while(isdigit(THISLINE[i + 5 + index + strlen(action)])){
											line_affected1 [index] = THISLINE[i + 5 + index + strlen(action)];
											index ++;
										}
										
										if(atoi(line_affected1) < 1 || atoi(line_affected1) > Line_Lim){
											CLR;
											red;
											printf("Error on line command argument (LINE_UNKNOWN)\n");
											white;
											Small_stop;
											hit_something = true;
											break;
										}
										
										if(strcmp(action, "removesome")== 0 || strcmp(action, "edit")== 0 || strcmp(action, "copy")== 0){
											//Get 2nd Line Affected
											index = 0;
											while(isdigit(THISLINE[i + 6 + index + strlen(action) + strlen(line_affected1)])){
												line_affected2[index] = tolower(THISLINE[i + 6 + index + strlen(action) + strlen(line_affected1)]);
												index ++;
											}
											
											if(strlen(THISLINE) - 1 < atoi(line_affected3) || atoi(line_affected3) < 0){
												CLR;
												red;
												printf("Error on line argument related to line manipulation (INDEX_UNKNOWN)\n");
												white;
												Small_stop;
												hit_something = true;
												break;
											}
											
											//Get wanted string bellow
											int CUR_POS = -1, FINAL_POS = atoi(line_affected1);
											cur_line = FINAL_POS;
											
											FILE * fmodifypointerpos = fopen(FileName, "r");
											
											//Getting pointer in disired line
											while(CUR_POS != FINAL_POS){
												memset(THISLINE, '\0', sizeof(THISLINE));
												fgets(THISLINE, 1000, fmodifypointerpos);
												CUR_POS ++;
											}
											
											memset(THISLINE, '\0', sizeof(THISLINE));
											fgets(THISLINE, 1000, fmodifypointerpos);
											fflush(stdin);
											fflush(stdout);
											fclose(fmodifypointerpos);
											
											//"RemoveSome" action
											if(strcmp(action, "removesome")== 0){
												//Get 3rd Line Affected
												index = 0;
												while(isdigit(THISLINE[i + 7 + index + strlen(action) + strlen(line_affected1) + strlen(line_affected2)])){
													line_affected3[index] = tolower(THISLINE[i + 7 + index + strlen(action) + strlen(line_affected1) + strlen(line_affected2)]);
													index ++;
												}
												
												if(strlen(THISLINE) - 1 < atoi(line_affected3) || atoi(line_affected3) < 0){
													CLR;
													red;
													printf("Error on removesome line argument (INDEX_UNKNOWN)\n");
													white;
													Small_stop;
													hit_something = true;
													break;
												}
												
												int agr1 = atoi(line_affected2), agr2 = atoi(line_affected3);	//yes
												int selected_str = strlen(THISLINE), index = 0;		//INCLUDES '\n'
												int both_agr_displacement = abs(agr1 - agr2);	//Dont care if agr1 is starter or agr2 is starter
												bool didnt_reach_end_of_string_lol = true;
												
												while(didnt_reach_end_of_string_lol){
													//This one cares who is higher or lower
													if(agr1 < agr2){
														THISLINE[index + agr1] = THISLINE[index + agr1 + both_agr_displacement];
														
														if(index + agr1 >= selected_str)
														didnt_reach_end_of_string_lol = false;
													} else {
														THISLINE[index + agr2] = THISLINE[index + agr2 + both_agr_displacement];
														
														if(index + agr2 >= selected_str)
														didnt_reach_end_of_string_lol = false;	
													}
													
													index ++;	
												}
												
												changed_lines = -2;
												Line_Lim ++; 
												
											//"Edit" action
											} else if(strcmp(action, "edit")== 0){
												char get_edit_line [1000];
												
												//125 Bytes for this shit :despair:
												char LINE_AGR1 [1000] = { '\0' }, LINE_AGR2 [1000] = { '\0' }, LINE_ADD [1000] = { '\0' };
												int index = 0, agr1_chr = atoi(line_affected2);
												
												//Get LINE_AGR1 and LINE_AGR2
												while(index < agr1_chr){
													LINE_AGR1[index] = THISLINE[index];
													LINE_AGR2[index] = THISLINE[index + agr1_chr];
													index ++;	
												}
												
												printf("Editing Line %d:\n", cur_line);
												printf("%s", LINE_AGR1);
												
												fflush(stdin);
												fgets(LINE_ADD, 1000, stdin);
												LINE_ADD[strlen(LINE_ADD) - 1] = '\0';
												CLR;
												
												memset(THISLINE, '\0', sizeof(THISLINE));
												strcpy(THISLINE, LINE_AGR1);
												strcat(THISLINE, LINE_ADD);
												strcat(THISLINE, LINE_AGR2);
												
												if(strlen(THISLINE) > 1000){
													CLR;
													red;
													printf("Error on edit line argument (TOO_LARGE)\n");
													white;
													Small_stop;
													hit_something = true;
													break;
												}
												
												changed_lines = -2;
												Line_Lim ++; 
																							
											//"Copy" action
											} else {
												
												temp_curline = cur_line;
												cur_line = atoi(line_affected2);
												reverse_cur_line = true;
											}
										
										//"RemoveAll" action
										} else if(strcmp(action, "removeall")== 0){
											cur_line = atoi(line_affected1);
											changed_lines = -1;
											
											Line_Lim ++;
											memset(THISLINE, '\0', sizeof(THISLINE));
											
										//"MakeBlankLine" action
										} else if(strcmp(action, "makeblankline")== 0){
											cur_line = atoi(line_affected1);
											changed_lines = 1;
											
											Line_Lim ++;
											memset(THISLINE, '\0', sizeof(THISLINE));
										}
										
										break;
									}
										
									case 'P': {
										
										char what [10] = { '\0' }, page_affected [10] = { '\0' };
										int index = 0;
										
										//Get what user wants to do
										while(THISLINE[i + 4 + index] != ' '){
											if(THISLINE[index + i + 4] == ' ' || THISLINE[index + i + 4] == '\0')
											break;
											
											what[index] = tolower(THISLINE[index + i + 4]);
											index ++;
										}
										
										if(what[0] == '\0' || what[0] == ' '){
											CLR;
											red;
											printf("Missing main argument on page command (ARGUMENT_MISSING)\n");
											white;
											Small_stop;
											hit_something = true;
											break;
										}
										
										//Get the page affected
										index = 0;
										while(isdigit(THISLINE[i + 5 + index + strlen(what)])){
											page_affected[index] = THISLINE[i + 5 + index + strlen(what)];
											index ++;
										}
										
										if(page_affected[0] == '\0'){
											CLR;
											red;
											printf("Missing sub argument on page command (ARGUMENT_MISSING)\n");
											white;
											Small_stop;
											hit_something = true;
											break;
										}
										
										int what_page = atoi(page_affected);
										if(what_page < 1 || what_page > 10){
											CLR;
											red;
											printf("Error on page command argument (PAGE_UNKNOWN)\n");
											white;
											Small_stop;
											hit_something = true;
											break;
										}
										
										strcat(page_affected, ".txt");
										ChangeCurPath("OTHER.books");
										
										if(strcmp(what, "change")== 0){
											FILE * fcurpage = fopen("CurPage.txt", "w");
											fprintf(fcurpage, "%s", page_affected);
											fclose(fcurpage);
											
											//Change file being edited
											strcpy(FileName, page_affected);
											
											//Get current line number AND wanted declarations from file we changed to :>
											FILE * fgetline = fopen(FileName, "r");
											fscanf(fgetline, "%d\n", &cur_line);
											fscanf(fgetline, "%s\n", wanted_declarations);
											fclose(fgetline);
											
										} else if(strcmp(what, "remove")== 0){
											remove(page_affected);
											FILE * fnewp = fopen(page_affected, "w");
											fprintf(fnewp, "1\ntemp.\n");
											fclose(fnewp);
											
										} else if(strcmp(what, "copy")== 0){
											char destination_page [10] = { '\0' };
											
											//Get the destination page
											index = 0;
											while(isdigit(THISLINE[i + 6 + index + strlen(what) + (strlen(page_affected) - 4)])){
												destination_page[index] = THISLINE[i + 6 + index + strlen(what) + (strlen(page_affected) - 4)];
												index ++;
											}
											
											what_page = atoi(destination_page);
											if(what_page < 1 || what_page > 10){
												CLR;
												red;
												printf("Error on copy page argument (UNKNOWN_PAGE)\n");
												white;
												Small_stop;
												hit_something = true;
												break;
											}
											
											strcat(destination_page, ".txt");
											
											//Error handling										
											if(strcmp(destination_page, page_affected)== 0){
												CLR;
												red;
												printf("Error on copy page argument (SAME_FILE)\n");
												white;
												Small_stop;
												hit_something = true;
												break;
											}
											
											int LINE_LIM = 0, CUR_LINE = 0;
											
											FILE * fgetlinelimit = fopen(page_affected, "r");
											fscanf(fgetlinelimit, "%d", &LINE_LIM);
											fclose(fgetlinelimit);
											LINE_LIM += 1;
											
											//Copy the contents of the source file to the new destination
											char * TEMP_LINE = (char *)malloc(1000);
											FILE * fsource = fopen(page_affected, "r");
											FILE * fdestination = fopen(destination_page, "w");
											
											while(CUR_LINE != LINE_LIM){
												fgets(TEMP_LINE, 1000, fsource);
												fprintf(fdestination, "%s", TEMP_LINE);
												memset(TEMP_LINE, '\0', sizeof(TEMP_LINE));	
												CUR_LINE ++;
											}
											
											fclose(fsource);
											fclose(fdestination);
											free(TEMP_LINE);
										}
										
										hit_something = true;
										break;
									}
									
									case 'R': {
										char new_declarations [555] = { '\0' };
										int index = 0;
										
										//Get new output rule (stolen from L argument)
										while(THISLINE[i + 4 + index] != ' '){
											if(THISLINE[index + i + 4] == ' ' || THISLINE[index + i + 4] == '\0')
											break;
											
											new_declarations[index] = tolower(THISLINE[index + i + 4]);
											index ++;
										}
										
										hit_something = true;
										new_declarations[strlen(new_declarations) - 1] = '\0';
										
										//Diplay rules if yes
										if(strcmp(new_declarations, "view")== 0){
											CLR;
											light_aqua;
											printf("Your current output rules are: %s\n", wanted_declarations);
											white;
											Small_stop;
											
										//Copy over if no
										} else {
											strcpy(wanted_declarations, new_declarations);
											
											//Update output rules from the file directly
											int MAX_LINE, CUR_LINE = 0;
											char GETLINE [1000] = { '\0' };
									
											MAX_LINE = Line_Lim;
											
											FILE * fnewtemp = fopen("__temp.txt", "w");
											FILE * foldone = fopen(FileName, "r");
											
											//Skipping BOTH lines
											fgets(GETLINE, 1000, foldone);
											fprintf(fnewtemp, "%s", GETLINE);
											fgets(GETLINE, 1000, foldone);
											fprintf(fnewtemp, "%s\n", wanted_declarations);
											
											while(CUR_LINE <= MAX_LINE){
												memset(GETLINE, '\0', sizeof(GETLINE));
												fgets(GETLINE, 1000, foldone);
												fprintf(fnewtemp, "%s", GETLINE);
												CUR_LINE ++;
											}
											
											fclose(fnewtemp);
											fclose(foldone);
											
											//Delete old, rename new to old :>
											remove(FileName);
											rename("__temp.txt", FileName);
										}
										break;
									}
										
									default:
										//Not doing anything here :>
										break;
								}
								
								//Wont display line if its a command
								if(hit_something)
								memset(THISLINE, '\0', sizeof(THISLINE));
							}
						}	
						
						//Exit if user asked to
						if(exit_editing)
						break;
						
						//Format acordingly if last input didnt include a comand
						if(!hit_something){
							char * temp_THISLINE = (char *)malloc(1000);
							memset(temp_THISLINE, '\0', sizeof(temp_THISLINE));
							strcpy(temp_THISLINE, THISLINE);
							
							cur_line ++;
							
							//Update the line limit
							if(cur_line > Line_Lim && changed_lines != -1)
							Line_Lim = cur_line;	
							
							int currentline = 0;
							FILE * ftemp = fopen("__temp.txt", "w");
							FILE * fgetbookline = fopen(FileName, "r");
							
							//Transfer data from one file to another, keeping the current line in mind
							while(currentline <= Line_Lim){
								//Transfer normaly
								if(currentline != cur_line){
									fgets(THISLINE, 1000, fgetbookline);
									
									if(currentline != 0)
									fprintf(ftemp, "%s", THISLINE);
									
									else
									fprintf(ftemp, "%d\n", Line_Lim);
									
								//Transfer string the user wrote
								} else if(temp_THISLINE[0] != '\0'){
									fgets(THISLINE, 1000, fgetbookline);	//Skip THIS line  
									
									fprintf(ftemp, "%s", temp_THISLINE);	
									
								} else {
									//Make new Blank Line 
									if(changed_lines == 1 && currentline == cur_line){
										fprintf(ftemp, "\n");
										
									//Delete this line
									} else if(changed_lines == -1 && currentline == cur_line){
										fgets(THISLINE, 1000, fgetbookline);
										memset(THISLINE, '\0', sizeof(THISLINE));
									}
									
								}
								
								currentline ++;
							}
							
							fclose(ftemp);
							fclose(fgetbookline);
							
							//Delete old, rename new to old :>
							remove(FileName);
							rename("__temp.txt", FileName);
							
							free(temp_THISLINE);
							
							//Forcing the set back limit
							if(Line_Lim > 50)
							Line_Lim = 50;
							
							//This only exists to update max line :despair:
							if(changed_lines == -1 || changed_lines == -2){
								int MAX_LINE, CUR_LINE = -1;
								char GETLINE [1000] = { '\0' };
								
								if(changed_lines == -1)
								Line_Lim -= 2;
								
								else
								Line_Lim --;
								
								MAX_LINE = Line_Lim;
								
								FILE * fnewtemp = fopen("__temp.txt", "w");
								FILE * foldone = fopen(FileName, "r");
								
								//Skipping this line
								fgets(GETLINE, 1000, foldone);
								fprintf(fnewtemp, "%d\n", MAX_LINE);
								
								while(CUR_LINE <= MAX_LINE){
									memset(GETLINE, '\0', sizeof(GETLINE));
									fgets(GETLINE, 1000, foldone);
									fprintf(fnewtemp, "%s", GETLINE);
									CUR_LINE ++;
								}
								
								fclose(fnewtemp);
								fclose(foldone);
								
								//Delete old, rename new to old :>
								remove(FileName);
						     	rename("__temp.txt", FileName);
							}
							
							if(reverse_cur_line)
							cur_line = temp_curline;
							
						}
					}
					
					free(wanted_declarations);
					free(FileName);
					free(THISLINE);
					CLR;
				}
			}
			
		} else if(strcmp(Input, "back")== 0 || strcmp(Input, "nevermind")== 0){
			break; CLR;
			
		} else { Error; }
		
	}
	
	return ITEM_CODE;
}

//This function only exists to display the special items and is only used in GitItem case "Item" cause i dont wanna write the same thing over and over again
int DisplayAllSpecialItems(void){
	
	int special_itm_id = 0, number_of_items_we_have = 0;
	
	//1st SMALL one to get the MAX strlen size and the count of special items we have
	ChangeCurPath("INVENTORY");
	FILE * fgetspecialitemswehave = fopen("Specials.txt", "r");
	GetAppResources("Usefull files.Items");
	FILE * fcountMAXstrlen = fopen("SpecialItemNames.txt", "r");
	
	int has_special = 0, current_max_strlen = 0;
	char current_itm_name [100] = { '\0' };
	bool has_items = false;
	
	//Counting EACH line
	for(int i = 0; i < 26; i ++){
		fscanf(fgetspecialitemswehave, "%d", &has_special);
		fgets(current_itm_name, 100, fcountMAXstrlen);
		
		int counted_strlen = 0;
		
		//If its a yes, count strlen
		if(has_special == 1){
			number_of_items_we_have ++;
			has_items = true;
			
			//Sp item 8 is (kinda) bugged rn so we have to make a special case for it
			if(i != 8){
				//count the strlen of the 1st space 
				while(current_itm_name[counted_strlen] != 32)
				counted_strlen ++;
				
			} else {
				counted_strlen = 18;
			}
			
			counted_strlen += strlen(current_itm_name);
			//2 spaces and the '[]'
			counted_strlen += 4;
			
			if(counted_strlen > current_max_strlen)
			current_max_strlen = counted_strlen;
		}
		memset(current_itm_name, '\0', sizeof(current_itm_name));
	}
	
	fclose(fgetspecialitemswehave);
	fclose(fcountMAXstrlen);
	
	//No items? Dont format.
	if(!has_items){
		red;
		printf("You have no special Items.\n");
		white;
		Small_stop;
		return -1;
	}
	
	//We kinda need to have this pointer ALWAYS open (while formating)
	ChangeCurPath("INVENTORY");
	FILE * fcheckwhatitemswehave = fopen("Specials.txt", "r");
	
	//Variables we need inside the loop lol
	int repeat_delim = GetTerminalSize("columns") / (current_max_strlen + 2), times_repeated = number_of_items_we_have / repeat_delim;
	int items_AFTER_normal_formating = times_repeated * repeat_delim - number_of_items_we_have, cur_id = 1, last_itm_name = 0;
	items_AFTER_normal_formating = abs(items_AFTER_normal_formating);
	
	//Repeating MANY times
	for(int k = 0; k < times_repeated + 1; k ++){
	
		int next_displacement = 0;
		//Get the B I G line in
		ChangeCurPath("OTHER.temp");
		FILE * fsetformatingvars = fopen("FormatingVarTemp.txt", "w");
		for(int i = 0; i < repeat_delim; i ++){
			fprintf(fsetformatingvars, "%d\n", next_displacement);
			fprintf(fsetformatingvars, "|");
			for(int j = 0; j < current_max_strlen; j ++)
			fprintf(fsetformatingvars, "-");
			
			fprintf(fsetformatingvars, "|\n");
			
			next_displacement += current_max_strlen + 2;	
		}
		
		fclose(fsetformatingvars);
		
		FormatTextEXT("center", "", true, 0, ".", true, 0, 0);
		
		ChangeCurPath("OTHER.temp");
		
		if(k == times_repeated){
			if(items_AFTER_normal_formating != 0)
			fopen("FormatingVarTemp.txt", "w");
			
		} else
		fopen("FormatingVarTemp.txt", "w");
		
		//Get full special itm name and its 1st name (and display)
		int temp = 0, delim = last_itm_name + repeat_delim, current_delim = 0;
		
		if(k == times_repeated && items_AFTER_normal_formating != 0){
			last_itm_name = 0;
			delim = items_AFTER_normal_formating;
		}
		
		else if(k == times_repeated && items_AFTER_normal_formating == 0)
		delim = 0;
		
		char * catch_name_returned = (char *)malloc(50), solo_name[50] = { '\0' };
		while(last_itm_name < delim){
			fscanf(fcheckwhatitemswehave, "%d\n", &temp);
			
			//Exists? Show.
			if(temp == 1){
				last_itm_name ++;
				
				memset(catch_name_returned, '\0', sizeof(catch_name_returned));
				catch_name_returned = GetItemName(200 + cur_id);
				
				int curchar = 0;
				memset(solo_name, '\0', sizeof(solo_name));
				while(catch_name_returned[curchar] != 32){
					solo_name[curchar] = catch_name_returned[curchar];
					curchar ++;
					
					//Bandaid patch for "Arrow-Shapped-Leaf"
					if(strcmp(catch_name_returned, "Arrow-Shapped-Leaf")== 0 && curchar >= 18)
					break;
				}
				
				int str_delim = current_max_strlen - (strlen(catch_name_returned) + strlen(solo_name) + 4);  
				
				fprintf(fsetformatingvars, "%d\n", current_delim);
				fprintf(fsetformatingvars, "| %s [%s]", catch_name_returned, solo_name);
				
				for(int i = 0; i < str_delim; i ++){
					fprintf(fsetformatingvars, " ");	
					current_delim ++;
				}
				
				fprintf(fsetformatingvars, "|\n");
				current_delim += strlen(catch_name_returned) + strlen(solo_name) + 6;
			}
			
			cur_id ++;
		}
		
		fclose(fsetformatingvars);
		free(catch_name_returned);
		
		FormatTextEXT("center", "", true, 0, ".", true, 0, 0);
		
		//LAST LINE NEEDS CUSTOM FORMATING
		if(k == times_repeated && items_AFTER_normal_formating != 0){
			next_displacement = 0;
			
			ChangeCurPath("OTHER.temp");
			FILE * fsetformatingvars = fopen("FormatingVarTemp.txt", "w");
			for(int i = 0; i < items_AFTER_normal_formating; i ++){
				fprintf(fsetformatingvars, "%d\n", next_displacement);
				fprintf(fsetformatingvars, "|");
				for(int j = 0; j < current_max_strlen; j ++)
				fprintf(fsetformatingvars, "-");
				
				fprintf(fsetformatingvars, "|\n");
				
				next_displacement += current_max_strlen + 2;	
			}
			
			fclose(fsetformatingvars);
			
			FormatTextEXT("center", "", true, 0, ".", true, 0, 0);
		}
	}
	
	fclose(fcheckwhatitemswehave);
	
	printf("\n");
	light_blue; CenterText("Please select an item...");
	CenterText("You can always type \"Back\" to leave!"); white;
	
	String_Input;
	
	//FREE MY BOY HE DID NOTHING WRONG
	if(strcmp(Input, "back")== 0)
	return -1;
	
	//See if name user inputed actually exists
	GetAppResources("Usefull Files.Items");
	char compare_name [50] = { '\0' };
	bool hit_special_itm = false;
	
	//2 pointers in the same file to do the needed distribuition
	FILE * fget1stspecialitemname = fopen("SpecialItemNames.txt", "r");
	FILE * fgetpointerdisplacement = fopen("SpecialItemNames.txt", "r");
	
	//Loop for ALL lines
	for(int i = 0; i < 26; i ++){ 
		special_itm_id ++;
		memset(compare_name, '\0', sizeof(compare_name));
		fscanf(fget1stspecialitemname, "%s\n", compare_name);
		
		for(int j = 0; j < strlen(compare_name); j ++)
		compare_name[j] = tolower(compare_name[j]);
		
		if(strcmp(Input, compare_name)== 0 && Inventory("CHECK", 199 + special_itm_id, 1)){
			hit_special_itm = true;
			break;
		}
		
		//This is to get "compare_name" ONLY to get the start word of the string 
		fgets(compare_name, 50, fgetpointerdisplacement);
		fseek(fget1stspecialitemname, ftell(fgetpointerdisplacement), SEEK_SET);
	}
	
	fclose(fget1stspecialitemname);
	fclose(fgetpointerdisplacement);
	
	if(!hit_special_itm)
	special_itm_id = 0;
	
	return special_itm_id;
}

int DisplayCenterList(const char * wat_mer){
	
	//The "MerPriceInfo" for the Center function to see
	
	/*
	Note to reader:
	
	Theres a formating error depending on the window size / terminal size
	gets deformated by 1 (or more)
	*/
	
	bool price_variates_on_tree_dig = false;
	char full_itm_name [100] = { '\0' };
	int wanted_itm = 0, displace_ptr = 0, limits_needed = 0, max_full_name_strlen = 0, max_short_name_strlen = 0, total_possible_strlen = 0;
	
	int check_for_ids [5] = { 35, 45, 101, 115, 134 };
	
	//Getting variables and stuff here
	int INT_MERCHANT = wat_mer[3] - '0';
	INT_MERCHANT -= 1;
	limits_needed = check_for_ids[INT_MERCHANT];
	
	if(INT_MERCHANT > 0){
		limits_needed -= check_for_ids[INT_MERCHANT - 1];
		displace_ptr = check_for_ids[INT_MERCHANT - 1];
		
		if(INT_MERCHANT == 4){
			limits_needed = 8;
			displace_ptr = 124;
			
		} 
	}
	
	ChangeCurPath("OTHER.merprices");
	CatCurPath(wat_mer);
	
	FILE * fgetbuy = fopen("Buy.txt", "r");
	FILE * fgetsell = fopen("Sell.txt", "r");
	
	//Tiny check (price_variates_on_tree_dig)
	int check_for_doubles = 0;
	while(fscanf(fgetbuy, "%d", &check_for_doubles)!= EOF){
		if(check_for_doubles >= 100){
			price_variates_on_tree_dig = true;
			break;	
		}
	}
	
	fclose(fgetbuy);
	
	//Reset ptr to start of the file to be used again on the display
	fopen("Buy.txt", "r");
	
	GetAppResources("Usefull Files.Items");
	FILE * fgetitemnames = fopen("ItemNames.txt", "r");
	
	//Changing current ptr pos
	for(int i = 0; i < displace_ptr; i ++){
		fgets(full_itm_name, 100, fgetitemnames);
		memset(full_itm_name, '\0', sizeof(full_itm_name));
	}
	
	char temp_1st_name [50] = { '\0' }; 
	
	//Get MAX_FULL_STRLEN and MAX_SHORT_STRLEN
	for(int i = 0; i < limits_needed; i ++){
		int full_itm_strlen = 0, first_itm_strlen = 0;
		
		fgets(full_itm_name, 100, fgetitemnames);
		full_itm_name[strlen(full_itm_name) - 1] = '\0';
		int cur_char = 0;
		
		full_itm_strlen = strlen(full_itm_name);
		
		//Get 1st name
		while(full_itm_name[cur_char] != 32){
			temp_1st_name[cur_char] = full_itm_name[cur_char];
			cur_char ++;
			
			if(cur_char > full_itm_strlen)
			break;
		}
		
		first_itm_strlen = strlen(temp_1st_name);
		
		//Full name strlen
		if(full_itm_strlen > max_full_name_strlen)
		max_full_name_strlen = full_itm_strlen;
		
		//Short name strlen
		if(first_itm_strlen > max_short_name_strlen)
		max_short_name_strlen = first_itm_strlen;
		
		memset(full_itm_name, '\0', sizeof(full_itm_name));
		memset(temp_1st_name, '\0', sizeof(temp_1st_name));
	}
	
	//Calculating limit
	total_possible_strlen = 10;
	total_possible_strlen += max_short_name_strlen;
	total_possible_strlen += 4;
	total_possible_strlen += max_full_name_strlen;
	total_possible_strlen += 4;
	total_possible_strlen += 13;
	
	if(price_variates_on_tree_dig)
	total_possible_strlen ++;
	
	while(true){
		CLR;
		
		//TRY to format Y
		int expected_y_formating = GetTerminalSize("rows") - (limits_needed + 6);
		if(expected_y_formating > 0){
			expected_y_formating /= 2;
			
			for(int i = 0; i < expected_y_formating; i ++)
			printf("\n");
		}
		
		wanted_itm = 0;
		bool is_valid = false;
		
		GetAppResources("Usefull Files.Items");
		FILE * fgetitemnames = fopen("ItemNames.txt", "r");
		
		//Displace ptr
		for(int i = 0; i < displace_ptr; i ++){
			fgets(full_itm_name, 100, fgetitemnames);
			memset(full_itm_name, '\0', sizeof(full_itm_name));
		}
		
		ChangeCurPath("OTHER.temp");
		
		for(int k = 0; k < 2; k ++){
			//|-----------------------------------------------------------|
			for(int i = 0; i < 2; i ++){
				FILE * fsetformatingvars = fopen("FormatingVarTemp.txt", "w");
				fprintf(fsetformatingvars, "0\n");
				fprintf(fsetformatingvars, "|-------");
				
				//Getting delims
				for(int j = 0; j < max_full_name_strlen + max_short_name_strlen + 5; j ++)
				fprintf(fsetformatingvars, "-");
				
				//BUY / SELL
				fprintf(fsetformatingvars, "-----------------");
				
				if(price_variates_on_tree_dig)
				fprintf(fsetformatingvars, "-");
				
				fprintf(fsetformatingvars, "|\n");
				fclose(fsetformatingvars);	
				
				FormatTextEXT("center", "", true, 0, ".", true, 0, 0);
				
				if(i == 1)
				break;
				
				fopen("FormatingVarTemp.txt", "w");
				fprintf(fsetformatingvars, "0\n");
				
				//| [ID] | [NAME]       | [FULL NAME]          | [SELL / BUY] |
				if(k == 0){
					fprintf(fsetformatingvars, "| [ID] | [NAME]  ");
					
					for(int j = 0; j < max_short_name_strlen - 5; j ++)
					fprintf(fsetformatingvars, " ");
					
					fprintf(fsetformatingvars, "| [FULL NAME] ");
					
					for(int j = 0; j < max_full_name_strlen - 11; j ++)
					fprintf(fsetformatingvars, " ");
					
					fprintf(fsetformatingvars, "| [SELL / BUY] ");
					
					if(price_variates_on_tree_dig)
					fprintf(fsetformatingvars, " ");
					
				//| [Type Name or Item ID to select it] |
				} else {
					fprintf(fsetformatingvars, "|");
					
					int how_many_spaces = 28 + max_short_name_strlen + max_full_name_strlen;
					how_many_spaces -= 35;
					how_many_spaces /= 2;
					
					//+ 2 here because it was bugging sometimes
					for(int j = 0; j < how_many_spaces + 1; j ++)
					fprintf(fsetformatingvars, " ");
					
					fprintf(fsetformatingvars, "[Type Name or Item ID to select it]");
					
					for(int j = 0; j < how_many_spaces; j ++)
					fprintf(fsetformatingvars, " ");
					
					//b e t t e r formating
					if(price_variates_on_tree_dig){
						fprintf(fsetformatingvars, " ");
					
						if(total_possible_strlen % 2 == 0)
						fprintf(fsetformatingvars, " ");
							
					} else if(!price_variates_on_tree_dig && total_possible_strlen % 2 != 0)
					fprintf(fsetformatingvars, " ");
					
				}
				
				fprintf(fsetformatingvars, "|\n");
				fclose(fsetformatingvars);
				
				FormatTextEXT("center", "", true, 0, ".", true, 0, 0);
			}
			
			//| [01] | [Basil]      | Basil                | [06] |  [14] |
			if(k == 0){
				int copy_of_max_short_strlen = max_short_name_strlen;
				int copy_of_max_long_strlen = max_full_name_strlen;
		
				char temp_1st_name [50] = { '\0' }; 
				
				ChangeCurPath("OTHER.temp");
				
				//EVERY SINGLE LINE LMFAO
				int current_ID = 0;
				for(int i = 0; i < limits_needed; i ++){
					current_ID ++;
					
					//Reset (and get new) names
					memset(full_itm_name, '\0', sizeof(full_itm_name));
					memset(temp_1st_name, '\0', sizeof(temp_1st_name));
					
					//There are some expections
					if(INT_MERCHANT == 1 && i == 6){
						fgets(full_itm_name, 100, fgetitemnames);
						memset(full_itm_name, '\0', sizeof(full_itm_name));
						i ++;
					
					//Remember unused ids
					} else if(INT_MERCHANT == 2 && (i % 7 == 0 || i == 1)){
						//If its invalid we skip :D
						fgets(full_itm_name, 100, fgetitemnames);
						memset(full_itm_name, '\0', sizeof(full_itm_name));
						i ++;
						
					}
					
					fgets(full_itm_name, 100, fgetitemnames);
					full_itm_name[strlen(full_itm_name) - 1] = '\0';
					
					int cur_char = 0;
					while(full_itm_name[cur_char] != 32){
						temp_1st_name[cur_char] = full_itm_name[cur_char];
						cur_char ++;
						
						if(cur_char >= strlen(full_itm_name))
						break;
					}
					
					int stlren_1st_name = strlen(temp_1st_name);
					
					int add_to_displacement = 0;
					//NEED TO PREDICT NEXT VARIABLE SPACE BTW!!!
					FILE * fsetformatingvars = fopen("FormatingVarTemp.txt", "w");
					fprintf(fsetformatingvars, "0\n");
					
					//ID.	
					if(current_ID < 10){
						fprintf(fsetformatingvars, "| [0\n");
						fprintf(fsetformatingvars, "4\n");
				
					} else {
						fprintf(fsetformatingvars, "| [\n");	
						fprintf(fsetformatingvars, "3\n");
						
					} 
					
					fprintf(fsetformatingvars, "%d] | [\n", current_ID);
					
					fprintf(fsetformatingvars, "10\n");
					fprintf(fsetformatingvars, "%s\n", temp_1st_name);
					
					int temp_displace_ptr = strlen(temp_1st_name);
					fprintf(fsetformatingvars, "%d\n", 10 + stlren_1st_name);
					
					fprintf(fsetformatingvars, "] ");
					
					//Displace spaces here (max short)
					temp_displace_ptr += copy_of_max_short_strlen - stlren_1st_name;
					for(int j = 0; j < copy_of_max_short_strlen - stlren_1st_name; j ++)
					fprintf(fsetformatingvars, " ");
					
					fprintf(fsetformatingvars, "| \n");
					
					fprintf(fsetformatingvars, "%d\n", 15 + temp_displace_ptr);
					
					fprintf(fsetformatingvars, "%s", full_itm_name);
					
					int strlen_full_name = strlen(full_itm_name);
					
					//Displace spaces here (max long)
					temp_displace_ptr += copy_of_max_long_strlen - strlen_full_name;
					for(int j = 0; j < copy_of_max_long_strlen - strlen_full_name; j ++)
					fprintf(fsetformatingvars, " ");
					
					fprintf(fsetformatingvars, " | \n");
					
					fprintf(fsetformatingvars, "%d\n", 22 + temp_displace_ptr + strlen_full_name);
					
					//SELL / BUY things
					fprintf(fsetformatingvars, "[");
					
					//Git sell
					int sell_val = 0, buy_val = 0;
					fscanf(fgetsell, "%d", &sell_val);
					
					if(sell_val < 10 && price_variates_on_tree_dig)
					fprintf(fsetformatingvars, "0");
					
					if(sell_val < 10 && !price_variates_on_tree_dig)
					fprintf(fsetformatingvars, "0");
					
					if(sell_val < 100 && price_variates_on_tree_dig)
					fprintf(fsetformatingvars, "0");
					
					if(!price_variates_on_tree_dig)
					fprintf(fsetformatingvars, "%d] |  [", sell_val);
					
					else
					fprintf(fsetformatingvars, "%d] | [", sell_val);
					
					//Git buy
					fscanf(fgetbuy, "%d", &buy_val);
					
					if(buy_val < 10 && price_variates_on_tree_dig)
					fprintf(fsetformatingvars, "0");
					
					if(buy_val < 10 && !price_variates_on_tree_dig)
					fprintf(fsetformatingvars, "0");
					
					if(buy_val < 100 && price_variates_on_tree_dig)
					fprintf(fsetformatingvars, "0");
					
					fprintf(fsetformatingvars, "%d] |     \n", buy_val);
					
					fclose(fsetformatingvars);
					
					//Some formating errors caused by the (total_possible_strlen) being par or inpar
					//(And the 5 spaces at the end of the fprintf on BUY)
					if(total_possible_strlen % 2 == 0)
					FormatTextEXT("center", "", true, -1, ".", true, 0, 0);	
					
					else
					FormatTextEXT("center", "", true, -4, ".", true, 0, 0);	
				}
			}
		}
		fclose(fgetitemnames);
		
		//Try Y formating
		if(expected_y_formating > 0){
			for(int i = 0; i < expected_y_formating; i ++)
			printf("\n");
		}
		
		String_Input;
		
		if(strcmp(Input, "back")== 0){
			fclose(fgetbuy);
			fclose(fgetsell);
			return 0;
		}
		
		ChangeCurPath("OTHER.temp");
		FILE * fputtempvarsin = fopen("MerPriceInfo.txt", "w");
		
		//Is id?
		if(isdigit(Input[0])){
			wanted_itm = atoi(Input);
			
			if(wanted_itm > 0 && wanted_itm < limits_needed)
			is_valid = true;
			
			else
			wanted_itm = 0;
			
			//Need to displace somethings
			if(is_valid){
				ChangeCurPath("OTHER.merprices");
				CatCurPath(wat_mer);
				
				FILE * fgetsellprice = fopen("Sell.txt", "r");
				FILE * fgetbuyprice = fopen("Buy.txt", "r");
				
				int sell_price = 0, buy_price = 0;
				char tempstr [5] = { '\0' };
				
				//Displace both pointers to get the value needed
				for(int i = 0; i < wanted_itm - 1; i ++){
					fgets(tempstr, 5, fgetsellprice);
					fgets(tempstr, 5, fgetbuyprice);
				}
				
				fscanf(fgetsellprice, "%d", &sell_price);
				fscanf(fgetbuyprice, "%d", &buy_price);
				
				fclose(fgetsellprice);
				fclose(fgetbuyprice);
				
				fprintf(fputtempvarsin, "%d\n", sell_price);
				fprintf(fputtempvarsin, "%d\n", buy_price);
				
				if(INT_MERCHANT == 1 && wanted_itm >= 6)
				wanted_itm ++;
				
				else if(INT_MERCHANT == 2){
					int predicted_displacement = (wanted_itm + 1) / 6;
					predicted_displacement ++;
					
					wanted_itm += predicted_displacement;
				}
			}
			
		} else {
			GetAppResources("Usefull Files.Items");
			FILE * fgetitemnames = fopen("ItemNames.txt", "r");
			
			//Changing current ptr pos
			for(int i = 0; i < displace_ptr; i ++){
				fgets(full_itm_name, 100, fgetitemnames);
				memset(full_itm_name, '\0', sizeof(full_itm_name));
			}
			
			wanted_itm = displace_ptr;
			
			char temp_1st_name [50] = { '\0' }; 
			
			//Is string?
			for(int i = 0; i < limits_needed; i ++){
				fgets(full_itm_name, 100, fgetitemnames);
				
				int cur_char = 0;
				//Get 1st name
				while(full_itm_name[cur_char] != 32){
					temp_1st_name[cur_char] = full_itm_name[cur_char];
					temp_1st_name[cur_char] = tolower(temp_1st_name[cur_char]);
					cur_char ++;
					
					if(cur_char >= strlen(full_itm_name))
					break;
				}
				
				//Check if any 1st name matches (auto gets id from the file btw)
				if(strcmp(Input, temp_1st_name)== 0){
					wanted_itm += i + 1;
					is_valid = true;
					break;
				}
				
				memset(full_itm_name, '\0', sizeof(full_itm_name));
				memset(temp_1st_name, '\0', sizeof(temp_1st_name));
			}	
		}
		
		fclose(fputtempvarsin);
		
		if(is_valid)
		break;
		
		//Give Error msg
		red;
		switch(INT_MERCHANT){
			case 0:
				CenterText("[NPC] Anfigo: \"Please type the item id or the item name provided in the list\" [Type \"back\" to leave]"); break;
				
			case 1:
				CenterText("[NPC] Synist: \"Type the id or the name of the item you want\" [Type \"back\" to leave]"); break;
				
			case 2:
				CenterText("[NPC] Lavist: \"I cannot understand what you want, type the ID or the Name of the item you wish\" [Type \"back\" to leave]"); break;
			
			case 3:
				CenterText("[NPC] Firment: \"Hey, just type the ID or the Name of the item you want to get!\" [Type \"back\" to leave]"); break;
				
			case 4:
				CenterText("[NPC] Maidiste: \"Type the ID or the Name of the item you want\"..."); break;
				
			default:
				break;
		}
		white;
		Small_stop;
	}
	
	fclose(fgetbuy);
	fclose(fgetsell);
	
	//Get real ID in
	wanted_itm += displace_ptr;
	return wanted_itm;
}

//Animal function
int Animal(bool is_tut){
	
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
	int animal_got = 0;
	
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
			
			Small_stop;
		}
		
		printf("Next move?\n");
			
			if((strcmp(game_set, "Char")== 0 && !is_tut) || (strcmp(tut_game_set, "Char")== 0 && is_tut)){
				
			String_Input;
			
				//Happends cause lead is for animal barn thing and lure is for wild animals in the montain
				//and the whole trust system thing
				
				//Movements
				if(strcmp(Input, "up")== 0){
				Y -= 1; stored_move = 1; }
					
				else if(strcmp(Input, "left")== 0){
				X -= 1;	stored_move = 2; }
				
				else if(strcmp(Input, "right")== 0){
				X += 1; stored_move = 3; }
					
				else if(strcmp(Input, "down")== 0){
				Y += 1;	stored_move = 4; }
				
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
				String_Input;
				
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
					
			String_Input;
					
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
			
		TimeCalc("CALC", 0, 1, 0);
		
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
			
			Small_stop;
			free(hint);
			CLR;
		}
	}
	
	return animal_got;
}

//Crop Function
void Crop(const short int Crop1_ID, bool is_tut){
	
	//Note to reader: This is a backup of the "game_set" global setting, used for the display and movements in minigames table types, 
	//makes you able to alter your gameset to whatever you want without actually altering it
	char tut_game_set [5];
	strcpy(tut_game_set, game_set);
	
	bool changed_game_set = true, do_key3 = false;
	
	//defined table showcase and accepted input type
	short int i_table_pos_[26];
	char c_table_pos_[26] [15];
	
	short int user_turn = 0, X, Y, L, user_pos, dif;
	short int crops_colected, crop_spawn, crop_spawn1, crop_pick_up, two_crops, picked1, picked2;
	short int next_move;
	int crp_ID = 0;
	
	bool Leave = false;
	
	//Tutorial Skipping stuff :>
	if(is_tut){
		if(display_all_tut_once){
			ChangeCurPath("OTHER.tutorials");
			if(access("Crop.txt", F_OK)== 0)
			return;
		}
		if(skip_tut_display)
		return;
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
		if(strcmp(hint_minigame, "Crop")== 0){
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
	
	while(true){
	
		//Crop spawning depending on table size + dificulty
		if(strcmp(dificulty, "Lucid")== 0 || strcmp(dificulty, "False")== 0){
			
			if(strcmp(dificulty, "Lucid")== 0){
				crop_spawn = rand()% 9 + 1;
				crop_spawn1 = rand()% 9 + 1;
			}
			
			if(strcmp(dificulty, "False")== 0){
			crop_spawn = rand()% 9 + 1;
			crop_spawn1 = 0;
			}
			
			dif = 1;
			
		} else {
			
			if(strcmp(dificulty, "Vivid")== 0){
				crop_spawn = rand()% 25 + 1;
				crop_spawn1 = rand()% 25 + 1;
			}
			
			if(strcmp(dificulty, "Nightmare")== 0){
			crop_spawn = rand()% 25 + 1;
			crop_spawn1 = 0;
			}
			
			dif = 2;	
		}
		
		if(crop_spawn == crop_spawn1){
			
			if(strcmp(dificulty, "False")== 0 || strcmp(dificulty, "Nightmare")== 0)
			crop_spawn1 = 0;
				
			else {
				
			if(dif == 1)
			crop_spawn = rand()% 9 + 1;
			
			else
			crop_spawn1 = rand()% 25 + 1;
				
			if(DEBUG_MODE)
			printf("[DEBUG] _> Both crops in the same position\n");
			sleep(1);
			
			
			}
		
		} else
		break;
	
	}
	
	if(DEBUG_MODE)
	printf("[DEBUG] _> Crop pos? %d / Crop1 pos? %d\n", crop_spawn, crop_spawn1);
	
	
	printf("Starting Grid:\n");
	
	//Shows the "starting table"
	if(dif == 1){
		if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
			printf("[0] [1] [0]\n");
		    printf("[2] [9] [3]\n");
		    printf("[0] [4] [0]\n\n\n");
		} else {
			printf("[NONE] [UP] [NONE]\n");
		    printf("[LEFT] [YOU] [RIGHT]\n");
		    printf("[NONE] [DOWN] [NONE]\n\n\n");
		}
		
	} else {
		if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
			printf("[0] [0] [0] [0] [0]\n");
		    printf("[0] [0] [1] [0] [0]\n");
		    printf("[0] [2] [9] [3] [0]\n");
		    printf("[0] [0] [4] [0] [0]\n");
		    printf("[0] [0] [0] [0] [0]\n\n\n");
		} else {
			printf("[NONE] [NONE] [NONE] [NONE] [NONE]\n");
		    printf("[NONE] [NONE] [UP] [NONE] [NONE]\n");
		    printf("[NONE] [LEFT] [YOU] [RIGHT] [NONE]\n");
		    printf("[NONE] [NONE] [DOWN] [NONE] [NONE]\n");
		    printf("[NONE] [NONE] [NONE] [NONE] [NONE]\n\n\n");
		}
		
	}

	//Setting starting location
	if(dif == 1)
	X = 2, Y = 2;
	
	else
	X = 3, Y = 3;
	
	//Caps mobility at 15 turns b4 closing the game
	while(user_turn != 15){
		
		if(changed_game_set && is_tut){
			changed_game_set = false;
			
			if((strcmp(tut_game_set, "Int")== 0 && is_tut)){
				printf("Listen up, this is important\n");
				printf("Type 1 to go Up a Square, 2 to go left, 3 to go right and 4 to go down\n");
				printf("Type 9 to leave WITHOUT collect matherials and 0 to stay in the same spot\n");
				printf("Type 8 to switch \"game_set\" types, aka if you are playing with \"INT\" it switches to \"CHAR\" and vice versa (tutorial only command)\n");
				printf("Might has well mention your objective here is to pick up crops, you can see them by looking at the squares and seeing a big old \"8\" inside of them, just walk over them and you will pick them up\n");
				printf("One last thing, you have a limited number of moves before you get kicked out BUT you get the matherials if you get kicked out by the number of moves\n");
				printf("Understood? You better...\n\n");
			} else {
				printf("Listen up, this is important\n");
				printf("Type \"Up\" to go Up a Square, \"Left\" to go left, \"Right\" to go right and \"Down\" to go down\n");
				printf("Type \"Leave\" or \"Back\" to leave WITHOUT collect matherials and \"stay\" to stay in the same spot\n");
				printf("Type \"Game\" to switch \"game_set\" types, aka if you are playing with \"INT\" it switches to \"CHAR\" and vice versa\n");
				printf("Might has well mention your objective here is to pick up crops, you can see them by looking at the squares and seeing a big old \"CROP\" inside of them, just walk over them and you will pick them up\n");
				printf("One last thing, you have a limited number of moves before you get kicked out BUT you get the matherials if you get kicked out by the number of moves\n");
				printf("Understood? You better...\n\n");
			}
					
			Small_stop;
		}
		
		printf("Next move?\n");
		
		if((strcmp(game_set, "Char")== 0 && !is_tut) || (strcmp(tut_game_set, "Char")== 0 && is_tut)){
		String_Input;
		
			//Movements
			if(strcmp(Input, "up")== 0)
			Y -= 1;
				
			else if(strcmp(Input, "left")== 0)
			X -= 1;	
			
			else if(strcmp(Input, "right")== 0)
			X += 1;
				
			else if(strcmp(Input, "down")== 0)
			Y += 1;	
				
			else if(strcmp(Input, "stay")== 0)
			user_turn -= 1;
				
			else if(strcmp(Input, "game")== 0 && is_tut){
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
			String_Input;
			
			//Int movements
			if(strcmp(Input, "1")== 0)
			Y -= 1;
			
			else if(strcmp(Input, "2")== 0)
			X -= 1;
			
			else if(strcmp(Input, "3")== 0)
			X += 1;
			
			else if(strcmp(Input, "4")== 0)
			Y += 1;
			
			else if(strcmp(Input, "0")== 0)
			user_turn -= 1;
			
			else if(strcmp(Input, "8")== 0 && is_tut){
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
			
			CLR;
			
			if(Leave)
			break;
			
		}
		
		CLR;
		
		user_turn ++;
		
		//Showing errors depending on how big table is
		if(dif == 2){
			
			if (X >= 6){ printf("Outside playing field\n"); sleep(1); X = 5; user_turn--; CLR; }
		    else if (Y >= 6){ printf("Outside playing field\n"); sleep(1); Y = 5; user_turn--; CLR; }
		    else if (X <= 0){ printf("Outside playing field\n"); sleep(1); X = 1; user_turn--; CLR; }
		    else if (Y <= 0){ printf("Outside playing field\n"); sleep(1); Y = 1; user_turn--; CLR; }
			
		} else {
			
			if (X >= 4){ printf("Outside playing field\n"); sleep(1); X = 3; user_turn--; CLR; }
		    else if (Y >= 4){ printf("Outside playing field\n"); sleep(1); Y = 3; user_turn--; CLR; }
		    else if (X <= 0){ printf("Outside playing field\n"); sleep(1); X = 1; user_turn--; CLR; }
		    else if (Y <= 0){ printf("Outside playing field\n"); sleep(1); Y = 1; user_turn--; CLR; }
							
		}
		
		//Calculate L with this simple formula (diferent on what dificulty user is playing)
		if(dif == 2)
		L = (Y * 5) - 5;
		
		else
		L = (Y * 3) - 3;
		
		//Calculating table position
		user_pos = X + L;
		
		if(DEBUG_MODE)
		printf("[DEBUG] _> User X? %d / Y? %d / L? %d / Pos? %d\n", X, Y, L, user_pos);
		 
		
		//Loop to randomize AND display crops again if they are in the same place
		while(true){
			
		if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
			
			//Reseting all positions to nothing to be modified has playing field
			memset(i_table_pos_, 0, sizeof(i_table_pos_));
			
			//Displays the user position and crop(s) positions
			i_table_pos_[crop_spawn] = 8;
			i_table_pos_[crop_spawn1] = 8;
			i_table_pos_[user_pos] = 9;
			
		} else {
			
			//Reseting all positions to nothing to be modified has playing field
			for(int i = 1; i < 26; i ++)
			strcpy(c_table_pos_[i], "NONE");
			
			//Displays the user position and crop(s) positions
			strcpy(c_table_pos_[crop_spawn], "CROP");
			strcpy(c_table_pos_[crop_spawn1], "CROP");
			strcpy(c_table_pos_[user_pos], "YOU");
			
		}
		 
		//When crop is picked up
		if(user_pos == crop_spawn || user_pos == crop_spawn1){
			
			//randomize crop 1 position when its picked up
			if(user_pos == crop_spawn){
				
				if(dif == 1)
				crop_spawn = rand()% 9 + 1;
				
				else 
				crop_spawn = rand()% 25 + 1;
			
			//randomize crop 2 position when its picked up	
			} else {
				
				if(dif == 1)
				crop_spawn1 = rand()% 9 + 1;
				
				else
				crop_spawn1 = rand()% 25 + 1;
				
			}
			
			int crop_rand = rand()% 5 + 1;
			
			green;
			printf("Picked up a crop!\n");
			white;
			
			if(!is_tut){
				if(crop_rand == 1)
				crp_ID = Crop1_ID;
				
				else if(crop_rand == 2)
				crp_ID = Crop1_ID + 1;
				
				else if(crop_rand == 3)
				crp_ID = Crop1_ID + 2;
				
				else if(crop_rand == 4)
				crp_ID = Crop1_ID + 3;
				
				else 
				crp_ID = Crop1_ID + 4;
				
				int Quant = 1;
				int overflow = Inventory("CALC", crp_ID, Quant);
				
				if(overflow != 0){
					red;
					printf("Inventory is full!\n");
					sleep(3);
					CLR;
					break;
					white;
				}
				
			} else {
				if(crop_rand == 1)
				printf("Got a TUTORIAL_CROP_1!\n"); 
				
				else if(crop_rand == 2)
				printf("Got a TUTORIAL_CROP_2!\n");
				
				else if(crop_rand == 3)
				printf("Got a TUTORIAL_CROP_3!\n");
				
				else if(crop_rand == 4)
				printf("Got a TUTORIAL_CROP_4!\n");
				
				else 
				printf("Got a TUTORIAL_CROP_5!\n");
				
			}
		}
		
		//Random crop positions if they are in the same place so there are 2 on the screen
		if(crop_spawn == crop_spawn1){
			
			if(strcmp(dificulty, "False")== 0 || strcmp(dificulty, "Nightmare")== 0)
			crop_spawn1 = 0;
				
			else {
				
			if(dif == 1)
			crop_spawn = rand()% 9 + 1;
			
			else
			crop_spawn1 = rand()% 25 + 1;
			
			if(DEBUG_MODE){
			    printf("[DEBUG] _> Both crops in the same position\n");
			    sleep(1);
			}
			
			}
			
		} else {
			break; //Breaks out of loop when they are in diferent places
		}

		}
		
		if(show_user_turn)
		printf("Current user turn -> %d\n\n", user_turn);
		
		
		//Shows table depending on game type settings and dificulty
		if(dif == 1){
			
			if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
				
				for(int i = 1; i < 10; i ++){
					printf("[%d] ", i_table_pos_[i]);
					
					if(i % 3 == 0)
					printf("\n");
					
					if(i == 9)
					printf("\n");
				}
				
			} else {
				
				for(int i = 1; i < 10; i ++){
					printf("[%s] ", c_table_pos_[i]);
					
					if(i % 3 == 0)
					printf("\n");
					
					if(i == 9)
					printf("\n");
				}
				
			}
			
		} else {
			
			if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
				
				for(int i = 1; i < 26; i ++){
					printf("[%d] ", i_table_pos_[i]);
					
					if(i % 5 == 0)
					printf("\n");
					
					if(i == 25)
					printf("\n");
				}
				
		    } else {
				
				for(int i = 1; i < 26; i ++){
					printf("[%s] ", c_table_pos_[i]);
					
					if(i % 5 == 0)
					printf("\n");
					
					if(i == 25)
					printf("\n");
				}
				
		   }
		}
		
	}
	
	//User choose to leave so, we set all colected crops to 0 and add annother hour so its the same and so he dosent get shit
	if(is_tut){
		//Register tutorial has done
		if(display_all_tut_once){
			ChangeCurPath("OTHER.tutorials");
			FILE * ftutdisp = fopen("Crop.txt", "w");
			fclose(ftutdisp);
		}
		
		while(true){
			CLR;
			printf("Tutorial done!\n");
			printf("Again? [Y/N]\n");
		
			String_Input;
			
			if(strcmp(Input, "y")== 0){
				short int temp = 1;
				Crop(Crop1_ID, true); break;
			}	
			
			else if(strcmp(Input, "n")== 0)
			break;
			
			else 
			Error;
	
		}
		
	} else {
		TimeCalc("CALC", 0, 1, 0);
		
		if(!Leave && do_key3 && rand()% 2 + 1 == 1){
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
			
			Small_stop;
			free(hint);
			CLR;
		}
	}
}

//Fish Function
void Fish(const short int Fish1_ID, const char *what_pond, bool is_tut){

	//Note to reader: This is a backup of the "game_set" global setting, used for the display and movements in minigames table types, 
	//makes you able to alter your gameset to whatever you want without actually altering it
	char tut_game_set [5];
	strcpy(tut_game_set, game_set);
	
	bool changed_game_set = true, do_key3 = false;
	//KEY 3 ONLY
	int numb_traps_checked = 0;	
	
	//Starting Times
	int fish_hour = TimeCalc("CHECK", 0, 1, 0);
	int fish_day = TimeCalc("CHECK", 0, 0, 1);
		
	int tut_hour = fish_hour, tut_day = fish_day, tut_traps;	
	
	//Get current number of traps
	ChangeCurPath("INVENTORY");
	FILE * futility = fopen("Utility.txt", "r");
	fscanf(futility, "%d", &tut_traps);
	fclose(futility);
	
	short int trap = tut_traps;
	
	short int i_table_pos_[26];
	char c_table_pos_[26] [6];
	
	short int hour_fish_array[7] = { 0, 0, 0, 0, 0, 0, 0 };
	long int day_fish_array[7] = { 0, 0, 0, 0, 0, 0, 0 };
	
	int X, Y, L, user_pos;
	int Leave = 0, next_move, trap_limit, current_trap = 1, skip_trap, checked_trap = 0, fish_id; 
	bool inv_trap_loc = false, check_trap = false, pickup_trap = false, try_trap = false;
	
	//Tutorial Skipping stuff :>
	if(is_tut){
		if(display_all_tut_once){
			ChangeCurPath("OTHER.tutorials");
			if(access("Fish.txt", F_OK)== 0)
			return;
		}
		if(skip_tut_display)
		return;
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
		if(strcmp(hint_minigame, "Fish")== 0){
			ChangeCurPath("STORY.Locations");
			char cur_loc [50] = { '\0' };
			
			FILE * fcurloc = fopen("Current.txt", "r");
			fscanf(fcurloc, "%s\n", cur_loc);
			fclose(fcurloc);
			
			//Check if its right location
			if(strcmp(cur_loc, hint_loc)== 0)
			do_key3 = true;
		}
		
		if(do_key3){
			ChangeCurPath("OTHER");
			mkdir("temp_key3");
			ChangeCurPath("OTHER.temp_key3");
			
			//File dosent exit? Make
			if(access("TrapProg.txt", F_OK)!= 0){
				FILE * ftrapprog = fopen("TrapProg.txt", "w");
				fclose(ftrapprog);
			} else {
				FILE * ftrapprog = fopen("TrapProg.txt", "r");
				fscanf(ftrapprog, "%d\n", &numb_traps_checked);
				fclose(ftrapprog);
			}
		}
	}
	
	//register 5 trap locations for specific lake and save in "OTHER" dir
	short int trap_loc[7] = { 0, 0, 0, 0, 0, 0, 0 };
	
	//calculate the final time that trap can be claimed so it has fish
	short int final_fish_hour_array[7] = { 0, 0, 0, 0, 0, 0, 0 };
	
	//register what fish the user knows and what trap it is from
	short int fish_inside_trap_array [7] = { 0, 0, 0, 0, 0, 0, 0 };
	
	if(strcmp(dificulty, "Lucid")== 0)
	trap_limit = 5;
	
	else if(strcmp(dificulty, "False")== 0)
	trap_limit = 3;
	
	else if(strcmp(dificulty, "Vivid")== 0)
	trap_limit = 2;
	
	else
	trap_limit = 1;
	
	//Check for "Fishing permit"
	bool temp;
	ChangeCurPath("INVENTORY");
	FILE * fother = fopen("Special.txt", "r");
	fscanf(fother, "%d", &temp);
	fclose(fother);
	
	if(temp)
	trap_limit ++;
	
	if(DEBUG_MODE)
	printf("[DEBUG] _> Trap Limit? %d\n", trap_limit);
	
	ChangeCurPath("OTHER");
	
	//Checking if the normal path has alr been made b4
	char fish_path [MAX_PATH];
	getcwd(fish_path, MAX_PATH);
	strcat(fish_path, "\\positions\\Fish\\");
	strcat(fish_path, what_pond);
	
	ChangeCurPath("OTHER.positions");
	
	//Dosent exist? Make it.
	if(ExistDiret(fish_path)== false){
		mkdir("Fish");
		ChangeCurPath("OTHER.positions.Fish");
		
		for(int i = 1; i < 9; i ++){
			char fish_dir [2] = "0";
			fish_dir[0] = i + '0'; 
			mkdir(fish_dir);
		}
	}
	
	ChangeCurPath("OTHER.positions.Fish");
	CatCurPath(what_pond);
	
	//Check if the files exist
	if(access("Fishpos.txt", F_OK)== 0){
		//Git trap pos
		FILE * ffish_pos = fopen("Fishpos.txt", "r");
		for(int i = 1; i < 7; i ++)
		fscanf(ffish_pos, "%d\n", &trap_loc[i]);
		fclose(ffish_pos);
		
		//Git fish inside trap
		FILE * ffish_trap = fopen("Fishtrap.txt", "r");
		for(int i = 1; i < 7; i ++)
		fscanf(ffish_trap, "%d\n", &fish_inside_trap_array[i]);
		fclose(ffish_trap);
		
		//Git hour that the trap was last interacted with
		FILE * ffish_hour = fopen("Fishhour.txt", "r");
		for(int i = 1; i < 7; i ++)
		fscanf(ffish_hour, "%d\n", &hour_fish_array[i]);
		fclose(ffish_hour);
		
		//Git day that the trap was last interacted with
		FILE * ffish_day = fopen("Fishday.txt", "r");
		for(int i = 1; i < 7; i ++)
		fscanf(ffish_day, "%d\n", &day_fish_array[i]);
		fclose(ffish_day);
		
		//Git the final hour estimated for the trap to be ready
		FILE * ffish_final_hour = fopen("Fishfinalhour.txt", "r");
		for(int i = 1; i < 7; i ++)
		fscanf(ffish_final_hour, "%d\n", &final_fish_hour_array[i]);
		fclose(ffish_final_hour);
	}
	printf("Starting Grid:\n");
	
	//Shows starting table
	if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
		printf("[0] [0] [0] [0] [0]\n");
	    printf("[0] [0] [1] [0] [0]\n");
	    printf("[0] [2] [9] [3] [0]\n");
		printf("[0] [0] [4] [0] [0]\n");
		printf("[0] [0] [0] [0] [0]\n");
	} else {
		printf("[NONE] [NONE] [NONE] [NONE] [NONE]\n");
		printf("[NONE] [NONE] [UP] [NONE] [NONE]\n");
		printf("[NONE] [LEFT] [YOU] [RIGHT] [NONE]\n");
		printf("[NONE] [NONE] [DOWN] [NONE] [NONE]\n");
		printf("[NONE] [NONE] [NONE] [NONE] [NONE]\n");
	}
		
	X = 3, Y = 3;
	
	while(true){
		
		if(changed_game_set && is_tut){
			changed_game_set = false;
			
			if(strcmp(tut_game_set, "Int")== 0 && is_tut){
				printf("Listen up, this is important\n");
				printf("Type 1 to go Up a Square, 2 to go left, 3 to go right and 4 to go down\n");
				printf("Type 9 to leave WITHOUT collect matherials and 0 to stay in the same spot\n");
				printf("Type 8 to switch \"game_set\" types, aka if you are playing with \"INT\" it switches to \"CHAR\" and vice versa (tutorial only command)\n\n");
				
				printf("Type 5 to place down a trap, 6 to check a trap and 7 to remove a trap\n");
				printf("Also type 10 to move a few hours in the future so you can have the fish in the trap (tutorial only command)\n\n");
				
				printf("[(Important) EXTRA INFO] - Small note to keep in mind\n");
				printf("Your save file will store the positions of the traps in all diferent ponds, so you can move them around has you wish and when you come back they will stay in the same spot\n\n");
				
				printf("Might has well mention the objetive here is to place down traps and wait, the traps do their jobs on collecting fish, all you need to do is come back a few hours after you place them down\n");
				printf("Also also when you are done with placing down traps you might has well just leave, staying there wont do anything\n");
				printf("Understood? You better...\n\n");
			} else {
				printf("Listen up, this is important\n");
				printf("Type \"Up\" to go Up a Square, \"Left\" to go left, \"Right\" to go right and \"Down\" to go down\n");
				printf("Type \"Leave\" or \"Back\" to leave WITHOUT collect matherials and \"stay\" to stay in the same spot\n");
				printf("Type \"Game\" to switch \"game_set\" types, aka if you are playing with \"INT\" it switches to \"CHAR\" and vice versa (tutorial only command)\n\n");
				
				printf("Type \"Trap\" to place down a trap, \"Check\" to check a trap and \"Pick\" to remove a trap\n");
				printf("Also type \"Hour\" to move a few hours in the future so you can have the fish in the trap (tutorial only command)\n\n");
				
				printf("[(Important) EXTRA INFO] - Small note to keep in mind\n");
				printf("Your save file will store the positions of the traps in all diferent ponds, so you can move them around has you wish and when you come back they will stay in the same spot\n\n");
				
				printf("Might has well mention the objetive here is to place down traps and wait, the traps do their jobs on collecting fish, all you need to do is come back a few hours after you place them down\n");
				printf("Also also when you are done with placing down traps you might has well just leave, staying there wont do anything\n");
				printf("Understood? You better...\n\n");
			}
			
			Small_stop;
		}
		
		if(DEBUG_MODE){
		    printf("\n[DEBUG] _> ALL hour values? (Trap num): 1 - > %d / 2 - > %d / 3 - > %d / 4 - > %d / 5 - > %d / 6- > %d\n", hour_fish_array[1], hour_fish_array[2], hour_fish_array[3], hour_fish_array[4], hour_fish_array[5], hour_fish_array[6]);
		    printf("[DEBUG] _> ALL day values? (Trap num): 1 - > %d / 2 - > %d / 3 - > %d / 4 - > %d / 5 - > %d / 6- > %d\n", day_fish_array[1], day_fish_array[2], day_fish_array[3], day_fish_array[4], day_fish_array[5], day_fish_array[6]);
		    printf("[DEBUG] _> ALL trap locations? (Trap num): 1 - > %d / 2 - > %d / 3 - > %d / 4 - > %d / 5 - > %d / 6- > %d\n", trap_loc[1], trap_loc[2], trap_loc[3], trap_loc[4], trap_loc[5], trap_loc[6]);
		}
		
		printf("Next move?\n");
			
			if((strcmp(game_set, "Char")== 0 && !is_tut) || (strcmp(tut_game_set, "Char")== 0 && is_tut)){
			String_Input;
			
				//Movements
				if(strcmp(Input, "up")== 0)
				Y -= 1;
					
				else if(strcmp(Input, "left")== 0)
				X -= 1;	
				
				else if(strcmp(Input, "right")== 0)
				X += 1;
					
				else if(strcmp(Input, "down")== 0)
				Y += 1;	
					
				else if(strcmp(Input, "trap")== 0)
				//Tries to place down a trap in current user position
				try_trap = true;
				
				else if(strcmp(Input, "check")== 0)
				//Checks the trap
				check_trap = true;
				
				else if(strcmp(Input, "pick")== 0)
				//Picks up the trap
				pickup_trap = true;
				
				else if(strcmp(Input, "stay")== 0){ }
				
				else if(strcmp(Input, "game")== 0 && is_tut){
					changed_game_set = true;
					
					if((strcmp(tut_game_set, "Int")== 0 && is_tut))
					strcpy(tut_game_set, "Char");
					
					else
					strcpy(tut_game_set, "Int");
					
					green;
					printf("Changed game type!\n");
					white;
					
				} else if(strcmp(Input, "hour")== 0 && is_tut)
				tut_hour += 15;
					
				else if(strcmp(Input, "leave")== 0 || strcmp(Input, "back")== 0){
				Leave = 1; break;
					
				} else { Error; }
				
			} else {
				
				//Also using "string_Input" cause if the user mistaked it for a char input it would bug out but with this nothing happends so the user is safe
				String_Input;
				
				//Int movements
				if(strcmp(Input, "1")== 0)
				Y -= 1;
				
				else if(strcmp(Input, "2")== 0)
				X -= 1;
				
				else if(strcmp(Input, "3")== 0)
				X += 1;
				
				else if(strcmp(Input, "4")== 0)
				Y += 1;
				
				else if(strcmp(Input, "5")== 0)
				//Tries to place down a trap in current user position
				try_trap = true;
				
				else if(strcmp(Input, "6")== 0)
				//Checks the trap
				check_trap = true;
				
				else if(strcmp(Input, "7")== 0)
				//Picks up the trap
				pickup_trap = true;
				
				else if(strcmp(Input, "0")== 0){ }
				
				else if(strcmp(Input, "8")== 0 && is_tut){
					changed_game_set = true;
					
					if((strcmp(tut_game_set, "Int")== 0 && is_tut))
					strcpy(tut_game_set, "Char");
					
					else
					strcpy(tut_game_set, "Int");
					
					green;
					printf("Changed game type!\n");
					white;
					
				} else if(strcmp(Input, "10")== 0 && is_tut)
				tut_hour += 15;

				else if(strcmp(Input, "9")== 0){

				Leave = 1; break;
				
				} else { Error; }
				
			}
			
			//For tutorial calculations
			if(tut_hour >= 24 && is_tut){
				tut_hour -= 24;
				tut_day ++;
			}
			
			if (X >= 6){ printf("Outside playing field\n"); sleep(1); X = 5; CLR; }
			else if (Y >= 6){ printf("Outside playing field\n"); sleep(1); Y = 5; CLR; }
			else if (X <= 0){ printf("Outside playing field\n"); sleep(1); X = 1; CLR; }
			else if (Y <= 0){ printf("Outside playing field\n"); sleep(1); Y = 1; CLR; }
				
			//Calculate L with this simple formula
			L = (Y * 5) - 5;
				
			//Calculating table position
			user_pos = X + L;
			
			if(DEBUG_MODE)
			printf("[DEBUG] _> User X? %d / Y? %d / L? %d / Pos? %d\n", X, Y, L, user_pos);
			
			if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
				
				//Reseting all positions to nothing to be modified has playing field
				memset(i_table_pos_, 0, sizeof(i_table_pos_));
				
				//Displays the user position and current trap positions
				i_table_pos_[user_pos] = 9;
				
				for(int i = 1; i < 7; i ++)
				i_table_pos_[trap_loc[i]] = 8;
				
			} else {
				
				//Reseting all positions to nothing to be modified has playing field
				for(int i = 0; i < 27; i ++)
				strcpy(c_table_pos_[i], "NONE");
				
				//Displays the user position
				strcpy(c_table_pos_[user_pos], "YOU");
				
				//Displays trap position(s)
				for(int i = 1; i < 7; i ++)
				strcpy(c_table_pos_[trap_loc[i]], "TRAP");
				
			}
			
			//Trap placement stuff
			if(try_trap){
				try_trap = false;
				
				if(current_trap > trap_limit || current_trap == -1 || trap == 0){
					//Change color to red
					red;
					
					if(current_trap > trap_limit || current_trap == -1)
					printf("Trap limit reached, leave or check other traps\n");
					
					else
					printf("You dont have traps in your inventory to place!\n");
					
					//Change color to white
					white;
				} else {
				
				trap_loc[current_trap] = user_pos;
				
				switch (current_trap){
					case 1:
						skip_trap = 1;
						break;
						
					case 2:
						skip_trap = 2;
						break;
						
					case 3:
						skip_trap = 3;
						break;
						
					case 4:
						skip_trap = 4;
						break;
						
					case 5:
						skip_trap = 5;
						break;
						
					case 6:
						skip_trap = 6;
						break;
						
					default:
						break;
						
				}
				
				if(DEBUG_MODE)
				printf("[DEBUG] _> Skip trap? %d\n", skip_trap);
				
				//Repeating this code 5 more times to see if the spot the user wants to place his trap on doesnt have anything in there
				//Also informing debug mode if it passed the check or if it skippped it
				if(skip_trap != 1){
					
					if((trap_loc[current_trap] != trap_loc[1]) && inv_trap_loc != true){
						if(DEBUG_MODE)
						printf("[DEBUG] _> PASSED TRAP 1 CHECK\n");
						 
						
					} else
					inv_trap_loc = true;
					
				} else {
					if(DEBUG_MODE)
					printf("[DEBUG] _> SKIPED TRAP 1 CHECK\n");
					
				}
				
				if(skip_trap != 2){
					
					if((trap_loc[current_trap] != trap_loc[2]) && inv_trap_loc != true){
						if(DEBUG_MODE)
						printf("[DEBUG] _> PASSED TRAP 2 CHECK\n");
						
					} else
					inv_trap_loc = true;
					
				} else {
					if(DEBUG_MODE)
					printf("[DEBUG] _> SKIPED TRAP 2 CHECK\n");
					
				}
				
				if(skip_trap != 3){
					
					if((trap_loc[current_trap] != trap_loc[3])&& inv_trap_loc != true){
						if(DEBUG_MODE)
						printf("[DEBUG] _> PASSED TRAP 3 CHECK\n");
						
					} else
					inv_trap_loc = true;
					
				} else {
					if(DEBUG_MODE)
					printf("[DEBUG] _> SKIPED TRAP 3 CHECK\n");
					
				}
				
				if(skip_trap != 4){
					
					if((trap_loc[current_trap] != trap_loc[4])&& inv_trap_loc != true){
						if(DEBUG_MODE)
						printf("[DEBUG] _> PASSED TRAP 4 CHECK\n");
						
					} else
					inv_trap_loc = true;
					
				} else {
					if(DEBUG_MODE)
					printf("[DEBUG] _> SKIPED TRAP 4 CHECK\n");
					
				}
				
				if(skip_trap != 5){
					
					if((trap_loc[current_trap] != trap_loc[5]) && inv_trap_loc != true){
						if(DEBUG_MODE)
						printf("[DEBUG] _> PASSED TRAP 5 CHECK\n");
						
					} else
					inv_trap_loc = true;
					
				} else {
					if(DEBUG_MODE)
					printf("[DEBUG] _> SKIPED TRAP 5 CHECK\n");
					
				}
				
				if(skip_trap != 6){
					
					if((trap_loc[current_trap] != trap_loc[6]) && inv_trap_loc != true){
						if(DEBUG_MODE)
						printf("[DEBUG] _> PASSED TRAP 6 CHECK\n");
						
					} else
					inv_trap_loc = true;
					
				} else {
					if(DEBUG_MODE)
					printf("[DEBUG] _> SKIPED TRAP 6 CHECK\n");
					
				}
				
				if(!inv_trap_loc && (trap > 0 || tut_traps > 0)){ 
					//takes a trap away
					if(!is_tut)
					trap --;
					
					else
					tut_traps --;
					//Registers hour and day trap has been placed
					hour_fish_array[current_trap] = fish_hour;
					day_fish_array[current_trap] = fish_day;
					//Calculates hour for next time user checks THAT trap
					final_fish_hour_array[current_trap] = fish_hour + 15;
					if(DEBUG_MODE){
					    printf("[DEBUG] _> Hour fish array? %d\n", hour_fish_array[current_trap]);
					    printf("[DEBUG] _> Final fish array? %d [above 24 is considered null]\n", final_fish_hour_array[current_trap]);
					    printf("[DEBUG] _> Day fish array? %d\n", day_fish_array[current_trap]);
					}
					
				} else if(inv_trap_loc){
					inv_trap_loc = false;
					//Set back trap location to 0 AKA void
					trap_loc[current_trap] = 0;
					//Change color to red
					red;
					printf("You cant place your trap there!\n");
					//Change color back to white
					white;
				} else if(trap == 0 || tut_traps == 0){
					//Set back trap location to 0 AKA void
					trap_loc[current_trap] = 0;
					red;
					printf("Ran out of traps!\n");
					white;
				}
				
			}
			
			}
			
			//Code to let the program know what trap we want it to sellect
			if(check_trap || pickup_trap){
				
				checked_trap = 0;
				
				//What trap is being checked?
				if(user_pos == trap_loc[1])
				checked_trap = 1;
				
				else if(user_pos == trap_loc[2])
				checked_trap = 2;
				
				else if(user_pos == trap_loc[3])
				checked_trap = 3;
				
				else if(user_pos == trap_loc[4])
				checked_trap = 4;
				
				else if(user_pos == trap_loc[5])
				checked_trap = 5;
				
				else if(user_pos == trap_loc[6])
				checked_trap = 6;
				
				else {
				red;
				printf("You cannot check / remove your trap since you are not standing in a trap.\n");
				white;
				}
				
				if(DEBUG_MODE)
				printf("[DEBUG] _> Checked trap? %d\n", checked_trap);
				
			}
			
			if(check_trap){
				
				check_trap = false;
				bool collect_fish = false;
				
				if(checked_trap != 0){
				
					if(!is_tut){
						//Check if its the same day or annother day
						if(day_fish_array[checked_trap] == fish_day){
							
							if(DEBUG_MODE){
						    	printf("[DEBUG] _> Hour fish array? %d\n", hour_fish_array[checked_trap]);
						    	printf("[DEBUG] _> Final fish hour array? %d\n", final_fish_hour_array[checked_trap]);
							}
							
							//Check if 15 hours have passed since trap was placed down
							if(fish_hour >= final_fish_hour_array[checked_trap]){
								final_fish_hour_array[checked_trap] = 32767; //Invalid so user cant get infinite fish [also its the max int for a short :>]
								//Flipping value to true
								collect_fish = true;
							} else {
								collect_fish = false;
								red;
								printf("Not enough time has passed for this trap to catch any fish\n");
								white;
							}
						} else {
						final_fish_hour_array[current_trap] = fish_hour + 15;
						
						if(DEBUG_MODE)
						printf("[DEBUG] _> Final fish hour array? %d\n\n", final_fish_hour_array[current_trap]);
						
						//Flipping value to true
						collect_fish = true;
						}
					
					//Same thing has above but tutorial times instead
					} else {
						if(day_fish_array[checked_trap] == tut_day){
							
							if(DEBUG_MODE){
						    	printf("[DEBUG] _> Hour fish array? %d\n", hour_fish_array[checked_trap]);
						    	printf("[DEBUG] _> Final fish hour array? %d\n", final_fish_hour_array[checked_trap]);
							}
							
							if(tut_hour >= final_fish_hour_array[checked_trap]){
								final_fish_hour_array[checked_trap] = 32767; 
								collect_fish = true;
							} else {
								collect_fish = false;
								red;
								printf("Not enough time has passed for this trap to catch any fish\n");
								white;
							}
						} else {
						final_fish_hour_array[current_trap] = tut_hour + 15;
						
						if(DEBUG_MODE)
						printf("[DEBUG] _> Final fish hour array? %d\n\n", final_fish_hour_array[current_trap]);
						
						collect_fish = true;
						}
					}
				
				}
				
				if(DEBUG_MODE)
				printf("[DEBUG] _> COLLECT FISH VALUE? %d\n", collect_fish);
				
				
				//Randomize fish that he got
				if(collect_fish){
					
					//Key 3 safety check :>
					if(do_key3)
					numb_traps_checked ++;
					
					short int funny_array [7] = { 0, 0, 0, 0, 0, 0, 0 }; //this array purelly exists for 1 line of code
					
					collect_fish = false;
					bool rarity_pass = false;
					
					//checking THAT trap variable is made to prevent rand from reroling if user put the fish there in stash alr
					bool checking_THAT_trap = false;
					
					//Traps ALWAYS drop 1 fish so i set quantity to 1 for the later inventory "CALC" call
					int quant = 1;
					
					short int fish2_rand = 0; //declaring here so the stash dosent fuck up
					short int fish1_rand = 0; //declaring here so the program dosent have a stroke
					
					//since memcmp cant take constants i just make a new array all filed up with 0s and made them compare
					//if no fish is known the for loop dosent need to be executed :>
					
					if(memcmp(fish_inside_trap_array, funny_array, sizeof(fish_inside_trap_array))!= 0){
					
					if(DEBUG_MODE)
					printf("[DEBUG] _> Fish inside trap array is all 0 and loop has been executed!\n");
					
					
					for(int i = 0; i < 7; i++){
						
					if(fish_inside_trap_array[i] != 0){
						
					if(i == checked_trap){
					//hit! aka the trap user is trying to check again has a fish the user TRIED to claim!
					checking_THAT_trap = true;
					break;
					}
					
					} else {
					//no hit [L]
					checking_THAT_trap = false;
					}
					
					}
					
					}
					
					
					if(!checking_THAT_trap)
					fish1_rand = rand()% 6 + 1;
					
					else {
						if(DEBUG_MODE)
						printf("[DEBUG] _> User is checking THAT trap!\n");
						
						fish1_rand = fish_inside_trap_array[checked_trap];	
					}
					
										
					yellow;
					
					if(!is_tut){
					short int special_got = 0; 
					//Rarity 1
					switch(fish1_rand){
						case 1:
							//Randomize bettewn treasure
							special_got = rand()% 100 + 1;
							if(special_got >= 1 && special_got <= 10){
								printf("You got ... Nothing!\n");
								fish_id = 0;
							
							} else if(special_got >= 11 && special_got <= 20){
								printf("You got an Algae?\n");
								fish_id = 127;
							
							} else if(special_got >= 21 && special_got <= 25){
								printf("You got a Japanese Iris! How pretty!\n");
								fish_id = 128;
								
							} else if(special_got >= 26 && special_got <= 40){
								printf("You got ... some old boots...Amazing!!!\n");
								fish_id = 0;
								
							} else if(special_got >= 41 && special_got <= 50){
								printf("You got a Water Lily! Floats like a boat!\n");
								fish_id = 129;
								
							} else if(special_got >= 51 && special_got <= 60){
								printf("You captured a water snail!\n");
								fish_id = 130;
								
							} else if(special_got >= 61 && special_got <= 75){
								printf("Just the remains of a fish, nothing much.\n");
								fish_id = 0;
								
							} else if(special_got >= 76 && special_got <= 80){
								printf("You got a Mediterranean Tree Frog! Croak?\n");
								fish_id = 131;
								
							} else if(special_got >= 81 && special_got <= 85){
								printf("You got a Iberian Water Frog! Ribbit?\n");
								fish_id = 132;
								
							} else if(special_got >= 86 && special_got <= 99){
								printf("You got a Giant Freshwater Prawn (Shrimp)! Watch out for the big claws!\n");
								fish_id = 133;
								
							} else {
								printf("You got a Gold Fish!? Lucky you.\n");
								fish_id = 134;
								
							}
							
							break;
						
						case 2:
							rarity_pass = true;
							break;
							
						case 3:
							printf("You got a Commun Fish!\n");
							fish_id = Fish1_ID;
							break;
						
						case 4:
							printf("You got a Commun Fish!\n");
							fish_id = Fish1_ID + 1;
							break;
							
						case 5:
							printf("You got a Commun Fish!\n");
							fish_id = Fish1_ID + 2;
							break;
						
						case 6:
							printf("You got a Commun Fish!\n");
							fish_id = Fish1_ID + 3;
							break;
							
							
						case 11:
							printf("You got a Rare Fish!\n");
							fish_id = Fish1_ID + 4;
							break;
								
						case 12:
							printf("You got a Rare Fish!\n");
							fish_id = Fish1_ID + 5;
							break;
							
						default:
							printf("[SYSTEM] _> INTERNAL ISSUE LOADING FISH CATCHED\n");
							break;
					}
					
					//Rarity 2
					if(rarity_pass){
						fish2_rand = rand()% 2 + 1;
						rarity_pass = false;
						
						switch(fish2_rand){
							case 1:
								printf("You got a Rare Fish!\n");
								fish_id = Fish1_ID + 4;
								
								fish1_rand = 11;
								break;
								
							case 2:
								printf("You got a Rare Fish!\n");
								fish_id = Fish1_ID + 5;
								
								fish1_rand = 12;
								break;
								
							default:
								printf("[SYSTEM] _> INTERNAL ISSUE LOADING FISH CATCHED\n");
								break;
								
						}
						
					}
					
					int quant = 1;
					int overflow_val = Inventory("CALC", fish_id, quant);
					
					//Stash management
					if(overflow_val != 0){ 
						
						white;
						
						while(true){
						printf("You didnt have enough inventory space for this fish\n");
						printf("What should we do to the fish?\n");
						printf(">Let it go [Go]\n");
						printf(">Keep it in the trap for later [Keep]\n");
						
						String_Input;
						
						if(strcmp(Input, "go")== 0){
							
							//(the fish dies btw) (jk)
							printf("You let go of the fish\n");
							
							//re-registers the normal trap stuff :>
							hour_fish_array[checked_trap] = fish_hour;
							day_fish_array[checked_trap] = fish_day;
							final_fish_hour_array[checked_trap] = fish_hour + 15;
							
							if(checking_THAT_trap)
							fish_inside_trap_array[checked_trap] = 0;
							
							break;
							
						} else if(strcmp(Input, "keep")== 0){
							
							if(fish1_rand == 1){
							printf("Why are you keeping nothing in the trap?\n");
							printf("Dumbo.\n");
							printf("[SYSTEM] _> Trap %d has no items.\n", checked_trap);
							}
							
							else
							printf("You keep the fish in the trap\n");
							
							//set so user can claim THIS trap whenever he wants
							final_fish_hour_array[checked_trap] = -100;
							
							fish_inside_trap_array[checked_trap] = fish1_rand;
							
							if(DEBUG_MODE)
							printf("[DEBUG] _> Fish inside trap array? %d [Contains the rand id]\n", fish_inside_trap_array[checked_trap]);
							
							
							break;
								
						} else { Error; }
						
						}
						
						Small_stop;
					}
				
				} else {
					switch(fish1_rand){
						case 1:
							printf("Got a TUTORIAL_NOTHING!\n");
							break;
						
						case 2:
							rarity_pass = true;
							break;
							
						case 3:
							printf("Got a TUTORIAL_FISH_RARITY_1_1!\n");
							break;
						
						case 4:
							printf("Got a TUTORIAL_FISH_RARITY_1_2!\n");
							break;
							
						case 5:
							printf("Got a TUTORIAL_FISH_RARITY_1_3!\n");
							break;
						
						case 6:
							printf("Got a TUTORIAL_FISH_RARITY_1_4!\n");
							break;
							
							
						case 11:
							printf("Got a TUTORIAL_FISH_RARITY_1_5!\n");
							break;
								
						case 12:
							printf("Got a TUTORIAL_FISH_RARITY_1_6!\n");
							break;
							
						default:
							printf("[SYSTEM] _> INTERNAL ISSUE LOADING FISH CATCHED\n");
							break;
					}
					
					if(rarity_pass){
						fish2_rand = rand()% 2 + 1;
						rarity_pass = false;
						
						switch(fish2_rand){
							case 1:
								printf("Got a TUTORIAL_FISH_RARITY_2_1!\n");
								
								fish1_rand = 11;
								break;
								
							case 2:
								printf("Got a TUTORIAL_FISH_RARITY_2_2!\n");
								
								fish1_rand = 12;
								break;
								
							default:
								printf("[SYSTEM] _> INTERNAL ISSUE LOADING FISH CATCHED\n");
								break;
								
						}
						
					}
				}
				
				}
				
			}
			
			white;
			
			if(pickup_trap){
				
				pickup_trap = false;
				
				if(checked_trap != 0){
					trap_loc[checked_trap] = 0;
					hour_fish_array[checked_trap] = 0;
					day_fish_array[checked_trap] = 0;
					
					if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut))
					i_table_pos_[user_pos] = 9;
					
					else
					strcpy(c_table_pos_[user_pos], "YOU");
					
					printf("Removed trap %d!\n", checked_trap);
					
					//gives trap back
					if(!is_tut)
					trap ++;
					
					else
					tut_traps ++;
				}
				
			}
			
			//Check what is the current trap by seeing if the loc on each trap is 0 aka non existent
			if(trap_loc[1] == 0)
			current_trap = 1; 
			
			else if(trap_loc[2] == 0)
			current_trap = 2;
			
			else if(trap_loc[3] == 0)
			current_trap = 3;
			
			else if(trap_loc[4] == 0)
			current_trap = 4;
			
			else if(trap_loc[5] == 0)
			current_trap = 5;
			
			else if(trap_loc[6] == 0)
			current_trap = 6;
			
			else
			current_trap = -1;
			
		if(DEBUG_MODE)
		printf("[DEBUG] _> Current trap? %d\n\n", current_trap);
		
		if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
			
			for(int i = 1; i < 26; i ++){
				printf("[%d] ", i_table_pos_[i]);
				
				if(i % 5 == 0)
				printf("\n");
				
				if(i == 25)
				printf("\n");
			}
			
	    } else {
			
			for(int i = 1; i < 26; i ++){
				printf("[%s] ", c_table_pos_[i]);
				
				if(i % 5 == 0)
				printf("\n");
				
				if(i == 25)
				printf("\n");
			}
			
	   }
		
	}
	
	if(!is_tut){
		TimeCalc("CALC", 0, 1, 0);
		
		ChangeCurPath("OTHER");
		ChangeCurPath("OTHER.positions.Fish");
		CatCurPath(what_pond);
		
		//Register trap pos
		FILE * ffish_pos = fopen("Fishpos.txt", "w");
		for(int i = 1; i < 7; i ++)
		fprintf(ffish_pos, "%d\n", trap_loc[i]);
		fclose(ffish_pos);
		
		//Register fish inside trap
		FILE * ffish_trap = fopen("Fishtrap.txt", "w");
		for(int i = 1; i < 7; i ++)
		fprintf(ffish_trap, "%d\n", fish_inside_trap_array[i]);
		fclose(ffish_trap);
		
		//Register hour that the trap was last interacted with
		FILE * ffish_hour = fopen("Fishhour.txt", "w");
		for(int i = 1; i < 7; i ++)
		fprintf(ffish_hour, "%d\n", hour_fish_array[i]);
		fclose(ffish_hour);
		
		//Register day that the trap was last interacted with
		FILE * ffish_day = fopen("Fishday.txt", "w");
		for(int i = 1; i < 7; i ++)
		fprintf(ffish_day, "%d\n", day_fish_array[i]);
		fclose(ffish_day);
		
		//Register the final hour estimated for the trap to be ready
		FILE * ffish_final_hour = fopen("Fishfinalhour.txt", "w");
		for(int i = 1; i < 7; i ++)
		fprintf(ffish_final_hour, "%d\n", final_fish_hour_array[i]);
		fclose(ffish_final_hour);
		
		if(do_key3){
			ChangeCurPath("OTHER.temp_key3");
			FILE * ftrapprog = fopen("TrapProg.txt", "w");
			fprintf(ftrapprog, "%d\n", numb_traps_checked);
			fclose(ftrapprog);
		}
		
		//Key 3 checks stuff
		if(numb_traps_checked >= 3 && do_key3 && rand()% 2 + 1 == 1){
			
			//Delete temp dir
			ChangeCurPath("OTHER");
			system("rmdir /s /q temp_key3");
			
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
			
			Small_stop;
			free(hint);
			CLR;
		}
		
	} else {
		//Register tutorial has done
		if(display_all_tut_once){
			ChangeCurPath("OTHER.tutorials");
			FILE * ftutdisp = fopen("Fish.txt", "w");
			fclose(ftutdisp);
		}
		
		while(true){
		
			CLR;
			printf("Tutorial done!\n");
			printf("Again? [Y/N]\n");
					
			String_Input;
					
			if(strcmp(Input, "y")== 0){
				short int temp = 0;
				Fish(temp, "1", true); break;
			}	
					
			else if(strcmp(Input, "n")== 0)
			break;
					
			else 
			Error;
		
		}
	}
}

//Tree Fucntion
void Tree(bool is_invasive, const char *num_spot, const short int Log1_ID, const short int special_tree_ID, bool is_tut){	

	//Note to reader: This is a backup of the "game_set" global setting, used for the display and movements in minigames table types, 
	//makes you able to alter your gameset to whatever you want without actually altering it
	char tut_game_set [5];
	strcpy(tut_game_set, game_set);
	
	bool changed_game_set = true, do_key3 = false;

	//Key 3 only
	int number_trees_choped_down = 0;

	//Note to reader: This function is a little bit of a mess (Talking about the tree detection system)
	
	//Starting Times
	int tree_day = TimeCalc("CHECK", 0, 0, 1);
	
	//set vars
	bool Leave = false, diferent_day = false;
	
	long int day_tree = -5;
	short int i_table_pos_[50];
	char c_table_pos_[50] [10];
	
	short int X, Y, L, user_pos, bckp_bckp_pos = 0, stored_move, num_trees_next_to_user = 0;
	short int num_trees, axes_needed, num_trees_chopped, stump_axes_needed;
	int tree_ID, tree_quant;
	
	bool Chop = false, Collect = false, near_tree = false, near_log = false;
	
	//Tutorial Skipping stuff :>
	if(is_tut){
		if(display_all_tut_once){
			ChangeCurPath("OTHER.tutorials");
			if(access("Tree.txt", F_OK)== 0)
			return;
		}
		if(skip_tut_display)
		return;
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
		if(strcmp(hint_minigame, "Tree")== 0){
			ChangeCurPath("STORY.Locations");
			char cur_loc [50] = { '\0' };
			
			FILE * fcurloc = fopen("Current.txt", "r");
			fscanf(fcurloc, "%s\n", cur_loc);
			fclose(fcurloc);
			
			//Check if its right location
			if(strcmp(cur_loc, hint_loc)== 0)
			do_key3 = true;
		}
		
		if(do_key3){
			ChangeCurPath("OTHER");
			mkdir("temp_key3");
			ChangeCurPath("OTHER.temp_key3");
			
			//File dosent exit? Make
			if(access("TreeProg.txt", F_OK)!= 0){
				FILE * ftreeprog = fopen("TreeProg.txt", "w");
				fclose(ftreeprog);
			} else {
				FILE * ftreeprog = fopen("TreeProg.txt", "r");
				fscanf(ftreeprog, "%d\n", &number_trees_choped_down);
				fclose(ftreeprog);
			}
		}
	}
	
	//Set constant values [Altering these values may cause unexpected glitches]
	if(strcmp(dificulty, "Lucid")== 0){
		
		num_trees = 4;
		axes_needed = 2;
		stump_axes_needed = 5;
		
	} else if(strcmp(dificulty, "False")== 0){
		
		num_trees = 3;
		axes_needed = 3;
		stump_axes_needed = 7;
		
	} else if(strcmp(dificulty, "Vivid")== 0){
		
		num_trees = 2;
		axes_needed = 5;
		stump_axes_needed = 10;
		
	} else {
		
		num_trees = 1;
		axes_needed = 6;
		stump_axes_needed = 13;
		
	}
	
	//Invasive trees are weak
	if(is_invasive)
	stump_axes_needed -= 3;
	
	//Set up array that knows the positions alr done AND annother one to be the posible moves to a tree [assistance array]
	char arr_alr_done_tree_pos[4];
	memset(arr_alr_done_tree_pos, ' ', sizeof(arr_alr_done_tree_pos));
	
	short int assist_arr[4] = { -7, -1, 1, 7 };
	
	//Depending on the tree, set the number of chops alr done AND set the location of the trees AND set status
	short int axes_done[num_trees + 1];
	memset(axes_done, 0, sizeof(axes_done));
	short int stump_axes_done[num_trees + 1];
	memset(stump_axes_done, 0, sizeof(stump_axes_done));
	short int tree_location[num_trees + 1];
	memset(tree_location, 0, sizeof(tree_location));
	bool is_tree_down[num_trees + 1];
	memset(is_tree_down, 0, sizeof(is_tree_down));
	
	//2d array(s) for the position of the logs and to know if its stick or not
	short int log_pos[num_trees + 1] [5];
	memset(log_pos, 0, sizeof(log_pos));
	bool is_stick[num_trees + 1] [5];
	memset(is_stick, 0, sizeof(is_stick));
	
	//Setting up some invalid variabes
	axes_done[0] = -55;
	stump_axes_done[0] = -55;
	tree_location[0] = -55;
	tree_location[0] = -55;
	log_pos[0][0] = -55;
	is_tree_down[0] = false;
	
	//Loop to choose random tree positions for how many trees there r
	for(int i = 1; i < num_trees + 1; i ++){
		//Choose random tree position
		short int tree_pos_chosen = rand()% 49 + 1;
		
		//Tree cannot spawn in the same place has user and its not in other trees place
		if(memchr(tree_location, tree_pos_chosen, sizeof(tree_location))!= NULL || tree_pos_chosen == 25)
		i --;
		
		else
		tree_location[i] = tree_pos_chosen;
		
		if(DEBUG_MODE)
		printf("[DEBUG] _> tree_location[%d]? %d\n", i, tree_location[i]);
		
	}
	
	ChangeCurPath("OTHER");
	
	//Checking if the normal path has alr been made b4
	char tree_path [MAX_PATH];
	getcwd(tree_path, MAX_PATH);
	strcat(tree_path, "\\positions\\Tree\\");
	strcat(tree_path, num_spot);
	
	ChangeCurPath("OTHER.positions");
	
	//Dosent exist? Make it.
	if(ExistDiret(tree_path)== false){
		mkdir("Tree");
		ChangeCurPath("OTHER.positions.Tree");
		
		for(int i = 1; i < 10; i ++){
			char tree_dir [2] = "0";
			tree_dir[0] = i + '0'; 
			mkdir(tree_dir);
		}
	}
	
	ChangeCurPath("OTHER.positions.Tree");
	CatCurPath(num_spot);
	
	if(access("Treepos.txt", F_OK)== 0){
		//git tree positions
		FILE * ftree_pos = fopen("Treepos.txt", "r");
		for(int i = 1; i < num_trees + 1; i ++)
		fscanf(ftree_pos, "%d\n", &tree_location[i]);
		fclose(ftree_pos);
		
		//git axes done to trees
		FILE * ftree_axes = fopen("Treeaxes.txt", "r");
		for(int i = 1; i < num_trees + 1; i ++)
		fscanf(ftree_axes, "%d\n", &axes_done[i]);
		fclose(ftree_axes);
		
		//git stump axes done to trees
		FILE * ftree_stumps = fopen("Treestumps.txt", "r");
		for(int i = 1; i < num_trees + 1; i ++)
		fscanf(ftree_stumps, "%d\n", &stump_axes_done[i]);
		fclose(ftree_stumps);
		
		//git Tree Status
		FILE * ftree_status = fopen("Treestatus.txt", "r");
		for(int i = 1; i < num_trees + 1; i ++){
			short int tree_stat;
			fscanf(ftree_status, "%d\n", &tree_stat);
			
			if(tree_stat == 1)
			is_tree_down[i] = true;
			
			else
			is_tree_down[i] = false;
		}
		fclose(ftree_status);
		
		//git Log pos
		FILE * flog_pos = fopen("Logpos.txt", "r");
		for(int i = 1; i < num_trees + 1; i ++){
			for(int j = 1; j < 5; j ++)
			fscanf(flog_pos, "%d\n", &log_pos[i][j]);
		}
		fclose(flog_pos);
		
		//git Log status
		FILE * flog_status = fopen("Logstatus.txt", "r");
		for(int i = 1; i < num_trees + 1; i ++){
			short int log_stat;
			for(int j = 1; j < 5; j ++){
				fscanf(ftree_status, "%d\n", &log_stat);
				
				if(log_stat == 1)
				is_stick[i][j] = true;
				
				else
				is_stick[i][j] = false;
			}
		}
		fclose(flog_status);
		
		//Locate last day done
		FILE * ftree_day = fopen("Treeday.txt", "r");
		fscanf(ftree_day, "%d\n", &day_tree);
		fclose(ftree_day);
	}
	
	bool can_reset = true;
	
	for(int i = 1; i < num_trees + 1; i ++){
		for(int j = 1; j < 5; j ++){
			if(log_pos[i][j] != -55)
			can_reset = false;
		}
	}
	
	//See if it alr passed 3 days b4 the last visit (set to -5 in the 1st visit)
	if(tree_day != day_tree){
		long int diference_day = abs(tree_day - day_tree);
		
		if(DEBUG_MODE)
		printf("[DEBUG] _> Day tree? %d\n", day_tree);
		
		
		if(diference_day >= 3){
			day_tree = tree_day;
			diferent_day = true;
		}
		
		if(DEBUG_MODE){
		    printf("[DEBUG] _> Diference day? %d / Day tree? %d / Day? %d\n", diference_day, day_tree, tree_day);
		    printf("[DEBUG] _> Diferent Day? %d (Boolean Value)\n", diferent_day);
		}
	}
	
	//Reset the trees that need it (wont reset if there are still logs out there)
	if(diferent_day && can_reset){
		for(int i = 1; i < num_trees + 1; i ++){
			if(tree_location[i] == -55){
				short int tree_pos_chosen = rand()% 49 + 1;
				if(memchr(tree_location, tree_pos_chosen, sizeof(tree_location))!= NULL || tree_pos_chosen == 25)
				i --;
				
				else
				tree_location[i] = tree_pos_chosen;
				
				if(DEBUG_MODE)
				printf("[DEBUG] _> tree_location[%d]? %d\n", i, tree_location[i]);
			}
			
			if(is_tree_down[i])
			is_tree_down[i] = false;
			
			if(axes_done[i] >= axes_needed)
			axes_done[i] = 0;
			
			if(stump_axes_done[i] >= stump_axes_needed)
			stump_axes_done[i] = 0;
		}
	}
	
	if(DEBUG_MODE)
	printf("\n");
	
	
	printf("Starting Table:\n");
	
	//Display starting pos
	if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
		printf("[0] [0] [0] [0] [0] [0] [0]\n");
		printf("[0] [0] [0] [0] [0] [0] [0]\n");
		printf("[0] [0] [0] [1] [0] [0] [0]\n");
		printf("[0] [0] [2] [9] [3] [0] [0]\n");
		printf("[0] [0] [0] [4] [0] [0] [0]\n");
		printf("[0] [0] [0] [0] [0] [0] [0]\n");
		printf("[0] [0] [0] [0] [0] [0] [0]\n\n\n");
	} else {
		printf("[NONE] [NONE] [NONE] [NONE] [NONE] [NONE] [NONE]\n");
		printf("[NONE] [NONE] [NONE] [NONE] [NONE] [NONE] [NONE]\n");
		printf("[NONE] [NONE] [NONE] [UP] [NONE] [NONE] [NONE]\n");
		printf("[NONE] [NONE] [LEFT] [YOU] [RIGHT] [NONE] [NONE]\n");
		printf("[NONE] [NONE] [NONE] [DOWN] [NONE] [NONE] [NONE]\n");
		printf("[NONE] [NONE] [NONE] [NONE] [NONE] [NONE] [NONE]\n");
		printf("[NONE] [NONE] [NONE] [NONE] [NONE] [NONE] [NONE]\n\n\n");
	}
	
	X = 4;
	Y = 4;
	
	while(true){
		
		if(changed_game_set && is_tut){
			changed_game_set = false;
			
			if(strcmp(tut_game_set, "Int")== 0 && is_tut){
				printf("Listen up, this is important\n");
				printf("Type 1 to go Up a Square, 2 to go left, 3 to go right and 4 to go down\n");
				printf("Type 9 to leave WITHOUT collect matherials and 0 to stay in the same spot\n");
				printf("Type 8 to switch \"game_set\" types, aka if you are playing with \"INT\" it switches to \"CHAR\" and vice versa (tutorial only command)\n\n");
				
				printf("Type 5 to chop down trees down or chop logs into sticks\n");
				printf("Type 6 to collect the logs or sticks you just chopped\n");
				printf("Type 7 to switch \"is_invasive\", aka switch bettewn invasive and non invasive trees\n\n");
				
				printf("The chopping down tree system:\n");
				printf("After you chop down a tree it leaves a trunk behind and some logs on the path it choose, you can choose to chop those logs more and leave a stick behind\n\n");
				
				printf("Invasive vs Non Invasive trees:\n");
				printf("You are ENCOURAGED to chop down Invasive stumps and leave Non Invasive stumps behind\n");
				printf("Invasive trees and stumps, are easier to chop down because they are WEAK and must be GONE\n");
				printf("If you chop down tree stumps they will respawn in annother place, else they will spawn in the same spot has it was left on [Same for both Invasive and Non Invasive]\n");
				printf("[Your save file will save the positions of the stumps, dont worry] [Resets every 3 days]\n\n");
				
				printf("[(Important) EXTRA INFO] - Small note to keep in mind\n");
				printf("Tree / Stumps get priority over whats chosen to chop down or collect (alters the gameplay a little bit) (only works if trees / stumps are near logs)\n\n");
				
				printf("[Saves stuff]\n");
				printf("Your save saves EVERYTHING that you did on THAT spot, including logs and trees\n");
				printf("That being said, to make the trees respawn you need to collect all logs that are in the ground and leave\n");
				printf("If 3 days pass, the trees will respawn normaly\n\n");
				
				printf("Your goal is to just chop down trees and colect logs or sticks, chop down stumps if you want\n");
				printf("Understood? You better...\n\n");
			} else {
				printf("Listen up, this is important\n");
				printf("Type \"Up\" to go Up a Square, \"Left\" to go left, \"Right\" to go right and \"Down\" to go down\n");
				printf("Type \"Leave\" or \"Back\" to leave WITHOUT collect matherials and \"stay\" to stay in the same spot\n");
				printf("Type \"Game\" to switch \"game_set\" types, aka if you are playing with \"INT\" it switches to \"CHAR\" and vice versa (tutorial only command)\n\n");
				
				printf("Type \"Chop\" to chop down trees down or chop logs into sticks\n");
				printf("Type \"Collect\" to collect the logs or sticks you just chopped\n");
				printf("Type \"Invasive\" to switch \"is_invasive\", aka switch bettewn invasive and non invasive trees\n\n");
				
				printf("The chopping down tree system:\n");
				printf("After you chop down a tree it leaves a trunk behind and some logs on the path it choose, you can choose to chop those logs more and leave a stick behind\n\n");
				
				printf("Invasive vs Non Invasive trees:\n");
				printf("You are ENCOURAGED to chop down Invasive stumps and leave Non Invasive stumps behind\n");
				printf("Invasive trees and stumps, are easier to chop down because they are WEAK and must be GONE\n");
				printf("If you chop down tree stumps they will respawn in annother place, else they will spawn in the same spot has it was left on [Same for both Invasive and Non Invasive]\n");
				printf("[Your save file will save the positions of the stumps, dont worry] [Resets every 3 days]\n\n");
				
				printf("[(Important) EXTRA INFO] - Small note to keep in mind\n");
				printf("Tree / Stumps get priority over whats chosen to chop down or collect (alters the gameplay a little bit) (only works if trees / stumps are near logs)\n\n");
				
				printf("[Saves stuff]\n");
				printf("Your save saves EVERYTHING that you did on THAT spot, including logs and trees\n");
				printf("That being said, to make the trees respawn you need to collect all logs that are in the ground and leave\n");
				printf("If 3 days pass, the trees will respawn normaly\n\n");
				
				printf("Your goal is to just chop down trees and colect logs or sticks, chop down stumps if you want\n");
				printf("Understood? You better...\n\n");
			}
			
			Small_stop;
		}
		
		//Movements depending on game set status
		printf("Next move?\n");
			
			if((strcmp(game_set, "Char")== 0 && !is_tut) || (strcmp(tut_game_set, "Char")== 0 && is_tut)){
			String_Input;
			
				if(strcmp(Input, "up")== 0){
				Y -= 1; stored_move = 1; }
					
				else if(strcmp(Input, "left")== 0){
				X -= 1;	stored_move = 2; }
				
				else if(strcmp(Input, "right")== 0){
				X += 1; stored_move = 3; }
					
				else if(strcmp(Input, "down")== 0){
				Y += 1;	stored_move = 4; }
				
				else if(strcmp(Input, "chop")== 0)
				Chop = true;
					
				else if(strcmp(Input, "collect")== 0)
				Collect = true;
				
				else if(strcmp(Input, "stay")== 0){ }
				
				else if(strcmp(Input, "invasive")== 0 && is_tut){
					green;
					
					if(!is_invasive)
					is_invasive = true;
					
					else
					is_invasive = false;
					
					if(is_invasive)
					printf("Changed to Invasive Trees!\n");
					
					else
					printf("Changed to Non Invasive Trees!\n");
					
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
					
				}
				
				else if(strcmp(Input, "leave")== 0 || strcmp(Input, "back")== 0){
					
					Leave = true; break;
					
				} else { Error; }
				
			} else {
				
				String_Input;
				
				if(strcmp(Input, "1")== 0){
				Y -= 1; stored_move = 1; }
				
				else if(strcmp(Input, "2")== 0){
				X -= 1; stored_move = 2; }
				
				else if(strcmp(Input, "3")== 0){
				X += 1; stored_move = 3; }
				
				else if(strcmp(Input, "4")== 0){
				Y += 1; stored_move = 4; }
				
				else if(strcmp(Input, "5")== 0)
				Chop = true;
				
				else if(strcmp(Input, "6")== 0)
				Collect = true;
				
				else if(strcmp(Input, "0")== 0){ }
				
				else if(strcmp(Input, "7")== 0 && is_tut){
					green;
					
					if(!is_invasive)
					is_invasive = true;
					
					else
					is_invasive = false;
					
					if(is_invasive)
					printf("Changed to Invasive Trees!\n");
					
					else
					printf("Changed to Non Invasive Trees!\n");
					
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
					
				}
				
				else if(strcmp(Input, "9")== 0){

				Leave = true; break;
				
				} else { Error; }
				
				if(Leave)
				break;
				
			}
			
			//Normal stuff but now its a 7x7 table
			if (X >= 8){ printf("Outside playing field\n"); sleep(1); X = 7; CLR; }
			else if (X <= 0){ printf("Outside playing field\n"); sleep(1); X = 1; CLR; }
			else if (Y <= 0){ printf("Outside playing field\n"); sleep(1); Y = 1; CLR; }
			else if (Y >= 8){ printf("Outside playing field\n"); sleep(1); Y = 7; CLR; }
			
			//Calc pos
			L = (Y * 7) - 7;
			
			user_pos = X + L;
			
			//Current user pos is inside any of the trees?
			if(memchr(tree_location, user_pos, sizeof(tree_location))!= NULL || memchr(log_pos, user_pos, sizeof(log_pos))!= NULL){
				red;
				printf("Try not to walk into trees or logs, please\n");
				white;
				
				if(stored_move == 1)
				Y += 1;
				
				else if(stored_move == 2)
				X += 1;
				
				else if(stored_move == 3)
				X -= 1;
				
				else
				Y -= 1;
			}
			
			L = (Y * 7) - 7;
			user_pos = X + L;
			
			if(DEBUG_MODE)
			printf("[DEBUG] _> X? %d / Y? %d / L? %d / User_pos? %d\n", X, Y, L, user_pos);
	
			if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
				
				//Set all pos to 0
				memset(i_table_pos_, 0, sizeof(i_table_pos_));
				
				//Git usr pos and others
				i_table_pos_[user_pos] = 9;
				
				//Get tree location and change display depending if its down or not
				for(int i = 1; i < num_trees + 1; i ++){
					if(tree_location[i] != -55){
						if(is_tree_down[i])
						i_table_pos_[tree_location[i]] = 6;
						
						else
						i_table_pos_[tree_location[i]] = 8;
					}
				}
				
				//Show logs or sticks
				for(int y = 1; y < num_trees + 1; y ++){
					for(int z = 1; z < 6; z ++){
						if(log_pos[y][z] != -55){
							if(!is_stick[y][z])
							i_table_pos_[log_pos[y][z]] = 7;
							
							else
							i_table_pos_[log_pos[y][z]] = 5;
						}
					}
				}
					
				
			} else {
				
				//Set all pos to "NONE"
				for(int i = 1; i < 50; i ++)
				strcpy(c_table_pos_[i], "NONE");
				
				//Git usr pos and others
				strcpy(c_table_pos_[user_pos], "YOU");
					
				//Get tree location and change display depending if its down or not
				for(int i = 1; i < num_trees + 1; i ++){
					if(tree_location[i] != -55){
						if(is_tree_down[i])
						strcpy(c_table_pos_[tree_location[i]], "STUMP");
						
						else
						strcpy(c_table_pos_[tree_location[i]], "TREE");
					}
				}
				
				//Show logs or sticks
				for(int y = 1; y < num_trees + 1; y ++){
					for(int z = 1; z < 6; z ++){
						if(log_pos[y][z] != -55){
							if(!is_stick[y][z])
							strcpy(c_table_pos_[log_pos[y][z]], "LOG");
							
							else
							strcpy(c_table_pos_[log_pos[y][z]], "STICK");
						}
					}
				}
				
			}
			
			short int bckp_pos = user_pos, bp_bckp_pos = 0, bckp_Y = 0;
			short int move_to_tree_pos = 0, move_to_log_pos = 0, interacting_tree = 0, interacting_log = 0;
			
			//system to detect how many trees are next to the user
			num_trees_next_to_user = 0;
			
			//Using 2 assisting arrays for this
			bool tree_assisting_array[50];
			memset(tree_assisting_array, 0, sizeof(tree_assisting_array));
			bool log_assisting_array[50];
			memset(log_assisting_array, 0, sizeof(log_assisting_array));
			
			//Very unoptimized but it serves its purpose
			//Get tree positions and if its down or not
			for(int i = 1; i < num_trees + 1; i++)
			tree_assisting_array[tree_location[i]] = is_tree_down[i];
			
			//Get log positions and if its down or not
			for(int i = 1; i < num_trees + 1; i++){
				for(int j = 1; j < 5; j++)
				log_assisting_array[log_pos[i][j]] = is_stick[i][j];
			}
			
			//This checks if tree is NOT DOWN and it actually exists, simular to the code a few lines bellow
			//And does the same thing w logs, checks if its NOT stick and if it exists
			if((memchr(tree_location, bckp_pos -7, sizeof(tree_location))!= NULL && !tree_assisting_array[bckp_pos - 7]) || 
			(memchr(log_pos, bckp_pos - 7, sizeof(log_pos))!= NULL && !log_assisting_array[bckp_pos - 7])){
				bp_bckp_pos = bckp_pos - 7;
				if(bp_bckp_pos >= 1 && bp_bckp_pos <= 49)
				num_trees_next_to_user ++;
			}
			
			if((memchr(tree_location, bckp_pos + 7, sizeof(tree_location))!= NULL && !tree_assisting_array[bckp_pos + 7]) ||
			(memchr(log_pos, bckp_pos + 7, sizeof(log_pos))!= NULL && !log_assisting_array[bckp_pos + 7])){
				bp_bckp_pos = bckp_pos + 7;
				if(bp_bckp_pos >= 1 && bp_bckp_pos <= 49)
				num_trees_next_to_user ++;
			}
			
			if((memchr(tree_location, bckp_pos - 1, sizeof(tree_location))!= NULL && !tree_assisting_array[bckp_pos - 1]) ||
			(memchr(log_pos, bckp_pos - 1, sizeof(log_pos))!= NULL && !log_assisting_array[bckp_pos - 1])){
				bckp_Y = (bckp_pos - 1) / 7.1428571428571429;
				bckp_Y += 1;
				if(bckp_Y == Y && user_pos != 1)
				num_trees_next_to_user ++;
			}
			
			if((memchr(tree_location, bckp_pos + 1, sizeof(tree_location))!= NULL && !tree_assisting_array[bckp_pos + 1]) ||
			(memchr(log_pos, bckp_pos + 1, sizeof(log_pos))!= NULL && !log_assisting_array[bckp_pos + 1])){
				bckp_Y = (bckp_pos + 1) / 7.1428571428571429;
				bckp_Y += 1;
				if(bckp_Y == Y && user_pos != 1)
				num_trees_next_to_user ++;
			}
			
			if(DEBUG_MODE)
			printf("[DEBUG] _> Num Trees Next To User? %d\n", num_trees_next_to_user);
			
			//Checks if user is near tree or stump [CODE MESS BELLOW, PLEASE HELP LOLLLL]
			//Note: I cant find a better way to do this, this problem is such a big mess i just gave up on optimizing it
			while(true){ 														
			
				//Wipe assisting array if user moves from previous interacting tree spot OR if there is only 1 tree near user
				if(bckp_bckp_pos != user_pos || num_trees_next_to_user == 1)
				memset(arr_alr_done_tree_pos, 0, sizeof(arr_alr_done_tree_pos));
				
				//Declare assisting pointer has NULL
				char * tree_ptr = NULL;
				
				//Set up a check to see if previous pos was done (made for the pointer )
				bool previous_pos_done = false;
				
				//Check if -7 is inside of any positions in arr_alr_done_tree_pos and give a value to the pointer
				//If pointer == NULL means theres not but if pointer has a value, it just gives the position of the array that -7 is stored at
				//Also check if user is trying to collect log to not show error
				if(!Collect)
				tree_ptr = (char *)memchr(arr_alr_done_tree_pos, -7, sizeof(arr_alr_done_tree_pos));
				
				//Check if user is near tree and set the pos diference bettewn the 2
				//Also check if this position wasnt checked b4 (pointer help)
				//& check if position is inside board and valid
				if(memchr(tree_location, bckp_pos -7, sizeof(tree_location))!= NULL && tree_ptr == NULL){
					bp_bckp_pos = bckp_pos - 7;
					if(bp_bckp_pos >= 1 && bp_bckp_pos <= 49){
						move_to_tree_pos = -7;
						previous_pos_done = true;
					}
				}
				
				//Same thing has above but switch -7 to -1
				if(!previous_pos_done){
					if(!Collect)
					tree_ptr = (char *)memchr(arr_alr_done_tree_pos, -1, sizeof(arr_alr_done_tree_pos));
										
					if(memchr(tree_location, bckp_pos - 1, sizeof(tree_location))!= NULL && tree_ptr == NULL){
						bckp_Y = (bckp_pos - 1) / 7.1428571428571429;
						bckp_Y += 1;
						if(bckp_Y == Y && user_pos != 1){	//Check for not pos 1 cause pos 1 causes an invalid tree bug
							move_to_tree_pos = -1;
							previous_pos_done = true;
						}
					}
				}
				
				//Same thing has above but switch -1 to 1
				if(!previous_pos_done){
					if(!Collect)
					tree_ptr = (char *)memchr(arr_alr_done_tree_pos, 1, sizeof(arr_alr_done_tree_pos));
					
					if(memchr(tree_location, bckp_pos + 1, sizeof(tree_location))!= NULL && tree_ptr == NULL){
						bckp_Y = (bckp_pos + 1) / 7.1428571428571429;
						bckp_Y += 1;
						if(bckp_Y == Y){
							move_to_tree_pos = 1;
							previous_pos_done = true;
						}
					}
				}
				
				//Same thing has above but switch 1 to 7 AND no need for bool var switch
				if(!previous_pos_done){
					if(!Collect)
					tree_ptr = (char *)memchr(arr_alr_done_tree_pos, 7, sizeof(arr_alr_done_tree_pos));
					
					if(memchr(tree_location, bckp_pos + 7, sizeof(tree_location))!= NULL && tree_ptr == NULL){
						bp_bckp_pos = bckp_pos + 7;
						if(bp_bckp_pos >= 1 && bp_bckp_pos <= 49)
						move_to_tree_pos = 7;
					}
				}
				
				//Detected tree?
				if(move_to_tree_pos != 0)
				near_tree = true;
				
				//What tree did it detect?
				if(near_tree){
					for(int i = 1; i < num_trees + 1; i ++){
						if(bckp_pos + move_to_tree_pos == tree_location[i]){
							interacting_tree = i;
							bckp_bckp_pos = user_pos;
							break;
						} else
						interacting_tree = 0;
					}
				
				//Checking for logs if there arent any trees
				} else {
					
					//Note: this part is the same thing has detecting tree but i switch the variables to log variables, the process is still the same
					
					char * log_ptr = NULL;
					
					if(!Collect)
					log_ptr = (char *)memchr(arr_alr_done_tree_pos, -7, sizeof(arr_alr_done_tree_pos));
					
					
					if(memchr(log_pos, bckp_pos -7, sizeof(log_pos))!= NULL && log_ptr == NULL){
						bp_bckp_pos = bckp_pos - 7;
						if(bp_bckp_pos >= 1 && bp_bckp_pos <= 49){
							move_to_log_pos = -7;
							previous_pos_done = true;
						}
					}
					
					if(!previous_pos_done){
						if(!Collect)
						log_ptr = (char *)memchr(arr_alr_done_tree_pos, -1, sizeof(arr_alr_done_tree_pos));
											
						if(memchr(log_pos, bckp_pos - 1, sizeof(log_pos))!= NULL && log_ptr == NULL){
							bckp_Y = (bckp_pos - 1) / 7.1428571428571429;
							bckp_Y += 1;
							if(bckp_Y == Y && user_pos != 1){	//Check for not pos 1 cause pos 1 causes an invalid log bug
								move_to_log_pos = -1;
								previous_pos_done = true;
							}
						}
					}
					
					if(!previous_pos_done){
						if(!Collect)
						log_ptr = (char *)memchr(arr_alr_done_tree_pos, 1, sizeof(arr_alr_done_tree_pos));
						
						if(memchr(log_pos, bckp_pos + 1, sizeof(log_pos))!= NULL && log_ptr == NULL){
							bckp_Y = (bckp_pos + 1) / 7.1428571428571429;
							bckp_Y += 1;
							if(bckp_Y == Y){
								move_to_log_pos = 1;
								previous_pos_done = true;
							}
						}
					}
					
					if(!previous_pos_done){
						if(!Collect)
						log_ptr = (char *)memchr(arr_alr_done_tree_pos, 7, sizeof(arr_alr_done_tree_pos));
						
						if(memchr(log_pos, bckp_pos + 7, sizeof(log_pos))!= NULL && log_ptr == NULL){
							bp_bckp_pos = bckp_pos + 7;
							if(bp_bckp_pos >= 1 && bp_bckp_pos <= 49)
							move_to_log_pos = 7;
						}
					}
					
					if(move_to_log_pos != 0)
					near_log = true;
					
					bool done_log = false;
					
					//This nested check gives the program the tree that the log is part of and the number of the log that it is from that tree
					if(near_log){
						short int bckp_interacting_log = interacting_log, bckp_interacting_tree = interacting_tree; 
							for(int i = 1; i < num_trees  + 1; i ++){
								for(int j = 1; j < 5; j ++){
									if(bckp_pos + move_to_log_pos == log_pos[i][j]){
										interacting_tree = i;
										interacting_log = j;
										bckp_bckp_pos = user_pos;
										done_log = true;
										break;
									}
								}
								if(done_log)
								break;
							}
						}
					
				}
					
				//break out of loop
				if(interacting_tree != 0 || move_to_tree_pos == 0 || interacting_log != 0 || move_to_log_pos == 0)
				break;
				
			}
			
			if(DEBUG_MODE){
			    printf("[DEBUG] _> Near tree? %d / Near log? %d (boolean values)\n", near_tree, near_log);
			    printf("[DEBUG] _> Move to tree pos? %d / Inteacting tree? %d\n", move_to_tree_pos, interacting_tree);
			    printf("[DEBUG] _> Move to log pos? %d / Interacting log? %d\n", move_to_log_pos, interacting_log);
			    printf("[DEBUG] _> Bckp Y? %d\n", bckp_Y); 
			
			    for(int i = 0; i < 4; i++)
			    printf("[DEBUG] [%d] _> Arr alr done tree pos? %d\n", i, arr_alr_done_tree_pos[i]);
			    //har har har har (this array name sounds like the fnaf meme)
	        }
			
			
			//Make a move on the tree (LMAO)
			if(Chop && (near_tree || near_log)){
				
				//Chop down tree
				if(near_tree){			
					green;
		
					//not down? chop it.
					if(!is_tree_down [interacting_tree]){
						
						axes_done[interacting_tree] ++;
						if(axes_done[interacting_tree] <= axes_needed)
						printf("Thats the spirit!\n");
					} else {
						
						stump_axes_done[interacting_tree] += 1;
						printf("CUT IT DOWN! YEAAAAAAAAAAAA!!! (Man things)\n");
						
						if(DEBUG_MODE){
						    for(int i = 1; i < num_trees + 1; i++)
						    printf("[DEBUG] [%d] _> Stump axes done? %d\n", i, stump_axes_done[i]);;
						}
					} 
					
					white;
				}
				
				
				//Chop down logs for sticks
				else if(near_log){
					//Mk it stick if its not alr
					if(!is_stick[interacting_tree][interacting_log]){
						is_stick[interacting_tree][interacting_log] = true;
						
						//Add the new move to the filter array
						//Note: ur supost to chop it down into a stick and THEN collect it or collect it while its a log
						if(memchr(arr_alr_done_tree_pos, move_to_log_pos, sizeof(arr_alr_done_tree_pos))== NULL){
							for(int i = 0; i < 5; i ++){
								if(arr_alr_done_tree_pos[i] == 0){
								arr_alr_done_tree_pos[i] = move_to_log_pos;
								break;
								}
							}
						}
						
						//Update pos
						if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut))
						i_table_pos_[log_pos[interacting_tree][interacting_log]] = 5;
						
						else
						strcpy(c_table_pos_[log_pos[interacting_tree][interacting_log]], "STICK");
						
					} else { //Err. msg
						red;
						printf("You cant chop a stick smaller than it already is!\n");
						white;
					}
				} 
			
			//Cant make a move on the tree (git rejected)
			} else if(Chop && (!near_tree || !near_log)){
				red;
				printf("You arent near enough to a tree, a trunk or a log to chop it down\n");
				white;
			}
			
			//Chopped down the stump :>
			if(stump_axes_done[interacting_tree] == stump_axes_needed && is_tree_down[interacting_tree]){
				tree_ID = Log1_ID;
				tree_quant = 3;
				
				int overflow = Inventory("CALC", tree_ID, tree_quant);
				
				//Stash initiated!
				if(overflow > 0){
					CLR;
					light_blue;
					printf("Woops! Your inventory was full so, might has well empty it sooner or later!\n");
					white;
					Small_stop;
					
				} else {
					
				yellow;
				printf("STUMP CHOPPED\n");
				white;
				
				//Update pos
				if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut))
				i_table_pos_[tree_location[interacting_tree]] = 0;
				
				else
				strcpy(c_table_pos_[tree_location[interacting_tree]], "NONE");
				
				tree_location[interacting_tree] = -55;
				stump_axes_done[interacting_tree] = 55;
				
				light_blue;
				
				if(!is_tut){
					if(is_invasive)
					printf("Got 3 invasive logs!\n");
					
					else
					printf("Got 3 non invasive logs!\n");
					
					//Key 3 related stuff
					if(do_key3)
					number_trees_choped_down ++;
					
				} else {
					if(is_invasive)
					printf("You got 3x TUTORIAL_INVASIVE_LOG");
					
					else
					printf("You got 3x TUTORIAL_NON_INVASIVE_LOG");
					
				}
				
				white;
				
				if(DEBUG_MODE)
				printf("[DEBUG] _> Here is your debug mode message i guess? There arent calculations here lul\n");
				
			}
		}
			
			//System to get the tree to fall down
			if(axes_done[interacting_tree] == axes_needed && !is_tree_down[interacting_tree]){
				
				//Add the new move to the filter array
				if(memchr(arr_alr_done_tree_pos, move_to_tree_pos, sizeof(arr_alr_done_tree_pos))== NULL && num_trees_next_to_user != 1){
					for(int i = 0; i < 5; i ++){
						if(arr_alr_done_tree_pos[i] == 0){
						arr_alr_done_tree_pos[i] = move_to_tree_pos;
						break;
						}
					}
	 			}
				
				is_tree_down[interacting_tree] = true;
				
				num_trees_next_to_user --;
				
				yellow;
				printf("TIMBER!\n");
				white;
				
				//Set more vars for assistance
				bool can_this_tree_fall_over = true;
				short int bckp_tree_pos = tree_location[interacting_tree];
				
				//Used to randomize position and get WHAT direction its going to fall in
				//AND the number of logs that will fall over
				short int radius_chosen = 1, number_of_logs_down = 1;
				
				number_of_logs_down += rand()% 3 + 1;
				
				for(int radius_chosen = 1; radius_chosen < 6; radius_chosen ++){
					
				//Tree cant fall :<
				if(radius_chosen == 5){
					is_tree_down[interacting_tree] = false; 						//Tree cant fall so set both bools to false
					can_this_tree_fall_over = false;								//Set this thing to false
					
					num_trees_next_to_user ++;
					axes_done[interacting_tree] --;									//Make these things go up
					
					for(int i = 0; i < 5; i++)										//Tree cant fall so set log positions to -55
					log_pos[interacting_tree][i] = -55;
					
					red;	//Inform user that it cannot fall.
					printf("[SYSTEM] Tree cannot fall. [Move over or chop other stuff to make way for it]\n");
					white;
					break;
				}
					
				can_this_tree_fall_over = true;
					//Up and down chosen
					if(radius_chosen == 1 || radius_chosen == 4){
						//Check the ending position on both
						if(radius_chosen == 1)
						bckp_tree_pos = tree_location[interacting_tree] - (7 * number_of_logs_down);
						
						else
						bckp_tree_pos = tree_location[interacting_tree] + (7 * number_of_logs_down);
						
						//Get the Y position of the last log position
						bckp_tree_pos /= 7;
						
						if(DEBUG_MODE)
						printf("[DEBUG] [%d] [Y AXIS] _> Bckp tree pos? %d\n", radius_chosen, bckp_tree_pos);
						
						
						//Válid? Check if there r logs in the way
						if(bckp_tree_pos >= 1 && bckp_tree_pos <= 7){
							
							short int bckp_j = tree_location[interacting_tree];
							
							//Simulate log positions and check if they r valid or not
							for(int j = 1; j < number_of_logs_down + 1; j++){
								//Check individual log positions
								if(radius_chosen == 1)
								bckp_j -= 7;
								
								else
								bckp_j += 7;
								
								//Check if current log position is inside position of tree or stump
								if(memchr(tree_location, bckp_j, sizeof(tree_location))!= NULL)
								can_this_tree_fall_over = false;
								
								//Check if current log position is inside the position of annother log
								if(memchr(log_pos, bckp_j, sizeof(log_pos))!= NULL)
								can_this_tree_fall_over = false;
								
								//Tree wont fall on user lol
								if(bckp_j == user_pos)
								can_this_tree_fall_over = false;
								
								//Break loop if the tree cant fall in ANY position
								if(!can_this_tree_fall_over)
								break;
							}
							
						} else 
						can_this_tree_fall_over = false;
						
					} else if(radius_chosen == 2 || radius_chosen == 3){
						//Check the ending position on both
						if(radius_chosen == 2)
						bckp_tree_pos = tree_location[interacting_tree] - number_of_logs_down;
						
						else
						bckp_tree_pos = tree_location[interacting_tree] + number_of_logs_down;
						
						//Git both starting and end point Y cord
						short int start_Y_log = tree_location[interacting_tree] / 7.1428571428571429; 
						short int end_Y_log = bckp_tree_pos / 7.1428571428571429;
						
						//Note to reader: the value above (7.1428571428571429) checks if the last position is (VAR / 7) + 1 AKA (1/7) + 7
						//Value made to see if the last pos is anywhere near around 8 / 15 / 22 / 29 / 36 / 43
						
						if(DEBUG_MODE)
						printf("[DEBUG] [%d] [X AXIS] _> Start Y log? %d / End Y log? %d\n", radius_chosen, start_Y_log, end_Y_log);
						
						//Válid? Check if there r logs in the way
						if(start_Y_log == end_Y_log){
							
							short int bckp_j = tree_location[interacting_tree];
							
							//Simulate log positions and check if they r valid or not
							for(int j = 1; j < number_of_logs_down + 1; j++){
								
								//Check individual log positions
								if(radius_chosen == 2)
								bckp_j -= 1;
								
								else
								bckp_j += 1;
								
								//Check if current log position is inside position of tree or stump
								if(memchr(tree_location, bckp_j, sizeof(tree_location))!= NULL)
								can_this_tree_fall_over = false;
								
								//Check if current log position is inside the position of annother log
								if(memchr(log_pos, bckp_j, sizeof(log_pos))!= NULL)
								can_this_tree_fall_over = false;
								
								//Tree wont fall on user lol
								if(bckp_j == user_pos)
								can_this_tree_fall_over = false;
								
								//Break loop if the tree cant fall in ANY position
								if(!can_this_tree_fall_over)
								break;
							}
							
						} else 
						can_this_tree_fall_over = false;
						
					}
						
					//If check passes, show tree
					if(can_this_tree_fall_over){
						
						short int starting_pos = tree_location[interacting_tree];
						
						//Loop to fill current log position with logs in the display and in the 2d array storing them
						for(int l = 1; l < number_of_logs_down + 1; l ++){
							
							if(radius_chosen == 1)
							starting_pos -= 7;
							
							else if(radius_chosen == 2)
							starting_pos -= 1;
							
							else if(radius_chosen == 3)
							starting_pos += 1;
							
							else if(radius_chosen == 4)
							starting_pos += 7;
							
							log_pos[interacting_tree][l] = starting_pos;
							
							if(DEBUG_MODE)
							printf("[DEBUG] _> Starting Pos? %d (AKA next log position)\n", starting_pos);
							
						}
						
						if(is_tree_down[interacting_tree]){
						
							//Show logs and stump in table for int and char
							if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
								for(int y = 1; y < num_trees + 1; y ++){
									for(int z = 1; z < number_of_logs_down + 1; z ++)
									i_table_pos_[log_pos[y][z]] = 7;
									
									i_table_pos_[tree_location[interacting_tree]] = 6;
								}
							} else {
								for(int y = 1; y < num_trees + 1; y ++){
									for(int z = 1; z < 6; z ++)
									strcpy(c_table_pos_[log_pos[y][z]], "LOG");
									
									strcpy(c_table_pos_[tree_location[interacting_tree]], "STUMP");
								}
							}
						
						}
					
					}
					
					//Stopping loop if tree fell
					if(can_this_tree_fall_over){
						break;	
					}
									
				}
				
				if(DEBUG_MODE){
				    printf("[DEBUG] _> Number of logs down? %d\n", radius_chosen, number_of_logs_down);
				
				    //Show all log positions
				    for(int y = 1; y < num_trees + 1; y ++){
				    for(int z = 1; z < 5; z ++)
				    printf("[DEBUG] _> Log Pos[%d][%d]? %d\n",y ,z, log_pos[y][z]);
			        }
				}
			}
			
			//Collect stuff
			if(Collect){
				Collect = false;
				
				if(near_log){
					light_blue;
					
					if(!is_tut){
						if(is_stick[interacting_tree][interacting_log]){
							printf("You got a Stick!\n");
							tree_ID = 102;
						}
							
						else {
							
							short int log_chosen = rand() % 10 + 1;
							
							
							if(is_invasive){
								printf("You got a Invasive Log!\n");
								tree_ID = Log1_ID;
							}
							
							else {
								printf("You got a Log!\n");
								tree_ID = Log1_ID;
							}
							
							if(log_chosen == 10){
								printf("You got a Special from a Log!\n");
								tree_ID = special_tree_ID;
							}
							
							tree_quant = 1;	
						}
					
					} else {
						if(is_stick[interacting_tree][interacting_log])
						printf("You got a TUTORIAL_STICK!"); 
						
						else {
							
							short int log_chosen = rand() % 10 + 1;
							
							
							if(is_invasive){
								printf("You got a TUTORIAL_INVASIVE_LOG!\n");
							}
							
							else {
								printf("You got a TUTORIAL_NON_INVASIVE_LOG!\n");
							}
							
							if(log_chosen == 10){
								printf("You got a TUTORIAL_SPECIAL_TREE_ITEM!\n");
							}
								
						}
						
						tree_quant = 0;
					}
					
					white;
					
					int overflow = Inventory("CALC", tree_ID, tree_quant);
					
					if(overflow > 0){
						CLR;
						light_blue;
						printf("Woops! Your inventory was full so, might has well empty it sooner or later!\n");
						white;
						Small_stop;
						
					} else {
					
						if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut))
						i_table_pos_[log_pos[interacting_tree][interacting_log]] = 0;
						
						else
						strcpy(c_table_pos_[log_pos[interacting_tree][interacting_log]], "NONE");
						
						log_pos[interacting_tree][interacting_log] = -55;
						
					}
					
				} else {
					red;
					printf("You arent near enough to a log or a stick to collect it!\n");
					white;
				}
			}
			
			near_tree = false;
			near_log = false;
			Chop = false;
			Collect = false;
			
			printf("\n");
			
			//Set all "log_pos 0" to -55, and stump axes done that are not done to "0" [Preventing bugs from happening]
			for(int i = 1; i < num_trees + 1; i ++){
				log_pos[i][0] = -55;

                //1-9-2024: What the fuck is this? (lets hope removing "|| stump_axes_done[i] == NULL" wont cause any errors!)
				if(stump_axes_done[i] == 0)
				stump_axes_done[i] = 0;
			}
			
			//Set all log pos not shown to -55
			for(int i = 1; i < num_trees + 1; i ++){
				if(!is_tree_down[i]){
					for(int j = 1; j <= 4; j ++)
					log_pos[i][j] = -55;
				}
			}
			
			if(DEBUG_MODE){
			    for(int i = 1; i < num_trees + 1; i ++){
				    for(int j = 1; j < 5; j ++)
				    printf("[DEBUG] [%d] [%d] _> Log pos? %d\n", i, j, log_pos[i][j]);
			    }
		    }
			
			//Show table in a 7 x 7 
			if((strcmp(game_set, "Int")== 0 && !is_tut) || (strcmp(tut_game_set, "Int")== 0 && is_tut)){
					
				for(int i = 1; i < 50; i ++){
					printf("[%d] ", i_table_pos_[i]);
						
					if(i % 7 == 0)
					printf("\n");
						
					if(i == 49)
					printf("\n");
				}
					
				} else {
   					
   				for(int i = 1; i < 50; i ++){
					printf("[%s] ", c_table_pos_[i]);
						
					if(i % 7 == 0)
					printf("\n");
						
					if(i == 49)
					printf("\n");
				}
					
			}
			
	}
	
	if(!is_tut){
		int cur_day = TimeCalc("CHECK", 0, 0, 1);
		
		ChangeCurPath("OTHER");
		ChangeCurPath("OTHER.positions.Tree");
		CatCurPath(num_spot);
		
		//Save the day this was done in
		FILE * ftree_day = fopen("Treeday.txt", "w");
		fprintf(ftree_day, "%d\n", cur_day);
		fclose(ftree_day);
		
		//Register tree positions
		FILE * ftree_pos = fopen("Treepos.txt", "w");
		for(int i = 1; i < num_trees + 1; i ++){
			if(tree_location[i] != -55)
			fprintf(ftree_pos, "%d\n", tree_location[i]);
			
			else
			fprintf(ftree_pos, "-55\n");
		}
		fclose(ftree_pos);
		
		//Register axes done to trees
		FILE * ftree_axes = fopen("Treeaxes.txt", "w");
		for(int i = 1; i < num_trees + 1; i ++)
		fprintf(ftree_axes, "%d\n", axes_done[i]);
		fclose(ftree_axes);
		
		//Register stump axes done to trees
		FILE * ftree_stumps = fopen("Treestumps.txt", "w");
		for(int i = 1; i < num_trees + 1; i ++)
		fprintf(ftree_stumps, "%d\n", stump_axes_done[i]);
		fclose(ftree_stumps);
		
		//Register Tree Status
		FILE * ftree_status = fopen("Treestatus.txt", "w");
		for(int i = 1; i < num_trees + 1; i ++){
			if(is_tree_down[i])
			fprintf(ftree_status, "1\n");
			
			else
			fprintf(ftree_status, "0\n");
		}
		fclose(ftree_status);
		
		//Register Log pos
		FILE * flog_pos = fopen("Logpos.txt", "w");
		for(int i = 1; i < num_trees + 1; i ++){
			for(int j = 1; j < 5; j ++)
			fprintf(flog_pos, "%d\n", log_pos[i][j]);
		}
		fclose(flog_pos);
		
		//Register Log status
		FILE * flog_status = fopen("Logstatus.txt", "w");
		for(int i = 1; i < num_trees + 1; i ++){
			for(int j = 1; j < 5; j ++){
				if(is_stick[i][j])
				fprintf(flog_status, "1\n");
				
				else
				fprintf(flog_status, "0\n");
			}
		}
		fclose(flog_status);
		
        //Checking for key3 related stuff
		if(do_key3){
			ChangeCurPath("OTHER.temp_key3");
			FILE * ftreeprog = fopen("TreeProg.txt", "w");
			fprintf(ftreeprog, "%d\n", number_trees_choped_down);
			fclose(ftreeprog);
		}
		
		TimeCalc("CALC", 0, 1, 0);
		
		if(number_trees_choped_down >= 3 && do_key3 && rand()% 2 + 1 == 1){
			
			//Delete temp dir
			ChangeCurPath("OTHER");
			system("rmdir /s /q temp_key3");
			
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
			
			Small_stop;
			free(hint);
			CLR;
		}
		
	} else {
		//Register tutorial has done
		if(display_all_tut_once){
			ChangeCurPath("OTHER.tutorials");
			FILE * ftutdisp = fopen("Tree.txt", "w");
			fclose(ftutdisp);
		}
		
		while(true){
		
			//Funny story
			//>Bug exists for 2 weeks reguarding the last index on "stump_axes_done" being a garbo file
			//>Too scared to fix it
			//>Cant replicate it on Tree function
			//>Put the code bellow to understand the output
			//>Bug (somehow) fixed?
			//Im a great programmer :)
			
			FILE * ftree_stumps = fopen("a.txt", "w");
			for(int i = 1; i < num_trees + 1; i ++)
			fprintf(ftree_stumps, "%d\n", stump_axes_done[i]);
			fclose(ftree_stumps);
			
			remove("a.txt");
			
			CLR;
			printf("Tutorial done!\n");
			printf("Again? [Y/N]\n");
					
			String_Input;
					
			if(strcmp(Input, "y")== 0){
				short int temp = 0;
				Tree(false, num_spot, Log1_ID, special_tree_ID, true); break;
			}	
					
			else if(strcmp(Input, "n")== 0)
			break;
					
			else 
			Error;
			
		}
	}
}

//Key manager
void Key(const char *Caller){
	CLR;
	
	//I dont want this temp to be a global in the function lol
	int * temp = (int *)malloc(2);
	int INT_key = 0;
	
	//erm, this in unoptimized (i know)
	if(strcmp(Caller, "Forest")== 0)
	INT_key = 1;
	
	else if(strcmp(Caller, "Cascade")== 0)
	INT_key = 2;
	
	else if(strcmp(Caller, "Fungi")== 0)
	INT_key = 3;
	
	else if(strcmp(Caller, "Geysers")== 0)
	INT_key = 4;
	
	else if(strcmp(Caller, "Blossom")== 0)
	INT_key = 5;
	
	else if(strcmp(Caller, "Peak")== 0)
	INT_key = 6;
	
	else
	INT_key = 0;
	
	ChangeCurPath("OTHER.triggers.story");
	FILE * fgetwhattriggersweneed = fopen("KeyTriggersDone.txt", "r");
	for(int i = 0; i < INT_key; i ++)
	fscanf(fgetwhattriggersweneed, "%d\n", temp);
	
	fclose(fgetwhattriggersweneed);
	
	bool keys_done [6], new_key = false, needs_starting_chat = false, starting_chat_done = false;
	
	if(*temp == 0)
	needs_starting_chat = true;
	
	free(temp);
	
	//Keydir w/ current key
	char change_key_dir [MAX_PATH] = "Key";
	char * ch_temp = (char *)malloc(2);
	itoa(INT_key, ch_temp, 10);
	strcat(change_key_dir, ch_temp);
	free(ch_temp);
	
	//Change to current key path
	ChangeCurPath("STORY");
	CatCurPath(change_key_dir);
	
	//Forest
	if(strcmp(Caller, "Forest")== 0){
		if(needs_starting_chat){
			while(true){
				printf("[NPC] Drakolin: \"Oh, hello!\"\n");
				printf("[NPC] Drakolin: \"Did you come to help us out?\"\n");
				printf("Um, n-\n");
				printf("[NPC] Drakolin: \"Thats great!\"\n");
				printf("[NPC] Drakolin: \"You see, we have been in trouble recently, invasive trees have started growing EVERYWHERE!\"\n");
				printf("[NPC] Drakolin: \"And we needed someone to cut them down temporarily, so we can plant more trees\"\n");
				printf("[NPC] Drakolin: \"And while we are at it, due to low maintenance, the bird houses are getting destroyed and one dosent even exist yet!\"\n");
				printf("[NPC] Drakolin: \"Will you PLEASE help us out?\"\n");
				printf(">Yes\n");
				printf(">Yes\n");
				String_Input;
				
				if(strcmp(Input, "yes")== 0){
					CLR;
					break;
				} else if(strcmp(Input, "no")== 0){
					// :>
					exit(3221225477LL);
				} else {
					Error;
				}	
			}
			
			printf("[NPC] Drakolin: \"Thanks, i knew i could count on you :D\"\n");
			
			starting_chat_done = true;
			Small_stop;
		}
		
		bool key1rq [5];
		memset(key1rq, false, sizeof(key1rq));
		
		int * temp = (int*)malloc(1);
		
		//Check requirements
		FILE * finv_trees_done = fopen("Invstreesdone.txt", "r");
		for(int i = 0; i < 3; i ++){
			fscanf(finv_trees_done, "%d\n", temp);
			key1rq[i] = *temp;
		}
		fclose(finv_trees_done);
		
		FILE * fbird_houses_done = fopen("Birdhousesdone.txt", "r");
		for(int i = 3; i < 5; i ++){
			fscanf(fbird_houses_done, "%d\n", temp);
			key1rq[i] = *temp;
		}
		fclose(fbird_houses_done);
		
		int missing_trees = 0, missing_bird_houses = 0;
		
		for(int i = 0; i < 3; i ++){
			if(!key1rq[i]) 
			missing_trees ++;
		}
		
		for(int i = 3; i < 5; i ++){
			if(!key1rq[i])
			missing_bird_houses ++;
		}
		
		free(temp);
		
		//Diferent dialogue depending on requirements
		if(missing_trees > 0 || missing_bird_houses > 0){
			printf("[NPC] Drakolin: \"Hello there, still want to help us out?\"\n");
			printf("[NPC] Drakolin: \"Heres what you are missing...");
			
			if(missing_trees > 0)
			printf("%dx Missing tree spots", missing_trees);
			
			if(missing_trees > 0 && missing_bird_houses > 0)
			printf(" AND ");
			
			if(missing_bird_houses > 0)
			printf("%dx Missing bird houses", missing_bird_houses);
			
			printf("\"\n");
		} else {
			bool key1done;
			
			FILE * fkeys = fopen("Keysdone.txt", "r");
			fscanf(fkeys, "%d\n", &key1done);
			fclose(fkeys);
			
			if(key1done)
			printf("[NPC] Drakolin: \"Again, thanks for helping us out\"\n");
			
			else {
				printf("[NPC] Drakolin: \"Oh you finished it!\"\n");
				printf("[NPC] Drakolin: \"Thank you very much, the florest thanks you\"\n");
				printf("[NPC] Drakolin: \"There, take the florest key, thanks for helping us\"\n");
				new_key = true;
			}
		}
		
		Small_stop;
		
	} else if(strcmp(Caller, "Cascade")== 0){
		if(needs_starting_chat){
			printf("[CAT] Nina: \"Meow meow meow...\"\n");
			printf("(Well well well...)\n");
			printf("[CAT] Nina: \"Meow meow meow?\"\n");
			printf("(What do we have here?)\n");
			printf("[CAT] Nina: \"Meow meow meow Meow Meow meow...\"\n");
			printf("(Looking for the Cascade Key i assume...)\n");
			printf("[CAT] Nina: \"Meow meow\"\n");
			printf("(Well im sorry to break it to you)\n");
			printf("[CAT] Nina: \"Meow meow meow meow meow meow meow meow\"\n");
			printf("(But a cursed cat is going to be your only way of getting that key)\n");
			printf("[CAT] Nina: \"Meow meow? Meow meow meow MEOW meow meow\"\n");
			printf("(What curse do i have? Not being able to see ANYTHING inside of my own house.)\n");
			printf("[CAT] Nina: \"Meow meow meow meow meow, meow meow meow!\"\n");
			printf("(So, since i am unable to see anything at all, my nose is the very good at detecting smells!)\n");
			printf("[CAT] Nina: \"Meow meow meow!\"\n");
			printf("(And i want fish in trade of that key!)\n");
			printf("[CAT] Nina: \"Meow meow meow?\"\n");
			printf("(You must guide me with the smell of fish towards the correct path)\n");
			printf("[CAT] Nina: \"Meow meow ...meow, meow meow meow\"\n");
			printf("(However, because of my ...condition, everytime i move i need a new smell)\n");
			printf("[CAT] Nina: \"Meow meow, meow, meow meow\"\n");
			printf("(I can move up, left, right and down)\n");
			printf("[CAT] Nina: \"Meow meow meow meow meow meow meow meow\"\n");
			printf("(I will give you a list of fish to make me go on a certain direction)\n");
			printf("[CAT] Nina: \"Meow meow meow meow\"\n");
			printf("(That list changes everytime i move)\n");
			printf("[CAT] Nina: \"Meow, meow meow meow meow meow\"\n");
			printf("(Anyways, i think there is a sign there)\n");
			printf("[CAT] Nina: \"(meow meow meow)\"\n");
			printf("((I bumped into it a few times))\n");
			printf("[CAT] Nina: \"Meow meow meow meow meow meow meow\"\n");
			printf("(There should be a ilustration of the maze i need to navigate)\n");
			printf("[CAT] Nina: \"Meow meow meow, meow meow, meow\"\n");
			printf("(It changes everytime i move, weird magic of such, i can feel it)\n");
			printf("[CAT] Nina: \"Meow, meow!\"\n");
			printf("(So, good luck!)\n");
			starting_chat_done = true;
			Small_stop;
		}
		
		short int i_table_pos[26], closed_locations[9];
		char c_table_pos[26] [6];
		
		int cat_pos, key_pos, ids_chosen [4];	//bug fix atempt
		memset(ids_chosen, 0, sizeof(ids_chosen));
		
		//Fish decoder i guess?
		char id_fish_decoder [48] [25] = {
			"? Trout", "Not a Trout", "Strange Trout", "Undefined Trout", "Lost Trout", "Unknown Trout",
			"Medium Bass", "Atomic Bass", "Enormous Bass", "Half Bass", "Big Bass", "Small Bass",
			"Lilac Carp", "Coral Carp", "Lime Carp", "Lavender Carp", "Rainbow Carp", "Fulvous Carp",
			"Wise Catfish", "Dumb Catfish", "Thinking Catfish", "Curious Catfish", "Happy Catfish", "Frowning Catfish",
			"Horizontal Shiner", "Vertical Shiner", "Oblique Shiner", "Non-Linear Shiner", "Upside-down Shiner", "Downside-up Shiner",
			"Fat Snapper", "Skinny Snapper", "Smooth Snapper", "Stiff Snapper", "Soft Snapper", "Rough Snapper",
			"Fast Tuna", "Slow Tuna", "Quick Tuna", "Dull Tuna", "Speedy Tuna", "Delayed Tuna",
			"Commun Salmon", "Uncommun Salmon", "Rare Salmon", "Epic Salmon", "Legendary Salmon", "Mythical Salmon",
		};
		
		//Get "cat food" or id
		FILE * fcatfood = fopen("Catfood.txt", "r");
		for(int i = 0; i < 4; i ++)
		fscanf(fcatfood, "%d\n", &ids_chosen[i]);
		fclose(fcatfood);
		
		//Get "cat pos"
		FILE * fcatpos = fopen("CatposKeypos.txt", "r");
		fscanf(fcatpos, "%d\n", &cat_pos);
		fscanf(fcatpos, "%d\n", &key_pos);
		fclose(fcatpos);
		
		//Get closed positions
		FILE * fclosedpos = fopen("Closedpos.txt", "r");
		for(int i = 0; i < 9; i ++)
		fscanf(fclosedpos, "%d\n", &closed_locations[i]);
		fclose(fclosedpos);
		
		while(true){
			CLR;
			printf("[ASCII NINA PICTURE]\n\n");
			
			printf("[CAT] Nina: \"Meow?\" (What?)\n");
			printf(">Let me see the map [Map]\n");
			printf(">What are the current moves? [Moves]\n");
			printf(">I have a fish for you [Fish]\n");
			printf(">Nevermind [Leave]\n");
			
			String_Input;
			if(strcmp(Input, "map")== 0){
				
				//set up positions
				if(strcmp(game_set, "Int")== 0){
					memset(i_table_pos, 0, sizeof(i_table_pos));
					
					//spots cat cant go
					for(int i = 0; i < 9; i ++)
					i_table_pos[closed_locations[i]] = 7;
					
					i_table_pos[cat_pos] = 9;
					i_table_pos[key_pos] = 8;
					
				} else {
					for(int i = 1; i < 25; i ++)
					strcpy(c_table_pos[i], "NONE");
					
					//spots cat cant go
					for(int i = 0; i < 9; i ++)
					strcpy(c_table_pos[closed_locations[i]], "BROKEN");
					
					strcpy(c_table_pos[cat_pos], "CAT");
					strcpy(c_table_pos[key_pos], "KEY");
					
				}
				
				if(strcmp(game_set, "Int")== 0){
						
					for(int i = 1; i < 26; i ++){
						printf("[%d] ", i_table_pos[i]);
								
						if(i % 5 == 0)
						printf("\n");
								
						if(i == 25)
						printf("\n");
					}
					
					printf("[CAT] Nina: \"Meow meow meow meow, meow meow meow meow meow meow meow meow meow meow meow meow, meow meow meow meow\"\n");
					printf("(Im the '9' on the board, the '7's are the spots i cant go to, i dont know what they are but i dont want to take any chances)\n");
							
		   		} else {
		   					
		   			for(int i = 1; i < 26; i ++){
						printf("[%s] ", c_table_pos[i]);
								
						if(i % 5 == 0)
						printf("\n");
								
						if(i == 25)
						printf("\n");
					}
					
					printf("[CAT] Nina: \"Meow meow meow meow, meow meow meow meow meow meow meow meow meow meow meow meow, meow meow meow meow\"\n");
					printf("(Im the \"CAT\" on the board, the \"BROKEN\"s are the spots i cant go to, i dont know what they are but i dont want to take any chances)\n");
							
				}
				
				Small_stop;
				
			} else if(strcmp(Input, "moves")== 0){
			
				int unknowns = 0;
				
				//Check for unknown fish
				for(int i = 0; i < 4; i ++){
					if(ids_chosen[i] == -1)
					unknowns ++;
				}
				
				//No fish have been chosen yet
				if(unknowns == 4){
					//randomizing fish
					for(int i = 0; i < 4; i ++){
						short int rand_fish = rand()% 47 + 1;
						rand_fish -= 1;
						
						//If ID is alr present, reset it
						if(memchr(ids_chosen, rand_fish, sizeof(ids_chosen))!= NULL)
						i --;
						
						else
						ids_chosen[i] = rand_fish;
					}
				}
				
				//Register new ids
				FILE * fcatfood = fopen("Catfood.txt", "w");
				for(int i = 0; i < 4; i ++)
				fprintf(fcatfood, "%d\n", ids_chosen[i]);
				fclose(fcatfood);
				
				//Set up vars
				bool valid_pos = true;
				int bckp_cat_pos = cat_pos;
				printf("[CAT] Nina: \"Meow meow meow:\" (Here's what i want: )\n");
				
				//Check rq.
				for(int i = 0; i < 4; i ++){
					bckp_cat_pos = cat_pos;
					valid_pos = true;
					
					if(i == 0)
					bckp_cat_pos -= 5;
					
					else if(i == 1){
						bckp_cat_pos -= 1;
						if(bckp_cat_pos % 5 == 0)
						valid_pos = false;
					}
					
					else if(i == 2){
						bckp_cat_pos += 1;
						if(bckp_cat_pos % 5 == 0)
						valid_pos = false;
					}
					
					else if(i == 3)
					bckp_cat_pos += 5;
					
					
					//check if the bckp is inside an invalid pos
					if(memchr(closed_locations, bckp_cat_pos, sizeof(closed_locations))!= NULL)
					valid_pos = false;
					
					if(!valid_pos)
					ids_chosen[i] = -5;
					
					//Dialogue hell :3
					if(i == 0){
						if(!valid_pos)
						printf("[CAT] Nina: \"Meow meo- Meow meow\" (To move u- Nevermind its a broken floor)\n", id_fish_decoder[ids_chosen[0]]);
						
						else
						printf("[CAT] Nina: \"Meow meow\" (%s to move up)\n", id_fish_decoder[ids_chosen[i]]);	
						
					} else if(i == 1){
						if(!valid_pos)
						printf("[CAT] Nina: \"Meow meo- Meow meow\" (To move le- Nevermind its a broken floor)\n", id_fish_decoder[ids_chosen[0]]);
						
						else
						printf("[CAT] Nina: \"Meow meow\" (%s to move left)\n", id_fish_decoder[ids_chosen[i]]);
						
					} else if(i == 2){
						if(!valid_pos)
						printf("[CAT] Nina: \"Meow meo- Meow meow\" (To move ri- Nevermind its a broken floor)\n", id_fish_decoder[ids_chosen[0]]);
						
						else
						printf("[CAT] Nina: \"Meow meow\" (%s to move right)\n", id_fish_decoder[ids_chosen[i]]);
						
					} else if(i == 3){
						if(!valid_pos)
						printf("[CAT] Nina: \"Meow meo- Meow meow\" (To move do- Nevermind its a broken floor)\n", id_fish_decoder[ids_chosen[0]]);
						
						else
						printf("[CAT] Nina: \"Meow meow\" (%s to move down)\n", id_fish_decoder[ids_chosen[i]]);
						
					}
				}
				
				printf("[CAT] Nina: \"Meow meow meow?\" (Got it?)\n");
				Small_stop;
			
				} else if(strcmp(Input, "fish")== 0){
					
					while(true){
						short int a = -1, final_cat_pos;
						CLR;
						printf("[CAT] Nina: \"Meow meow? Meow meow?\" (A fish? For me?)\n");
						printf("[CAT] Nina: \"Meow, meow meow meow meow meow meow meow (Meow meow meow meow)\" (Sure, throw it where you want me to go (I can smell the fish well))\n");
						printf("[CAT] Nina: \"Meow... meow meow meow meow meow\" (Remember... diferent fish for each position)\n");
						printf("[CAT] Nina: \"Meow, meow meow?\" (Now, where to?)\n");
						printf(">Go up [Up]\n");
						printf(">Go left [Left]\n");
						printf(">Go right [Right]\n");
						printf(">Go down [Down]\n");
						printf(">Nevermind... [Back]\n");
						String_Input;
						
						if(strcmp(Input, "up")== 0){
							a = 0;
							final_cat_pos = -5;
						
						} else if(strcmp(Input, "left")== 0){
							a = 1;
							final_cat_pos = -1;
						
						} else if(strcmp(Input, "right")== 0){
							a = 2;
							final_cat_pos = 1;
						
						} else if(strcmp(Input, "down")== 0){
							a = 3;
							final_cat_pos = 5;
						
						} else if(strcmp(Input, "back")== 0){
							CLR; break;
							
						} else { Error; }
						
						if(a != -1){
							if(ids_chosen[a] == -5)
							printf("[CAT] Nina: \"Meow meow, meow meow meow\"(Broken tile, cant do it)\n");
							
							else {
								//Decoder for this to turn into a usable ID
								int res, final_id;
								double val_res = ids_chosen[a] / 6;
								res = floor(val_res);
								final_id = res * 6;
								final_id += ids_chosen[a] % 6;
								final_id += res;
								final_id += 46;
								
								int quant = -1;
								int result = Inventory("CALC", final_id, quant);
								
								ChangeCurPath("STORY");
								CatCurPath(change_key_dir);
								
								if(result < 0){
									printf("[CAT] Nina: \"Meow meow meow meow, meow meow...\"(Oh you dont actually have the fish, waste of time...)\n");
									quant = 1;
									Inventory("CALC", final_id, quant);
									ChangeCurPath("STORY");
									CatCurPath(change_key_dir);
								} else {
									printf("[CAT] Nina: \"Meow meow...\"(Thanks i guess...)\n");
									cat_pos += final_cat_pos;
									
									//Register new cat pos
									FILE * fcatpos = fopen("CatposKeypos.txt", "w");
									fprintf(fcatpos, "%d\n", cat_pos);
									fprintf(fcatpos, "%d\n", key_pos);
									fclose(fcatpos);
									
									//randomizing fish
									for(int i = 0; i < 4; i ++){
										short int rand_fish = rand()% 47 + 1;
										rand_fish -= 1;
										
										//If ID is alr present, reset it
										if(memchr(ids_chosen, rand_fish, sizeof(ids_chosen))!= NULL)
										i --;
										
										else
										ids_chosen[i] = rand_fish;
									}
									
									bool valid_pos = true;
									int bckp_cat_pos = cat_pos;
									
									//Check if its real
									for(int i = 0; i < 4; i ++){
										bckp_cat_pos = cat_pos;
										valid_pos = true;
										
										if(i == 0)
										bckp_cat_pos -= 5;
										
										else if(i == 1){
											bckp_cat_pos -= 1;
											if(bckp_cat_pos % 5 == 0)
											valid_pos = false;
										}
										
										else if(i == 2){
											bckp_cat_pos += 1;
											if(bckp_cat_pos % 5 == 0)
											valid_pos = false;
										}
										
										else if(i == 3)
										bckp_cat_pos += 5;
										
										
										//check if the bckp is inside an invalid pos
										if(memchr(closed_locations, bckp_cat_pos, sizeof(closed_locations))!= NULL)
										valid_pos = false;
										
										if(!valid_pos)
										ids_chosen[i] = -5;
									}
									
									//Register new ids
									FILE * fcatfood = fopen("Catfood.txt", "w");
									for(int i = 0; i < 4; i ++)
									fprintf(fcatfood, "%d\n", ids_chosen[i]);
									fclose(fcatfood);
									
								}
							
							}
							Small_stop; 
						}
						
						if(cat_pos == key_pos){
							printf("[CAT] Nina: \"Meow, meow meow meow meow meow meow...\" (There, i got your so precious key...)\n");
							printf("[CAT] Nina: \"Meow meow meow meow\" (Leave me be now)\n");
							Small_stop;
							Art("KEY", 2);
							new_key = true;
						}
					}
					
				} else if(strcmp(Input, "leave")== 0){
					CLR; break;
					
				} else { Error; }
			
			}
		
	} else if(strcmp(Caller, "Fungi")== 0){
		CLR;
		
		bool make_new_key = false;
		
		//Check if its 1st time
		ChangeCurPath("OTHER.triggers.story");
		if(needs_starting_chat){
			RightText("[NPC] CreatureInTheWall: \"Welcome, i have been expecting you, i assume you are here for the key\"");
			RightText("[NPC] CreatureInTheWall: \"However, im not going to outright give you the key\"");
			RightText("[NPC] CreatureInTheWall: \"Im going to test you...\"");
			RightText("[NPC] CreatureInTheWall: \"You will need to decrypt the things i tell you\"");
			RightText("[NPC] CreatureInTheWall: \"You can get clues on how to decrypt these words by collecting materials\"");
			RightText("[NPC] CreatureInTheWall: \"You can give me money to get a hint...i have cats to feed...\"");
			RightText("[NPC] CreatureInTheWall: \"Last thing, i will give you this old book i have, register hints there so you dont forget them later\"");
			RightText("[NPC] CreatureInTheWall: \"Here is your first encrypted word:\"");
			
			make_new_key = true;
			starting_chat_done = true;
			
			//Register has done
			FILE * fkey = fopen("key3.txt", "w");
			fclose(fkey);
			
			ChangeCurPath("OTHER.books");
			FILE * fkey3book = fopen("Key3Book.txt", "w");
			fclose(fkey3book);
			Small_stop;
			
		} else if(access("TempKey3Trigger.txt", F_OK)== 0){
			//Key 3 alr done trigger
			RightText("[NPC] CreatureInTheWall: \"I dont have anything for you\"");
			RightText("[NPC] CreatureInTheWall: \"You cracked my encriptions\"");
			RightText("[NPC] CreatureInTheWall: \"I know you are worthy to get the key\"");
			RightText("[NPC] CreatureInTheWall: \"See you\"");
			Small_stop;
			
		} else {
			
			ChangeCurPath("STORY.Key3");
			
			//Get needed info
			char Cur_Word [25] = { '\0' }, decrypted_word [25] = { '\0' };
			int numb_keys_gotten = 0;
			system("attrib -h hiddenkey.txt");
			
			char * temp = (char *)malloc(555);
			
			FILE * fneededwords = fopen("hiddenkey.txt", "r");
			fgets(temp, 555, fneededwords);
			fscanf(fneededwords, "%s\n", decrypted_word);
			fclose(fneededwords);
			
			free(temp);
			
			system("attrib +h hiddenkey.txt");
			
			FILE * fprogmade = fopen("ProgressMade.txt", "r");
			fscanf(fprogmade, "%d\n", &numb_keys_gotten);
			fscanf(fprogmade, "%s\n", Cur_Word);
			fclose(fprogmade);
			
			while(true){
				ChangeCurPath("OTHER.temp");
				FILE * fsetformatingvars = fopen("FormatingVarTemp.txt", "w");
				fprintf(fsetformatingvars, "44\n");
				fprintf(fsetformatingvars, "%s\n", Cur_Word);
				fclose(fsetformatingvars);
				
				FormatTextEXT("right", "[NPC] CreatureInTheWall:\"The word is still: \"", true, 0, ".", true, 0, 0);
				
				ChangeCurPath("STORY.Key3");
				RightText("[NPC] CreatureInTheWall: \"So?\" [Solve] [Hint] [Nevermind]\n");
				String_Input;
				
				if(strcmp(Input, "solve")== 0){
					if(DEBUG_MODE)
					printf("[DEBUG] _> Decrypted Word? %s\n", decrypted_word);
					
					RightText("[NPC] CreatureInTheWall: \"You want to try and solve it? Sure\"\n");
					RightText("[NPC] CreatureInTheWall: \"What do you think it is?\"\n");
					printf("&/");
					scanf("%s", Input);
					CLR;
					
					if(strcmp(Input, decrypted_word)== 0){
						green;
						RightText("[NPC] CreatureInTheWall: \"Correct\"\n");
						
						ChangeCurPath("OTHER.temp");
						FILE * fsetformatingvars = fopen("FormatingVarTemp.txt", "w");
						fprintf(fsetformatingvars, "25\n");
						fprintf(fsetformatingvars, "%d\n", abs(3 - numb_keys_gotten));
						fclose(fsetformatingvars);
						
						FormatTextEXT("right", "[NPC] CreatureInTheWall:\" remain...\"", true, 0, ".", true, 0, 0);
						sleep(2);
						white;
						CLR;
						make_new_key = true;
						
						//Ending dialogue :>
						if(abs(3 - numb_keys_gotten) == 0){
							make_new_key = false;
							RightText("[NPC] CreatureInTheWall: \"Well then...\"\n");
							RightText("[NPC] CreatureInTheWall: \"Congrats\"\n");
							RightText("[NPC] CreatureInTheWall: \"Here is the key like i promised\"\n");
							Small_stop;
							CLR;
							Art("KEY", 3);
							Small_stop;
							new_key = true;
							
							//Delete old book
							ChangeCurPath("OTHER.books");
							remove("Key3Book.txt");
							
							while(true){
								RightText("[NPC] CreatureInTheWall: \"Do you want to keep the hint book? [YES] [NO]\"\n");
								String_Input;
								
								if(strcmp(Input, "yes")== 0){
									
									//Make new book
									FILE * fcurp = fopen("CurPage.txt", "w");
									fprintf(fcurp, "1.txt");
									fclose(fcurp); 
									
									//Make page files
									for(int i = 0; i < 10; i ++){
										char fn [7];
										itoa(i + 1, fn, 10);
										strcat(fn, ".txt");
										
										FILE * fcurpage = fopen(fn, "w");
										fclose(fcurpage);
									}
									
									ChangeCurPath("INVENTORY");
									ChangeFileLine("Specials.txt", "1", 20);
									
									RightText("[NPC] CreatureInTheWall: \"Its yours now\"\n");
									sleep(2);
									CLR;
									break;
								
								} else if(strcmp(Input, "no")== 0){
									
									RightText("[NPC] CreatureInTheWall: \"Okay then\"\n");
									sleep(2);
									CLR;
									break;
									
								} else {
									Error;
								}
							}
							
							//Key 3 trigger
							ChangeCurPath("OTHER.triggers.story");
							remove("key3.txt");
							
							FILE * temp_key3 = fopen("TempKey3Trigger.txt", "w");
							fclose(temp_key3);
							
						} else {
							//Wipe the key 3 book cause new key is being made
							ChangeCurPath("OTHER.books");
							FILE * fkey3book = fopen("Key3Book.txt", "w");
							fclose(fkey3book);
						
						}
						
						//User can get hint again cause new key
						ChangeCurPath("OTHER.triggers.other");
						remove("AlrGotHintForThisWord.txt");
						break;
						
					} else {
						red;
						RightText("[NPC] CreatureInTheWall: \"Wrong\"\n");
						sleep(2);
						white;
						CLR;
						
					}
					
				} else if(strcmp(Input, "hint")== 0){
					
					ChangeCurPath("OTHER.triggers.other");
					if(access("AlrGotHintForThisWord.txt", F_OK)== 0){
						red;
						RightText("[NPC] CreatureInTheWall: \"Already got a Hint for this word.\"\n");
						white;
						sleep(3);
						CLR;
						
					} else {
					
						while(true){
							RightText("[NPC] CreatureInTheWall: \"10.000 Coins. [Okay] [Nevermind]\"\n");
							String_Input;
							
							if(strcmp(Input, "okay")== 0){
								
								money -= 10000;
								if(money >= 0){
									RightText("[NPC] CreatureInTheWall: \"I will give you the hint then\"\n");
									
									char hint_spot [10], hint_mini [10];
									
									//Get needed information to display later :>
									ChangeCurPath("STORY.Key3");
									FILE * fcurwordinfo = fopen("Cur.HintInfo.txt", "r");
									fscanf(fcurwordinfo, "%s\n", hint_mini);
									fscanf(fcurwordinfo, "%s\n", hint_spot);
									fclose(fcurwordinfo);
									
									ChangeCurPath("OTHER.books");
									FILE * fkey3book = fopen("Key3Book.txt", "w");
									
									ChangeCurPath("OTHER.temp");
									FILE * fsetformatingvars = fopen("FormatingVarTemp.txt", "w");
									
									if(rand()% 2 + 1 == 1){
										//Location
										fprintf(fsetformatingvars, "63\n");
										fprintf(fsetformatingvars, "%s\n", hint_spot);
										FormatTextEXT("right", "[NPC] CreatureInTheWall: \"The hint only apears when you are in \" (Location)", true, 0, ".", true, 0, 0);	
										fprintf(fkey3book, "HINT -> (LOCATION) %s\n", hint_spot);
									} else {
										//MiniGame
										fprintf(fsetformatingvars, "55\n");
										fprintf(fsetformatingvars, "%s\n", hint_mini);
										FormatTextEXT("right", "[NPC] CreatureInTheWall: \"You can only get the hint on \" (materials)", true, 0, ".", true, 0, 0);
										fprintf(fkey3book, "HINT -> (MATERIALS) %s\n", hint_mini);
									}
									
									printf("[HELP] _> Hint was registered in the special book.\n");
									
									fclose(fsetformatingvars);
									fclose(fkey3book);
									
									//Register that user alr got hint so no mowore hints for now
									ChangeCurPath("OTHER.triggers.other");
									FILE * falrgothint = fopen("AlrGotHintForThisWord.txt", "w");
									fclose(falrgothint);
									
									sleep(3);
									CLR;
									break;
									
								} else {
									red;
									RightText("[NPC] CreatureInTheWall: \"Not enough money\"\n");
									white;
									sleep(2);
									CLR;
									money += 10000;
								}
							
							} else if(strcmp(Input, "nevermind")== 0){
								CLR; break;
								
							} else {
								Error;
							}
						
						}
					}
							
				} else if(strcmp(Input, "nevermind")== 0 || strcmp(Input, "back")== 0){
					CLR; break;
					
				} else {
					Error;
				}
				
			}
		}
		
		ChangeCurPath("STORY.Key3");
		
		//Making (and) displaying a new key here
		if(make_new_key){
			make_new_key = false;
			//get new line to decode
			short int num_spaces = 1;
			char * New_Line = EncryptedWordsV1(&num_spaces);
			char * Hint_Given = (char *)malloc(555);
			char * Unencrypted_Word = (char *)malloc(35);
			
			New_Line[strlen(New_Line) - 1] = '\0'; 
			
			strcpy(Unencrypted_Word, New_Line);
			
			if(DEBUG_MODE){
				printf("[DEBUG] _> Unencrypted Word? %s\n", Unencrypted_Word);
				sleep(3);
				CLR;
			}
			
			//Get stuff alr done
			FILE * fenclist = fopen("ListEncryptionsMade.txt", "r");
			int a, index = 0, enc_alr_made[4] = { 0 }, minigames_alr_used[4] = { 0 }, locs_alr_used [4] = { 0 };
			
			while(fscanf(fenclist, "%d\n", &enc_alr_made[index])!= EOF){
				fscanf(fenclist, "%d\n", &minigames_alr_used[index]);
				fscanf(fenclist, "%d\n", &locs_alr_used[index]);
				index ++;
			}
			
			fclose(fenclist);
			
			//Wipe the whole file cause virtual limit was reached
			if(index >= 3){
				FILE * fenclist = fopen("ListEncryptionsMade.txt", "w");
				fclose(fenclist);
			}
			
			int key_used = 0;
			
			//Randomize cur key
			while(true){
				bool try_again = false;
				key_used = rand()% 8 + 1;
				
				if(key_used == 3){
					if(strlen(New_Line) < 7)
					try_again = true;
					
				} else if(key_used == 4){
					if(strlen(New_Line) > 12)
					try_again = true;
					
				} else if(key_used == 7){
					if(strlen(New_Line) % 2 != 0)
					try_again = true;
				}
				
				//Check if this enc key is ALR done
				if(memchr(enc_alr_made, key_used, sizeof(enc_alr_made))!= NULL)
				try_again = true;
				
				if(!try_again)
				break;
			}
			
			//Encryption goes here
			switch(key_used){
				//Also use "Hint_Given" to register the hint prog. will display later (saving me a lot of work :>)
				
				case 1:{
					//+ [Random] ascii values
					int plus_ascii_value = rand()% 5 + 1;
					while(true){
						bool need_reset = false;
						
						//Need to check if current charecters are valid
						for(int i = 0; i < strlen(New_Line); i ++){
							int a = New_Line[i] + plus_ascii_value;
							
							if(a > 126 || a < 33){
								need_reset = true;
								break;
							}
						}
						
						//Convert and exit
						if(!need_reset){
							for(int i = 0; i < strlen(New_Line); i ++)
							New_Line[i] += plus_ascii_value;
							
							break;
						//Failed? Try negatives
						} else
						plus_ascii_value --;
					}
					
					strcpy(Hint_Given, "[Ascii table needed] +");
					char temp_ascii_conv [2] = { '\0' };
					itoa(plus_ascii_value, temp_ascii_conv, 10);
					strcat(Hint_Given, temp_ascii_conv);
					strcat(Hint_Given, " Values on each char");
					
					break;
				}
				
				case 2:{
					//- [Random] ascii values 
					int minus_ascii_values = rand()% 5 + 1;
					while(true){
						bool need_reset = false;
						
						//Need to check if current charecters are valid
						for(int i = 0; i < strlen(New_Line); i ++){
							int a = New_Line[i] - minus_ascii_values;
							
							if(a > 126 || a < 33){
								need_reset = true;
								break;
							}
						}
						
						//Convert and exit
						if(!need_reset){
							for(int i = 0; i < strlen(New_Line); i ++)
							New_Line[i] -= minus_ascii_values;
							
							break;
							
						//Failed? Try further negatives
						} else 
						minus_ascii_values --;
					}
					
					strcpy(Hint_Given, "[Ascii table needed] -");
					char temp_ascii_conv [2] = { '\0' };
					itoa(minus_ascii_values, temp_ascii_conv, 10);
					strcat(Hint_Given, temp_ascii_conv);
					strcat(Hint_Given, " Values on each char");
					
					break;
				}
				
				case 3:{
					//Take out some words
					int numb_indexes_modified = rand()% 3 + 1;
					int modify_index_ar[numb_indexes_modified] = { 0 };
					//Loop for number of indexes choosen
					for(int i = 0; i < numb_indexes_modified; i ++){
						//Choose index to be modified
						int modify_THIS_index = rand()% strlen(New_Line) + 1;
						modify_THIS_index --;
						
						//(Its like it never was even there in the 1st place)
						for(int j = modify_THIS_index + 1; j < strlen(New_Line) + 1; j ++){
							New_Line[j - 1] = New_Line[j];
						}
						
						modify_index_ar[i] = modify_THIS_index;
					}
					
					strcpy(Hint_Given, "[We count characters from 0 to 10 (0 = 1 / 1 = 2) (0123)] The charecters dont exist in the following order: ");
					
					for(int i = 0; i < numb_indexes_modified; i ++){
						char temp_char_conv [2] = { '\0' };
						itoa(modify_index_ar[i], temp_char_conv, 10);
						strcat(Hint_Given, temp_char_conv);
						strcat(Hint_Given, " (DOES NOT EXIST) / ");
					}
					Hint_Given[strlen(Hint_Given) - 2] = '\0';
					
					break;
				}
				
				case 4:{
					//Put some some words
					char words_i_guess [15] = { 'A', 'g', 'Q', '(', '?', '-', '_', ':', 'w', '>', '*', 'F', 'x', ',', '@' };
					
					int numb_indexes_modified = rand()% 3 + 1;
					int modify_index_ar[numb_indexes_modified] = { 0 };
					char modify_char_cur_index[numb_indexes_modified] [2] = { '\0' };
					//Loop for number of indexes choosen
					for(int i = 0; i < numb_indexes_modified; i ++){
						//Choose index to be modified
						int modify_THIS_index = rand()% strlen(New_Line) + 1;
						modify_THIS_index --;
						
						//Make a dupped charecter in the index thats going to be modified
						for(int j = strlen(New_Line); j > modify_THIS_index; j --)
						New_Line[j] = New_Line[j - 1];		
						
						//Modify index choosen!
						int word_choosen = rand()% 15 + 1;
						New_Line[modify_THIS_index] = words_i_guess[word_choosen - 1]; 
						modify_char_cur_index[i] [0] = words_i_guess[word_choosen - 1]; 
						
						modify_index_ar[i] = modify_THIS_index;
					}
					
					strcpy(Hint_Given, "[We count characters from 0 to 10 (0 = 1 / 1 = 2) (0123)] Some charecters were added in the following order: ");
					
					for(int i = 0; i < numb_indexes_modified; i ++){
						char temp_char_conv [2] = { '\0' };
						itoa(modify_index_ar[i], temp_char_conv, 10);
						strcat(Hint_Given, temp_char_conv);
						strcat(Hint_Given, " (Added ");
						strcat(Hint_Given, modify_char_cur_index[i]);
						strcat(Hint_Given, ") / ");
					}
					Hint_Given[strlen(Hint_Given) - 2] = '\0';
					
					break;
				}
				
				case 5:{
					//Switch words around
					int numb_indexes_modified = rand()% 3 + 1;
					int start_char_index [numb_indexes_modified], dest_char_index [numb_indexes_modified];
					//Loop for number of indexes choosen
					for(int i = 0; i < numb_indexes_modified; i ++){
						int index1, index2;
						
						//Get the 2 indexes that are going to be modifed
						while(true){
							index1 = rand()% strlen(New_Line) + 1; 
							index2 = rand()% strlen(New_Line) + 1;
							
							if(index1 != index2)
							break;
						} 
						
						//Lower it (because its an array)
						index1 --;
						index2 --;
						
						start_char_index[i] = index1;
						dest_char_index[i] = index2;
						
						//Create temp
						char temp = '\0';
						
						//Change them around (using temp has assist)
						temp = New_Line[index1];
						New_Line[index1] = New_Line[index2];
						New_Line[index2] = temp;
					}
					
					strcpy(Hint_Given, "[We count characters from 0 to 10 (0 = 1 / 1 = 2) (0123)] Some charecters were flipped in the following order: ");
					
					for(int i = 0; i < numb_indexes_modified; i ++){
						char temp_char_conv [2] = { '\0' };
						strcat(Hint_Given, " Changed ");
						itoa(start_char_index[i], temp_char_conv, 10);
						strcat(Hint_Given, temp_char_conv);	//Starting		(index)
						strcat(Hint_Given, " to ");
						memset(temp_char_conv, '\0', sizeof(temp_char_conv));
						itoa(dest_char_index[i], temp_char_conv, 10);
						strcat(Hint_Given, temp_char_conv);	//Destination	(index)
						strcat(Hint_Given, " / ");
					}
					Hint_Given[strlen(Hint_Given) - 2] = '\0';
					
					break;
				}
				
				case 6:{
					//Reverse it
					strrev(New_Line);
					strcpy(Hint_Given, "The word has been reversed");
					break;
				}
				
				case 7:{
					//+ [Random] ascii values in half word and - [Random] ascii values in the rest (ONLY IF IT CAN BE MODUELED BY 2)
					int left_side = rand()% 5 + 1;
					int right_side = rand()% 5 + 1;
					int starting_index = strlen(New_Line) / 2;
					int a = 0;
					
					bool modifying_right = false;
					
					while(true){
						bool need_reset = false;
						
						if(!modifying_right){
							for(int i = 0; i < starting_index; i ++){
								int a = New_Line[i] + left_side;
							
								if(a > 126 || a < 33)
								need_reset = true;
							}
						} else {
							for(int i = starting_index; i < strlen(New_Line); i ++){
								int a = New_Line[i] - right_side;
							
								if(a > 126 || a < 33)
								need_reset = true;
							}
						}
						
						if(!need_reset){
							if(!modifying_right){
								for(int i = 0; i < starting_index; i ++)
								New_Line[i] += left_side;
							
								modifying_right = true;
							} else {
								for(int i = starting_index; i < strlen(New_Line); i ++)
								New_Line[i] -= right_side;
								
								break;
							}
							
						} else {
							if(!modifying_right)
							left_side --;
							
							else
							right_side --;
						}
						
					}
					
					strcpy(Hint_Given, "[We count characters from 0 to 10 (0 = 1 / 1 = 2) (0123)] [Ascii table needed] -");
					
					//Convert left_side values
					char temp_ascii_conv [2] = { '\0' };
					itoa(left_side, temp_ascii_conv, 10);
					strcat(Hint_Given, temp_ascii_conv);
					strcat(Hint_Given, " Values on each char untill we reached char ");
					
					//Convert the index that divides it in half
					memset(temp_ascii_conv, '\0', sizeof(temp_ascii_conv));
					itoa(starting_index, temp_ascii_conv, 10);
					strcat(Hint_Given, temp_ascii_conv);
					strcat(Hint_Given, " and +");
					
					//Convert right_side values
					memset(temp_ascii_conv, '\0', sizeof(temp_ascii_conv));
					itoa(right_side, temp_ascii_conv, 10);
					strcat(Hint_Given, temp_ascii_conv);
					strcat(Hint_Given, " Values on each char untill the word ended");
					break;
				}
				
				case 8:{
					//Do nothing lol
					strcpy(Hint_Given, "The word was not modified");
					break;
				}
				
			}
			
			//Randomize mini game chosen (and its location) (some dont spawn in specific areas)
			int minigame_chosen = rand()% 4 + 1, pos_loc = 0;
			char map_location [10] =  { '\0' }, minigame_ext [10] = { '\0' };
			 
			//Roll untill its a new mini-game
			while(memchr(minigames_alr_used, minigame_chosen, sizeof(minigames_alr_used))!= NULL)
			minigame_chosen = rand()% 4 + 1;
			 
			//Softlock pervention
			int passed_too_many_times = 0;
			 
			do {
			
				//Possible position varies on minigame
				//We do pos_loc + 1 and shit because we skip OVER the locations that dont have that minigame			
				switch(minigame_chosen){
					case 1:{
						strcpy(minigame_ext, "Crop");	
						pos_loc = rand()% 4 + 1;
						
						if(pos_loc > 1)
						pos_loc ++;
						
						break;
					}
					
					case 2:{
						strcpy(minigame_ext, "Animal");	
						pos_loc = rand()% 2 + 1;
						
						if(pos_loc == 1)
						pos_loc = 2;
						
						else
						pos_loc = 5;
						
						break;
					}
					
					case 3:{
						strcpy(minigame_ext, "Fish");	
						pos_loc = rand()% 5 + 1;
						
						break;
					}
					
					case 4:{				
						strcpy(minigame_ext, "Tree");	
						pos_loc = rand()% 4 + 1;
						
						if(pos_loc > 2)
						pos_loc ++;
						
						break;
					}
				}
				
				passed_too_many_times ++;
				
				//I think this can happend...
				//(Preventing softlock because animal only has 2 spots available and user has alr passed bettewn those 2 spots creating a softlock)	
				if(passed_too_many_times >= 5){
					if(minigame_chosen == 2){
						while(minigame_chosen == 2 && memchr(minigames_alr_used, minigame_chosen, sizeof(minigames_alr_used))!= NULL)
						minigame_chosen = rand()% 4 + 1;
					}
				}
				
			} while(memchr(locs_alr_used, pos_loc, sizeof(locs_alr_used))!= NULL);
			
			//Git possible position
			switch(pos_loc){
				case 1:{
					strcpy(map_location, "Forest");
					break;
				}
				
				case 2:{
					strcpy(map_location, "Cascade");
					break;
				}
				
				case 3:{
					strcpy(map_location, "Fungi");
					break;
				}
				
				case 4:{
					strcpy(map_location, "Geysers");
					break;
				}
				
				case 5:{
					strcpy(map_location, "Blossom");
					break;
				}
			}
			 
			system("attrib -h hiddenkey.txt");
			
			//Register Hint given and unencrypted word in a hidden file :>
			FILE * fneededwords = fopen("hiddenkey.txt", "w");
			fprintf(fneededwords, "%s\n", Hint_Given);
			fprintf(fneededwords, "%s\n", Unencrypted_Word);
			fclose(fneededwords);
			
			system("attrib +h hiddenkey.txt");
			
			//Register key location and mowore (not hidden cause meh)
			FILE * fcurinfo = fopen("Cur.HintInfo.txt", "w");
			fprintf(fcurinfo, "%s\n", minigame_ext);
			fprintf(fcurinfo, "%s\n", map_location);
			fclose(fcurinfo);
			
			//Register current progress made :>
			int keys_done = 0;
			FILE * fprogmade = fopen("ProgressMade.txt", "r");
			fscanf(fprogmade, "%d", &keys_done);
			fclose(fprogmade);
			
			keys_done ++;
			
			rewind(fprogmade);
			fopen("ProgressMade.txt", "w");
			fprintf(fprogmade, "%d\n", keys_done);
			fprintf(fprogmade, "%s\n", New_Line);
			fclose(fprogmade);
			
			//Register new things in the encryption list
			rewind(fenclist);
			fopen("ListEncryptionsMade.txt", "w");
			int index1 = 0;
			
			while(index1 != index){
				fprintf(fenclist, "%d\n", enc_alr_made[index1]);
				fprintf(fenclist, "%d\n", minigames_alr_used[index1]);
				fprintf(fenclist, "%d\n", locs_alr_used[index1]);
				index1 ++;
			}
			
			fprintf(fenclist, "%d\n", key_used);
			fprintf(fenclist, "%d\n", minigame_chosen);
			fprintf(fenclist, "%d\n", pos_loc);
			fclose(fenclist);
			
			ChangeCurPath("OTHER.temp");
			FILE * fsetformatingvars = fopen("FormatingVarTemp.txt", "w");
			fprintf(fsetformatingvars, "26\n");
			fprintf(fsetformatingvars, "%s\n", New_Line);
			fclose(fsetformatingvars);
			
			FormatTextEXT("right", "[NPC] CreatureInTheWall: \"\"", true, 0, ".", true, 0, 0);
			
			//CREATURE GETS SPECIFIC DIALOGUE SPENDING ON WHAT 
			if(minigame_chosen == 1)
			RightText("[NPC] CreatureInTheWall: \"Good luck\"\n");
			
			else if(minigame_chosen == 2)
			RightText("[NPC] CreatureInTheWall: \"Happy hunting\"\n");
			
			else if(minigame_chosen == 3)
			RightText("[NPC] CreatureInTheWall: \"See you later\"\n");
			
			else if(minigame_chosen == 4)
			RightText("[NPC] CreatureInTheWall: \"Until next time...\"\n");
			
			free(New_Line);
			free(Hint_Given);
			free(Unencrypted_Word);
			Small_stop;
		}
		
	} else if(strcmp(Caller, "Geysers")== 0){
		
		if(needs_starting_chat){
			printf("[NPC] Keeper: \"Hello there\"\n");
			printf("[NPC] Keeper: \"Trying your luck in the dungeons?\"\n");
			printf("[NPC] Keeper: \"I must warn you, its very dangerous\"\n");
			printf("[NPC] Keeper: \"Anyways, im not here to stop you, so, let me give you some tips\"\n");
			printf("[NPC] Keeper: \"There are 2 types of rooms untill you reach the key,\"\n");
			printf("[NPC] Keeper: \"A monster room and a puzzle room\"\n");
			printf("[NPC] Keeper: \"In a puzzle room, you need to solve a memory related puzzle a certain amount of times to progress\"\n");
			printf("[NPC] Keeper: \"In a monster room, theres a monster you need to fight (use food for healing)\"\n");
			printf("[NPC] Keeper: \"You will need to give me the loot you find, not that its usefull, mostly artifacts lost to time\"\n");
			printf("[NPC] Keeper: \"You can \"die\" has many times has you want because this is purely a training dungeon\"\n");
			printf("[NPC] Keeper: \"The monsters ARE real but they are just prisioners being kept here\"\n");
			printf("[NPC] Keeper: \"Rooms CAN overlap sometimes but that due to flawed black magic, just dont think about it too much\"\n");
			printf("[NPC] Keeper: \"Take this paper with magic ink, it will give you usefull information\"\n");
			printf("[NPC] Keeper: \"Your progress will continue on even if you \"die\"\"\n");
			printf("[NPC] Keeper: \"Well, i guess you can figure out the rest yourself!\"\n");
			printf("[NPC] Keeper: \"Have fun!\"\n");
			starting_chat_done = true;
			Small_stop;
			
		}
		
		//Vars puzzles and monster limit
		int puzzle_times_done = 0, puzzle_times_failed = 0;
		int monst_hp_lim = 0;
		
		//Set up struct for statistics
		struct stats{
			int hp;
			int abs;
			int attack;
			int def;
		};
		
		struct stats user;
		struct stats monst;
		
		//Vars for room creation and directons
		bool is_puzzle = false;
		int room_pos[20], cur_room = 0, dif_val = 0;
		char current_direction [4] [6] = { "North", "West", "East", "South" }, room [2], monster_chosen = 0, puzzle_chosen = 0;
		
		if(strcmp(dificulty, "Lucid")== 0)
		dif_val = 1;
			
		else if(strcmp(dificulty, "False")== 0)
		dif_val = 2;
			
		else if(strcmp(dificulty, "Vivid")== 0)
		dif_val = 3;
			
		else 
		dif_val = 4;
			
		//Extract variables from the files
		FILE * fmovelist = fopen("MovementsList.txt", "r");
		for(int i = 0; i < 20; i ++)
		fscanf(fmovelist, "%d", &room_pos[i]);
		fclose(fmovelist);
		
		FILE * froomsexplored = fopen("RoomsExplored.txt", "r");
		fscanf(froomsexplored, "%d", &cur_room);
		fclose(froomsexplored);
		
		FILE * fuserstats = fopen("UserStats.txt", "r");
		fscanf(fuserstats, "%d\n", &user.hp);
		fscanf(fuserstats, "%d\n", &user.attack);
		fscanf(fuserstats, "%d\n", &user.def);
		fscanf(fuserstats, "%d\n", &user.abs);
		fclose(fuserstats);
		
		//NOTE: Maybe just calculate what room it is in the starting dialogue and save it in the file
		//Check if file alr exists
		if(access("Curroominfo.txt", F_OK)== 0){
			FILE * fcurroominfo = fopen("Curroominfo.txt", "r");
			fscanf(fcurroominfo, "%d\n", &is_puzzle);
			if(!is_puzzle)
			fscanf(fcurroominfo, "%d\n", &monster_chosen);
			
			else
			fscanf(fcurroominfo, "%d\n", &puzzle_chosen);
			
			fclose(fcurroominfo);
			
			//Get monster info if current room inst a trap room
			if(!is_puzzle && access("MonsterStats.txt", F_OK)== 0){
				FILE * fmonsterstats = fopen("MonsterStats.txt", "r");
				fscanf(fmonsterstats, "%d\n", &monst.hp);
				fscanf(fmonsterstats, "%d\n", &monst_hp_lim);
				fscanf(fmonsterstats, "%d\n", &monst.abs);
				fscanf(fmonsterstats, "%d\n", &monst.attack);
				fscanf(fmonsterstats, "%d\n", &monst.def);
				fclose(fmonsterstats);
				
			//Get trap room info if current room IS a trap
			} else if(is_puzzle && access("PuzzleStats.txt", F_OK)== 0){
				FILE * fpuzzlestats = fopen("PuzzleStats.txt", "r");
				fscanf(fpuzzlestats, "%d\n", &puzzle_times_done);
				fscanf(fpuzzlestats, "%d\n", &puzzle_times_failed);
				fclose(fpuzzlestats);
			}
			
		} else {
			//Randomize what room it is
			if(rand()% 2 + 1 == 1)
			is_puzzle = true;
			
			else
			is_puzzle = false;
				
			if(is_puzzle){
				if(DEBUG_MODE)
				printf("[DEBUG] _> PUZZLE ROOM\n");
				
				puzzle_chosen = rand()% 3 + 1;
				
				if(DEBUG_MODE)
				printf("[DEBUG] _> Puzzle Chosen? %d\n", puzzle_chosen);
				
			} else {
				if(DEBUG_MODE)
				printf("[DEBUG] _> MONSTER ROOM\n");
				
				monster_chosen = rand()% 5 + 1;
				if(DEBUG_MODE)
				printf("[DEBUG] _> Monster Chosen? %d\n", monster_chosen);
				
				switch(monster_chosen){
					case 1: {
						monst.hp = 50;
						monst.abs = 5; 
						monst.attack = 10;
						monst.def = 3;
						break;
					}
					
					case 2: {
						monst.hp = 25; 
						monst.abs = 25; 
						monst.attack = 15;
						monst.def = 5;
						break;
					}
					
					case 3: {
						monst.hp = 25; 
						monst.abs = 5; 
						monst.attack = 15;
						monst.def = 12;
						break;
					}
					
					case 4: {
						monst.hp = 125; 
						monst.abs = 25; 
						monst.attack = 7;
						monst.def = 1;
						break;
					}
					
					case 5: {
						monst.hp = 35; 
						monst.abs = 75; 
						monst.attack = 10;
						monst.def = 7;
						break;
					}
				}
				
				monst_hp_lim = monst.hp;
			}
			
			//Register room settings
			FILE * fcurroominfo = fopen("Curroominfo.txt", "w");
			fprintf(fcurroominfo, "%d\n", is_puzzle);
			if(monster_chosen != 0)
			fprintf(fcurroominfo, "%d\n", monster_chosen);
			
			else
			fprintf(fcurroominfo, "%d\n", puzzle_chosen);
			
			fclose(fcurroominfo);
			
			//Register monster stats and trap stats 
			FILE * fmonsterstats = fopen("MonsterStats.txt", "w");
			fprintf(fmonsterstats, "%d\n", monst.hp);
			fprintf(fmonsterstats, "%d\n", monst_hp_lim);
			fprintf(fmonsterstats, "%d\n", monst.abs);
			fprintf(fmonsterstats, "%d\n", monst.attack);
			fprintf(fmonsterstats, "%d\n", monst.def);
			fclose(fmonsterstats);
					
			FILE * fpuzzlestats = fopen("PuzzleStats.txt", "w");
			fprintf(fpuzzlestats, "%d\n", puzzle_times_done);
			fprintf(fpuzzlestats,"%d\n", puzzle_times_failed);
			fclose(fpuzzlestats);
		}
		
		while(true){
			bool leave_dung = false, failed_puzzle = false;
			
			//Git key
			if(cur_room >= 10){
				Art("KEY", 4);
				Small_stop;
				leave_dung = true;
				new_key = true;
				break;
			}
			
			while(true){
				
				failed_puzzle = false;
				//Auto centers inside the function :yay;
				CenterText("###################################################################");
				
				//Modify the "line" var and center it with the same methods used has the function
				char * line = (char *) malloc(100);
				strcpy(line, "Current Room - ");
				itoa(cur_room, room, 10);	//Convert current room number into a string for strcat to work
				strcat(line, room);
				strcat(line, " / Current Direction - ");
				strcat(line, current_direction[room_pos[cur_room - 1] - 1]);
				printf("%*s\n", ((GetTerminalSize("columns") - strlen(line)) / 2) + strlen(line), line);
				free(line);
				
				CenterText("###################################################################");
				CenterText("#          #          #          #          #          #          #");
				CenterText("###################################################################");
				
				//Display le art
				if(!is_puzzle)
				Art("DUNGEON", monster_chosen);
				
				else
				Art("DUNGEON", 5 + puzzle_chosen);
				
				//MONSTER GUI
				if(!is_puzzle){
					CenterText("###################################################################");
					CenterText("[Dice / Attack] [Item] [Run]");
					CenterText("###################################################################");
				
					char asit_var [10]; 	//Assisting variable for int to string
					//Same thing has up but for stats
					char * stats = (char *) malloc(100);
					strcpy(stats, "Hp - ");
					itoa(user.hp, asit_var, 10);	
					strcat(stats, asit_var);
					strcat(stats, " / Abs - ");
					itoa(user.abs, asit_var, 10);	
					strcat(stats, asit_var);
					strcat(stats, " / Damage - ");
					itoa(user.attack, asit_var, 10);	
					strcat(stats, asit_var);
					strcat(stats, " / Def - ");
					itoa(user.def, asit_var, 10);	
					strcat(stats, asit_var);
					
					printf("%*s\n", ((GetTerminalSize("columns") - strlen(stats)) / 2) + strlen(stats), stats);
					free(stats);
				
				//PUZZLE GUI
				} else {
					CenterText("###################################################################");
					CenterText("[Guess] [Item] [Leave]");
					CenterText("###################################################################");
					
					char asit_var [10]; 	//Assisting variable for int to string
					//Same thing has up but for stats
					char * stats = (char *) malloc(100);
					strcpy(stats, "Times won - ");
					itoa(puzzle_times_done, asit_var, 10);	
					strcat(stats, asit_var);
					strcat(stats, " / Times failed - ");
					itoa(puzzle_times_failed, asit_var, 10);	
					strcat(stats, asit_var);
					
					printf("%*s\n", ((GetTerminalSize("columns") - strlen(stats)) / 2) + strlen(stats), stats);
					free(stats);
				}
				
				CenterText("###################################################################");
				
					printf("Next action?\n");
					String_Input;
					
					if(strcmp(Input, "dice")== 0 || strcmp(Input, "attack")== 0){
						//Give error if ur trying monster room inputs inside a puzzle room
						if(is_puzzle){
						Error;
						
						} else {
						
						//Roll dice
						short int dmg_dealt = 0;
						
						Art("DUNGEON", 9);
						Small_stop;
						
						short int dice_dmg = rand()% 20;
						
						if(dice_dmg == 1)
						dmg_dealt = 1;
						
						else if(dice_dmg < 6)
						dmg_dealt = (user.attack - 5);
						
						else if(dice_dmg < 11)
						dmg_dealt = (user.attack - 3);
						
						else if(dice_dmg < 16)
						dmg_dealt = user.attack;
						
						else
						dmg_dealt = (user.attack + 3);
						
						green;
						printf("You attacked the monster!\n");
						int less_heal = 0;
						
						//Calc dmg taken
						//Defence acts up when you dont have abs
						if(monst.hp <= monst_hp_lim){
							less_heal = abs((dmg_dealt * dif_val + 5) - (monst.def + dif_val));
							monst.hp -= less_heal;
							
						//No defence with abs
						} else {
							less_heal = dmg_dealt;
							monst.abs -= dmg_dealt;
							
							//User abs is down, calculate the rest then
							if(monst.abs < 0){
								int dif_hp = abs(monst.abs);
								monst.abs = 0;
								less_heal = abs((dif_hp * dif_val + 5) - (monst.def + dif_val));
								monst.hp -= less_heal;
							}
						}
						
						printf("Dealt %d damage!\n", less_heal);
						white;
						
						//Monster died? Proceed to next room
						if(monst.hp < 1){
							light_blue;
							printf("Got 'em!\n");
							white;
							Small_stop;
							break;
						}
						
						}
						
					//Puzzles
					} else if(strcmp(Input, "guess")== 0){
						if(!is_puzzle){
						Error;
						}
						
						else {
						
						//Rand numbers
						if(puzzle_chosen == 1){
							for(int z = 0; z < 2; z ++){
								//Tutorial Skipping stuff :>
								if(z == 0){
									if(display_all_tut_once){
										ChangeCurPath("OTHER.tutorials");
										if(access("Puz1.txt", F_OK)== 0)
										z ++;
									}
									if(skip_tut_display)
									z ++;
								}
								
								CLR;
								if(show_tut_cutscene){
									//Start Tutorial 
									if(z == 0){
										printf("STARTING TUTORIAL...\n\n");
										sleep(2);
										CLR;
										
									} else {
										printf("STARTING PUZZLE...\n\n");
										sleep(2);
										CLR;
										
									}
								}
								
								if(z == 0){
									printf("Listen up, this is important\n");
									printf("This is a 3x3 table of randomily generated numbers\n");
									printf("You need to pick the highest number\n\n");
									
									printf("The table goes like this:\n");
									printf("[1] [2] [3]\n");
									printf("[4] [5] [6]\n");
									printf("[7] [8] [9]\n\n");
									
									printf("Now imagine the number thats on spot \"2\" is the highest number\n");
									printf("You would just have to type out \"2\" and you would win\n");
									printf("Thats the same for every time its generated, just see the highest and pick it\n\n");
									
									printf("There are 2 modes in here, VIEW mode and ANSWER mode\n");
									printf("In VIEW mode you get 5 seconds to see what the highest number is and its position\n");
									printf("While in ANSWER mode you need to say what position the highest number was\n\n");
									
									printf("Understood? You better...\n\n");
									Small_stop;

								}
								
								int max_number, chosen_num;
								
								if(strcmp(dificulty, "Lucid")== 0)
								max_number = 100;
									
								else if(strcmp(dificulty, "False")== 0)
								max_number = 1000;
									
								else if(strcmp(dificulty, "Vivid")== 0)
								max_number = 5000;
									
								else 
								max_number = 10000;
								
								//Messy code lul
								CLR;
							    CenterText("Whats the highest Number?");
							    int Rand[10], highest_num = 0, highest_index = 0;
							   	memset(Rand, 0, sizeof(Rand));
							    
							    //Randomize numbers why is the rand so predictable
							    for(int i = 1; i < 10; i ++){
							    	short int randomized_num = rand()% (max_number - 10) + 0;
									randomized_num += 10;		//Bug fix atempt 
							    	
							    	//Check if number alr exists inside array, reset current num if it is
							    	if(memchr(Rand, randomized_num, sizeof(Rand))!= NULL){
							    		i --;
							    		if(DEBUG_MODE)
							    		printf("[DEBUG] _> 2 RANDS HAVE SAME NUMBER\n");
							    		
									} else 
									Rand[i] = randomized_num;
									
								}
								
								//Display table
								short int cur_rand = 0; 
								for(int i = 1; i < 4; i ++){
									//Yet again, same thing has up to center in the screen
									char asit_var [10]; 	
									char * stats = (char *) malloc(100);
									stats[0] = '\0';
									
									for(int j = 1; j < 4; j ++){
										cur_rand ++;
										strcat(stats, "[");
										itoa(Rand[cur_rand], asit_var, 10);	
										strcat(stats, asit_var);
										strcat(stats, "] ");
									}
									
									printf("%*s\n", ((GetTerminalSize("columns") - strlen(stats)) / 2) + strlen(stats), stats);
									free(stats);
									
									if(i == 3)
									printf("\n");
								}
								
								//reverse for loop for clock
								for(int i = 5; i > -1; i --){
									//Yet again, same thing has up to center in the screen
									char asit_var [10]; 	
									char * stats = (char *) malloc(100);
									itoa(i, asit_var, 10);	
									strcpy(stats, asit_var);
									
									printf("\r%*s", ((GetTerminalSize("columns") - strlen(stats)) / 2) + strlen(stats), stats);
									free(stats);
									sleep(1);
								}
							    
							    //Decide on the highest
							    for(int i = 1; i < 10; i ++){
							    	if(Rand[i] > highest_num){
							    		highest_num = Rand[i];
							    		highest_index = i;
							    	}
								}
								
								//Ask for highest
								while(true){
									CLR;
								    printf("What was the highest number?\n");
								    String_Input;
								    
								    ///Convert into string and back to integer to not have that annoying bug happend
								   	if(isdigit(Input[0])){
								    	chosen_num = atoi(Input);
								    
									} else {
										Error; 
									}
								    
								    CLR;
								    
								    if(chosen_num == highest_index){ 
								    	green;
								        printf("Correct :D\n"); 
								        if(z != 0)
										puzzle_times_done ++;
										
								        white;
								        break;
								        
								    } else if (chosen_num != highest_index){
								    	red;
								        printf("Not the right number\n");
								        printf("Correct was %d (%d)\n", highest_num, highest_index);
								        if(z != 0){
								        	puzzle_times_failed ++;
								        	failed_puzzle = true;
								    	}
								        white;
								        break;
								        
								    } else
								    Error;
								    
								}
								
								if(z == 0){
									//Register tutorial has done
									if(display_all_tut_once){
										ChangeCurPath("OTHER.tutorials");
										FILE * ftutdisp = fopen("Puz1.txt", "w");
										fclose(ftutdisp);
									}

									
									while(true){
		
										CLR;
										printf("Tutorial done!\n");
										printf("Again? [Y/N]\n");
												
										String_Input;
												
										if(strcmp(Input, "y")== 0){
										z --; break;
										}	
												
										else if(strcmp(Input, "n")== 0)
										break;
												
										else 
										Error;
										
									}
								}
								
							}
						
						//String Sperated by index	
						} else if(puzzle_chosen == 2){
							
							for(int z = 0; z < 2; z ++){
								//Tutorial Skipping stuff :>
								if(z == 0){
									if(display_all_tut_once){
										ChangeCurPath("OTHER.tutorials");
										if(access("Puz2.txt", F_OK)== 0)
										z ++;
									}
									if(skip_tut_display)
									z ++;
								}
								
								CLR;
								if(show_tut_cutscene){
									if(z == 0){
										//Start Tutorial 
										printf("STARTING TUTORIAL...\n\n");
										sleep(2);
										CLR;
										
									} else {
										printf("STARTING PUZZLE...\n\n");
										sleep(2);
										CLR;
										
									}
								}
								
								if(z == 0){
									printf("Listen up, this is important\n");
									printf("This puzzle will pass 5 random words in 5 seconds (10 if eazier dificulty)\n");
									printf("When the timer bellow the words says something like \"N O W !\"\n");
									printf("You need to memorize the current word\n");
									printf("And then type it out when it asks you to\n");
									printf("You can fail 1 character and it still counts\n");
									printf("Understood? You better...\n\n");
									Small_stop;
								}
							
								//Wrong indexes patience is always 1
								int seconds_delay, indexes;
								
								//Set variables depending on dificulty
								if(strcmp(dificulty, "Lucid")== 0){
									seconds_delay = 2;
									indexes = 3;
									
								} else if(strcmp(dificulty, "False")== 0){
									seconds_delay = 2;
									indexes = 4;
									
								} else if(strcmp(dificulty, "Vivid")== 0){
									seconds_delay = 1;
									indexes = 3;
									
								} else {
									seconds_delay = 1;
									indexes = 4;
								}
								
								int second_chosen = rand()% 5 + 1;
								char real_string [indexes + 1];
								char gotten_strings [6] [indexes + 1];	//On the rare chance a random string dupes
								memset(gotten_strings, '\0', sizeof(gotten_strings));
				
								//Seconds counter			
								for(int i = 1; i < 6; i ++){
									CLR;
									//Get returned string
									bool valid_str = true;
									short int num_spaces = 1;
									char *returned_string = EncryptedWordsV1(&num_spaces);
									
									//Set up to put the string in the middle again
									char asit_var [5]; 
									memset(asit_var, '\0', sizeof(asit_var));
									char * stats = (char *) malloc(100);
									
									//Get all chars
									for(int j = 0; j < indexes; j ++)
									asit_var[j] = returned_string[j];
									
									//Check if theres a dupe string
									for(int j = 0; j < 5; j ++){
										if(strcmp(gotten_strings[j], asit_var)== 0){
											if(DEBUG_MODE)
											printf("[DEBUG] _> Dupped strings! (Somehow lol)\n");
											valid_str = false;
											break;
										}
									}
									
									//Dupped string? Try again
									if(!valid_str){
										i --;
										
									} else {
									strcpy(gotten_strings[i - 1], asit_var);
									strcpy(stats, asit_var);
									
									//Display final
									printf("%*s\n", ((GetTerminalSize("columns") - strlen(stats)) / 2) + strlen(stats), stats);
									
									//Get the real string
									if(i == second_chosen)
									strcpy(real_string, stats);
									
									free(stats);
									free(returned_string);
									
									if(second_chosen == i){
										//Set up for mid string
										yellow;
										char * stats = (char *) malloc(100);
										strcpy(stats, "N O W !");
										
										//The second ur supost to write it says "NOW!" instead of displaying seconds
										fflush(stdout);
										printf("%*s\n", ((GetTerminalSize("columns") - strlen(stats)) / 2) + strlen(stats), stats);
										
										white;
										
										free(stats);
									} else {
										//Same thing has above but displays seconds
										char * stats = (char *) malloc(100);
										memset(asit_var, '\0', sizeof(asit_var));
										itoa(i, asit_var, 10);	
										strcpy(stats, asit_var);
										
										fflush(stdout);
										printf("%*s\n", ((GetTerminalSize("columns") - strlen(stats)) / 2) + strlen(stats), stats);
										
										free(stats);
									}
									
									sleep(seconds_delay);
									}
									
								}
								
								CLR;
								bool correct_str = false;
								int times_failed = 0;
								char p2_user_str [5];
								
								//Ask for real string
								printf("Please type the real string bellow\n");
								printf("&/");
								scanf("%s", p2_user_str);		//Cant use string input cause it would lower caracters
								
								//Insta win if its all correct
								if(strcmp(p2_user_str, real_string)== 0){
									correct_str = true;
								
								//Check all indexes
								} else {
									for(int i = 0; i < indexes + 1; i ++){
										if(real_string[i] != p2_user_str[i])
										times_failed ++;
									}
									
									//If indexes fail more than once its wrong :>
									if(times_failed > 1){
										correct_str = false;
									} else {
										correct_str = true;
									}
								}
								
								CLR;
								
								//Correct :yay;
								if(correct_str){
									green;
									if(times_failed == 0)
									printf("String is fully correct!\n");
									
									else
									printf("String is almost corrent!\n");
									
									if(z != 0)
									puzzle_times_done ++;
									
								//Incorect :despair:
								} else {
									red;
									printf("String is incorrect!\n");
									if(z != 0){
										puzzle_times_failed ++;
										failed_puzzle = true;
									}
								}
								
								white;
								
								if(z == 0){
									//Register tutorial has done
									if(display_all_tut_once){
										ChangeCurPath("OTHER.tutorials");
										FILE * ftutdisp = fopen("Puz2.txt", "w");
										fclose(ftutdisp);
									}
																
									while(true){
								
										CLR;
										printf("Tutorial done!\n");
										printf("Again? [Y/N]\n");
												
										String_Input;
												
										if(strcmp(Input, "y")== 0){
											z--; break;
										}	
												
										else if(strcmp(Input, "n")== 0)
										break;
												
										else 
										Error;
										
									}
								}
							}
							
						//CONFIRM INFORMATION
						} else if(puzzle_chosen == 3){
							
							for(int z = 0; z < 2; z ++){
								CLR;
								//Tutorial Skipping stuff :>
								if(z == 0){
									if(display_all_tut_once){
										ChangeCurPath("OTHER.tutorials");
										if(access("Puz3.txt", F_OK)== 0)
										z ++;
									}
									if(skip_tut_display)
									z ++;
								}
								
								if(show_tut_cutscene){
									if(z == 0){
										//Start Tutorial 
										printf("STARTING TUTORIAL...\n\n");
										sleep(2);
									} else {
										printf("STARTING PUZZLE...\n\n");
										sleep(2);
									}		
								}
							
								if(z == 0){
									printf("Listen up, this is important\n");
									printf("This puzzle is going to generate 4 to 6 diferent pieces of information (called arguments)\n");
									printf("You get has much time has you want to look at that information\n");
									printf("After that you need to answer 1 or 2 questions about the information you saw\n\n");
									
									printf("Your objective here is to anwser those questions correctly\n");
									printf("Depending on the dificulty more or less arguments and questions will generate\n");
									printf("Understood? You better...\n\n");
									Small_stop;
								}
							
							bool is_dif_hard = false;
							int num_quest, parameters, correct_q = 0;
							
							//Set variables depending on dificulty
							if(strcmp(dificulty, "Lucid")== 0){
								num_quest = 1;
								parameters = 4;
								
							} else if(strcmp(dificulty, "False")== 0){
								num_quest = 1;
								parameters = 6;
								
							} else if(strcmp(dificulty, "Vivid")== 0){
								num_quest = 2;
								parameters = 4;
								
							} else {
								num_quest = 2;
								parameters = 6;
								
							}
							
							//Set up array of parameters and array of final data
							int parameters_chosen[parameters + 1];
							char final_data [9] [10];
							memset(parameters_chosen, 0, sizeof(parameters_chosen));
							
	    					//Randomize paremeters
	    					for(int i = 0; i < parameters; i ++){
	    						int paremeter = rand()% 8 + 1;
	    						if(memchr(parameters_chosen, paremeter, sizeof(parameters_chosen))!= NULL)
	    						i --;
	    						
	    						else
	    						parameters_chosen[i] = paremeter; 
							}
							
							if(DEBUG_MODE){
								for(int i = 0; i < parameters; i ++)
								printf("[DEBUG] _> Parameters_chosen[%d]? %d\n", i, parameters_chosen[i]);
							}
							
							//Randomize paremeters
							for(int i = 0; i < parameters; i ++){
								char final_data_str [10];
								
								//Randomize NAME
								if(parameters_chosen[i] == 1){	
									short int num_spaces = 1;
									char passing_string [4];
									memset(passing_string, '\0', sizeof(passing_string));
									
									//Get "NAME" from the "encrypted" randomizer
									char *returned_string = EncryptedWordsV2("aaa");
									
									strcpy(final_data_str, passing_string);				
									free(returned_string);
			
								//Randomize BIRTH DATE
								} else if(parameters_chosen[i] == 2){
									//Day
									int dates = rand()% 31 + 1;
									char converted_dates [3];
									itoa(dates, converted_dates, 10);
									strcpy(final_data_str, converted_dates);
									strcat(final_data_str, "/");
									
									//Month	
									dates = rand()% 12 + 1;
									itoa(dates, converted_dates, 10);
									strcat(final_data_str, converted_dates);
									strcat(final_data_str, "/");
									
									//Year
									dates = rand()% 999 + 1;
									itoa(dates, converted_dates, 10);
									strcat(final_data_str, converted_dates);
									
								//Randomize REASON 
								} else if(parameters_chosen[i] == 3){	
									const char reasons [5] [10] = {"Cat", "Singer", "Job", "Visit", "Unknown" };
									short int rand_reason = rand()% 5 + 1;
									rand_reason --;
									
									strcpy(final_data_str, reasons[rand_reason]);
									
								//Randomize ID 
								} else if(parameters_chosen[i] == 4){
									int cur_char = 0;
									char id_str [10];
									memset(id_str, '\0', sizeof(id_str));
									
									//Kinda like an ip address
									for(int j = 0; j < 2; j ++){
										for(int k = 0; k < 3; k ++){
											int number = rand()% 10 + 1;
											number --;
											id_str[cur_char] = number + '0';
											cur_char ++;
										}
										id_str[cur_char] = '.';
										cur_char ++;
									}
									
									strcpy(final_data_str, id_str);
									
								//Randomize LUNA / NINA / UNKNOWN paremeters 
								} else if(parameters_chosen[i] == 5){
								
									int random_thing = rand()% 3 + 1;
									if(random_thing == 1)
									strcpy(final_data_str, "LUNA");
									
									else if(random_thing == 2)
									strcpy(final_data_str, "NINA");
									
									else
									strcpy(final_data_str, "UNKNOWN");
								
								//Randomize TRUE / FALSE paremeters
								} else if(parameters_chosen[i] == 6){
									
									if(rand()% 2 + 1 == 1)
									strcpy(final_data_str, "TRUE");
									
									else
									strcpy(final_data_str, "FALSE");
									
								//Randomize PASSCODE
								} else if(parameters_chosen[i] == 7){
									int what_number = rand()% 100 + 1;
									char string_wat_num [10];
									memset(string_wat_num, '\0', sizeof(string_wat_num));
									
									int wot_convertion = rand()% 3 + 1;
									if(wot_convertion == 1)
									itoa(what_number, string_wat_num, 10);	//Decimal
									
									else if(wot_convertion == 2)
									itoa(what_number, string_wat_num, 2);	//Binary
									
									else
									itoa(what_number, string_wat_num, 16);	//Hexadecimal
									
									strcpy(final_data_str, string_wat_num);
								
								//OS TIME
								} else if(parameters_chosen[i] == 8){
									char time_str [10];
									memset(time_str, '\0', sizeof(time_str));
									
									//Open time struct
									time_t now = time(NULL);
									struct tm *tm_struct = localtime(&now);
									
									//Get hour and minutes from time struct and put them inside final_data_str with the assisting array
									int cur_h = tm_struct->tm_hour;
									if(rand()% 2 + 1 == 1)
									cur_h += 2;
									
									itoa(cur_h, time_str, 10);
									strcpy(final_data_str, time_str);
									strcat(final_data_str, ":");
									
									int cur_m = tm_struct->tm_min;
									if(rand()% 2 + 1 == 1)
									cur_m += 12;
									
									itoa(cur_m, time_str, 10);
									strcat(final_data_str, time_str);
								}
								
								if(DEBUG_MODE)
								printf("[DEBUG] _> Final_data[%d]? %s [Parameter -> %d]\n", i, final_data_str, parameters_chosen[i]);
								
								//Put finished data inside the string
								strcpy(final_data[i], final_data_str);
								
							}
							
							//Set this up to use later on questions
							int arguments_order_and_stuff [parameters];
							
							//Show Paremeters
							for(int i = 0; i < parameters; i ++){		//Final_data is organized has 0 - [parameters] here
								//Put all arguements in the middle of the screen (same set up has all)
								char asit_var [10]; 	
								char * stats = (char *) malloc(100);
								strcpy(stats, "Argument ");
								itoa(i, asit_var, 10);	
								strcat(stats, asit_var);
								strcat(stats, ": ");
								strcat(stats, final_data[i]);
								
								printf("%*s\n", ((GetTerminalSize("columns") - strlen(stats)) / 2) + strlen(stats), stats);
								free(stats);
								
								arguments_order_and_stuff[i] = parameters_chosen[i];
							}
							
							//Final gets "organized" for question answer to be eazier
							for(int i = 0; i < parameters; i ++){ 
								char assit_str [11];
								memset(assit_str, '\0', sizeof(assit_str));
								//Check if not wiped string
								if(final_data[i] != NULL){
									//Organize depending on current index to match with parameters_chosen[i] index
									strcpy(assit_str, final_data[i]);
									strcpy(final_data[parameters_chosen[i]], assit_str);
									
									//Check if "i" value does NOT exist to be wiped off
									if(memchr(parameters_chosen, i, sizeof(parameters_chosen))== 0)
									for(int j = 0; j < 10; j ++)
									final_data[i] [j] = '\0';
								}
							}
							
							if(DEBUG_MODE){
								for(int i = 0; i < parameters; i ++)
								printf("[DEBUG] _> Arguments_order_and_stuff[%d]? %d\n", i, arguments_order_and_stuff[i]);
							}
							
							//Wait for input
							dark_blue;
							CenterText("[PRESS ANYTHING WHEN YOU THINK YOU ARE READY]");
							getch();
							CLR;
							white;
							
							//Ask questions here and loop number of questions
							for(int i = 0; i < num_quest; i ++){
								short int question_w_par = rand()% parameters + 1, what_quest = rand()% 2 + 1, argument, quest_alr_done = 0;
								question_w_par = arguments_order_and_stuff[question_w_par - 1];
								
								char cur_question [125];
								bool is_yes_or_no = false, is_luna_nina_unknown = false;
								
								//No duped questions :>
								if(question_w_par == quest_alr_done){
									while(question_w_par == quest_alr_done){
										question_w_par = rand()% parameters + 1;
										question_w_par = arguments_order_and_stuff[question_w_par - 1];
									}
								}
								
								char correct_awnser [10];
								memset(correct_awnser, '\0', sizeof(correct_awnser));
								bool is_final_data_correct = true;
								
								if(DEBUG_MODE){
									printf("[DEBUG] _> final_data[question_w_par]? \"%s\"\n", final_data[question_w_par]);
									printf("[DEBUG] _> Question w par? %d\n", question_w_par);
								}
								
								//Select from 1 or 2 questions in each
								switch(question_w_par){
								case 1:{	//NAME
										//Check if final_data is valid
										if(strlen(final_data[question_w_par])> 3)
										is_final_data_correct = false;
										
										//Ask question if its valid
										if(is_final_data_correct){	
											//Get index(argument) of current question
											for(int j = 0; j < parameters; j ++){
												if(arguments_order_and_stuff[j] == 1){
													argument = j;
													break;
												}
											}
											
											if(what_quest == 1){
												printf("What was the first character of the argument (%d)?\n", argument);
												strcpy(cur_question, "What was the first character of the argument?");
												correct_awnser[0] = final_data[question_w_par] [0];
											} else {
												printf("What was the last character of the argument (%d)?\n", argument);
												strcpy(cur_question, "What was the last character of the argument?");
												correct_awnser[0] = final_data[question_w_par] [2];
											}
											correct_awnser[0] = tolower(correct_awnser[0]);
										}
										break;
									}
									
									case 2:{	//BIRTH DATE
										int num_of_slashes = 0; 
										
										//Check if final_data is valid
										for(int j = 0; j < strlen(final_data[question_w_par]); j ++){
											//Check for slashes position and how many there are
											if(final_data[question_w_par] [j] == '/'){
												num_of_slashes += 1;
											//Check if its NOT integer
											} else if(isdigit(final_data[question_w_par] [j])== 0){
												is_final_data_correct = false;
												break;
											}
										}
										
										//Invalid date :>
										if(num_of_slashes != 2)
										is_final_data_correct = false;
										
										if(is_final_data_correct){
											int day, month, year;
											
											int cur_char = 0;
											char day_str [3];
											
											//Check day
											for(int j = 0; j < strlen(final_data[question_w_par]); j ++){
												if(final_data[question_w_par] [cur_char] == '/')
												break;
												
												else {
													//Register inside str
													day_str[j] = final_data[question_w_par] [cur_char]; 
													cur_char ++;
												}
											}
											
											//Convert into int
											day = atoi(day_str);
											
											cur_char ++;
											char month_str [3];
											//Check month
											for(int j = 0; j < strlen(final_data[question_w_par]); j ++){
												if(final_data[question_w_par] [cur_char] == '/')
												break;
												
												else {
													//Register inside str
													month_str[j] = final_data[question_w_par] [cur_char]; 
													cur_char ++;
												}
											}
											
											//Convert into int
											month = atoi(month_str);
											
											cur_char ++;
											char year_str [4];
											//Check year
											for(int j = 0; j < strlen(final_data[question_w_par]); j ++){
												if(final_data[question_w_par] [cur_char] == '/')
												break;
												
												else {
													//Register inside str
													year_str[j] = final_data[question_w_par] [cur_char]; 
													cur_char ++;
												}
											}
											
											//Convert into int
											year = atoi(year_str);
											
											cur_char ++;
											
											//Get index(argument) of current question
											for(int j = 0; j < parameters; j ++){
												if(arguments_order_and_stuff[j] == 2){
													argument = j;
													break;
												}
											}
											
											if(what_quest == 1){
												int bckp_day = day;
												//Change the day a little bit
												if(rand()% 2 + 1 == 1){
													while(true){
														bckp_day = day;
														
														//Randomize up day or down day
														if(rand()% 2 + 1 == 1)
														bckp_day -= rand()% 5 + 1;
														
														else
														bckp_day += rand()% 5 + 1;
														
														//Check if day is still valid
														if(bckp_day < 31 && bckp_day > 1)
														break;
													}
													strcpy(correct_awnser, "no");
													
												//No changes made
												} else 
												strcpy(correct_awnser, "yes");
												
												printf("Did argument (%d) have day has \"%d/--/---\"? [YES] [NO]\n", argument, bckp_day);
												strcpy(cur_question, "Did argument have day has \"");
												itoa(day, day_str, 10);
												strcat(cur_question, day_str);
												strcat(cur_question, "/--/---\"? [YES] [NO]");	
											} else {
												int bckp_year = year;
												//Change the day a little bit
												if(rand()% 2 + 1 == 1){
													while(true){
														bckp_year = year;
														
														//Randomize up day or down day
														if(rand()% 2 + 1 == 1)
														bckp_year -= rand()% 5 + 1;
														
														else
														bckp_year += rand()% 5 + 1;
														
														//Check if day is still valid
														if(bckp_year < 999 && bckp_year > 1)
														break;
													}
													strcpy(correct_awnser, "no");
													
												//No changes made
												} else 
												strcpy(correct_awnser, "yes");
												
												printf("Did argument (%d) have year has \"--/--/%d\"? [YES] [NO]\n", argument, bckp_year);
												strcpy(cur_question, "Did argument have year has \"--/--/");
												itoa(year, year_str, 10);
												strcat(cur_question, year_str);
												strcat(cur_question, "\"? [YES] [NO]");
											}
											
											is_yes_or_no = true;
										}
										break;
									}
									
									case 3:{	//REASON
										
										//Check if final_data is valid
										if(strcmp(final_data[question_w_par], "Cat")!= 0 &&
										strcmp(final_data[question_w_par], "Singer")!= 0 &&
										strcmp(final_data[question_w_par], "Job")!= 0 &&
										strcmp(final_data[question_w_par], "Visit")!= 0 &&
										strcmp(final_data[question_w_par], "Unknown")!= 0)
										is_final_data_correct = false;
										
										//Ask question if its valid
										if(is_final_data_correct){
											//Get index(argument) of current question
											for(int j = 0; j < parameters; j ++){
												if(arguments_order_and_stuff[j] == 3){
													argument = j;
													break;
												}
											}
											
											if(strcmp(final_data[question_w_par] ,"Singer")== 0 ||
											strcmp(final_data[question_w_par] ,"Job")== 0 ||
											strcmp(final_data[question_w_par] ,"Visit")== 0)
											strcpy(correct_awnser, "yes");
											
											else
											strcpy(correct_awnser, "no");
											
											printf("Heres the list of valid reasons:\n");
											printf("	-\"Singer\"\n");
											printf("	-\"Job\"\n");
											printf("	-\"Visit\"\n");
											printf("Did the argument (%d) have a valid reason? [YES] [NO]\n", argument);
											strcpy(cur_question, "Did argument have a valid reason? [YES] [NO]");
											
											is_yes_or_no = true;
										}
										break;
									}
									
									case 4:{	//ID
										int cur_char = 0;
										//Check if final_data is valid 
										for(int j = 0; j < 2; j ++){
											for(int k = 0; k < 3; k ++){
												//Check if its NOT integer
												if(isdigit(final_data[question_w_par] [cur_char])== 0){
													is_final_data_correct = false;
													break;
												}
												cur_char ++;
											}
											
											//Check if cur_char is NOT pointer
											if(final_data[question_w_par] [cur_char] != '.'){
												is_final_data_correct = false;
												break;
											}
											
											cur_char ++;
										}
										
										//Extra check just to make sure
										if(strlen(final_data[question_w_par])!= 8)
										is_final_data_correct = false;
	
										if(is_final_data_correct){
											//Get index(argument) of current question
											for(int j = 0; j < parameters; j ++){
												if(arguments_order_and_stuff[j] == 4){
													argument = j;
													break;
												}
											}
											
											if(what_quest == 1){
												char num_checked [2];
												int num_chosen = rand()%9 + 1;
												itoa(num_chosen, num_checked, 10);
												
												strcpy(correct_awnser, "no");
												
												//Check if "num_checked" is present
												for(int j = 0; j < strlen(final_data[question_w_par]); j ++){
													if(final_data[question_w_par][j] == num_checked [0]){
														strcpy(correct_awnser, "yes");
														break;
													}
												}
												
												printf("Did argument (%d) have the number \"%d\" on it? [YES] [NO]\n", argument, num_chosen);
												strcpy(cur_question, "Did argument have the number \"");
												strcat(cur_question, num_checked);
												strcat(cur_question, "\" on it? [YES] [NO]");
												
											} else {
												char searching_char [2];
												
												strcpy(correct_awnser, "no");
												
												//Search for char
												for(int j = 0; j < strlen(final_data[question_w_par]); j ++){
													//Change current char being tracked down
													searching_char[0] = final_data[question_w_par][j];
													
													//REPEATING NUMBERS, NOT CHARS
													if(searching_char[0] == '.'){
														j ++;
														searching_char[0] = final_data[question_w_par][j];
													}
													
													//Track down current char
													for(int k = 0; k < strlen(final_data[question_w_par]); k ++){
														if(final_data[question_w_par][k] == searching_char[0]){
															strcpy(correct_awnser, "yes");
															break;
														}
													}
													//If it alr found the char just break the loop lol
													if(strcmp(correct_awnser, "yes")== 0)
													break;
												}
												
												printf("Did argument (%d) have repeating numbers? [YES] [NO]\n", argument);
												strcpy(cur_question, "Did argument have repeating numbers? [YES] [NO]");
												
												is_yes_or_no = true;
											}
										}
										break;
									}
									
									case 5:{	//LUNA / NINA / UNKNOWN
									
										//Check if final_data is valid
										if(strcmp(final_data[question_w_par], "LUNA")!= 0 &&
										strcmp(final_data[question_w_par], "NINA")!= 0 &&
										strcmp(final_data[question_w_par], "UNKNOWN")!= 0)
										is_final_data_correct = false;
										
										//Ask question if its valid
										if(is_final_data_correct){
											//Get index(argument) of current question
											for(int j = 0; j < parameters; j ++){
												if(arguments_order_and_stuff[j] == 5){
													argument = j;
													break;
												}
											}
											
											strcpy(correct_awnser, final_data[question_w_par]);
											
											for(int j = 0; j < strlen(correct_awnser); j ++)												
											correct_awnser[j] = tolower(correct_awnser[j]);
											
											printf("What did the argument (%d) have on it?\n", argument);
											printf("[LUNA] / [NINA] / [UNKNOWN]\n");
											strcpy(cur_question, "What did argument have on it? [LUNA] [NINA] [UNKNOWN]");
											
											is_luna_nina_unknown = true;
										}
										break;
									}
									
									case 6:{	//TRUE / FALSE
										
										//Check if final_data is valid
										if(strcmp(final_data[question_w_par], "TRUE")!= 0 &&
										strcmp(final_data[question_w_par], "FALSE")!= 0)
										is_final_data_correct = false;
										
										//Ask question if its valid
										if(is_final_data_correct){
											//Get index(argument) of current question
											for(int j = 0; j < parameters; j ++){
												if(arguments_order_and_stuff[j] == 6){
													argument = j;
													break;
												}
											}
											
											strcpy(correct_awnser , final_data[question_w_par]);
											
											if(what_quest == 1){
												printf("Did argument (%d) have \"TRUE\" on it? [YES] [NO]\n", argument);
												strcpy(cur_question, "Did argument have \"TRUE\" on it? [YES] [NO]");
												if(strcmp(final_data[question_w_par], "TRUE")== 0)
												strcpy(correct_awnser, "yes");
												
												else
												strcpy(correct_awnser, "no");
												
											} else {
												printf("Did argument (%d) have \"FALSE\" on it? [YES] [NO]\n", argument);
												strcpy(cur_question, "Did argument have \"FALSE\" on it? [YES] [NO]");
												if(strcmp(final_data[question_w_par], "FALSE")== 0)
												strcpy(correct_awnser, "yes");
												
												else
												strcpy(correct_awnser, "no");
											}
											is_yes_or_no = true;
										}
										break;
									}
									
									case 7:{	//PASS
									
										//Check if final_data is valid (if all chars match array)
										int cur_char = 0;
										char valid_chars_arr [17] = "0123456789abcdef";
										
										//Sorry about this
										for(int j = 0; j < strlen(final_data[question_w_par]); j ++){
											int invalid = 0;
											for(int k = 0; k < strlen(valid_chars_arr); k ++){
												if(final_data[question_w_par][j] != valid_chars_arr[k])
												invalid ++;
												
												if(invalid == strlen(valid_chars_arr)){
													is_final_data_correct = false;
													break;
												}
											}
											if(!is_final_data_correct)
											break;
										}
									
										if(is_final_data_correct){
											bool is_bin = true, is_hex = true;
											//Get index(argument) of current question
											for(int j = 0; j < parameters; j ++){
												if(arguments_order_and_stuff[j] == 7){
													argument = j;
													break;
												}
											}
											
											if(what_quest == 1){
												printf("Is argument (%d) a Binary number? [YES] [NO]\n", argument);
												strcpy(cur_question, "Is argument a Binary number? [YES] [NO]");
												for(int j = 0; j < strlen(final_data[question_w_par]); j ++){
													//Check if all numbers are 1s or 0s
													if(final_data[question_w_par] [j] == '0' ||
													final_data[question_w_par] [j] == '1')
													is_bin = true;
													
													else {
														is_bin = false;
														break;
													}
												}
												
												if(is_bin)
												strcpy(correct_awnser, "yes");
												
												else
												strcpy(correct_awnser, "no");
												
											} else {
												printf("Is argument (%d) a Hexadecimal number? [YES] [NO]\n", argument);
												strcpy(cur_question, "Is argument a Hexadecimal number? [YES] [NO]");
												short int num_alphas = 0;
												
												//Check for chars
												for(int j = 0; j < strlen(final_data[question_w_par]) + 1; j ++){
													if(isalpha(final_data[question_w_par] [j] == 0))	//Check if its NOT char
													num_alphas ++;
												}
												
												//Hex code needs at least 1 char to make sure it hex and user can understand it
												if(num_alphas == 0)
												is_hex = false;
												
												//Max lenght it can get is 2 because its randomizing bettewn 100 and 1 decimal
												if(strlen(final_data[question_w_par])> 2)
												is_hex = false;
												
												if(is_hex)
												strcpy(correct_awnser, "yes");
												
												else
												strcpy(correct_awnser, "no");
											}
											
											is_yes_or_no = true;
										}
										break;
									}
									
									case 8:{	//TIME	
										//Open time struct
										time_t now = time(NULL);
										struct tm *tm_struct = localtime(&now);
										
										//Get computer hour and minute
										int comp_hour = tm_struct->tm_hour;
										int comp_min = tm_struct->tm_min;
										
										//Check if final_data is valid - hour and minute values match up to eachoder 
										int minutes = 0, hour = 0, doble_p_pos = 0;
										
										//Get ":" position
										for(int j = 0; j < strlen(final_data[question_w_par]); j ++){
											if(final_data[question_w_par][j] == ':'){
												doble_p_pos = j;
												break;
											}
										}
										
										//No ":"? Not it then
										if(doble_p_pos == 0)
										is_final_data_correct = false;
										
										//Get hour
										char hour_str [3];
										if(doble_p_pos == 2){
											//Double hour
											hour_str[0] = final_data[question_w_par] [0];
											hour_str[1] = final_data[question_w_par] [1];
										} else {
											//Single hour
											hour_str[0] = final_data[question_w_par] [0];
										}
										
										//Convert hour gotten into int
										hour = atoi(hour_str);
										
										//Get minute
										char minute_str [3];
										if(doble_p_pos == 2){
											//Double hour
											if(final_data[question_w_par][4] != '\0'){
												//Double minute
												minute_str[0] = final_data[question_w_par] [3];
												minute_str[1] = final_data[question_w_par] [4];
											//Single minute
											} else 
											minute_str[0] = final_data[question_w_par] [3];
										} else {
											//Double hour
											if(final_data[question_w_par][3] != '\0'){
												//Double minute
												minute_str[0] = final_data[question_w_par] [2];
												minute_str[1] = final_data[question_w_par] [3];
											//Single minute
											} else 
											minute_str[0] = final_data[question_w_par] [2];
										}
										
										//Convert minutes gotten into
										minutes = atoi(minute_str);
										
										if(comp_min != minutes && (comp_min + 12 != minutes))
										is_final_data_correct = false;
										
										else if(comp_hour != hour && (comp_hour + 2 != hour))
										is_final_data_correct = false;
										
										if(is_final_data_correct){
											short int final_data_hour, final_data_minute;
											bool is_hour_right = false, is_min_right = false;
											
											if(what_quest == 1){
												printf("Is argument (%d) hour equal to computer hour? [YES] [NO] (Only the hour when the question was made is valid)\n", argument);
												strcpy(cur_question, "Is argument hour equal to computer hour? [YES] [NO] (Only the hour when the question was made is valid)");
												
												//Checking if hour matches
												if(comp_hour == hour)
												is_hour_right = true;
												
												if(is_hour_right)
												strcpy(correct_awnser, "yes");
												
												else
												strcpy(correct_awnser, "no");
												
											} else {
												printf("Is argument (%d) minute equal to computer minute? [YES] [NO] (Only the minute when the question was made is valid)\n", argument);
												strcpy(cur_question, "Is argument minute equal to computer minute? [YES] [NO] (Only the minute when the question was made is valid)");
												
												//Checking if minute matches
												if(comp_min == minutes)
												is_min_right = true;
												
												if(is_min_right)
												strcpy(correct_awnser, "yes");
												
												else
												strcpy(correct_awnser, "no");
											}
											
											is_yes_or_no = true;
										}
										break;
									}
								}
							
							//Reset parameter
							if(!is_final_data_correct)
							i --;
							
							if(DEBUG_MODE){
								printf("[DEBUG] _> Correct Anwser? %s\n", correct_awnser);
								printf("[DEBUG] _> Is final data Correct? %d\n", is_final_data_correct);
								printf("[DEBUG] _> Question alr done? %d\n", question_w_par);
							}
							
							//Ask questions and stuff
							if(is_final_data_correct){
								quest_alr_done = question_w_par;	//Register alr done question if theres 2 questions
								bool is_wrong = false; 
								
								while(true){
									String_Input;
																				
									if(strcmp(Input, correct_awnser)== 0){
										green;
										printf("Correct!");
										correct_q ++;
										
										if(num_quest == 2)
										printf(" [%d/2]", correct_q);
										
										printf("\n");
										break;
									
									//Checking if its a misspelling error or a legitimate error
									} else {
										red;
										if(is_yes_or_no){
											
											if(strcmp(Input, "yes")!= 0 && strcmp(Input, "no")!= 0){
												printf("You must answer yes or no!\n");
												sleep(3);
												
											} else
											is_wrong = true;
											
										} else if(is_luna_nina_unknown){
											if(strcmp(Input, "luna")!= 0 && strcmp(Input, "nina")!= 0 && strcmp(Input, "unknown")!= 0){
												printf("You must answer Luna / Nina / Unknown!\n");
												sleep(3);
											
											} else
											is_wrong = true;
											
										} else {
											is_wrong = true;
										}
										
										if(is_wrong){
											printf("Incorrect!\n");
											printf("Correct anwser was \"%s\"!\n", correct_awnser);
											if(z != 0){
												puzzle_times_failed ++;
												failed_puzzle = true;	
											}
											break;
										}
									}
									
									white;
									CLR;
									printf("%s\n", cur_question);
									printf("(Argument is %d)\n", argument);
									
									if(question_w_par == 3){
											printf("Heres the list of valid reasons:\n");
											printf("	-\"Singer\"\n");
											printf("	-\"Job\"\n");
											printf("	-\"Visit\"\n");
									}
								}
								white;
								
								if(correct_q == num_quest && z != 0)
								puzzle_times_done ++;
								
								if(failed_puzzle)
								break;
							}
							
							}	//END OF FOR LOOP
						
						if(z == 0){
							//Register tutorial has done
							if(display_all_tut_once){
								ChangeCurPath("OTHER.tutorials");
								FILE * ftutdisp = fopen("Puz3.txt", "w");
								fclose(ftutdisp);
							}

							
							while(true){
		
								CLR;
								printf("Tutorial done!\n");
								printf("Again? [Y/N]\n");
										
								String_Input;
										
								if(strcmp(Input, "y")== 0){
									z --; break;
								}	
										
								else if(strcmp(Input, "n")== 0)
								break;
										
								else 
								Error;
								
							}
						}
							
						}
							
						} //PUZZLES END HERE
						
						printf("\n");
						Small_stop;
						
						//Puzzle done? go to next room
						if(puzzle_times_done == 2){
							green;
							printf("Puzzles over!\n");
							white;
							Small_stop;
							break;
						}
						
						}
						
					} else if(strcmp(Input, "item")== 0){
						
						Art("DUNGEON", 10);
						Small_stop;
						
						while(true){
							//Code "stolen" from chest function :>
							int inv_return = Inventory("ID", 0, 0);
							int bckp_inv_return = inv_return;
							
							if(inv_return == 0){
								printf("No healing it is then\n");
								sleep(2);
								CLR;
								break;
							}
							
							//Special error value in case inv has no items :)
							if(inv_return == -99999){
								CLR;
								red;
								printf("Empty Inventory!\n");
								white;
								Small_stop;
								break;
							} else {
								int Quantity, ID;
								
								//Decode returning value
								Quantity = inv_return / 1000;
								bckp_inv_return -= (Quantity * 1000);
								ID = bckp_inv_return;
								
								if(ID == 38 || ID == 43 || ID == 113 || ID == 115 || ID == 116 || ID == 133 ||
								(ID > 46 && ID < 101)){
									
									//Subtract item from inventory
									int bckp_quantity = Quantity;
									Quantity = -Quantity;
									
									Inventory("CALC", ID, Quantity);
									CLR;
									
									light_blue;
									if(ID == 113)
									printf("You feel a little bit lightheaded, eehehe...Zzzzz\n");
									//^Myth about medronho is that it gets you drunk
									
									else
									printf("You ate it and...?\n");
									white;
									sleep(2);
									CLR;
									
									short int more_heal = 0;
									
									//Diferent amounts of hp depending on item
									if (ID > 46 && ID < 101)	//Fish
									more_heal = 10;
									
									if(ID == 38 || ID == 43)	//Livestock
									more_heal = 15;
									
									if(ID == 113 || ID == 115)	//Fruits
									more_heal = 12;
									
									if(ID == 116)				//Milk "potion"
									more_heal = 3;
									
									if(ID == 133)				//[BIG NAME] Shrimp
									more_heal = 20;
									
									light_blue;
									printf("Recovered %d Health!\n", more_heal * abs(Quantity));
									
									//Add to current hp here depending on quantity
									short int bckp_hp = user.hp;
									Quantity = abs(Quantity);
									bckp_hp += Quantity * more_heal;
									
									//Calculate abs overflow
									if(bckp_hp > 100){
										int extra_abs = bckp_hp - 100;
										user.abs += extra_abs;
										user.hp = 100;
										printf("Bonus! Got %d abs hp!\n", extra_abs);
									
									//Just transfer the bckp to the normal one
									} else 
									user.hp = bckp_hp;
									
									white;
									Small_stop;
									break;
								} else {
									red;
									printf("This item cannot be eaten because:\n");
									printf("-> Its poisonous\n");
									printf("-> Tastes bad\n");
									printf("-> I make the rules\n");
									printf("-> No nutritinal value\n");
									printf("-> Wont help you in your current situation\n");
									white;
									Small_stop;
								}
							
							}
						
						}
						
					} else if(strcmp(Input, "run")== 0 || strcmp(Input, "leave")== 0){
						bool can_leave;
						short int try_leave = 0;
						
						if(strcmp(dificulty, "Lucid")== 0){
							can_leave = true;
							
						} else if(strcmp(dificulty, "False")== 0){
							if(rand()% 2 + 1 == 1)
							can_leave = true;
							
						} else if(strcmp(dificulty, "Vivid")== 0){
							try_leave = rand()% 3 + 1;
							if(try_leave == 1)
							can_leave = true;
							
						} else {
							try_leave = rand()% 4 + 1;
							if(try_leave == 1)
							can_leave = true;
							
						}
						
						if(can_leave){
							red;
							printf("Coward...\n");
							white;
							sleep(2);
							leave_dung = true;
							break;
						} else {
							red;
							printf("You couldnt run away!\n");
							white;
						}
						
						CLR;
						
					} else { Error;	}
				
				//Monster can only attack in a monster room
				if(!is_puzzle){
					red;
					printf("The monster attacked! ow...\n");
					int less_heal = 0;
					
					//Defence acts up when you dont have abs
					if(user.hp <= 100){
						//abs((monst.attack * dif_val + 5) - (monst.def + dif_val));
						less_heal = abs((monst.attack * dif_val + 5) - (monst.def + dif_val));
						user.hp -= less_heal;
						
					//No defence with abs
					} else {
						less_heal = monst.attack;
						user.abs -= monst.attack;
						
						//User abs is down, calculate the rest then
						if(user.abs < 0){
							int dif_hp = abs(user.abs);
							user.abs = 0;
							less_heal = abs((dif_hp * dif_val + 5) - (monst.def + dif_val));
							user.hp -= less_heal;
						}
					}
					
					printf("-%d hp!\n\n", less_heal);
					white;
				
				} else if(failed_puzzle){
					red;
					printf("Debuff from failing the puzzle! ow...\n");
					int less_heal = 0, puzzle_dmg = 0;
					
					if(puzzle_dmg < 5)
					puzzle_dmg = 5 * puzzle_times_failed;
					
					else
					puzzle_dmg = 25;
					
					//Defence acts up when you dont have abs
					if(user.hp <= 100){
						less_heal = abs((puzzle_dmg * dif_val + 5) - (monst.def + dif_val));
						user.hp -= less_heal;
						
					//No defence with abs
					} else {
						less_heal = puzzle_dmg;
						user.abs -= puzzle_dmg;
						
						//User abs is down, calculate the rest then
						if(user.abs < 0){
							int dif_hp = abs(user.abs);
							user.abs = 0;
							less_heal = abs((dif_hp * dif_val + 5) - (monst.def + dif_val));
							user.hp -= less_heal;
						}
					}
					
					printf("-%d hp!\n\n", less_heal);
					white;
				}
				
				//Died
				if(user.hp < 1){
					red;
					printf("You fainted!\n");
					white;
					Small_stop;
					user.hp = 10;
					leave_dung = true;
					break;
				}
			
			}	//Current room is done? Move onto the next
			
			//Reset parameters
			monster_chosen = 0;
			puzzle_chosen = 0;
			puzzle_times_failed = 0;
			puzzle_times_done = 0;
			
			//User requested to leave
			if(leave_dung)
			break;
			
			green;
			//1st room loot is always the old book
			if(cur_room == 1){
				printf("LOOT! Got an old book!\n");
				ChangeCurPath("OTHER.books");
				//Change this ltr depending on how many books there r gn be
				FILE * foldbook = fopen("BooksFound.txt", "w");
				fprintf(foldbook, "1");
				fclose(foldbook);
				ChangeCurPath("STORY");
				CatCurPath(change_key_dir);
				
			//Randomize loot outside of 1st room
			} else {
				if(rand()% 2 + 1 == 1){
					printf("LOOT! ");
					int loot_randomizer = rand()% 8 + 1;
					switch(loot_randomizer){
						case 1:
							printf("Got 3 Gold Coins!\n");
							break;
							
						case 2:
							printf("Got a Mask!\n");
							break;
							
						case 3:
							printf("Got a Broken Pot!\n");
							break;
							
						case 4:
							printf("Got a Shark Tooth!\n");
							break;
							
						case 5:
							printf("Got a Plant Fossil!\n");
							break;
							
						case 6:
							printf("Got a Spinel Ring!\n");
							break;	
						
						case 7:
							printf("Got a Zircon Necklace!\n");
							break;
							
						case 8:
							printf("Got a Burnt Map!\n");
							break;
						
						default:
							break;
					}
					
				} //Nothing lol
			}
			white;
			
			//Assuming to be complete
			cur_room ++;
			
			//Randomize next room it is
			if(rand()% 2 + 1 == 1)
			is_puzzle = true;
			
			else
			is_puzzle = false;
				
			if(is_puzzle){
				if(DEBUG_MODE)
				printf("[DEBUG] _> PUZZLE ROOM\n");
				
				puzzle_chosen = rand()% 3 + 1;
				
				if(DEBUG_MODE)
				printf("[DEBUG] _> Puzzle Chosen? %d\n", puzzle_chosen);
				
			} else {
				if(DEBUG_MODE)
				printf("[DEBUG] _> MONSTER ROOM\n");
				
				monster_chosen = rand()% 5 + 1;
				if(DEBUG_MODE)
				printf("[DEBUG] _> Monster Chosen? %d\n", monster_chosen);
				
				switch(monster_chosen){
					case 1: {
						monst.hp = 50;
						monst.abs = 5; 
						monst.attack = 10;
						monst.def = 3;
						break;
					}
					
					case 2: {
						monst.hp = 25; 
						monst.abs = 25; 
						monst.attack = 15;
						monst.def = 5;
						break;
					}
					
					case 3: {
						monst.hp = 25; 
						monst.abs = 5; 
						monst.attack = 15;
						monst.def = 12;
						break;
					}
					
					case 4: {
						monst.hp = 125; 
						monst.abs = 25; 
						monst.attack = 7;
						monst.def = 0;
						break;
					}
					
					case 5: {
						monst.hp = 35; 
						monst.abs = 75; 
						monst.attack = 10;
						monst.def = 7;
						break;
					}
				}
				
				monst_hp_lim = monst.hp;
			}
			
			//Register room settings
			FILE * fcurroominfo = fopen("Curroominfo.txt", "w");
			fprintf(fcurroominfo, "%d\n", is_puzzle);
			if(monster_chosen != 0)
			fprintf(fcurroominfo, "%d\n", monster_chosen);
			
			else
			fprintf(fcurroominfo, "%d\n", puzzle_chosen);
			
			fclose(fcurroominfo);
		}
		
		//User will prob call inv and change the current dir
		ChangeCurPath("STORY");
		CatCurPath(change_key_dir);
		
		//Register new variables	
		fopen("RoomsExplored.txt", "w");
		fprintf(froomsexplored, "%d\n", cur_room);
		fclose(froomsexplored);
		
		fopen("UserStats.txt", "w");
		fprintf(fuserstats, "%d\n", user.hp);
		fprintf(fuserstats, "%d\n", user.attack);
		fprintf(fuserstats, "%d\n", user.def);
		fprintf(fuserstats, "%d\n", user.abs);
		fclose(fuserstats);
		
		//Register monster stats and trap stats 
		FILE * fmonsterstats = fopen("MonsterStats.txt", "w");
		fprintf(fmonsterstats, "%d\n", monst.hp);
		fprintf(fmonsterstats, "%d\n", monst_hp_lim);
		fprintf(fmonsterstats, "%d\n", monst.abs);
		fprintf(fmonsterstats, "%d\n", monst.attack);
		fprintf(fmonsterstats, "%d\n", monst.def);
		fclose(fmonsterstats);
				
		FILE * fpuzzlestats = fopen("PuzzleStats.txt", "w");
		fprintf(fpuzzlestats, "%d\n", puzzle_times_done);
		fprintf(fpuzzlestats,"%d\n", puzzle_times_failed);
		fclose(fpuzzlestats);
		
	} else if(strcmp(Caller, "Blossom")== 0){
		if(needs_starting_chat){
			printf("[NPC] Astro: \"Stars are quite beautifull arent they?\"\n");
			printf("[NPC] Astro: \"Personaly, i belive that stars are here to deliver us messages from the universe\"\n");
			printf("[NPC] Astro: \"Dont you agree\"\n");
			printf("I need the key\n");
			printf("[NPC] Astro: \"Ah, yes the oh so precious Blossom key i have been holding onto\"\n");
			printf("[NPC] Astro: \"But there is a problem\"\n");
			printf("[NPC] Astro: \"Are you worthy of this key?\"\n");
			printf("[NPC] Astro: \"I still dont know...\"\n");
			printf("[NPC] Astro: \"Here, take these items\"\n");
			printf("[NPC] Astro: \"Its an Astrall Compass and a Portable Telescope\"\n");
			printf("[NPC] Astro: \"Follow the compass and let the stars guide your way\"\n");
			printf("[NPC] Astro: \"If everything goes right i wont see you for a good while\"\n");
			printf("[NPC] Astro: \"Bring me the item i am looking for...\"\n");
			printf("[NPC] Astro: \"Good luck.\"\n");
			starting_chat_done = true;
			Small_stop;
		}
		
	} else if(strcmp(Caller, "Peak")== 0){
		if(needs_starting_chat){
			
			starting_chat_done = true;
			Small_stop;
		}
		
	} else {
		CLR;
		red;
		printf("Unknown key (Key Function ARG error)\n");
		white;
		Small_stop;
		return;
	}
	
	//Update if we alr did the starting chats or not
	if(starting_chat_done && needs_starting_chat){
		int updatebool = 0;
		
		//Same thing has updating the new key done
		ChangeCurPath("OTHER.triggers.story");
		FILE * fupdatekeytriggers = fopen("KeyTriggersDone.txt", "r");
		FILE * ftemp = fopen("__temp.txt", "w");
		
		int cur_lines = 1;
		while(fscanf(fupdatekeytriggers, "%d\n", &updatebool)!= EOF){
			if(cur_lines == INT_key)
			fprintf(ftemp, "1\n");
			
			else
			fprintf(ftemp, "%d\n", updatebool);
			
			cur_lines ++;
		}
	
		fclose(fupdatekeytriggers);
		fclose(ftemp);
		
		remove("KeyTriggersDone.txt");
		rename("__temp.txt", "KeyTriggersDone.txt");
	}
	
	ChangeCurPath("STORY");
	
	//Register new key
	if(new_key){
		int updatebool = 0;
		
		FILE * fupdatekeydone = fopen("Keysdone.txt", "r");
		FILE * ftemp = fopen("__temp.txt", "w");
		
		int cur_lines = 1;
		while(fscanf(fupdatekeydone, "%d\n", &updatebool)!= EOF){
			if(cur_lines == INT_key)
			fprintf(ftemp, "1\n");
			
			else
			fprintf(ftemp, "%d\n", updatebool);
			
			cur_lines ++;
		}
	
		fclose(fupdatekeydone);
		fclose(ftemp);
		
		remove("Keysdone.txt");
		rename("__temp.txt", "Keysdone.txt");
	}
	
	return;
}

void SpecialLocations(const char * Caller){
	CLR;
	
	if(strcmp(Caller, "Forest")== 0){
		/*
		Note to reader:
		
		This is kinda complicated i think
		*/
		
		bool try_to_spawn_new_bird = false, first_time = false;
		int number_of_birds = 0, art_code = 111, number_of_houses_broken = 0, number_of_unfinished_h = 0;
		int number_of_h_w_itm = 0, last_h_refreshed = 0;
		long int last_d_refreshed = 0;
		
		struct house_stats {
			bool can_have_bird, has_item, has_bird;
			unsigned int item_id;
			int item_quantity, bird_id, nest_days_spent, last_nest_day;
		};
		
		struct bird_stats {
			bool bird_exists, is_bird_rare;
			int day_the_bird_got_here;
		};
		
		struct house_stats house[3];
		struct bird_stats bird[3];
		
		ChangeCurPath("STASH.Animals");
		if(access("BirdHousesInfo.txt", F_OK)== 0){
			long int last_d_refreshed = 0;
			int last_h_refreshed = 0;
			
			/*
			Inside BirdHousesInfo.txt:
			
			last_h_refreshed		[Integer]
			last_d_refreshed		[Integer]
			number_of_birds			[Integer]
			number_of_houses_broken [Integer]
			number_of_unfinished_h	[Integer]
			number_of_h_w_itm		[Integer]
			
			(Repeat this 3 times over)
			can_have_bird 			[Boolean]
			has_item				[Boolean]
			item_id					[Integer] (Is 0 if theres nothing)
			item_quantity			[Integer]
			has_bird				[Boolean]
			bird_id					[Integer]
			nest_days_spent			[Integer]
			last_nest_day			[Integer]

			(Repeat this 3 times over)
			bird_exists 			[Boolean]
			is_bird_rare 			[Boolean]
			day_the_bird_got_here	[Integer]
			
			*/
			
			//Chonky file
			FILE * fgetbirdhinfo = fopen("BirdHousesInfo.txt", "r");
			fscanf(fgetbirdhinfo, "%d\n", &last_h_refreshed);
			fscanf(fgetbirdhinfo, "%d\n", &last_d_refreshed);
			fscanf(fgetbirdhinfo, "%d\n", &number_of_birds);
			fscanf(fgetbirdhinfo, "%d\n", &number_of_houses_broken);
			fscanf(fgetbirdhinfo, "%d\n", &number_of_unfinished_h);
			fscanf(fgetbirdhinfo, "%d\n", &number_of_h_w_itm);
			
			//Bandaid patch (house[i].item_id was turning into 0 when getting data from the file NO IDEA WHY)
			int temp_ids [3] = { 0 };
			
			for(int i = 0; i < 3; i ++){
				fscanf(fgetbirdhinfo, "%d\n", &house[i].can_have_bird);
				fscanf(fgetbirdhinfo, "%d\n", &house[i].has_item);
				fscanf(fgetbirdhinfo, "%d\n", &temp_ids[i]);
				fscanf(fgetbirdhinfo, "%d\n", &house[i].item_quantity);
				fscanf(fgetbirdhinfo, "%d\n", &house[i].has_bird);
				fscanf(fgetbirdhinfo, "%d\n", &house[i].bird_id);
				fscanf(fgetbirdhinfo, "%d\n", &house[i].nest_days_spent);
				fscanf(fgetbirdhinfo, "%d\n", &house[i].last_nest_day);
			}
			
			for(int i = 0; i < 3; i ++){
				fscanf(fgetbirdhinfo, "%d\n", &bird[i].bird_exists);
				fscanf(fgetbirdhinfo, "%d\n", &bird[i].is_bird_rare);
				fscanf(fgetbirdhinfo, "%d\n", &bird[i].day_the_bird_got_here);
			}
			
			fclose(fgetbirdhinfo);	
			
			//See if new bird can try to wander in
			if(number_of_birds != 3){
				if(TimeCalc("CHECK", 0, 0, 1) > last_d_refreshed && (last_h_refreshed + 5) - 24 < TimeCalc("CHECK", 0, 1, 0))
				try_to_spawn_new_bird = true;
				
				else if (TimeCalc("CHECK", 0, 1, 0) > last_h_refreshed + 5)
				try_to_spawn_new_bird = true;	
			}	
			
			//This is some needed checks to see if bird houses changed or not 
			for(int i = 0; i < 3; i ++){
				if(house[i].has_bird && bird[house[i].bird_id].day_the_bird_got_here + 3 <= TimeCalc("CHECK", 0, 0, 1)){
					bird[house[i].bird_id].day_the_bird_got_here = -1;
					house[i].has_bird = false;
					number_of_h_w_itm ++;
					house[i].has_item = true;
				}
				
				if(house[i].nest_days_spent < 10){
					house[i].nest_days_spent += abs(house[i].last_nest_day - TimeCalc("CHECK", 0, 0, 1));
					house[i].last_nest_day = TimeCalc("CHECK", 0, 0, 1);	
				}
				
				if(house[i].nest_days_spent >= 10){
					light_red;
					printf("A bird took the nest from house %d!\n", i + 1);
					white;
					house[i].can_have_bird = false;
				}
				
				//Wandering bird system
				if(try_to_spawn_new_bird && house[i].can_have_bird && !house[i].has_bird){
					house[i].has_bird = true;
					number_of_birds ++;
					
					for(int j = 0; j < 3; j ++){
						if(!bird[j].bird_exists){
							bird[j].bird_exists = true;
							bird[j].is_bird_rare = true;
							bird[j].day_the_bird_got_here = TimeCalc("CHECK", 0, 0, 1);
							house[i].bird_id = j;
						}
					}
				}
			}
			
			//We need this cause "house[i].item_id" bugged and turned the values into 0 during testing phase
			for(int i = 0; i < 3; i ++)
			house[i].item_id = temp_ids[i];	
			
		} else {
			last_h_refreshed = TimeCalc("CHECK", 0, 1, 0);
			last_d_refreshed = TimeCalc("CHECK", 0, 0, 1);
			number_of_houses_broken = 2;
			number_of_unfinished_h = 1;
			
			for(int i = 0; i < 3; i ++){
				house[i].can_have_bird = false;
				house[i].has_item = false;
				house[i].item_id = 0;
				house[i].item_quantity = 0;
				house[i].has_bird = false;
				house[i].bird_id = 0;
				house[i].nest_days_spent = 0;
				house[i].last_nest_day = 0;
				bird[i].bird_exists = false;
				bird[i].is_bird_rare = false;
				bird[i].day_the_bird_got_here = 0;
			}
			
			first_time = true;
		}
		
		while(true){
			
			//Update art code
			art_code = 0;
			
			if(number_of_houses_broken == 2)
			art_code += 100;
			
			else
			art_code += 200;
			
			if(number_of_unfinished_h == 1)
			art_code += 10;
			
			else
			art_code += 20;
			
			if(number_of_houses_broken >= 1)
			art_code += 1;
			
			else
			art_code += 2;
			
			//Code 1 means its broken and code 2 means its fixed
			Art("BIRD", art_code);
			ChangeCurPath("STASH.Animals");
			
			if(first_time){
				printf("\n");
				CenterText("It was a pretty idea to house the birds but its all abandoned");
				CenterText("I should fix them...\n");
				first_time = false;
			}
			
			printf("\nWhat to do...\n");
			
			if(number_of_houses_broken > 0)
			printf(">Fix a house [Fix]\n");
			
			if(number_of_unfinished_h > 0)
			printf(">Finish a house [Finish]\n");
			
			if(number_of_h_w_itm > 0)
			printf(">Check a bird house [House]\n");
			
			printf(">Nothing to do...[Back]\n");
			String_Input;
			
			if(strcmp(Input, "fix")== 0){
				if(number_of_houses_broken == 0){
					Error;
					
				} else {
					while(true){
						printf("Looks like you need to gather some wood\n");
					
						if(number_of_houses_broken == 2)
						printf("2x Ash Log, 3x Pine Log and 10x Sticks\n");
						
						else
						printf("3x Willow Log, 2x Birch Log and 8x Sticks\n");
						
						printf("Complete the bird house?\n");
						printf(">Yes\n");
						printf(">No\n");
						String_Input;
						
						if(strcmp(Input, "yes")== 0){
							
							if(number_of_houses_broken == 2){
								
								//Check if user has the items needed
								bool can_go = true;
								can_go = Inventory("CHECK", 106, -2);
								
								if(can_go){
									can_go = Inventory("CHECK", 103, -3);
									if(can_go)	
									can_go = Inventory("CHECK", 102, -10);
								}
								
								if(!can_go){
									red;
									printf("Looks like you dont have enough items!\n");
									white;
									Small_stop;
									break;
									
								} else {
									Inventory("CALC", 106, -2);
									Inventory("CALC", 103, -3);
									Inventory("CALC", 102, -10);
									
									green;
									printf("The house is back to normal and ready to be used!\n");
									white;
									house[0].can_have_bird = true;
									number_of_houses_broken --;
									Small_stop;
									break;
									
								}
								
							} else {
								//Check if user has the items needed
								bool can_go = false;
								can_go = Inventory("CHECK", 107, -3);
								
								if(can_go){
									can_go = Inventory("CHECK", 105, -2);
									if(can_go)	
									can_go = Inventory("CHECK", 102, -10);
								}
								
								if(!can_go){
									red;
									printf("Looks like you dont have enough items!\n");
									white;
									Small_stop;
									break;
									
								} else {
									Inventory("CALC", 107, -3);
									Inventory("CALC", 105, -2);
									Inventory("CALC", 102, -8);
									
									green;
									printf("The house is back to normal and ready to be used!\n");
									white;
									house[2].can_have_bird = true;
									number_of_houses_broken --;
									Small_stop;
									break;
								}
							}
							
						} else if(strcmp(Input, "no")== 0){
							
							CLR;
							break;
							
						} else {
							Error;
						}	
					}
				}
				
			} else if(strcmp(Input, "finish")== 0){
				if(number_of_unfinished_h == 0){
					Error;
					
				} else {
					while(true){
						printf("To build back this house you will need...\n");
						printf("7x Mapple Log and 5x Hickory Log and 15x Stick and 2x Bird Nest\n");
						
						printf("Finish the bird house?\n");
						printf(">Yes\n");
						printf(">No\n");
						String_Input;
						
						if(strcmp(Input, "yes")== 0){
							
							//Check if user has the items needed
							bool can_go = false;
							can_go = Inventory("CHECK", 109, -7);
							
							if(can_go){
								can_go = Inventory("CHECK", 104, -5);
								if(can_go){
									can_go = Inventory("CHECK", 102, -15);
									if(can_go)
									can_go = Inventory("CHECK", 108, -2);	
								}
							}
							
							if(!can_go){
								red;
								printf("Looks like you dont have enough items!\n");
								white;
								Small_stop;
								break;
								
							} else {
								Inventory("CALC", 109, -7);
								Inventory("CALC", 104, -5);
								Inventory("CALC", 102, -15);
								Inventory("CALC", 108, -2);
								
								green;
								printf("The house is back to normal and ready to be used!\n");
								white;
								number_of_unfinished_h --;
								house[1].can_have_bird = true;
								Small_stop;
								break;
							}
							
						} else if(strcmp(Input, "no")== 0){
							
							CLR;
							break;
							
						} else {
							Error;
						}
					}
				}
				
			} else if(strcmp(Input, "house")== 0){
				if(number_of_h_w_itm == 0){
					Error;
					
				} else {
					while(true){
						int what_house = 0;
						
						for(int i = 0; i < 3; i ++){
							if(house[i].has_item)
							printf("House %d [%d]\n", i + 1, i + 1);
						}	
						printf(">Back\n");
						
						String_Input;
						
						//To leave
						if(strcmp(Input, "back")!= 0)
						what_house = atoi(Input);
						
						else {
							CLR;
							break;
						}
						
						what_house --;
						
						//To stay
						if(house[what_house].has_item){
							
							printf("house[what_house].item_id? %d\n", house[what_house].item_id);
							printf("house[what_house].item_quantity? %d\n", house[what_house].item_quantity);
							
							house[what_house].has_item = false;
							if(house[what_house].item_id > 0 && house[what_house].item_quantity > 0){
								char * what_item = GetItemName(house[what_house].item_id);
								
								red;
								if(house[what_house].item_quantity > 1)
								printf("You still need to claim %dx %s!\n", house[what_house].item_quantity, what_item);
								
								else 
								printf("You still have a %s to claim!\n", what_item);
								white;
								
								int overflow = Inventory("CALC", house[what_house].item_id, house[what_house].item_quantity);
								
								if(overflow > 0){
									light_red;
									printf("You are still missing %dx %s!\n", overflow, what_item);
									white;	
									house[what_house].item_quantity = overflow;
									house[what_house].has_item = true;
									
								} else {
									light_green;
									printf("You claimed the rest of the items!\n");
									white;
									house[what_house].item_id = 0;
									house[what_house].item_quantity = 0;
									
								}
								
								free(what_item);
								Small_stop;
								break;
								
							}
							
							//Bird IS rare
							if(bird[house[what_house].bird_id].is_bird_rare){
								if(rand()% 10 + 1 == 1){
									light_green;
									printf("You found a special item! (Rusty Gear)\n");
									white;
									Inventory("CALC", 210, 1);
									number_of_h_w_itm --;
									Small_stop;
									break;
									
								} else {
									int quantity = 0, id = 0, what_itm = rand()% 50 + 1;
									
									if(what_itm >= 1 && what_itm <= 5){
										quantity = 3; id = 102;
									} else if(what_itm >= 6 && what_itm <= 15){
										quantity = 2; id = 5;
									} else if(what_itm >= 16 && what_itm <= 20){
										quantity = 3; id = 1;
									} else if(what_itm >= 21 && what_itm <= 30){
										quantity = 2; id = 126;
									} else if(what_itm >= 31 && what_itm <= 45){
										quantity = 2; id = 113;
									} else {
										quantity = 1; id = 108;
									}
									
									int over_spill = Inventory("CALC", id, quantity);
									char * item_name = GetItemName(id);
									
									if(over_spill != 0){
										red;
										printf("Looks like you didnt have enough space for %dx %s!\n", over_spill, item_name);
										white;
										house[what_house].has_item = true;
										house[what_house].item_id = id;
										house[what_house].item_quantity = over_spill;
																				
									} else {
										light_aqua;
										printf("You got %dx %s!\n", quantity, item_name);
										white;	
										number_of_h_w_itm --;
										house[what_house].item_id = 0;
										house[what_house].item_quantity = 0;
									}
									
									free(item_name);
									Small_stop;
									break;
								}
								
							//Birb isnt rare
							} else {
								int what_feather = rand()% 3 + 1;
								char * catch_new_name = GetItemName(38 + what_feather);
								
								int overspill = Inventory("CALC", 38 + what_feather, 1);
					
								if(overspill > 0){
									red;
									printf("Looks like you didnt have enough space to the %s...\n", catch_new_name);
									white;	
									house[what_house].has_item = true;
									house[what_house].item_id = 38 + what_feather;
									house[what_house].item_quantity = overspill;
									
								} else {
									green;
									printf("You got a %s!\n", catch_new_name);
									white;
									number_of_h_w_itm --;
									house[what_house].item_id = 0;
									house[what_house].item_quantity = 0;
									
								}
								
								free(catch_new_name);
								Small_stop;
								break;
								
							}
							
						} else {
							Error;
						}
					}
				}
				
			} else if(strcmp(Input, "back")== 0){
				
				ChangeCurPath("STASH.Animals");
				
				//Register changes made
				FILE * fgetbirdhinfo = fopen("BirdHousesInfo.txt", "w");
				fprintf(fgetbirdhinfo, "%d\n", TimeCalc("CHECK", 0, 1, 0));
				fprintf(fgetbirdhinfo, "%d\n", TimeCalc("CHECK", 0, 0, 1));
				fprintf(fgetbirdhinfo, "%d\n", number_of_birds);
				fprintf(fgetbirdhinfo, "%d\n", number_of_houses_broken);
				fprintf(fgetbirdhinfo, "%d\n", number_of_unfinished_h);
				fprintf(fgetbirdhinfo, "%d\n", number_of_h_w_itm);
				
				for(int i = 0; i < 3; i ++){
					fprintf(fgetbirdhinfo, "%d\n", house[i].can_have_bird);
					fprintf(fgetbirdhinfo, "%d\n", house[i].has_item);
					fprintf(fgetbirdhinfo, "%d\n", house[i].item_id);
					fprintf(fgetbirdhinfo, "%d\n", house[i].item_quantity);
					fprintf(fgetbirdhinfo, "%d\n", house[i].has_bird);
					fprintf(fgetbirdhinfo, "%d\n", house[i].bird_id);
					fprintf(fgetbirdhinfo, "%d\n", house[i].nest_days_spent);
					fprintf(fgetbirdhinfo, "%d\n", house[i].last_nest_day);
				}
				
				for(int i = 0; i < 3; i ++){
					fprintf(fgetbirdhinfo, "%d\n", bird[i].bird_exists);
					fprintf(fgetbirdhinfo, "%d\n", bird[i].is_bird_rare);
					fprintf(fgetbirdhinfo, "%d\n", bird[i].day_the_bird_got_here);
				}
				
				fclose(fgetbirdhinfo);
				
				CLR;
				break;
				
			} else {
				Error;
			}	
		}
		
	} else if(strcmp(Caller, "Cascade")== 0){
		
		/*
		Note to reader:
		
		This one is more simple because its LITERALY just a shop
		
		(Fisherman position 1 is idle)
		(Fisherman position 2 is selling smt)
		*/
		
		bool knows_ab_permit = false, has_permit = false;
		
		ChangeCurPath("OTHER.triggers.other");
		
		if(access("KnowsAbFishingPermit.txt", F_OK)== 0)
		knows_ab_permit = true;
		
		if(access("HasFishingPermit.txt", F_OK) == 0)
		has_permit = true;
		
		while(true){
			Art("FISHERMAN", 1);
			printf("[NPC] Fisherman: \"What do you want to buy?\"\n");
			printf(">More traps [Traps]\n");
			
			if(!knows_ab_permit && !has_permit)
			printf(">Whats a \"Fishing Permit\" [What]\n");
			
			else if(!has_permit && knows_ab_permit)
			printf(">Fishing Permit [Permit]\n");
			
			printf(">Nothing to shop here [Back]\n");
			String_Input;
			
			if(strcmp(Input, "traps")== 0){
				while(true){
					CLR;
					Art("FISHERMAN", 2);
				
					printf("[NPC] Fisherman: \"Well, you need to buy some traps?\"\n");
					printf("[NPC] Fisherman: \"How many do you need?\"\n");
					printf("[NPC] Fisherman: \"I sell them for 50 coins each!\"\n");
					String_Input;
					INT_Protocol;
					
					if(INT_Input <= 0){
						Error;	
						
					} else {
						bool failed = false;
						
						//Check moni
						if(money - (INT_Input * 50) < 0){
							printf("[NPC] Fisherman: \"Looks like you dont have enough money for that.\"\n");
							failed = true;
						} else 
						money -= INT_Input * 50;
						
						int overspill = 0;
						
						//Check Item overflow
						if(!failed)
						overspill = Inventory("CALC", 135, INT_Input);
						
						if(overspill > 0 && !failed){
							printf("[NPC] Fisherman: \"Looks like you dont have enough inventory space for that.\"\n");
							int displacement = INT_Input - overspill;
							displacement = -displacement;
							Inventory("CALC", 135, displacement);
							failed = true;
						}
						
						if(!failed){
							printf("[NPC] Fisherman: \"You bought %dx Traps!\"\n", INT_Input);	
						}
						
						Small_stop;
						break;
					}	
				}
				
			} else if(strcmp(Input, "what")== 0 && !knows_ab_permit){

				printf("[NPC] Fisherman: \"Basically a fishing permit just extends your trap limit by 1\"\n");
				printf("[NPC] Fisherman: \"You can get a fishing permit by catching a golden fish, its ");
				light_blue;
				printf("VERY");
				white;
				printf(" rare\"\n");
				printf("[NPC] Fisherman: \"So, good luck!\"\n");
				
				ChangeCurPath("OTHER.triggers.other");
				FILE * fknowsabpermit = fopen("KnowsAbFishingPermit.txt", "w");
				fclose(fknowsabpermit);
				
				knows_ab_permit = true;
				
				Small_stop;
				
			} else if(strcmp(Input, "permit")== 0 && !has_permit){
				while(true){
					Art("FISHERMAN", 2);
					
					printf("[NPC] Fisherman: \"Are you sure you what to buy a Fishing Permit? It requires a golden fish.\"\n");
					printf(">Yes i am sure [Yes]\n");
					printf(">Nevermind [No]\n");
					String_Input;
					
					if(strcmp(Input, "yes")== 0){
						bool has_fish = Inventory("CHECK", 134, -1);
						//Yes fish :>
						if(has_fish){
							Inventory("CALC", 134, -1);
							printf("[NPC] Fisherman: \"Congrats on your ");
							light_green;
							printf("Fishing Permit");
							white;
							printf("\"\n");
							
							has_permit = true;
							
							ChangeCurPath("OTHER.triggers.other");
							remove("KnowsAbFishingPermit.txt");
							FILE * fgotfishingpermit = fopen("HasFishingPermit.txt", "w");
							fclose(fgotfishingpermit);
							
							Small_stop;
						
						//No fish :<	
						} else {
							printf("[NPC] Fisherman: \"Looks like you didnt have the golden fish, too bad\"\n");
							Small_stop;
						}
						break;
						
					} else if(strcmp(Input, "no")== 0){
						CLR;
						break;
						
					} else {
						Error;
					}
				}
				
			} else if(strcmp(Input, "back")== 0){
				CLR;
				break;
				
			} else {
				Error;
			}	
			
		}
		
	} else if(strcmp(Caller, "Fungi")== 0){
		
		if(TimeCalc("CHECK", 0, 1, 0)== 3){
			ChangeCurPath("INVENTORY");
			char temp [50] = { '\0' };
			FILE * fgetspecialstats = fopen("SpecialStats.txt", "r");
			fgets(temp, 10, fgetspecialstats);
			memset(temp, '\0', sizeof(temp));
			fscanf(fgetspecialstats, "%s", temp);
			fclose(fgetspecialstats);
			
			if(strcmp(temp, "E9AR5")== 0){
				Art("RITUAL", 3);
				red;
				CenterText("THE KEY IS IN THE EXPOIT");
				CenterText("THERE IS SOMEONE YOU NEED TO MEET");
				CenterText("THIS IS A DISTRACTION");
				CenterText("FOLLOW THE PATH");
				CenterText("YOUR TIME WILL COME");
				white;
				Small_stop;
				return;
			}
		}
		
		while(true){
			Art("RITUAL", 1);
		
			printf("Its a strange ritual...\n");
			printf("Examine?\n");
			printf(">Yes\n");
			printf(">No\n");
			String_Input;	
			
			if(strcmp(Input, "yes")== 0){
				
				Art("RITUAL", 2);
				
				printf("\n\n");
				red;
				CenterText("SET SIGNAL TO E9AR5");
				CenterText("APEAR AT 3(h)");
				CenterText("LISTEN TO US");
				CenterText("LISTEN TO THE TRUTH");
				CenterText("FOLLOW OUR VOICES");
				CenterText("SEE YOU SOON");
				white;
				Small_stop;
				break;
				
			} else if(strcmp(Input, "no")== 0){
				
				CLR;
				break;
				
			} else {
				Error;
			}
		}		
		
	} else if(strcmp(Caller, "Geysers")== 0){
		
	} else if(strcmp(Caller, "Blossom")== 0){
		
	} else if(strcmp(Caller, "Peak")== 0){
		
	} else {
		CLR;
		red;
		printf("Unknown Location (SpecialLocations Function ARG error)\n");
		white;
		Small_stop;
		return;
	}
	
	return;
}

int TimeCalc(const char *MODE, const long int timer, const int hour, const long int day){
	
	int backUp_time, backUp_hour, h = 10;
	long int t = 0, d = 0;
	
	//Change directory to "TIME"
	ChangeCurPath("TIME");
	
	//Get vars from file
	if(access("Time.txt", F_OK)== 0){
		FILE * ftime = fopen("Time.txt", "r");
		fscanf(ftime, "%d", &t);
		fscanf(ftime, "%d", &h);
		fscanf(ftime, "%d", &d);
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
				//Set Vars.
				char Current_Weather [10];
				
				ChangeCurPath("STORY");
				
				int weather = rand()% 10 + 1;
				
				if(weather >= 1 && weather <= 4)
				strcpy(Current_Weather, "Rain");
					
				else if(weather == 5)
				strcpy(Current_Weather, "Thunder");
				
				else 
				strcpy(Current_Weather, "Clear");
				
				//Save Current Weather and Weather day in the weather file
				ChangeCurPath("STORY");
				FILE * fweather = fopen("Weather.txt", "w");
				fprintf(fweather, "%s\n", Current_Weather);
				fclose(fweather);
				
				if(DEBUG_MODE){
					printf("[DEBUG] _> Current Weather? \"%s\"\n", Current_Weather);
					sleep(3);
					CLR;
				}
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
		
		backUp_time = t;
		
	    //Timer gets reset
	    t = 0;
	    t = backUp_time;
	    
	    //Calculates the remaning hours after 24 hours pass [positive]
	    if(h >= 24){
		    while(h >= 24){
		    	d ++;
		        h = 24 - h;
		        h = abs(h);
		    }
		}
		
		//Also we check for time dependent things over here
		ChangeCurPath("OTHER.activepots");
		
		int pot_hour = 0, pot_day = 0;
		char pot_name [25] = { '\0' };
		bool expired = false;
		
		for(int i = 0; i < 10; i ++){
			expired = false;
			char file_name [6] = { '\0' };
			itoa(i, file_name, 10);
			strcat(file_name, ".txt");
			if(access(file_name, F_OK)== 0){
				FILE * fchangepotsactive = fopen(file_name, "r");
				fscanf(fchangepotsactive, "%d\n", &pot_hour);
				fscanf(fchangepotsactive, "%d\n", &pot_day);
				fgets(pot_name, 25, fchangepotsactive);
				fclose(fchangepotsactive);
				
				if(h >= pot_hour){
					if(d >= pot_day)
					expired = true;	
				}
				
				else if(d > pot_day)
				expired = true;
				
				if(expired){
					remove(file_name);
					pot_name[strlen(pot_name) - 1] =  '\0';
					printf("Your \"%s\" expired!\n", pot_name);
					sleep(3);
					CLR;
				}
			}
		}
		
	}
	
	ChangeCurPath("TIME");
	if(strcmp(MODE, "CALC_EXT")== 0){
		printf("EXTRAS ONLY, AFTER CALC?\n");
		
		printf("Timer? %d\n", t);
		printf("Hour? %d\n", h);
		printf("Day? %d\n", d);
	}
	
	//Save the time data on the file
	FILE * ftime = fopen("Time.txt", "w");
	fprintf(ftime, "%d\n", t);
	fprintf(ftime, "%d\n", h);
	fprintf(ftime, "%d\n", d);
	fclose(ftime);
	
	chdir("..");
    return 0;   //default exit (no err.)
}

int Inventory(const char *Inv_call, const int ID, const int Quantity){
	
	//Change to the inventory dir
	ChangeCurPath("INVENTORY");
	
	const unsigned int INV_LIMIT = 300;
	int CUR_INV_ITM = 0, farm_itm_c = 0, livestock_itm_c = 0, fishing_itm_c = 0, foraging_itm_c = 0, alch_itm_c = 0, extra_itm_c = 0;
	
	//Some ids are invalid because they are placeholders for other stuff
	
	int List_Quantities[136];
	memset(List_Quantities, 0, sizeof(List_Quantities));
	
	//Check if there is alr a save done
	if(access("Crops.txt", F_OK)== 0){
		int i;
		
		//Save the chest invntory in the files set in the CHEST dir
		FILE * fcrop = fopen("Crops.txt", "r");
		for(i = 1; i < 36; i ++)
		fscanf(fcrop, "%d\n", &List_Quantities[i]);
		fclose(fcrop);
		
		FILE * fanimal = fopen("Animals.txt", "r");
		for(i = 36; i < 46; i ++)
		fscanf(fanimal, "%d\n", &List_Quantities[i]);
		fclose(fanimal);
		
		FILE * ffish = fopen("Fish.txt", "r");
		for(i = 46; i < 102; i ++)
		fscanf(ffish, "%d\n", &List_Quantities[i]);
		fclose(ffish);
		
		FILE * fforaging = fopen("Foraging.txt", "r");
		for(i = 102; i < 116; i ++)
		fscanf(fforaging, "%d\n", &List_Quantities[i]);
		fclose(fforaging);
		
		FILE * falchemy = fopen("Alchemy.txt", "r");
		for(i = 116; i < 126; i ++)
		fscanf(falchemy, "%d\n", &List_Quantities[i]);
		fclose(falchemy);
		
		FILE * fextras = fopen("Extras.txt", "r");
		for(i = 126; i < 135; i ++)
		fscanf(fextras, "%d\n", &List_Quantities[i]);
		fclose(fextras);
		
		FILE * futility = fopen("Utility.txt", "r");
		fscanf(futility, "%d\n", &List_Quantities[135]);
		fclose(futility);
	}
	
	for(int i = 1; i <= 35; i ++)
	farm_itm_c += List_Quantities[i];
	
	for(int i = 36; i <= 45; i ++)
	livestock_itm_c += List_Quantities[i];
	
	for(int i = 47; i <= 101; i ++)
	fishing_itm_c += List_Quantities[i];
	
	for(int i = 102; i <= 115; i ++)
	foraging_itm_c += List_Quantities[i];
	
	for(int i = 116; i <= 125; i ++)
	alch_itm_c += List_Quantities[i];
	
	for(int i = 126; i <= 134; i ++)
	extra_itm_c += List_Quantities[i];
	
	//Check current inv space
	CUR_INV_ITM = farm_itm_c + livestock_itm_c + fishing_itm_c + foraging_itm_c + alch_itm_c + extra_itm_c;	
	CUR_INV_ITM += List_Quantities[135];
	
	if(strcmp(Inv_call, "SHOW")== 0 || strcmp(Inv_call, "ID")== 0){
		
		//Note: Special returns - 0  means No item and -99999 means theres nothing in inv
		
		chdir("..");
		
		//declare assisting vars to organize inv
		bool crops[7], animals[3], ponds[8], trees[4], Alchemy = false, Extras = false, leave_inv = false;
		memset(crops, false, sizeof(crops));
		memset(animals, false, sizeof(animals));
		memset(ponds, false, sizeof(ponds));
		memset(trees, false, sizeof(trees));
				
		//Check crop quantity
		for(int i = 0; i < 7; i ++){
			for(int j = 0; j < 5; j ++){
				if(List_Quantities[(j + 1) * (i + 1)] > 0){
					crops[i] = true;
					break;
				}
			}
		}
		
		//Check livestock quantity
		for(int i = 0; i < 3; i ++){
			for(int j = 0; j < 3; j ++){
				if(List_Quantities[((j + 1) * (i + 1) + 35)] > 0){
					animals[i] = true;
					break;
				}
			}
		}
		
		//Check fishing quantity
		for(int i = 0; i < 8; i ++){
			for(int j = 0; j < 6; j ++){
				if(List_Quantities[((j + 2) * (i + 1) + 45)] > 0){
					ponds[i] = true;
					break;
				}
			}
		}
		
		//Checking for trees
		//tree 1
		for(int i = 103; i <= 108; i ++){
			if(List_Quantities[i] > 0){
				trees[0] = true;
				break;
			}
		}
		
		//tree 2
		for(int i = 109; i <= 110; i ++){
			if(List_Quantities[i] > 0){
				trees[1] = true;
				break;
			}
		}
		
		//tree 3
		for(int i = 111; i <= 113; i ++){
			if(List_Quantities[i] > 0){
				trees[2] = true;
				break;
			}
		}
		
		//tree 4
		for(int i = 114; i <= 115; i ++){
			if(List_Quantities[i] > 0){
				trees[3] = true;
				break;
			}
		}
		
		//Check alchemy quantity
		for(int i = 116; i < 126; i ++){
			if(List_Quantities[i] > 0){
				Alchemy = true;
				break;
			}
		}
		
		//Check for extras quantity
		for(int i = 126; i < 135; i ++){
			if(List_Quantities[i] > 0){
				Extras = true;
				break;
			}
		}
		
		while(true){
			
		CLR;
		
		//Note for reader: i really dont know how to make this compact, i tried
		printf("Money? %d\n", money);
		
		short int cnt = 0;
		
		for(int i = 0; i < 136; i ++){
			if(List_Quantities[i] <= 0)
			cnt++;
		}		
		
		//no items (brokie LMAO)
		if(cnt == 136){
			red;
			printf("\n\nNothing but spider webs here\n\n");
			white;
			Small_stop;
			return -99999;
		} else {
			if(div_inv_sect){
				
				while(true){
					bool no_break = false;	
					
					printf("What category do you want to see?\n");
					printf(">Farming\n");
					printf(">Livestock\n");
					printf(">Fishing\n");
					printf(">Foraging\n");
					printf(">Alchemy\n");
					printf(">Extras\n");
					printf(">Leave\n");
					String_Input;
					
					for(int i = 0; i < 6; i ++)
					arr_limit_inv[i] = false;
					
					if(strcmp(Input, "farming")== 0)
					arr_limit_inv[0] = true;
					
					else if(strcmp(Input, "livestock")== 0)
					arr_limit_inv[1] = true;
					
					else if(strcmp(Input, "fishing")== 0)
					arr_limit_inv[2] = true;
					
					else if(strcmp(Input, "foraging")== 0)
					arr_limit_inv[3] = true;
					
					else if(strcmp(Input, "alchemy")== 0)
					arr_limit_inv[4] = true;
					
					else if(strcmp(Input, "extras")== 0)
					arr_limit_inv[5] = true;
					
					else if(strcmp(Input, "leave")== 0)
					return 0;
					
					else { Error; no_break = true; }
					
					
					if(!no_break)
					break;
					
				}
			}
		}
		
		if(arr_limit_inv[0]){
			
			//FARMING	
			if(memchr(crops, true, sizeof(crops)) != NULL)
			printf("\nFarming items [%d]\n\n", farm_itm_c);
			
			//CROP 1
			if(crops[0]){
				printf("[FROM: HERB GARDEN] _> 1.Basil? %d / 2. Oregano? %d / 3. Mint? %d / 4. Thyme? %d / 5. Worm? %d\n", 
				List_Quantities[1], List_Quantities[2], List_Quantities[3], List_Quantities[4], List_Quantities[5]);
			}
			
			//CROP 2
			if(crops[1]){
				printf("[FROM: FLOREST] _> 6.Potato? %d / 7. Carrot? %d / 8. Wheat? %d / 9. Rice? %d / 10. Cabbage? %d\n", 
				List_Quantities[6], List_Quantities[7], List_Quantities[8], List_Quantities[9], List_Quantities[10]);
			}
			
			//CROP 3
			if(crops[2]){
				printf("[FROM: FUNGI (1)] _> 11.Tomato? %d / 12. Cucumber? %d / 13. Lettuce? %d / 14. Pepper? %d / 15. Bean? %d\n", 
				List_Quantities[11], List_Quantities[12], List_Quantities[13], List_Quantities[14], List_Quantities[15]);
			}
			
			//CROP 4
			if(crops[3]){
				printf("[FROM: FUNGI (2)] _> 16.Honey Mushroom? %d / 17. Hedgehog Mushroom? %d / 18. Chicken of the Woods? %d / 19. Hen of the Woods? %d / 20. Abortive Entoloma? %d\n", 
				List_Quantities[16], List_Quantities[17], List_Quantities[18], List_Quantities[19], List_Quantities[20]);
			}
			
			//CROP 5
			if(crops[4]){
				printf("[FROM: FUNGI (3)] _> 21.Corn? %d / 22. Onion? %d / 23. Pea? %d / 24. Asparagus ? %d / 25. Broccoli? %d\n", 
				List_Quantities[21], List_Quantities[22], List_Quantities[23], List_Quantities[24], List_Quantities[25]);
			}
			
			//CROP 6
			if(crops[5]){
				printf("[FROM: GERSYERS]_> 26.Blackberry? %d / 27. Blueberry? %d / 28. Strawberry? %d / 29. Cape Gooseberry? %d / 30. Raspberry? %d\n", 
				List_Quantities[26], List_Quantities[27], List_Quantities[28], List_Quantities[29], List_Quantities[30]);	
			}
			
			//CROP 7
			if(crops[6]){
				printf("[FROM: BLOSSOM] _> 31.Sunflower? %d / 32. Allium? %d / 33. Milkweed? %d / 34. Poppies? %d / 35. Beebalms? %d\n\n", 
				List_Quantities[31], List_Quantities[32], List_Quantities[33], List_Quantities[34], List_Quantities[35]);
			}
			
		} 
		
		if(arr_limit_inv[1]){
		
			//LIVESTOCK
			if(memchr(animals, true, sizeof(animals)) != NULL)
			printf("\nLivestock items [%d]\n\n", livestock_itm_c);
			
			//ANIMAL 1
			if(animals[0]){
				printf("[FROM: HERB GARDEN] _> 36.Egg? %d / 37. Wool? %d / 38. Milk? %d\n", 
				List_Quantities[36], List_Quantities[37], List_Quantities[38]);
			}
				
			//ANIMAL 2
			if(animals[1]){
				printf("[FROM: BIRDHOUSES] _> 39.Flight Feather? %d / 40. Down Feather? %d / 41. Tail Feather? %d\n", 
				List_Quantities[39], List_Quantities[40], List_Quantities[41]);
			}
			
			//ANIMAL 3
			if(animals[2]){
				printf("[FROM: BEHIVE] _> 43.Honey? %d / 44. Pollen? %d / 45. Beeswax? %d\n\n", 
				List_Quantities[43], List_Quantities[44], List_Quantities[45]);
			}
		
		} 
		
		if(arr_limit_inv[2]){
		
			//FISHING
			if(memchr(ponds, true, sizeof(ponds)) != NULL)
			printf("\nFishing items [%d]\n\n", fishing_itm_c);
			
			//POND 1
			if(ponds[0]){
				printf("[FROM: TROUT POND] _> 47. ? Trout? %d / 48. Not a Trout? %d / 49. Strange Trout? %d / ", 
				List_Quantities[47], List_Quantities[48], List_Quantities[49]);
				printf("50. Undefined Trout? %d / 51. Lost Trout? %d / 52. Unknown Trout? %d\n", 
				List_Quantities[50], List_Quantities[51], List_Quantities[52]);
			}
			
			//POND 2
			if(ponds[1]){
				printf("[FROM: BASS POND] _> 54. Medium Bass? %d / 55. Atomic Bass? %d / 56. Enormous Bass? %d / ", 
				List_Quantities[54], List_Quantities[55], List_Quantities[56]);
				printf("57. Half Bass? %d / 58. Big Bass? %d / 59. Small Bass? %d\n", 
				List_Quantities[57], List_Quantities[58], List_Quantities[59]);
			}
			
			//POND 3
			if(ponds[2]){
				printf("[FROM: CARP POND] _> 61. Lilac Carp? %d / 62. Coral Carp? %d / 63. Lime Carp? %d / ", 
				List_Quantities[61], List_Quantities[62], List_Quantities[63]);
				printf("64. Lavender Carp? %d / 65. Rainbow Carp? %d / 66. Fulvous Carp? %d\n", 
				List_Quantities[64], List_Quantities[65], List_Quantities[66]);
			}
			
			//POND 4
			if(ponds[3]){
				printf("[FROM: CATFISH POND] _> 68. Wise Catfish? %d / 69. Dumb Catfish? %d / 70. Thinking Catfish? %d / ", 
				List_Quantities[68], List_Quantities[69], List_Quantities[70]);
				printf("71. Curious Catfish? %d / 72. Happy Catfish? %d / 73. Frowning Catfish? %d\n", 
				List_Quantities[71], List_Quantities[72], List_Quantities[73]);
			}
			
			//POND 5
			if(ponds[4]){
				printf("[FROM: SHINER POND] _> 75. Horizontal Shiner? %d / 76. Vertical Shiner? %d / 77. Oblique Shiner? %d / ", 
				List_Quantities[75], List_Quantities[76], List_Quantities[77]);
				printf("78. Non-Linear Shiner? %d / 79. Upside-down Shiner? %d / 80. Downside-up Shiner? %d\n", 
				List_Quantities[78], List_Quantities[79], List_Quantities[80]);
			}
			
			//POND 6
			if(ponds[5]){
				printf("[FROM: SNAPPER POND] _> 82. Fat Snapper? %d / 83. Skinny Snapper? %d / 84. Smooth Snapper? %d / ", 
				List_Quantities[82], List_Quantities[83], List_Quantities[84]);
				printf("85. Stiff Snapper? %d / 86. Soft Snapper? %d / 87. Rough Snapper? %d\n", 
				List_Quantities[85], List_Quantities[86], List_Quantities[87]);
			}
			
			//POND 7
			if(ponds[6]){
				printf("[FROM: TUNA POND] _> 89. Fast Tuna? %d / 90. Slow Tuna? %d / 91. Quick Tuna? %d / ", 
				List_Quantities[89], List_Quantities[90], List_Quantities[91]);
				printf("92. Dull Tuna? %d / 93. Speedy Tuna? %d / 94. Delayed Tuna? %d\n", 
				List_Quantities[92], List_Quantities[93], List_Quantities[94]);
			}
			
			//POND 8
			if(ponds[7]){
				printf("[FROM: SALMON POND] _> 96. Commun Salmon? %d / 97. Uncommun Salmon? %d / 98. Rare Salmon? %d / ", 
				List_Quantities[96], List_Quantities[97], List_Quantities[98]);
				printf("99. Epic Salmon? %d / 100. Legendary Salmon? %d / 101. Mythical Salmon? %d\n", 
				List_Quantities[99], List_Quantities[100], List_Quantities[101]);
			}
		
		} 
		
		if(arr_limit_inv[3]){
		
			//FORAGING
			if(memchr(trees, true, sizeof(trees)) != NULL)
			printf("\nForaging items [%d]\n\n", foraging_itm_c );
			
			if(List_Quantities[102] > 0)
			printf("[FROM: EVERYWHERE] _> 102. Stick? %d\n", List_Quantities[102]);
			
			//TREE 1
			if(trees[0]){
				printf("[FROM: FLOREST] _> 103. Pine Log? %d / 104. Hickory Log? %d / 105. Birch Log? %d / ", 
				List_Quantities[103], List_Quantities[104], List_Quantities[105]);
				printf("106. Ash Log? %d / 107. Willow Log? %d / ", 
				List_Quantities[106], List_Quantities[107]);
				printf("108. Bird nest? %d\n", List_Quantities[108]);
			}
			
			//TREE 2
			if(trees[1])
			printf("[FROM: CASCADE] _> 109. Mapple Log? %d / 110. Pinecone? %d\n", List_Quantities[109], List_Quantities[110]);
			
			
			//TREE 3
			if(trees[2]){
				printf("[FROM: GEYSERS] _> 111.Acacia Log? %d / ", List_Quantities[111]);
				printf("112. Oak Log? %d / 113. Medronhos Fruit? %d\n", List_Quantities[112], List_Quantities[113]);
			}
			
			//TREE 4
			if(trees[3])
			printf("[FROM: BLOSSOM] _> 114. Mimosa Log? %d / 115. Jackfruit? %d\n", List_Quantities [114], List_Quantities[115]);
			
		} 
		
		if(arr_limit_inv[4]){
					
			//ALL ALCHEMY
			if(Alchemy){
				printf("\nAlchemy items [%d]\n\n", alch_itm_c);
				
				printf("[ALCHEMY ITEMS (1)] _> 116. Refresher? %d / 117. Mint Tea? %d / 118. Woods Water? %d\n", 
				List_Quantities[116], List_Quantities[117], List_Quantities[118]);
				printf("[ALCHEMY ITEMS (2)] _> 119. Hidden Bush? %d / 120. Time Decline? %d / 121. Happy Acident? %d\n", 
				List_Quantities[119], List_Quantities[120], List_Quantities[121]);
				printf("[ALCHEMY ITEMS (3)] _> 122. Early Grave? %d / 123. Lots of Fish Bones? %d / 124. High risk, Low reward? %d / 125. Im Special! %d\n", 
				List_Quantities[122], List_Quantities[123], List_Quantities[124], List_Quantities[125]);
			}
		
		} 
		
		if(arr_limit_inv[5]){
		
			//ALL EXTRAS
			if(Extras){
				printf("\nExtra items [%d]\n\n", extra_itm_c);
				
				printf("[EXTRA ITEMS (1)] _> 126. Leaves? %d / 127. Algae? %d / 128. Japanese Iris? %d\n", 
				List_Quantities[126], List_Quantities[127], List_Quantities[128]);
				printf("[EXTRA ITEMS (2)] _> 129. Water Lily? %d / 130. Apple Snail? %d / 131. Mediterranean Tree Frog? %d\n", 
				List_Quantities[129], List_Quantities[130], List_Quantities[131]);
				printf("[EXTRA ITEMS (3)] _> 132. Iberian Water Frog? %d / 133. Giant Freshwater Prawn (Shrimp)? %d / 134. Golden Fish? %d\n", 
				List_Quantities[132], List_Quantities[133], List_Quantities[134]);
			}
		
		} 
		
		printf("\n");
			
		if(strcmp(Inv_call, "SHOW")== 0){
		Small_stop;
		
		} else if(strcmp(Inv_call, "ID")== 0){
			int call_id, call_quantity;
			
			while(true){
				printf("\nPlease select the ID of the item\n");
				printf("&/");
				scanf("%d", &call_id);
				
				CLR;
				
				if((call_id < 1 || call_id > 135) || List_Quantities[call_id] <= 0
				|| (call_id == 42 || call_id == 46 || call_id == 53 || call_id == 60 || 			//These ids are reserved for
				call_id == 67 || call_id == 74 || call_id == 81 || call_id == 88 || call_id == 95))	//rand fish trash special itm
				printf("\n\nInvalid ID, dosent exist OR quantity of that ID is 0\n\n");				//and also bird trash special itm
				
				else
				break;
			}
			
			while(true){
				printf("\nPlease select the QUANTITY of the item\n");
				printf("&/");
				scanf("%d", &call_quantity);
				
				CLR;
				
				if(call_quantity > List_Quantities[call_id])
				printf("\n\nInvalid QUANTITY, the quantity you are asking for is above the one you have :>\n\n");
				
				else
				break;
			}
			
			//info = [QUANTITY][ID] [AKA] QUANTITY * 1000
			//Exmp QUANTITY = 12 / ID = 23 / info = 12023 (gets decoded in caller function)
			int info = 0;
			info = call_id;
			call_quantity *= 1000;
			info += call_quantity;
			
			return info;
		}
		
		}
		
		CLR;
		
	} else if(strcmp(Inv_call, "CALC")== 0){
		
		if(ID >= 200){
			//We update the file depending on the ID number that was given
			int line_to_modify = ID - 200;
			FILE * fspecials = fopen("Specials.txt", "r");
			FILE * ftemp = fopen("__temp.txt", "w");
			
			int cur_line = 0, cur_val = 0;
			
			while(fscanf(fspecials, "%d\n", &cur_val)!= EOF){
				
				if(cur_line == line_to_modify)
				fprintf(ftemp, "1\n");
				
				else
				fprintf(ftemp, "%d\n", cur_val);
				
				cur_line ++;
			}
			
			fclose(fspecials);
			fclose(ftemp);
			
			remove("Specials.txt");
			rename("__temp.txt", "Specials.txt");
			
			return 0;
		}
		
		//Remaking this from scratch (V3)
		if((CUR_INV_ITM <= INV_LIMIT && Quantity < 0) || (CUR_INV_ITM >= 0 && Quantity > 0)){
			
			int bckp_id = List_Quantities[ID];
			int BCKP_CUR_INV = CUR_INV_ITM;
			CUR_INV_ITM += Quantity;
			
			//Positive quantity handeling
			if(Quantity > 0){
				
				if(CUR_INV_ITM > INV_LIMIT){	//Over limit? Calculate (over)flow
					Overflow_Value = CUR_INV_ITM - INV_LIMIT;
					List_Quantities[ID] += Quantity - Overflow_Value;
				} else {
					List_Quantities[ID] += Quantity;
					Overflow_Value = 0;
				}
				Small_stop;
				
			//Negative quantity handeling
			} else {
				
				List_Quantities[ID] += Quantity;
				
				if(CUR_INV_ITM < 0 || List_Quantities[ID] < 0){
					List_Quantities[ID] = bckp_id;			//Under limit? Calculate (under)flow
					Overflow_Value = Quantity + bckp_id;
					List_Quantities[ID] += Quantity + abs(Overflow_Value);
				} else {
					List_Quantities[ID] = bckp_id;	
					List_Quantities[ID] += Quantity;
					Overflow_Value = 0;
				}
				
			}
			
		//Inv is alr full or empty
		} else {
			red;
			if(CUR_INV_ITM >= INV_LIMIT && Quantity >= 0)
			printf("Inventory Full.\n");
			
			else if(CUR_INV_ITM < 0)
			printf("Inventory VERY Empty.\n");	//Not supost to show up unless something bugs out
			
			Overflow_Value = Quantity;
			white;
			sleep(2);
			CLR;
		}
		
	} else if(strcmp(Inv_call, "CHECK")== 0){
		
		if(ID < 200){
			//Quantity is always negative for "CHECK" argument
			int possible_overflow = List_Quantities[ID] += Quantity;
			
			//Return arguments depending if user has it or not
			if(possible_overflow > -1)
			return 1;		//TRUE (has)
			
			else
			return 0;		//FALSE	
				
		} else {
			int what_line = ID - 200, yes = 0;
			
			//Check if item exists (these are booleans)
			FILE * fspecials = fopen("Specials.txt", "r");
			for(int i = 0; i < what_line + 1; i ++)
			fscanf(fspecials, "%d\n", &yes);
			fclose(fspecials);
			
			if(yes == 1)
			return 1;		//TRUE (has)
			
			else 
			return 0;		//FALSE
			
		}
		
	} else { printf("[SYSTEM] _> WRONG INV_CALL ARGUMENT LOLLLL\n"); }
	
	int i;
	//Save the current inventory in the files set in the INVENTORY dir
	FILE * fcrop = fopen("Crops.txt", "w");
	for(i = 1; i < 36; i ++)
	fprintf(fcrop, "%d\n", List_Quantities[i]);
	fclose(fcrop);
	
	FILE * fanimal = fopen("Animals.txt", "w");
	for(i = 36; i < 46; i ++)
	fprintf(fanimal, "%d\n", List_Quantities[i]);
	fclose(fanimal);
	
	FILE * ffish = fopen("Fish.txt", "w");
	for(i = 46; i < 102; i ++)
	fprintf(ffish, "%d\n", List_Quantities[i]);
	fclose(ffish);
	
	FILE * fforaging = fopen("Foraging.txt", "w");
	for(i = 102; i < 116; i ++)
	fprintf(fforaging, "%d\n", List_Quantities[i]);
	fclose(fforaging);
	
	FILE * falchemy = fopen("Alchemy.txt", "w");
	for(i = 116; i < 126; i ++)
	fprintf(falchemy, "%d\n", List_Quantities[i]);
	fclose(falchemy);
	
	FILE * fextras = fopen("Extras.txt", "w");
	for(i = 126; i < 135; i ++)
	fprintf(fextras, "%d\n", List_Quantities[i]);
	fclose(fextras);
	
	FILE * futility = fopen("Utility.txt", "w");
	fprintf(futility, "%d\n", List_Quantities[135]);
	fclose(futility);
	
	return Overflow_Value;
}

char * GetItemName(int ID){
	
	//My head hurts but i think this should work
	char * Item_Name = (char *)malloc(30);
	
	GetAppResources("Usefull Files.Items");
	
	if(ID <= 200){
		//Get Item from file (no way)
		FILE * fgetitemname = fopen("ItemNames.txt", "r");
		for(int i = 0; i < ID; i ++){
			memset(Item_Name, '\0', sizeof(Item_Name));
			fgets(Item_Name, 30, fgetitemname);
		}
		fclose(fgetitemname);	
		
	} else {
		ID -= 200;
		FILE * fgetspecialitemname = fopen("SpecialItemNames.txt", "r");
		for(int i = 0; i < ID; i ++){
			memset(Item_Name, '\0', sizeof(Item_Name));
			fgets(Item_Name, 30, fgetspecialitemname);
		}
		fclose(fgetspecialitemname);
		
	}
	
	if(Item_Name[0] == '\0'){
		strcpy(Item_Name, "Item not found..");
	}
	
	Item_Name[strlen(Item_Name) - 1] = '\0';
	return Item_Name;
}

int Art(const char *CALLER, const int Parameter){
	
	/*
	Note to reader:
	
	No, i dont know of a better way to format the text
	*/
	
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
	
	if(access(temp_str, F_OK)!= 0)	//Error code
	return -1;
	
	//Extract the needed info from the file
	FILE * facessedart = fopen(temp_str, "r");
	
	while(fgets(ARTLINE, 256, facessedart)!= NULL){
		ARTLINE[strlen(ARTLINE) - 1] = '\0';	//Prevent fgets from putting \n at the end
		
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
}

//Creates random words with a certain number of spaces
char * EncryptedWordsV1(short int *num_of_spaces){
	
	const char possible_chars [78] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
	'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
	'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '?', '=', '+', '-', '*', '/', '#', '<', '>', '.',
	':', '@', '_', ';', '^', ','};
	
	short int string_size, word_chosen, curr_word = 0;
	char *final_str = (char *)malloc(555);
	memset(final_str, '\0', 555);
	
	for(int i = 0; i < *num_of_spaces; i ++){
		string_size = rand()% 10 + 3;
		string_size += 2;
		
		for(int j = 0; j < string_size; j ++){
			word_chosen = rand()% 78 + 1;
			word_chosen -= 1;
			final_str[curr_word] = possible_chars [word_chosen];
			curr_word ++;
		}
		
		final_str[curr_word] = ' ';
		curr_word ++;
	}
	
	return final_str;
}

char * EncryptedWordsV2(const char * line){
	
	char * final_str = (char *)malloc(sizeof(char) * 555);
	memset(final_str, '\0', 555);

	short int cur_char = 0, stop_when_value_is_reached = strlen(line);

	while(cur_char < stop_when_value_is_reached){
		while(line[cur_char] != ' ' && cur_char < stop_when_value_is_reached){
			int rand_num = rand()% 93 + 1;
			rand_num += 32;

			final_str[cur_char] = rand_num;
			cur_char ++;
		}

		final_str[cur_char] = ' ';
		cur_char ++;
	}

	return final_str;
}

//Read (and format) txt files!
void ReadTextFile(const char *FileName, const char *specifications){
	
	/*
	Programer note:
	
	"rules_gotten" array is like this
	[INDEX] [WHAT RULE]
	0 	-> Show Formating?
	1 	-> Dont Format?
	2	-> Show Line Number?
	3 	-> Center (ALL) Text?
	4	-> Put (ALL) text on right side?
	5	-> Put (ALL) text in the middle?
	6	-> Ignore /W/ commands
	7	-> Read each line with a certain amount of ms delay
	
	More rules yet to come :>
	*/
	
	char * FileNametemp = (char *)malloc(20);
	strcpy(FileNametemp, FileName);
	bool rules_gotten [10] = { 0 };
	
	//Get page and display it IF its UsersBook
	if(strcmp(FileNametemp, "UsersBook.dir")== 0){
		FILE * finst = fopen("CurPage.txt", "r");
		fscanf(finst, "%s", FileNametemp);
		fclose(finst);
		rules_gotten[2] = true;
		char temp = '\0';
		printf("Current Page? %c\n\n", FileNametemp[0]);
	}
	
	//SLOWREAD IS A SPECIAL CASE
	char * specifications_copy = (char *)malloc(555);
	strcpy(specifications_copy, specifications);
	char * cur_par, temp_char = '\0';
	char delim [2] = ".";
	int cur_line = 1, rule7_wait_time = 0;
	
	cur_par = strtok(specifications_copy, delim);
	
	//Here we get all special requests made
	while(cur_par != NULL){
		if(strcmp(cur_par, "showformating")== 0)
		rules_gotten[0] = true;
		
		else if(strcmp(cur_par, "dontformat")== 0)
		rules_gotten[1] = true;
		
		else if(strcmp(cur_par, "showlinenum")== 0)
		rules_gotten[2] = true;
		
		else if(strcmp(cur_par, "centertext")== 0)
		rules_gotten[3] = true;
		
		else if(strcmp(cur_par, "righttext")== 0)
		rules_gotten[4] = true;
		
		else if(strcmp(cur_par, "middletext")== 0)
		rules_gotten[5] = true;
		
		else if(strcmp(cur_par, "ignorewaittime")== 0)
		rules_gotten[6] = true;
		
		//We dont check for full string here because it contains int values at the end
		else if(cur_par[0] == 's' && cur_par[7] == 'd' && isdigit(cur_par[8])){
			rules_gotten[7] = true;
			char * temp = (char *)malloc(100);
			
			//Get wait time	
			int cur_index = 0;
			while(isdigit(cur_par[cur_index + 8])){
				temp[cur_index] = cur_par[cur_index + 8];
				cur_index ++;
			}
			
			rule7_wait_time = atoi(temp);
			free(temp);
		}
		
		cur_par = strtok(NULL, delim);
	}
	
	if(rules_gotten[5]){
		for(int i = 0; i < GetTerminalSize("rows"); i ++)
		printf("\n");
	}
	
	char * CUR_LINE = (char *)malloc(1000);
	
	FILE * fformattxt = fopen(FileNametemp, "r");
	
	//We really dont want the information above to show up
	if(strcmp(FileName, "UsersBook.dir")== 0){
		fgets(CUR_LINE, 1000, fformattxt);
		fgets(CUR_LINE, 1000, fformattxt);	
	}
 
	memset(CUR_LINE, '\0', sizeof(CUR_LINE));
	while(fgets(CUR_LINE, 1000, fformattxt)!= NULL){
		
		if(rules_gotten[2]){
			white;
			printf("L%d\t", cur_line);
		}
		
		if(rules_gotten[3] || rules_gotten[5])
		printf("%*c", ((GetTerminalSize("columns") - strlen(CUR_LINE)) / 2) + strlen(CUR_LINE), temp_char);
		
		if(rules_gotten[4])
		printf("%*c", (GetTerminalSize("columns") - strlen(CUR_LINE)) + strlen(CUR_LINE), temp_char);
		
		//Formating go here
		for(int i = 0; i < strlen(CUR_LINE); i ++){
			
			if(CUR_LINE[i] == '/' && CUR_LINE[i + 2] == '/' && !rules_gotten[1]){
				
				char code = CUR_LINE[i + 1];
			
				//Remove the intruding formating code from the output
				if(!rules_gotten[0])
				i += 3;
				
				//NEEDED FORMATING DECODER
				switch(code){
					case '1':
						dark_blue;
						break;
						
					case '2':
						green;
						break;
						
					case '3':
						light_blue;
						break;
					
					case '4':
						red;
						break;
						
					case '5':
						purple;
						break;
						
					case '6':
						yellow;
						break;
						
					case '7':
						white;
						break;
						
					case '8':
						gray;
						break;
						
					case '9':
						mid_blue;
						break;
					
					case 'X':{
						
						if(!rules_gotten[0])
						i -= 3;
						
						switch(CUR_LINE[i + 4]){
							//Double switch case for no uppercase sensitivity
							case 'a':
							case 'A':
								light_green;
								break;
							
							case 'b':
							case 'B':
								light_aqua;
								break;
							
							case 'c':
							case 'C':
								light_red;
								break;
							
							case 'd':	
							case 'D':
								light_purple;
								break;
							
							case 'e':	
							case 'E':
								light_yellow;
								break;
							
							case 'f':	
							case 'F':
								bright_white;
								break;	
								
							default:
								break;
						}
						
						if(!rules_gotten[0])
						i += 5;
						break;
					}
					
					case 'T':
						printf("\t");
						break;
						
					case 'F': {
						char mode [10] = { '\0' };
						int index = 0;
						
						//Put this in normal for eazy calculations
						if(!rules_gotten[0])
						i -= 3;
						
						//Get mode
						while(CUR_LINE[i + index + 4] != ' '){
							if(CUR_LINE[i + index + 4] == ' ' || CUR_LINE[i + index + 4] == '\0')
							break;
							
							mode[index] = tolower(CUR_LINE[index + i + 4]);
							index ++;
						}
						
						//Reverse to normal
						if(!rules_gotten[0])
						i += 3;
						
						//Formula used: (GetTerminalSize("columns") - (strlen(CUR_LINE) - (3 (/F/) + 1 ( ) + 6 (center) + 1 ( ) + 1 (\0)
						
						//Format acordingly
						if(strcmp(mode, "center")== 0){
							if(rules_gotten[0])
							printf("%*c", (GetTerminalSize("columns") - (strlen(CUR_LINE) - 2)) / 2, temp_char);
							
							else {
								i += 7;
								printf("%*c", (GetTerminalSize("columns") - (strlen(CUR_LINE) - 12)) / 2, temp_char);	
							}	
							
						} else if(strcmp(mode, "right")== 0){
							if(rules_gotten[0])
							printf("%*c", GetTerminalSize("columns") - (strlen(CUR_LINE) - 2), temp_char);
							
							else {
								i += 6;
								printf("%*c", GetTerminalSize("columns") - (strlen(CUR_LINE) - 11), temp_char);	
							}
							
						} else if(strcmp(mode, "middle")== 0){
							for(int j = 0; j < (GetTerminalSize("rows") / 2); j ++)
							printf("\n");
							
							if(rules_gotten[0])
							printf("%*c", (GetTerminalSize("columns") - (strlen(CUR_LINE) - 2)) / 2, temp_char);
							
							else {
								i += 7;
								printf("%*c", (GetTerminalSize("columns") - (strlen(CUR_LINE) - 12)) / 2, temp_char);
							}
						}
						
						break;
					}
					
					case 'W': {
						char * temp = (char *)malloc(100);
						
						int cur_index = 0;
						//Get wait time	
						while(isdigit(CUR_LINE[(cur_index + 4) + i])){
							temp[cur_index] = CUR_LINE[(cur_index + 4) + i];
							cur_index ++;
						}
						
						usleep(atoi(temp));
						free(temp);
						break;
					}
					
					default:
						break;
						
				}
			}
			printf("%c", CUR_LINE[i]);
			
		}
		
		if(rules_gotten[7])
		usleep(rule7_wait_time);
		
		memset(CUR_LINE, '\0', sizeof(CUR_LINE));
		cur_line ++;
	}
	
	fclose(fformattxt);
	free(CUR_LINE);
	free(FileNametemp);
	
	return;
}

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
				Small_stop;
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
			Small_stop;
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
		Small_stop;
	}
	
	if(!there_is_dir && !appdata_done)
	return false;
	
	return true;
}

bool MakeSaveFiles(const char * what){
	if(strcmp(what, "new")== 0){
		chdir(FULL_PATH);
		
		//Make normal save file stuff
		mkdir("INVENTORY");
		mkdir("ACHIVEMENTS");
		mkdir("SETTINGS");
		mkdir("CHEST_INVENTORY");
		mkdir("QUESTS");
		mkdir("STASH");
		mkdir("STORY"); 
		mkdir("TIME"); 
		mkdir("OTHER");
	    
	    //Make new files for ltr
	    ChangeCurPath("Inventory");
	    FILE * fspecials = fopen("Specials.txt", "w");
	    
	    for(int i = 0; i < 26; i ++)
	    fprintf(fspecials, "0\n");
	    
		fclose(fspecials);
		
		FILE * fspecialstats = fopen("SpecialStats.txt", "w");
		fprintf(fspecialstats, "NONE\n");
		fprintf(fspecialstats, "NONE\n");
		fprintf(fspecialstats, "0\n");
		fclose(fspecialstats);
	    
	    ChangeCurPath("ACHIVEMENTS");
		FILE * fachi = fopen("Achivements.txt", "w");
		for(int i = 0; i < 2; i ++)
		fprintf(fachi, "NO\n");
		fclose(fachi);
		ChangeCurPath("STORY");
	    
	    for(int i = 1; i < 7; i ++){
	    	ChangeCurPath("STORY");
	    	
	    	char mk_key_dir [10] = "Key";
	    	mk_key_dir[3] = i + '0';
		    mkdir(mk_key_dir);
		    
		    ChangeCurPath("STORY");
		    CatCurPath(mk_key_dir);
		  
		    switch(i){
		    	case 1: {
		    		FILE * ftreedone = fopen("Invstreesdone.txt", "w");
		    		for(int i = 0; i < 3; i ++)
		    		fprintf(ftreedone, "0\n");
		    		fclose(ftreedone);
		    		
		    		FILE * fbirddone = fopen("Birdhousesdone.txt", "w");
		    		for(int i = 0; i < 2; i ++)
		    		fprintf(fbirddone, "0\n");
		    		fclose(fbirddone);
		    		
		    		break;
		    	}
		    	
		    	case 2: {
		    		FILE * fcatfood = fopen("Catfood.txt", "w");
		    		for(int i = 0; i < 4; i ++)
		    		fprintf(fcatfood, "-1\n");
		    		fclose(fcatfood);
		    		
		    		short int closed_locations [9], cat_pos, key_pos;
		    		
					short int what_path = rand()% 3 + 1;
				    	
				    //Depending on the path, diferent locations
				    if(what_path == 1){
				    	closed_locations[0] = 1;
				    	closed_locations[1] = 5;
				    	closed_locations[2] = 6;
				    	closed_locations[3] = 8;
				    	closed_locations[4] = 13;
				    	closed_locations[5] = 14;
				    	closed_locations[6] = 17;
				    	closed_locations[7] = 18;
				    	closed_locations[8] = 25;
				    		
				    	cat_pos = 7;
				   		key_pos = 19;
				   			
					} else if(what_path == 2){
						closed_locations[0] = 2;
				    	closed_locations[1] = 9;
				    	closed_locations[2] = 11;
				    	closed_locations[3] = 12;
				    	closed_locations[4] = 13;
				    	closed_locations[5] = 14;
				    	closed_locations[6] = 17;
				    	closed_locations[7] = 24;
				    	closed_locations[8] = 25;
				    	
				    	cat_pos = 8;
				    	key_pos = 16;
				    		
					} else {
						closed_locations[0] = 3;
				    	closed_locations[1] = 4;
				    	closed_locations[2] = 9;
				    	closed_locations[3] = 10;
				    	closed_locations[4] = 12;
				    	closed_locations[5] = 16;
				    	closed_locations[6] = 17;
				    	closed_locations[7] = 19;
				    	closed_locations[8] = 24;
				    	
				    	cat_pos = 25;
				    	key_pos = 11;
				    		
					}
				    		
				    FILE * fcatpos = fopen("CatposKeypos.txt", "w");
				    fprintf(fcatpos, "%d\n", cat_pos);
				    fprintf(fcatpos, "%d\n", key_pos);
				    fclose(fcatpos);
				    		
				    FILE * fclosedpos = fopen("Closedpos.txt", "w");
				    for(int i = 0; i < 9; i ++)
				    fprintf(fclosedpos, "%d\n", closed_locations[i]);
				    fclose(fclosedpos);
		    		
		    		break;
		    	
		    	}
		    	
		    	case 3: {
		    		FILE * fhintinfo = fopen("Cur.HintInfo.txt", "w");
					fclose(fhintinfo);
					
					FILE * fhiddenkey = fopen("hiddenkey.txt", "w");
					fclose(fhiddenkey);
					
					FILE * fEncList = fopen("ListEncryptionsMade.txt", "w");
					fclose(fEncList);
					
					FILE * fprog = fopen("ProgressMade.txt", "w");
					fclose(fprog);
					
					//Hide the hiddenkey file (contains needed information for the key3 to function)
					system("attrib +h hiddenkey.txt");
		    		
					break;
				}
		    	
		    	case 4: {
		    		//Key4 Rq.
		    		
		    		//Choosing a random maze shape for the dungeon :>
		    		int last_move = 0, all_moves[20];
		    		for(int i = 0; i < 20; i ++){
						int next_move = rand()% 4 + 1;
						
						if(next_move == 1 && last_move == 4)
						i --;
						
						else if(next_move == 2 && last_move == 3)
						i --;
						
						else if(next_move == 3 && last_move == 2)
						i --;
						
						else if(next_move == 4 && last_move == 1)
						i --;
						
						else {
							last_move = next_move;
							all_moves[i] = next_move;
							
							//Make it more linear, less annoying to traverse
							if(rand()% 2 + 1 == 1){
								all_moves[i + 1] = next_move;
								i ++;
							}
						}
					}
					
					//List movements in the file (aka the dungeon)
					FILE * fmovementlist = fopen("MovementsList.txt", "w");
					for(int i = 0; i < 20; i ++)
					fprintf(fmovementlist, "%d\n", all_moves[i]);
					fclose(fmovementlist);
							
					//List number of rooms explored in the file
					FILE * roomsexplored = fopen("RoomsExplored.txt", "w");
					fprintf(roomsexplored, "1");
					fclose(roomsexplored);
		    		
		    		//Git user stats
					FILE * fuserstats = fopen("UserStats.txt", "w");
					fprintf(fuserstats, "100\n");		//Hp
					fprintf(fuserstats, "10\n");		//Attack
					fprintf(fuserstats, "5\n");			//Defence
					fprintf(fuserstats, "0\n"); 		//Absorption
					fclose(fuserstats);
		    		
		    		break;
		    	}
		    	
		    	case 5: {
		    		
		    		break;
				}
				
		    	case 6: {
					
		    		//Key 6 Rq.
		    		FILE * fpathtaken = fopen("Pathtaken.txt", "w");
		    		fprintf(fpathtaken, "UNKNOWN");
		    		fclose(fpathtaken);
		    		
		    		break;
				}
				
		    	default:
		    		break;
			}
			
		}
	    
	    //Change back to story because keydone dosent need a dir file
	    ChangeCurPath("STORY");
	    
	    //Make annother to know what keys the user already has
	    FILE * fkeysd = fopen("Keysdone.txt", "w");
	    for(int i = 0; i < 6; i ++)
	    fprintf(fkeysd, "0\n");
	    fclose(fkeysd);
	    
	    FILE * fweather = fopen("Weather.txt", "w");
	    fprintf(fweather, "Clear");
	    fclose(fweather);
	    
	    //Other dir for location gathering & set up files for ltr
	    mkdir("Locations");
	    ChangeCurPath("STORY.Locations");
	    FILE * floc = fopen("Current.txt", "w");
	    fprintf(floc, "NOT");
	    fclose(floc);
	    
	    //other dirs to save other NEEDED stuff
	    ChangeCurPath("OTHER");
		mkdir("positions");
		mkdir("chalenges");
		mkdir("books");
		mkdir("triggers");
		mkdir("tutorials");
		mkdir("activepots");
		mkdir("merprices");
		mkdir("temp");
		
		//other dirs to save other triggers related stuff
		ChangeCurPath("OTHER.triggers");
		mkdir("other");
		mkdir("story");
		
		//Some story files need to be made b4 hand
		CatCurPath("story");
		FILE * fwizstory = fopen("WizardSpecifics.txt", "w");
		fprintf(fwizstory, "0");
		fclose(fwizstory);
		
		FILE * fkeytriggersdone = fopen("KeyTriggersDone.txt", "w");
		for(int i = 0; i < 6; i ++)
		fprintf(fkeytriggersdone, "0\n");
		
		fclose(fkeytriggersdone);
		
		//Register merchant prices here
		ChangeCurPath("OTHER.merprices");
		for(int i = 1; i < 6; i ++){
	    	char mk_mer_dir [10] = "mer";
	    	mk_mer_dir[3] = i + '0';
		    mkdir(mk_mer_dir);    
		}
		
		//other dirs to save STASH related stuff
	    ChangeCurPath("STASH");
		mkdir("Animals");
		mkdir("Potions");
		mkdir("Merchants");
		
		//file to register animal stash stuff
		ChangeCurPath("STASH.Animals");
		FILE * fastash = fopen("StableInfo.txt", "w");
		fprintf(fastash, "-1\n1\n0\n0\n0");
		fclose(fastash);
		
		//Quest stuff (other dirs)
		ChangeCurPath("QUESTS");
		mkdir("Main");
		mkdir("Other");
		mkdir("Started");
		
		//Achivements related stuff
		ChangeCurPath("ACHIVEMENTS");
		mkdir("Done");
		mkdir("Progress");
		mkdir("Extra");
		
		//Get dificulty
		while(true){
			CLR;
			white;
		    printf("Before starting, select a dificulty\n");
		    printf(">Lucid Dream [Lucid]\n");
		    printf(">False Awakening [False]\n");
		    printf(">Vivid Dream [Vivid]\n");
		    printf(">Nightmare\n");
				 
		    printf("[Use the names inside the \"[]\"]\n");
		    String_Input;
		    
		    CLR;
		    light_blue;
		    
		    if (strcmp(Input, "nightmare")== 0 || strcmp(Input, "lucid")== 0 || strcmp(Input, "false")== 0 || strcmp(Input, "vivid")== 0) { // 4
		        Input[0] = toupper(Input[0]);
				printf("%s dificulty\n", Input);
		        strcpy(dificulty, Input);
		        break;
		            
		    } else { Error; }
    		
    	}
    	
    	sleep(3);
    	white;
    	CLR;
    	
    	//Register dificulty in save file AND set up default settings
    	ChangeCurPath("SETTINGS");
    	FILE * fdif = fopen("Dificulty.txt", "w");
    	fprintf(fdif, "%s\n", dificulty);
    	fclose(fdif);
    	
    	FILE * fintros = fopen("IntroSet.txt", "w");
	    fprintf(fintros, "0\n");
	    fclose(fintros);
	    
	    FILE * fMiniGames = fopen("MiniGamesSet.txt", "w");
	    fprintf(fMiniGames, "Int\n");
	    fprintf(fMiniGames, "1\n");
	    fclose(fMiniGames);
    	
		FILE * fTutorials = fopen("TutorialSet.txt", "w");
	    fprintf(fTutorials, "1\n");
	    fprintf(fTutorials, "0\n");
	    fprintf(fTutorials, "0\n");
	    fclose(fTutorials);	
    	
    	FILE * fdisplaytip = fopen("DisplayTipSet.txt", "w");
		fprintf(fdisplaytip, "1\n");
		fclose(fdisplaytip);

		FILE * finventoryset = fopen("InventorySet.txt", "w");
		fprintf(finventoryset, "1\n");
		fprintf(finventoryset, "0\n");
		for(int i = 0; i < 6; i++)
		fprintf(finventoryset, "1\n");
		fclose(finventoryset);
		
	} else if(strcmp(what, "check")== 0){
		chdir(LOCAL_PATH);
		//Waiting on LOCALAPPDATA to be made
		//ADD READ ONLY TO ALL LOCALAPPDATA FILES SO USER CAN MODIFY THEM BY ACIDENT
		
		chdir(FULL_PATH);
		
	} else if(strcmp(what, "load")== 0){
		chdir(FULL_PATH);
		
		//load save in the vars
		ChangeCurPath("SETTINGS");
		
		//Dificulty
		FILE * fdif = fopen("Dificulty.txt", "r");
		fscanf(fdif, "%s\n", &dificulty);
		fclose(fdif);
		
		if(dificulty[0] == '\0'){
			red;
			printf("NO DIFICULTY, SAVE FILE CORRUPTED");
			white;
			Small_stop;
			FILE * fdif = fopen("Dificulty.txt", "w");
			fprintf(fdif, "Lucid");
			fclose(fdif);
			exit(1);
		}
		
		//Display tip
		FILE * ftip = fopen("DisplayTipSet.txt", "r");
		fscanf(ftip, "%d\n", &display_tip);
		fclose(ftip);
		
		//Skip intro?
		FILE * fintro = fopen("IntroSet.txt", "r");
		fscanf(fintro, "%d\n", &skip_intro);
		fclose(fintro);
		
		short int * a = (short int *)malloc(1);
		
		//Inventory
		FILE * finv = fopen("InventorySet.txt", "r");
		fscanf(finv, "%d\n", a);
		div_inv_sect = *a;
		fscanf(finv, "%d\n", a);
		limit_inv = *a;
		for(int i = 0; i < 6; i ++){
			fscanf(finv, "%d\n", a);
			arr_limit_inv[i] = *a;
		}
		fclose(finv);
		
		//Mini-Games
		FILE * fgames = fopen("MiniGamesSet.txt", "r");
		fscanf(fgames, "%s\n", &game_set);
		fscanf(fgames, "%d\n", &show_user_turn);
		fclose(fgames);
		
		//Tutorial
		FILE * ftut = fopen("TutorialSet.txt", "r");
		fscanf(ftut, "%d\n", a);
		display_all_tut_once = *a;
		fscanf(ftut, "%d\n", a);
		force_tut_display = *a;
		fscanf(ftut, "%d\n", a);
		skip_tut_display = *a;
		fclose(ftut);
		
		free(a);
		
	} else if(strcmp(what, "saveall")== 0){
		
		//Clear all temporary files
		ChangeCurPath("OTHER");
		system("rmdir temp /s /q");
		mkdir("temp");
		
		if(isdigit(FULL_PATH[strlen(FULL_PATH) - 1])){
			while(FULL_PATH[strlen(FULL_PATH) - 1] != 'N')
			FULL_PATH[strlen(FULL_PATH) - 1] = '\0';
		}
		
		chdir(FULL_PATH);
		chdir(".out");
		
		//Converts time spent to like day:hour:minute:second
		int seconds = 0, minutes = 0, hours = 0, days = 0;
		int bckp_sec = 0, bckp_min = 0, bckp_hour = 0, bckp_day = 0;
		
		char * time_spent = (char *)malloc(30);
		char * temp_convert = (char *)malloc(30);
		char delim [2] = ":";
		
		FILE * fmore = fopen(".more.txt", "r");
		fscanf(fmore, "%s", time_spent);
		fclose(fmore);
		
		//Getting paremeters needed
		char * rest = strtok(time_spent, delim);
		days = atoi(rest);
		rest = strtok(NULL, delim);
		hours = atoi(rest);
		rest = strtok(NULL, delim);
		minutes = atoi(rest);
		rest = strtok(NULL, delim);
		seconds = atoi(rest);
		
		memset(time_spent, '\0', sizeof(time_spent));
		
		//Smol error here btw
		bckp_sec = GetTimeSpent();
		bckp_min += bckp_sec / 60;
		bckp_sec -= bckp_min * 60;
		bckp_hour += bckp_min / 60;
		bckp_min -= bckp_hour * 60;
		bckp_day += bckp_hour / 24;
		bckp_hour -= bckp_day * 24;
		
		seconds += bckp_sec;
		minutes += bckp_min;
		hours += bckp_min;
		days += bckp_day;
		
		itoa(days, temp_convert, 10);
		strcat(time_spent, temp_convert);	
		strcat(time_spent, ":");
		itoa(hours, temp_convert, 10);	
		strcat(time_spent, temp_convert);
		strcat(time_spent, ":");
		itoa(minutes, temp_convert, 10);	
		strcat(time_spent, temp_convert);
		strcat(time_spent, ":");
		itoa(seconds, temp_convert, 10);	
		strcat(time_spent, temp_convert);
		
		rewind(fmore);
		fopen(".more.txt", "w");
		fprintf(fmore, "%s", time_spent);
		fclose(fmore);
		
		free(time_spent);
		free(temp_convert);
		
	} else {
		printf("INVALID ARGUMENT ON MakeSaveFiles");
	}
	
	//Check for achivement done (FILE) on FULL_PATH
	chdir(FULL_PATH);
	chdir("..");
	if(access("ACHIVEMENTDONE.txt", F_OK)== 0){
		remove("ACHIVEMENTDONE.txt");
		chdir(FULL_PATH);
		chdir("ACHIVEMENTS\\Done");
		FILE * fnewachiv = fopen("StartingScreen.txt", "w");
		fclose(fnewachiv);
	}

    return true;    //default exit (everything oki)
}

void ChangeFileLine(const char * file_name, const char * line, int line_to_modify){
	
	FILE * freadlines = fopen(file_name, "r");
	FILE * ftemp = fopen("__temp.txt", "w");
	
	int cur_line = 0;
	char read_line [5000] = { '\0' };
	
	while(fgets(read_line, 5000, freadlines)!= NULL){
		if(line_to_modify == cur_line)
		fprintf(ftemp, "%s\n", line);
		
		else
		fprintf(ftemp, "%s", read_line);	
			
		cur_line ++;
		memset(read_line, '\0', sizeof(read_line));
	}
	
	fclose(freadlines);
	fclose(ftemp);
	
	remove(file_name);
	rename("__temp.txt", file_name);
	
	return;
}

//Copy cat of the function above but modified to navigate the "OTHER" dir instead
void ChangeCurPath(const char * please_change_to_this_line){
	char *final_path = (char *)malloc(MAX_PATH);
	memset(final_path, '\0', MAX_PATH);
	
	char * copy_of_arg = (char *)malloc(strlen(please_change_to_this_line) * sizeof(char) + 5);
	memset(copy_of_arg, '\0', sizeof(copy_of_arg));
	strcpy(copy_of_arg, please_change_to_this_line);
	
	strcpy(final_path, FULL_PATH);
	strcat(final_path, "\\");
	
	//Seperate paremeters
	char delim [2] = ".";
	char * current_cat_line;
	current_cat_line = strtok(copy_of_arg, delim);
	if(current_cat_line == NULL){
		chdir(final_path);
		return;
	}
	
	strcat(final_path, current_cat_line);
	strcat(final_path, "\\");
	
	//Continue untill end
	while(current_cat_line != NULL){
		current_cat_line = strtok(NULL, delim);	
		if(current_cat_line == NULL)
		break;
		
		strcat(final_path, current_cat_line);
		strcat(final_path, "\\");
	}
	
	chdir(final_path);
	free(final_path);
	free(copy_of_arg);
	
	return;
}

//Same has function above but its made to get app resources (access localappdata)
void GetAppResources(const char * please_change_to_this_line){
	char *final_path = (char *)malloc(MAX_PATH);
	memset(final_path, '\0', MAX_PATH);
	
	char * copy_of_arg = (char *)malloc(strlen(please_change_to_this_line) * sizeof(char) + 5);
	memset(copy_of_arg, '\0', sizeof(copy_of_arg));
	strcpy(copy_of_arg, please_change_to_this_line);
	
	strcpy(final_path, LOCAL_PATH);
	strcat(final_path, "\\Resources\\");
	
	//Seperate paremeters
	char delim [2] = ".";
	char * current_cat_line;
	current_cat_line = strtok(copy_of_arg, delim);
	
	if(strcmp(current_cat_line, "switchbacktomain")== 0){
		strcpy(final_path, LOCAL_PATH);
		strcat(final_path, "\\");
		current_cat_line = strtok(NULL, delim);	
		
	} else if(current_cat_line == NULL){
		chdir(final_path);
		return;
	}
	
	strcat(final_path, current_cat_line);
	strcat(final_path, "\\");
	
	//Continue untill end
	while(current_cat_line != NULL){
		current_cat_line = strtok(NULL, delim);	
		if(current_cat_line == NULL)
		break;
		
		strcat(final_path, current_cat_line);
		strcat(final_path, "\\");
	}
	
	chdir(final_path);
	free(final_path);
	free(copy_of_arg);
	
	return;
}

//Its not pretty but it works
void CatCurPath(const char * cat_this_line){
	char * copy_of_arg = (char *)malloc(strlen(cat_this_line) * sizeof(char));
	memset(copy_of_arg, '\0', sizeof(copy_of_arg));
	strcpy(copy_of_arg, cat_this_line);
	
	//Seperate paremeters
	char delim [2] = ".";
	char * current_cat_line;
	current_cat_line = strtok(copy_of_arg, delim);
	
	//Add to current path
	chdir(current_cat_line);
	
	//Continue untill end
	while(current_cat_line != NULL){
		current_cat_line = strtok(NULL, delim);	
		
		if(current_cat_line == NULL)
		break;
		
		chdir(current_cat_line);
	}
	
	free(copy_of_arg);
	return;
}

//Check if dir exists [Not made by me, thanks for whoever did it though]
bool ExistDiret(const char *path){
	struct stat stats;

    stat(path, &stats);
    
    if (S_ISDIR(stats.st_mode)){
    return true;
	}
	
    return false;
}

//Used to get cur Terminal Size information (not mine, found here: https://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows/12642749#12642749)
int GetTerminalSize(const char * what){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
  	
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	
	if(strcmp(what, "columns")== 0)
	return columns;
	
	else
	return rows;
}

//I forgot where i stole this from but its not mine (used to modify window pos and size)
HWND WINAPI GetConsoleWindowNT(void){
    typedef HWND WINAPI(*GetConsoleWindowT)(void);
    GetConsoleWindowT GetConsoleWindow;
    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib
    ,TEXT("GetConsoleWindow"));
    if(GetConsoleWindow == NULL){
        return NULL;
    }
    return GetConsoleWindow();
}

//Center texts thats passed through the parameter
void CenterText(const char *line){
	printf("%*s\n", ((GetTerminalSize("columns") - strlen(line)) / 2) + strlen(line), line);
	return;
}

//Same has function above but it puts it in the right side of the screen
void RightText(const char *line){
	printf("%*s\n", (GetTerminalSize("columns") - strlen(line)) + strlen(line), line);
	return;
}

//Same has function above but randomize X and Y value (and properly format them)
void RandText(const char *line){
	CLR;
	//Color
	short int rand_color = rand()% 3 + 1;
	if(rand_color == 1){
		white;
	} else if(rand_color == 2){
		red;
	} else {
		gray;
	}
	
	//Randomize X
	int rand_width = rand()% GetTerminalSize("columns") + 1;
	//Format X
    rand_width = (rand_width - strlen(line)) + strlen(line);
    
    //Randomize Y (no need for formating)
    int rand_rows = rand()% GetTerminalSize("rows") + 1;
    
    //Randomize number of lines
    const int numb_lines = rand()% 5 + 1;
    
    //Modify Y
    for(int i = 0; i < rand_rows; i ++)
    printf("\n");
    
    //Print result
    for(int i = 0; i < numb_lines; i ++)
	printf("%*s\n", rand_width, line);
	
	white;
	return;
}

//Same has above but X and Y arent random but are actually divided by 2 (and formated accordingly)
void MidScreenText(const char *line){
	for(int i = 0; i < (GetTerminalSize("rows") / 2); i ++)
    printf("\n");
    
    printf("%*s\n", ((GetTerminalSize("columns") - strlen(line)) / 2) + strlen(line), line);
    return;
}

//Fuction to format text but VERY extended (made for specific cases)
void FormatTextEXT(const char * mode, const char * line, bool new_line, int skip_starting_displacement, const char * wantedcolors, bool has_var_port, int only_do_THIS_number_of_lines, int repeat_THIS_many_times){
	
	if(repeat_THIS_many_times <= 0)
	repeat_THIS_many_times = 1;
	
	long int cur_char = 0, total_strlen = 0;
	int total_file_lines = 0;
	total_strlen = strlen(line);
	
	//Get var port from the temp file
	if(has_var_port){
		char temp [1000] = { '\0' };
		long int temp_delim = 0;
		
		ChangeCurPath("OTHER.temp");
		if(access("FormatingVarTemp.txt", F_OK)== 0){
			FILE * fgetvarports = fopen("FormatingVarTemp.txt", "r");
		
			while(fscanf(fgetvarports, "%d\n", &temp_delim)!= EOF){
				fgets(temp, 1000, fgetvarports);
				temp[strlen(temp) - 1] = '\0';
				total_strlen += strlen(temp);
			}
		
			fclose(fgetvarports);
		} else
		return;
	}
	
	char final_formated_str [total_strlen] = { '\0' };
	strcpy(final_formated_str, line);
	
	if(has_var_port){
		char temp [1000] = { '\0' };
		long int what_delim = 0, temp_INT = 0;
		/*
		Inside FormatingVarTemp.txt:
		
		[Starting Delim]
		[What text to add]
		[and so on...]
		
		Note: Need to predict the positions when trying to add other vars lmfao
		*/
		
		FILE * fgetvarports = fopen("FormatingVarTemp.txt", "r");
		while(fscanf(fgetvarports, "%d\n", &what_delim)!= EOF){
			
			fgets(temp, 1000, fgetvarports);
			temp[strlen(temp) - 1] = '\0';
			
			//Get variables we need to do  m a t h  with
			int original_strlen = strlen(final_formated_str), temp_strlen = strlen(temp);
			int total_strlen = temp_strlen;
			total_strlen += original_strlen;
			
			//Get the rest
			int rest_wanted = abs((temp_strlen + what_delim) - total_strlen);
			char str_to_strcat [rest_wanted + 1] = { '\0' };
			
			//Get the rest we are going to strcat ltr
			for(int i = 0; i < rest_wanted; i ++){
				str_to_strcat[i] = final_formated_str[what_delim + i];
				final_formated_str[what_delim + i] = '\0';	
			}
			
			//Put the new string in
			for(int i = 0; i < temp_strlen; i ++)
			final_formated_str[what_delim + i] = temp[i];
			
			//Cat the old string
			strcat(final_formated_str, str_to_strcat);
			
		}
		
		fclose(fgetvarports);
		remove("FormatingVarTemp.txt");
	}
	
	char temp_chr = '\0';
	
	//Repeat it MANY times
	for(int i = 0; i < repeat_THIS_many_times; i ++){
		//This is to format Y
		if(only_do_THIS_number_of_lines != 0){
			for(int i = 0; i < only_do_THIS_number_of_lines; i ++)
	    		printf("\n");
		}
		
		int add_to_strlen = 0;
		if(total_strlen % 2 != 0)
		add_to_strlen -= 2;
		
		//This is format X  
		if(strcmp(mode, "center")== 0)
		printf("%*c", ((GetTerminalSize("columns") - (total_strlen + add_to_strlen)) / 2) - skip_starting_displacement, temp_chr);	
		//x = ((z - (y + w)) / 2) - u 	(z is constant)			
	
		else if(strcmp(mode, "right")== 0)
		printf("%*c", (GetTerminalSize("columns") - total_strlen) - skip_starting_displacement + 1, temp_chr);
		//+ 1 cause it bugs
		
		else if(strcmp(mode, "rand")== 0){
			
			int rand_width = rand()% GetTerminalSize("columns") + 1;
		    rand_width = (rand_width - total_strlen) + total_strlen - skip_starting_displacement;
		    
		    int rand_rows = rand()% GetTerminalSize("rows") + 1;
			
			if(only_do_THIS_number_of_lines == 0){
				for(int i = 0; i < rand_rows; i ++)
		   		printf("\n");
	   		}
			
			printf("%*c", rand_width, temp_chr);	
		}
		
		else if(strcmp(mode, "middle")== 0){
			if(only_do_THIS_number_of_lines == 0){
				for(int i = 0; i < (GetTerminalSize("rows") / 2); i ++)
	    		printf("\n");	
			}
			
			printf("%*c", ((GetTerminalSize("columns") - (total_strlen + add_to_strlen)) / 2) - skip_starting_displacement, temp_chr);	
		}
		
		else if(strcmp(mode, "none")== 0)
		printf("%c", temp_chr);
		
		else {
			red;
			printf("Wrong argument on FormatTextEXT function!!! (bozo)\n");
			white;
			return;
		}
		
		char wat_color = '\0';
		int displacement_starter = 0, current_color_displacement = 1, cur_index = 0, color_strlen = strlen(wantedcolors);
		
		for(int i = 0; i < total_strlen; i ++){
			
			//Note: Using 0 has starting displacement treats it has 1 starting displacement
			if(wantedcolors[0] != '.' && i >= displacement_starter && cur_index <= color_strlen){
				//[Color].[Displacement]
				
				displacement_starter = 0;
				wat_color = wantedcolors[cur_index];
				cur_index += 2;
				
				//This loop is to get the displacement
				while(true){
					if(wantedcolors[cur_index] != '.' && cur_index <= color_strlen){
						displacement_starter *= 10;
						displacement_starter += (int)wantedcolors[cur_index] - 48;
						cur_index ++;
						
					} else
					break;	
				}
				
				cur_index ++;
				
				//Change to THIS color
				ChangeToThisColor(0, wat_color);
			}
			
			printf("%c", final_formated_str[i]);
		}
		
		if(new_line)
		printf("\n");	
	}
	
	return;
}

//I dont wanna copy this GODDAM switch statement everytime i make a new function that needs all colors
void ChangeToThisColor(int INT_color, char CHAR_color){
	
	if(INT_color != 0){
		switch(INT_color){
			case 1:
				dark_blue;
				break;
				
			case 2:
				green;
				break;
				
			case 3:
				light_blue;
				break;
			
			case 4:
				red;
				break;
				
			case 5:
				purple;
				break;
				
			case 6:
				yellow;
				break;
				
			case 7:
				white;
				break;
				
			case 8:
				gray;
				break;
				
			case 9:
				mid_blue;
				break;
			
			case 10:
				light_green;
				break;
			
			case 11:
				light_aqua;
				break;
				
			case 12:
				light_red;
				break;
				
			case 13:
				light_purple;
				break;
				
			case 14:
				light_yellow;
				break;
				
			case 15:
				bright_white;
				break;	
				
			default:
				red;
				printf("Erm, i dont know this color (ChangeToThisColor function error)\n");
				white;
				break;
		}
	} else {
		if(isalpha(CHAR_color))
		CHAR_color = toupper(CHAR_color);
		
		switch(CHAR_color){
			case '1':
				dark_blue;
				break;
				
			case '2':
				green;
				break;
				
			case '3':
				light_blue;
				break;
			
			case '4':
				red;
				break;
				
			case '5':
				purple;
				break;
				
			case '6':
				yellow;
				break;
				
			case '7':
				white;
				break;
				
			case '8':
				gray;
				break;
				
			case '9':
				mid_blue;
				break;
			
			case 'A':
				light_green;
				break;
			
			case 'B':
				light_aqua;
				break;
				
			case 'C':
				light_red;
				break;
				
			case 'D':
				light_purple;
				break;
				
			case 'E':
				light_yellow;
				break;
				
			case 'F':
				bright_white;
				break;	
				
			default:
				red;
				printf("Erm, i dont know this color (ChangeToThisColor function error)\n");
				white;
				break;
		}
	}
	
	return;
}

int GetTimeSpent(void){
	time_needed = clock() - time_needed;
	return time_needed / CLOCKS_PER_SEC;
}

//Tank for plawing ma gayme
int EndOfBeta(){
	
	white;
	sleep(2);
	CLR;
	Credits();
	CLR;
	yellow;
	printf("Press anything to leave with code \"thanks for playing\" (has ascii code)\n");
	getch();
	white;
				// T /  H /  A 	/  N  / K   /  S / [SPACE] /  F  /  O  /  R  / [SPACE] /  P  /  L  /  A /  Y  /  I  /  N  /  G [Total is 1 796 btw]
	short int leave =  116 + 104 + 97 + 110 + 107 + 115 +   32   + 102 + 111 + 114 +    32   + 112 + 108 + 97 + 121 + 105 + 110 + 103;
	
	CLR;
	yellow;
	CenterText("WAKE UP! ITS A DREAM AFTER ALL!");
	white;
	getch();
	
    exit(leave);
}
