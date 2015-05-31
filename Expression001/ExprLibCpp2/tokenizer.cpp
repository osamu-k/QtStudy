#include "tokenizer.h"
#include "ctype.h"

map<char,Token::Type> Tokenizer::m_singleCharMap;
//map<string, Token::Type> Tokenizer::m_keywordMap;

Tokenizer::Tokenizer()
{
    m_singleCharMap['+'] = Token::TYPE_OPERATOR_ADD;
    m_singleCharMap['-'] = Token::TYPE_OPERATOR_SUB;
    m_singleCharMap['*'] = Token::TYPE_OPERATOR_MUL;
    m_singleCharMap['/'] = Token::TYPE_OPERATOR_DIV;
    m_singleCharMap['('] = Token::TYPE_PAREN_OPEN;
    m_singleCharMap[')'] = Token::TYPE_PAREN_CLOSE;
//    m_singleCharMap['='] = Token::TYPE_ASSIGNMENT;

//    m_keywordMap["var"] = Token::TYPE_KEYWORD_VAR;
}

Tokenizer::~Tokenizer()
{
}

void Tokenizer::setSource( string source )
{
    m_source = source;
    m_nextc = m_source.begin();
    m_remainedString = m_source.begin();
}

void Tokenizer::skipSpaces()
{
    while( isspace(*m_nextc) )
        m_nextc++;
}

Token Tokenizer::next()
{
    skipSpaces();
    m_remainedString = m_nextc;

    if( makeTokenNumber() )
        ;
    else if( makeTokenName() )
        ;
    else if( makeTokenSingleChar())
        ;
    else
        m_currentToken = Token("", Token::TYPE_END);
    return m_currentToken;
}

string Tokenizer::remainedString() const
{
    string::const_iterator end = m_source.end();
    return string(m_remainedString,end);
}

bool Tokenizer::makeTokenNumber()
{
    bool ret = false;
    if( isnumber(*m_nextc) ){
        ret = true;
        string::const_iterator start = m_nextc;
        while( isnumber(*m_nextc) )
            m_nextc++;
        m_currentToken = Token(string( start, m_nextc ),Token::TYPE_NUMBER);
    }
    return ret;
}

bool Tokenizer::makeTokenName()
{
    bool ret = false;
    if( isalpha(*m_nextc) ){
        ret = true;
        string::const_iterator start = m_nextc;
        while( isalnum(*m_nextc) )
            m_nextc++;
        string name = string( start, m_nextc );

//        map<string, Token::Type>::const_iterator it = m_keywordMap.find(name);
//        if( it != m_keywordMap.end() )
//            m_currentToken = Token(name,it->second);
//        else
//            m_currentToken = Token(name,Token::TYPE_NAME);
    }
    return ret;
}

bool Tokenizer::makeTokenSingleChar()
{
    bool ret = false;
    map<char,Token::Type>::const_iterator it = m_singleCharMap.find(*m_nextc);
    if( it != m_singleCharMap.end() ){
        string::const_iterator start = m_nextc;
        m_nextc++;
        m_currentToken = Token(string( start, m_nextc ),it->second);
        ret = true;
    }
    return ret;
}
