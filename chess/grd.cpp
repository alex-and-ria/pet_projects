#include "grd.h"

grd::grd(QObject *parent) : QObject(parent)
{
    for(usi i=0;i<8*8;i++){
        grd_cells[i/8][i%8].gtype=figure::emptyt;
        grd_cells[i/8][i%8].gcolour=figure::Fempty;
    }
    /*Fking(Fcolour colour,QObject *parent = 0);
    Fqueen(Fcolour colour,QObject *parent = 0);
    Frook(Fcolour colour,unsigned int p_pos,QObject *parent = 0);
    Fbishop(Fcolour colour,unsigned int p_pos,QObject *parent = 0);
    Fknight(Fcolour colour,unsigned int p_pos,QObject *parent = 0);
    Fpawn(Fcolour colour,unsigned int p_pos,QObject *parent = 0);*/
    unsigned int cnt=0;
    //kingw=new Fking(figure::Fwhite);
    figures[cnt]=new Fking(figure::Fwhite); cnt++;
    //connect(figures[cnt-1],&Fking::set_on_grd,this,&grd::set_fig);
    //kingb=new Fking(figure::Fblack);
    figures[cnt]=new Fking(figure::Fblack); cnt++;
    //connect(figures[cnt-1],&Fking::set_on_grd,this,&grd::set_fig);
    //queenw=new Fqueen(figure::Fwhite);
    figures[cnt]=new Fqueen(figure::Fwhite); cnt++;
    //connect(figures[cnt-1],&Fqueen::set_on_grd,this,&grd::set_fig);
    //queenb=new Fqueen(figure::Fblack);
    figures[cnt]=new Fqueen(figure::Fblack); cnt++;
    //connect(figures[cnt-1],&Fqueen::set_on_grd,this,&grd::set_fig);

    //rooks[0].set_clr_pos(figure::Fwhite,56);
    figures[cnt]=new Frook(figure::Fwhite,56); cnt++;
    //connect(figures[cnt-1],&Frook::set_on_grd,this,&grd::set_fig);
    //rooks[1].set_clr_pos(figure::Fwhite,63);
    figures[cnt]=new Frook(figure::Fwhite,63); cnt++;
    //connect(figures[cnt-1],&Frook::set_on_grd,this,&grd::set_fig);
    //rooks[2].set_clr_pos(figure::Fblack,0);
    figures[cnt]=new Frook(figure::Fblack,0); cnt++;
    //connect(figures[cnt-1],&Frook::set_on_grd,this,&grd::set_fig);
    //rooks[3].set_clr_pos(figure::Fblack,7);
    figures[cnt]=new Frook(figure::Fblack,7); cnt++;
    //connect(figures[cnt-1],&Frook::set_on_grd,this,&grd::set_fig);

    //bishops[0].set_clr_pos(figure::Fwhite,58);
    figures[cnt]=new Fbishop(figure::Fwhite,58); cnt++;
    //connect(figures[cnt-1],&Fbishop::set_on_grd,this,&grd::set_fig);
    //bishops[1].set_clr_pos(figure::Fwhite,61);
    figures[cnt]=new Fbishop(figure::Fwhite,61); cnt++;
    //connect(figures[cnt-1],&Fbishop::set_on_grd,this,&grd::set_fig);
    //bishops[2].set_clr_pos(figure::Fblack,2);
    figures[cnt]=new Fbishop(figure::Fblack,2); cnt++;
    //connect(figures[cnt-1],&Fbishop::set_on_grd,this,&grd::set_fig);
    //bishops[3].set_clr_pos(figure::Fblack,5);
    figures[cnt]=new Fbishop(figure::Fblack,5); cnt++;
    //connect(figures[cnt-1],&Fbishop::set_on_grd,this,&grd::set_fig);

    //knights[0].set_clr_pos(figure::Fwhite,57);
    figures[cnt]=new Fknight(figure::Fwhite,57); cnt++;
    //connect(figures[cnt-1],&Fknight::set_on_grd,this,&grd::set_fig);
    //knights[1].set_clr_pos(figure::Fwhite,62);
    figures[cnt]=new Fknight(figure::Fwhite,62); cnt++;
    //connect(figures[cnt-1],&Fknight::set_on_grd,this,&grd::set_fig);
    //knights[2].set_clr_pos(figure::Fblack,1);
    figures[cnt]=new Fknight(figure::Fblack,1); cnt++;
    //connect(figures[cnt-1],&Fknight::set_on_grd,this,&grd::set_fig);
    //knights[3].set_clr_pos(figure::Fblack,6);
    figures[cnt]=new Fknight(figure::Fblack,6); cnt++;
    //connect(figures[cnt-1],&Fknight::set_on_grd,this,&grd::set_fig);

    for(usi i=0;i<Npawns/2;i++){
        //pawns[i].set_clr_pos(figure::Fwhite,48+i);
        figures[cnt]=new Fpawn(figure::Fwhite,48+i); cnt++;
        //connect(figures[cnt-1],&Fpawn::set_on_grd,this,&grd::set_fig);
    }
    for(usi i=0;i<Npawns/2;i++){
        //pawns[Npawns/2+i].set_clr_pos(figure::Fblack,8+i);
        figures[cnt]=new Fpawn(figure::Fblack,8+i); cnt++;
        //connect(figures[cnt-1],&Fpawn::set_on_grd,this,&grd::set_fig);
    }
    for(usi i=0;i<cnt;i++){
        grd_cells[figures[i]->get_posx()][figures[i]->get_posy()].gcolour=figures[i]->get_clr();
        grd_cells[figures[i]->get_posx()][figures[i]->get_posy()].gtype=figures[i]->get_id();
        grd_cells[figures[i]->get_posx()][figures[i]->get_posy()].fig_i=i;
    }
    allow_mv=false; curr_i=-1; com_cnt=0; mv_clr=figure::Fwhite;
    qDebug()<<"\ngrd constructor";
}

