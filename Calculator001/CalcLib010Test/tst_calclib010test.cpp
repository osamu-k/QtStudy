#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QLineEdit>
#include <QMap>
#include <QPushButton>

#include "calculator.h"

class CalcLib009Test : public QObject
{
    Q_OBJECT

public:
    CalcLib009Test(){
        setupButtonNameMap();
    }

private Q_SLOTS:
    void initTestCase(){}
    void cleanupTestCase(){}

    void testCalculatorCanBeShown()
    {
        Calculator calc;
        calc.show();
        QCOMPARE(calc.isVisible(),true);
        pause();

        clickAndAssert(calc,"","","");
    }

    void testCalculatorAcceptsNumber1()
    {
        Calculator calc;
        calc.show();
        pause();

        clickAndAssert(calc,"1","","1");
    }

    void testCalculatorAcceptsNumber1234567890()
    {
        Calculator calc;
        calc.show();
        pause();
        clickAndAssert(calc,"1234567890","","1234567890");
    }

    void testCalculatorIgnoresPrecidingZeros()
    {
        Calculator calc;
        calc.show();
        pause();
        clickAndAssert(calc,"0","","0");
        clickAndAssert(calc,"00","","0");
        clickAndAssert(calc,"000","","0");
    }

    void testCalculatorCalculatesOperatorAdd()
    {
        Calculator calc;
        calc.show();
        pause();

        QString disp2str = QString("12345 %1").arg(Calculator::operatorSymbolAdd);
        clickAndAssert(calc,"12345+", disp2str, "");
        clickAndAssert(calc,"67", disp2str, "67");
        clickAndAssert(calc,"=", QString::number(12345+67), "");
    }

    void testCalculatorCalculatesOperatorSub()
    {
        Calculator calc;
        calc.show();
        pause();

        QString disp2str = QString("12345 %1").arg(Calculator::operatorSymbolSub);
        clickAndAssert(calc,"12345-", disp2str, "");
        clickAndAssert(calc,"67", disp2str, "67");
        clickAndAssert(calc,"=", QString::number(12345-67), "");
    }

    void testCalculatorCalculatesOperatorMul()
    {
        Calculator calc;
        calc.show();
        pause();

        QString disp2str = QString("12345 %1").arg(Calculator::operatorSymbolMul);
        clickAndAssert(calc,"12345*", disp2str, "");
        clickAndAssert(calc,"67", disp2str, "67");
        clickAndAssert(calc,"=", QString::number(12345*67), "");
    }

    void testCalculatorCalculatesOperatorDiv()
    {
        Calculator calc;
        calc.show();
        pause();

        QString disp2str = QString("12345 %1").arg(Calculator::operatorSymbolDiv);
        clickAndAssert(calc,"12345/", disp2str, "");
        clickAndAssert(calc,"67", disp2str, "67");
        clickAndAssert(calc,"=", QString::number(12345/67), "");
    }

    void testCalculatorCalculatesRepeatedOperators()
    {
        Calculator calc;
        calc.show();
        pause();
        clickAndAssert(calc,"123+456+789=",QString::number(123+456+789),"");
    }

    void testCalculatorCalculatesOperatorAddAfterEqual()
    {
        Calculator calc;
        calc.show();
        pause();

        QString disp2str = QString("%1 %2").arg(1+2).arg(Calculator::operatorSymbolAdd);
        clickAndAssert(calc,"1+2=+", disp2str, "");
        clickAndAssert(calc,"3", disp2str, "3");
        clickAndAssert(calc,"=", QString::number(1+2+3), "");
    }

    void testCalculatorAcceptsSign()
    {
        Calculator calc;
        calc.show();
        pause();

        clickAndAssert(calc,"S","","-");
        clickAndAssert(calc,"S","","");
        clickAndAssert(calc,"123","","123");
        clickAndAssert(calc,"S","","-123");
        clickAndAssert(calc,"456","","-123456");
        clickAndAssert(calc,"S","","123456");
    }

    void testCalculatorCalculatesMinusAddPlus()
    {
        Calculator calc;
        calc.show();
        pause();

        QString disp2str = QString("-12345 %1").arg(Calculator::operatorSymbolAdd);
        clickAndAssert(calc,"S12345+", disp2str, "");
        clickAndAssert(calc,"67", disp2str, "67");
        clickAndAssert(calc,"=", QString::number(-12345+67), "");
    }

    void testCalculatorAcceptsClearButton()
    {
        Calculator calc;
        calc.show();
        pause();

        clickAndAssert(calc,"C","","");

        clickAndAssert(calc,"S","","-");
        clickAndAssert(calc,"C","","");

        clickAndAssert(calc,"S123","","-123");
        clickAndAssert(calc,"C","","");

        clickAndAssert(calc,"S123+456=",QString::number(-123+456),"");
        clickAndAssert(calc,"C",QString::number(-123+456),"");

        clickAndAssert(calc,"S789",QString::number(-123+456),"-789");
        clickAndAssert(calc,"C",QString::number(-123+456),"");
    }

    void testCalculatorAcceptsAllClearButton()
    {
        Calculator calc;
        calc.show();
        pause();

        clickAndAssert(calc,"A","","");

        clickAndAssert(calc,"S","","-");
        clickAndAssert(calc,"A","","");

        clickAndAssert(calc,"S123","","-123");
        clickAndAssert(calc,"A","","");

        clickAndAssert(calc,"S123+456=",QString::number(-123+456),"");
        clickAndAssert(calc,"A","","");

        clickAndAssert(calc,"S123+456=S789",QString::number(-123+456),"-789");
        clickAndAssert(calc,"A","","");
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

    QMap<QChar,QString> buttonNameMap;

    void setupButtonNameMap()
    {
        buttonNameMap['0'] = "button0";
        buttonNameMap['1'] = "button1";
        buttonNameMap['2'] = "button2";
        buttonNameMap['3'] = "button3";
        buttonNameMap['4'] = "button4";
        buttonNameMap['5'] = "button5";
        buttonNameMap['6'] = "button6";
        buttonNameMap['7'] = "button7";
        buttonNameMap['8'] = "button8";
        buttonNameMap['9'] = "button9";
        buttonNameMap['+'] = "buttonAdd";
        buttonNameMap['-'] = "buttonSub";
        buttonNameMap['*'] = "buttonMul";
        buttonNameMap['/'] = "buttonDiv";
        buttonNameMap['='] = "buttonEqual";
        buttonNameMap['S'] = "buttonSign";
        buttonNameMap['A'] = "buttonAC";
        buttonNameMap['C'] = "buttonC";
    }

    void clickEncodedString( Calculator &calc, QString numstr )
    {
        foreach( QChar c, numstr ){
            if( buttonNameMap.contains(c) ){
                clickButton(calc,buttonNameMap[c]);
            }
        }
    }

    void clickAndAssert(
        Calculator &calc,
        QString encodedString,
        QString expectedDisplay1,
        QString expectedDisplay2
    )
    {
        clickEncodedString(calc,encodedString);
        assertDisplay1(calc,expectedDisplay1);
        assertDisplay2(calc,expectedDisplay2);
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

    void pause()
    {
        QTest::qWait(50 );
    }
};

QTEST_MAIN(CalcLib009Test)

#include "tst_calclib010test.moc"
