import QtQuick 2.0
import QtQuick.Controls 2.0
import QtCharts 2.2

Item {
    width: 480
    height: 200
    visible: true
    Rectangle{width: parent.width; height: parent.height; color: "white"}//clearing background;
    property var lst_model: l_model
    property int cnt: 0
    ChartView {
        title: "Vth(Vsub); dox=const"
        objectName: "graph2"
        width: parent.width
        height: parent.height*0.8
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 0
        anchors.leftMargin: 0
        antialiasing: true
        legend.alignment: Qt.AlignBottom
        ValueAxis {
            id: axisX
            min: lst_model.xmin
            max: lst_model.xmax
            tickCount: ((parent.width/100)>2) ? parent.width/100 : 2
            Component.onCompleted: {
                console.log("x: min=",lst_model.xmin,"max=",lst_model.xmax);
                console.log("y: min=",lst_model.ymin,"max=",lst_model.ymax);
            }
        }
        ValueAxis {
            id: axisY
            min: lst_model.ymin
            max: lst_model.ymax
            tickCount: ((parent.height/100)>2) ? parent.height/100 : 2
        }
        SplineSeries {
            id: graph_Vth1
            objectName: "g2_series"
            name: "Vth2"
            axisX: axisX
            axisY: axisY
            onHovered: {
                console.log("onHovered: " + point.x + ", " + point.y, 'st=',state);
                if(state){
                    txtftst.text="coords: x="+point.x+"\ty="+point.y;
                }
            }
        }
    }
    ListView{
        width: 0
        height: 0
        model: l_model
        delegate:
            Rectangle {
                id: hidden_rect
                Component.onCompleted: {
                    console.log(cnt," coords: ",x_coord,' ', y_coord);
                    graph_Vth1.append(x_coord,y_coord);
                    cnt++;
                }
            }
    }
    Rectangle{
        id: rectq2
        width: parent.width
        height: parent.height*0.1;
        anchors{
            bottom: parent.bottom
            bottomMargin: parent.height*0.1
        }
        color: "white"
        Text {
            id: txtftst
            width: parent.width
            height: parent.height
            anchors{
                left: parent.left
                leftMargin: parent.width*0.01
                right: parent.right
                rightMargin: parent.width*0.01
            }
            text: qsTr("move mouse on rendered line to see appropriate coordinates")
        }
    }
    Button {
        text: "load graph1";
        height: parent*(0.1-2*0.05)
        anchors{
            top: rectq2.bottom
            bottom: parent.bottom
            left: parent.left
            //topMargin: parent.height*0.05
            bottomMargin: parent.height*0.05
            leftMargin: parent.width*0.01
        }
        MouseArea{
            anchors.fill: parent
            onClicked:{
                console.log("ldr");
                ldr2.source="q1.qml";
            }
        }
    }
    Loader{
        id:ldr2;
        anchors.fill: parent;
    }
}
