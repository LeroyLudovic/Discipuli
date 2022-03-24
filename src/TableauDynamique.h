#ifndef _TAB_DYN
#define _TAB_DYN

#include "Element.h"

class TableauDynamique {
public:
    /* donnees membres */
    /* =============== */
    /* (ne sont pas censees etre connues par l'utilisateur,
        si on avait pu ne pas les faire figurer dans l'interface, on l'aurait fait)
    */
    unsigned int capacite;
    unsigned int taille_utilisee;
    Element * ad;

    /* fonctions membres */
    /* ================= */
    TableauDynamique (); // Constructeur par defaut
    /* Postcondition : le tableau a 1 emplacement alloue mais vide (taille utilisee nulle) */

    TableauDynamique (const TableauDynamique& t); // Constructeur par copie
    /* Precondition : le tableau t est initialise */
    /* Postcondition : les deux tableaux contiennent des sequences d'ElementTD identiques (copie de t) */

    ~TableauDynamique (); // Destructeur
    /* Postcondition : la memoire allouee dynamiquement est liberee. */
	
	void vider ();
    /* Postcondition : la memoire allouee dynamiquement est liberee.
	                   le tableau a 1 emplacement alloue mais vide (taille utilisee nulle) */

    void ajouterElement (Element e);
    /* Postcondition : l'element e est ajoute dans le premier emplacement inutilise du tableau,
                       la taille est incrementee de 1. Doublement de la capacite si necessaire. */

    Element valeurIemeElement (unsigned int indice) const;
    /* Precondition : 0 <= indice < taille_utilisee */
    /* Resultat : retourne l'ElementTD e l'indice en parametre */

    void modifierValeurIemeElement (Element e, unsigned int indice);
    /* Precondition : 0 <= indice < taille_utilisee */
    /* Postcondition : l'ElementTD a l'indice en parametre vaut e */

    void afficher () const;
    /* Postcondition : les elements du tableau sont affiches sur la sortie standard (espacement entre les elements)
                       en utilisant la procedure d'affichage de ElementTD */

    void supprimerElement (unsigned int indice);
    /* Precondition : le tableau est non vide, et 0 <= indice < taille_utilisee */
    /* Postcondition : la taille utilisee du tableau est decrementee de 1.
                       si taille_utilisee < capacite/3, alors on divise la capacite par 2. */

    void insererElement (Element e, unsigned int indice);
    /* Precondition : 0 <= indice < taille_utilisee */
    /* Postcondition : e est insere a l'indice en parametre et la taille utilisee est incrementee de 1 */

    void trier ();
    /* Postcondition : le tableau est trie dans l'ordre croissant des valeurs des elements */

    int rechercherElement (Element e) const;
    /* Precondition : le tableau est trie dans l'ordre croissant */
    /* Resultat : indice de l'emplacement qui contient un ElementTD egal a e,
                  -1 si le tableau ne contient pas d'element egal a e */

};

#endif
