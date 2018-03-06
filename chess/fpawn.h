#ifndef FPAWN_H
#define FPAWN_H

#include "figure.h"

class Fpawn: public figure
{
    Q_OBJECT
public:
    Fpawn(Fcolour colour=Fwhite,unsigned int p_pos=0,QObject *parent = 0);
    ~Fpawn();
    void fill_go(unsigned int pos);
    void set_clr_pos(Fcolour colour,unsigned int p_pos);

public://private:// setter & getter;
    bool is_qexist;
};

#endif // FPAWN_H
