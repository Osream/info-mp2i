#ifndef MIN_SPANNING_TREE
#define MIN_SPANNING_TREE

#include "city_graph.h"
#include "union-find.h"
#include "edge-sorting.h"
#include "min-heap.h"

// -------------------- MSP computation -------------------- //
edge_t *kruskal(city_node_t *node_array, unsigned node_count);
edge_t *prim(city_node_t *node_array, unsigned node_count);


#endif /* MIN_SPANNING_TREE */
