#ifndef PARSER_H
#define PARSER_H

#include "node.h"
#include "tokenizer.h"

class Parser
{
public:
    enum ParsingStatus {
        PARSING_OK,
        PARSING_ERROR_SOURCE_NULL,
        PARSING_ERROR_EXTRA_CHARACTERS,
        PARSING_ERROR_NO_EXPRESSION,
        PARSING_ERROR_NO_OPERAND_OF_BINARY_OP,
        PARSING_ERROR_NO_OPERAND_OF_UNARY_OP,
        PARSING_ERROR_NO_RIGHT_PARENTHESIS,
        PARSING_ERROR_NO_VARIABLE_NAME,
        PARSING_ERROR_NO_EQUAL_OP,
        PARSING_ERROR_NO_ASSIGNMENT_VALUE
    };

    Parser( Tokenizer *tokenizer );
    ~Parser();
    Node *parse( string source );
//    void setError( string message );
    void setError( ParsingStatus status, string message );
    bool isError();
    ParsingStatus status();
    string errorMessage();
private:
    Node *parseExpression();
    Node *parseTerm();
    Node *parsePrefix();
    Node *parseFactor();
    Node *parseAssign();
    void nextToken();
    Tokenizer *m_tokenizer;
    Token *m_token;
//    bool m_error;
    ParsingStatus m_status;
    string m_errorMessage;
};

#endif // PARSER_H
