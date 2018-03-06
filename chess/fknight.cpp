#include "fknight.h"

Fknight::Fknight(Fcolour colour,unsigned int p_pos,QObject *parent):
        figure(8,colour,knightt,true,p_pos,parent){
    //mvsz=8: knight can move on 8 cells in total;
    fill_go(init_pos);
    //qDebug()<<"\nknight constructor: "<<p_pos;
}

Fknight::~Fknight(){

}

void Fknight::fill_go(unsigned int pos){
    //posx=pos/8;
    //posy=pos%8;                              6 - 7
    figure::fill_go(pos);//                5     |       0
    int next_posx=posx, next_posy=posy;//  |---knight ---|
    if((next_posy+2)>7){//                 4     |       1
        cells_go[0]=-1; cells_go[1]=-1;//      3 - 2
    } else if((next_posx-1)<0){
        cells_go[0]=-1; cells_go[1]=(posx+1)*8+posy+2;
    } else if((next_posx+1)>7){
        cells_go[0]=(posx-1)*8+posy+2; cells_go[1]=-1;
    }
    else{
        cells_go[0]=(posx-1)*8+posy+2; cells_go[1]=(posx+1)*8+posy+2;
    }
    if((next_posx+2)>7){
        cells_go[2]=-1; cells_go[3]=-1;
    } else if((next_posy+1)>7){
        cells_go[2]=-1; cells_go[3]=(posx+2)*8+posy-1;
    } else if((next_posy-1)<0){
        cells_go[2]=(posx+2)*8+posy+1; cells_go[3]=-1;
    }
    else{
        cells_go[2]=(posx+2)*8+posy+1; cells_go[3]=(posx+2)*8+posy-1;
    }
    if((next_posy-2)<0){
        cells_go[4]=-1; cells_go[5]=-1;
    } else if((next_posx+1)>7){
        cells_go[4]=-1; cells_go[5]=(posx-1)*8+posy-2;
    } else if((next_posx-1)<0){
        cells_go[4]=(posx+1)*8+posy-2; cells_go[5]=-1;
    }
    else{
        cells_go[4]=(posx+1)*8+posy-2; cells_go[5]=(posx-1)*8+posy-2;
    }
    if((next_posx-2)<0){
        cells_go[6]=-1; cells_go[7]=-1;
    } else if((next_posy-1)<0){
        cells_go[6]=-1; cells_go[7]=(posx-2)*8+posy+1;
    } else if((next_posy+1)>7){
        cells_go[6]=(posx-2)*8+posy-1; cells_go[7]=-1;
    }
    else{
        cells_go[6]=(posx-2)*8+posy-1; cells_go[7]=(posx-2)*8+posy+1;
    }
}

void Fknight::set_clr_pos(Fcolour colour, unsigned int p_pos){
    figure::set_clr_pos(colour,p_pos);

}
