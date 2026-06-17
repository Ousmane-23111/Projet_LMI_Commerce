#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "persistance.h"

/* Sauvegarder dans un fichier binaire */
void sauvegarder(TableauStatique *ts, char *nom_fichier)
{
    FILE *f = fopen(nom_fichier, "wb");
    if (f == NULL) {
        printf("Erreur ouverture fichier !\n");
        return;
    }

    /* Sauvegarder le nombre de produits */
    fwrite(&ts->nb_produits, sizeof(int), 1, f);

    /* Sauvegarder chaque produit */
    int i;
    for (i = 0; i < ts->nb_produits; i++) {
        fwrite(&ts->produits[i], sizeof(Produit), 1, f);

        /* Sauvegarder la description (longueur variable) */
        int len = strlen(ts->produits[i].description) + 1;
        fwrite(&len, sizeof(int), 1, f);
        fwrite(ts->produits[i].description, sizeof(char), len, f);
    }

    fclose(f);
    printf("? %d produits sauvegardés dans '%s'\n",
           ts->nb_produits, nom_fichier);
}

/* Charger depuis un fichier binaire */
void charger(TableauStatique *ts, char *nom_fichier)
{
    FILE *f = fopen(nom_fichier, "rb");
    if (f == NULL) {
        printf("Fichier '%s' introuvable !\n", nom_fichier);
        return;
    }

    /* Lire le nombre de produits */
    int nb;
    fread(&nb, sizeof(int), 1, f);
    ts->nb_produits = 0;

    /* Lire chaque produit */
    int i;
    for (i = 0; i < nb; i++) {
        Produit p;
        fread(&p, sizeof(Produit), 1, f);

        /* Lire la description */
        int len;
        fread(&len, sizeof(int), 1, f);
        p.description = malloc(len * sizeof(char));
        fread(p.description, sizeof(char), len, f);

        ts_inserer(ts, p);
    }

    fclose(f);
    printf("? %d produits chargés depuis '%s'\n",
           nb,nom_fichier);
}
