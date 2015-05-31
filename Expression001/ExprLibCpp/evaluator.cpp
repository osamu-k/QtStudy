#include "evaluator.h"

Evaluator::Evaluator()
    : m_status(EVALUATION_OK)
{
}

Evaluator::~Evaluator()
{
}

int Evaluator::evaluate( SyntaxNode *node ){
    m_status = EVALUATION_OK;
    m_errorMessage = "";

    if( node == 0 ){
        setError(EVALUATION_ERROR_INCOMPLETE_SYNTAX,"No expression to evaluate.");
        return 0;
    }
    node->acceptVisitor( this );
    int value = 0;
    if( m_status == EVALUATION_OK ){
        value = popValue();
    }
    return value;
}

void Evaluator::visit( SyntaxNodeNumber *node )
{
    if( m_status != EVALUATION_OK )
        return;
    m_valueStack.push( node->value() );
}

bool Evaluator::checkBinaryStatus( SyntaxNodeBinary *node )
{
    if( m_status != EVALUATION_OK )
        return false;
    if( (node->operand1() == 0) || (node->operand2() == 0) ){
        setError(EVALUATION_ERROR_INCOMPLETE_SYNTAX, "Incomplete syntax !");
        return false;
    }
    return true;
}

void Evaluator::visit( SyntaxNodeAdd *node )
{
    if( checkBinaryStatus(node) ) {
        int operand2 = popValue();
        int operand1 = popValue();
        m_valueStack.push( operand1 + operand2 );
    }
}

void Evaluator::visit( SyntaxNodeSub *node )
{
   if( checkBinaryStatus(node) ) {
        int operand2 = popValue();
        int operand1 = popValue();
        m_valueStack.push( operand1 - operand2 );
    }
}

void Evaluator::visit( SyntaxNodeMul *node )
{
    if( checkBinaryStatus(node) ) {
         int operand2 = popValue();
         int operand1 = popValue();
         m_valueStack.push( operand1 * operand2 );
     }
}

void Evaluator::visit( SyntaxNodeDiv *node )
{
    if( checkBinaryStatus(node) ) {
         int operand2 = popValue();
         if( operand2 == 0 ){
             setError(EVALUATION_ERROR_DIVIDED_BY_ZERO, "Divided by zero.");
             return;
         }
         int operand1 = popValue();
         m_valueStack.push( operand1 / operand2 );
     }
}

bool Evaluator::checkUnaryStatus( SyntaxNodeUnary *node )
{
    if( m_status != EVALUATION_OK )
        return false;
    if( node->operand() == 0 ){
        setError(EVALUATION_ERROR_INCOMPLETE_SYNTAX, "Incomplete syntax !");
        return false;
    }
    return true;
}

void Evaluator::visit( SyntaxNodePlus *node )
{
    if( checkUnaryStatus(node) ){
        // Nothing to do.
        // m_valueStack.push( popValue() );
    }
}

void Evaluator::visit( SyntaxNodeMinus *node )
{
    if( checkUnaryStatus(node) ){
        m_valueStack.push( - popValue() );
    }
}

void Evaluator::visit( SyntaxNodeVarDecl *node )
{
    if( m_status != EVALUATION_OK )
        return;

    m_varName = node->name();
}

void Evaluator::visit( SyntaxNodeVarRef *node )
{
    if( m_status != EVALUATION_OK )
        return;

    if( m_varMap.find(node->name()) == m_varMap.end() ){
        setError(EVALUATION_ERROR_UNDEFINED_VARIABLE, "Variable '" + node->name() + "' is not defined.");
    }
    m_valueStack.push(m_varMap[node->name()]);
}

void Evaluator::visit( SyntaxNodeAssign *node )
{
    if( m_status != EVALUATION_OK )
        return;

    int value = 0;
    if( node->value() ){
        value = m_valueStack.top();
    }
    m_varMap[m_varName] = value;
}

void Evaluator::setError( EvaluationStatus status, string message )
{
    m_status = status;
    m_errorMessage = message;
}

bool Evaluator::isError()
{
    return m_status != EVALUATION_OK;
}

Evaluator::EvaluationStatus Evaluator::status()
{
    return m_status;
}

string Evaluator::errorMessage()
{
    return m_errorMessage;
}

void Evaluator::pushValue( int value )
{
    m_valueStack.push( value );
}

int Evaluator::popValue()
{
    if( m_valueStack.empty() )
        return 0;
    int value = m_valueStack.top();
    m_valueStack.pop();
    return value;
}
