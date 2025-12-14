#ifndef GEOJSON_PRODUCER
#define GEOJSON_PRODUCER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "city_graph.h"
#include "city_parser.h"

// Format ref:
// https://fr.wikipedia.org/wiki/GeoJSON

void dump_city(FILE* fp, const city_node_t* node);
void dump_edge(FILE* fp, const edge_t* edge, const city_node_t* node_array);

void dump_nodes_and_edges(FILE* fp, const city_node_t* nodes, size_t node_count,
                                    const edge_t* edges, size_t edge_count);


#endif /* GEOJSON_PRODUCER */
