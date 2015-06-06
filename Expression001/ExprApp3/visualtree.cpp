#include "visualtree.h"

#include <QFont>
#include <QFontMetrics>
#include <QDebug>

#include <algorithm>
using namespace std;

VisualTree::VisualTree()
    :m_node(0)
{
}

VisualTree::~VisualTree()
{
    if( m_node )
        delete m_node;
    foreach( VisualTree *branch, m_branches ){
        delete branch;
    }
    m_branches.clear();
}

void VisualTree::setNode( VisualTreeNode *node )
{
    if( m_node )
        delete m_node;
    m_node = node;
}

VisualTreeNode *VisualTree::node()
{
    return m_node;
}

void VisualTree::addBranch( VisualTree *branch )
{
    m_branches << branch;
}

VisualTree *VisualTree::branch( int i )
{
    return m_branches[i];
}

QRect VisualTree::layout( QFontMetrics &fm )
{
    int spacing = fm.height() * 2;

    m_rect = QRect(0,0,0,0);
    QRect rectNode = m_node->layout( fm );
    QRect rectBranches = layoutBranches( fm );

    m_rect.setWidth( max( rectNode.width(), rectBranches.width()) );
    m_rect.setHeight( rectNode.height() + rectBranches.height() );

    if( rectBranches.height() > 0 ){
        m_rect.adjust( 0, 0, 0, spacing );
        if( rectNode.width() <= rectBranches.width() ){
            m_node->adjustPosition( QPoint((rectBranches.width() - rectNode.width())/2, 0) );
            adjustBranchs( 0,
                           rectNode.height() + spacing );
        }
        else{
            adjustBranchs( (rectNode.width() - rectBranches.width()) / 2,
                           rectNode.height() + spacing );
        }
    }
    return m_rect;
}

QRect VisualTree::layoutBranches( QFontMetrics fm )
{
    QRect rect(0,0,0,0);
    int spacingH = fm.averageCharWidth() * 2;

    foreach( VisualTree *branch, m_branches ){
        QRect brect = branch->layout( fm );
        if( rect.width() > 0 ){
            rect.adjust(0,0,spacingH,0);
        }
        branch->adjustPosition( QPoint(rect.width(),0) );
        rect.adjust(0,0,brect.width(),0);
        if( rect.height() < brect.height() ){
            rect.adjust(0,0,0,brect.height());
        }
    }
    return rect;
}

void VisualTree::adjustBranchs( int dx, int dy )
{
    foreach( VisualTree *branch, m_branches ){
        branch->adjustPosition( QPoint(dx,dy) );
    }
}

void VisualTree::adjustPosition( QPoint offset ){
    m_rect.translate( offset );
    m_node->adjustPosition( offset );
    foreach( VisualTree *branch, m_branches ){
        branch->adjustPosition( offset );
    }
}

QRect VisualTree::rect()
{
    return m_rect;
}

QPoint VisualTree::pointBranchIn()
{
    return m_node->pointBranchIn();
}

void VisualTree::draw( QPainter *painter ){
    foreach( VisualTree *branch, m_branches ){
        painter->drawLine( m_node->pointBranchOut(), branch->pointBranchIn() );
        branch->draw( painter );
    }
    m_node->draw( painter );
}

VisualTreeNode::VisualTreeNode( QString string )
    : m_string(string)
{
}

VisualTreeNode::~VisualTreeNode()
{
}

QRect VisualTreeNode::layout( QFontMetrics &fm )
{
    QRect brect = fm.boundingRect(m_string);
    m_rect = QRect( 0, 0, brect.width() + fm.averageCharWidth(), brect.height() + fm.height() );
    if( m_rect.width() < m_rect.height() ){
        m_rect.setWidth( m_rect.height() );
    }
    return m_rect;
}

void VisualTreeNode::adjustPosition( QPoint offset ){
    m_rect.translate( offset );
}

QRect VisualTreeNode::rect()
{
    return m_rect;
}

QPoint VisualTreeNode::pointBranchIn()
{
    return QPoint( m_rect.x() + m_rect.width() / 2, m_rect.y() );
}

QPoint VisualTreeNode::pointBranchOut()
{
    return QPoint( m_rect.x() + m_rect.width() / 2, m_rect.y() + m_rect.height() );
}

void VisualTreeNode::draw( QPainter *painter )
{
    QFont f = painter->font();
    QFontMetrics fm(f);
    painter->drawText( m_rect, m_string, Qt::AlignHCenter | Qt::AlignVCenter );
    painter->drawRect( m_rect );
}
