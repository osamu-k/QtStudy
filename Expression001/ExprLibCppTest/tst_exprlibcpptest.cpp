#include "interpreter.h"

#include <QString>
#include <QtTest>

class ExprLibCppTest : public QObject
{
    Q_OBJECT

public:
    ExprLibCppTest(){}

private Q_SLOTS:
    void initTestCase(){}
    void cleanupTestCase(){}

    void testInterpretNumber()
    {
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "1" ), 1 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretNumber2()
    {
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "12345" ), 12345 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretPositiveNumber()
    {
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "+123" ), +123 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretNegativeNumber()
    {
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "-123" ), -123 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretPositiveAddPositive()
    {
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "123+456" ), 123+456 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretNegativeAddNegative()
    {
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "-123+-456" ), -123+-456 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretPositiveAddNegativeIsPositive()
    {
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "456+-123" ), 456+-123 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretPositiveAddNegativeIsNegative()
    {
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "123+-456" ), 123+-456 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretNegativeAddPositiveIsPositive()
    {
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "-123+456" ), -123+456 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretNegativeAddPositiveIsNegative()
    {
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "-456+123" ), -456+123 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretPositiveSubPositiveIsPositive()
    {
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "456-123" ), 456-123 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretPositiveSubPositiveIsNegative()
    {
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "123-456" ), 123-456 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretAddSubRepeated()
    {
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "12+34-56+78-90" ), 12+34-56+78-90 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretPositiveMulPositive(){
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "123*456" ), 123*456 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretPositiveMulNegative(){
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "123*-456" ), 123*-456 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretNegativeMulPositive(){
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "-123*456" ), -123*456 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretNegativeMulNegative(){
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "-123*-456" ), -123*-456 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretPositiveDivPositive(){
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "12345/456" ), 12345/456 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretPositiveDivNegative(){
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "12345/-456" ), 12345/-456 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretNegativeDivPositive(){
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "-12345/456" ), -12345/456 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretNegativeDivNegative(){
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "-12345/-456" ), -12345/-456 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretMulDivRepeated(){
        Interpreter interpreter;
        QCOMPARE( interpreter.interpret( "98*76/54*32/10" ), 98*76/54*32/10 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretVariable(){
        Interpreter interpreter;

        QCOMPARE( interpreter.interpret( "var abc = 123+456-789"), 123+456-789 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );

        QCOMPARE( interpreter.interpret( "abc"), 123+456-789 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretUndefinedVariable(){
        Interpreter interpreter;

        QCOMPARE( interpreter.interpret( "var abc = 123+456-789"), 123+456-789 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );

        QCOMPARE( interpreter.interpret( "xyz"), 0 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_ERROR_UNDEFINED_VARIABLE );
    }

    void testInterpretComplexExpression(){
        Interpreter interpreter;

        QCOMPARE( interpreter.interpret( "var abc = 1200"), 1200 );
        QCOMPARE( interpreter.interpret( "var xyz = 98"), 98 );

        QCOMPARE( interpreter.interpret( "(+(abc+3400)*-(56-78))/(+(xyz-76)*-(54+32))" ), (+(1200+3400)*-(56-78))/(+(98-76)*-(54+32)) );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
    }

    void testInterpretDivideByZero(){
        Interpreter interpreter;

        QCOMPARE( interpreter.interpret( "1/0" ), 0 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_ERROR_DIVIDED_BY_ZERO );
    }
};

QTEST_APPLESS_MAIN(ExprLibCppTest)

#include "tst_exprlibcpptest.moc"
