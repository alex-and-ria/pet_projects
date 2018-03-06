#ifndef GRD_H
#define GRD_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QVector>
#include <QStack>
#include "figure.h"
#include "fking.h"
#include "fqueen.h"
#include "frook.h"
#include "fbishop.h"
#include "fknight.h"
#include "fpawn.h"

#define Nrooks 4
#define Nbishops 4
#define Nknights 4
#define Npawns 16

class grd : public QObject{
    Q_OBJECT

public:
    explicit grd(QObject *parent = 0);
    ~grd();
    struct Gon_elem{
        figure::Ftype gtype;
        figure::Fcolour gcolour;
        unsigned int fig_i;
    };
    Q_INVOKABLE int get_im_index(unsigned int i, unsigned int j);
    Q_INVOKABLE unsigned int get_cnt();
    Q_INVOKABLE void save_curr();
    Q_INVOKABLE void load_curr();
    Q_INVOKABLE void init_new();
    Q_INVOKABLE bool get_new_mv(bool nxt);
    Q_INVOKABLE void push_ts(int p_val);
    Q_INVOKABLE int pop_fs();
    Q_INVOKABLE void push_tms(unsigned int p_val);
    Q_INVOKABLE unsigned int pop_fms();
    Q_INVOKABLE int top_fms();
    Q_PROPERTY(bool allow_mv READ is_mv_allowed CONSTANT)
    bool allow_mv;
    bool is_mv_allowed() const;
    Q_PROPERTY(unsigned int com_cnt READ get_com_cnt WRITE set_com_cnt)
    unsigned int com_cnt;
    unsigned int get_com_cnt() const;
    void set_com_cnt(unsigned int p_cnt);
    Q_PROPERTY(unsigned int from READ fromf CONSTANT)
    unsigned int from;
    unsigned int fromf() const;
    Q_PROPERTY(unsigned int to READ tof CONSTANT)
    unsigned int to;
    unsigned int tof() const;
    Q_PROPERTY(unsigned int curr_mv READ curr_mvf CONSTANT)
    unsigned int curr_mv;
    unsigned int curr_mvf() const;

//signals:
//    void sendMv(int to_pos,unsigned int from_pos);


private:
    Gon_elem grd_cells[8][8];
    /*Fking* kingw;
    Fking* kingb;
    Fqueen* queenw;
    Fqueen* queenb;
    Frook rooks[Nrooks];
    Fbishop bishops[Nbishops];
    Fknight knights[Nknights];
    Fpawn pawns[Npawns];*/
    figure *figures[Nrooks+Nbishops+Nknights+Npawns+4];
    int curr_i;
    unsigned int prev_i;
    figure::Fcolour mv_clr;
    QVector<unsigned int> mvmnts;
    QStack<int> fig_stack;
    QStack<unsigned int> mv_stack;


public slots:
    //void receiveFromQml();
    void set_fig(figure::Ftype p_id, figure::Fcolour p_clr, unsigned int p_pos);
    void pressed_area(unsigned int p_pos);
};
#endif // GRD_H
