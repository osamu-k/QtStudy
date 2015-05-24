#ifndef TOKENIZER_H
#define TOKENIZER_H

enum token_type {
    TOKEN_UNDEFINED,
    TOKEN_NAME,
    TOKEN_NUMBER,
    TOKEN_OP_ADD_SUB,
    TOKEN_OP_MUL_DIV,
    TOKEN_OP_EQUAL,
    TOKEN_PAREN_LEFT,
    TOKEN_PAREN_RIGHT,
    TOKEN_KEYWORD_VAR,
    TOKEN_END,
    TOKEN_UNRECOGNIZED
};

void tokenizer_set_text( const char *text );
void tokenizer_next();
enum token_type tokenizer_type();
const char *tokenizer_string();

#endif // TOKENIZER_H
