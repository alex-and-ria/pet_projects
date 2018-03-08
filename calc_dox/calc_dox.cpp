#include "calc_dox.h"

calc_dox::calc_dox(QQmlApplicationEngine* p_engine, QObject* parent){
    Q_UNUSED(parent);
    phims=new double; *phims=0.1;//*qe;//phi metal_semiconductor; 1eV= 1*qV;
    phiF=new double; *phiF=0.7;//*qe;//Fermi level for n-type semiconductor;
    qox=new double; *qox=0;//q_oxide;
    eox=new double; *eox=3.85;//e_oxide;
    esub=new double; *esub=11.7;//e_sub;
    Nsub=new double; *Nsub=1e14;//sm^(-3);
    Vsub=new double; *Vsub=0.1;//V;
    Vth=new double; *Vth=0.7;//V;
    dox=new double; *dox=0;
    qb=new double; *qb=0;
    connect(this,&calc_dox::doxChanged,this,&calc_dox::ondoxCgd);
    set_model();
    for(unsigned int i=0;i<(unsigned int)dataList.size()-1;i++){
        connect(qobject_cast<data_vars*> (dataList.at(i)), &data_vars::param_valChanged,
                this,&calc_dox::calc);
    }
    qml_cntxt=(p_engine->rootContext());
    pm_engine=p_engine;
    num_points=50; m_m_list=new list_model(num_points+1);//from 0 to num_points it is num_points+1 points;
    calc();//uses qml_cntxt->setContextProperty() in ondoxCgd();
    set_points();//uses m_m_list and qml_cntxt->setContextProperty();
    qml_cntxt->setContextProperty("calc", this);
    pm_engine->load(QUrl(QLatin1String("qrc:/main.qml")));
}

void calc_dox::calc(){
    (*dox)=((-(*phims)*qe+2*(*phiF)*qe+(*Vth))*(*eox)*e0)
            /(sqrt(2*qe*(*eox)*e0*(*Nsub))*
              (fabs(-2*(*phiF)*qe+(*Vsub))-
               fabs(-2*(*phiF)*qe)));
    qDebug()<<" calc dox="<<(*dox);
    emit doxChanged(dox);
}

void calc_dox::set_model(/*QList<QObject *> &dataList*/){
    dataList.append(new data_vars("phims",phims,0.1,4,"eV"));
    dataList.append(new data_vars("phiF",phiF,0.7,0.9,"eV"));
    dataList.append(new data_vars("eox",eox,1.0,2000.0,""));
    dataList.append(new data_vars("esub",esub,1.0,2000.0,""));
    dataList.append(new data_vars("Nsub",Nsub,1.e14,1.e16,"sm^(-3)"));
    dataList.append(new data_vars("Vsub",Vsub,0.,10.,"V"));
    qDebug()<<Q_FUNC_INFO<<" dox="<<*dox;
    dataList.append(new data_vars("dox",dox,*dox,*dox,"sm"));
}

void calc_dox::ondoxCgd(double *ndox){
    qDebug()<<Q_FUNC_INFO<<" dox="<<*dox<<"ndox="<<*ndox;
    qml_cntxt->setContextProperty("p_model", QVariant::fromValue(dataList));
}

calc_dox::~calc_dox(){
    delete phims;
    delete phiF;
    delete qox;
    delete eox;
    delete esub;
    delete Nsub;
    delete Vsub;
    delete Vth;
    delete dox;
    delete qb;
}

void calc_dox::set_points(){
    _g1_points.clear();
    m_m_list->add_pnt(QPointF(),true);
    *Vth=0.5;// *Nsub=1e14;
    for(*Nsub=1e14;*Nsub<1e16;*Nsub+=(1e16-1e14)/(num_points+0.0)){
        double d_tmp=(*phims)*qe-2*(*phiF)*qe+((*dox)*
                                               sqrt(fabs(2*qe*(*eox)*e0*(*Nsub)))*
                                               (sqrt(fabs(-2*(*phiF)*qe+(*Vsub)))-sqrt(fabs(-2*(*phiF)*qe)))
                                               )/((*eox)*e0);
        _g1_points.append(*Nsub); _g1_points.append(d_tmp);
    }
    *Vth=0.5; *Nsub=1e14;
    for((*Vsub)=0;(*Vsub)<10;(*Vsub)+=(10-0)/(num_points+0.0)){
        *qb=-sqrt(2*qe*(*esub)*e0*(*Nsub)*fabs((*Vsub)-2*(*phiF)*qe));
        double d_tmp=(*phims)*qe-2*(*phiF)*qe+((*dox)*
            sqrt(fabs(2*qe*(*eox)*e0*(*Nsub)))*
            (sqrt(fabs(-2*(*phiF)*qe+(*Vsub)))-sqrt(fabs(-2*(*phiF)*qe)))
            )/((*eox)*e0);
        m_m_list->add_pnt(QPointF(*Vsub,d_tmp),false);
    }
    m_m_list->set_bnds();
    qml_cntxt->setContextProperty("l_model",m_m_list);
    if(_g1_points.empty())
        qDebug()<<Q_FUNC_INFO<<" empt";
}

QVariantList calc_dox::g1_points() const{
    return _g1_points;
}
