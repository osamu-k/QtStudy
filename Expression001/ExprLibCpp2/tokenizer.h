#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"
#include <map>
#include <string>

using namespace std;

class Tokenizer
{
public:
    Tokenizer();
    ~Tokenizer();
    void setSource( string source );
    Token next();
    string remainedString() const;
    Token current() const { return m_currentToken; }
private:
    void skipSpaces();
    bool makeTokenNumber();
    bool makeTokenName();
    bool makeTokenSingleChar();
    string m_source;
    Token m_currentToken;
    string::const_iterator m_nextc;
    string::const_iterator m_remainedString;
    static map<char,Token::Type> m_singleCharMap;
//    static map<string, Token::Type> m_keywordMap;
};

#endif // TOKENIZER_H
