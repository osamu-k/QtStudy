#include "evaluator.h"
#include "parser.h"
#include "varlist.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static int evaluate_number(struct syntax_node *n);
static int evaluate_variable(struct syntax_node *n);
static int evaluate_binary_op(struct syntax_node *n);
static int evaluate_unary_op(struct syntax_node *n);
static int evaluate_assignment(struct syntax_node *n);

static enum evaluation_status status = EVALUATION_OK;

int evaluate( struct syntax_node *n )
{
    status = EVALUATION_OK;

    if( n == 0 ){
        status = EVALUATION_ERROR_INCOMPLETE_SYNTAX;
        return 0;
    }

    switch( n->type ){
    case NODE_NUMBER:
        return evaluate_number(n);
    case NODE_VARIABLE:
        return evaluate_variable(n);
    case NODE_BINARY_OP:
        return evaluate_binary_op(n);
    case NODE_UNARY_OP:
        return evaluate_unary_op(n);
    case NODE_ASSIGNMENT:
        return evaluate_assignment(n);
    default:
        return 0;
    }
}

static int evaluate_number(struct syntax_node *n)
{
    struct syntax_node_number *nn = (struct syntax_node_number *)n;
    return nn->value;
}

static int evaluate_variable(struct syntax_node *n)
{
    int value = 0;
    struct syntax_node_variable *nv = (struct syntax_node_variable *)n;
    bool found = var_list_get( nv->var, &value );
    if( ! found ){
        status = EVALUATION_ERROR_UNDEFINED_VARIABLE;
    }
    return value;
}

static int evaluate_binary_op(struct syntax_node *n)
{
    struct syntax_node_binary_op *nb = (struct syntax_node_binary_op *)n;
    int o1 = evaluate( nb->operand1 );
    int o2 = evaluate( nb->operand2 );
    switch( nb->symbol ){
    case '+':
        return o1 + o2;
    case '-':
        return o1 - o2;
    case '*':
        return o1 * o2;
    case '/':
        if( o2 != 0 )
            return o1 / o2;
        else{
            status = EVALUATION_ERROR_DIVIDED_BY_ZERO;
            return 0;
        }
    default:
        return 0;
    }
}

static int evaluate_unary_op(struct syntax_node *n)
{
    struct syntax_node_unary_op *nb = (struct syntax_node_unary_op *)n;
    int o = evaluate( nb->operand );
    switch( nb->symbol ){
    case '+':
        return o;
    case '-':
        return - o;
    default:
        return 0;
    }
}

static int evaluate_assignment(struct syntax_node *n)
{
    int value = 0;
    struct syntax_node_assignment *na = (struct syntax_node_assignment *)n;
    value = evaluate( na->value );
    var_list_add( na->var, value );
    return value;
}

enum evaluation_status evaluation_status()
{
    return status;
}
