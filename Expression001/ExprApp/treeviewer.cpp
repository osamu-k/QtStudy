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

void TreeViewer::setNode( SyntaxNode *node )
{
    clearTreeStack();
    if( node ){
        node->acceptVisitor( this );
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

Tree *TreeViewer::makeBinaryTree( SyntaxNodeBinary *node, QString string )
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

Tree *TreeViewer::makeUnaryTree( SyntaxNodeUnary *node, QString string )
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