/*void grd::receiveFromQml()
{
    for(unsigned int q=0;q<8*8;q++){
        //i=q/8; j=q%8;
        //emit sendToQml(i,j);
    }
    //qDebug()<<"\n emit cellSig1";
}*/

void grd::set_fig(figure::Ftype p_id, figure::Fcolour p_clr, unsigned int p_pos){
    unsigned int tmp_posx=p_pos/8,tmp_posy=p_pos%8;
    grd_cells[tmp_posx][tmp_posy].gtype=p_id;
    grd_cells[tmp_posx][tmp_posy].gcolour=p_clr;
    //qDebug()<<"grd::set_fig cached from "<<p_id<<" "<<p_clr<<" on "
    //       <<" ["<<tmp_posx<<"]["<<tmp_posy<<"]";
}

int grd::get_im_index(unsigned int i,unsigned int j){
    if(grd_cells[i][j].gtype==figure::emptyt) return -1;
    int retval=0;
    if(grd_cells[i][j].gcolour==figure::Fwhite){
        retval=6; //qDebug()<<"\nwhite here";
    }
    //else qDebug()<<"\nblack here";
    switch (grd_cells[i][j].gtype) {
    case figure::kingt:
        //retval=retval;
        break;
    case figure::queent:
        retval+=1;
        break;
    case figure::rookt:
        retval+=2;
        break;
    case figure::bishopt:
        retval+=3;
        break;
    case figure::knightt:
        retval+=4;
        break;
    case figure::pawnt:
        retval+=5;
        break;
    default:
        break;
    }
    //qDebug()<<" retval="<<retval;
    return retval;
}

