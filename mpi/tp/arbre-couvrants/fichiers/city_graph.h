#ifndef CITY_GRAPH
#define CITY_GRAPH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// -------------------- City node structure -------------------- //
typedef struct city_node
{
    unsigned array_ID;
    int ID;
    char *nom;
    double lat;
    double lon;
} city_node_t;

void default_init(city_node_t *n);
void copy(city_node_t *dest, const city_node_t *src);
void delete(city_node_t *node);

#define NODE_FORMAT                                \
    "|-----------------------------------------\n" \
    "| array_ID : %d\n"                            \
    "| ID       : %d\n"                            \
    "| nom      : %s\n"                            \
    "| Latitude : %f\n"                            \
    "| Longitude: %f\n"                            \
    "|-----------------------------------------\n"

void fprint_node(FILE *f, city_node_t *node);

#define PI 3.14159265359
#define R_TERRE 6371 // km

double distance(city_node_t a, city_node_t b);

// -------------------- Edge structure -------------------- //
typedef struct edge
{
    unsigned ID_1, ID_2;
    double weight;
} edge_t;

double tree_cost(edge_t *edge_array, size_t n);


#endif /* CITY_GRAPH */
