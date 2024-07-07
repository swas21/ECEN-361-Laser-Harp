/*
 * tranposition.c
 *
 *  Created on: Jul 3, 2024
 *      Author: ianse
 */

#include "tranposition.h"
#include "sine_tables.h"

enum tranposition__octave {
	// This enum holds the information for which octave we are holding
	OCTAVE_1 = 0,
	OCTAVE_2 = 1,
	OCTAVE_3 = 2,
	OCTAVE_4 = 3,
	OCTAVE_5 = 4,
	OCTAVE_6 = 6,
	OCTAVE_7 = 7

};
// Local Function Variables Variables

enum tranposition__octave activeOctave = OCTAVE_4;

const int *current_C_TABLE;
const int *current_Cs_TABLE;
const int *current_D_TABLE;
const int *current_Ds_TABLE;
const int *current_E_TABLE;
const int *current_F_TABLE;
const int *current_Fs_TABLE;
const int *current_G_TABLE;
const int *current_Gs_TABLE;
const int *current_A_TABLE;
const int *current_As_TABLE;
const int *current_B_TABLE;

// Variables to store the current samples for each note
int current_C_SAMPLES;
int current_Cs_SAMPLES;
int current_D_SAMPLES;
int current_Ds_SAMPLES;
int current_E_SAMPLES;
int current_F_SAMPLES;
int current_Fs_SAMPLES;
int current_G_SAMPLES;
int current_Gs_SAMPLES;
int current_A_SAMPLES;
int current_As_SAMPLES;
int current_B_SAMPLES;


void update_note_tables();


void tranposition__increment_octave() {
	/*
	 * This is a simple state machine to increase the octave.
	 * After the switch case we need to update the values for
	 * the notes and indexes.
	 */
	switch (activeOctave) {
	case OCTAVE_1:
		activeOctave = OCTAVE_2;
		break;
	case OCTAVE_2:
		activeOctave = OCTAVE_3;
		break;
	case OCTAVE_3:
		activeOctave = OCTAVE_4;
		break;
	case OCTAVE_4:
		activeOctave = OCTAVE_5;
		break;
	case OCTAVE_5:
		activeOctave = OCTAVE_6;
		break;
	case OCTAVE_6:
		activeOctave = OCTAVE_7;
		break;
	default:
	case OCTAVE_7:
		activeOctave = OCTAVE_1;
		break;

	}

	update_note_tables();

}

void tranposition__decrement_octave() {
	/*
	 * This is a simple state machine to decrement the octave.
	 * After the switch case we need to update the values for
	 * the notes and indexes.
	 */

	switch (activeOctave) {
	case OCTAVE_1:
		activeOctave = OCTAVE_7;
		break;
	case OCTAVE_2:
		activeOctave = OCTAVE_1;
		break;
	case OCTAVE_3:
		activeOctave = OCTAVE_2;
		break;
	case OCTAVE_4:
		activeOctave = OCTAVE_3;
		break;
	case OCTAVE_5:
		activeOctave = OCTAVE_4;
		break;
	case OCTAVE_6:
		activeOctave = OCTAVE_5;
		break;
	default:
	case OCTAVE_7:
		activeOctave = OCTAVE_6;
		break;

	}

	update_note_tables();
}

