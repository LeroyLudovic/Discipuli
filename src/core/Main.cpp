#include "Vecteur.h"
#include "Terrain.h"
#include <iostream>

using namespace std;

int main(){
    Terrain t;
    Vecteur a(2,1);
    t.generation();
    for(int i =0;i<5;i++){
        for(int j =0;j<20;j++){
            cout<<t.getCase(i,j);
        }
        cout<<endl;
    }
    for(int i = 0;i<20;i++){
        cout<<a;
        a = t.prochaineCase(a);
    }
   
    
    return 0;
}   