import QtQuick 2.0

Rectangle {
    id: container
    width: 0
    height: 0
    visible: false

    property string displayString1 : ""
    property string displayString2 : ""

    property bool operatorEnabled : false
    property bool equalEnabled: false

    property int currentValue: 0
    property int currentSign: +1
    property int lastValue: 0

    property var currentOperator: 0
    property var operatorMap: {
        "+": calculateAdd,
        "-": calculateSub,
        "*": calculateMul,
        "/": calculateDiv,
    }

    state: "WAITING_VALUE1"
    states: [
        State{
            name: "WAITING_VALUE1"
        },
        State{
            name: "READING_VALUE1"
            PropertyChanges {
                target: container
                operatorEnabled: true
            }
        },
        State{
            name: "WAITING_VALUE2"
        },
        State{
            name: "READING_VALUE2"
            PropertyChanges {
                target: container
                operatorEnabled: true
                equalEnabled: true
            }
        },
        State{
            name: "SHOWING_ANSWER"
            PropertyChanges {
                target: container
                operatorEnabled: true
            }
        },
        State{
            name: "READING_VALUE1_SHOWING_ANSWER"
            PropertyChanges {
                target: container
                operatorEnabled: true
            }
        }
    ]

    function addDigit( digit )
    {
        switch(state){
        case "WAITING_VALUE1":
            addDigitToCurrentValue( digit );
            state = "READING_VALUE1";
            break;
        case "READING_VALUE1":
            addDigitToCurrentValue( digit );
            break;
        case "WAITING_VALUE2":
            addDigitToCurrentValue( digit );
            state = "READING_VALUE2";
            break;
        case "READING_VALUE2":
            addDigitToCurrentValue( digit );
            break;
        case "SHOWING_ANSWER":
            addDigitToCurrentValue( digit );
            state = "READING_VALUE1_SHOWING_ANSWER";
            break;
        case "READING_VALUE1_SHOWING_ANSWER":
            addDigitToCurrentValue( digit );
            break;
        default:
            break;
        }
    }

    function addDigitToCurrentValue( digit )
    {
        currentValue *= 10
        currentValue += digit
        showCurrentValue();
    }

    function showCurrentValue()
    {
        displayString2 = "" + currentSign * currentValue
    }

    function setOperator( operator )
    {
        console.log( "setOperator called ! state = " + state )
        switch(state){
        case "WAITING_VALUE1":
            break;
        case "READING_VALUE1":
            storeCurrentValue();
            storeOperator( operator );
            state = "WAITING_VALUE2";
            break;
        case "WAITING_VALUE2":
            break;
        case "READING_VALUE2":
            if( calculateOperator() ){
                storeOperator( operator );
                state = "WAITING_VALUE2";
            }
            break;
        case "SHOWING_ANSWER":
            storeOperator( operator );
            state = "WAITING_VALUE2";
            break;
        case "READING_VALUE1_SHOWING_ANSWER":
            storeCurrentValue();
            storeOperator( operator );
            state = "WAITING_VALUE2";
            break;
        default:
            break;
        }
    }

    function storeCurrentValue()
    {
        lastValue = currentValue * currentSign
        showLastValue()
        clearCurrentValue()
    }

    function storeOperator(operator)
    {
        displayString1 = displayString1 + " " + operator
        currentOperator = operatorMap[operator]
        clearCurrentValue()
    }

    function calculateAdd()
    {
        console.log( "function calculateAdd called" )
        lastValue = lastValue + (currentValue * currentSign)
        return true
    }

    function calculateSub()
    {
        console.log( "function calculateSub called" )
        lastValue = lastValue - (currentValue * currentSign)
        return true
    }

    function calculateMul()
    {
        console.log( "function calculateMul called" )
        lastValue = lastValue * (currentValue * currentSign)
        return true
    }

    function calculateDiv()
    {
        console.log( "function calculateDiv called" )
        if( currentValue != 0 ){
            lastValue = lastValue / (currentValue * currentSign)
            return true
        }
        else{
            return false;
        }
    }

    function calculate()
    {
        console.log( "calculate called !" )
        switch(state){
        case "WAITING_VALUE1":
            break;
        case "READING_VALUE1":
            break;
        case "WAITING_VALUE2":
            break;
        case "READING_VALUE2":
            if( calculateOperator() ){
                state = "SHOWING_ANSWER";
            }
            break;
        case "SHOWING_ANSWER":
            break;
        case "READING_VALUE1_SHOWING_ANSWER":
            break;
        default:
            break;
        }
    }

    function calculateOperator()
    {
        if( currentOperator() ){
            showLastValue();
            clearCurrentValue();
            return true;
        }
        return false;
    }

    function changeSign()
    {
        currentSign *= -1
        showCurrentValue();
    }

    function clear()
    {
        switch(state){
        case "WAITING_VALUE1":
            clearCurrentValue()
            break;
        case "READING_VALUE1":
            clearCurrentValue()
            state = "WAITING_VALUE1"
            break;
        case "WAITING_VALUE2":
            clearCurrentValue()
            break;
        case "READING_VALUE2":
            clearCurrentValue();
            state = "WAITING_VALUE2";
            break;
        case "SHOWING_ANSWER":
            clearCurrentValue();
            break;
        case "READING_VALUE1_SHOWING_ANSWER":
            clearCurrentValue();
            state = "SHOWING_ANSWER";
            break;
        default:
            break;
        }
    }

    function clearAll()
    {
        lastValue = 0;
        currentOperator = 0;
        displayString1 = "";
        clearCurrentValue();
        state = "WAITING_VALUE1";
    }

    function clearCurrentValue()
    {
        currentValue = 0
        currentSign = +1
        displayString2 = "";
    }

    function showLastValue()
    {
        displayString1 = "" + lastValue
    }
}
