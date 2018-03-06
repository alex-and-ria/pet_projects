#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QDebug>
typedef unsigned short int usi;

class figure : public QObject{
    Q_OBJECT

public:
    enum Fcolour{
        Fwhite,Fblack,Fempty
    };
    enum Ftype{
        kingt,queent,rookt,bishopt,knightt,pawnt,emptyt
    };

    explicit figure(
            unsigned int p_mvsz,Fcolour p_clr,Ftype p_type,
            bool p_jump,unsigned int p_pos,QObject *parent = 0);
    virtual ~figure();
    virtual void fill_go(unsigned int pos)=0;
    void set_clr_pos(Fcolour colour,unsigned int p_pos);
    int* cells_go;
    void set_id(Ftype p_type);
    Ftype get_id() const;
    void set_clr(Fcolour p_clr);
    Fcolour get_clr() const;
    unsigned int get_mvsz() const;
    unsigned int get_posx() const;
    unsigned int get_posy() const;
    void set_is_first(bool p_is_first);
    bool get_is_first() const;

signals:
    void set_on_grd(Ftype p_id, Fcolour p_clr,unsigned int p_pos);

protected://public: //protected:
    Ftype id;
    Fcolour clr;
    unsigned int mvsz;
    bool jump;
    unsigned int posx;
    unsigned int posy;
    unsigned int init_pos;
    bool is_first;
};

#endif // FIGURE_H
