#include "evaluator.h"
#include "treeiterator.h"

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

    int value = 0;
    if( node == 0 ){
        m_status = EVALUATION_ERROR_NOTHING_TO_EVALUATE;
        m_errorMessage = "Nothing to evaluate.";
        return 0;
    }
    try{
        TreeIterator iterator(node);
        while( ! iterator.isDone() ){
            SyntaxNode *syntaxNode = dynamic_cast<SyntaxNode *>(iterator.current());
            syntaxNode->accept( this );
            iterator.next();
        }
        value = popValue();
    }
    catch(EvaluationException ex){
        m_status = ex.status();
        m_errorMessage = ex.message();
    }
    return value;
}

void Evaluator::visit( SyntaxNodeNumber *node )
{
    m_valueStack.push( node->value() );
}

void Evaluator::evaluateBinaryOperand( SyntaxNodeBinary *node, int &value1, int &value2 )
{
    if( (node->operand1() == 0) || (node->operand2() == 0) ){
        throw EvaluationException(EVALUATION_ERROR_INCOMPLETE_SYNTAX, "Incomplete syntax !");
    }
    value2 = popValue();
    value1 = popValue();
}

void Evaluator::visit( SyntaxNodeAdd *node )
{
    int operand1 = 0, operand2 = 0;
    evaluateBinaryOperand( node, operand1, operand2 );
    m_valueStack.push( operand1 + operand2 );
}

void Evaluator::visit( SyntaxNodeSub *node )
{
    int operand1 = 0, operand2 = 0;
    evaluateBinaryOperand( node, operand1, operand2 );
    m_valueStack.push( operand1 - operand2 );
}

void Evaluator::visit( SyntaxNodeMul *node )
{
    int operand1 = 0, operand2 = 0;
    evaluateBinaryOperand( node, operand1, operand2 );
    m_valueStack.push( operand1 * operand2 );
}

void Evaluator::visit( SyntaxNodeDiv *node )
{
    int operand1 = 0, operand2 = 0;
    evaluateBinaryOperand( node, operand1, operand2 );
    if( operand2 == 0 ){
        throw EvaluationException(
                    EVALUATION_ERROR_DIVIDED_BY_ZERO,
                    "Divided by zero.");
    }
    m_valueStack.push( operand1 / operand2 );
}

void Evaluator::visit( SyntaxNodePlus *node )
{
    if( node->operand() == 0 ){
        throw EvaluationException(
                    EVALUATION_ERROR_INCOMPLETE_SYNTAX,
                    "Incomplete syntax !");
    }
}

void Evaluator::visit( SyntaxNodeMinus *node )
{
    if( node->operand() == 0 ){
        throw EvaluationException(
                    EVALUATION_ERROR_INCOMPLETE_SYNTAX,
                    "Incomplete syntax !");
    }
    m_valueStack.push( - popValue() );
}

void Evaluator::visit( SyntaxNodeVarRef *node )
{
    if( m_varMap.find(node->name()) == m_varMap.end() ){
        throw EvaluationException(
                    EVALUATION_ERROR_UNDEFINED_VARIABLE,
                    "Variable '" + node->name() + "' is not defined.");
    }
    m_valueStack.push(m_varMap[node->name()]);
}

void Evaluator::visit( SyntaxNodeVarDecl *node )
{
    //m_varName = node->name();
}

void Evaluator::visit( SyntaxNodeAssign *node )
{
    if( (node->var() == 0) || (node->value() == 0) ){
        throw EvaluationException(
                    EVALUATION_ERROR_INCOMPLETE_SYNTAX,
                    "Incomplete syntax !");
    }
    m_varMap[node->var()->name()] = m_valueStack.top();
}

void Evaluator::setError( EvaluationStatus status, string message )
{
    m_status = status;
    m_errorMessage = message;
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
