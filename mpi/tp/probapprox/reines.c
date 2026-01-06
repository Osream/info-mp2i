#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


int abs(int n){
    if (n < 0){
        return -n;
    }
    return n;
}


bool peut_manger(int i, int j, int k, int m){
    return j == m || abs(i-k) == abs(j-m) || i+k == m+j;
}


bool check (int n, int sol[], int k){
    for (int i = 0; i < k; i++){
        if (peut_manger(i, sol[i], k, sol[k])){
            return false;
        }
    }
    return true;
}

void solve_aux (int n, int sol[], bool check[], int k, int i){
    if (i < k){
        for(int j = 0; j < n ; j++){
            check[j] = !(peut_manger(i, sol[i], k, j)) && check[j];
        }
        solve_aux(n, sol, check, k, i+1);
    }
}


bool solve (int n, int sol[], int k){
    bool* check_arr = malloc(n * sizeof(bool));
    for (int i = 0; i < n; i++){
        check_arr[i] = true;
    }
    solve_aux(n, sol, check_arr, k, 0);

    for (int i = 0; i < n; i++){
        if (check_arr[i]){
            free(check_arr);
            sol[k] = i;
            return true;
        }
    }
    free(check_arr);
    return false;
}
