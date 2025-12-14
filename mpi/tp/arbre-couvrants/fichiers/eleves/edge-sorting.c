#include "../edge-sorting.h"

static void swap_edges(edge_t *e1, edge_t *e2)
{
    edge_t tmp = *e1;

    e1->ID_1 = e2->ID_1;
    e1->ID_2 = e2->ID_2;
    e1->weight = e2->weight;

    e2->ID_1 = tmp.ID_1;
    e2->ID_2 = tmp.ID_2;
    e2->weight = tmp.weight;
}

void on_place_edge_sort(edge_t* edge_arr, unsigned n)
{
    unsigned i_min = 0;
    for(unsigned i = 0; i < n; i++){
        i_min = i;
        for (unsigned j = i; j < n; j++){
            if(edge_arr[i_min].weight > edge_arr[j].weight){
                i_min = j;
            }
        }
        swap_edges(&edge_arr[i], &edge_arr[i_min]);
    }
}
