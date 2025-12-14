#include "../union-find.h"
#include "assert.h"
#include <stddef.h>


union_find uf_create(size_t n)
{
    union_find uf = malloc(n* sizeof(size_t));
    assert(uf != NULL);

    for (int i = 0; i < n; i++){
        uf[i] = i;
    }

    return uf;
}

void uf_delete(union_find u)
{
    if (u != NULL){
        free(u);
    }
}

size_t uf_parent(union_find u, size_t x)
{
    assert(u != NULL);
    if (u[x] == x){
       return x; 
    }
    else{
        return u[x];
    }
}

bool uf_is_root(union_find u, size_t x)
{
    assert(u!= NULL);
    return uf_parent(u, x) == x;
}

size_t find_aux(union_find u, size_t x){
    if(uf_is_root(u, x)){
        return x;
    }
    else{
        return find_aux(u, uf_parent(u, x));
    }
}

size_t uf_find(union_find u, size_t x)
{
    assert(u != NULL);
    size_t par_x = find_aux(u, x);
    u[x] = par_x;
    return par_x;
}

size_t uf_unite(union_find u, size_t x, size_t y)
{
    assert(u != NULL);
    size_t par_x = find_aux(u, x);
    size_t par_y = find_aux(u, y);

    u[par_x] = par_y;
    return par_y;
}
