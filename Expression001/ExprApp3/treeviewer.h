#ifndef TREEVIEWER_H
#define TREEVIEWER_H

#include <QWidget>
#include "syntaxnode.h"
#include "nodevisitor.h"
#include "visualtree.h"

#include <stack>
using namespace std;

class TreeViewer : public QWidget, public SyntaxNodeVisitor
{
    Q_OBJECT
public:
    explicit TreeViewer(QWidget *parent = 0);
    ~TreeViewer();

    void setNode( SyntaxNode *tree );

    void visit( SyntaxNodeNumber * );
    void visit( SyntaxNodeVarDecl * );
    void visit( SyntaxNodeAdd * );
    void visit( SyntaxNodeSub * );
    void visit( SyntaxNodeMul * );
    void visit( SyntaxNodeDiv * );
    void visit( SyntaxNodePlus * );
    void visit( SyntaxNodeMinus * );
    void visit( SyntaxNodeVarRef * );
    void visit( SyntaxNodeAssign * );

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);

private:
    VisualTree *makeSimpleTree( QString string );
    VisualTree *makeBinaryTree( SyntaxNodeBinary *node, QString string );
    VisualTree *makeUnaryTree( SyntaxNodeUnary *node, QString string );
    void clearTreeStack();

    stack<VisualTree *> m_treeStack;
};

#endif // TREEVIEWER_H
