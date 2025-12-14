#include "tri.h" 

//explicit enough
int* fst_half(int* arr, int len){
  int* res = malloc((len/2)*sizeof(int));
  for (int i = 0; i < len/2; i++){
    res[i] = arr[i];
  }
  return res;
}

int* snd_half(int* arr, int len){
  int* res = malloc((len - (len/2))*sizeof(int));
  int len_res = len - (len/2);
  for (int i = 0; i < len_res; i++){
    res[i] = arr[i + len_res];
  }
  return res;
}

int* merge(int arr1[], int arr2[], int len_arr1, int len_arr2){
  // explicit enough
  int* arr_res = malloc((len_arr2+len_arr1)*sizeof(int));
  int pt_res = 0;
  
  // pointer for the first array
  int pt1 = 0;

  // pointer for the second
  int pt2 = 0;

  // the merge
  while (pt1 < len_arr1 && pt2 < len_arr2){
    printf("%d - %d \n", arr1[pt1], arr2[pt2]);
    if (arr1[pt1] <= arr2[pt2]){
      arr_res[pt_res] = arr1[pt1];
      pt1++;
    }
    else{
      arr_res[pt_res] = arr2[pt2];
      pt2++;
    }
    pt_res++;
  }

  // both arrays are generally not the same size
  // in said case we have not fully explored both arrays
  while (pt1 < len_arr1){
    arr_res[pt_res] = arr1[pt1];
    pt1++;
    pt_res++;
  }
  while (pt2 < len_arr2){
    arr_res[pt_res] = arr2[pt2];
    pt2++;
    pt_res++;
  }

  return arr_res;
}

int* merge_sort(int array[], int array_len){
  if (array_len == 0){
    return NULL;
  }
  else if (array_len == 1){
    // we need to copy the array else we get a problem with the free
    int* res = malloc(sizeof(int));
    res[0] = array[0];
    return res; 
  }
  else{
    // we cut the array in halves
    int* first_half = fst_half(array, array_len);
    int* second_half = snd_half(array, array_len);
    
    // we sort both sizes
    int* left_arr = merge_sort(first_half, array_len/2);
    int* right_arr = merge_sort(second_half, array_len - (array_len/2));
    
    // and merge
    int *res = merge(left_arr, right_arr, array_len/2, array_len - (array_len/2));

    free(first_half);
    free(second_half);
    free(right_arr);
    free(left_arr);

    return res;
  }
}

int main(){
  int test[7] = {5, 6, 2, 7, 9, 10, 1};
  int const len_test = 7;
  int* sorted = merge_sort(test, len_test);
  for (int i = 0; i < len_test; i++){
    printf("%d \n", sorted[i]);
  }
  free(sorted);
}
