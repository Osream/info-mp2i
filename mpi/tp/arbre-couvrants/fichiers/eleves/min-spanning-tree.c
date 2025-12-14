#include "../min-spanning-tree.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

edge_t* cree_edge_tableau(city_node_t *vertices, unsigned n){
    unsigned taille = n*(n-1)/2;
    
    edge_t* arr = malloc(taille*sizeof(edge_t));
    assert(arr != NULL);

    for(int i = 0; i < n; i++){
        for(int j = 0; j<i; j++){
            arr[(i-1)*i/2 + j].ID_1 = vertices[i].array_ID;
            arr[(i-1)*i/2 + j].ID_2 = vertices[j].array_ID;
            arr[(i-1)*i/2 + j].weight = distance(vertices[i], vertices[j]);
        }
    }
    return arr;
}


// -------------------- MSP computation -------------------- //
edge_t *kruskal(city_node_t *vertices, unsigned n)
{
    unsigned card_a  = n*(n-1)/2;
    edge_t* edge_arr = cree_edge_tableau(vertices, n);
    on_place_edge_sort(edge_arr, card_a);
    
    union_find uf = uf_create(n);
    
    edge_t* res = malloc((n-1) * sizeof(edge_t)); 

    int ind_res = 0;

    for (int i = 0; ind_res != (n-1) && i < card_a; i++){
        size_t par_id1 = uf_find(uf, edge_arr[i].ID_1);
        size_t par_id2 = uf_find(uf, edge_arr[i].ID_2);

        if(par_id1 != par_id2){
            uf_unite(uf, par_id1, par_id2);
            res[ind_res] = edge_arr[i];
            ind_res ++;
        }
    }

    uf_delete(uf);
    free(edge_arr);

    return res;
    
}

edge_t *prim(city_node_t *vertices, unsigned n)
{
    fprintf(stderr,"La fonction 'prim' n'est pas implementee! Exit...\n");
    exit(1);
}
