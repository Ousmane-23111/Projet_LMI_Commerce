#include <stdio.h>
#include <string.h>
#include "tri.h"

/* ===== TRI PAR INSERTION SUR LE PRIX ===== */
void tri_insertion_prix(TableauStatique *ts)
{
    int i, j;
    Produit cle;
    for (i = 1; i < ts->nb_produits; i++) {
        cle = ts->produits[i];
        j   = i - 1;
        while (j >= 0 && ts->produits[j].prix > cle.prix) {
            ts->produits[j + 1] = ts->produits[j];
            j--;
        }
        ts->produits[j + 1] = cle;
    }
}

/* ===== TRI PAR INSERTION SUR LE NOM ===== */
void tri_insertion_nom(TableauStatique *ts)
{
    int i, j;
    Produit cle;
    for (i = 1; i < ts->nb_produits; i++) {
        cle = ts->produits[i];
        j   = i - 1;
        while (j >= 0 && strcmp(ts->produits[j].nom, cle.nom) > 0) {
            ts->produits[j + 1] = ts->produits[j];
            j--;
        }
        ts->produits[j + 1] = cle;
    }
}

/* ===== TRI RAPIDE SUR LE PRIX ===== */
int partition_prix(TableauStatique *ts, int gauche, int droite)
{
    float   pivot = ts->produits[droite].prix;
    int     i     = gauche - 1;
    Produit tmp;
    int     j;
    for (j = gauche; j < droite; j++) {
        if (ts->produits[j].prix <= pivot) {
            i++;
            tmp                  = ts->produits[i];
            ts->produits[i]      = ts->produits[j];
            ts->produits[j]      = tmp;
        }
    }
    tmp                      = ts->produits[i + 1];
    ts->produits[i + 1]      = ts->produits[droite];
    ts->produits[droite]     = tmp;
    return i + 1;
}

void tri_rapide_prix(TableauStatique *ts, int gauche, int droite)
{
    if (gauche < droite) {
        int pivot = partition_prix(ts, gauche, droite);
        tri_rapide_prix(ts, gauche,     pivot - 1);
        tri_rapide_prix(ts, pivot + 1,  droite);
    }
}

/* ===== TRI RAPIDE SUR LE NOM ===== */
int partition_nom(TableauStatique *ts, int gauche, int droite)
{
    char   *pivot = ts->produits[droite].nom;
    int     i     = gauche - 1;
    Produit tmp;
    int     j;
    for (j = gauche; j < droite; j++) {
        if (strcmp(ts->produits[j].nom, pivot) <= 0) {
            i++;
            tmp                  = ts->produits[i];
            ts->produits[i]      = ts->produits[j];
            ts->produits[j]      = tmp;
        }
    }
    tmp                      = ts->produits[i + 1];
    ts->produits[i + 1]      = ts->produits[droite];
    ts->produits[droite]     = tmp;
    return i + 1;
}

void tri_rapide_nom(TableauStatique *ts, int gauche, int droite)
{
    if (gauche < droite) {
        int pivot = partition_nom(ts, gauche, droite);
        tri_rapide_nom(ts, gauche,    pivot - 1);
        tri_rapide_nom(ts, pivot + 1, droite);
    }
}
