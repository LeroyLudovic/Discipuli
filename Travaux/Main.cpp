#include "Vecteur.h"
#include <iostream>

using namespace std;

int main(){
    Vecteur v1(1,8);
    Vecteur v2(3,3);
    cout<<v1;
    v1 = v1+v2;
    cout<<v1<<v2;
    return 0;
}