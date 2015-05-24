#include "varlist.h"
#include <stdlib.h>
#include <string.h>

struct variable_list_node {
    char *name;
    int value;
    struct variable_list_node *next;
};

static struct variable_list_node *var_list = 0;

void var_list_add( char *name, int value )
{
    if( name == 0 ) return;

    struct variable_list_node *new_element = (struct variable_list_node *)malloc( sizeof(struct variable_list_node) );
    new_element->name = strdup( name );
    new_element->value = value;
    new_element->next = var_list;
    var_list = new_element;
}

bool var_list_get( char *name, int *value )
{
    if( name == 0 ) return false;

    for( struct variable_list_node *acp = var_list; acp != 0; acp = acp->next ){
        if( strcmp( name, acp->name) == 0 ){
            *value = acp->value;
            return true;
        }
    }
    return false;
}
