#include <stdio.h>
#include <math.h>
#include "agregations.h"
#include "tri.h"

/* Minimum */
float ag_minimum(TableauStatique *ts)
{
    int i;
    float min = ts->produits[0].prix;
    for (i = 1; i < ts->nb_produits; i++) {
        if (ts->produits[i].prix < min)
            min = ts->produits[i].prix;
    }
    return min;
}

/* Maximum */
float ag_maximum(TableauStatique *ts)
{
    int i;
    float max = ts->produits[0].prix;
    for (i = 1; i < ts->nb_produits; i++) {
        if (ts->produits[i].prix > max)
            max = ts->produits[i].prix;
    }
    return max;
}

/* Moyenne */
float ag_moyenne(TableauStatique *ts)
{
    int i;
    float somme = 0;
    for (i = 0; i < ts->nb_produits; i++)
        somme += ts->produits[i].prix;
    return somme / ts->nb_produits;
}

/* Médiane */
float ag_mediane(TableauStatique *ts)
{
    TableauStatique copie = *ts;
    tri_insertion_prix(&copie);
    int n = copie.nb_produits;
    if (n % 2 == 0)
        return (copie.produits[n/2 - 1].prix +
                copie.produits[n/2].prix) / 2.0;
    else
        return copie.produits[n/2].prix;
}

/* Écart-type */
float ag_ecart_type(TableauStatique *ts)
{
    int i;
    float moy   = ag_moyenne(ts);
    float somme = 0;
    for (i = 0; i < ts->nb_produits; i++) {
        float diff = ts->produits[i].prix - moy;
        somme += diff * diff;
    }
    return sqrt(somme / ts->nb_produits);
}

/* Afficher toutes les stats */
void ag_afficher_stats(TableauStatique *ts)
{
    printf("\n===== STATISTIQUES SUR LES PRIX =====\n");
    printf("Nombre de produits : %d\n",       ts->nb_produits);
    printf("Minimum            : %.2f FCFA\n", ag_minimum(ts));
    printf("Maximum            : %.2f FCFA\n", ag_maximum(ts));
    printf("Moyenne            : %.2f FCFA\n", ag_moyenne(ts));
    printf("Mediane            : %.2f FCFA\n", ag_mediane(ts));
    printf("Ecart-type         : %.2f FCFA\n", ag_ecart_type(ts));
    printf("=====================================\n");
}
