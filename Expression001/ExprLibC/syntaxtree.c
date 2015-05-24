#include "syntaxtree.h"
#include <stdlib.h>
#include <string.h>

struct syntax_node_number *alloc_node_number(
    int value
)
{
    struct syntax_node_number *nn = (struct syntax_node_number *)malloc(sizeof(struct syntax_node_number));
    nn->type = NODE_NUMBER;
    nn->value = value;
    return nn;
}

static void free_node_number(
    struct syntax_node *n
)
{
    if( n == 0 ) return;
    free(n);
}

struct syntax_node_variable *alloc_node_variable(
    const char *var
)
{
    if( var == 0 ) return 0;

    struct syntax_node_variable *nv = (struct syntax_node_variable *)malloc( sizeof(struct syntax_node_variable) );
    nv->type = NODE_VARIABLE;
    nv->var = strdup( var );
    return nv;
}

static void free_node_variable(
    struct syntax_node *n
)
{
    if( n == 0 ) return;
    struct syntax_node_variable *nv = (struct syntax_node_variable *)n;
    free(nv->var);
    free(n);
}

struct syntax_node_unary_op *alloc_node_unary_op(
    char symbol,
    struct syntax_node *operand
)
{
    struct syntax_node_unary_op *nu = (struct syntax_node_unary_op *)malloc(sizeof(struct syntax_node_unary_op));
    nu->type = NODE_UNARY_OP;
    nu->symbol = symbol;
    nu->operand = operand;
    return nu;
}

static void free_node_unary_op(
    struct syntax_node *n
)
{
    if( n == 0 ) return;
    struct syntax_node_unary_op *nu = (struct syntax_node_unary_op *)n;
    free_syntax_tree(nu->operand);
    free(n);
}

struct syntax_node_binary_op *alloc_node_binary_op(
    char symbol,
    struct syntax_node *operand1,
    struct syntax_node *operand2
)
{
    struct syntax_node_binary_op *nb = (struct syntax_node_binary_op *)malloc(sizeof(struct syntax_node_binary_op));
    nb->type = NODE_BINARY_OP;
    nb->symbol = symbol;
    nb->operand1 = operand1;
    nb->operand2 = operand2;
    return nb;
}

static void free_node_binary_op(
    struct syntax_node *n
)
{
    if( n == 0 ) return;

    struct syntax_node_binary_op *nb = (struct syntax_node_binary_op *)n;
    free_syntax_tree(nb->operand1);
    free_syntax_tree(nb->operand2);
    free(n);
}

struct syntax_node_assignment *alloc_node_assignment(
    const char *var,
    struct syntax_node *value
)
{
    if( var == 0 ) return 0;

    struct syntax_node_assignment *na = (struct syntax_node_assignment *)malloc( sizeof(struct syntax_node_assignment) );
    na->type = NODE_ASSIGNMENT;
    na->var = strdup( var );
    na->value = value;
    return na;
}

static void free_node_assignment(
    struct syntax_node *n
)
{
    if( n == 0 ) return ;

    struct syntax_node_assignment *na = (struct syntax_node_assignment *)n;
    free(na->var);
    free_syntax_tree(na->value);
    free(n);
}

void free_syntax_tree(
    struct syntax_node *n
)
{
    if(n == 0 ) return;

    switch(n->type){
    case NODE_UNDEFINED:
        break;
    case NODE_NUMBER:
        free_node_number(n);
        break;
    case NODE_VARIABLE:
        free_node_variable(n);
        break;
    case NODE_UNARY_OP:
        free_node_unary_op(n);
        break;
    case NODE_BINARY_OP:
        free_node_binary_op(n);
        break;
    case NODE_ASSIGNMENT:
        free_node_assignment(n);
        break;
    default:
        break;
    }
}
