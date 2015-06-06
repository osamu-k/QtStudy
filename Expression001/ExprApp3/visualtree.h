#ifndef VISUAL_TREE_H
#define VISUAL_TREE_H

#include <QList>
#include <QPainter>
#include <QRect>

class VisualTreeNode;

class VisualTree
{
public:
    VisualTree();
    ~VisualTree();
    void setNode( VisualTreeNode *node );
    void addBranch( VisualTree *branch );
    VisualTree *branch( int i );
    QRect layout( QFontMetrics &fm );
    QRect rect();
    void draw( QPainter *painter );

private:
    VisualTreeNode *node();
    QRect layoutBranches( QFontMetrics fm );
    void adjustBranchs( int dx, int dy );
    void adjustPosition( QPoint offset );
    QPoint pointBranchIn();

    VisualTreeNode *m_node;
    QList<VisualTree*> m_branches;
    QRect m_rect;
};

class VisualTreeNode
{
public:
    VisualTreeNode( QString string );
    ~VisualTreeNode();
    QRect layout( QFontMetrics &fm );
    void adjustPosition( QPoint offset );
    QRect rect();
    QPoint pointBranchIn();
    QPoint pointBranchOut();
    void draw( QPainter *painter );

private:
    QString m_string;
    QRect m_rect;
};

#endif // VISUAL_TREE_H
