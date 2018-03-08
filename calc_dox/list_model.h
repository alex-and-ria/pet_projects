#ifndef LIST_MODEL_H
#define LIST_MODEL_H
#include <QAbstractListModel>
#include <QPointF>
#include <QDebug>

class list_model:public QAbstractListModel{
    Q_OBJECT
    Q_PROPERTY(double xmin READ xmin)
    Q_PROPERTY(double xmax READ xmax)
    Q_PROPERTY(double ymin READ ymin)
    Q_PROPERTY(double ymax READ ymax)
public:
    enum coord_roles{
        Role_x=Qt::UserRole+1,
        Role_y
    };
    list_model(unsigned int num_points,QObject* parent=0);
    ~list_model() {}
    void add_pnt(const QPointF& pnt,bool is_strt);
    void set_bnds();
    double xmin() const;
    double xmax() const;
    double ymin() const;
    double ymax() const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
protected:
    QHash<int,QByteArray> roleNames() const;
private:
    QList<QPointF> m_pnts;
    double m_xmin;
    double m_xmax;
    double m_ymin;
    double m_ymax;
    unsigned int m_num_points;/*as m_pnts dynamicaly changes with add_pnt(), we should know future number of points
    before rowCount() will be called;*/
};

#endif // LIST_MODEL_H
