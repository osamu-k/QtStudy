#include "syntaxnode.h"

SyntaxNode::SyntaxNode( Type type )
    : m_type(type)
{
}

SyntaxNode::~SyntaxNode()
{
}

SyntaxNodeNumber::SyntaxNodeNumber( int value )
    : SyntaxNode(SyntaxNode::TYPE_NUMBER),m_value(value)
{
}

SyntaxNodeNumber::~SyntaxNodeNumber()
{
}

void SyntaxNodeNumber::accept( SyntaxNodeVisitor *visitor )
{
    visitor->visit(this);
}

SyntaxNodeBinary::SyntaxNodeBinary( Type type, SyntaxNode *operand1, SyntaxNode *operand2 )
    :SyntaxNode(type), m_operand1(operand1), m_operand2(operand2)
{
    m_children.push_back(operand1);
    m_children.push_back(operand2);
}

SyntaxNodeBinary::~SyntaxNodeBinary()
{
    if( m_operand1 )
        delete m_operand1;
    if( m_operand2 )
        delete m_operand2;
}

SyntaxNodeAdd::SyntaxNodeAdd( SyntaxNode *operand1, SyntaxNode *operand2 )
    : SyntaxNodeBinary(SyntaxNode::TYPE_ADD, operand1, operand2)
{
}

SyntaxNodeAdd::~SyntaxNodeAdd()
{
}

void SyntaxNodeAdd::accept( SyntaxNodeVisitor *visitor )
{
    visitor->visit(this);
}

SyntaxNodeSub::SyntaxNodeSub( SyntaxNode *operand1, SyntaxNode *operand2 )
    : SyntaxNodeBinary(SyntaxNode::TYPE_SUB, operand1, operand2)
{
}

SyntaxNodeSub::~SyntaxNodeSub()
{
}

void SyntaxNodeSub::accept( SyntaxNodeVisitor *visitor )
{
    visitor->visit(this);
}

SyntaxNodeMul::SyntaxNodeMul( SyntaxNode *operand1, SyntaxNode *operand2 )
    : SyntaxNodeBinary(SyntaxNode::TYPE_MUL, operand1, operand2)
{
}

SyntaxNodeMul::~SyntaxNodeMul()
{
}

void SyntaxNodeMul::accept( SyntaxNodeVisitor *visitor )
{
    visitor->visit(this);
}

SyntaxNodeDiv::SyntaxNodeDiv( SyntaxNode *operand1, SyntaxNode *operand2 )
    : SyntaxNodeBinary(SyntaxNode::TYPE_DIV, operand1, operand2)
{
}

SyntaxNodeDiv::~SyntaxNodeDiv()
{
}

void SyntaxNodeDiv::accept( SyntaxNodeVisitor *visitor )
{
    visitor->visit(this);
}

SyntaxNodeUnary::SyntaxNodeUnary( SyntaxNode::Type type, SyntaxNode *operand )
    : SyntaxNode(type), m_operand(operand)
{
    m_children.push_back(operand);
}

SyntaxNodeUnary::~SyntaxNodeUnary()
{
    if( m_operand )
        delete m_operand;
}

SyntaxNodePlus::SyntaxNodePlus( SyntaxNode *operand )
    : SyntaxNodeUnary(SyntaxNode::TYPE_PLUS, operand)
{
}

SyntaxNodePlus::~SyntaxNodePlus()
{
}

void SyntaxNodePlus::accept( SyntaxNodeVisitor *visitor )
{
    visitor->visit(this);
}

SyntaxNodeMinus::SyntaxNodeMinus( SyntaxNode *operand )
    : SyntaxNodeUnary(SyntaxNode::TYPE_MINUS, operand)
{
}

SyntaxNodeMinus::~SyntaxNodeMinus()
{
}

void SyntaxNodeMinus::accept( SyntaxNodeVisitor *visitor )
{
    visitor->visit(this);
}

SyntaxNodeVarDecl::SyntaxNodeVarDecl( string name )
    :SyntaxNode(SyntaxNode::TYPE_VAR_DECL), m_name(name)
{
}

SyntaxNodeVarDecl::~SyntaxNodeVarDecl()
{
}

void SyntaxNodeVarDecl::accept( SyntaxNodeVisitor *visitor )
{
    visitor->visit(this);
}

SyntaxNodeAssign::SyntaxNodeAssign( SyntaxNodeVarDecl *var, SyntaxNode *value )
    : SyntaxNode(SyntaxNode::TYPE_ASSIGN), m_var(var), m_value(value)
{
    m_children.push_back(var);
    m_children.push_back(value);
}

SyntaxNodeAssign::~SyntaxNodeAssign()
{
    if( m_var ) delete m_var;
    if( m_value ) delete m_value;
}

void SyntaxNodeAssign::accept( SyntaxNodeVisitor *visitor )
{
    visitor->visit(this);
}

SyntaxNodeVarRef::SyntaxNodeVarRef( string name )
    :SyntaxNode(SyntaxNode::TYPE_VAR_REF), m_name(name)
{
}

SyntaxNodeVarRef::~SyntaxNodeVarRef()
{
}

void SyntaxNodeVarRef::accept( SyntaxNodeVisitor *visitor )
{
    visitor->visit(this);
}
