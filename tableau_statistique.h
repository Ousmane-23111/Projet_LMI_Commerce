#ifndef TABLEAU_STATISTIQUE_H
#define TABLEAU_STATISTIQUE_H

#include "structures.h"

#define MAX 100

typedef struct {
    Produit produits[MAX];
    int     nb_produits;
} TableauStatique;

/* Prototypes des fonctions */
void ts_init(TableauStatique *ts);
int  ts_inserer(TableauStatique *ts, Produit p);
int  ts_rechercher_id(TableauStatique *ts, int id);
void ts_afficher(TableauStatique *ts);
void ts_supprimer(TableauStatique *ts, int id);

#endif
