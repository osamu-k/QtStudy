#include "parser.h"

Node *Parser::parse( string source )
{
    m_error = false;
    m_tokenizer->setSource( source );
    nextToken();
    if( m_token == 0 || m_token->type() == Token::TYPE_END )
        return 0;

    Node *node = 0;
    if( m_token->type() == Token::TYPE_KEYWORD_VAR ){
        node = parseAssign();
    }
    else{
        node = parseExpression();
    }
    if( ! m_error ){
        if( ! m_tokenizer->remainedString().empty() ){
            setError("Unrecognized string '" + m_tokenizer->remainedString() + "'" );
        }
        else if( node == 0 ){
            setError("No eexpression.");
        }
    }
    return node;
}

Node *Parser::parseExpression()
{
    Node *operand1 = parseTerm();
    if( operand1 == 0 || m_error ){
        return operand1;
    }
    while( true ){
        string tokstr = m_token->getString();
        if( m_token->type() == Token::TYPE_OPERATOR_ADD ){
            nextToken();
            Node *operand2 = parseTerm();
            operand1 = new NodeAdd( operand1, operand2 );
            if( m_error )
                return operand1;
            if( operand2 == 0 ){
                setError("No expression after operator '" + tokstr + "'.");
                return operand1;
            }
        }
        else if( m_token->type() == Token::TYPE_OPERATOR_SUB ){
            nextToken();
            Node *operand2 = parseTerm();
            operand1 = new NodeSub( operand1, operand2 );
            if( m_error )
                return operand1;
            if( operand2 == 0 ){
                setError("No expression after operator '" + tokstr + "'.");
                return operand1;
            }
        }
        else{
            break;
        }
    }
    return operand1;
}

Node *Parser::parseTerm()
{
    Node *operand1 = parsePrefix();
    if( operand1 == 0 || m_error ){
        return operand1;
    }
    while(true){
        string tokstr = m_token->getString();
        if( m_token->type() == Token::TYPE_OPERATOR_MUL ){
            nextToken();
            Node *operand2 = parsePrefix();
            operand1 = new NodeMul( operand1, operand2 );
            if( m_error )
                return operand1;
            if( operand2 == 0 ){
                setError("No expression after operator '" + tokstr + "'.");
                return operand1;
            }
        }
        else if( m_token->type() == Token::TYPE_OPERATOR_DIV ){
            nextToken();
            Node *operand2 = parsePrefix();
            operand1 = new NodeDiv( operand1, operand2 );
            if( m_error )
                return operand1;
            if( operand2 == 0 ){
                setError("No expression after operator '" + tokstr + "'.");
                return operand1;
            }
        }
        else{
            break;
        }
    }
    return operand1;
}

Node *Parser::parsePrefix()
{
    if( m_token->type() == Token::TYPE_OPERATOR_ADD ){
        nextToken();
        Node *operand = parseFactor();
        Node * node = new NodePlus( operand );
        if( m_error ){
            return node;
        }
        if( operand == 0 ){
            setError("No expression after operator '+'.");
            return node;
        }
        return node;
    }
    else if( m_token->type() == Token::TYPE_OPERATOR_SUB ){
        nextToken();
        Node *operand = parseFactor();
        Node * node = new NodeMinus( operand );
        if( m_error ){
            return node;
        }
        if( operand == 0 ){
            setError("No expression after operator '-'.");
            return node;
        }
        return node;
    }
    else{
        return parseFactor();
    }
}

Node *Parser::parseFactor()
{
    if( m_token->type() == Token::TYPE_INTEGER ){
        TokenInteger *tokenInt = dynamic_cast<TokenInteger *>(m_token);
        Node *node = new NodeInteger( tokenInt->value() );
        nextToken();
        return node;
    }
    else if( m_token->type() == Token::TYPE_NAME ){
        TokenName *tokenName = dynamic_cast<TokenName *>(m_token);
        Node *node = new NodeVarRef(tokenName->name());
        nextToken();
        return node;
    }
    if( m_token->type() == Token::TYPE_PAREN_OPEN ){
        nextToken();
        Node *node = parseExpression();
        if( m_error )
            return node;
        if( m_token->type() != Token::TYPE_PAREN_CLOSE ){
            setError("Parenthesis is not closed.");
            return node;
        }
        nextToken();
        return node;
    }
    return 0;
}

Node *Parser::parseAssign()
{
    nextToken();
    if( m_token->type() != Token::TYPE_NAME ){
        m_error = true;
        m_errorMessage = "No variable name.";
        return new NodeAssign( 0, 0 );
    }
    TokenName *tokenName = dynamic_cast<TokenName*>(m_token);
    NodeVarDecl *varDecl = new NodeVarDecl( tokenName->name() );

    nextToken();
    if( m_token->type() != Token::TYPE_ASSIGNMENT ){
        setError("No assignment operator.");
        return new NodeAssign( varDecl, 0 );
    }

    nextToken();
    Node *value = parseExpression();
    if( m_error ){
        return value;
    }
    if( value == 0 ){
        setError("No expression after assignment operator.");
        return new NodeAssign( varDecl, value );
    }
    return new NodeAssign( varDecl, value );
}

void Parser::nextToken()
{
    if( m_token ) delete m_token;
    m_token = m_tokenizer->next();
}