void update_note_tables(){
	/*
	 * This function takes the current octave and uses it to update our current
	 * note and sample information.
	 * The NOTE_TABLES are found in sine_tables.h
	 *
	 */
	current_C_TABLE = C_TABLES[activeOctave];
	current_Cs_TABLE = Cs_TABLES[activeOctave];
	current_D_TABLE = D_TABLES[activeOctave];
	current_Ds_TABLE = Ds_TABLES[activeOctave];
	current_E_TABLE = E_TABLES[activeOctave];
	current_F_TABLE = F_TABLES[activeOctave];
	current_Fs_TABLE = Fs_TABLES[activeOctave];
	current_G_TABLE = G_TABLES[activeOctave];
	current_Gs_TABLE = Gs_TABLES[activeOctave];
	current_A_TABLE = A_TABLES[activeOctave];
	current_As_TABLE = As_TABLES[activeOctave];
	current_B_TABLE = B_TABLES[activeOctave];

	current_C_SAMPLES = C_SAMPLES[activeOctave];
	current_Cs_SAMPLES = Cs_SAMPLES[activeOctave];
	current_D_SAMPLES = D_SAMPLES[activeOctave];
	current_Ds_SAMPLES = Ds_SAMPLES[activeOctave];
	current_E_SAMPLES = E_SAMPLES[activeOctave];
	current_F_SAMPLES = F_SAMPLES[activeOctave];
	current_Fs_SAMPLES = Fs_SAMPLES[activeOctave];
	current_G_SAMPLES = G_SAMPLES[activeOctave];
	current_Gs_SAMPLES = Gs_SAMPLES[activeOctave];
	current_A_SAMPLES = A_SAMPLES[activeOctave];
	current_As_SAMPLES = As_SAMPLES[activeOctave];
	current_B_SAMPLES = B_SAMPLES[activeOctave];

}
int tranposition__note_update() {

	/****************************************************************
		 This first section of Code is to handle the reseting of each index.
		 Normally this would be done at the end, but since we might be switching octaves
		 we need to make sure that our indexes are restarted.
	*********************************************************************/
		if (index[NOTE_C] > current_C_SAMPLES)
			index[NOTE_C] = 0;
		if (index[NOTE_Cs] > current_Cs_SAMPLES)
			index[NOTE_Cs] = 0;
		if (index[NOTE_D] > current_D_SAMPLES)
			index[NOTE_D] = 0;
		if (index[NOTE_Ds] > current_Ds_SAMPLES)
			index[NOTE_Ds] = 0;
		if (index[NOTE_E] > current_E_SAMPLES)
			index[NOTE_E] = 0;
		if (index[NOTE_F] > current_F_SAMPLES)
			index[NOTE_F] = 0;
		if (index[NOTE_Fs] > current_Fs_SAMPLES)
			index[NOTE_Fs] = 0;
		if (index[NOTE_G] > current_G_SAMPLES)
			index[NOTE_G] = 0;
		if (index[NOTE_Gs] > current_Gs_SAMPLES)
			index[NOTE_Gs] = 0;
		if (index[NOTE_A] > current_A_SAMPLES)
			index[NOTE_A] = 0;
		if (index[NOTE_As] > current_As_SAMPLES)
			index[NOTE_As] = 0;
		if (index[NOTE_B] > current_B_SAMPLES)
			index[NOTE_B] = 0;
	/* ***************************************************************
	 * This first batch of values is to look update the value for each Note.
	 * By using a list and different indexes we can speed up the program with good spatial locality
	 * If the note is active then we update the value. Otherwise we return a zero.
	 ***************************************************************************/
	int wave_out =0;
	wave_out	+= active[NOTE_C] ? current_C_TABLE[index[NOTE_C]] : 0;
	wave_out	+= active[NOTE_Cs] ? current_Cs_TABLE[index[NOTE_Cs]] : 0;
	wave_out 	+= active[NOTE_D] ? current_D_TABLE[index[NOTE_D]] : 0;
	wave_out 	+= active[NOTE_Ds] ? current_Ds_TABLE[index[NOTE_Ds]] : 0;
	wave_out 	+= active[NOTE_E] ? current_E_TABLE[index[NOTE_E]] : 0;
	wave_out 	+= active[NOTE_F] ? current_F_TABLE[index[NOTE_F]] : 0;
	wave_out 	+= active[NOTE_Fs] ? current_Fs_TABLE[index[NOTE_Fs]] : 0;
	wave_out 	+= active[NOTE_G] ? current_G_TABLE[index[NOTE_G]] : 0;
	wave_out 	+= active[NOTE_Gs] ? current_Gs_TABLE[index[NOTE_Gs]] : 0;
	wave_out 	+= active[NOTE_A] ? current_A_TABLE[index[NOTE_A]] : 0;
	wave_out 	+= active[NOTE_As] ? current_As_TABLE[index[NOTE_As]] : 0;
	wave_out 	+= active[NOTE_B] ? current_B_TABLE[index[NOTE_B]] : 0;

	/* ***************************************************************
	 This batch of code is to just update the index if the note is active.
	 Since the active list should only ever hold a 0 or a 1, this code works. Avoid if statements
	 ***************************************************************************/
	index[NOTE_C] += active[NOTE_C];
	index[NOTE_Cs] += active[NOTE_Cs];
	index[NOTE_D] += active[NOTE_D];
	index[NOTE_Ds] += active[NOTE_Ds];
	index[NOTE_E] += active[NOTE_E];
	index[NOTE_F] += active[NOTE_F];
	index[NOTE_Fs] += active[NOTE_Fs];
	index[NOTE_G] += active[NOTE_G];
	index[NOTE_Gs] += active[NOTE_Gs];
	index[NOTE_A] += active[NOTE_A];
	index[NOTE_As] += active[NOTE_As];
	index[NOTE_B] += active[NOTE_B];



	return	wave_out;

}

