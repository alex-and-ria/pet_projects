#include "frook.h"

Frook::Frook(Fcolour colour,unsigned int p_pos,QObject *parent):
        figure(14,colour,rookt,false,p_pos,parent){
    //mvsz=14: rook can move on all cells in 4 directions;
    fill_go(init_pos);
    //qDebug()<<"\nrook constructor: "<<p_pos;
}

Frook::~Frook(){

}

void Frook::fill_go(unsigned int pos){
    //posx=pos/8;
    //posy=pos%8;
    figure::fill_go(pos);
    int next_posy=0; //QDebug debug=qDebug(); debug<<"\nrook: (pos="<<pos<<")\n";
    for(usi i=0;i<7;i++){//horisontal;
        if(next_posy!=posy){
            cells_go[i]=posx*8+next_posy;
            next_posy++;
        }
        else{
            i--; next_posy++;
        }
    }
    int next_posx=0;
    for(usi i=0;i<7;i++){//vertical;
        if(next_posx!=posx){
            cells_go[i+7]=next_posx*8+posy;
            next_posx++;
        }
        else{
            i--; next_posx++;
        }
    }
    /*for(usi i=0;i<mvsz;i++){
        debug<<cells_go[i]<<' ';
    }*/
}

void Frook::set_clr_pos(Fcolour colour, unsigned int p_pos){
    figure::set_clr_pos(colour,p_pos);
}
