#include <QFont>
#include <QFontMetrics>

#include "treeviewer.h"
#include "visualtree.h"
#include "treeiterator.h"

TreeViewer::TreeViewer(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setPalette( Qt::white );
}

TreeViewer::~TreeViewer()
{
    clearTreeStack();
}

void TreeViewer::setNode( SyntaxNode *node )
{
    clearTreeStack();

    TreeIterator iterator(node);
    while( ! iterator.isDone() ){
        SyntaxNode *syntaxNode = dynamic_cast<SyntaxNode *>(iterator.current());
        if( syntaxNode )
            syntaxNode->accept( this );
        iterator.next();
    }
    update();
}

void TreeViewer::visit( SyntaxNodeNumber *node )
{
    makeSimpleTree( QString::number(node->value()) );
}

void TreeViewer::visit( SyntaxNodeVarDecl *node )
{
    makeSimpleTree( node->name().c_str() );
}

void TreeViewer::visit( SyntaxNodeAdd *node )
{
    makeBinaryTree( node, "+" );
}

void TreeViewer::visit( SyntaxNodeSub *node )
{
    makeBinaryTree( node, "-" );
}

void TreeViewer::visit( SyntaxNodeMul *node )
{
    makeBinaryTree( node, "*" );
}

void TreeViewer::visit( SyntaxNodeDiv *node )
{
    makeBinaryTree( node, "/" );
}

void TreeViewer::visit( SyntaxNodePlus *node )
{
    makeUnaryTree( node, "+" );
}

void TreeViewer::visit( SyntaxNodeMinus *node )
{
    makeUnaryTree( node, "-" );
}

void TreeViewer::visit( SyntaxNodeVarRef *node )
{
    makeSimpleTree( node->name().c_str() );
}

void TreeViewer::visit( SyntaxNodeAssign *node )
{
    VisualTree *value = 0;
    if( node->value() ){
        value = m_treeStack.top();
        m_treeStack.pop();
    }
    VisualTree *var = 0;
    if( node->var() ){
        var = m_treeStack.top();
        m_treeStack.pop();
    }

    VisualTree *tree = new VisualTree();
    VisualTreeNode *treeNode = new VisualTreeNode( "var" );
    tree->setNode( treeNode );
    if( var )
        tree->addBranch( var );
    if( value )
        tree->addBranch( value );

    m_treeStack.push( tree );
}

VisualTree *TreeViewer::makeSimpleTree( QString string )
{
    VisualTree *tree = new VisualTree();
    VisualTreeNode *treeNode = new VisualTreeNode( string );
    tree->setNode( treeNode );
    m_treeStack.push( tree );
    return tree;
}

VisualTree *TreeViewer::makeBinaryTree( SyntaxNodeBinary *node, QString string )
{
    VisualTree *operand2 = 0;
    if( node->operand2() ){
        operand2 = m_treeStack.top();
        m_treeStack.pop();
    }
    VisualTree *operand1 = 0;
    if( node->operand1() ){
        operand1 = m_treeStack.top();
        m_treeStack.pop();
    }

    VisualTree *tree = new VisualTree();
    VisualTreeNode *treeNode = new VisualTreeNode( string );
    tree->setNode( treeNode );
    if( operand1 )
        tree->addBranch( operand1 );
    if( operand2 )
        tree->addBranch( operand2 );

    m_treeStack.push( tree );
    return tree;
}

VisualTree *TreeViewer::makeUnaryTree( SyntaxNodeUnary *node, QString string )
{
    VisualTree *operand = 0;
    if( node->operand() ){
        operand = m_treeStack.top();
        m_treeStack.pop();
    }
    VisualTree *tree = new VisualTree();
    VisualTreeNode *treeNode = new VisualTreeNode( string );
    tree->setNode( treeNode );
    if( operand )
        tree->addBranch( operand );

    m_treeStack.push( tree );
    return tree;
}

void TreeViewer::paintEvent(QPaintEvent *)
{
    if( m_treeStack.empty() )
        return;
    VisualTree *tree = m_treeStack.top();

    QPainter painter(this);

    QFont f = painter.font();
    QFontMetrics fm(f);
    tree->layout( fm );
    tree->draw( &painter );
}

void TreeViewer::clearTreeStack()
{
    while( ! m_treeStack.empty() ){
        VisualTree *tree = m_treeStack.top();
        m_treeStack.pop();
        delete tree;
    }
}
