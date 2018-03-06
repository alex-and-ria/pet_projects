import QtQuick 2.0

Item {
    Rectangle {
        width: parent.width
        height: parent.width
        color: "navy";
        Text {
            anchors.centerIn: parent
            text: "Page 1"
        }

        MouseArea{
            anchors.fill: parent;
            onClicked: ldr.source="";
        }
    }
}
