#include "treeiterator.h"

TreeIterator::TreeIterator( TreeNode *target )
    : m_target(target)
{
    if( target ){
        m_stack.push( StackItem( target, 0 ) );
        while(target->childCount()){
            target = target->child(0);
            m_stack.push( StackItem( target, 0 ) );
        }
    }
}

TreeIterator::~TreeIterator()
{
}

void TreeIterator::first()
{
    // ToDo.
}

void TreeIterator::next()
{
    if(m_stack.size() == 0)
        return;
    m_stack.pop();
    if(m_stack.size() == 0)
        return;
    m_stack.top().index ++;
    if( m_stack.top().index  < m_stack.top().node->childCount() ){
        TreeNode *node = m_stack.top().node->child(m_stack.top().index);
        m_stack.push( StackItem(node,0) );
        if( node ){
            while(node->childCount()){
                node = node->child(0);
                m_stack.push( StackItem( node, 0 ) );
            }
        }
    }
}

bool TreeIterator::isDone()
{
    return m_stack.size() == 0;
}

TreeNode *TreeIterator::current()
{
    TreeNode *node = 0;
    if( m_stack.size() > 0 ){
        node = m_stack.top().node;
    }
    return node;
}
