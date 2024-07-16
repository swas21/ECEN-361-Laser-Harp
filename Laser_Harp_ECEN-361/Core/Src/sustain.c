/*
 *

   _____                  __        _
  / ___/__  ___________ _/ /_____ _(_)___   _____
  \__ \/ / / / ___/ __ `/ __/ __ `/ / __ \ / ___/
 ___/ / /_/ (__  ) /_/ / /_/ /_/ / / / / // /__
/____/\__,_/____/\__,_/\__/\__,_/_/_/ /_(_)___/


 *
 *  Created on: Jul 16, 2024
 *      Author: Marshall Potts
 */

#include "sustain.h"
#include "tranposition.h"

// sets value for each note index of the array active[]
#define NOTE_C 		0
#define NOTE_Cs 	1
#define NOTE_D 		2
#define NOTE_Ds 	3
#define NOTE_E 		4
#define NOTE_F 		5
#define NOTE_Fs 	6
#define NOTE_G 		7
#define NOTE_Gs 	8
#define NOTE_A 		9
#define NOTE_As		10
#define NOTE_B 		11


//global decay value variables for each note. Also used in transposition.c for output wave
float decay_value_C = 1;
float decay_value_Cs = 1;
float decay_value_D = 1;
float decay_value_Ds = 1;
float decay_value_E = 1;
float decay_value_F = 1;
float decay_value_Fs = 1;
float decay_value_G = 1;
float decay_value_Gs = 1;
float decay_value_A = 1;
float decay_value_As = 1;
float decay_value_B = 1;

// global index for each note in the decay tables
int decay_index_C = 0;
int decay_index_Cs = 0;
int decay_index_D = 0;
int decay_index_Ds = 0;
int decay_index_E = 0;
int decay_index_F = 0;
int decay_index_Fs = 0;
int decay_index_G = 0;
int decay_index_Gs = 0;
int decay_index_A = 0;
int decay_index_As = 0;
int decay_index_B = 0;

void update_decay_values()
{
	if(sustain_flag == 1)
	{
		// set the value of decay from 1-0 defaults to 1 when note is inactive
		decay_value_C = active[NOTE_C] ? decay_table[decay_index_C]:1;
		decay_index_C++;

		decay_value_Cs = active[NOTE_Cs] ? decay_table[decay_index_Cs]:1;
		decay_index_Cs++;

		decay_value_D = active[NOTE_D] ? decay_table[decay_index_D]:1;
		decay_index_D++;

		decay_value_Ds = active[NOTE_Ds] ? decay_table[decay_index_Ds]:1;
		decay_index_Ds++;

		decay_value_E = active[NOTE_E] ? decay_table[decay_index_E]:1;
		decay_index_E++;

		decay_value_F = active[NOTE_F] ? decay_table[decay_index_F]:1;
		decay_index_F++;

		decay_value_Fs = active[NOTE_Fs] ? decay_table[decay_index_Fs]:1;
		decay_index_Fs++;

		decay_value_G = active[NOTE_G] ? decay_table[decay_index_G]:1;
		decay_index_G++;

		decay_value_Gs = active[NOTE_Gs] ? decay_table[decay_index_Gs]:1;
		decay_index_Gs++;

		decay_value_A = active[NOTE_A] ? decay_table[decay_index_A]:1;
		decay_index_A++;

		decay_value_As = active[NOTE_As] ? decay_table[decay_index_As]:1;
		decay_index_As++;

		decay_value_B = active[NOTE_B] ? decay_table[decay_index_B]:1;
		decay_index_B++;

	}

	else
	{
		// return all values to 1 when sustain is off
		decay_value_C = 1;
		decay_value_Cs = 1;
		decay_value_D = 1;
		decay_value_Ds = 1;
		decay_value_E = 1;
		decay_value_F = 1;
		decay_value_Fs = 1;
		decay_value_G = 1;
		decay_value_Gs = 1;
		decay_value_A = 1;
		decay_value_As = 1;
		decay_value_B = 1;
	}


}
