#include "data_vars.h"

data_vars::data_vars(QString p_nm, double *p_val, double lbnd, double tbnd, QString p_units, QObject* parent):
    m_param_nm(p_nm), m_param_val(*p_val),pm_param_val(p_val), m_l_bound(lbnd), m_t_bound(tbnd), m_param_units(p_units){
    Q_UNUSED(parent);
    pm_param_val=new double; pm_param_val=p_val;
}

QString data_vars::param_nm() const{
    return m_param_nm;
}
double data_vars::param_val() const{
    return *pm_param_val;
}
double data_vars::l_bound() const{
    return m_l_bound;
}
double data_vars::t_bound() const{
    return m_t_bound;
}
QString data_vars::param_units() const{
    return m_param_units;
}
void data_vars::setParam_val(const double n_param_val){
    if(n_param_val!=*pm_param_val){
        qDebug()<<Q_FUNC_INFO<<" m_param_val="<<*pm_param_val;
        *pm_param_val=n_param_val; m_param_val=n_param_val;
        emit param_valChanged();
    }
}

data_vars::~data_vars(){
    delete pm_param_val;
}
