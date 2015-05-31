#ifndef NODEVISITOR_H
#define NODEVISITOR_H

class SyntaxNodeNumber;
class SyntaxNodeVarDecl;
class SyntaxNodeAdd;
class SyntaxNodeSub;
class SyntaxNodeMul;
class SyntaxNodeDiv;
class SyntaxNodePlus;
class SyntaxNodeMinus;
class SyntaxNodeVarRef;
class SyntaxNodeAssign;

class NodeVisitor
{
public:
    NodeVisitor()
    {}

    virtual ~NodeVisitor()
    {}

    virtual void visit( SyntaxNodeNumber * ) = 0;
    virtual void visit( SyntaxNodeVarDecl * ) = 0;
    virtual void visit( SyntaxNodeAdd * ) = 0;
    virtual void visit( SyntaxNodeSub * ) = 0;
    virtual void visit( SyntaxNodeMul * ) = 0;
    virtual void visit( SyntaxNodeDiv * ) = 0;
    virtual void visit( SyntaxNodePlus * ) = 0;
    virtual void visit( SyntaxNodeMinus * ) = 0;
    virtual void visit( SyntaxNodeVarRef * ) = 0;
    virtual void visit( SyntaxNodeAssign * ) = 0;
};

#endif // NODEVISITOR_H
