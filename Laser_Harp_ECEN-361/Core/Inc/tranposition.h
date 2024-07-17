/*
 *
  ______                                       _ __  _               __
 /_  __/________ _____  _________  ____  _____(_) /_(_)___  ____    / /_
  / / / ___/ __ `/ __ \/ ___/ __ \/ __ \/ ___/ / __/ / __ \/ __ \  / __ \
 / / / /  / /_/ / / / (__  ) /_/ / /_/ (__  ) / /_/ / /_/ / / / / / / / /
/_/ /_/   \__,_/_/ /_/____/ .___/\____/____/_/\__/_/\____/_/ /_(_)_/ /_/
                         /_/

 *
 *  Created on: Jul 3, 2024
 *      Author: ianse
 */


//Global Variables imported from another function

extern const int* C_TABLES[];
extern const int* Cs_TABLES[];
extern const int* D_TABLES[];
extern const int* Ds_TABLES[];
extern const int* E_TABLES[];
extern const int* F_TABLES[];
extern const int* Fs_TABLES[];
extern const int* G_TABLES[];
extern const int* Gs_TABLES[];
extern const int* A_TABLES[];
extern const int* As_TABLES[];
extern const int* B_TABLES[];


extern const int C_SAMPLES[];
extern const int Cs_SAMPLES[];
extern const int D_SAMPLES[];
extern const int Ds_SAMPLES[];
extern const int E_SAMPLES[];
extern const int F_SAMPLES[];
extern const int Fs_SAMPLES[];
extern const int G_SAMPLES[];
extern const int Gs_SAMPLES[];
extern const int A_SAMPLES[];
extern const int As_SAMPLES[];
extern const int B_SAMPLES[];

extern int my_index[];
extern int active[];

//import global decay_value variables from sustain.c
extern float decay_value_C;
extern float decay_value_Cs;
extern float decay_value_D;
extern float decay_value_Ds;
extern float decay_value_E;
extern float decay_value_F;
extern float decay_value_Fs;
extern float decay_value_G;
extern float decay_value_Gs;
extern float decay_value_A;
extern float decay_value_As;
extern float decay_value_B;

void tranposition__increment_octave();
void tranposition__decrement_octave();
int tranposition__note_update();
