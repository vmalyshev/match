import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

import game.ua 1.0

import "logic.js" as Logic

Window {
    id: root
    visible: true
    width: 640
    height: 640
    title: qsTr("Match-3 GAME")

    GameModel {
        id: gameModel

        function getImgByType(type) {
            return Logic.images[type]
        }

        onPlayerWon: {
            console.log("you win");
        }

        onPlayerLost: {
            console.log("you lose");
        }
    }

    property int gameFieldCellSizePx: 64

    property int gameFieldHeight: gameFieldCellSizePx * gameModel.gameFieldRow
    property int gameFieldWidth: gameFieldCellSizePx * gameModel.gameFieldColumn

    Item {
        id: gameField
        y: -gameFieldCellSizePx

        width: gameFieldWidth
        height: gameFieldHeight

        GridView {
            id: gameBoard
            anchors.fill: parent;
            cellHeight: gameFieldCellSizePx
            cellWidth: gameFieldCellSizePx
            model: gameModel;
            interactive: false

            delegate: Rectangle {
                height: gameBoard.cellHeight
                width: gameBoard.cellWidth

                color: {
                    if (GridView.isCurrentItem && model.type) {
                        return "#DBDBDB";
                    } else {
                        return "transparent";
                    }
                }

                Image {
                    height: gameBoard.cellHeight
                    width: gameBoard.cellWidth
                    source: gameModel.getImgByType(model.type)
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        console.log(model.index);
                        //gameBoard.currentIndex = model.index

                        //gameModel.swapItem(model.index, model.index);

                 //       gameModel.swapItem(model.index, model.index);

//                        gameModel.swapItem(29 - gameModel.gameFieldColumn, model.index);
//                        gameModel.swapItem(29, model.index);

                        //gameModel.swapItem(model.index, model.index);




                        gameModel.checkMatch()


/*
                        var startObjectRow = Logic.findRow(gameBoard.currentIndex, gameModel.gameFieldColumn);
                        var startObjectColumn = Logic.findColumn(gameBoard.currentIndex, gameModel.gameFieldColumn);

                        var finishObjectRow = Logic.findRow(model.index, gameModel.gameFieldColumn);
                        var finishObjectColumn = Logic.findColumn(model.index, gameModel.gameFieldColumn);

                        var checkRow = ((startObjectRow + 1 === finishObjectRow) || (startObjectRow - 1 === finishObjectRow))
                                && (startObjectColumn === finishObjectColumn);

                        var checkColumn = ((startObjectColumn + 1 === finishObjectColumn) || (startObjectColumn - 1 === finishObjectColumn))
                                && (startObjectRow === finishObjectRow);

                        console.log(checkRow + " " + checkColumn)

                        if ((checkRow || checkColumn) && (model.index >= gameModel.gameFieldColumn) && (gameBoard.currentIndex >= gameModel.gameFieldColumn)) {
                            gameModel.swapItem(gameBoard.currentIndex, model.index);
                            gameModel.checkMatch();
                            gameBoard.currentIndex = 0;
                        } else {
                            gameBoard.currentIndex = model.index
                       }
                       */
                    }
                }

            }


        move: Transition {
            SequentialAnimation {
                NumberAnimation {
                    properties: "y"
                    easing.type: Easing.OutBounce
                    duration: 100
                    easing.amplitude: 0.1;
                }
            }
            //PauseAnimation { duration: 500 }

        }


/*
            move: Transition {
                SequentialAnimation {
                    PauseAnimation { duration: 200 }
                    //NumberAnimation { properties: "x"; duration: 200; }
                    NumberAnimation { easing.amplitude: 0.8; properties: "y"; duration: 800; easing.type: Easing.OutBounce }
                }
            }

*/
            remove: Transition {
                SequentialAnimation {
                    NumberAnimation {
                        properties: "opacity"
                        from: 0
                        to: 1.0
                        duration: 100
                        easing {
                            type: Easing.OutBounce;
                            overshoot: 50
                        }
                    }
                }
            }

            add: Transition {
                NumberAnimation {
                    properties: "opacity"
                    from: 0
                    to: 1
                    duration: 100
                    easing {
                        type: Easing.OutBounce;
                        overshoot: 50
                    }
                }
            }
        }
    }

    ColumnLayout {
        anchors {
            top: parent.top
            left: gameField.right
        }

        Text {
            id: txtScoreLabel
            text: "Total score"
            font.bold: true
            font.pixelSize: 20
        }

        Text {
            id: txtScore
            text: gameModel.gameScore
        }
    }
}
