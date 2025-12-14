#ifndef UNION_FIND
#define UNION_FIND

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef size_t* union_find;

union_find uf_create(size_t n);
void uf_delete(union_find u);
size_t uf_parent(union_find u, size_t x);
bool uf_is_root(union_find u, size_t x);
size_t uf_unite(union_find u, size_t x, size_t y);
size_t uf_find(union_find u, size_t x);


#endif /* UNION_FIND */
