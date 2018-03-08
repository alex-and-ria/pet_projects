#ifndef CALC_DOX_H
#define CALC_DOX_H

#include <QObject>
#include <QDebug>
#include <QVariantList>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QChartView>
#include <QPointF>
#include "data_vars.h"
#include "list_model.h"

class calc_dox : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList g1_points READ g1_points)
public:
    calc_dox(QQmlApplicationEngine* p_qml_obj1, QObject* parent=0);
    ~calc_dox();
    void set_model();
    void set_points();
    QVariantList g1_points() const;
signals:
    void doxChanged(double* ch);

public slots:
    void calc();
    void ondoxCgd(double* ndox);

private:
    double e0=8.854*1e-14;//F*sm^(-1);
    double qe=1.602*1e-19;//C;
    double *phims;//def: 0.1*qe;//phi metal_semiconductor; 1eV= 1*qV;
    double *phiF;//def: 0.7*qe;//Fermi level for n-type semiconductor;
    double *qox;//def: 0;//q_oxide;
    double *eox;//def: 3.85;//e_oxide;
    double *esub;//def: 11.7;//e_sub;
    double *Nsub;//def: 10e14;//sm^(-3);
    double *Vsub;//def: 0;//V;
    double *Vth;//def: 0;//V;
    double *dox;//d_oxide;
    double *qb;//q_bulk;
    QQmlContext* qml_cntxt;
    QList<QObject *> dataList;
    QQmlApplicationEngine* pm_engine;
    unsigned int num_points;
    QVariantList _g1_points;
    list_model* m_m_list;
};

#endif // CALC_DOX_H
