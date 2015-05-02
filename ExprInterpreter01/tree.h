#ifndef TREE_H
#define TREE_H

#include <QFont>
#include <QFontMetrics>
#include <QList>
#include <QPainter>
#include <QDebug>
#include <QRect>

class TreeNode
{
public:
    TreeNode( QString string )
        : m_string(string)
    {}

    ~TreeNode()
    {}

    QRect layout( QFontMetrics &fm )
    {
        m_rect = fm.boundingRect(m_string);
        m_rect.adjust( 0, 0, fm.averageCharWidth(), fm.height() );
        if( m_rect.width() < m_rect.height() ){
            m_rect.setWidth( m_rect.height() );
        }
        m_rect.moveTo( 0, 0 );
        return m_rect;
    }

    QRect translate( QPoint offset ){
        m_rect.translate( offset );
    }

    QRect rect()
    {
        return m_rect;
    }

    void draw( QPainter *painter )
    {
        QFont f = painter->font();
        QFontMetrics fm(f);
        painter->drawText( m_rect, m_string, Qt::AlignHCenter | Qt::AlignVCenter );
        painter->drawRect( m_rect );
    }

private:
    QString m_string;
    QRect m_rect;
};

class Tree
{
public:
    Tree();
    ~Tree();

    void setNode( TreeNode *node )
    {
        m_node = node;
    }

    TreeNode *node()
    {
        return m_node;
    }

    void addBranch( Tree *branch )
    {
        m_branches << branch;
    }

    Tree *branch( int i )
    {
        return m_branches[i];
    }

    QRect layout( QFontMetrics &fm )
    {
        qDebug() << "Layouting...";
        int fontWidth = fm.averageCharWidth();
        int fontHeight = fm.height();
        int width = 0;
        int height = 0;

        foreach( Tree *branch, m_branches ){
            QRect brect = branch->layout( fm );
            if( width > 0 ){
                width += fontWidth * 2;
            }
            branch->translate( QPoint(width,0) );
            width += brect.width();
            if( height < brect.height() ){
                height = brect.height();
            }
        }

        if( height > 0 ){
            height += fontHeight * 2;
        }
        QRect nodeRect = m_node->layout( fm );
        if( width < nodeRect.width() ){
            width = nodeRect.width();
            int dx = (nodeRect.width() - width) / 2;
            foreach( Tree *branch, m_branches ){
                branch->translate( QPoint(dx,0) );
            }
        }
        else{
            int dx = (width - nodeRect.width()) / 2;
            m_node->translate( QPoint(dx,0) );
        }
        height += nodeRect.height();

        int dy = fontHeight * 2 + nodeRect.height();
        foreach( Tree *branch, m_branches ){
            branch->translate( QPoint(0,dy) );
        }

        m_rect = QRect( 0, 0, width, height );
        return m_rect;
    }

    QRect translate( QPoint offset ){
        m_rect.translate( offset );
        m_node->translate( offset );
        foreach( Tree *branch, m_branches ){
            branch->translate( offset );
        }
    }

    QRect rect()
    {
        return m_rect;
    }

    QRect nodeRect()
    {
        return m_node->rect();
    }

    void draw( QPainter *painter ){
        foreach( Tree *branch, m_branches ){
            branch->draw( painter );
            QPoint p1 = QPoint( m_node->rect().x() + m_node->rect().width() / 2, m_node->rect().y() + m_node->rect().height() );
            QPoint p2 = QPoint( branch->rect().x() + branch->rect().width() / 2, branch->rect().y() );
            painter->drawLine( p1, p2 );
        }
        m_node->draw( painter );
    }

private:
    TreeNode *m_node;
    QList<Tree*> m_branches;
    QRect m_rect;
};

#endif // TREE_H
