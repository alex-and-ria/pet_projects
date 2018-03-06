#ifndef FBISHOP_H
#define FBISHOP_H

#include "figure.h"

class Fbishop: public figure
{
    Q_OBJECT
public:
    Fbishop(Fcolour colour=Fwhite,unsigned int p_pos=0,QObject *parent = 0);
    ~Fbishop();
    void fill_go(unsigned int pos);
    void set_clr_pos(Fcolour colour,unsigned int p_pos);
};

#endif // FBISHOP_H
