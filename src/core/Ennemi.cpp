/**
*   @file Ennemi.h
*   @brief contient la classe ennemi
*   @author JeSaisPAs
*/

#include "Ennemi.h"
#include <ctime>


/** @brief permet de construire un ennemi en fonction de certain paramètre.
* @param[in] Vecteur Position de l'ennemi.
* @param[in] int type de l'ennemi.
* @param[in] bool détermine si l'ennemi seras plus fort que les autes ou non.
*/
Ennemi::Ennemi(Vecteur v, int t, bool fort){
    type = t;
    position = v;
    chargement = 0;
    switch (t){
        case 1 :
            vie = 200;
            vitesse = 1;
            if (fort){
                vie *= 2.5;
                vitesse *= 1;
            }
            break;
        case 2 :
            vie = 50;
            vitesse = 3;
            if (fort){
                vie *= 1;
                vitesse *= 2;
            }
            break;
        case 3 :
            vie = 100;
            vitesse = 1;
            if (fort){
                vie *= 2;
                vitesse *= 2;
            }
            break;
        case 4 :
            vie = 50;
            vitesse = 1;
            if (fort){
                vie *= 1.5;
                vitesse *= 1.5;
            }
            break;
    }
    
    
}


///@brief destructeur de l'ennemi
Ennemi::~Ennemi(){

}

/** @brief Augmente la vie des ennemie en fonction de la vague pour améliorer la difficulté.
    * @param[in] vague permet de savoir a quel niveau du jeu nous en somme.
    */
void Ennemi::lvlUp(int vague){
    //std::cout<<vie<<std::endl;
    vie += vague*2;
    //std::cout<<vie<<std::endl;
}

    /** @brief charge le déplacement vers la prochaine case.
    * @return true si l'ennemi peut se déplacer
    */
bool Ennemi::Charg(){
    chargement+=vitesse;
    if(chargement > 20){
        chargement = 0;
        return true;
    }
    return false;
}

/** @brief déplace l'ennemi dans une nouvelle case.
    * @param[in] Vecteur Nouvelle position de l'ennemi.
    */
void Ennemi::Deplacement(Vecteur v){
    position = position + v;
}

    /** @brief Modifi la vitesse de l'ennemi
    * @param[in] n valeur avec la quel la vitesse va être modifié
    */
void Ennemi::BoostVitesse(float n){
    vitesse = vitesse * n; 
}

 /** @brief donne la position x de l'ennemi
    * @return La position x de l'ennemi
    */
int Ennemi::getX(){
    return position.x;
}

 /** @brief donne la position y de l'ennemi
    * @return La position y de l'ennemi
    */
int Ennemi::getY(){
    return position.y;
}