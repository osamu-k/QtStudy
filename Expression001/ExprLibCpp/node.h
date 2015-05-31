#ifndef NODE_H
#define NODE_H

#include "nodevisitor.h"

#include <string>
using namespace std;

class SyntaxNode
{
public:
    enum Type {
        TYPE_UNDEFINED,
        TYPE_NUMBER,
        TYPE_ADD,
        TYPE_SUB,
        TYPE_MUL,
        TYPE_DIV,
        TYPE_VAR_DECL,
        TYPE_VAR_REF,
        TYPE_ASSIGN,
        TYPE_PLUS,
        TYPE_MINUS
    };

    SyntaxNode( Type type = TYPE_UNDEFINED );
    virtual ~SyntaxNode();
    Type type();
    virtual void acceptVisitor( NodeVisitor *visitor ) = 0;
private:
    Type m_type;
};

class SyntaxNodeNumber : public  SyntaxNode
{
public:
    SyntaxNodeNumber( int value );
    ~SyntaxNodeNumber();
    int value();
    void acceptVisitor( NodeVisitor *visitor );
private:
    int m_value;
};

class SyntaxNodeBinary : public SyntaxNode
{
public:
    SyntaxNodeBinary( Type type, SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeBinary();
    SyntaxNode *operand1();
    SyntaxNode *operand2();
    void acceptVisitor( NodeVisitor *visitor );
private:
     SyntaxNode *m_operand1;
     SyntaxNode *m_operand2;
};

class SyntaxNodeAdd : public SyntaxNodeBinary
{
public:
    SyntaxNodeAdd( SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeAdd();
    void acceptVisitor( NodeVisitor *visitor );
};

class SyntaxNodeSub : public SyntaxNodeBinary
{
public:
    SyntaxNodeSub( SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeSub();
    void acceptVisitor( NodeVisitor *visitor );
};

class SyntaxNodeMul : public SyntaxNodeBinary
{
public:
    SyntaxNodeMul( SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeMul();
    void acceptVisitor( NodeVisitor *visitor );
};

class SyntaxNodeDiv : public SyntaxNodeBinary
{
public:
    SyntaxNodeDiv( SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeDiv();
    void acceptVisitor( NodeVisitor *visitor );
};

class SyntaxNodeVarDecl : public SyntaxNode
{
public:
    SyntaxNodeVarDecl( string name );
    ~SyntaxNodeVarDecl();
    string name();
    void acceptVisitor( NodeVisitor *visitor );
private:
    string m_name;
};

class SyntaxNodeVarRef : public SyntaxNode
{
public:
    SyntaxNodeVarRef( string name );
    ~SyntaxNodeVarRef();
    string name();
    void acceptVisitor( NodeVisitor *visitor );
private:
    string m_name;
};

class SyntaxNodeAssign : public SyntaxNode
{
public:
    SyntaxNodeAssign( SyntaxNodeVarDecl *var, SyntaxNode *value );
    ~SyntaxNodeAssign();
    SyntaxNodeVarDecl *var();
    SyntaxNode *value();
    void acceptVisitor( NodeVisitor *visitor );
private:
    SyntaxNodeVarDecl *m_var;
    SyntaxNode *m_value;
};

class SyntaxNodeUnary : public SyntaxNode
{
public:
    SyntaxNodeUnary( SyntaxNode::Type type, SyntaxNode *operand );
    ~SyntaxNodeUnary();
    SyntaxNode *operand();
    void acceptVisitor( NodeVisitor *visitor );
private:
    SyntaxNode *m_operand;
};

class SyntaxNodePlus : public SyntaxNodeUnary
{
public:
    SyntaxNodePlus( SyntaxNode *operand );
    ~SyntaxNodePlus();
    void acceptVisitor( NodeVisitor *visitor );
};

class SyntaxNodeMinus : public SyntaxNodeUnary
{
public:
    SyntaxNodeMinus( SyntaxNode *operand );
    ~SyntaxNodeMinus();
    void acceptVisitor( NodeVisitor *visitor );
};

#endif // NODE_H
