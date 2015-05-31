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

int SyntaxNodeNumber::evaluate()
{
    return value();
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

int SyntaxNodeBinary::evaluate()
{
    if( (operand1() == 0) || (operand2() == 0) )
        throw IncompleteSyntaxException();

    int value1 = operand1()->evaluate();
    int value2 = operand2()->evaluate();
    return calculate(value1,value2);
}

SyntaxNodeAdd::SyntaxNodeAdd( SyntaxNode *operand1, SyntaxNode *operand2 )
    : SyntaxNodeBinary(SyntaxNode::TYPE_ADD, operand1, operand2)
{
}

SyntaxNodeAdd::~SyntaxNodeAdd()
{
}

int SyntaxNodeAdd::calculate(int x, int y)
{
    return x + y;
}

SyntaxNodeSub::SyntaxNodeSub( SyntaxNode *operand1, SyntaxNode *operand2 )
    : SyntaxNodeBinary(SyntaxNode::TYPE_SUB, operand1, operand2)
{
}

SyntaxNodeSub::~SyntaxNodeSub()
{
}

int SyntaxNodeSub::calculate(int x, int y)
{
    return x - y;
}

SyntaxNodeMul::SyntaxNodeMul( SyntaxNode *operand1, SyntaxNode *operand2 )
    : SyntaxNodeBinary(SyntaxNode::TYPE_MUL, operand1, operand2)
{
}

SyntaxNodeMul::~SyntaxNodeMul()
{
}

int SyntaxNodeMul::calculate(int x, int y)
{
    return x * y;
}

SyntaxNodeDiv::SyntaxNodeDiv( SyntaxNode *operand1, SyntaxNode *operand2 )
    : SyntaxNodeBinary(SyntaxNode::TYPE_DIV, operand1, operand2)
{
}

SyntaxNodeDiv::~SyntaxNodeDiv()
{
}

int SyntaxNodeDiv::calculate(int x, int y)
{
    if( y == 0 )
        throw DividedByZeroException();
    return x / y;
}

SyntaxNodeUnary::SyntaxNodeUnary( SyntaxNode::Type type, SyntaxNode *operand )
    : SyntaxNode(type), m_operand(operand)
{
}

SyntaxNodeUnary::~SyntaxNodeUnary()
{
    if( m_operand )
        delete m_operand;
}

int SyntaxNodeUnary::evaluate()
{
    if( operand() == 0 )
        throw IncompleteSyntaxException();

    int value = operand()->evaluate();
    return calculate(value);
}

SyntaxNodePlus::SyntaxNodePlus( SyntaxNode *operand )
    : SyntaxNodeUnary(SyntaxNode::TYPE_PLUS, operand)
{
}

SyntaxNodePlus::~SyntaxNodePlus()
{
}

int SyntaxNodePlus::calculate(int x)
{
    return x;
}

SyntaxNodeMinus::SyntaxNodeMinus( SyntaxNode *operand )
    : SyntaxNodeUnary(SyntaxNode::TYPE_MINUS, operand)
{
}

SyntaxNodeMinus::~SyntaxNodeMinus()
{
}

int SyntaxNodeMinus::calculate(int x)
{
    return - x;
}

//SyntaxNodeVarDecl::SyntaxNodeVarDecl( string name )
//    :SyntaxNode(SyntaxNode::TYPE_VAR_DECL), m_name(name)
//{
//}

//SyntaxNodeVarDecl::~SyntaxNodeVarDecl()
//{
//}

//SyntaxNodeVarRef::SyntaxNodeVarRef( string name )
//    :SyntaxNode(SyntaxNode::TYPE_VAR_REF), m_name(name)
//{
//}

//SyntaxNodeVarRef::~SyntaxNodeVarRef()
//{
//}

//SyntaxNodeAssign::SyntaxNodeAssign( SyntaxNodeVarDecl *var, SyntaxNode *value )
//    : SyntaxNode(SyntaxNode::TYPE_ASSIGN), m_var(var), m_value(value)
//{
//}

//SyntaxNodeAssign::~SyntaxNodeAssign()
//{
//    if( m_var ) delete m_var;
//    if( m_value ) delete m_value;
//}


//int SyntaxNodeAssign::evaluate()
//{
//    if( operand() == 0 )
//        throw new IncompleteSyntaxException;

//    int value = operand()->evaluate();
//    return calculate(value);
//}
