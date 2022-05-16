
/**
*   @file Ennemi.h
*   @brief contient la classe ennemi
*   @author JeSaisPAs
*/

#ifndef _ENNEMI
#define _ENNEMI

#include "Vecteur.h"

/** 
* @class Ennemi
* @brief Classe qui contient les caractéristique d'un ennemie.
*/
class Ennemi {

    private :

    public :
    
    float vitesse;
    float chargement;


    unsigned int type;
    Vecteur position;
    double vie;

    /** @brief permet de construire un ennemi en fonction de certain paramètre.
    * @param[in] Vecteur Position de l'ennemi.
    * @param[in] int type de l'ennemi.
    * @param[in] bool détermine si l'ennemi seras plus fort que les autes ou non.
    */
    Ennemi(Vecteur, int, bool);

    /** @brief destructeur de l'ennemi
    */
    ~Ennemi();

    /** @brief Augmente la vie des ennemie en fonction de la vague pour améliorer la difficulté.
    * @param[in] vague permet de savoir a quel niveau du jeu nous en somme.
    */
    void lvlUp(int vague);

    /** @brief charge le déplacement vers la prochaine case.
    * @return true si l'ennemi peut se déplacer
    */
    bool Charg();

    /** @brief déplace l'ennemi dans une nouvelle case.
    * @param[in] Vecteur Nouvelle position de l'ennemi.
    */
    void Deplacement (Vecteur v);

    /** @brief Modifi la vitesse de l'ennemi
    * @param[in] n valeur avec la quel la vitesse va être modifié
    */
    void BoostVitesse(float n);

    /** @brief donne la position x de l'ennemi
    * @return La position x de l'ennemi
    */
    int getX();

    /** @brief donne la position y de l'ennemi
    * @return La position y de l'ennemi
    */
    int getY();

};

#endif