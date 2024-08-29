#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//funni
#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
    #define OS_NAME "W"
    #define MAX_PATH_LENGTH MAX_PATH
    #define CLEAR_COMMAND "cls"
#elif defined(__linux__)
    #include <linux/limits.h>
    #define OS_NAME "L"
    #define MAX_PATH_LENGTH PATH_MAX
    #define CLEAR_COMMAND "clear"
#elif defined(__APPLE__) && defined(__MACH__)
    #include <sys/syslimits.h>
    #define OS_NAME "A"
    #define MAX_PATH_LENGTH PATH_MAX
    #define CLEAR_COMMAND "clear"
#else
    #define OS_NAME "U"
#endif

void ShowErr(const char * err_msg);
int max_path = 0;

int main(void){
	
	char HomePath[max_path];
	getcwd(HomePath, max_path);
	
	char clear_msg [50];
	
	if (OS_NAME[0] == 'U') {
	    ShowErr("Unknown OS.");
	}
	
	char filename [5000];
	
	printf("What File do you want to hardcode?\n");
	scanf("%s", filename);
	
	char dir [max_path];
	strcpy(dir, filename);

	//Computing filename goes here
	char next_dir[max_path];
	memset(next_dir, '\0', sizeof(next_dir));
	int cur_char = -1, last_slash_pos = 0;
	char path_break = '\0';

	if(OS_NAME[0] == 'W')
		path_break = '\\';
		
	else
		path_break = '/';

	//Switch to dir if necessary
	while(true){
		int temp_int = 0;

		if(dir[cur_char] != '.'){
			cur_char ++;
			memset(next_dir, '\0', sizeof(next_dir));
		}

		while(dir[cur_char] != path_break && dir[cur_char] != '.'){
			next_dir[temp_int] = dir[cur_char];
			cur_char ++;
			temp_int ++;
		}

		if(dir[cur_char] != '.'){
			last_slash_pos = cur_char;
			if(chdir(next_dir) != 0)
				chdir(HomePath);
				break;
		}

		if(dir[cur_char] == '.'){
			last_slash_pos ++;
			int name_strlen = strlen(dir);
			temp_int = 0;

			while(last_slash_pos != name_strlen){
				next_dir[temp_int] = dir[last_slash_pos];
				last_slash_pos ++;
				temp_int ++;
			}

			break;
		}
	}

	strcpy(filename, next_dir);
	
	if(access(filename, F_OK)!= 0)
		ShowErr("File not found.");
	
	//printf("");
	//printf("");
	
	return 0;
}

void ShowErr(const char * err_msg){
	system(CLEAR_COMMAND);
	printf(err_msg);
	sleep(2);
	exit(1);
}
