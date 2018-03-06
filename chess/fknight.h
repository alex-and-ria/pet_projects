#ifndef FKNIGHT_H
#define FKNIGHT_H

#include "figure.h"

class Fknight: public figure
{
    Q_OBJECT
public:
    Fknight(Fcolour colour=Fwhite,unsigned int p_pos=0,QObject *parent = 0);
    ~Fknight();
    void fill_go(unsigned int pos);
    void set_clr_pos(Fcolour colour,unsigned int p_pos);
};

#endif // FKNIGHT_H
