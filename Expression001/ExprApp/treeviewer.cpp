#include <QFont>
#include <QFontMetrics>

#include "treeviewer.h"
#include "node.h"

TreeViewer::TreeViewer(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setPalette( Qt::white );
}

TreeViewer::~TreeViewer()
{
    clearTreeStack();
}

void TreeViewer::setNode( Node *node )
{
    clearTreeStack();
    if( node ){
        node->acceptVisitor( this );
    }
    update();
}

void TreeViewer::visit( NodeInteger *node )
{
    makeSimpleTree( QString::number(node->value()) );
}

void TreeViewer::visit( NodeVarDecl *node )
{
    makeSimpleTree( node->name().c_str() );
}

void TreeViewer::visit( NodeAdd *node )
{
    makeBinaryTree( node, "+" );
}

void TreeViewer::visit( NodeSub *node )
{
    makeBinaryTree( node, "-" );
}

void TreeViewer::visit( NodeMul *node )
{
    makeBinaryTree( node, "*" );
}

void TreeViewer::visit( NodeDiv *node )
{
    makeBinaryTree( node, "/" );
}

void TreeViewer::visit( NodePlus *node )
{
    makeUnaryTree( node, "+" );
}

void TreeViewer::visit( NodeMinus *node )
{
    makeUnaryTree( node, "-" );
}

void TreeViewer::visit( NodeVarRef *node )
{
    makeSimpleTree( node->name().c_str() );
}

void TreeViewer::visit( NodeAssign *node )
{
    Tree *value = 0;
    if( node->value() ){
        value = m_treeStack.top();
        m_treeStack.pop();
    }
    Tree *var = 0;
    if( node->var() ){
        var = m_treeStack.top();
        m_treeStack.pop();
    }

    Tree *tree = new Tree();
    TreeNode *treeNode = new TreeNode( "var" );
    tree->setNode( treeNode );
    if( var )
        tree->addBranch( var );
    if( value )
        tree->addBranch( value );

    m_treeStack.push( tree );
}

Tree *TreeViewer::makeSimpleTree( QString string )
{
    Tree *tree = new Tree();
    TreeNode *treeNode = new TreeNode( string );
    tree->setNode( treeNode );
    m_treeStack.push( tree );
    return tree;
}

Tree *TreeViewer::makeBinaryTree( NodeInfix *node, QString string )
{
    Tree *operand2 = 0;
    if( node->operand2() ){
        operand2 = m_treeStack.top();
        m_treeStack.pop();
    }
    Tree *operand1 = 0;
    if( node->operand1() ){
        operand1 = m_treeStack.top();
        m_treeStack.pop();
    }

    Tree *tree = new Tree();
    TreeNode *treeNode = new TreeNode( string );
    tree->setNode( treeNode );
    if( operand1 )
        tree->addBranch( operand1 );
    if( operand2 )
        tree->addBranch( operand2 );

    m_treeStack.push( tree );
    return tree;
}

Tree *TreeViewer::makeUnaryTree( NodePrefix *node, QString string )
{
    Tree *operand = 0;
    if( node->operand() ){
        operand = m_treeStack.top();
        m_treeStack.pop();
    }
    Tree *tree = new Tree();
    TreeNode *treeNode = new TreeNode( string );
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
    Tree *tree = m_treeStack.top();

    QPainter painter(this);

    QFont f = painter.font();
    QFontMetrics fm(f);
    tree->layout( fm );
    tree->draw( &painter );
}

void TreeViewer::clearTreeStack()
{
    while( ! m_treeStack.empty() ){
        Tree *tree = m_treeStack.top();
        m_treeStack.pop();
        delete tree;
    }
}
