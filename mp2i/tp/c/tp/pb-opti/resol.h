#ifndef __RESOL_H__
#define __RESOL_H__
#include "../../libraries.h"

int** mat_moins_1(int, int);
void det_mat(int**, int);
int remplir(int l, int c, int M[l][c], int** memo, int i, int j);
int** top_down(int l, int c, int M[l][c]);

#endif
