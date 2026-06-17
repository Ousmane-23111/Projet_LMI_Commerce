#include <stdio.h>
#include <stdlib.h>
#include "abr.h"

/* Initialiser l'arbre */
void abr_init(ABR *a)
{
    a->racine      = NULL;
    a->nb_elements = 0;
}

/* Créer un noeud */
NoeudABR *creer_noeud_abr(Produit *p)
{
    NoeudABR *n = malloc(sizeof(NoeudABR));
    if (n == NULL) {
        printf("Erreur allocation !\n");
        exit(1);
    }
    n->produit = p;
    n->gauche  = NULL;
    n->droite  = NULL;
    return n;
}

/* Insérer — récursif */
NoeudABR *abr_inserer(NoeudABR *racine, Produit *p)
{
    if (racine == NULL)
        return creer_noeud_abr(p);

    if (p->id < racine->produit->id)
        racine->gauche = abr_inserer(racine->gauche, p);
    else if (p->id > racine->produit->id)
        racine->droite = abr_inserer(racine->droite, p);
    else
        printf("ID %d déjà existant !\n", p->id);

    return racine;
}

/* Rechercher par ID — récursif */
NoeudABR *abr_rechercher(NoeudABR *racine, int id)
{
    if (racine == NULL)
        return NULL;
    if (id == racine->produit->id)
        return racine;
    if (id < racine->produit->id)
        return abr_rechercher(racine->gauche, id);
    return abr_rechercher(racine->droite, id);
}

/* Trouver le minimum (noeud le plus à gauche) */
NoeudABR *abr_minimum(NoeudABR *racine)
{
    while (racine->gauche != NULL)
        racine = racine->gauche;
    return racine;
}

/* Supprimer par ID — récursif */
NoeudABR *abr_supprimer(NoeudABR *racine, int id)
{
    if (racine == NULL) {
        printf("Produit introuvable !\n");
        return NULL;
    }

    if (id < racine->produit->id)
        racine->gauche = abr_supprimer(racine->gauche, id);
    else if (id > racine->produit->id)
        racine->droite = abr_supprimer(racine->droite, id);
    else {
        /* Cas 1 : feuille */
        if (racine->gauche == NULL && racine->droite == NULL) {
            free(racine->produit->description);
            free(racine->produit);
            free(racine);
            return NULL;
        }
        /* Cas 2 : un seul enfant */
        else if (racine->gauche == NULL) {
            NoeudABR *tmp = racine->droite;
            free(racine->produit->description);
            free(racine->produit);
            free(racine);
            return tmp;
        }
        else if (racine->droite == NULL) {
            NoeudABR *tmp = racine->gauche;
            free(racine->produit->description);
            free(racine->produit);
            free(racine);
            return tmp;
        }
        /* Cas 3 : deux enfants */
        else {
            NoeudABR *min = abr_minimum(racine->droite);
            racine->produit = min->produit;
            racine->droite  = abr_supprimer(racine->droite,
                                            min->produit->id);
        }
    }
    return racine;
}

/* Parcours infixe — gauche, racine, droite */
void abr_infixe(NoeudABR *racine)
{
    if (racine == NULL) return;
    abr_infixe(racine->gauche);
    printf("%-5d %-20s %-10.2f\n",
           racine->produit->id,
           racine->produit->nom,
           racine->produit->prix);
    abr_infixe(racine->droite);
}

/* Parcours préfixe — racine, gauche, droite */
void abr_prefixe(NoeudABR *racine)
{
    if (racine == NULL) return;
    printf("%-5d %-20s %-10.2f\n",
           racine->produit->id,
           racine->produit->nom,
           racine->produit->prix);
    abr_prefixe(racine->gauche);
    abr_prefixe(racine->droite);
}

/* Parcours postfixe — gauche, droite, racine */
void abr_postfixe(NoeudABR *racine)
{
    if (racine == NULL) return;
    abr_postfixe(racine->gauche);
    abr_postfixe(racine->droite);
    printf("%-5d %-20s %-10.2f\n",
           racine->produit->id,
           racine->produit->nom,
           racine->produit->prix);
}

/* Libérer la mémoire */
void abr_liberer(NoeudABR *racine)
{
    if (racine == NULL) return;
    abr_liberer(racine->gauche);
    abr_liberer(racine->droite);
    free(racine->produit->description);
    free(racine->produit);
    free(racine);
}
