#ifndef TREEVIEWER_H
#define TREEVIEWER_H

#include <QWidget>
#include "node.h"
#include "nodevisitor.h"
#include "tree.h"

#include <stack>
using namespace std;

class TreeViewer : public QWidget, public NodeVisitor
{
    Q_OBJECT
public:
    explicit TreeViewer(QWidget *parent = 0);
    ~TreeViewer();

    void setNode( Node *tree );

    void visit( NodeInteger * );
    void visit( NodeVarDecl * );
    void visit( NodeAdd * );
    void visit( NodeSub * );
    void visit( NodeMul * );
    void visit( NodeDiv * );
    void visit( NodePlus * );
    void visit( NodeMinus * );
    void visit( NodeVarRef * );
    void visit( NodeAssign * );

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);

private:
    Tree *makeSimpleTree( QString string );
    Tree *makeBinaryTree( NodeInfix *node, QString string );
    Tree *makeUnaryTree( NodePrefix *node, QString string );
    void clearTreeStack();

    stack<Tree *> m_treeStack;
};

#endif // TREEVIEWER_H
