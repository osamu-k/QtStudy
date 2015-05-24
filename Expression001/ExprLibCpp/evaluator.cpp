#include "evaluator.h"

Evaluator::Evaluator()
    : m_status(EVALUATION_OK)
{
}

Evaluator::~Evaluator()
{
}

int Evaluator::evaluate( Node *node ){
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

void Evaluator::visit( NodeInteger *node )
{
    if( m_status != EVALUATION_OK )
        return;
    m_valueStack.push( node->value() );
}

void Evaluator::visit( NodeAdd *node )
{
    if( m_status != EVALUATION_OK )
        return;

    int operand2 = 0;
    if( node->operand2() ){
        operand2 = popValue();
    }
    int operand1 = 0;
    if( node->operand1() ){
        operand1 = popValue();
    }
    m_valueStack.push( operand1 + operand2 );
}

void Evaluator::visit( NodeSub *node )
{
    if( m_status != EVALUATION_OK )
        return;

    int operand2 = 0;
    if( node->operand2() ){
        operand2 = popValue();
    }
    int operand1 = 0;
    if( node->operand1() ){
        operand1 = popValue();
    }
    m_valueStack.push( operand1 - operand2 );
}

void Evaluator::visit( NodeMul *node )
{
    if( m_status != EVALUATION_OK )
        return;

    int operand2 = 1;
    if( node->operand2() ){
        operand2 = popValue();
    }
    int operand1 = 1;
    if( node->operand1() ){
        operand1 = popValue();
    }
    m_valueStack.push( operand1 * operand2 );
}

void Evaluator::visit( NodeDiv *node )
{
    if( m_status != EVALUATION_OK )
        return;

    int operand2 = 1;
    if( node->operand2() ){
        operand2 = popValue();
    }
    int operand1 = 1;
    if( node->operand1() ){
        operand1 = popValue();
    }
    if( operand2 == 0 ){
        setError(EVALUATION_ERROR_DIVIDED_BY_ZERO, "Divided by zero.");
        return;
    }
    m_valueStack.push( operand1 / operand2 );
}

void Evaluator::visit( NodePlus *node )
{
    if( m_status != EVALUATION_OK )
        return;

    int operand = 0;
    if( node->operand() ){
        operand = popValue();
    }
    m_valueStack.push( operand );
}

void Evaluator::visit( NodeMinus *node )
{
    if( m_status != EVALUATION_OK )
        return;

    int operand = 0;
    if( node->operand() ){
        operand = popValue();
    }
    m_valueStack.push( - operand );
}

void Evaluator::visit( NodeVarDecl *node )
{
    if( m_status != EVALUATION_OK )
        return;

    m_varName = node->name();
}

void Evaluator::visit( NodeVarRef *node )
{
    if( m_status != EVALUATION_OK )
        return;

    if( m_varMap.find(node->name()) == m_varMap.end() ){
        setError(EVALUATION_ERROR_UNDEFINED_VARIABLE, "Variable '" + node->name() + "' is not defined.");
    }
    m_valueStack.push(m_varMap[node->name()]);
}

void Evaluator::visit( NodeAssign *node )
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
