#ifndef ABR_H
#define ABR_H

#include "structures.h"

/* ===== NOEUD ABR ===== */
typedef struct NoeudABR {
    Produit        *produit;
    struct NoeudABR *gauche;
    struct NoeudABR *droite;
} NoeudABR;

/* ===== ARBRE ===== */
typedef struct {
    NoeudABR *racine;
    int       nb_elements;
} ABR;

/* Prototypes */
void      abr_init(ABR *a);
NoeudABR *abr_inserer(NoeudABR *racine, Produit *p);
NoeudABR *abr_rechercher(NoeudABR *racine, int id);
NoeudABR *abr_supprimer(NoeudABR *racine, int id);
void      abr_infixe(NoeudABR *racine);
void      abr_prefixe(NoeudABR *racine);
void      abr_postfixe(NoeudABR *racine);
void      abr_liberer(NoeudABR *racine);

#endif
