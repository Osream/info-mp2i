#ifndef CITY_PARSER
#define CITY_PARSER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "min-spanning-tree.h"

// -------------------- Parser -------------------- //

#define HEADER "\"Geoname ID\";\"ASCII Name\";\"Country Code\";\"Population\";\"Latitude\";\"Longitude\""

unsigned parse_file(FILE* f, city_node_t** node_arr);


#endif /* CITY_PARSER */
