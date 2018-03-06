import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    id: allitem
    anchors.fill: parent
    Rectangle{
        anchors {
            top: parent.top
            left: parent.left
        }
        width: parent.width
        height: parent.height*0.1
        color: "white"
        Button{
            id: start_b
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.5/6
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.1
            width: parent.width/3
            height: parent.height*0.8

            text: "start";
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    grido.init_new();
                    ldr.source="strt.qml"
                }
            }
        }
        Button{
            id: load_b
            anchors.left: parent.left
            anchors.leftMargin: parent.width*3.5/6
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.1
            width: parent.width/3
            height: parent.height*0.8
            text: "load";
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    grido.load_curr();
                    console.log("load");
                    ldr.source="load.qml"
                }
            }
        }
    }
    GridLayout{
        id: grd
        anchors.topMargin: parent.height*0.1;
        anchors.fill: parent
        rows: 8
        columns: 8
        rowSpacing: 0
        columnSpacing: 0
        Repeater{
            model: 8*8
            Rectangle{
                id: modelelem
                //color:  Qt.rgba(Math.random(),Math.random(),Math.random(),1);
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.row: index/8
                Layout.column: index%8
                Image {
                    property int rowmode: (index/8)%2//index/8 -- row; index%8 -- column;
                    anchors.fill: parent
                    source: cellim[(rowmode+index+1)%2].path
                }
                /*Text {
                    id: txt_m
                    text: qsTr(Number(index).toLocaleString(Qt.locale("en_US"),'f',0))
                }*/
            }
        }
    }
}
