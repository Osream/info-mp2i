#include "city_parser.h"

#define UNUSED __attribute__((unused))

// -------------------- List structure -------------------- //

struct city_node_list_el
{
    struct city_node_list_el *prev, *next;
    city_node_t node;
};

typedef struct city_node_list_el *city_node_list;

// ----- Creation ----- //

static city_node_list create_empty_list(void)
{
    return NULL;
}

static struct city_node_list_el *create_empty_node(void)
{
    struct city_node_list_el *res = (struct city_node_list_el *)malloc(sizeof(struct city_node_list_el));
    res->next = NULL;
    res->prev = NULL;
    default_init(&res->node);
    return res;
}

static struct city_node_list_el *create_node(city_node_t *n)
{
    struct city_node_list_el *res = (struct city_node_list_el *)malloc(sizeof(struct city_node_list_el));
    res->next = NULL;
    res->prev = NULL;
    copy(&res->node, n);
    return res;
}

// ----- List access ----- //

static city_node_list next(city_node_list l)
{
    return l->next;
}

static city_node_list prev(city_node_list l)
{
    return l->prev;
}

// ----- List delete ----- //

static void prev_delete(city_node_list l)
{
    if (l == NULL)
        return;

    if (l->prev != NULL)
        prev_delete(l->prev);

    delete (&l->node);
    free(l);
}

static void next_delete(city_node_list l)
{
    if (l == NULL)
        return;

    if (l->next != NULL)
        next_delete(l->next);

    delete (&l->node);
    free(l);
}

static void list_delete(city_node_list l)
{
    if (l == NULL)
        return;

    if (l->prev != NULL)
        prev_delete(l->prev);

    if (l->next != NULL)
        next_delete(l->next);

    delete (&l->node);
    free(l);
}

// ----- List append ----- //

// Returns a ref to the first element of the list
static UNUSED city_node_list list_append_prev(city_node_list l, city_node_t *n)
{
    if (l == NULL)
        return create_node(n);

    if (l->prev == NULL)
    {
        struct city_node_list_el *new_el = create_node(n);
        l->prev = new_el;
        new_el->next = l;
        return new_el;
    }
    else
    {
        return list_append_prev(l->prev, n);
    }
}

// Returns an ref to the last element of the list
static UNUSED city_node_list list_append_next(city_node_list l, city_node_t *n)
{
    if (l == NULL)
        return create_node(n);

    if (l->next == NULL)
    {
        struct city_node_list_el *new_el = create_node(n);
        l->next = new_el;
        new_el->prev = l;
        return new_el;
    }
    else
    {
        return list_append_next(l->next, n);
    }
}

// Returns a ref to the first element of the list
static UNUSED city_node_list list_append_empty_prev(city_node_list l)
{
    if (l == NULL)
        return create_empty_node();

    if (l->prev == NULL)
    {
        struct city_node_list_el *new_el = create_empty_node();
        l->prev = new_el;
        new_el->next = l;
        return new_el;
    }
    else
    {
        return list_append_empty_prev(l->prev);
    }
}

// Returns an ref to the last element of the list
static city_node_list list_append_empty_next(city_node_list l)
{
    if (l == NULL)
        return create_empty_node();

    if (l->next == NULL)
    {
        struct city_node_list_el *new_el = create_empty_node();
        l->next = new_el;
        new_el->prev = l;
        return new_el;
    }
    else
    {
        return list_append_empty_next(l->next);
    }
}

// ----- List length ----- //

static unsigned prev_length(city_node_list l)
{
    if (l == NULL)
        return 0;

    if (l->prev == NULL)
        return 1;
    else
        return 1 + prev_length(l->prev);
}

static unsigned next_length(city_node_list l)
{
    if (l == NULL)
        return 0;

    if (l->next == NULL)
        return 1;
    else
        return 1 + next_length(l->next);
}

static unsigned total_length(city_node_list l)
{
    if (l == NULL)
        return 0;

    unsigned prev_l = 0;
    unsigned next_l = 0;

    if (l->prev != NULL)
        prev_l = prev_length(l->prev);

    if (l->next != NULL)
        next_l = next_length(l->next);

    return prev_l + 1 + next_l;
}

// ----- List to array ----- //

// Convert the given list 'l' to an array (put at the location fixed by 'array_ptr')
// Returns the size of the built array
static unsigned list_to_array(city_node_list l, city_node_t **array_ptr)
{
    if (l == NULL)
        return 0;

    unsigned size = total_length(l);
    *array_ptr = (city_node_t *)malloc(size * sizeof(city_node_t));

    city_node_list it = l;
    unsigned index = 0;

    // Copy nodes before
    while (it != NULL)
    {
        copy(&(*array_ptr)[index], &it->node);
        (*array_ptr)[index].array_ID = index;
        it = prev(it);
        index++;
    }

    // Copy nodes after
    it = l->next;
    while (it != NULL)
    {
        copy(&(*array_ptr)[index], &it->node);
        (*array_ptr)[index].array_ID = index;
        it = next(it);
        index++;
    }

    return size;
}

// -------------------- CSV parser -------------------- //

static void parse_line(char *line, city_node_t *node)
{
    char *tok;
    int field_num = 0;
    for (tok = strtok(line, ";"); (tok != NULL) && (*tok != '\0'); tok = strtok(NULL, ";\n"))
    {
        switch (field_num)
        {
        case 0:
            node->ID = strtol(tok, NULL, 10);
            break;

        case 1:
            // Remove First and Last character (assuming it is ")
            node->nom = strdup(&tok[1]);
            node->nom[strlen(node->nom) - 1] = '\0';
            break;

        case 2: // Country code
        case 3: // Population
            break;

        case 4:
            node->lat = strtod(tok, NULL);
            if (isnan(node->lat))
            {
                fprintf(stderr,"Error while parsing latitude for line:\n%s\n",line);
            }
            break;
        case 5:
            node->lon = strtod(tok, NULL);
            if (isnan(node->lon))
            {
                fprintf(stderr,"Error while parsing latitude for line:\n%s\n",line);
            }
            break;
        default:
            fprintf(stderr, "Colonne supplementaire inattendue!\n");
            exit(1);
            break;
        }
        field_num++;
    }
}

unsigned parse_file(FILE *f, city_node_t **node_arr)
{
    char buffer[1024];
    if (fgets(buffer, 1024, f))
    {
        if (strncmp(buffer, HEADER, sizeof(HEADER) - 1) != 0)
        {
            fprintf(stderr, "Unexpected header! Expected:\n%s\nGot:\n%s\n", HEADER, buffer);
            exit(1);
        }
    }
    else
    {
        fprintf(stderr, "Error while reading the first line\n");
        exit(1);
    }

    city_node_list l = create_empty_list();

    while (fgets(buffer, 1024, f))
    {
        l = list_append_empty_next(l);
        parse_line(buffer, &l->node);
    }

    unsigned size = list_to_array(l, node_arr);
    list_delete(l);
    return size;
}
