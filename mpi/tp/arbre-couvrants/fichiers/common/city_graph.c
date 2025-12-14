#include "city_graph.h"

// -------------------- City node structure -------------------- //
void default_init(city_node_t *n)
{
    n->array_ID = -1;
    n->ID = -1;
    n->lat = NAN;
    n->lon = NAN;
    n->nom = NULL;
}

void copy(city_node_t *dest, const city_node_t *src)
{
    dest->array_ID = src->array_ID;
    dest->ID = src->ID;
    dest->lat = src->lat;
    dest->lon = src->lon;
    dest->nom = strdup(src->nom);
}

void delete (city_node_t *node)
{
    node->array_ID = -1;
    node->ID = -1;
    node->lat = NAN;
    node->lon = NAN;

    if (node->nom != NULL)
        free(node->nom);

    node->nom = NULL;
}

void fprint_node(FILE *f, city_node_t *node)
{
    fprintf(f, NODE_FORMAT, node->array_ID, node->ID, node->nom, node->lat, node->lon);
}

// -------------------- Distance computation -------------------- //
static double to_radian(double angle)
{
    return (PI / 180) * angle;
}

double distance(city_node_t a, city_node_t b)
{
    double phi_a = to_radian(a.lat);
    double phi_b = to_radian(b.lat);

    double lambda_a = to_radian(a.lon);
    double lambda_b = to_radian(b.lon);

    double result = R_TERRE * acos(sin(phi_a) * sin(phi_b) + cos(phi_a) * cos(phi_b) * cos(lambda_b - lambda_a));

    if (isnan(result))
    {
        fprintf(stderr, "Warning: Obtained %f when computing distance between %s and %s\n", result, a.nom, b.nom);
        fprintf(stderr, "%s[%u] : (%f,%f)\n%s[%u] : (%f,%f)\n", a.nom, a.array_ID, a.lat, a.lon, b.nom, b.array_ID, b.lat, b.lon);
    }

    return result;
}

double tree_cost(edge_t *edge_array, size_t n)
{
    double output = 0;
    for (size_t i = 0; i < n; i++)
    {
        output += edge_array[i].weight;
    }
    return output;
}
