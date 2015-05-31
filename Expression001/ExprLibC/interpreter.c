#include "interpreter.h"
#include "parser.h"
#include "evaluator.h"
#include "syntaxtree.h"

int interpret( const char *source )
{
    int value = 0;
    struct syntax_node *node = parse( source );
    if( parsing_status() == PARSING_OK ){
        value = evaluate( node );
    }
    free_syntax_tree( node );
    return value;
}
