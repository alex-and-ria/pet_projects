#include "fqueen.h"

Fqueen::Fqueen(Fcolour colour,QObject *parent):
        figure(28,colour,queent,false,0,parent){
    //mvsz=28: queen can move on all cells in 8 directions; maximum -- 28 cells;
    if(colour==Fwhite){
        init_pos=59;
    }
    else init_pos=3;
    fill_go(init_pos);
    emit figure::set_on_grd(queent,colour,init_pos);
    //qDebug()<<"\nqueen constructor: "<<init_pos;
}

Fqueen::~Fqueen(){

}

void Fqueen::fill_go(unsigned int pos){
    //posx=pos/8;
    //posy=pos%8;
    figure::fill_go(pos);
    bool whiteb=true;
    if(clr==Fblack){
        whiteb=false;// posx=7-posx;
    }
    int next_posy=0; unsigned int cnt=0;
    for(usi i=0;i<7;i++,cnt++){//horisontal;
        if(next_posy!=posy){
            if(whiteb) cells_go[cnt]=posx*8+next_posy;
            else cells_go[cnt]=posx*8+next_posy;
            next_posy++;
        }
        else{
            i--; cnt--; next_posy++;
        }
    }
    int next_posx=0;
    for(usi i=0;i<7;i++,cnt++){//vertical;
        if(next_posx!=posx){
            cells_go[cnt]=next_posx*8+posy;
            next_posx++;
        }
        else{
            i--; cnt--; next_posx++;
        }
    }
    next_posx=posx; next_posy=posy;
    while (next_posx!=7&&next_posy!=0) {
        ++next_posx; --next_posy;
    }
    for(usi i=0;i<7&&next_posx>=0&&next_posy<=7;i++,cnt++){//diagonal: left-right;
        if(next_posx!=posx&&next_posy!=posy){
            cells_go[cnt]=next_posx*8+next_posy;
            next_posx--; next_posy++;
        }
        else{
            i--; cnt--; next_posx--; next_posy++;
        }
    }
    next_posx=posx; next_posy=posy;
    while (next_posx!=7&&next_posy!=7) {
        ++next_posx; ++next_posy;
    }
    for(usi i=0;i<7&&next_posx>=0&&next_posy>=0;i++,cnt++){
        if(next_posx!=posx&&next_posy!=posy){
            cells_go[cnt]=next_posx*8+next_posy;
            next_posx--; next_posy--;
        }
        else{
            i--; cnt--; next_posx--; next_posy--;
        }
    }
    for(unsigned int i=cnt;i<mvsz;i++){
        cells_go[i]=-1;
    }
}
