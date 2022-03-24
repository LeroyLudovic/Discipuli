#ifndef _VECTEUR_H
#define _VECTEUR_H

#include <iostream>

class Vecteur{
    private :
        int x;
        int y;
    public :   
        Vecteur();

        Vecteur(int,int);

        ~Vecteur();

        const Vecteur operator + (const Vecteur&);
        
        friend std::ostream& operator << (std::ostream&, const Vecteur&);
};

#endif