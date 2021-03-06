import QtQuick 2.0

QtObject {

    property int maxColumn: 0
    property int maxRow: 0
    property int blockSize: 0
    property var gameCanvas: null

    property int maxIndex: 0
    property var board: null
    property var block: null

    property int fillFound: 0
    property var fillBoard: null

    property int  score: 0
    property bool gameOver: false
    property int bonusPoint: 500

    function index( column, row )
    {
        return column + (row * maxColumn)
    }

    function startNewGame( canvas, nColumn, nRow, blSize )
    {
        if( board != null ){
            for( var i = 0; i < maxIndex; i++ ){
                if( board[i] != null ){
                    board[i].destroy()
                    board[i] = null
                }
            }
        }

        maxColumn = nColumn
        maxRow = nRow
        blockSize = blSize
        gameCanvas = canvas

        maxIndex = nColumn * nRow

        board = new Array(maxIndex)
        for( var column = 0; column < maxColumn; column++ ){
            for( var row = 0; row < maxRow; row++ ){
                board[index(column,row)] = createBlock( column, row )
            }
        }

        score = 0
        gameOver = false
    }

    function createBlock( column, row )
    {
        if( block == null ){
            block = Qt.createComponent("Block.qml")
        }
        if( block.status == Component.Ready ){
            var blockObject = block.createObject( gameCanvas )
            if( blockObject != null ){
                blockObject.type = Math.floor( Math.random() * 3 )
                blockObject.x = blockSize * column
                blockObject.y = blockSize * row
                blockObject.width = blockSize
                blockObject.height = blockSize
                blockObject.spawned = true
                return blockObject
            }
            else{
                console.log( "error creating Block" )
                console.log( block.errorString() )
                return null
            }
        }
        else{
            console.log( "error loading Block component" )
            console.log( block.errorString() )
            return null
        }
    }

    function handleClick( xPos, yPos )
    {
        if( gameOver )
            return
        var column = Math.floor( xPos / blockSize )
        var row = Math.floor( yPos / blockSize )
        if( (column < 0) || (maxColumn <= column) || (row < 0 ) || (maxRow <= row) )
            return
        if(board[index(column,row)] == null)
            return;

        fillFound = 0
        fillBoard = new Array(maxIndex)
        floodFill( column, row, board[index(column,row)].type )
        shuffleDown()
        slideLeft()
        score += (fillFound - 1) * (fillFound - 1)
        if( isGameOver() ){
            gameOver = true
            console.log( "Game over !" )
            if( isAllCleared() ){
                score += bonusPoint
                console.log( "bonusPoint = " + bonusPoint )
            }
        }
    }

    function floodFill( column, row, type )
    {
        if( (column < 0) || (maxColumn <= column) || (row < 0) || (maxRow <= row) )
            return
        if( fillBoard[index(column,row)] == 1)
            return
        if( board[index(column,row)] == null )
            return
        if( board[index(column,row)].type != type )
            return
        fillBoard[index(column,row)] = 1
        fillFound += 1

        floodFill( column - 1, row, type )
        floodFill( column + 1, row, type )
        floodFill( column, row - 1, type )
        floodFill( column, row + 1, type )

        if( fillFound > 1 ){
            board[index(column,row)].dying = true
            board[index(column,row)] = null;
        }
    }

    function shuffleDown()
    {
        for( var column = 0; column < maxColumn; column++ ){
            var row = maxRow - 1
            var fallDist = 0;
            while( row >= 0 ){
                for( ; row >= 0 && board[index(column,row)] != null; row -- ){
                    if( fallDist > 0 ){
                        board[index(column,row)].y += blockSize * fallDist
                        board[index(column, row + fallDist)] = board[index(column,row)]
                        board[index(column,row)] = null
                    }
                }
                for( ; row >= 0 && board[index(column,row)] == null; row -- )
                    fallDist ++
            }
        }
    }

    function slideLeft()
    {
        var slideDist = 0
        var column = 0;
        while( column < maxColumn ){
            for( ; column < maxColumn && board[index(column,maxRow-1)] != null; column++ ){
                if( slideDist > 0 ){
                    for( var row = 0; row < maxRow; row++ ){
                        if( board[index(column,row)] != null ){
                            board[index(column,row)].x -= blockSize * slideDist
                            board[index(column - slideDist, row)] = board[index(column,row)]
                            board[index(column,row)] = null
                        }
                    }
                }
            }
            for( ; column < maxColumn && board[index(column,maxRow-1)] == null; column++ )
                slideDist ++
        }
    }

    function isGameOver( column, row, type)
    {
        for( var column = 0; column < maxColumn; column ++ ){
            for( var row = 0; row < maxRow; row ++ ){
                if( board[index(column,row)] != null){
                    var type = board[index(column,row)].type
                    if( isSameType(column-1,row,type) ||
                        isSameType(column+1,row,type) ||
                        isSameType(column,row-1,type) ||
                        isSameType(column,row+1,type) )
                        return false
                }
            }
        }
        return true
    }

    function isSameType( column, row, type )
    {
        if( (column < 0) || (maxColumn <= column) || (row < 0) || (maxRow <= row) )
            return false
        if( board[index(column,row)] == null )
            return false
        return (board[index(column,row)].type == type )
    }

    function isAllCleared()
    {
        return (board[index(0,maxRow-1)] == null)
    }
}


