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
            cout<<t.tab[i][j];
        }
        cout<<endl;
    }
    cout<<t.prochaineCase(a);
    return 0;
}   