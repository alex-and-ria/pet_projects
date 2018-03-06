#include "fking.h"

Fking::Fking(Fcolour colour,QObject *parent):
        figure(8,colour,kingt,false,0,parent){
    //mvsz=4: king can move on 1 cell in four directions;
    if(colour==Fwhite){
        init_pos=60;
    }
    else init_pos=4;
    fill_go(init_pos);
    emit figure::set_on_grd(kingt,colour,init_pos);
    //qDebug()<<"\nking constructor: "<<init_pos;
}

Fking::~Fking(){

}

void Fking::fill_go(unsigned int pos){
    //posx=pos/8; //        5   6  7
    //posy=pos%8; //        4 king 0
    figure::fill_go(pos);// 3   2  1
    /*bool whiteb=true;
    if(clr==Fblack){
        whiteb=false; posx=7-posx;
    }*/
    for(usi i=0;i<mvsz;i++){
        cells_go[i]=-1;
    }
    if(posx<8&&posy<8){
        if(posx==7&&posy==7){
            cells_go[4]=posx*8+posy-1; cells_go[5]=(posx-1)*8+posy-1;
            cells_go[6]=(posx-1)*8+posy;
        }
        else if(posx==7&&posy==0){
            cells_go[0]=posx*8+posy+1; cells_go[6]=(posx-1)*8+posy;
            cells_go[7]=(posx-1)*8+posy+1;
        }
        else if(posx==0&&posy==0){
            cells_go[0]=posx*8+posy+1; cells_go[1]=(posx+1)*8+posy+1;
            cells_go[2]=(posx+1)*8+posy;
        }
        else if(posx==0&&posy==7){
            cells_go[2]=(posx+1)*8+posy; cells_go[3]=(posx+1)*8+posy-1;
            cells_go[4]=posx*8+posy-1;
        }
        else if(posx==7){
            cells_go[0]=posx*8+posy+1; cells_go[4]=posx*8+posy-1;
            cells_go[5]=(posx-1)*8+posy-1; cells_go[6]=(posx-1)*8+posy;
            cells_go[7]=(posx-1)*8+posy+1;
        }
        else if(posx==0){
            cells_go[0]=posx*8+posy+1; cells_go[1]=(posx+1)*8+posy+1;
            cells_go[2]=(posx+1)*8+posy; cells_go[3]=(posx+1)*8+posy-1;
            cells_go[4]=posx*8+posy-1;
        }
        else if(posy==0){
            cells_go[0]=posx*8+posy+1; cells_go[1]=(posx+1)*8+posy+1;
            cells_go[2]=(posx+1)*8+posy; cells_go[6]=(posx-1)*8+posy;
            cells_go[7]=(posx-1)*8+posy+1;
        }
        else if(posy==7){
            cells_go[2]=(posx+1)*8+posy; cells_go[3]=(posx+1)*8+posy-1;
            cells_go[4]=posx*8+posy-1; cells_go[5]=(posx-1)*8+posy-1;
            cells_go[6]=(posx-1)*8+posy;
        }
        else{
            cells_go[0]=posx*8+posy+1; cells_go[1]=(posx+1)*8+posy+1;
            cells_go[2]=(posx+1)*8+posy; cells_go[3]=(posx+1)*8+posy-1;
            cells_go[4]=posx*8+posy-1; cells_go[5]=(posx-1)*8+posy-1;
            cells_go[6]=(posx-1)*8+posy; cells_go[7]=(posx-1)*8+posy+1;
        }
    }
    /*if(clr==Fblack){
        whiteb=false; posx=7-posx;
    }*/
}
