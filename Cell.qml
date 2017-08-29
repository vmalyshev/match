import QtQuick 2.0


Item {
    signal itemSelected(int num);

    MouseArea {
        anchors.fill: parent
        onClicked: {
            itemSelected(model.index);
        }
    }
}
