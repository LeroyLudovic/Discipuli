#include "Vecteur.h"
#include <iostream>

using namespace std;

int main(){
    Vecteur v1(8,8);
    Vecteur v2(5,6);

    cout<<v1<<endl;

    v1 = v1+v2;

    cout<<v1<<endl;
}