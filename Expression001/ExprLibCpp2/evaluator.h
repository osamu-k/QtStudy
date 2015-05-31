#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "syntaxnode.h"
#include "nodevisitor.h"

#include <map>
#include <stack>
using namespace std;

class Evaluator
{
public:
    enum EvaluationStatus{
        EVALUATION_OK,
        EVALUATION_ERROR_DIVIDED_BY_ZERO,
        EVALUATION_ERROR_INCOMPLETE_SYNTAX
    };

    Evaluator();
    ~Evaluator();
    int evaluate( SyntaxNode *node );
    void setError( EvaluationStatus status, string message );
    bool isError() { return m_status != EVALUATION_OK; }
    EvaluationStatus status() const { return m_status; }
    string errorMessage() const { return m_errorMessage; }
private:
    EvaluationStatus m_status;
    string m_errorMessage;
};

#endif // EVALUATOR_H
