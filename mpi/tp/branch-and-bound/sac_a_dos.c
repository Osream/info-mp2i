#include <stdlib.h>

double h (int* p, int* v, int* a, int i, int P){
    double p_sum = 0;
    double v_sum = 0;
    for(int j = 1; j <= i; j++){
        if (a[j]){
            p_sum += p[j];
            v_sum += v[j];
        }
    }
    
    int P_frac = P-p_sum;
    int j = 0;
    while (j<=(i-1) && p_sum + p[j] <= P_frac){
        p_sum += p[j];
        v_sum += v[j];
        j ++;
    }
   
    return v_sum + (j != i)*(P_frac-p_sum)/(p[j])*v[j];
}

void sac_aux (int* p, int* v, int* a, int* amax, int n, int i, int P, int* Vmax){
    if (i == n){
        if(h(p, v, a, i, P) >= *Vmax){
            *Vmax = h(p, v, a, i, P);
            for(int j = 0; j < n; j++){
                amax[j] = a[j];
            }
        }
    }
    else{
        if(h(p, v, a, i, P) >= *Vmax){
            sac_aux(p, v, a, amax, n, i+1, P, Vmax);
            a[i] = 1 - a[i];
            sac_aux(p, v, a, amax, n, i+1, P, Vmax);
        }
    }
}

int* sac_a_dos_01 (int* p, int* v, int n, int P){
    int* a_max = malloc(n * sizeof(int));
    int* a = malloc(n* sizeof(int));
    int  Vmax = 0;
    for(int i = 0; i < n; i++){
        a[i] = 0;
        a_max[i] = 0;
    }
    sac_aux(p, v, a, a_max, n , 0, P, &Vmax);
    free(a);
    return a_max;
}

int main(){
    return 0;
}