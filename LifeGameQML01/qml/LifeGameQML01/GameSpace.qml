/****************************************************************************
**
** Copyright (C) 2014 Osamu Kobayashi.
** Contact: osamu-k@arion.ocn.ne.jp
**
** This file may be used under the terms of
** the GNU General Public License version 3.0
** as published by the Free Software Foundation
** http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

import QtQuick 2.0
import LifeGame 1.0

Canvas {
    id: canvas
    property real cellSize: 16
    property string fillStyleOfLife: "rgb(0,255,0)"
    property string fillStyleOfEmptiness: "rgb(255,0,0)"
    property real contentScale: 1.0
    property real contentOffsetX: width / 2
    property real contentOffsetY: height / 2

    property GameModel model: GameModel{
        onCellChanged: {
            canvas.requestPaint();
        }
        onAllChanged: {
            canvas.requestPaint();
        }
    }

    property Timer timer: Timer{
        id: timer
        interval: 1000
        repeat: true
        onTriggered: {
            canvas.model.next()
        }
    }

    function start(){
        timer.start()
    }

    function stop(){
        timer.stop()
    }

    function clear(){
        timer.stop()
        model.clear()
    }

    onPaint: {
        var ctx = getContext( '2d' )
        ctx.save();
        ctx.translate( canvas.contentOffsetX, canvas.contentOffsetY )
        ctx.scale( canvas.contentScale, canvas.contentScale )

        var canvasWidth = canvas.width / canvas.contentScale
        var canvasHeight = canvas.height / canvas.contentScale
        var offsetX = canvas.contentOffsetX / canvas.contentScale
        var offsetY = canvas.contentOffsetY / canvas.contentScale
        var rowStart = Math.floor( (- offsetY) / canvas.cellSize )
        var rowEnd = Math.ceil( (canvasHeight - offsetY) / canvas.cellSize )
        var columnStart = Math.floor( (- offsetX) / canvas.cellSize )
        var columnEnd = Math.ceil( (canvasWidth - offsetX) / canvas.cellSize )

        ctx.fillStyle = canvas.fillStyleOfEmptiness
        ctx.fillRect( columnStart * canvas.cellSize, rowStart * canvas.cellSize,
                      (columnEnd - columnStart) * canvas.cellSize, (rowEnd - rowStart) * canvas.cellSize )
        ctx.fillStyle = canvas.fillStyleOfLife
        var row, col
        for( row = rowStart; row <= rowEnd; row ++ ){
            for( col = columnStart; col <= columnEnd; col ++ ){
                if( model.isLifeInCell( row, col ) ){
                    ctx.fillRect( col * canvas.cellSize, row * canvas.cellSize, canvas.cellSize, canvas.cellSize )
                }
            }
        }
        ctx.beginPath()
        for( row = rowStart; row <= rowEnd; row ++ ){
            ctx.moveTo( columnStart * canvas.cellSize, row * canvas.cellSize )
            ctx.lineTo( columnEnd * canvas.cellSize, row * canvas.cellSize )
        }
        for( col = columnStart; col <= columnEnd; col ++ ){
            ctx.moveTo( col * canvas.cellSize, rowStart * canvas.cellSize )
            ctx.lineTo( col * canvas.cellSize, rowEnd * canvas.cellSize )
        }
        ctx.stroke()

        ctx.restore();
    }

    PinchArea{
        anchors.fill: parent
        onPinchStarted: {
        }
        onPinchUpdated: {
            canvas.contentScale *= (pinch.scale / pinch.previousScale)
            canvas.contentOffsetX += (pinch.center.x - pinch.previousCenter.x)
            canvas.contentOffsetY += (pinch.center.y - pinch.previousCenter.y)
            canvas.requestPaint()
        }
        onPinchFinished: {
            canvas.contentScale *= (pinch.scale / pinch.previousScale)
            canvas.contentOffsetX += (pinch.center.x - pinch.previousCenter.x)
            canvas.contentOffsetY += (pinch.center.y - pinch.previousCenter.y)
            canvas.requestPaint()
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                var row = Math.floor( (mouse.y - canvas.contentOffsetY) / canvas.cellSize / canvas.contentScale )
                var col = Math.floor( (mouse.x - canvas.contentOffsetX) / canvas.cellSize / canvas.contentScale )
                model.invertCellState( row, col );
            }
        }
    }

}
