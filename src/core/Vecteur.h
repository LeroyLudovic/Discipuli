#ifndef _VECTEUR_H
#define _VECTEUR_H

#include <iostream>

class Vecteur{
    public : 

        int x;
        
        int y;

        Vecteur();

        Vecteur(int,int);

        ~Vecteur();

        const Vecteur operator + (const Vecteur&);

        const Vecteur operator = (const Vecteur&);
        
        friend std::ostream& operator << (std::ostream&, const Vecteur&);
};

#endif