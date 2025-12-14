#include "geojson_producer.h"

void dump_city(FILE* fp, const city_node_t* node)
{
    fprintf(
        fp,
        "{\n\"type\": \"Feature\",\n"   \
        "\"geometry\": {\n"             \
        "   \"type\": \"Point\",\n"     \
        "   \"coordinates\": [%f,%f]\n" \
        "},\n"                          \
        "\"properties\": {\n"           \
        "   \"ID\": %d,\n"              \
        "   \"name\": \"%s\"\n"         \
        "}\n}",
        node->lon, node->lat, node->ID, node->nom
    );
}


void dump_edge(FILE* fp, const edge_t* edge, const city_node_t* node_array)
{
    fprintf(
        fp,
        "{\n\"type\": \"Feature\",\n"   \
        "\"geometry\": {\n"             \
        "   \"type\": \"LineString\",\n"\
        "   \"coordinates\": \n"        \
        "       [ [%f,%f], [%f,%f] ]\n" \
        "},\n"                          \
        "\"properties\": {\n"           \
        "   \"ID1\": %d,\n"             \
        "   \"ID2\": %d,\n"             \
        "   \"name1\": \"%s\",\n"        \
        "   \"name2\": \"%s\",\n"        \
        "   \"distance\": %f\n"         \
        "}\n}",
        node_array[edge->ID_1].lon, node_array[edge->ID_1].lat,
        node_array[edge->ID_2].lon, node_array[edge->ID_2].lat,
        node_array[edge->ID_1].ID,
        node_array[edge->ID_2].ID,
        node_array[edge->ID_1].nom,
        node_array[edge->ID_2].nom,
        edge->weight
    );
}

void dump_nodes_and_edges(FILE* fp, const city_node_t* nodes, const size_t node_count,
                                    const edge_t* edges, const size_t edge_count)
{
    fprintf(
        fp,
        "{\n\"type\": \"FeatureCollection\",\n"\
        "\"features\": [\n"
    );

    for(size_t n = 0; n < node_count; n++)
    {
        dump_city(fp,&nodes[n]);
        fprintf(fp,",\n");
    }
    for (size_t e = 0; e < edge_count-1; e++)
    {
        dump_edge(fp,&edges[e],nodes);
        fprintf(fp,",\n");
    }
    dump_edge(fp,&edges[edge_count-1],nodes);
    fprintf(fp,"]}\n");
}