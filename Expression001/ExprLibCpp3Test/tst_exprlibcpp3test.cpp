#include <QString>
#include <QtTest>

#include "interpreter.h"
#include "treeiterator.h"
#include "parser.h"
#include "tokenizer.h"

class ExprLibCpp3Test : public QObject
{
    Q_OBJECT

public:
    ExprLibCpp3Test(){}

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

//    void testInterpretComplexExpression(){
//        Interpreter interpreter;

//        QCOMPARE( interpreter.interpret( "(+(1200+3400)*-(56-78))/(+(98-76)*-(54+32))" ), (+(1200+3400)*-(56-78))/(+(98-76)*-(54+32)) );
//        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
//        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_OK );
//    }

    void testInterpretDivideByZero(){
        Interpreter interpreter;

        QCOMPARE( interpreter.interpret( "1/0" ), 0 );
        QCOMPARE( interpreter.parsingStatus(), Parser::PARSING_OK );
        QCOMPARE( interpreter.evaluationStatus(), Evaluator::EVALUATION_ERROR_DIVIDED_BY_ZERO );
    }

    void testIterateEmptyTree(){
        TreeIterator iterator(0);
        QCOMPARE( iterator.isDone(), true );
    }

    void testIterateSingleNodeTree(){
        Tokenizer tokenizer;
        Parser parser( &tokenizer );
        SyntaxNode *node = parser.parse("1");
        TreeIterator iterator(node);
        QCOMPARE( iterator.isDone(), false );
        QCOMPARE( iterator.current(), node );
        iterator.next();
        QCOMPARE( iterator.isDone(), true );
    }

    void testIterate2NodeTree(){
        Tokenizer tokenizer;
        Parser parser( &tokenizer );
        SyntaxNode *node = parser.parse("-1");
        TreeIterator iterator(node);
        QCOMPARE( iterator.isDone(), false );
        QCOMPARE( iterator.current(), dynamic_cast<SyntaxNodeUnary*>(node)->operand() );
        iterator.next();
        QCOMPARE( iterator.isDone(), false );
        QCOMPARE( iterator.current(), node );
        iterator.next();
        QCOMPARE( iterator.isDone(), true );
    }

    void testIterateComplexTree(){
        SyntaxNodeNumber *number1 = new SyntaxNodeNumber(1);
        SyntaxNodeNumber *number2 = new SyntaxNodeNumber(2);
        SyntaxNodeAdd *add1 = new SyntaxNodeAdd( number1, number2 );
        SyntaxNodeNumber *number3 = new SyntaxNodeNumber(3);
        SyntaxNodeNumber *number4 = new SyntaxNodeNumber(4);
        SyntaxNodeAdd *add2 = new SyntaxNodeAdd( number3, number4 );
        SyntaxNodeAdd *add3 = new SyntaxNodeAdd( add1, add2 );

        TreeIterator iterator(add3);
        QCOMPARE( iterator.isDone(), false );
        QCOMPARE( iterator.current(), number1 );
        iterator.next();
        QCOMPARE( iterator.isDone(), false );
        QCOMPARE( iterator.current(), number2 );
        iterator.next();
        QCOMPARE( iterator.isDone(), false );
        QCOMPARE( iterator.current(), add1 );
        iterator.next();
        QCOMPARE( iterator.isDone(), false );
        QCOMPARE( iterator.current(), number3 );
        iterator.next();
        QCOMPARE( iterator.isDone(), false );
        QCOMPARE( iterator.current(), number4 );
        iterator.next();
        QCOMPARE( iterator.isDone(), false );
        QCOMPARE( iterator.current(), add2 );
        iterator.next();
        QCOMPARE( iterator.isDone(), false );
        QCOMPARE( iterator.current(), add3 );
        iterator.next();
        QCOMPARE( iterator.isDone(), true );
    }
};

QTEST_APPLESS_MAIN(ExprLibCpp3Test)

#include "tst_exprlibcpp3test.moc"
