#ifndef TREE_H
#define TREE_H

#include <vector>
using namespace std;

class TreeNode
{
public:
    TreeNode();
    virtual ~TreeNode();
    int childCount() const;
    TreeNode *child( int index );
protected:
    vector<TreeNode *> m_children;
};

#endif // TREE_H
