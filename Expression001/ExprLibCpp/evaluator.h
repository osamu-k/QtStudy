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
    bool isError();
    EvaluationStatus status();
    string errorMessage();
private:
    bool checkBinaryStatus( SyntaxNodeBinary *node );
    bool checkUnaryStatus( SyntaxNodeUnary *node );
    void pushValue( int value );
    int popValue();
    stack<int> m_valueStack;
    string m_varName;
    map<string,int> m_varMap;
    EvaluationStatus m_status;
    string m_errorMessage;
};

#endif // EVALUATOR_H
