import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 400
    height: 200
    title: qsTr("rgr")
    ListView{
        id: g_view
        objectName: "mn"
        width: parent.width
        height: parent.height-parent.height*0.1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: parent.height*0.05
        anchors.leftMargin: parent.width*0.01
        interactive: false
        model: p_model
        delegate: Rectangle{
            id: rect
            width: childrenRect.width
            height: childrenRect.height
            Label{
                id: curr_lbl
                text: model.modelData.param_nm+'='
            }
            TextInput{
                id: curr_ti
                anchors.left: curr_lbl.right
                text: model.modelData.param_val;
                validator: DoubleValidator{
                    id: curr_validator
                    bottom: model.modelData.l_bound; top: model.modelData.t_bound
                }
                onEditingFinished: {
                    if(model.modelData.param_nm!="dox"){
                        model.modelData.param_val=curr_ti.text;
                    }
                    else{
                        console.log("qml: dox");
                    }
                    console.log("validator: ",curr_ti.text,"parseFloat(getText(0, 20))=",parseFloat(getText(0, 20)));
                }
            }
            Label{
                anchors.left: curr_ti.right
                text: ' '+model.modelData.param_units
            }
        }
    }

    Button{
        text: "load graph1";
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: parent.height*0.05
        anchors.leftMargin: parent.width*0.1
        MouseArea{
            anchors.fill: parent
            onClicked:{
                console.log("ldr");
                ldr.source="q1.qml";
            }
        }
    }

    Button{
        text: "load graph2";
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: parent.height*0.05
        anchors.rightMargin: parent.width*0.1
        MouseArea{
            anchors.fill: parent
            onClicked:{
                console.log("ldr");
                ldr.source="q2.qml";
            }
        }
    }

    Loader{
        id:ldr;
        anchors.fill: parent;
    }
}
