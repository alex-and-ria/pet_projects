#ifndef FROOK_H
#define FROOK_H

#include "figure.h"

class Frook: public figure
{
    Q_OBJECT
public:
    Frook(Fcolour colour=Fwhite,unsigned int p_pos=0,QObject *parent = 0);
    ~Frook();
    void fill_go(unsigned int pos);
    void set_clr_pos(Fcolour colour,unsigned int p_pos);
};

#endif // FROOK_H
