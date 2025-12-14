#include "resol.h"
int min_3 (int a, int b, int c){
  if (a<=b && a<=c){
    return a;
  }
  else if(c<=b && c<=a){
    return b;
  }
  else{
    return c;
  }
}

void print_mat(int l, int c, int** mat){
  for(int i =0; i <l; i ++){
    for(int j = 0; j<c; j++){
      printf("%d\t", mat[i][j]);
    }
    printf("\n");
  }
}

int main(){
    int mat_ex1[7][9] = {{1, 0, 0, 0, 0, 0, 0, 1, 0}, 
    {1, 0, 1, 1, 1, 1, 1, 1, 0}, 
    {1, 0, 1, 1, 1, 1, 0, 0, 0}, 
    {0, 1, 1, 1, 1, 1, 0, 1, 0}, 
    {0, 0, 1, 1, 1, 1, 0, 0, 1}, 
    {0, 0, 1, 1, 1, 0, 0, 1, 1}, 
    {0, 1, 0, 0, 0, 0, 0, 1, 1}};
  const int L_ex1 = 7;
  const int C_ex1 = 9;
        
  /*int mat_ex2[6][6] = {{1, 0, 0, 1, 1, 1}, */
  /*  {0, 1, 1, 1, 1, 0}, */
  /*  {0, 0, 1, 1, 1, 0}, */
  /*  {1, 0, 1, 1, 1, 1}, */
  /*  {1, 1, 1, 0, 0, 1}, */
  /*  {0, 1, 1, 1, 1, 1}};*/
  /*const int L_ex2 = 6;*/
  /*const int C_ex2 = 6;*/
  
  int** moins_1 = top_down(L_ex1, C_ex1, mat_ex1);
  print_mat(L_ex1, C_ex1, moins_1);
  det_mat(moins_1, L_ex1);
}


int** mat_moins_1(int l ,int c){
  int** mat = malloc(l*sizeof(int*));
  for(int i = 0; i<l; i++){
    mat[i] = malloc(c*sizeof(int));
    for(int j=0; j<c; j++){
      mat[i][j] = -1;
    }
  }
  return mat;
}

void det_mat(int** mat, int l){
  for(int i = 0; i<l; i++){
    free(mat[i]);
  }
  free(mat);
}


int remplir(int l, int c, int M[l][c], int** memo, int i, int j){
  if (M[i][j] == 0){
    memo[i][j] = 0;
    return 0;
  }
  else if(memo[i][j] != -1){
    return memo[i][j];
  }
  else if(i == 0 || j == 0){
    memo[i][j] = 1;
    return 1;
  }
  else {
    int suite_i = remplir(l, c, M, memo, i-1, j);
    int suite_j = remplir(l, c, M, memo, i, j-1);
    int suite_1 = remplir(l, c, M, memo, i-1, j-1);
    memo[i][j] = 1 + min_3(suite_i, suite_j, suite_1);
    return memo[i][j];
  }
}

int** top_down(int l, int c, int M[l][c]){
  int** mat_moins = mat_moins_1(l, c);
  for (int i = 0; i<l; i++){
    for(int j = 0; j<c; j++){
      remplir(l, c, M, mat_moins, i, j);
    }
  }
  return mat_moins;
}
