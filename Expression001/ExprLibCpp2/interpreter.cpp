#include "interpreter.h"

Interpreter::Interpreter()
    : m_parser( &m_tokenizer )
{

}

Interpreter::~Interpreter()
{

}

int Interpreter::interpret(string source)
{
    SyntaxNode *node = m_parser.parse(source);
    int ret = m_evaluator.evaluate(node);
    return ret;
}

bool Interpreter::isError()
{
    return (parsingStatus() != Parser::PARSING_OK)
            || (evaluationStatus() != Evaluator::EVALUATION_OK);
}

string Interpreter::errorMessage()
{
    if( parsingStatus() != Parser::PARSING_OK )
        return parsingErrorMessage();
    else if( evaluationStatus() != Evaluator::EVALUATION_OK )
        return evaluationErrorMessage();
    return string();
}

Parser::ParsingStatus Interpreter::parsingStatus()
{
    return m_parser.status();
}

string Interpreter::parsingErrorMessage()
{
    return m_parser.errorMessage();
}

Evaluator::EvaluationStatus Interpreter::evaluationStatus()
{
    return m_evaluator.status();
}

string Interpreter::evaluationErrorMessage()
{
    return m_evaluator.errorMessage();
}
