#ifndef TABLEAU_DYNAMIQUE_H
#define TABLEAU_DYNAMIQUE_H

#include "structures.h"

#define CAPACITE_INITIALE 4
#define FACTEUR_CROISSANCE 2

typedef struct {
    Produit **produits;   /* tableau de pointeurs vers Produit */
    int       nb_produits;
    int       capacite;
} TableauDynamique;

/* Prototypes */
void td_init(TableauDynamique *td);
int  td_inserer(TableauDynamique *td, Produit *p);
int  td_rechercher_id(TableauDynamique *td, int id);
void td_supprimer(TableauDynamique *td, int id);
void td_afficher(TableauDynamique *td);
void td_liberer(TableauDynamique *td);

#endif
