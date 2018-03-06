#include "figure.h"

figure::figure(unsigned int p_mvsz,Fcolour p_clr,Ftype p_type,
               bool p_jump,unsigned int p_pos,QObject *parent) :
        QObject(parent),id(p_type),clr(p_clr),jump(p_jump),init_pos(p_pos){
    mvsz=p_mvsz;
    cells_go=new int [mvsz];
    is_first=true;
}

figure::~figure(){
    delete[] cells_go;
}

void figure::fill_go(unsigned int pos){
    posx=pos/8;
    posy=pos%8;
}

void figure::set_clr_pos(Fcolour colour,unsigned int p_pos){
    clr=colour; init_pos=p_pos;
    posx=p_pos/8;
    posy=p_pos%8;
    //emit set_on_grd(id,clr,init_pos);
    //qDebug()<<"\nfigure emited set_clr_pos";
}

void figure::set_id(Ftype p_type){
    id=p_type;
}

figure::Ftype figure::get_id() const{
    return id;
}

void figure::set_clr(Fcolour p_clr){
    clr=p_clr;
}

figure::Fcolour figure::get_clr() const{
    return clr;
}

unsigned int figure::get_mvsz() const{
    return mvsz;
}

unsigned int figure::get_posx() const{
    return posx;
}

unsigned int figure::get_posy() const{
    return posy;
}

void figure::set_is_first(bool p_is_first){
    is_first=p_is_first;
}

bool figure::get_is_first() const{
    return is_first;
}
