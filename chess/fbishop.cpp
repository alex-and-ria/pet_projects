#include "fbishop.h"

Fbishop::Fbishop(Fcolour colour,unsigned int p_pos,QObject *parent):
        figure(14,colour,bishopt,false,p_pos,parent){
    //mvsz=14: bishop can move on all cells in four directions; maximum -- 14 cells;
    fill_go(init_pos);
    //qDebug()<<"\nbishop constructor: "<<p_pos;
}

Fbishop::~Fbishop(){

}

void Fbishop::fill_go(unsigned int pos){
    //posx=pos/8;
    //posy=pos%8;
    figure::fill_go(pos);
    int next_posy=posx; int next_posx=posy; unsigned int cnt=0;
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

void Fbishop::set_clr_pos(Fcolour colour, unsigned int p_pos){
    figure::set_clr_pos(colour,p_pos);

}
