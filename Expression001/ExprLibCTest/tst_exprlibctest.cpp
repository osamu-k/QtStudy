#include <QString>
#include <QtTest>

extern "C" {
#include "tokenizer.h"
#include "interpreter.h"
#include "parser.h"
#include "evaluator.h"
}

class ExprLibCTest : public QObject
{
    Q_OBJECT

public:
    ExprLibCTest(){}

private Q_SLOTS:
    void initTestCase(){}
    void cleanupTestCase(){}

    void testInterpretNumber()
    {
        QCOMPARE( interpret( "1" ), 1 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretNumber2()
    {
        QCOMPARE( interpret( "12345" ), 12345 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretPositiveNumber()
    {
        QCOMPARE( interpret( "+123" ), +123 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretNegativeNumber()
    {
        QCOMPARE( interpret( "-123" ), -123 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretPositiveAddPositive()
    {
        QCOMPARE( interpret( "123+456" ), 123+456 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretNegativeAddNegative()
    {
        QCOMPARE( interpret( "-123+-456" ), -123+-456 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretPositiveAddNegativeIsPositive()
    {
        QCOMPARE( interpret( "456+-123" ), 456+-123 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretPositiveAddNegativeIsNegative()
    {
        QCOMPARE( interpret( "123+-456" ), 123+-456 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretNegativeAddPositiveIsPositive()
    {
        QCOMPARE( interpret( "-123+456" ), -123+456 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretNegativeAddPositiveIsNegative()
    {
        QCOMPARE( interpret( "-456+123" ), -456+123 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretPositiveSubPositiveIsPositive()
    {
        QCOMPARE( interpret( "456-123" ), 456-123 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretPositiveSubPositiveIsNegative()
    {
        QCOMPARE( interpret( "123-456" ), 123-456 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretAddSubRepeated()
    {
        QCOMPARE( interpret( "12+34-56+78-90" ), 12+34-56+78-90 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretPositiveMulPositive(){
        QCOMPARE( interpret( "123*456" ), 123*456 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretPositiveMulNegative(){
        QCOMPARE( interpret( "123*-456" ), 123*-456 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretNegativeMulPositive(){
        QCOMPARE( interpret( "-123*456" ), -123*456 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretNegativeMulNegative(){
        QCOMPARE( interpret( "-123*-456" ), -123*-456 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretPositiveDivPositive(){
        QCOMPARE( interpret( "12345/456" ), 12345/456 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretPositiveDivNegative(){
        QCOMPARE( interpret( "12345/-456" ), 12345/-456 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretNegativeDivPositive(){
        QCOMPARE( interpret( "-12345/456" ), -12345/456 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretNegativeDivNegative(){
        QCOMPARE( interpret( "-12345/-456" ), -12345/-456 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretMulDivRepeated(){
        QCOMPARE( interpret( "98*76/54*32/10" ), 98*76/54*32/10 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretVariable(){
        QCOMPARE( interpret( "var abc = 123+456-789"), 123+456-789 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );

        QCOMPARE( interpret( "abc"), 123+456-789 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretUndefinedVariable(){
        QCOMPARE( interpret( "var abc = 123+456-789"), 123+456-789 );
        QCOMPARE( evaluation_status(), EVALUATION_OK );

        QCOMPARE( interpret( "xyz"), 0 );
        QCOMPARE( evaluation_status(), EVALUATION_ERROR_UNDEFINED_VARIABLE );
    }

    void testInterpretComplexExpression(){
        QCOMPARE( interpret( "var abc = 1200"), 1200 );
        QCOMPARE( interpret( "var xyz = 98"), 98 );

        QCOMPARE( interpret( "(+(abc+3400)*-(56-78))/(+(xyz-76)*-(54+32))" ), (+(1200+3400)*-(56-78))/(+(98-76)*-(54+32)) );
        QCOMPARE( evaluation_status(), EVALUATION_OK );
    }

    void testInterpretAddOverflow(){
        QCOMPARE( interpret( "1/0" ), 0 );
        QCOMPARE( evaluation_status(), EVALUATION_ERROR_DIVIDED_BY_ZERO );
    }
};

QTEST_APPLESS_MAIN(ExprLibCTest)

#include "tst_exprlibctest.moc"
