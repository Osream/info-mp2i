#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "city_graph.h"
#include "city_parser.h"
#include "min-spanning-tree.h"
#include "geojson_producer.h"

// ----- Program entry point ----- //

static void print_help(char *prog_name)
{
    printf("TP11 -- Arbre couvrant\n\n");
    printf("Usage:\n%s [-p] villes.csv [output.geojson]\n\n", prog_name);
    printf(
        "Calcule l'arbre couvrant de poids minimal sur le graphe geometrique\n"
        "des villes donnee en entree. Par defaut, utilise l'algorithme de Kruskal.\n\n"
        "Arguments:\n"
        "\t villes.csv     : Fichier a lire pour recuperer la listes des villes.\n"
        "\t                  Si vide, lis sur l'entree standard a la place.\n\n"
        "\t output.geojson : Fichier dans lequel ecrire le resultat (liste des villes\n"
        "\t                  et liste des aretes).\n"
        "\t                  Si vide, ecrit dans 'villes.csv.[kruskal|prim].geojson'.\n"
        "\t                  Si 'villes.csv' est aussi vide,\n"
        "\t                    ecrit dans 'default_output.geojson'.\n\n"
        "Options:\n"
        "\t -h : Ecrit ce message.\n"
        "\t -p : Utilise l'algorithme de Prim au lieu de Kruskal.\n");
}

int main(int argc, char *argv[])
{
    int c;
    bool prim_flag = false;

    while ((c = getopt(argc, argv, "hp")) != -1)
    {
        switch (c)
        {
        case 'p':
            prim_flag = true;
            break;
        case 'h':
            print_help(argv[0]);
            exit(0);
            break;
        case '?':
            if (isprint(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
            break;
        default:
            abort();
            break;
        }
    }

    FILE *file = NULL;
    FILE *output_file = NULL;
    if (argc - (optind - 1) < 2)
    {
        file = stdin;
    }
    else
    {
        file = fopen(argv[1 + (optind - 1)], "r");
    }

    printf("- Parsing ...");

    city_node_t *node_array = NULL;
    unsigned node_count = parse_file(file, &node_array);

    printf(" Done\n");

    fclose(file);

    printf("- Computing using ");

    edge_t *spanning_tree;
    if (prim_flag)
    {
        printf("Prim algorithm");
        spanning_tree = prim(node_array, node_count);
    }
    else
    {
        printf("Kruskal algorithm");
        spanning_tree = kruskal(node_array, node_count);
    }

    printf(" ... Done\n");
    printf("-> Tree cost: %f\n", tree_cost(spanning_tree, node_count - 1));

    printf("- Dumping results in ");

    if (argc - (optind - 1) >= 3)
    {
        output_file = fopen(argv[2 + (optind - 1)], "w");
        printf("'%s' ...", argv[2 + (optind - 1)]);
    }
    else
    {
        char *output_file_name;
        if (argc - (optind - 1) < 2)
        {
            output_file_name = "default_output.geojson";
            output_file = fopen(output_file_name, "w");
            printf("'%s' ...", output_file_name);
        }
        else
        {
            if (prim_flag)
            {
                output_file_name = (char *)malloc(strlen(argv[1 + (optind - 1)]) + sizeof(".prim.geojson") + 1);
                strcpy(output_file_name, argv[1 + (optind - 1)]);
                strcat(output_file_name, ".prim.geojson");
            }
            else
            {
                output_file_name = (char *)malloc(strlen(argv[1 + (optind - 1)]) + sizeof(".kruskal.geojson") + 1);
                strcpy(output_file_name, argv[1 + (optind - 1)]);
                strcat(output_file_name, ".kruskal.geojson");
            }
            output_file = fopen(output_file_name, "w");
            printf("'%s' ...", output_file_name);
            free(output_file_name);
        }
    }

    dump_nodes_and_edges(output_file,
                         node_array, node_count,
                         spanning_tree, node_count - 1);

    fclose(output_file);

    printf(" Done!\n");

    for (size_t i = 0; i < node_count; i++)
    {
        delete (&node_array[i]);
    }
    free(node_array);

    free(spanning_tree);

    return 0;
}
