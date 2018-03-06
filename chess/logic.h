#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QDebug>

class AppCore : public QObject
{
    Q_OBJECT
public:
    explicit AppCore(QObject *parent = 0);
    struct fld{
        int count;
        int count1;
    };

signals:
    // Сигнал для передачи данных в qml-интерфейс
    void sendToQml(int val,int val1);
    void scc();
    void nscc();

public slots:
    // Слот для приёма данных из qml-интерфейса
    void receiveFromQml();
    void grdslot(int i,int j);

private:
    fld val;
};

#endif // LOGIC_H
