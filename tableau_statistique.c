#include <stdio.h>
#include <string.h>
#include "tableau_statistique.h"

/* Initialiser le tableau */
void ts_init(TableauStatique *ts)
{
    ts->nb_produits = 0;
} 

/* Insérer un produit */
int ts_inserer(TableauStatique *ts, Produit p)
{
    if (ts->nb_produits >= MAX) {
        printf("Tableau plein !\n");
        return 0;
    }
    ts->produits[ts->nb_produits] = p;
    ts->nb_produits++;
    return 1;
}

/* Rechercher par ID — retourne l'indice ou -1 */
int ts_rechercher_id(TableauStatique *ts, int id)
{
    int i;
    for (i = 0; i < ts->nb_produits; i++) {
        if (ts->produits[i].id == id)
            return i;
    }
    return -1;
}

/* Supprimer par ID */
void ts_supprimer(TableauStatique *ts, int id)
{
    int i;
    int indice = ts_rechercher_id(ts, id);
    if (indice == -1) {
        printf("Produit introuvable !\n");
        return;
    }
    for (i = indice; i < ts->nb_produits - 1; i++) {
        ts->produits[i] = ts->produits[i+1];
    }
    ts->nb_produits--;
    printf("Produit supprimé.\n");
}

/* Afficher tous les produits */
void ts_afficher(TableauStatique *ts)
{
    int i;
    if (ts->nb_produits == 0) {
        printf("Tableau vide.\n");
        return;
    }
    printf("\n%-5s %-20s %-10s %-8s\n",
           "ID", "Nom", "Prix", "Stock");
    printf("----------------------------------------\n");
    for (i = 0; i < ts->nb_produits; i++) {
        printf("%-5d %-20s %-10.2f %-8d\n",
               ts->produits[i].id,
               ts->produits[i].nom,
               ts->produits[i].prix,
               ts->produits[i].stock);
    }
}
