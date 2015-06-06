#ifndef NODE_H
#define NODE_H

#include "nodevisitor.h"
#include "tree.h"

#include <string>
using namespace std;

class SyntaxNode : public TreeNode
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
        TYPE_VAR_DECL,
        TYPE_VAR_REF,
        TYPE_ASSIGN,
    };

    SyntaxNode( Type type = TYPE_UNDEFINED );
    virtual ~SyntaxNode();
    virtual void accept( SyntaxNodeVisitor *visitor ) = 0;
    Type type() { return m_type; }
private:
    Type m_type;
};

class SyntaxNodeNumber : public  SyntaxNode
{
public:
    SyntaxNodeNumber( int value );
    ~SyntaxNodeNumber();
    void accept( SyntaxNodeVisitor *visitor );
    int value() { return m_value; }
private:
    int m_value;
};

class SyntaxNodeBinary : public SyntaxNode
{
public:
    SyntaxNodeBinary( Type type, SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeBinary();
    SyntaxNode *operand1() { return m_operand1; }
    SyntaxNode *operand2() { return m_operand2; }
private:
     SyntaxNode *m_operand1;
     SyntaxNode *m_operand2;
};

class SyntaxNodeAdd : public SyntaxNodeBinary
{
public:
    SyntaxNodeAdd( SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeAdd();
    void accept( SyntaxNodeVisitor *visitor );
};

class SyntaxNodeSub : public SyntaxNodeBinary
{
public:
    SyntaxNodeSub( SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeSub();
    void accept( SyntaxNodeVisitor *visitor );
};

class SyntaxNodeMul : public SyntaxNodeBinary
{
public:
    SyntaxNodeMul( SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeMul();
    void accept( SyntaxNodeVisitor *visitor );
};

class SyntaxNodeDiv : public SyntaxNodeBinary
{
public:
    SyntaxNodeDiv( SyntaxNode *operand1, SyntaxNode *operand2 );
    ~SyntaxNodeDiv();
    void accept( SyntaxNodeVisitor *visitor );
};

class SyntaxNodeUnary : public SyntaxNode
{
public:
    SyntaxNodeUnary( SyntaxNode::Type type, SyntaxNode *operand );
    ~SyntaxNodeUnary();
    SyntaxNode *operand() { return m_operand; }
private:
    SyntaxNode *m_operand;
};

class SyntaxNodePlus : public SyntaxNodeUnary
{
public:
    SyntaxNodePlus( SyntaxNode *operand );
    ~SyntaxNodePlus();
    void accept( SyntaxNodeVisitor *visitor );
};

class SyntaxNodeMinus : public SyntaxNodeUnary
{
public:
    SyntaxNodeMinus( SyntaxNode *operand );
    ~SyntaxNodeMinus();
    void accept( SyntaxNodeVisitor *visitor );
};

class SyntaxNodeVarDecl : public SyntaxNode
{
public:
    SyntaxNodeVarDecl( string name );
    ~SyntaxNodeVarDecl();
    void accept( SyntaxNodeVisitor *visitor );
    string name() { return m_name; }
private:
    string m_name;
};

class SyntaxNodeAssign : public SyntaxNode
{
public:
    SyntaxNodeAssign( SyntaxNodeVarDecl *var, SyntaxNode *value );
    ~SyntaxNodeAssign();
    void accept( SyntaxNodeVisitor *visitor );
    SyntaxNodeVarDecl *var() { return m_var; }
    SyntaxNode *value() { return m_value; }
private:
    SyntaxNodeVarDecl *m_var;
    SyntaxNode *m_value;
};

class SyntaxNodeVarRef : public SyntaxNode
{
public:
    SyntaxNodeVarRef( string name );
    ~SyntaxNodeVarRef();
    void accept( SyntaxNodeVisitor *visitor );
    string name() { return m_name; }
private:
    string m_name;
};

#endif // NODE_H
