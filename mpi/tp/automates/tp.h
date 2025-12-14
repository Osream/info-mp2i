#ifndef __TP_H__
#define __TP_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdlib.h>

#include "dicos.h"

typedef struct afnd_s* afnd;
const int a0 = (int) 'a';

void liberer(afnd);

afnd init(int, int);

void ajout_transition(afnd, int, char, int);

afnd text2afnd(char*);

void afnd2dot(afnd, char*);

bool* Delta_partie(afnd, bool*, int);

bool* Delta_etoile(afnd, bool*, char*);

bool reconnu(afnd, char* );

int partie2entier(bool*, int);

bool* entier2partie(int, int);

dico* accessible(afnd);

afnd determinise(afnd);

#endif