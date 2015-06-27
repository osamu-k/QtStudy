.import QtQuick.LocalStorage 2.0 as Sql
.import QtQuick 2.0 as Quick

var maxColumn = 10
var maxRow = 15
var maxIndex = maxColumn * maxRow
var board = new Array(maxIndex)
var component
var scoresURL = ""
var gameDuration

function index(column,row){
    return column + (row * maxColumn)
}

function startNewGame() {
    console.log( "New game startd" );

    for(var i = 0; i < maxIndex; i++){
        if(board[i] != null)
            board[i].destroy()
    }

    maxColumn = Math.floor(gameCanvas.width / gameCanvas.blockSize)
    maxRow = Math.floor(gameCanvas.height / gameCanvas.blockSize)
    maxIndex = maxColumn * maxRow

    nameInputDialog.hide()
    dialog.hide()

    board = new Array(maxIndex)
    for( var column = 0; column < maxColumn; column++ ){
        for( var row = 0; row < maxRow; row++ ){
            board[index(column,row)] = null;
            createBlock(column,row)
        }
    }

    gameCanvas.score = 0
    gameDuration = new Date()
}

function createBlock(column,row)
{
    console.log( "Creating block (" + column + "," + row + ")" );

    if(component == null){
        component = Qt.createComponent("Block.qml")
    }
    if(component.status == Quick.Component.Ready){
        var dynamicObject = component.createObject(gameCanvas)
        if(dynamicObject == null){
            console.log("error creating block")
            console.log(component.errorString())
            return false
        }
        dynamicObject.spawned = true
        dynamicObject.type = Math.floor(Math.random()*3)
        dynamicObject.x = gameCanvas.blockSize * column
        dynamicObject.y = gameCanvas.blockSize * row
        dynamicObject.width = gameCanvas.blockSize
        dynamicObject.height = gameCanvas.blockSize
        board[index(column,row)] = dynamicObject
        console.log( "Block (" + column + "," + row + ") created on ("
                     + dynamicObject.x + ","
                     + dynamicObject.y + ","
                     + dynamicObject.width + ","
                     + dynamicObject.height + ")" );
    }
    else{
        console.log("error loading block compomemt")
        console.log(component.errorString())
        return false
    }
    return true
}

var fillFound
var floodBoard

function handleClick(xPos,yPos)
{
    var column = Math.floor(xPos / gameCanvas.blockSize)
    var row = Math.floor(yPos / gameCanvas.blockSize)
    if(column < 0 || maxColumn <= column || row < 0 || maxRow <= row)
        return
    if(board[index(column,row)] == null)
        return
    floodFill(column,row,-1)
    if(fillFound <= 0)
        return
    gameCanvas.score += (fillFound - 1) * (fillFound - 1)
    shuffleDown()
    victoryCheck()
}

function floodFill(column,row,type)
{
    console.log( "floodFill(" + column + "," + row + "," + type + ")" );

    if(board[index(column,row)] == null)
        return
    var first = false
    if(type == -1){
        first = true
        type = board[index(column,row)].type
        fillFound = 0
        floodBoard = new Array(maxIndex)
    }
    if(column < 0 || maxColumn <= column || row < 0 || maxRow <= row)
        return
    if(floodBoard[index(column,row)] == 1)
        return
    if( ! first && type != board[index(column,row)].type)
        return
    floodBoard[index(column,row)] = 1
    floodFill(column-1,row,type)
    floodFill(column+1,row,type)
    floodFill(column,row-1,type)
    floodFill(column,row+1,type)
    if(first && fillFound == 0)
        return
    board[index(column,row)].dying = true
    board[index(column,row)] = null
    fillFound ++
    console.log("fillFound = " + fillFound)
}

