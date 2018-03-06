#include "fpawn.h"

Fpawn::Fpawn(Fcolour colour,unsigned int p_pos,QObject *parent):
        figure(4,colour,pawnt,false,p_pos,parent),is_qexist(true){
    //mvsz=4: pawn can move up to 2 cells forward + 2 cells when displacing another figure;
    fill_go(init_pos);
    //qDebug()<<"\npawn constructor: "<<p_pos;
}

Fpawn::~Fpawn(){

}

void Fpawn::fill_go(unsigned int pos){
    //posx=pos/8; //              3
    //posy=pos%8; //           2  1   0
    figure::fill_go(pos);//     pawn
    bool whiteb=true;
    if(clr==Fblack){
        whiteb=false; posx=7-posx;
    }
    int next_posx=posx, next_posy=posy;
    if((next_posx-1)<0){
         cells_go[0]=cells_go[1]=cells_go[2]=cells_go[3]=-1;
         if(!is_qexist){
             if(!whiteb) posx=7-posx;
             //emit signal new queen;
         }
    }
    else{
        if((next_posy+1)>7){
            cells_go[0]=-1;
        }else{
            if(whiteb) cells_go[0]=(posx-1)*8+posy+1;
            else cells_go[0]=(7-(posx-1))*8+posy+1;
        }
        if(whiteb) cells_go[1]=(posx-1)*8+posy;
        else cells_go[1]=(7-(posx-1))*8+posy;
        if((next_posy-1)<0){
            cells_go[2]=-1;
        }else{
           if(whiteb) cells_go[2]=(posx-1)*8+posy-1;
           else cells_go[2]=(7-(posx-1))*8+posy-1;
        }
        if(!is_first||(next_posx-2)<0){
            cells_go[3]=-1;
        }else{
            if(whiteb) cells_go[3]=(next_posx-2)*8+posy;
            else cells_go[3]=(7-(next_posx-2))*8+posy;
        }
    }
    if(!whiteb) posx=7-posx;
}

void Fpawn::set_clr_pos(Fcolour colour, unsigned int p_pos){
    figure::set_clr_pos(colour,p_pos);

}
