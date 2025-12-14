#ifndef __DM7_H__
#define __DM7_H__

#include "../../libraries.h"
#include "../../algos_importants/implementations/liste/liste.h"

void divise(liste, liste*, liste*);
liste fusion(liste, liste);
liste tri_fusion(liste);
void partition(liste, int, liste*, liste*);
liste tri_rapide(liste);

#endif