void grd::pressed_area(unsigned int p_pos){
    //qDebug()<<"\ncurr_i="<<curr_i<<" allow_mv="<<allow_mv;
    if(curr_i==-1
            &&allow_mv==false){//first;
        if(grd_cells[p_pos/8][p_pos%8].gtype!=figure::emptyt
                &&grd_cells[p_pos/8][p_pos%8].gcolour==mv_clr){
            curr_i=grd_cells[p_pos/8][p_pos%8].fig_i;//figure index;
            prev_i=p_pos;//prev pos index;
            figures[curr_i]->fill_go(p_pos);
            allow_mv=true; com_cnt+=1;
            QDebug debug=qDebug(); debug<<"\np_posx="<<p_pos/8<<" p_posy="<<p_pos%8
                                       <<"\n figures[curr_i]->cells_go:\n";
            for(usi i=0;i<figures[curr_i]->get_mvsz();i++){
                debug<<figures[curr_i]->cells_go[i];
            }
        }
    }
    else{//second;
        if(prev_i==p_pos){
            allow_mv=false; curr_i=-1; com_cnt+=1; return;
        }
        for(usi i=0;i<figures[curr_i]->get_mvsz();i++){
            if(figures[curr_i]->cells_go[i]>0
                    &&figures[curr_i]->cells_go[i]==p_pos
                    &&(figures[curr_i]->get_clr())!=
                        (grd_cells[p_pos/8][p_pos%8].gcolour)){
                //possible to go on p_pos;
                if(figures[curr_i]->get_id()==figure::pawnt){//at first time pawn can go on 2 cells;
                    if(figures[curr_i]->get_is_first()==true){
                        figures[curr_i]->set_is_first(false);//next -- on 1 cell Fpawn::fill_go(pos);
                    }
                    if(prev_i%8!=p_pos%8
                            &&grd_cells[p_pos/8][p_pos%8].gtype==figure::emptyt){//pown's diagonal movement;
                        return;
                    }
                    if(prev_i%8==p_pos%8
                            &&grd_cells[p_pos/8][p_pos%8].gtype!=figure::emptyt){//pown's forward movement;
                        return;
                    }
                }
                if(figures[curr_i]->get_id()==figure::queent
                        ||figures[curr_i]->get_id()==figure::rookt
                        ||figures[curr_i]->get_id()==figure::bishopt){//checking for obstacles;
                    if(prev_i<p_pos&&(prev_i/8)==(p_pos/8)){//p_pos in horisontal left;
                        for(usi i=0;i<figures[curr_i]->get_mvsz();i++){
                            if(figures[curr_i]->cells_go[i]>0
                                    &&((figures[curr_i]->cells_go[i])/8)==(p_pos/8)//horisontal
                                    &&figures[curr_i]->cells_go[i]<p_pos
                                    &&figures[curr_i]->cells_go[i]>prev_i
                                    &&grd_cells[(figures[curr_i]->cells_go[i])/8][(figures[curr_i]->cells_go[i])%8].gtype
                                        !=figure::emptyt){
                                return;
                            }
                        }
                    }
                    if(prev_i>p_pos&&(prev_i/8)==(p_pos/8)){//p_pos in horisontal right;
                        for(usi i=0;i<figures[curr_i]->get_mvsz();i++){
                            if(figures[curr_i]->cells_go[i]>0
                                    &&((figures[curr_i]->cells_go[i])/8)==(p_pos/8)
                                    &&figures[curr_i]->cells_go[i]>p_pos
                                    &&figures[curr_i]->cells_go[i]<prev_i
                                    &&grd_cells[(figures[curr_i]->cells_go[i]/8)][(figures[curr_i]->cells_go[i])%8].gtype
                                        !=figure::emptyt){
                                return;
                            }
                        }
                    }
                    unsigned int prev_i_x=prev_i/8, prev_i_y=prev_i%8,p_pos_x=p_pos/8, p_pos_y=p_pos%8;
                    if(prev_i_x<p_pos_x&&prev_i_y==p_pos_y){//p_pos in vertical bottom
                        for(usi i=0;i<figures[curr_i]->get_mvsz();i++){
                            if(figures[curr_i]->cells_go[i]>0
                                    &&((figures[curr_i]->cells_go[i])%8)==p_pos_y
                                    &&(figures[curr_i]->cells_go[i])/8<p_pos_x
                                    &&(figures[curr_i]->cells_go[i])/8>prev_i_x
                                    &&grd_cells[(figures[curr_i]->cells_go[i]/8)][(figures[curr_i]->cells_go[i])%8].gtype
                                        !=figure::emptyt){
                                return;
                            }
                        }
                    }
                    if(prev_i_x>p_pos_x&&prev_i_y==p_pos_y){//p_pos in vertical top
                        for(usi i=0;i<figures[curr_i]->get_mvsz();i++){
                            if(figures[curr_i]->cells_go[i]>0
                                    &&((figures[curr_i]->cells_go[i])%8)==p_pos_y
                                    &&(figures[curr_i]->cells_go[i])/8>p_pos_x
                                    &&(figures[curr_i]->cells_go[i])/8<prev_i_x
                                    &&grd_cells[(figures[curr_i]->cells_go[i]/8)][(figures[curr_i]->cells_go[i])%8].gtype
                                        !=figure::emptyt){
                                return;
                            }
                        }
                    }
                    if(prev_i_x<p_pos_x&&prev_i_y<p_pos_y){//p_pos in right buttom
                        for(usi i=0;i<figures[curr_i]->get_mvsz();i++){
                            if(figures[curr_i]->cells_go[i]>0
                                    &&(figures[curr_i]->cells_go[i])/8>prev_i_x
                                    &&(figures[curr_i]->cells_go[i])%8>prev_i_y
                                    &&(figures[curr_i]->cells_go[i])/8<p_pos_x
                                    &&(figures[curr_i]->cells_go[i])%8<p_pos_y
                                    &&grd_cells[(figures[curr_i]->cells_go[i])/8][(figures[curr_i]->cells_go[i])%8].gtype
                                    !=figure::emptyt){
                                return;
                            }
                        }
                    }
                    if(prev_i_x<p_pos_x&&prev_i_y>p_pos_y){//p_pos in left buttom
                        for(usi i=0;i<figures[curr_i]->get_mvsz();i++){
                            if(figures[curr_i]->cells_go[i]>0
                                    &&(figures[curr_i]->cells_go[i])/8>prev_i_x
                                    &&(figures[curr_i]->cells_go[i])%8<prev_i_y
                                    &&(figures[curr_i]->cells_go[i])/8<p_pos_x
                                    &&(figures[curr_i]->cells_go[i])%8>p_pos_y
                                    &&grd_cells[(figures[curr_i]->cells_go[i])/8][(figures[curr_i]->cells_go[i])%8].gtype
                                    !=figure::emptyt){
                                return;
                            }
                        }
                    }
                    if(prev_i_x>p_pos_x&&prev_i_y>p_pos_y){//p_pos in left top
                        for(usi i=0;i<figures[curr_i]->get_mvsz();i++){
                            if(figures[curr_i]->cells_go[i]>0
                                    &&(figures[curr_i]->cells_go[i])/8<prev_i_x
                                    &&(figures[curr_i]->cells_go[i])%8<prev_i_y
                                    &&(figures[curr_i]->cells_go[i])/8>p_pos_x
                                    &&(figures[curr_i]->cells_go[i])%8>p_pos_y
                                    &&grd_cells[(figures[curr_i]->cells_go[i])/8][(figures[curr_i]->cells_go[i])%8].gtype
                                    !=figure::emptyt){
                                return;
                            }
                        }
                    }
                    if(prev_i_x>p_pos_x&&prev_i_y<p_pos_y){//p_pos in right top
                        for(usi i=0;i<figures[curr_i]->get_mvsz();i++){
                            if(figures[curr_i]->cells_go[i]>0
                                    &&(figures[curr_i]->cells_go[i])/8<prev_i_x
                                    &&(figures[curr_i]->cells_go[i])%8>prev_i_y
                                    &&(figures[curr_i]->cells_go[i])/8>p_pos_x
                                    &&(figures[curr_i]->cells_go[i])%8<p_pos_y
                                    &&grd_cells[(figures[curr_i]->cells_go[i])/8][(figures[curr_i]->cells_go[i])%8].gtype
                                    !=figure::emptyt){
                                return;
                            }
                        }
                    }
                }
                grd_cells[prev_i/8][prev_i%8].gtype=figure::emptyt;
                grd_cells[prev_i/8][prev_i%8].gcolour=figure::Fempty;
                grd_cells[p_pos/8][p_pos%8].gtype=figures[curr_i]->get_id();
                grd_cells[p_pos/8][p_pos%8].gcolour=figures[curr_i]->get_clr();
                grd_cells[p_pos/8][p_pos%8].fig_i=curr_i;
                qDebug()<<"\nmoved: from"<<prev_i<<" to "<<p_pos;
                allow_mv=false; curr_i=-1; com_cnt+=1;
                if(mv_clr==figure::Fwhite){
                    mv_clr=figure::Fblack;
                }
                else mv_clr=figure::Fwhite;
                mvmnts.push_back(prev_i); mvmnts.push_back(p_pos);
                return;
            }
        }
    }

    qDebug()<<"\nboard:";
    for(usi i=0;i<8;i++)
        for(usi j=0;j<8;j++){
            QDebug debug=qDebug();
            debug<<"cell: "<<i*8+j<<' ';
            switch (grd_cells[i][j].gtype) {
            case figure::kingt:
                debug<<"king";
                break;
            case figure::queent:
                debug<<"queen";
                break;
            case figure::rookt:
                debug<<"rook";
                break;
            case figure::bishopt:
                debug<<"bishop";
                break;
            case figure::knightt:
                debug<<"knight";
                break;
            case figure::pawnt:
                debug<<"pawn";
                break;
            case figure::emptyt:
                debug<<"-";
                break;
            default:
                break;
            } debug<<' ';
            switch (grd_cells[i][j].gcolour) {
            case figure::Fwhite:
                debug<<"white";
                break;
            case figure::Fblack:
                debug<<"black";
                break;
            default:
                debug<<"-";
                break;
            }
        }
}

