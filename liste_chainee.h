#ifndef LISTE_CHAINEE_H
#define LISTE_CHAINEE_H

#include "structures.h"

/* ===== NOEUD ===== */
typedef struct Noeud {
    Produit      *produit;
    struct Noeud *suivant;
    struct Noeud *precedent;
} Noeud;

/* ===== LISTE ===== */
typedef struct {
    Noeud *tete;
    Noeud *queue;
    int    nb_elements;
} ListeDouble;

/* Prototypes */
void  lc_init(ListeDouble *l);
void  lc_inserer_tete(ListeDouble *l, Produit *p);
void  lc_inserer_queue(ListeDouble *l, Produit *p);
Noeud *lc_rechercher_id(ListeDouble *l, int id);
void  lc_supprimer(ListeDouble *l, int id);
void  lc_afficher(ListeDouble *l);
void  lc_afficher_inverse(ListeDouble *l);
void  lc_liberer(ListeDouble *l);

#endif
