#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "syntaxtree.h"

enum evaluation_status{
    EVALUATION_OK,
    EVALUATION_ERROR_DIVIDED_BY_ZERO,
    EVALUATION_ERROR_INCOMPLETE_SYNTAX,
    EVALUATION_ERROR_UNDEFINED_VARIABLE
};

int evaluate( struct syntax_node *n );
enum evaluation_status evaluation_status();

#endif // EVALUATOR_H