bool grd::is_mv_allowed() const {
    return allow_mv;
}

unsigned int grd::get_cnt(){
    return com_cnt;
}

unsigned int grd::get_com_cnt() const{
    return com_cnt;
}

void grd::set_com_cnt(unsigned int p_cnt){
    com_cnt=p_cnt;
}

void grd::save_curr(){
    QDebug debug=qDebug();
    QFile fl("./q.txt");
    if(!fl.open(QIODevice::Truncate|QIODevice::WriteOnly)){
        debug<<"\nsave: cannot open"; return;
    }
    QDataStream fl_stream(&fl); debug<<"\nmvmnts: ";
    fl_stream<<mvmnts.size();
    for(unsigned int i=0;i<mvmnts.size();i++){
        fl_stream<<mvmnts.at(i);
        debug<<mvmnts.at(i)<<' ';
    }
    /*for(usi i=0;i<8*8;i++){
        fl_stream<<(unsigned int)(grd_cells[i/8][i%8].gtype);
        debug<<(unsigned int)(grd_cells[i/8][i%8].gtype);
    }
    for(usi i=0;i<8*8;i++){
        fl_stream<<(unsigned int)(grd_cells[i/8][i%8].gcolour);
    }
    for(usi i=0;i<8*8;i++){
        fl_stream<<(unsigned int)(grd_cells[i/8][i%8].fig_i);
    }
    fl_stream<<curr_i;
    fl_stream<<prev_i;
    fl_stream<<mv_clr;*/
    fl.close();
    qDebug()<<"\nsave: file closed";
}
void grd::load_curr(){
    QDebug debug=qDebug();
    mvmnts.clear();
    curr_mv=0;
    fig_stack.clear();
    mv_stack.clear();
    QFile fl("./q.txt");
    if(!fl.open(QIODevice::ReadOnly)){
        debug<<"\nload: cannot open"; return;
    }
    QDataStream fl_stream(&fl); unsigned int val_ff,tmp_sz;
    fl_stream>>tmp_sz;
    for(unsigned int i=0;i<tmp_sz;i++){
       fl_stream>>val_ff;
       mvmnts.push_back(val_ff);
    } curr_mv=0;
    debug<<"\nloaded:";
    for(unsigned int i=0;i<mvmnts.size();i++){
        debug<<mvmnts.at(i)<<' ';
    }
    /*for(usi i=0;i<8*8;i++){
        fl_stream>>val_ff;
        switch (val_ff) {
        case 0:
            grd_cells[i/8][i%8].gtype=figure::kingt;
            break;
        case 1:
            grd_cells[i/8][i%8].gtype=figure::queent;
            break;
        case 2:
            grd_cells[i/8][i%8].gtype=figure::rookt;
            break;
        case 3:
            grd_cells[i/8][i%8].gtype=figure::bishopt;
            break;
        case 4:
            grd_cells[i/8][i%8].gtype=figure::knightt;
            break;
        case 5:
            grd_cells[i/8][i%8].gtype=figure::pawnt;
            break;
        default:
            break;
        }
        debug<<val_ff;
    }
    for(usi i=0;i<8*8;i++){
        fl_stream>>val_ff;
        switch (val_ff) {
        case 0:
            grd_cells[i/8][i%8].gcolour=figure::Fwhite;
            break;
        case 1:
            grd_cells[i/8][i%8].gcolour=figure::Fblack;
            break;
        case 2:
            grd_cells[i/8][i%8].gcolour=figure::Fempty;
            break;
        default:
            break;
        }
    }
    for(usi i=0;i<8*8;i++){
        fl_stream>>grd_cells[i/8][i%8].fig_i;
    }
    fl_stream>>curr_i;
    fl_stream>>prev_i;
    fl_stream>>val_ff;
    if(val_ff==0) mv_clr=figure::Fwhite;
    else mv_clr=figure::Fblack;*/
    fl.close(); init_new();
    qDebug()<<"\nload: file closed";
}

