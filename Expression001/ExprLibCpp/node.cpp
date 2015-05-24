#include "node.h"

Node::Node( Type type )
    : m_type(type)
{
}

Node::~Node()
{
}

Node::Type Node::type()
{
    return m_type;
}

NodeInteger::NodeInteger( int value )
    : Node(Node::TYPE_INTEGER),m_value(value)
{
}

NodeInteger::~NodeInteger()
{
}

int NodeInteger::value()
{
    return m_value;
}

void NodeInteger::acceptVisitor( NodeVisitor *visitor )
{
    visitor->visit( this );
}

NodeInfix::NodeInfix( Type type, Node *operand1, Node *operand2 )
    :Node(type), m_operand1(operand1), m_operand2(operand2)
{
}

NodeInfix::~NodeInfix()
{
    if( m_operand1 )
        delete m_operand1;
    if( m_operand2 )
        delete m_operand2;
}

Node *NodeInfix::operand1()
{
    return m_operand1;
}

Node *NodeInfix::operand2()
{
    return m_operand2;
}

void NodeInfix::acceptVisitor( NodeVisitor *visitor )
{
    if( operand1() )
        operand1()->acceptVisitor(visitor);
    if( operand2() )
        operand2()->acceptVisitor(visitor);
}

NodeAdd::NodeAdd( Node *operand1, Node *operand2 )
    : NodeInfix(Node::TYPE_ADD, operand1, operand2)
{
}

NodeAdd::~NodeAdd()
{
}

void NodeAdd::acceptVisitor( NodeVisitor *visitor )
{
    NodeInfix::acceptVisitor( visitor );
    visitor->visit( this );
}

NodeSub::NodeSub( Node *operand1, Node *operand2 )
    : NodeInfix(Node::TYPE_SUB, operand1, operand2)
{
}

NodeSub::~NodeSub()
{
}

void NodeSub::acceptVisitor( NodeVisitor *visitor )
{
    NodeInfix::acceptVisitor( visitor );
    visitor->visit( this );
}

NodeMul::NodeMul( Node *operand1, Node *operand2 )
    : NodeInfix(Node::TYPE_MUL, operand1, operand2)
{
}

NodeMul::~NodeMul()
{
}

void NodeMul::acceptVisitor( NodeVisitor *visitor )
{
    NodeInfix::acceptVisitor( visitor );
    visitor->visit( this );
}

NodeDiv::NodeDiv( Node *operand1, Node *operand2 )
    : NodeInfix(Node::TYPE_DIV, operand1, operand2)
{}

NodeDiv::~NodeDiv()
{}

void NodeDiv::acceptVisitor( NodeVisitor *visitor )
{
    NodeInfix::acceptVisitor( visitor );
    visitor->visit( this );
}

NodeVarDecl::NodeVarDecl( string name )
    :Node(Node::TYPE_VAR_DECL), m_name(name)
{
}

NodeVarDecl::~NodeVarDecl()
{
}

string NodeVarDecl::name()
{
    return m_name;
}

void NodeVarDecl::acceptVisitor( NodeVisitor *visitor )
{
    visitor->visit( this );
}

NodeVarRef::NodeVarRef( string name )
    :Node(Node::TYPE_VAR_REF), m_name(name)
{
}

NodeVarRef::~NodeVarRef()
{
}

string NodeVarRef::name()
{
    return m_name;
}

void NodeVarRef::acceptVisitor( NodeVisitor *visitor )
{
    visitor->visit( this );
}

NodeAssign::NodeAssign( NodeVarDecl *var, Node *value )
    : Node(Node::TYPE_ASSIGN), m_var(var), m_value(value)
{
}

NodeAssign::~NodeAssign()
{
    if( m_var ) delete m_var;
    if( m_value ) delete m_value;
}

NodeVarDecl *NodeAssign::var()
{
    return m_var;
}

Node *NodeAssign::value()
{
    return m_value;
}

void NodeAssign::acceptVisitor( NodeVisitor *visitor )
{
    if( var() )
        var()->acceptVisitor(visitor);
    if( value() )
        value()->acceptVisitor(visitor);
    visitor->visit( this );
}

NodePrefix::NodePrefix( Node::Type type, Node *operand )
    : Node(type), m_operand(operand)
{
}

NodePrefix::~NodePrefix()
{
    if( m_operand ) delete m_operand;
}

Node *NodePrefix::operand()
{ return m_operand; }

void NodePrefix::acceptVisitor( NodeVisitor *visitor )
{
    if( operand() )
        operand()->acceptVisitor( visitor );
}

NodePlus::NodePlus( Node *operand )
    : NodePrefix(Node::TYPE_PLUS, operand)
{
}

NodePlus::~NodePlus()
{
}

void NodePlus::acceptVisitor( NodeVisitor *visitor )
{
    NodePrefix::acceptVisitor( visitor );
    visitor->visit( this );
}

NodeMinus::NodeMinus( Node *operand )
    : NodePrefix(Node::TYPE_MINUS, operand)
{
}

NodeMinus::~NodeMinus()
{
}

void NodeMinus::acceptVisitor( NodeVisitor *visitor )
{
    NodePrefix::acceptVisitor( visitor );
    visitor->visit( this );
}
