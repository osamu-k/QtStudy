#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "evaluator.h"
#include "parser.h"
#include "tokenizer.h"
#include <string>
using namespace std;

class Interpreter
{
public:
    Interpreter();
    ~Interpreter();
    int interpret(string source);
    bool isError();
    string errorMessage();
    Parser::ParsingStatus parsingStatus();
    string parsingErrorMessage();
    Evaluator::EvaluationStatus evaluationStatus();
    string evaluationErrorMessage();
private:
    Tokenizer m_tokenizer;
    Parser m_parser;
    Evaluator m_evaluator;
};

#endif // INTERPRETER_H
