#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "syntaxnode.h"
#include "nodevisitor.h"

#include <map>
#include <stack>
using namespace std;

class Evaluator : public SyntaxNodeVisitor
{
public:
    enum EvaluationStatus{
        EVALUATION_OK,
        EVALUATION_ERROR_DIVIDED_BY_ZERO,
        EVALUATION_ERROR_INCOMPLETE_SYNTAX,
        EVALUATION_ERROR_UNDEFINED_VARIABLE,
        EVALUATION_ERROR_NOTHING_TO_EVALUATE
    };

    class EvaluationException
    {
    public:
        EvaluationException(EvaluationStatus status, string message)
            : m_status(status), m_message(message)
        {}
        ~EvaluationException()
        {}
        EvaluationStatus status() { return m_status; }
        string message() { return m_message; }
    private:
        EvaluationStatus m_status;
        string m_message;
    };

    Evaluator();
    ~Evaluator();
    int evaluate( SyntaxNode *node );
    void visit( SyntaxNodeNumber *node );
    void visit( SyntaxNodeAdd *node );
    void visit( SyntaxNodeSub *node );
    void visit( SyntaxNodeMul *node );
    void visit( SyntaxNodeDiv *node );
    void visit( SyntaxNodePlus *node );
    void visit( SyntaxNodeMinus *node );
    void visit( SyntaxNodeVarDecl *node );
    void visit( SyntaxNodeVarRef *node );
    void visit( SyntaxNodeAssign *node );
    void setError( EvaluationStatus status, string message );
    bool isError() { return m_status != EVALUATION_OK; }
    EvaluationStatus status() { return m_status; }
    string errorMessage() { return m_errorMessage; }
private:
    void evaluateBinaryOperand( SyntaxNodeBinary *node, int &value1, int &value2 );
    void pushValue( int value );
    int popValue();
    stack<int> m_valueStack;
    map<string,int> m_varMap;
    EvaluationStatus m_status;
    string m_errorMessage;
};

#endif // EVALUATOR_H
