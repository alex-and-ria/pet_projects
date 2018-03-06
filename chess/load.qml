import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    property variant im_indexes: [-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1
        -1,-1,-1,-1,-1,-1,-1,-1
        -1,-1,-1,-1,-1,-1,-1,-1
        -1,-1,-1,-1,-1,-1,-1,-1
        -1,-1,-1,-1,-1,-1,-1,-1
        -1,-1,-1,-1,-1,-1,-1,-1
        -1,-1,-1,-1,-1,-1,-1,-1]
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
            text: "prev";
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var isok=grido.get_new_mv(0); console.log("\ngrido.curr_mv=",grido.curr_mv," grido.top_fms()=",grido.top_fms())
                    console.log(" prev: from:",grido.from,"to:",grido.to," isok",isok)
                    if(isok){
                        var tmpind=((grido.from/8)%2+grido.from%2+1)%2
                        console.log("allitem.im_indexes[grido.from]=",allitem.im_indexes[grido.from])
                        var is_prev=false;
                        var poped_i=-1;
                        var top_val_m1=grido.top_fms()-1;
                        console.log("b: allitem.im_indexes[grido.from]=",
                                    allitem.im_indexes[grido.from]," allitem.im_indexes[grido.to]=",
                                    allitem.im_indexes[grido.to])
                        console.log("\ngrido.curr_mv=",grido.curr_mv," grido.top_fms()=",grido.top_fms())
                        if(grido.curr_mv==top_val_m1){//take previous figure;
                            console.log("==");
                            grido.pop_fms();
                            is_prev=true;
                            poped_i=grido.pop_fs()
                        }
                        g_cell.itemAt(grido.to).imgp=fig_im[allitem.im_indexes[grido.from]].path//set new figure's img;
                        allitem.im_indexes[grido.to]=allitem.im_indexes[grido.from]//set new figure's index
                        if(is_prev){
                            g_cell.itemAt(grido.from).imgp=fig_im[poped_i].path
                        }else{
                            g_cell.itemAt(grido.from).imgp=cellim[Math.floor(tmpind)].path
                        }
                        allitem.im_indexes[grido.from]=poped_i;

                        /*if(allitem.im_indexes[grido.from]<0){
                            allitem.im_indexes[grido.from]=grido.pop_fs();
                            g_cell.itemAt(grido.from).imgp=fig_im[allitem.im_indexes[grido.from]].path//set new figure's img;
                            console.log("allitem.im_indexes[grido.from]=",allitem.im_indexes[grido.from]);
                            delay(250, function(){
                                console.log("here1");
                                g_cell.itemAt(grido.to).imgp=fig_im[allitem.im_indexes[grido.from]].path//set new figure's img;
                                allitem.im_indexes[grido.to]=allitem.im_indexes[grido.from]//set new figure's index
                                g_cell.itemAt(grido.from).imgp=cellim[Math.floor(tmpind)].path
                                allitem.im_indexes[grido.from]=-1
                            })
                        }else{
                            g_cell.itemAt(grido.to).imgp=fig_im[allitem.im_indexes[grido.from]].path//set new figure's img;
                            allitem.im_indexes[grido.to]=allitem.im_indexes[grido.from]//set new figure's index
                            g_cell.itemAt(grido.from).imgp=cellim[Math.floor(tmpind)].path
                            allitem.im_indexes[grido.from]=-1
                       }*/
                    }
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
            text: "next";
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var isok=grido.get_new_mv(1); console.log("\ngrido.curr_mv=",grido.curr_mv," grido.top_fms()=",grido.top_fms())
                    console.log("\n\nnext: from:",grido.from,"to:",grido.to," isok",isok)
                    if(isok){
                        var tmpind=((grido.from/8)%2+grido.from%2+1)%2
                        if(allitem.im_indexes[grido.to]>0){
                            grido.push_ts(allitem.im_indexes[grido.to])
                            grido.push_tms(grido.curr_mv)
                            console.log(grido.curr_mv," in stack");
                        }
                        g_cell.itemAt(grido.to).imgp=fig_im[allitem.im_indexes[grido.from]].path//set new figure's img;
                        allitem.im_indexes[grido.to]=allitem.im_indexes[grido.from]//set new figure's index
                        g_cell.itemAt(grido.from).imgp=cellim[Math.floor(tmpind)].path
                        allitem.im_indexes[grido.from]=-1
                        console.log("a: allitem.im_indexes[grido.from]=",
                                    allitem.im_indexes[grido.from]," allitem.im_indexes[grido.to]=",
                                    allitem.im_indexes[grido.to])
                    }
                }
            }
        }
    }
    GridLayout{
        id: grd
        anchors.topMargin: parent.height*0.1;
        anchors.bottomMargin: parent.height*0.1;
        anchors.fill: parent
        width: parent.width
        height: parent.height*0.8
        rows: 8
        columns: 8
        rowSpacing: 0
        columnSpacing: 0
        Repeater{
            id: g_cell
            model: 8*8
            Rectangle{
                id: modelelem
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.row: index/8
                Layout.column: index%8
                property string imgp: ""
                Image {
                    property int rowmode: (index/8)%2//index/8 -- row; index%8 -- column;
                    anchors.fill: parent
                    source: cellim[(rowmode+index+1)%2].path
                }
                Image {
                    id: figelem
                    anchors.fill: parent
                    property int isfig: grido.get_im_index(index/8,index%8);
                    Component.onCompleted: {
                        allitem.im_indexes[index]=isfig
                    }
                    //source: parent.imgp
                    source: (isfig<0)?"/images/transparent.svg":fig_im[isfig].path
                    MouseArea{
                        anchors.fill: parent
                        onClicked:
                            console.log("allitem.im_indexes[index]=",allitem.im_indexes[index]," isfig=",parent.isfig)
                    }
                }
                Image {
                    id: new_im
                    anchors.fill: parent
                    source: parent.imgp
                }
                /*Text {
                    id: txt_m
                    text: qsTr(Number(index).toLocaleString(Qt.locale("en_US"),'f',0))
                }*/
            }
        }
    }
    Rectangle{
        anchors {
            bottom: parent.bottom
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
                    grido.init_new();
                    for(var i=0;i<8*8;i++){
                        var ntmpind=grido.get_im_index(i/8,i%8)
                        allitem.im_indexes[i]=ntmpind
                        if(ntmpind>=0){
                            //console.log("ntmpind=",ntmpind);
                            g_cell.itemAt(i).imgp=fig_im[Math.floor(ntmpind)].path;
                        }
                        else{
                            var tmpind=((i/8)%2+i%2+1)%2
                            g_cell.itemAt(i).imgp=cellim[Math.floor(tmpind)].path
                        }
                    }
                }
            }
        }
    }

}