void grd::init_new(){

    for(usi i=0;i<8*8;i++){
        grd_cells[i/8][i%8].gtype=figure::emptyt;
        grd_cells[i/8][i%8].gcolour=figure::Fempty;
        grd_cells[i/8][i%8].fig_i=0;
    }
    unsigned int cnt=0;
    figures[cnt]->set_clr_pos(figure::Fwhite,60); cnt++;
    figures[cnt]->set_clr_pos(figure::Fblack,4); cnt++;
    figures[cnt]->set_clr_pos(figure::Fwhite,59); cnt++;
    figures[cnt]->set_clr_pos(figure::Fblack,3); cnt++;

    figures[cnt]->set_clr_pos(figure::Fwhite,56); cnt++;
    figures[cnt]->set_clr_pos(figure::Fwhite,63); cnt++;
    figures[cnt]->set_clr_pos(figure::Fblack,0); cnt++;
    figures[cnt]->set_clr_pos(figure::Fblack,7); cnt++;

    figures[cnt]->set_clr_pos(figure::Fwhite,58); cnt++;
    figures[cnt]->set_clr_pos(figure::Fwhite,61); cnt++;
    figures[cnt]->set_clr_pos(figure::Fblack,2); cnt++;
    figures[cnt]->set_clr_pos(figure::Fblack,5); cnt++;

    figures[cnt]->set_clr_pos(figure::Fwhite,57); cnt++;
    figures[cnt]->set_clr_pos(figure::Fwhite,62); cnt++;
    figures[cnt]->set_clr_pos(figure::Fblack,1); cnt++;
    figures[cnt]->set_clr_pos(figure::Fblack,6); cnt++;

    for(usi i=0;i<Npawns/2;i++){
        figures[cnt]->set_clr_pos(figure::Fwhite,48+i);
        figures[cnt]->set_is_first(true); cnt++;
    }
    for(usi i=0;i<Npawns/2;i++){
        figures[cnt]->set_clr_pos(figure::Fblack,8+i);
        figures[cnt]->set_is_first(true); cnt++;
    }
    for(usi i=0;i<cnt;i++){
        grd_cells[figures[i]->get_posx()][figures[i]->get_posy()].gcolour=figures[i]->get_clr();
        grd_cells[figures[i]->get_posx()][figures[i]->get_posy()].gtype=figures[i]->get_id();
        grd_cells[figures[i]->get_posx()][figures[i]->get_posy()].fig_i=i;
    }
    allow_mv=false; curr_i=-1; com_cnt=0; mv_clr=figure::Fwhite;
    /*qDebug()<<"\nboard (init):";
    for(usi i=0;i<8;i++)
        for(usi j=0;j<8;j++){
            QDebug debug=qDebug();
            debug<<"cell: "<<i*8+j<<' ';
            switch (grd_cells[i][j].gtype) {
            case figure::kingt:
                debug<<"king";
                break;
            case figure::queent:
                debug<<"queen";
                break;
            case figure::rookt:
                debug<<"rook";
                break;
            case figure::bishopt:
                debug<<"bishop";
                break;
            case figure::knightt:
                debug<<"knight";
                break;
            case figure::pawnt:
                debug<<"pawn";
                break;
            case figure::emptyt:
                debug<<"-";
                break;
            default:
                break;
            } debug<<' ';
            switch (grd_cells[i][j].gcolour) {
            case figure::Fwhite:
                debug<<"white";
                break;
            case figure::Fblack:
                debug<<"black";
                break;
            default:
                debug<<"-";
                break;
            }
        }*/
}

