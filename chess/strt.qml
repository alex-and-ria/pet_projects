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
            id: stop_b
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.5/6
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.1
            width: parent.width/3
            height: parent.height*0.8
            text: "stop";
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    //Qt.quit();
                    grido.init_new()
                    ldr.source="new_main.qml"
                }
            }
        }
        Button{
            id: save_btn
            anchors.left: parent.left
            anchors.leftMargin: parent.width*3.5/6
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.1
            width: parent.width/3
            height: parent.height*0.8
            text: "save";
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    //ldr.source="strt.qml"
                    grido.save_curr()
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
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.row: index/8
                Layout.column: index%8
                Image {
                    property int rowmode: (index/8)%2//index/8 -- row; index%8 -- column;
                    anchors.fill: parent
                    source: cellim[(rowmode+index+1)%2].path

                }
                Image {
                    id: figelem
                    anchors.fill: parent
                    property int isfig: grido.get_im_index(index/8,index%8);
                    source: (isfig<0)?"":fig_im[isfig].path
                    MouseArea{
                        anchors.fill: parent
                        //drag.target: parent
                        onClicked:{
                            grido.pressed_area(index)
                            console.log("pressed ", index)
                            console.log("allow move on ",index," =",grido.allow_mv)
                            console.log("com_cnt= ",grido.com_cnt," internal=",internal_cnt)
                            var cnt_tmp=grido.com_cnt;
                            if(cnt_tmp%2==1
                                    &&cnt_tmp!=internal_cnt){
                                figelem.source="";
                                internal_cnt=cnt_tmp;
                                //grido.com_cnt+=1;
                            }
                            else{
                                var tmpinex=grido.get_im_index(index/8,index%8)
                                figelem.source=fig_im[tmpinex].path;
                                internal_cnt=cnt_tmp;
                            }
                        }
                    }
                    /*states: [
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
                    ]*/
                }
                /*Text {
                    id: txt_m
                    text: qsTr(Number(index).toLocaleString(Qt.locale("en_US"),'f',0))
                }*/
            }
        }
    }
}
