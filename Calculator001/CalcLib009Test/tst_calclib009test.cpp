#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QLineEdit>
#include <QPushButton>

#include "calculator.h"

class CalcLib009Test : public QObject
{
    Q_OBJECT

public:
    CalcLib009Test(){}

private Q_SLOTS:
    void initTestCase(){}
    void cleanupTestCase(){}

    void testCalculatorCanBeShown()
    {
        Calculator calc;
        calc.show();
        QCOMPARE(calc.isVisible(),true);
        pause();
    }

    void testCalculatorAcceptsNumber1()
    {
        Calculator calc;
        calc.show();
        pause();
        clickButton( calc, "button1" );
        assertDisplay2( calc, QString("1") );
    }

    void testCalculatorAcceptsNumber1234567890()
    {
        Calculator calc;
        calc.show();
        pause();
        clickButton( calc, "button1" );
        clickButton( calc, "button2" );
        clickButton( calc, "button3" );
        clickButton( calc, "button4" );
        clickButton( calc, "button5" );
        clickButton( calc, "button6" );
        clickButton( calc, "button7" );
        clickButton( calc, "button8" );
        clickButton( calc, "button9" );
        clickButton( calc, "button0" );

        assertDisplay2( calc, QString("1234567890") );
    }

    void testCalculatorIgnoresPrecidingZeros()
    {
        Calculator calc;
        calc.show();
        pause();

        clickButton( calc, "button0" );
        assertDisplay2( calc, QString("0") );

        clickButton( calc, "button0" );
        clickButton( calc, "button0" );
        assertDisplay2( calc, QString("0") );

        clickButton( calc, "button1" );
        clickButton( calc, "button0" );
        clickButton( calc, "button0" );
        assertDisplay2( calc, QString("100") );
    }

    void testCalculatorAcceptsAddOperator()
    {
        Calculator calc;
        calc.show();
        pause();
        assertOperator(calc,"buttonAdd");
    }

    void testCalculatorAcceptsSubOperator()
    {
        Calculator calc;
        calc.show();
        pause();
        assertOperator(calc,"buttonSub");
    }

    void testCalculatorAcceptsMulOperator()
    {
        Calculator calc;
        calc.show();
        pause();
        assertOperator(calc,"buttonMul");
    }

    void testCalculatorAcceptsDivOperator()
    {
        Calculator calc;
        calc.show();
        pause();
        assertOperator(calc,"buttonDiv");
    }

    void testCalculatorAcceptsNumberAfterOperatorAdd()
    {
        Calculator calc;
        calc.show();
        pause();
        assertNumberAfterOperator(calc,"buttonAdd");
    }

    void testCalculatorAcceptsNumberAfterOperatorSub()
    {
        Calculator calc;
        calc.show();
        pause();
        assertNumberAfterOperator(calc,"buttonSub");
    }

    void testCalculatorAcceptsNumberAfterOperatorMul()
    {
        Calculator calc;
        calc.show();
        pause();
        assertNumberAfterOperator(calc,"buttonMul");
    }

    void testCalculatorAcceptsNumberAfterOperatorDiv()
    {
        Calculator calc;
        calc.show();
        pause();
        assertNumberAfterOperator(calc,"buttonDiv");
    }

    void testCalculatorCalculatesOperatorAdd()
    {
        Calculator calc;
        calc.show();
        pause();
        assertCalculation( calc,"12345","buttonAdd","67",12345l + 67l );
    }

    void testCalculatorCalculatesOperatorSub()
    {
        Calculator calc;
        calc.show();
        pause();
        assertCalculation( calc,"12345","buttonSub","67",12345l - 67l );
    }

    void testCalculatorCalculatesOperatorMul()
    {
        Calculator calc;
        calc.show();
        pause();
        assertCalculation( calc,"12345","buttonMul","67",12345l * 67l );
    }

    void testCalculatorCalculatesOperatorDiv()
    {
        Calculator calc;
        calc.show();
        pause();
        assertCalculation( calc,"12345","buttonDiv","67",12345l / 67l );
    }

private:
    // Helper functions
    void clickButton( Calculator &calc, QString objectName )
    {
        QPushButton *button = calc.findChild<QPushButton*>(objectName);
        QString message = QString("button \"%1\" not found").arg(objectName);
        QVERIFY2( button != 0, message.toUtf8().constData() );

        QTest::mousePress(button,Qt::LeftButton);
        pause();
        QTest::mouseRelease(button,Qt::LeftButton);
        pause();
    }

    void clickNumberString( Calculator &calc, QString numstr )
    {
        foreach( QChar c, numstr ){
            QString objectName("button");
            objectName += c;
            clickButton(calc,objectName);
        }
    }

    void assertDisplay1( Calculator &calc, QString text )
    {
        QLineEdit *display1 = calc.findChild<QLineEdit*>("display1");
        QVERIFY2( display1 != 0, "display1 not found." );
        QCOMPARE( display1->text(), text );
    }

    void assertDisplay2( Calculator &calc, QString text )
    {
        QLineEdit *display2 = calc.findChild<QLineEdit*>("display2");
        QVERIFY2( display2 != 0, "display2 not found." );
        QCOMPARE( display2->text(), text );
    }

    void assertOperator( Calculator &calc, QString objectName )
    {
        clickButton( calc, "button1" );
        clickButton( calc, "button2" );
        clickButton( calc, "button3" );
        clickButton( calc, objectName );

        QPushButton *button = calc.findChild<QPushButton*>(objectName);
        QString expectedStr("123 ");
        expectedStr.append(button->text());
        assertDisplay1( calc, expectedStr );
        assertDisplay2( calc, QString("") );
    }

    void assertNumberAfterOperator( Calculator &calc, QString objectName )
    {
        clickButton( calc, "button1" );
        clickButton( calc, "button2" );
        clickButton( calc, "button3" );
        clickButton( calc, "button4" );
        clickButton( calc, "button5" );
        clickButton( calc, objectName );
        clickButton( calc, "button6" );
        clickButton( calc, "button7" );

        QPushButton *button = calc.findChild<QPushButton*>(objectName);
        QString expectedStr("12345 ");
        expectedStr.append(button->text());

        assertDisplay1( calc, expectedStr );
        assertDisplay2( calc, QString("67") );
    }

    void assertCalculation(
            Calculator &calc,
            QString operand1,
            QString operatorButton,
            QString operand2,
            long answer )
    {
        clickNumberString(calc,operand1);
        clickButton( calc, operatorButton );
        clickNumberString(calc,operand2);
        clickButton( calc, "buttonEqual" );

        assertDisplay1( calc, QString::number(answer) );
        assertDisplay2( calc, QString("") );
    }

    void pause()
    {
        QTest::qWait( 200 );
    }
};

QTEST_MAIN(CalcLib009Test)

#include "tst_calclib009test.moc"
