#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "node.h"
#include "nodevisitor.h"

#include <map>
#include <stack>
using namespace std;

class Evaluator : public NodeVisitor
{
public:
    enum EvaluationStatus{
        EVALUATION_OK,
        EVALUATION_ERROR_DIVIDED_BY_ZERO,
        EVALUATION_ERROR_INCOMPLETE_SYNTAX,
        EVALUATION_ERROR_UNDEFINED_VARIABLE
    };

    Evaluator();
    ~Evaluator();
    int evaluate( Node *node );
    void visit( NodeInteger *node );
    void visit( NodeAdd *node );
    void visit( NodeSub *node );
    void visit( NodeMul *node );
    void visit( NodeDiv *node );
    void visit( NodePlus *node );
    void visit( NodeMinus *node );
    void visit( NodeVarDecl *node );
    void visit( NodeVarRef *node );
    void visit( NodeAssign *node );
    void setError( EvaluationStatus status, string message );
    bool isError();
    EvaluationStatus status();
    string errorMessage();
private:
    void pushValue( int value );
    int popValue();
    stack<int> m_valueStack;
    string m_varName;
    map<string,int> m_varMap;
    EvaluationStatus m_status;
    string m_errorMessage;
};

#endif // EVALUATOR_H
