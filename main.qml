import QtQuick 2.5
import QtQuick.Window 2.2

import game.ua 1.0

import "logic.js" as Logic

Window {
    id: root
    visible: true
    width: 640
    height: 640
    title: qsTr("Hello World")

    GameModel {
        id: gameModel

        function getImgByType(type) {
            return Logic.images[type]
        }
    }

    property int gameFieldCellSizePx: 64

    property int gameFieldHeight: gameFieldCellSizePx * gameModel.gameFieldRow
    property int gameFieldWidth: gameFieldCellSizePx * gameModel.gameFieldColumn





    Item {

        id: gameField
        width: gameFieldWidth;
        height: gameFieldHeight;

        GridView {
            id: gameBoard
            anchors.fill: parent;
            cellHeight: gameFieldCellSizePx;
            cellWidth: gameFieldCellSizePx;
            model: gameModel;


            clip: false
            /*
            highlight: Rectangle {
                id: qwer
                color: "transparent"
                border.color: Qt.lighter("black")
                border.width: 2

            }*/

            delegate: Rectangle {
                id: currentItem
                height: gameBoard.cellHeight
                width: gameBoard.cellWidth


                color: {
                    if (/*GridView.isCurrentItem &&*/ model.visible) {
                        return "transparent";
                    } else {
                        return "#DBDBDB";
                    }
                }

                Image {
                    height: gameBoard.cellHeight
                    width: gameBoard.cellWidth

                 //   enabled: model.visible
                  //  visible: model.visible

                    source: gameModel.getImgByType(model.type)// : gameModel.getImgByType(9);
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        console.log(model.index);
                        gameBoard.currentIndex = model.index
                        //gameModel.swapItem(0, 0);

                        gameModel.swapItem(10, model.index);
                        gameModel.swapItem(20, model.index);

                        /*

                        var startObjectRow = Logic.findRow(gameBoard.currentIndex, gameModel.gameFieldColumn);
                        var startObjectColumn = Logic.findColumn(gameBoard.currentIndex, gameModel.gameFieldColumn);

                        var finishObjectRow = Logic.findRow(model.index, gameModel.gameFieldColumn);
                        var finishObjectColumn = Logic.findColumn(model.index, gameModel.gameFieldColumn);

                        var checkRow = ((startObjectRow === finishObjectRow + 1 || startObjectRow === finishObjectRow - 1)
                                        && startObjectColumn === finishObjectColumn);

                        var checkColumn = ((startObjectColumn === finishObjectColumn + 1 || startObjectColumn === finishObjectColumn - 1)
                                           && startObjectRow === finishObjectRow);

                        if (checkRow || checkColumn) {
                            gameModel.swapItem(gameBoard.currentIndex, model.index);

                            //currentItem.

                            //gameBoard.currentIndex = -1;
                        }
                        else {
                            gameBoard.currentIndex = model.index
                        }
                        */

                        //gameModel.checkMatch()
                    }
                }

            }

/*
            move: Transition {
                NumberAnimation {
                    properties: "y"
                    easing.type: Easing.InOutBack
                    duration: 10000

                }
            }
*/

            displaced: Transition {
                NumberAnimation { properties: "opacity"; to: 1.0; duration: 1000}
            }


            move: Transition {
                SequentialAnimation {
                    PauseAnimation { duration: 200 }
                    NumberAnimation { properties: "x"; duration: 200; }
                    NumberAnimation { easing.amplitude: 0.8; properties: "y"; duration: 800; easing.type: Easing.OutBounce }
                }
            }


            remove: Transition {
                NumberAnimation {
                    properties: "opacity"
                    from: 0
                    to: 1.0
                    duration: 1000
                    easing {
                        type: Easing.OutInBounce;
                        overshoot: 500
                    }
                }
            }

            /*
            add: Transition {
                NumberAnimation {


                    properties: "opacity"
                    from: 0
                    to: 1.0
                    duration: 5000
                    easing {
                        type: Easing.OutInBounce;
                        overshoot: 2500
                    }

                    /*
                    properties: "opacity"
                    from: 0
                    to: 1.0
                    duration: 1500
                    easing {type: Easing.Linear; overshoot: 200 }
                }
            }
                    */

            Component.onCompleted: {
                //gameModel.checkMatch()
            }
        }
    }
}
