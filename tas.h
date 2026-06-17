				#ifndef TAS_H
#define TAS_H

#include "structures.h"

#define TAS_MAX 100

typedef struct {
    Produit *produits[TAS_MAX];
    int      taille;
} Tas;

/* Prototypes */
void     tas_init(Tas *t);
void     tas_inserer(Tas *t, Produit *p);
Produit *tas_extraire_max(Tas *t);
void     tas_afficher(Tas *t);
void     tas_liberer(Tas *t);

#endif
