/*
 * tranposition.h
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

extern int index[];
extern int active[];

void tranposition__increment_octave();
void tranposition__decrement_octave();
int tranposition__note_update();
