#ifndef SYTAXNODEITERATOR_H
#define SYTAXNODEITERATOR_H

#include "tree.h"
#include <stack>

class TreeIterator
{
public:
    TreeIterator( TreeNode *target );
    ~TreeIterator();
    void first();
    void next();
    bool isDone();
    TreeNode *current();

private:
    TreeNode *m_target;
    struct StackItem{
        TreeNode *node;
        int index;
        StackItem(TreeNode *n, int i)
            :node(n),index(i)
        {}
    };
    std::stack<StackItem> m_stack;
};

#endif // SYTAXNODEITERATOR_H
