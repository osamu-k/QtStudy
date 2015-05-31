#include "node.h"

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

void SyntaxNodeNumber::acceptVisitor( NodeVisitor *visitor )
{
    visitor->visit( this );
}

SyntaxNodeBinary::SyntaxNodeBinary( Type type, SyntaxNode *operand1, SyntaxNode *operand2 )
    :SyntaxNode(type), m_operand1(operand1), m_operand2(operand2)
{
}

SyntaxNodeBinary::~SyntaxNodeBinary()
{
    if( m_operand1 )
        delete m_operand1;
    if( m_operand2 )
        delete m_operand2;
}

void SyntaxNodeBinary::acceptVisitor( NodeVisitor *visitor )
{
    if( operand1() )
        operand1()->acceptVisitor(visitor);
    if( operand2() )
        operand2()->acceptVisitor(visitor);
}

SyntaxNodeAdd::SyntaxNodeAdd( SyntaxNode *operand1, SyntaxNode *operand2 )
    : SyntaxNodeBinary(SyntaxNode::TYPE_ADD, operand1, operand2)
{
}

SyntaxNodeAdd::~SyntaxNodeAdd()
{
}

void SyntaxNodeAdd::acceptVisitor( NodeVisitor *visitor )
{
    SyntaxNodeBinary::acceptVisitor( visitor );
    visitor->visit( this );
}

SyntaxNodeSub::SyntaxNodeSub( SyntaxNode *operand1, SyntaxNode *operand2 )
    : SyntaxNodeBinary(SyntaxNode::TYPE_SUB, operand1, operand2)
{
}

SyntaxNodeSub::~SyntaxNodeSub()
{
}

void SyntaxNodeSub::acceptVisitor( NodeVisitor *visitor )
{
    SyntaxNodeBinary::acceptVisitor( visitor );
    visitor->visit( this );
}

SyntaxNodeMul::SyntaxNodeMul( SyntaxNode *operand1, SyntaxNode *operand2 )
    : SyntaxNodeBinary(SyntaxNode::TYPE_MUL, operand1, operand2)
{
}

SyntaxNodeMul::~SyntaxNodeMul()
{
}

void SyntaxNodeMul::acceptVisitor( NodeVisitor *visitor )
{
    SyntaxNodeBinary::acceptVisitor( visitor );
    visitor->visit( this );
}

SyntaxNodeDiv::SyntaxNodeDiv( SyntaxNode *operand1, SyntaxNode *operand2 )
    : SyntaxNodeBinary(SyntaxNode::TYPE_DIV, operand1, operand2)
{}

SyntaxNodeDiv::~SyntaxNodeDiv()
{}

void SyntaxNodeDiv::acceptVisitor( NodeVisitor *visitor )
{
    SyntaxNodeBinary::acceptVisitor( visitor );
    visitor->visit( this );
}

SyntaxNodeUnary::SyntaxNodeUnary( SyntaxNode::Type type, SyntaxNode *operand )
    : SyntaxNode(type), m_operand(operand)
{
}

SyntaxNodeUnary::~SyntaxNodeUnary()
{
    if( m_operand ) delete m_operand;
}

void SyntaxNodeUnary::acceptVisitor( NodeVisitor *visitor )
{
    if( operand() )
        operand()->acceptVisitor( visitor );
}

SyntaxNodePlus::SyntaxNodePlus( SyntaxNode *operand )
    : SyntaxNodeUnary(SyntaxNode::TYPE_PLUS, operand)
{
}

SyntaxNodePlus::~SyntaxNodePlus()
{
}

void SyntaxNodePlus::acceptVisitor( NodeVisitor *visitor )
{
    SyntaxNodeUnary::acceptVisitor( visitor );
    visitor->visit( this );
}

SyntaxNodeMinus::SyntaxNodeMinus( SyntaxNode *operand )
    : SyntaxNodeUnary(SyntaxNode::TYPE_MINUS, operand)
{
}

SyntaxNodeMinus::~SyntaxNodeMinus()
{
}

void SyntaxNodeMinus::acceptVisitor( NodeVisitor *visitor )
{
    SyntaxNodeUnary::acceptVisitor( visitor );
    visitor->visit( this );
}

SyntaxNodeVarDecl::SyntaxNodeVarDecl( string name )
    :SyntaxNode(SyntaxNode::TYPE_VAR_DECL), m_name(name)
{
}

SyntaxNodeVarDecl::~SyntaxNodeVarDecl()
{
}

void SyntaxNodeVarDecl::acceptVisitor( NodeVisitor *visitor )
{
    visitor->visit( this );
}

SyntaxNodeVarRef::SyntaxNodeVarRef( string name )
    :SyntaxNode(SyntaxNode::TYPE_VAR_REF), m_name(name)
{
}

SyntaxNodeVarRef::~SyntaxNodeVarRef()
{
}

void SyntaxNodeVarRef::acceptVisitor( NodeVisitor *visitor )
{
    visitor->visit( this );
}

SyntaxNodeAssign::SyntaxNodeAssign( SyntaxNodeVarDecl *var, SyntaxNode *value )
    : SyntaxNode(SyntaxNode::TYPE_ASSIGN), m_var(var), m_value(value)
{
}

SyntaxNodeAssign::~SyntaxNodeAssign()
{
    if( m_var ) delete m_var;
    if( m_value ) delete m_value;
}

void SyntaxNodeAssign::acceptVisitor( NodeVisitor *visitor )
{
    if( var() )
        var()->acceptVisitor(visitor);
    if( value() )
        value()->acceptVisitor(visitor);
    visitor->visit( this );
}
