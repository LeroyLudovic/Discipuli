#ifndef _VECTEUR
#define _VECTEUR

#include <iostream>

class Vecteur{
    private :
        int x;
        int y;
    public :   
        Vecteur();

        Vecteur(int,int);

        ~Vecteur();

        const Vecteur oparator + (const Vecteur&);
        
        friend std::ostream& operator << (std::ostream&, const Date&)
};

#endif