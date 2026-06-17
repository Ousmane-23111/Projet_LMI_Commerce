#include <stdio.h>
#include <stdlib.h>
#include "tas.h"

/* Initialiser le tas */
void tas_init(Tas *t)
{
    t->taille = 0;
}

/* Échanger deux produits */
void echanger(Produit **a, Produit **b)
{
    Produit *tmp = *a;
    *a = *b;	
    *b = tmp;
}

/* Monter un élément vers le haut */
void monter(Tas *t, int i)
{
    int parent = (i - 1) / 2;
    while (i > 0 && t->produits[i]->prix > t->produits[parent]->prix) {
        echanger(&t->produits[i], &t->produits[parent]);
        i      = parent;
        parent = (i - 1) / 2;
    }
}

/* Descendre un élément vers le bas */
void descendre(Tas *t, int i)
{
    int gauche, droite, max;
    while (1) {
        gauche = 2 * i + 1;
        droite = 2 * i + 2;
        max    = i;

        if (gauche < t->taille &&
            t->produits[gauche]->prix > t->produits[max]->prix)
            max = gauche;

        if (droite < t->taille &&
            t->produits[droite]->prix > t->produits[max]->prix)
            max = droite;

        if (max == i) break;

        echanger(&t->produits[i], &t->produits[max]);
        i = max;
    }
}

/* Insérer un produit */
void tas_inserer(Tas *t, Produit *p)
{
    if (t->taille >= TAS_MAX) {
        printf("Tas plein !\n");
        return;
    }
    t->produits[t->taille] = p;
    t->taille++;
    monter(t, t->taille - 1);
    printf("Inséré : %s (%.2f)\n", p->nom, p->prix);
}

/* Extraire le maximum (produit le plus cher) */
Produit *tas_extraire_max(Tas *t)
{
    if (t->taille == 0) {
        printf("Tas vide !\n");
        return NULL;
    }
    Produit *max = t->produits[0];
    t->taille--;
    t->produits[0] = t->produits[t->taille];
    descendre(t, 0);
    return max;
}

/* Afficher le tas */
void tas_afficher(Tas *t)
{
    int i;
    if (t->taille == 0) {
        printf("Tas vide.\n");
        return;
    }
    printf("\n%-5s %-20s %-10s\n", "ID", "Nom", "Prix");
    printf("----------------------------------------\n");
    for (i = 0; i < t->taille; i++) {
        printf("%-5d %-20s %-10.2f\n",
               t->produits[i]->id,
               t->produits[i]->nom,
               t->produits[i]->prix);
    }
    printf("Max (sommet) : %s — %.2f FCFA\n",
           t->produits[0]->nom,
           t->produits[0]->prix);
}

/* Libérer la mémoire */
void tas_liberer(Tas *t)
{
    int i;
    for (i = 0; i < t->taille; i++) {
        free(t->produits[i]->description);
        free(t->produits[i]);
    }
    t->taille = 0;
}
