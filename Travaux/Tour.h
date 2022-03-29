#ifndef _TOUR
#define _TOUR

class Tour {

    private :

    int type;
    int degat;
    float vitesse;
    int portee;
    int prix;

    public :

    Tour();

    ~Tour();

    void Amelioration();

    int Vendre();

}