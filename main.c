#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "tableau_statistique.h"
#include "tableau_dynamique.h"
#include "abr.h"
#include "tas.h"
#include "tri.h"
#include "agregations.h"

/* Créer un produit dynamiquement */
Produit *creer_produit(int id, char *nom, float prix,
                       int stock, char *categorie)
{
    Produit *p = malloc(sizeof(Produit));
    p->id = id;
    strcpy(p->nom, nom);
    p->prix = prix;
    p->stock = stock;
    strcpy(p->categorie, categorie);
    p->date_ajout.jour = 11;
    p->date_ajout.mois = 6;
    p->date_ajout.annee = 2026;
    p->description = malloc(100 * sizeof(char));
    strcpy(p->description, "Description produit");
    return p;
}

int main()
{
    /* ===== TEST TABLEAU STATIQUE ===== */
    printf("=============================\n");
    printf("   TEST TABLEAU STATIQUE\n");
    printf("=============================\n");

    TableauStatique ts;
    ts_init(&ts);

    ts_inserer(&ts, *creer_produit(1, "Samsung Galaxy", 150000, 10, "Electronique"));
    ts_inserer(&ts, *creer_produit(2, "iPhone 14",      450000,  5, "Electronique"));
    ts_inserer(&ts, *creer_produit(3, "Nike Air Max",    75000, 20, "Chaussures"));

    printf("\n-- Apres insertion --");
    ts_afficher(&ts);

    printf("\nRecherche ID=2 : ");
    int idx = ts_rechercher_id(&ts, 2);
    if (idx != -1)
        printf("Trouve : %s\n", ts.produits[idx].nom);

    printf("\n-- Suppression ID=2 --\n");
    ts_supprimer(&ts, 2);
    ts_afficher(&ts);

    /* ===== TEST TABLEAU DYNAMIQUE ===== */
    printf("\n=============================\n");
    printf("   TEST TABLEAU DYNAMIQUE\n");
    printf("=============================\n");

    TableauDynamique td;
    td_init(&td);

    td_inserer(&td, creer_produit(1, "Samsung Galaxy", 150000, 10, "Electronique"));
    td_inserer(&td, creer_produit(2, "iPhone 14",      450000,  5, "Electronique"));
    td_inserer(&td, creer_produit(3, "Nike Air Max",    75000, 20, "Chaussures"));
    td_inserer(&td, creer_produit(4, "HP Laptop",      350000,  8, "Informatique"));
    /* Ce 5ème insert va déclencher le realloc ! */
    td_inserer(&td, creer_produit(5, "Adidas Boost",    65000, 15, "Chaussures"));

    printf("\n-- Apres insertion --");
    td_afficher(&td);

    printf("\nRecherche ID=3 : ");
    int idx2 = td_rechercher_id(&td, 3);
    if (idx2 != -1)
        printf("Trouve : %s\n", td.produits[idx2]->nom);

    printf("\n-- Suppression ID=2 --\n");
    td_supprimer(&td, 2);
    td_afficher(&td);

    td_liberer(&td);

/* ===== TEST ABR ===== */
printf("\n=============================\n");
printf("       TEST ABR\n");
printf("=============================\n");

ABR a;
abr_init(&a);

a.racine = abr_inserer(a.racine, creer_produit(3, "Nike Air Max",   75000, 20, "Chaussures"));
a.racine = abr_inserer(a.racine, creer_produit(1, "Samsung Galaxy",150000, 10, "Electronique"));
a.racine = abr_inserer(a.racine, creer_produit(5, "HP Laptop",     350000,  8, "Informatique"));
a.racine = abr_inserer(a.racine, creer_produit(2, "Nike Air Max",   75000, 20, "Chaussures"));
a.racine = abr_inserer(a.racine, creer_produit(4, "Adidas Boost",   65000, 15, "Chaussures"));

printf("\n-- Parcours INFIXE (trié par ID) --\n");
printf("%-5s %-20s %-10s\n", "ID", "Nom", "Prix");
printf("----------------------------------------\n");
abr_infixe(a.racine);

printf("\n-- Parcours PREFIXE --\n");
printf("%-5s %-20s %-10s\n", "ID", "Nom", "Prix");
printf("----------------------------------------\n");
abr_prefixe(a.racine);

printf("\n-- Parcours POSTFIXE --\n");
printf("%-5s %-20s %-10s\n", "ID", "Nom", "Prix");
printf("----------------------------------------\n");
abr_postfixe(a.racine);

printf("\nRecherche ID=4 : ");
NoeudABR *trouve = abr_rechercher(a.racine, 4);
if (trouve != NULL)
    printf("Trouve : %s\n", trouve->produit->nom);

printf("\n-- Suppression ID=3 --\n");
a.racine = abr_supprimer(a.racine, 3);
printf("Apres suppression - Parcours infixe :\n");
abr_infixe(a.racine);

abr_liberer(a.racine);

/* ===== TEST TAS BINAIRE ===== */
printf("\n=============================\n");
printf("     TEST TAS BINAIRE\n");
printf("=============================\n");

Tas t;
tas_init(&t);

tas_inserer(&t, creer_produit(1, "Samsung Galaxy", 150000, 10, "Electronique"));
tas_inserer(&t, creer_produit(2, "iPhone 14",      450000,  5, "Electronique"));
tas_inserer(&t, creer_produit(3, "Nike Air Max",    75000, 20, "Chaussures"));
tas_inserer(&t, creer_produit(4, "HP Laptop",      350000,  8, "Informatique"));
tas_inserer(&t, creer_produit(5, "Adidas Boost",    65000, 15, "Chaussures"));

printf("\n-- Contenu du tas --");
tas_afficher(&t);

printf("\n-- Extraction du maximum --\n");
Produit *max = tas_extraire_max(&t);
if (max != NULL)
    printf("Produit le plus cher : %s — %.2f FCFA\n",
           max->nom, max->prix);

printf("\n-- Tas apres extraction --");
tas_afficher(&t);

tas_liberer(&t);
/* ===== TEST TRI ET AGREGATIONS ===== */
printf("\n=============================\n");
printf("   TEST TRI ET AGREGATIONS\n");
printf("=============================\n");

/* Remplir un tableau pour les tests */
TableauStatique ts2;
ts_init(&ts2);
ts_inserer(&ts2, *creer_produit(1, "Samsung Galaxy", 150000, 10, "Electronique"));
ts_inserer(&ts2, *creer_produit(2, "iPhone 14",      450000,  5, "Electronique"));
ts_inserer(&ts2, *creer_produit(3, "Nike Air Max",    75000, 20, "Chaussures"));
ts_inserer(&ts2, *creer_produit(4, "HP Laptop",      350000,  8, "Informatique"));
ts_inserer(&ts2, *creer_produit(5, "Adidas Boost",    65000, 15, "Chaussures"));

/* Tri par insertion sur le prix */
printf("\n-- Tri par insertion (prix croissant) --");
tri_insertion_prix(&ts2);
ts_afficher(&ts2);

/* Tri rapide sur le nom */
printf("\n-- Tri rapide (nom alphabetique) --");
tri_rapide_nom(&ts2, 0, ts2.nb_produits - 1);
ts_afficher(&ts2);

/* Agregations */
ag_afficher_stats(&ts2);
    return 0;
}
