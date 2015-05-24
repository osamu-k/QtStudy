#ifndef NODE_H
#define NODE_H

#include "nodevisitor.h"

#include <string>
using namespace std;

class Node
{
public:
    enum Type {
        TYPE_UNDEFINED,
        TYPE_INTEGER,
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

    Node( Type type = TYPE_UNDEFINED );
    virtual ~Node();
    Type type();
    virtual void acceptVisitor( NodeVisitor *visitor ) = 0;
private:
    Type m_type;
};

class NodeInteger : public  Node
{
public:
    NodeInteger( int value );
    ~NodeInteger();
    int value();
    void acceptVisitor( NodeVisitor *visitor );
private:
    int m_value;
};

class NodeInfix : public Node
{
public:
    NodeInfix( Type type, Node *operand1, Node *operand2 );
    ~NodeInfix();
    Node *operand1();
    Node *operand2();
    void acceptVisitor( NodeVisitor *visitor );
private:
     Node *m_operand1;
     Node *m_operand2;
};

class NodeAdd : public NodeInfix
{
public:
    NodeAdd( Node *operand1, Node *operand2 );
    ~NodeAdd();
    void acceptVisitor( NodeVisitor *visitor );
};

class NodeSub : public NodeInfix
{
public:
    NodeSub( Node *operand1, Node *operand2 );
    ~NodeSub();
    void acceptVisitor( NodeVisitor *visitor );
};

class NodeMul : public NodeInfix
{
public:
    NodeMul( Node *operand1, Node *operand2 );
    ~NodeMul();
    void acceptVisitor( NodeVisitor *visitor );
};

class NodeDiv : public NodeInfix
{
public:
    NodeDiv( Node *operand1, Node *operand2 );
    ~NodeDiv();
    void acceptVisitor( NodeVisitor *visitor );
};

class NodeVarDecl : public Node
{
public:
    NodeVarDecl( string name );
    ~NodeVarDecl();
    string name();
    void acceptVisitor( NodeVisitor *visitor );
private:
    string m_name;
};

class NodeVarRef : public Node
{
public:
    NodeVarRef( string name );
    ~NodeVarRef();
    string name();
    void acceptVisitor( NodeVisitor *visitor );
private:
    string m_name;
};

class NodeAssign : public Node
{
public:
    NodeAssign( NodeVarDecl *var, Node *value );
    ~NodeAssign();
    NodeVarDecl *var();
    Node *value();
    void acceptVisitor( NodeVisitor *visitor );
private:
    NodeVarDecl *m_var;
    Node *m_value;
};

class NodePrefix : public Node
{
public:
    NodePrefix( Node::Type type, Node *operand );
    ~NodePrefix();
    Node *operand();
    void acceptVisitor( NodeVisitor *visitor );
private:
    Node *m_operand;
};

class NodePlus : public NodePrefix
{
public:
    NodePlus( Node *operand );
    ~NodePlus();
    void acceptVisitor( NodeVisitor *visitor );
};

class NodeMinus : public NodePrefix
{
public:
    NodeMinus( Node *operand );
    ~NodeMinus();
    void acceptVisitor( NodeVisitor *visitor );
};

#endif // NODE_H
