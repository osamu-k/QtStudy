#include "evaluator.h"

Evaluator::Evaluator()
    : m_status(EVALUATION_OK)
{
}

Evaluator::~Evaluator()
{
}

int Evaluator::evaluate( SyntaxNode *node ){
    int value = 0;
    if( node == 0 ){
        setError(EVALUATION_ERROR_INCOMPLETE_SYNTAX,"No expression to evaluate.");
        return 0;
    }
    try{
        value = node->evaluate();
    }
    catch(DividedByZeroException){
        setError(EVALUATION_ERROR_DIVIDED_BY_ZERO, "Divided by zero.");
        value = 0;
    }
    catch(IncompleteSyntaxException){
        setError(EVALUATION_ERROR_INCOMPLETE_SYNTAX,"Incomplete expression.");
        value = 0;
    }
    return value;
}

void Evaluator::setError( EvaluationStatus status, string message )
{
    m_status = status;
    m_errorMessage = message;
}
