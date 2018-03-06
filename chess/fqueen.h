#ifndef FQUEEN_H
#define FQUEEN_H

#include "figure.h"

class Fqueen: public figure
{
    Q_OBJECT
public:
    Fqueen(Fcolour colour,QObject *parent = 0);
    ~Fqueen();
    void fill_go(unsigned int pos);
};

#endif // FQUEEN_H
