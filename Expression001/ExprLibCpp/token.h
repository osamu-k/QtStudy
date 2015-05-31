#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

class Token
{
public:
    enum Type{
        TYPE_UNDEFINED,
        TYPE_NUMBER,
        TYPE_OPERATOR_ADD,
        TYPE_OPERATOR_SUB,
        TYPE_OPERATOR_MUL,
        TYPE_OPERATOR_DIV,
        TYPE_PAREN_OPEN,
        TYPE_PAREN_CLOSE,
        TYPE_KEYWORD_VAR,
        TYPE_NAME,
        TYPE_ASSIGNMENT,
        TYPE_END
    };
    Token( string s = "", Type type = TYPE_UNDEFINED)
        :m_type(type),m_string(s){}
    virtual ~Token(){}
    Type type() const { return m_type; }
    string getString() const { return m_string; }
private:
    Type m_type;
    string m_string;
};

#endif // TOKEN_H
