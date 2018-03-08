#ifndef DATA_VARS_H
#define DATA_VARS_H

#include <QObject>
#include <QDebug>

class data_vars : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString param_nm READ param_nm CONSTANT)
    Q_PROPERTY(double param_val READ param_val WRITE setParam_val NOTIFY param_valChanged)
    Q_PROPERTY(double l_bound READ l_bound CONSTANT)
    Q_PROPERTY(double t_bound READ t_bound CONSTANT)
    Q_PROPERTY(QString param_units READ param_units CONSTANT)

public:
    data_vars(QString p_nm, double* p_val, double lbnd, double tbnd, QString p_units, QObject* parent=0);
    ~data_vars();
    QString param_nm() const;
    double param_val() const;
    double l_bound() const;
    double t_bound() const;
    QString param_units() const;
    void setParam_val(const double n_param_val);

signals:
    void param_valChanged();

private:
    QString m_param_nm;
    double m_param_val;
    double* pm_param_val;
    double m_l_bound;
    double m_t_bound;
    QString m_param_units;
};


#endif // DATA_VARS_H
