#include "tokenizer.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static char *source_text = 0;
static char *next_char = 0;
static enum token_type current_type = TOKEN_UNDEFINED;
static char *current_string = 0;

static bool get_number();
static bool get_name();
static bool get_single_char_token();
static void set_token( enum token_type type, const char *startp );
static void skip_spaces();

void tokenizer_set_text( const char *text )
{
    if(source_text != 0){
        free(source_text);
    }
    source_text = strdup(text);
    next_char = source_text;

    current_type = TOKEN_UNDEFINED;

    if(current_string != 0){
        free(current_string);
    }
    current_string = 0;
}

void tokenizer_next()
{
    skip_spaces();
    if( *next_char == 0 )
        set_token( TOKEN_END, 0 );
    else if( get_name() )
        ;
    else if( get_number() )
        ;
    else if( get_single_char_token() )
        ;
    else
        set_token( TOKEN_UNRECOGNIZED, 0 );
}

static void skip_spaces()
{
    for( ; isspace(*next_char); next_char++ )
        ;
}

static bool get_name()
{
    bool ret = false;
    if( isalpha( *next_char ) ){
        const char *startp = next_char;
        for( ; isalnum( *next_char ); next_char ++ )
            ;
        set_token( TOKEN_NAME, startp );

        if( strcmp("var", current_string) == 0 ){
            current_type = TOKEN_KEYWORD_VAR;
        }
        ret = true;
    }
    return ret;
}

static bool get_number(){
    bool ret = false;
    if( isdigit( *next_char) ){
        const char *startp = next_char ++;
        for( ; isdigit( *next_char ); next_char ++ )
            ;
        set_token( TOKEN_NUMBER, startp );
        ret = true;
    }
    return ret;
}

static bool get_single_char_token()
{
    enum token_type type = TOKEN_UNDEFINED;
    switch(*next_char){
    case '+':
    case '-':
        type = TOKEN_OP_ADD_SUB;
        break;
    case '*':
    case '/':
        type = TOKEN_OP_MUL_DIV;
        break;
    case '=':
        type = TOKEN_OP_EQUAL;
        break;
    case '(':
        type = TOKEN_PAREN_LEFT;
        break;
    case ')':
        type = TOKEN_PAREN_RIGHT;
        break;
    default:
        return false;
    }
    const char *startp = next_char ++;
    set_token( type, startp );
    return true;
}

static void set_token( enum token_type type, const char *startp )
{
    current_type = type;
    if( current_string != 0 )
        free( current_string );
    if( startp != 0 ){
        int size = next_char - startp;
        current_string = (char *)malloc( size + 1 );
        strncpy( current_string, startp, size );
        current_string[size] = '\0';
    }
    else{
        current_string = 0;
    }
}

enum token_type tokenizer_type()
{
    return current_type;
}

const char *tokenizer_string()
{
    return current_string;
}
