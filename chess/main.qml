import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "white"

    property var cellim: [
        {"path": "/images/brown.svg"},
        {"path": "/images/white.svg"},
    ]
    property var fig_im: [
        {"path": "/images/black_king.svg"},
        {"path": "/images/black_queen.svg"},
        {"path": "/images/black_rook.svg"},
        {"path": "/images/black_bishop.svg"},
        {"path": "/images/black_knight.svg"},
        {"path": "/images/black_pawn.svg"},

        {"path": "/images/white_king.svg"},
        {"path": "/images/white_queen.svg"},
        {"path": "/images/white_rook.svg"},
        {"path": "/images/white_bishop.svg"},
        {"path": "/images/white_knight.svg"},
        {"path": "/images/white_pawn.svg"}
    ]
    property int internal_cnt: 0

    /*Connections {
        target: grido
        onSendMv: {
            console.log("\nmv=",to_pos)
        }
    }*/


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
                        grido.init_new()
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
                        grido.init_new()
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
                        //property int isfig: grido.get_im_index(index/8,index%8);
                        //source: (isfig<0)?cellim[(rowmode+index)%2].path:fig_im[isfig].path
                    }
                    /*Image {
                        id: figelem
                        property int rowmode: (index/8)%2//index/8 -- row; index%8 -- column;
                        anchors.fill: parent
                        //source: cellim[(rowmode+index)%2].path
                        property int isfig: grido.get_im_index(index/8,index%8);
                        source: (isfig<0)?"/images/transparent.svg":fig_im[isfig].path
                        MouseArea{
                            anchors.fill: parent
                            drag.target: parent
                            onPressed: {
                                grido.pressed_area(index)
                                console.log("pressed ", index)
                                figelem.state == 'clicked' ?
                                            figelem.state = "" : figelem.state = 'clicked';
                            }
                            onReleased: {
                                figelem.state == 'released' ?
                                           figelem.state = "" : figelem.state = 'released';
                            }
                        }
                        states: [
                            State {
                                name: "clicked"
                                when: mouseArea.pressed
                                PropertyChanges { target: modelelem; opacity: 0.5 }
                            },
                            State {
                                name: "released"
                                when: mouseArea.released
                                PropertyChanges { target: modelelem; opacity: 1 }
                            }
                        ]
                    }*/
                    /*Text {
                        id: txt_m
                        text: qsTr(Number(index).toLocaleString(Qt.locale("en_US"),'f',0))
                    }*/
                }
            }
        }
    }
    Loader{
            id:ldr;
            anchors.fill: parent;
        }
/*    Timer {
        id: timer
    }

    function delay(delayTime, cb) {
        timer.interval = delayTime;
        timer.repeat = false;
        timer.triggered.connect(cb);
        timer.start();
    }*/
}
