import QtQuick 2.0
import QtQuick.Controls 2.0
import QtCharts 2.2

Item {
    width: 480
    height: 200
    visible: true
    Rectangle{width: parent.width; height: parent.height; color: "white"}//clearing background;
    property var points: 0
    ChartView {
        title: "Vth(Nsub); dox=const"
        objectName: "graph1"
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
            min: getbnd(0,0)
            max: getbnd(1,0)
            tickCount: ((parent.width/100)>2) ? parent.width/100 : 2
        }
        ValueAxis {
            id: axisY
            min: getbnd(0,1);
            max: getbnd(1,1);
            tickCount: ((parent.height/100)>2) ? parent.height/100 : 2
        }
        SplineSeries {
            id: graph_Vth
            objectName: "g1_series"
            name: "Vth"
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
    Component.onCompleted: {
        if(points==0)
            points=calc.g1_points;
        for(var i=0;i<points.length/2;i++){
            console.log(i,' ',points[2*i],' ', points[2*i+1]);
            graph_Vth.append(points[2*i],points[2*i+1]);
        }
    }

    Rectangle{
        id: rectq1
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
        text: "load graph2";
        height: parent*(0.1-2*0.05)
        anchors{
            top:rectq1.bottom
            bottom: parent.bottom
            bottomMargin: parent.height*0.05
            left: parent.left
            leftMargin: parent.width*0.01
        }
        MouseArea{
            anchors.fill: parent
            onClicked:{
                console.log("ldr");
                ldr1.source="q2.qml";
            }
        }
    }
    Loader{
        id:ldr1;
        anchors.fill: parent;
    }
    function getbnd(flmax,flpos){
        if(points==0)
            points=calc.g1_points;
        var retval=points[flpos];
        for(var i=0;i<points.length/2;i++){
            if(flmax&&points[2*i+flpos]>retval){
                retval=points[2*i+flpos];
            }
            else if(!flmax&&points[2*i+flpos]<retval){
                retval=points[2*i+flpos];
            }
            console.log('getbnd ::',i,' ',2*i+flpos,points[2*i+flpos])
        }
        console.log("getbnd: ",retval,' ',flpos)
        return retval;
    }
}
