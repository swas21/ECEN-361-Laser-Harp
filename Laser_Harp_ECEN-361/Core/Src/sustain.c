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
#include "menu.h"
#include "tranposition.h"
#include "exponential_tables.h"

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
	// sustain_flag is the on/off switch. up button sets it true(on) and down button sets it false(off)
	if(sustain_flag)
	{
		// if the note should be sustained then update decay value
		if(sustain_C)
		{
			decay_value_C = decay_table[decay_index_C];
			decay_index_C++;
		}

		if(sustain_Cs)
		{
			decay_value_Cs = decay_table[decay_index_Cs];
			decay_index_Cs++;
		}

		if(sustain_D)
		{
			decay_value_D = decay_table[decay_index_D];
			decay_index_D++;
		}

		if(sustain_Ds)
		{
			decay_value_Ds = decay_table[decay_index_Ds];
			decay_index_Ds++;
		}

		if(sustain_E)
		{
			decay_value_E = decay_table[decay_index_E];
			decay_index_E++;
		}

		if(sustain_F)
		{
			decay_value_F = decay_table[decay_index_F];
			decay_index_F++;
		}

		if(sustain_Fs)
		{
			decay_value_Fs = decay_table[decay_index_Fs];
			decay_index_Fs++;
		}

		if(sustain_G)
		{
			decay_value_G = decay_table[decay_index_G];
			decay_index_G++;
		}

		if(sustain_Gs)
		{
			decay_value_Gs = decay_table[decay_index_Gs];
			decay_index_Gs++;
		}

		if(sustain_A)
		{
			decay_value_A = decay_table[decay_index_A];
			decay_index_A++;
		}

		if(sustain_As)
		{
			decay_value_As = decay_table[decay_index_As];
			decay_index_As++;
		}

		if(sustain_B)
		{
			decay_value_B = decay_table[decay_index_B];
			decay_index_B++;
		}


	}


	// if the index has reached the end of the decay table then the note should not be sustained anymore
	if(decay_index_C > 2500-1)
	{
		sustain_C = 0;
		decay_index_C = 0; //  reset index for repeat of sustain when note is played.
		decay_value_C = 1; // reset decay value afterwards
	}

	if(decay_index_Cs > 2500-1)
	{
		sustain_Cs = 0;
		decay_index_Cs = 0;
		decay_value_Cs = 1;
	}

	if(decay_index_D > 2500-1)
	{
		sustain_D = 0;
		decay_index_D = 0;
		decay_value_D = 1;
	}

	if(decay_index_Ds > 2500-1)
	{
		sustain_Ds = 0;
		decay_index_Ds = 0;
		decay_value_Ds = 1;
	}

	if(decay_index_E > 2500-1)
	{
		sustain_E = 0;
		decay_index_E = 0;
		decay_value_E = 1;
	}

	if(decay_index_F > 2500-1)
	{
		sustain_F = 0;
		decay_index_F = 0;
		decay_value_F = 1;
	}

	if(decay_index_Fs > 2500-1)
	{
		sustain_Fs = 0;
		decay_index_Fs = 0;
		decay_value_Fs = 1;
	}

	if(decay_index_G > 2500-1)
	{
		sustain_G = 0;
		decay_index_G = 0;
		decay_value_G = 1;
	}

	if(decay_index_Gs > 2500-1)
	{
		sustain_Gs = 0;
		decay_index_Gs = 0;
		decay_value_Gs = 1;
	}

	if(decay_index_A > 2500-1)
	{
		sustain_A = 0;
		decay_index_A = 0;
		decay_value_A = 1;
	}

	if(decay_index_As > 2500-1)
	{
		sustain_As = 0;
		decay_index_As = 0;
		decay_value_As = 1;
	}

	if(decay_index_B > 2500-1)
	{
		sustain_B = 0;
		decay_index_B = 0;
		decay_value_B = 1;
	}



}
