#include "parser.h"

Parser::Parser( Tokenizer *tokenizer )
    : m_tokenizer(tokenizer),m_token(0),m_status(PARSING_OK)
{
}

Parser::~Parser()
{
}

SyntaxNode *Parser::parse( string source )
{
    m_status = PARSING_OK;
    m_tokenizer->setSource( source );
    nextToken();
    if( m_token == 0 || m_token->type() == Token::TYPE_END )
        return 0;

    SyntaxNode *node = 0;
    if( m_token->type() == Token::TYPE_KEYWORD_VAR ){
        node = parseAssign();
    }
    else{
        node = parseExpression();
    }
    if( isError() ){
        if( ! m_tokenizer->remainedString().empty() ){
            setError(PARSING_ERROR_EXTRA_CHARACTERS, "Unrecognized string '" + m_tokenizer->remainedString() + "'" );
        }
        else if( node == 0 ){
            setError(PARSING_ERROR_NO_EXPRESSION, "No eexpression.");
        }
    }
    return node;
}

SyntaxNode *Parser::parseExpression()
{
    SyntaxNode *operand1 = parseTerm();
    if( operand1 == 0 || isError() ){
        return operand1;
    }
    while( true ){
        string tokstr = m_token->getString();
        if( m_token->type() == Token::TYPE_OPERATOR_ADD ){
            nextToken();
            SyntaxNode *operand2 = parseTerm();
            operand1 = new SyntaxNodeAdd( operand1, operand2 );
            if( isError() )
                return operand1;
            if( operand2 == 0 ){
                setError(PARSING_ERROR_NO_OPERAND_OF_BINARY_OP,"No expression after operator '" + tokstr + "'.");
                return operand1;
            }
        }
        else if( m_token->type() == Token::TYPE_OPERATOR_SUB ){
            nextToken();
            SyntaxNode *operand2 = parseTerm();
            operand1 = new SyntaxNodeSub( operand1, operand2 );
            if( isError() )
                return operand1;
            if( operand2 == 0 ){
                setError(PARSING_ERROR_NO_OPERAND_OF_BINARY_OP,"No expression after operator '" + tokstr + "'.");
                return operand1;
            }
        }
        else{
            break;
        }
    }
    return operand1;
}

SyntaxNode *Parser::parseTerm()
{
    SyntaxNode *operand1 = parsePrefix();
    if( operand1 == 0 || isError() ){
        return operand1;
    }
    while(true){
        string tokstr = m_token->getString();
        if( m_token->type() == Token::TYPE_OPERATOR_MUL ){
            nextToken();
            SyntaxNode *operand2 = parsePrefix();
            operand1 = new SyntaxNodeMul( operand1, operand2 );
            if( isError() )
                return operand1;
            if( operand2 == 0 ){
                setError(PARSING_ERROR_NO_OPERAND_OF_BINARY_OP, "No expression after operator '" + tokstr + "'.");
                return operand1;
            }
        }
        else if( m_token->type() == Token::TYPE_OPERATOR_DIV ){
            nextToken();
            SyntaxNode *operand2 = parsePrefix();
            operand1 = new SyntaxNodeDiv( operand1, operand2 );
            if( isError() )
                return operand1;
            if( operand2 == 0 ){
                setError(PARSING_ERROR_NO_OPERAND_OF_BINARY_OP, "No expression after operator '" + tokstr + "'.");
                return operand1;
            }
        }
        else{
            break;
        }
    }
    return operand1;
}

SyntaxNode *Parser::parsePrefix()
{
    if( m_token->type() == Token::TYPE_OPERATOR_ADD ){
        nextToken();
        SyntaxNode *operand = parseFactor();
        SyntaxNode * node = new SyntaxNodePlus( operand );
        if( isError() ){
            return node;
        }
        if( operand == 0 ){
            setError(PARSING_ERROR_NO_OPERAND_OF_UNARY_OP, "No expression after operator '+'.");
            return node;
        }
        return node;
    }
    else if( m_token->type() == Token::TYPE_OPERATOR_SUB ){
        nextToken();
        SyntaxNode *operand = parseFactor();
        SyntaxNode * node = new SyntaxNodeMinus( operand );
        if( isError() ){
            return node;
        }
        if( operand == 0 ){
            setError(PARSING_ERROR_NO_OPERAND_OF_UNARY_OP, "No expression after operator '-'.");
            return node;
        }
        return node;
    }
    else{
        return parseFactor();
    }
}

SyntaxNode *Parser::parseFactor()
{
    if( m_token->type() == Token::TYPE_INTEGER ){
        TokenInteger *tokenInt = dynamic_cast<TokenInteger *>(m_token);
        SyntaxNode *node = new SyntaxNodeNumber( tokenInt->value() );
        nextToken();
        return node;
    }
    else if( m_token->type() == Token::TYPE_NAME ){
        TokenName *tokenName = dynamic_cast<TokenName *>(m_token);
        SyntaxNode *node = new SyntaxNodeVarRef(tokenName->name());
        nextToken();
        return node;
    }
    if( m_token->type() == Token::TYPE_PAREN_OPEN ){
        nextToken();
        SyntaxNode *node = parseExpression();
        if( isError() )
            return node;
        if( m_token->type() != Token::TYPE_PAREN_CLOSE ){
            setError(PARSING_ERROR_NO_RIGHT_PARENTHESIS, "Parenthesis is not closed.");
            return node;
        }
        nextToken();
        return node;
    }
    return 0;
}

SyntaxNode *Parser::parseAssign()
{
    nextToken();
    if( m_token->type() != Token::TYPE_NAME ){
        setError(PARSING_ERROR_NO_VARIABLE_NAME, "No variable name.");
        return new SyntaxNodeAssign( 0, 0 );
    }
    TokenName *tokenName = dynamic_cast<TokenName*>(m_token);
    SyntaxNodeVarDecl *varDecl = new SyntaxNodeVarDecl( tokenName->name() );

    nextToken();
    if( m_token->type() != Token::TYPE_ASSIGNMENT ){
        setError(PARSING_ERROR_NO_EQUAL_OP, "No variable name.");
        return new SyntaxNodeAssign( varDecl, 0 );
    }

    nextToken();
    SyntaxNode *value = parseExpression();
    if( isError() ){
        return value;
    }
    if( value == 0 ){
        setError(PARSING_ERROR_NO_ASSIGNMENT_VALUE, "No expression after assignment operator.");
        return new SyntaxNodeAssign( varDecl, value );
    }
    return new SyntaxNodeAssign( varDecl, value );
}

void Parser::nextToken()
{
    if( m_token ) delete m_token;
    m_token = m_tokenizer->next();
}

void Parser::setError( ParsingStatus status, string message )
{
    m_status = status;
    m_errorMessage = message;
}

bool Parser::isError()
{
    return m_status != PARSING_OK;
}

Parser::ParsingStatus Parser::status()
{
    return m_status;
}

string Parser::errorMessage()
{
    return m_errorMessage;
}

