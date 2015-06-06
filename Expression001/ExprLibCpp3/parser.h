#ifndef PARSER_H
#define PARSER_H

#include "syntaxnode.h"
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
        PARSING_ERROR_NO_EXPRESSION_AFTER_PARENTHESIS,
        PARSING_ERROR_NO_VARIABLE_NAME,
        PARSING_ERROR_NO_EQUAL_OP,
        PARSING_ERROR_NO_ASSIGNMENT_VALUE
    };

    Parser( Tokenizer *tokenizer );
    ~Parser();
    SyntaxNode *parse( string source );
    bool isError() const { return m_status != PARSING_OK; }
    ParsingStatus status() const {return m_status; }
    string errorMessage() const { return m_errorMessage; }
private:
    void nextToken();
    SyntaxNode *parseExpression();
    SyntaxNode *parseTerm();
    SyntaxNode *parsePrefix();
    SyntaxNode *parseFactor();
    SyntaxNode *parseAssign();
    void setError( ParsingStatus status, string message );
    Tokenizer *m_tokenizer;
    Token m_token;
    ParsingStatus m_status;
    string m_errorMessage;
};

#endif // PARSER_H
