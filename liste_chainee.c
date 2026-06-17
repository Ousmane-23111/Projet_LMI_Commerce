#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste_chainee.h"

/* Initialiser la liste */
void lc_init(ListeDouble *l)
{
    l->tete = NULL;
    l->queue = NULL;
    l->nb_elements = 0;
}

/* Créer un nouveau noeud */
Noeud *creer_noeud(Produit *p)
{
    Noeud *n = malloc(sizeof(Noeud));
    if (n == NULL) {
        printf("Erreur allocation noeud !\n");
        exit(1);
    }
    n->produit   = p;
    n->suivant   = NULL;
    n->precedent = NULL;
    return n;
}

/* Insérer en tête — O(1) */
void lc_inserer_tete(ListeDouble *l, Produit *p)
{
    Noeud *n = creer_noeud(p);
    if (l->tete == NULL) {
        l->tete  = n;
        l->queue = n;
    } else {
        n->suivant        = l->tete;
        l->tete->precedent = n;
        l->tete           = n;
    }
    l->nb_elements++;
}

/* Insérer en queue — O(1) */
void lc_inserer_queue(ListeDouble *l, Produit *p)
{
    Noeud *n = creer_noeud(p);
    if (l->queue == NULL) {
        l->tete  = n;
        l->queue = n;
    } else {
        n->precedent      = l->queue;
        l->queue->suivant = n;
        l->queue          = n;
    }
    l->nb_elements++;
}

/* Rechercher par ID */
Noeud *lc_rechercher_id(ListeDouble *l, int id)
{
    Noeud *courant = l->tete;
    while (courant != NULL) {
        if (courant->produit->id == id)
            return courant;
        courant = courant->suivant;
    }
    return NULL;
}

/* Supprimer par ID */
void lc_supprimer(ListeDouble *l, int id)
{
    Noeud *n = lc_rechercher_id(l, id);
    if (n == NULL) {
        printf("Produit introuvable !\n");
        return;
    }
    if (n->precedent != NULL)
        n->precedent->suivant = n->suivant;
    else
        l->tete = n->suivant;

    if (n->suivant != NULL)
        n->suivant->precedent = n->precedent;
    else
        l->queue = n->precedent;

    free(n->produit->description);
    free(n->produit);
    free(n);
    l->nb_elements--;
    printf("Produit supprimé.\n");
}

/* Afficher dans l'ordre normal */
void lc_afficher(ListeDouble *l)
{
    Noeud *courant = l->tete;
    if (courant == NULL) {
        printf("Liste vide.\n");
        return;
    }
    printf("\n%-5s %-20s %-10s %-8s\n",
           "ID", "Nom", "Prix", "Stock");
    printf("----------------------------------------\n");
    while (courant != NULL) {
        printf("%-5d %-20s %-10.2f %-8d\n",
               courant->produit->id,
               courant->produit->nom,
               courant->produit->prix,
               courant->produit->stock);
        courant = courant->suivant;
    }
}

/* Afficher en sens inverse */
void lc_afficher_inverse(ListeDouble *l)
{
    Noeud *courant = l->queue;
    if (courant == NULL) {
        printf("Liste vide.\n");
        return;
    }
    printf("\n--- Affichage inverse ---\n");
    printf("%-5s %-20s %-10s %-8s\n",
           "ID", "Nom", "Prix", "Stock");
    printf("----------------------------------------\n");
    while (courant != NULL) {
        printf("%-5d %-20s %-10.2f %-8d\n",
               courant->produit->id,
               courant->produit->nom,
               courant->produit->prix,
               courant->produit->stock);
        courant = courant->precedent;
    }
}

/* Libérer la mémoire */
void lc_liberer(ListeDouble *l)
{
    Noeud *courant = l->tete;
    Noeud *suivant;
    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant->produit->description);
        free(courant->produit);
        free(courant);
        courant = suivant;
    }
    l->tete = NULL;
    l->queue = NULL;
    l->nb_elements = 0;
}
