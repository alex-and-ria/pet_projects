#include "logic.h"

AppCore::AppCore(QObject *parent) : QObject(parent)
{
    val.count = 0;
}

void AppCore::receiveFromQml()
{
    val.count++;
    val.count1=0;
    emit sendToQml(val.count,val.count1);
}

void AppCore::grdslot(int i, int j){
    if(i==1&&j==1){
        emit scc();
        qDebug()<<"\nscc";
    }
    else{
        emit nscc();
        qDebug()<<"\n!nscc";
    }
}
