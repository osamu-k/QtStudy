#include "parser.h"
#include "tokenizer.h"
#include <stdlib.h>
#include <string.h>

struct syntax_node *parse_expression();
struct syntax_node *parse_term();
struct syntax_node *parse_signed();
struct syntax_node *parse_factor();
struct syntax_node *parse_assignment();

enum parsing_status status = PARSING_OK;

struct syntax_node *parse( const char *source )
{
    status = PARSING_OK;
    struct syntax_node *node = 0;

    if( source == 0 ){
        status = PARSING_ERROR_SOURCE_NULL;
        return node;
    }

    tokenizer_set_text( source );
    tokenizer_next();
    if( tokenizer_type() == TOKEN_KEYWORD_VAR ){
        node = parse_assignment();
    }
    else{
        node = parse_expression();
    }
    if( tokenizer_type() == TOKEN_UNRECOGNIZED ){
        if( status != PARSING_OK ){
            status = PARSING_ERROR_EXTRA_CHARACTERS;
        }
    }
    return node;
}

struct syntax_node *parse_expression()
{
    if( status != PARSING_OK )
        return 0;
    struct syntax_node *n1 = parse_term();
    if( n1 ){
        while( tokenizer_type() == TOKEN_OP_ADD_SUB ){
            char symbol = tokenizer_string()[0];
            tokenizer_next();
            struct syntax_node *n2 = parse_term();
            if( n2 == 0 ){
                status = PARSING_ERROR_NO_OPERAND_OF_BINARY_OP;
                break;
            }
            n1 = (struct syntax_node *)alloc_node_binary_op( symbol, n1, n2 );
        }
    }
    return n1;
}

struct syntax_node *parse_term()
{
    if( status != PARSING_OK )
        return 0;
    struct syntax_node *n1 = parse_signed();
    if( n1 ){
        while( tokenizer_type() == TOKEN_OP_MUL_DIV ){
            char symbol = tokenizer_string()[0];
            tokenizer_next();
            struct syntax_node *n2 = parse_signed();
            if( n2 == 0 ){
                status = PARSING_ERROR_NO_OPERAND_OF_BINARY_OP;
                break;
            }
            n1 = (struct syntax_node *)alloc_node_binary_op( symbol, n1, n2 );
        }
    }
    return n1;
}

struct syntax_node *parse_signed()
{
    if( status != PARSING_OK )
        return 0;
    if( tokenizer_type() == TOKEN_OP_ADD_SUB ){
        char symbol = tokenizer_string()[0];
        tokenizer_next();
        struct syntax_node *operand = parse_factor();
        if( operand != 0 ){
            return (struct syntax_node *)alloc_node_unary_op( symbol, operand );
        }
        else{
            status = PARSING_ERROR_NO_OPERAND_OF_UNARY_OP;
            return 0;
        }
    }
    else{
        return parse_factor();
    }
}

struct syntax_node *parse_factor()
{
    if( status != PARSING_OK )
        return 0;
    if( tokenizer_type() == TOKEN_NUMBER ){
        struct syntax_node_number *nn = alloc_node_number(atoi(tokenizer_string()));
        tokenizer_next();
        return (struct syntax_node *)nn;
    }
    else if( tokenizer_type() == TOKEN_NAME ){
        struct syntax_node_variable *nv = alloc_node_variable(tokenizer_string());
        tokenizer_next();
        return (struct syntax_node *)nv;
    }
    else if( tokenizer_type() == TOKEN_PAREN_LEFT ){
        tokenizer_next();
        struct syntax_node *n = parse_expression();
        if( tokenizer_type() == TOKEN_PAREN_RIGHT ){
            tokenizer_next();
        }
        else{
            status = PARSING_ERROR_NO_RIGHT_PARENTHESIS;
        }
        return n;
    }
    return 0;
}

struct syntax_node *parse_assignment()
{
    tokenizer_next();
    if( tokenizer_type() != TOKEN_NAME ){
        status = PARSING_ERROR_NO_VARIABLE_NAME;
        return 0;
    }
    char *var = strdup( tokenizer_string() );
    tokenizer_next();
    if( tokenizer_type() != TOKEN_OP_EQUAL ){
        status = PARSING_ERROR_NO_EQUAL_OP;
        free(var);
        return 0;
    }
    tokenizer_next();
    struct syntax_node *value = parse_expression();
    if( value == 0 ){
        status = PARSING_ERROR_NO_ASSIGNMENT_VALUE;
        free(var);
        return 0;
    }
    struct syntax_node *na = (struct syntax_node *)alloc_node_assignment(var,value);
    free(var);
    return (struct syntax_node *)na;
}

enum parsing_status parsing_status()
{
    return status;
}
