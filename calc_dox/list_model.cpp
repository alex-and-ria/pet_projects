#include "list_model.h"

list_model::list_model(unsigned int num_points, QObject *parent):
    QAbstractListModel(parent), m_num_points(num_points){}

void list_model::add_pnt(const QPointF &pnt, bool is_strt){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    if(is_strt){
        m_pnts.clear();
        endInsertRows();
        return;
    }
    m_pnts<<pnt;
    endInsertRows();
}

void list_model::set_bnds(){
    if(!m_pnts.size()){
        qWarning()<<"m_pnts.size()==0";
        return;
    }
    double tmpxmin,tmpxmax,tmpymin,tmpymax;
    tmpxmin=tmpxmax=m_pnts.at(0).x(); tmpymin=tmpymax=m_pnts.at(0).y();
    for(unsigned int i=0;i<(unsigned int)m_pnts.size();i++){
        if(m_pnts.at(i).x()<tmpxmin){
            tmpxmin=m_pnts.at(i).x();
        }
        if(m_pnts.at(i).x()>tmpxmax){
            tmpxmax=m_pnts.at(i).x();
        }
        if(m_pnts.at(i).y()<tmpymin){
            tmpymin=m_pnts.at(i).y();
        }
        if(m_pnts.at(i).y()>tmpymax){
            tmpymax=m_pnts.at(i).y();
        }
    }
    m_xmin=tmpxmin; m_xmax=tmpxmax; m_ymin=tmpymin; m_ymax=tmpymax;
    qDebug()<<"bounds: "<<m_xmin<<m_xmax<<m_ymin<<m_ymax;
}

double list_model::xmin() const{
    return m_xmin;
}

double list_model::xmax() const{
    return m_xmax;
}

double list_model::ymin() const{
    return m_ymin;
}

double list_model::ymax() const{
    return m_ymax;
}

int list_model::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return m_num_points;//future m_pnts.size();
}

QVariant list_model::data(const QModelIndex &index, int role) const{
    if(index.row()<0 || index.row()>=m_pnts.size()) return QVariant();
    if(role==Role_x){
        return m_pnts.at(index.row()).x();
    }
    else if(role==Role_y){
        return m_pnts.at(index.row()).y();
    }
    return 10;
}

QHash<int, QByteArray> list_model::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[Role_x]="x_coord";
    roles[Role_y]="y_coord";
    return roles;
}
