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
        TYPE_PLUS,
        TYPE_MINUS,
//        TYPE_VAR_DECL,
//        TYPE_VAR_REF,
//        TYPE_ASSIGN,
    };

    SyntaxNode( Type type = TYPE_UNDEFINED );
    virtual ~SyntaxNode();
    virtual int evaluate() = 0;
    Type type() { return m_type; }
private:
    Type m_type;
};

class SyntaxNodeNumber : public  SyntaxNode
{
public:
    SyntaxNodeNumber( int value );
    ~SyntaxNodeNumber();
    int evaluate();
    int value() { return m_value; }
private:
    int m_value;
};

class SyntaxNodeBinary : public SyntaxNode
{
public:
    SyntaxNodeBinary( Type type, SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeBinary();
    int evaluate();
    SyntaxNode *operand1() { return m_operand1; }
    SyntaxNode *operand2() { return m_operand2; }
protected:
    virtual int calculate(int x, int y) = 0;
private:
     SyntaxNode *m_operand1;
     SyntaxNode *m_operand2;
};

class SyntaxNodeAdd : public SyntaxNodeBinary
{
public:
    SyntaxNodeAdd( SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeAdd();
protected:
    int calculate(int x, int y);
};

class SyntaxNodeSub : public SyntaxNodeBinary
{
public:
    SyntaxNodeSub( SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeSub();
protected:
    int calculate(int x, int y);
};

class SyntaxNodeMul : public SyntaxNodeBinary
{
public:
    SyntaxNodeMul( SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeMul();
protected:
    int calculate(int x, int y);
};

class SyntaxNodeDiv : public SyntaxNodeBinary
{
public:
    SyntaxNodeDiv( SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeDiv();
protected:
    int calculate(int x, int y);
};

class SyntaxNodeUnary : public SyntaxNode
{
public:
    SyntaxNodeUnary( SyntaxNode::Type type, SyntaxNode *operand );
    ~SyntaxNodeUnary();
    int evaluate();
    SyntaxNode *operand() { return m_operand; }
protected:
    virtual int calculate(int x) = 0;
private:
    SyntaxNode *m_operand;
};

class SyntaxNodePlus : public SyntaxNodeUnary
{
public:
    SyntaxNodePlus( SyntaxNode *operand );
    ~SyntaxNodePlus();
protected:
    int calculate(int x);
};

class SyntaxNodeMinus : public SyntaxNodeUnary
{
public:
    SyntaxNodeMinus( SyntaxNode *operand );
    ~SyntaxNodeMinus();
protected:
    int calculate(int x);
};

//class SyntaxNodeVarDecl : public SyntaxNode
//{
//public:
//    SyntaxNodeVarDecl( string name );
//    ~SyntaxNodeVarDecl();
//    int evaluate();
//    string name() { return m_name; }
//private:
//    string m_name;
//};

//class SyntaxNodeVarRef : public SyntaxNode
//{
//public:
//    SyntaxNodeVarRef( string name );
//    ~SyntaxNodeVarRef();
//    int evaluate();
//    string name() { return m_name; }
//private:
//    string m_name;
//};

//class SyntaxNodeAssign : public SyntaxNode
//{
//public:
//    SyntaxNodeAssign( SyntaxNodeVarDecl *var, SyntaxNode *value );
//    ~SyntaxNodeAssign();
//    int evaluate();
//    SyntaxNodeVarDecl *var() { return m_var; }
//    SyntaxNode *value() { return m_value; }
//private:
//    SyntaxNodeVarDecl *m_var;
//    SyntaxNode *m_value;
//};

class DividedByZeroException
{
};

class IncompleteSyntaxException
{
};

#endif // NODE_H