bool grd::get_new_mv(bool nxt){
    if(nxt==true){
        if(curr_mv<(mvmnts.size()/2)){
            from=mvmnts.at(curr_mv*2);
            to=mvmnts.at(curr_mv*2+1);
            curr_mv++; return 1;
        }
        return 0;
    }
    else {
        if(curr_mv!=0){
            from=mvmnts.at(curr_mv*2-1);
            to=mvmnts.at(curr_mv*2-2);
            curr_mv--; return 1;
        }
        return 0;
    }
}

unsigned int grd::fromf() const{
    return from;
}

unsigned int grd::tof() const{
    return to;
}

void grd::push_ts(int p_val){
    fig_stack.push(p_val);
}

int grd::pop_fs(){
    fig_stack.pop();
}

void grd::push_tms(unsigned int p_val){
    mv_stack.push(p_val);
}

unsigned int grd::pop_fms(){
    return mv_stack.pop();
}

int grd::top_fms(){
    if(!mv_stack.isEmpty()){
        return mv_stack.top();
    }
    return -1;
}

unsigned int grd::curr_mvf() const{
    return curr_mv;
}

grd::~grd(){
    for(usi i=0;i<Nrooks+Nbishops+Nknights+Npawns+4;i++){
        delete figures[i];
    }
}
