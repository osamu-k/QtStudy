#include "parser.h"

Parser::Parser( Tokenizer *tokenizer )
    : m_tokenizer(tokenizer),m_status(PARSING_OK)
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
    SyntaxNode *node = 0;
    if( m_token.type() == Token::TYPE_KEYWORD_VAR ){
        node = parseAssign();
    }
    else{
        node = parseExpression();
    }
    if( ! isError() ){
        if( ! m_tokenizer->remainedString().empty() )
            setError(PARSING_ERROR_EXTRA_CHARACTERS, "Unrecognized string '" + m_tokenizer->remainedString() + "'" );
        else if( node == 0 )
            setError(PARSING_ERROR_NO_EXPRESSION, "No eexpression.");
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
        if( (m_token.type() == Token::TYPE_OPERATOR_ADD)
            ||(m_token.type() == Token::TYPE_OPERATOR_SUB) ){
            Token token = m_token;
            nextToken();
            SyntaxNode *operand2 = parseTerm();
            if( token.type() == Token::TYPE_OPERATOR_ADD )
                operand1 = new SyntaxNodeAdd( operand1, operand2 );
            else
                operand1 = new SyntaxNodeSub( operand1, operand2 );
            if( isError() )
                return operand1;
            if( operand2 == 0 ){
                setError(PARSING_ERROR_NO_OPERAND_OF_BINARY_OP,"No expression after operator '" + token.getString() + "'.");
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
        if( (m_token.type() == Token::TYPE_OPERATOR_MUL)
            || (m_token.type() == Token::TYPE_OPERATOR_DIV) ){
            Token token = m_token;
            nextToken();
            SyntaxNode *operand2 = parsePrefix();
            if(token.type() == Token::TYPE_OPERATOR_MUL)
                operand1 = new SyntaxNodeMul( operand1, operand2 );
            else
                operand1 = new SyntaxNodeDiv( operand1, operand2 );
            if( isError() )
                return operand1;
            if( operand2 == 0 ){
                setError(PARSING_ERROR_NO_OPERAND_OF_BINARY_OP, "No expression after operator '" + token.getString() + "'.");
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
    SyntaxNode *node = 0;
    if( (m_token.type() == Token::TYPE_OPERATOR_ADD)
        || (m_token.type() == Token::TYPE_OPERATOR_SUB) ){
        Token token = m_token;
        nextToken();
        SyntaxNode *operand = parseFactor();
        if(token.type() == Token::TYPE_OPERATOR_ADD)
            node = new SyntaxNodePlus( operand );
        else
            node = new SyntaxNodeMinus( operand );
        if( isError() ){
            return node;
        }
        if( operand == 0 ){
            setError(PARSING_ERROR_NO_OPERAND_OF_UNARY_OP, "No expression after operator '" + token.getString() + "'.");
            return node;
        }
    }
    else{
        node = parseFactor();
    }
    return node;
}

SyntaxNode *Parser::parseFactor()
{
    if( m_token.type() == Token::TYPE_NUMBER ){
        SyntaxNode *node = new SyntaxNodeNumber( std::atoi(m_token.getString().c_str()) );
        nextToken();
        return node;
    }
    else if( m_token.type() == Token::TYPE_NAME ){
        SyntaxNode *node = new SyntaxNodeVarRef(m_token.getString());
        nextToken();
        return node;
    }
    if( m_token.type() == Token::TYPE_PAREN_OPEN ){
        nextToken();
        SyntaxNode *node = parseExpression();
        if( isError() )
            return node;
        if( node == 0 ){
            setError(PARSING_ERROR_NO_EXPRESSION_AFTER_PARENTHESIS, "No expression after '('.");
            return node;
        }
        if( m_token.type() != Token::TYPE_PAREN_CLOSE ){
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
    if( m_token.type() != Token::TYPE_NAME ){
        setError(PARSING_ERROR_NO_VARIABLE_NAME, "No variable name.");
        return new SyntaxNodeAssign( 0, 0 );
    }
    SyntaxNodeVarDecl *varDecl = new SyntaxNodeVarDecl( m_token.getString() );
    nextToken();
    if( m_token.type() != Token::TYPE_ASSIGNMENT ){
        setError(PARSING_ERROR_NO_EQUAL_OP, "No variable name.");
        return new SyntaxNodeAssign( varDecl, 0 );
    }
    nextToken();
    SyntaxNode *value = parseExpression();
    if( isError() )
        return value;
    if( value == 0 )
        setError(PARSING_ERROR_NO_ASSIGNMENT_VALUE, "No expression after assignment operator.");
    return new SyntaxNodeAssign( varDecl, value );
}

void Parser::nextToken()
{
    m_token = m_tokenizer->next();
}

void Parser::setError( ParsingStatus status, string message )
{
    m_status = status;
    m_errorMessage = message;
}
