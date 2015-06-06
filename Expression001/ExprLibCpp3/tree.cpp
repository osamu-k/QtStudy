#include "tree.h"

TreeNode::TreeNode()
{
}

TreeNode::~TreeNode()
{
}

int TreeNode::childCount() const
{
    return m_children.size();
}

TreeNode *TreeNode::child( int index )
{
    if( index >= m_children.size() )
        return 0;
    return m_children[index];
}
