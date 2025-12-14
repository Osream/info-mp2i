#include "../min-heap.h"

#define UNUSED __attribute__((unused))

static void init_node(heap_node_t *n, size_t index)
{
    n->data = NULL;
    n->index = index;
    n->size = 0;
    n->weight = NAN;
}

// ----- Creation ----- //

min_heap mh_create(size_t n)
{
    heap_node_t* file = malloc(n*sizeof(heap_node_t));
    init_node(file, n);
    return (min_heap) {file, n};
}

// ----- Deletion ----- //

void mh_free(min_heap h)
{
    if(h.array != NULL){
        if(h.array->data != NULL){
            free(h.array->data);
        }
        free(h.array);
    }
}

// ----- Size test ----- //

bool mh_empty(min_heap h)
{
    fprintf(stderr,"La fonction 'mh_empty' n'est pas implementee! Exit...\n");
    exit(1);
}

size_t mh_size(min_heap h)
{
    fprintf(stderr,"La fonction 'mh_size' n'est pas implementee! Exit...\n");
    exit(1);
}

size_t mh_capacity(min_heap h)
{
    fprintf(stderr,"La fonction 'mh_capacity' n'est pas implementee! Exit...\n");
    exit(1);
}

// ----- Access ----- //

// No functions here yet...

// ----- Move data in the structure ----- //
//on conservera les noeuds en place et on ne fera que des échanges de contenu afin de préserver les valeurs de index et size et de ne modifier que les valeurs de weight et data

void change_content(heap_node_t* n1, heap_node_t* n2){
    void *tmp_data = n1->data;
    double tmp_weight = n1->weight;

    n1->data = n2->data;
    n1->weight = n2->weight;

    n2->data = tmp_data;
    n2->weight = tmp_weight;

}

void mh_percolate_up(min_heap h, heap_node_t *n)
{
    fprintf(stderr,"La fonction 'mh_percolate_up' n'est pas implementee! Exit...\n");
    exit(1);
}

void mh_percolate_down(min_heap h, heap_node_t *n)
{
    fprintf(stderr,"La fonction 'mh_percolate_down' n'est pas implementee! Exit...\n");
    exit(1);
}

// ----- Interaction with the structure ----- //
//on demande à ce que cette fonction renvoie -1 si la file de priorité est saturée et 1 si l'insertion s'est bien passée.
int mh_insert(min_heap h, double w, void *d)
{
    fprintf(stderr,"La fonction 'mh_insert' n'est pas implementee! Exit...\n");
    exit(1);
}

void *mh_pop(min_heap h)
{
    fprintf(stderr,"La fonction 'mh_pop' n'est pas implementee! Exit...\n");
    exit(1);
}

void mh_modify_weight(min_heap h, heap_node_t *n, double new_weight)
{
    fprintf(stderr,"La fonction 'mh_modify_weight' n'est pas implementee! Exit...\n");
    exit(1);
}

// ----- Inspection ----- //

void* mh_get_data(heap_node_t* n)
{
    return n->data;
}