function shuffleDown()
{
    for(var column = 0; column < maxColumn; column++){
        var fallDist = 0
        for(var row = maxRow-1; row >= 0; row--){
            if(board[index(column,row)] == null){
                fallDist ++
            }
            else if(fallDist > 0){
                var obj = board[index(column,row)]
                obj.y += fallDist * gameCanvas.blockSize
                board[index(column,row+fallDist)] = obj
                board[index(column,row)] = null
            }
        }
    }

    var fallDist = 0;
    for(var column = 0; column < maxColumn; column++){
        if(board[index(column,maxRow-1)] == null){
            fallDist++
        }
        else if(fallDist > 0){
            for(var row = 0; row < maxRow; row++){
                if(board[index(column,row)] != null){
                    var obj = board[index(column,row)]
                    obj.x -= fallDist * gameCanvas.blockSize
                    board[index(column-fallDist,row)] = obj
                    board[index(column,row)] = null
                }
            }
        }
    }
}

function victoryCheck()
{
    console.log("victoryCheck")
    var deserveBonus = true
    for(var column = maxColumn - 1; column >= 0; column--){
        if(board[index(column,maxRow-1)] != null)
            deserveBonus = false;
    }
    if(deserveBonus){
        gameCanvas.score += 500
    }
    var check = floodMoveCheck(0,maxRow -1, 0)
    console.log("floodCheck = " + check)
    console.log("victoryCheck deserveBonus=" + deserveBonus + " check=" + check)
    if( deserveBonus || ! check ){
        gameDuration = new Date() - gameDuration
        nameInputDialog.showWithInput("You won! Please enter your name: ")
    }
}

function floodMoveCheck(column,row,type)
{
    console.log("floodCheck("+ column + "," + row + "," + type + ")" )
    if(column < 0 || maxColumn <= column || row < 0 || maxRow <= row){
        console.log("floodCheck return 1" )
        return false
    }
    if(board[index(column,row)] == null){
        console.log("floodCheck return 2" )
        return false
    }
    var myType = board[index(column,row)].type
    if( type == myType ){
        console.log("floodCheck return 3" )
        return true
    }
    return floodMoveCheck(column + 1, row, myType) || floodMoveCheck(column, row - 1, myType)
}

function saveHighScore(name)
{
//    if (scoresURL != "")
//        sendHighScore(name);

    var db = Sql.LocalStorage.openDatabaseSync("SameGameScores","1.0","Local SameGame High Scores",100)
    var dataStr = "INSERT INTO Scores VALUES(?,?,?,?)"
    var data = [name, gameCanvas.score, maxColumn + "x" + maxRow, Math.floor(gameDuration / 1000)]
    db.transaction(function(tx) {
        tx.executeSql('CREATE TABLE IF NOT EXISTS Scores(name TEXT, socre NUMBER, gridSize TEXT, time NUMBER)')
        tx.executeSql(dataStr, data);

        var rs = tx.executeSql('SELECT * FROM Scores WHERE gridSize = "12x17" ORDER BY socre desc LIMIT 10')
        var r = "\nHIGH SCORES for a standard sized grid\n\n"
        for( var i = 0; i < rs.rows.length; i++){
            r += (i + 1) + ". " + rs.rows.item(i).name + ' got' + rs.rows.item(i).score + ' points in ' + rs.rows.item(i).time + ' seconds.\n'
        }
        dialog.show(r)
    })

//    if (scoresURL != "")
//        sendHighScore(name);

//    var db = Sql.LocalStorage.openDatabaseSync("SameGameScores", "1.0", "Local SameGame High Scores", 100);
//    var dataStr = "INSERT INTO Scores VALUES(?, ?, ?, ?)";
//    var data = [name, gameCanvas.score, maxColumn + "x" + maxRow, Math.floor(gameDuration / 1000)];
//    db.transaction(function(tx) {
//        tx.executeSql('CREATE TABLE IF NOT EXISTS Scores(name TEXT, score NUMBER, gridSize TEXT, time NUMBER)');
//        tx.executeSql(dataStr, data);

//        var rs = tx.executeSql('SELECT * FROM Scores WHERE gridSize = "12x17" ORDER BY score desc LIMIT 10');
//        var r = "\nHIGH SCORES for a standard sized grid\n\n"
//        for (var i = 0; i < rs.rows.length; i++) {
//            r += (i + 1) + ". " + rs.rows.item(i).name + ' got ' + rs.rows.item(i).score + ' points in ' + rs.rows.item(i).time + ' seconds.\n';
//        }
//        dialog.show(r);
//    });
}
