#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "union-find.h"

static void fprint_array(FILE* f, size_t* arr, size_t n)
{
    for(size_t i = 0; i < n; i++)
    {
        fprintf(f,"[%3ld] : %ld\n",i,arr[i]);
    }
}

static size_t** random_union_arr(size_t* arr, size_t n, size_t bins)
{
    size_t** output = (size_t**) malloc(bins*sizeof(size_t*));

    size_t* bin_sizes = (size_t*) malloc(bins*sizeof(size_t));
    for(size_t i = 0; i < bins; i++)
    {
        bin_sizes[i] = 0;
    }

    // Associate each index to a random bin:
    for(size_t i = 0; i < n; i++)
    {
        arr[i] = ((size_t)rand()) % bins;
        bin_sizes[arr[i]]++;
    }

    // Create the reverse map (caviat: index 0 contains the list's size)

    // Allocate it
    for(size_t i = 0; i < bins; i++)
    {
        output[i] = (size_t*)malloc((bin_sizes[i]+1)*sizeof(size_t));
        output[i][0] = 0;
    }

    // Fill it
    for(size_t i = 0; i < n; i++)
    {
        size_t bin = arr[i];
        output[bin][output[bin][0]+1] = i;
        output[bin][0]++;
    }

    free(bin_sizes);

    return output;

}

static void free_reverse_map(size_t** reverse_map, size_t bins)
{
    for(size_t i = 0; i < bins; i++)
    {
        free(reverse_map[i]);
    }
    free(reverse_map);
}

static union_find build_union_find_1(size_t n, size_t bins, size_t** reverse_map)
{
    union_find u = uf_create(n);
    for(size_t i = 0; i < bins; i++)
    {
        size_t count = reverse_map[i][0];

        // Unite elements of a bin in a regular order
        for(size_t j = 1; j < count; j++)
        {
            uf_unite(u,reverse_map[i][j],reverse_map[i][j+1]);
        }
    }

    return u;
}

static union_find build_union_find_2(size_t n, size_t bins, size_t** reverse_map)
{
    union_find u = uf_create(n);
    for(size_t i = 0; i < bins; i++)
    {
        size_t count = reverse_map[i][0];

        // Unite elements of a bin in a somewhat unusual order
        size_t left = 1;
        size_t right = count;
        while(left < right)
        {
            uf_unite(u,reverse_map[i][left],reverse_map[i][right]);
            left++;
            right--;
        }
        for(size_t j = 1; j <= count/2; j++)
        {
            uf_unite(u,reverse_map[i][j],reverse_map[i][j+1]);
        }
    }

    return u;
}

static bool check_union_find(size_t bins, size_t** reverse_map, union_find u)
{
    for(size_t i = 0; i < bins; i++)
    {
        size_t count = reverse_map[i][0];
        if (count == 0)
            continue;

        size_t tag = uf_find(u,reverse_map[i][1]);
        for(size_t j = 2; j <= count; j++)
        {
            size_t obtained = uf_find(u,reverse_map[i][j]);
            if (obtained != tag)
            {
                fprintf(stderr,"For element %ld\n    Expected tag %ld; got %ld\n",reverse_map[i][j],tag,obtained);
                return false;
            }
        }
    }

    return true;
}


int main()
{
    // Parameters
    unsigned long runs = 100;
    unsigned seed = 42;

    // Randomness initialization
    srand(seed);

    // Testing
    size_t arr_size = 10;
    size_t* test_arr = (size_t*)malloc(arr_size*sizeof(size_t));

    size_t bins_nbr = 3;
    size_t** reverse_map;
    union_find u;

    for(unsigned long i = 0; i < runs/10; i++)
    {
        reverse_map = random_union_arr(test_arr,arr_size,bins_nbr);
        u = build_union_find_1(arr_size,bins_nbr,reverse_map);
        if (!check_union_find(bins_nbr,reverse_map,u))
        {
            fprintf(stderr,"Failed at test n°%ld\nOn array:\n",i);
            fprint_array(stderr,test_arr,arr_size);
            exit(1);
        }
        free_reverse_map(reverse_map,bins_nbr);
        uf_delete(u);
    }

    for(unsigned long i = runs/10; i < 2*runs/10; i++)
    {
        reverse_map = random_union_arr(test_arr,arr_size,bins_nbr);
        u = build_union_find_2(arr_size,bins_nbr,reverse_map);
        if (!check_union_find(bins_nbr,reverse_map,u))
        {
            fprintf(stderr,"Failed at test n°%ld\nOn array:\n",i);
            fprint_array(stderr,test_arr,arr_size);
            exit(1);
        }
        free_reverse_map(reverse_map,bins_nbr);
        uf_delete(u);
    }

    free(test_arr);

    arr_size = runs;
    bins_nbr = 10;

    test_arr = (size_t*)malloc(arr_size*sizeof(size_t));

    for(unsigned long i = 2*runs/10; i < runs; i++)
    {
        reverse_map = random_union_arr(test_arr,arr_size,bins_nbr);
        u = build_union_find_2(arr_size,bins_nbr,reverse_map);
        if (!check_union_find(bins_nbr,reverse_map,u))
        {
            fprintf(stderr,"Failed at test n°%ld\nOn array:\n",i);
            fprint_array(stderr,test_arr,arr_size);
            exit(1);
        }
        free_reverse_map(reverse_map,bins_nbr);
        uf_delete(u);
    }

    free(test_arr);

    printf("Test reussi !\n");

    return 0;
}