#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tableau_dynamique.h"

/* Initialiser le tableau dynamique */
void td_init(TableauDynamique *td)
{
    td->capacite = CAPACITE_INITIALE;
    td->nb_produits = 0;
    td->produits = malloc(td->capacite * sizeof(Produit *));
    if (td->produits == NULL) {
        printf("Erreur allocation mémoire !\n");
        exit(1);
    }
}

/* Insérer un produit */
int td_inserer(TableauDynamique *td, Produit *p)
{
    /* Tableau plein — on double la capacité */
    if (td->nb_produits >= td->capacite) {
        td->capacite *= FACTEUR_CROISSANCE;
        td->produits = realloc(td->produits, 
                       td->capacite * sizeof(Produit *));
        if (td->produits == NULL) {
            printf("Erreur realloc !\n");
            exit(1);
        }
    }
    td->produits[td->nb_produits] = p;
    td->nb_produits++;
    return 1;
}

/* Rechercher par ID */
int td_rechercher_id(TableauDynamique *td, int id)
{
    int i;
    for (i = 0; i < td->nb_produits; i++) {
        if (td->produits[i]->id == id)
            return i;
    }
    return -1;
}

/* Supprimer par ID */
void td_supprimer(TableauDynamique *td, int id)
{
    int i;
    int indice = td_rechercher_id(td, id);
    if (indice == -1) {
        printf("Produit introuvable !\n");
        return;
    }
    free(td->produits[indice]->description);
    free(td->produits[indice]);
    for (i = indice; i < td->nb_produits - 1; i++) {
        td->produits[i] = td->produits[i+1];
    }
    td->nb_produits--;
    printf("Produit supprimé.\n");
}

/* Afficher tous les produits */
void td_afficher(TableauDynamique *td)
{
    int i;
    if (td->nb_produits == 0) {
        printf("Tableau vide.\n");
        return;
    }
    printf("\n%-5s %-20s %-10s %-8s\n",
           "ID", "Nom", "Prix", "Stock");
    printf("----------------------------------------\n");
    for (i = 0; i < td->nb_produits; i++) {
        printf("%-5d %-20s %-10.2f %-8d\n",
               td->produits[i]->id,
               td->produits[i]->nom,
               td->produits[i]->prix,
               td->produits[i]->stock);
    }
}

/* Libérer la mémoire */
void td_liberer(TableauDynamique *td)
{
    int i;
    for (i = 0; i < td->nb_produits; i++) {
        free(td->produits[i]->description);
        free(td->produits[i]);
    }
    free(td->produits);
    td->nb_produits = 0;
    td->capacite = 0;
}
