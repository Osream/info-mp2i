#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "edge-sorting.h"

static void random_fill(edge_t* arr, unsigned n)
{
    for(unsigned i = 0; i < n; i++)
    {
        arr[i].ID_1 = i;
        arr[i].ID_2 = i;
        arr[i].weight = (double)rand();
    }
}

static bool is_sorted(edge_t* arr, unsigned n)
{
    for(unsigned i = 0; i < n-1; i++)
    {
        if (arr[i].weight > arr[i+1].weight)
            return false;
    }
    return true;
}

static void print_array(FILE* f,edge_t* arr,unsigned n)
{
    for(unsigned i = 0; i < n; i++)
    {
        fprintf(f,"(%d) -- (%d) : %f\n",arr[i].ID_1,arr[i].ID_2,arr[i].weight);
    }
}

int main()
{
    // Parameters
    unsigned long runs = 100;
    unsigned seed = 42;

    // Randomness initialization
    srand(seed);

    // Testing
    unsigned arr_size = 10;
    edge_t* arr = (edge_t*)malloc(arr_size * sizeof(edge_t));

    for(unsigned i = 0; i < runs/10; i++)
    {
        random_fill(arr,arr_size);
       
        on_place_edge_sort(arr,arr_size);
        if (!is_sorted(arr,arr_size))
        {
            fprintf(stderr,"Erreur au test n°%d\n",i);
            fprintf(stderr,"Tableau d'arètes:\n");
            print_array(stderr,arr,arr_size);
            free(arr);
            return 1;
        }
    }

    free(arr);
    arr_size = runs;
    arr = (edge_t*)malloc(arr_size * sizeof(edge_t));

    for(unsigned i = runs/10; i < runs; i++)
    {
        random_fill(arr,arr_size);
        on_place_edge_sort(arr,arr_size);
        if (!is_sorted(arr,arr_size))
        {
            fprintf(stderr,"Erreur au test n°%d\n",i);
            fprintf(stderr,"Tableau d'arètes:\n");
            print_array(stderr,arr,arr_size);
            free(arr);
            return 1;
        }
    }

    free(arr);

    printf("Test reussi !\n");
    return 0;

}
