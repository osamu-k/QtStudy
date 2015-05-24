#include "token.h"

Token::Token( string s, Type type )
    :m_type(type),m_string(s)
{
}

Token::~Token()
{
}

Token::Type Token::type() const
{
    return m_type;
}

void Token::setString( string s )
{
    m_string = s;
}

string Token::getString()
{
    return m_string;
}

TokenInteger::TokenInteger( string s, int value )
    : Token(s,TYPE_INTEGER),m_value(value)
{
}

TokenInteger::~TokenInteger()
{
}

int TokenInteger::value()
{
    return m_value;
}

TokenName::TokenName( string s, string name )
    :Token(s,TYPE_NAME),m_name(name)
{
}

TokenName::~TokenName()
{
}

string TokenName::name()
{
    return m_name;
}
