#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

enum syntax_node_type {
    NODE_UNDEFINED,
    NODE_NUMBER,
    NODE_VARIABLE,
    NODE_UNARY_OP,
    NODE_BINARY_OP,
    NODE_ASSIGNMENT
};

struct syntax_node {
    enum syntax_node_type type;
};

struct syntax_node_number {
    enum syntax_node_type type;
    int value;
};

struct syntax_node_variable{
    enum syntax_node_type type;
    char *var;
};

struct syntax_node_unary_op{
    enum syntax_node_type type;
    char symbol;
    struct syntax_node *operand;
};

struct syntax_node_binary_op{
    enum syntax_node_type type;
    char symbol;
    struct syntax_node *operand1;
    struct syntax_node *operand2;
};

struct syntax_node_assignment{
    enum syntax_node_type type;
    char *var;
    struct syntax_node *value;
};

struct syntax_node_number *alloc_node_number(
    int value
);

struct syntax_node_variable *alloc_node_variable(
    const char *var
);

struct syntax_node_unary_op *alloc_node_unary_op(
    char symbol,
    struct syntax_node *operand
);

struct syntax_node_binary_op *alloc_node_binary_op(
    char symbol,
    struct syntax_node *operand1,
    struct syntax_node *operand2
);

struct syntax_node_assignment *alloc_node_assignment(
    const char *var,
    struct syntax_node *value
);

void free_syntax_tree(
    struct syntax_node *n
);

#endif // SYNTAXTREE_H

