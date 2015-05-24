#ifndef TREE_H
#define TREE_H

#include <QList>
#include <QPainter>
#include <QRect>

class TreeNode;

class Tree
{
public:
    Tree();
    ~Tree();
    void setNode( TreeNode *node );
    void addBranch( Tree *branch );
    Tree *branch( int i );
    QRect layout( QFontMetrics &fm );
    QRect rect();
    void draw( QPainter *painter );

private:
    TreeNode *node();
    QRect layoutBranches( QFontMetrics fm );
    void adjustBranchs( int dx, int dy );
    void adjustPosition( QPoint offset );
    QPoint pointBranchIn();

    TreeNode *m_node;
    QList<Tree*> m_branches;
    QRect m_rect;
};

class TreeNode
{
public:
    TreeNode( QString string );
    ~TreeNode();
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

#endif // TREE_H
