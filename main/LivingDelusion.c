#include "LivingDelusion.h"

//Declaring all external variable to their "starting" state, AKA the most commun states
path STARTING_PATH = { '\0' }, FULL_PATH = { '\0' }, LOCAL_PATH = { '\0' };
bool DEBUG_MODE = false;
char Input [50] = { '\0' };
clock_t time_needed = 0.0; //Long double (lul)
i64 INT_Input = 0;

char game_set [15] = { '\0' }, dificulty[50] = { '\0' };
bool skip_intro = false, show_user_turn = false, display_all_tut_once = false, skip_tut_display = false, force_tut_display = false, show_tut_cutscene = false;
bool display_tip = false, div_inv_sect = false, limit_inv = false, arr_limit_inv [6] = { false, false, false, false, false, false };

