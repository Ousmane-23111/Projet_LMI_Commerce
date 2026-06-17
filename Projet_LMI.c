#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "tableau_statistique.h"
#include "tableau_dynamique.h"
#include "liste_chainee.h"
#include "abr.h"
#include "tas.h"
#include "tri.h"
#include "agregations.h"
#include "persistance.h"
#include "benchmark.h"



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
    p->date_ajout.jour  = 15;
    p->date_ajout.mois  = 6;
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
    ts_inserer(&ts, *creer_produit(4, "HP Laptop",      350000,  8, "Informatique"));
    ts_inserer(&ts, *creer_produit(5, "Adidas Boost",    65000, 15, "Chaussures"));
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
    td_inserer(&td, creer_produit(5, "Adidas Boost",    65000, 15, "Chaussures"));
    td_afficher(&td);
    td_liberer(&td);

    /* ===== TEST LISTE CHAINEE ===== */
    printf("\n=============================\n");
    printf("   TEST LISTE CHAINEE\n");
    printf("=============================\n");
    ListeDouble l;
    lc_init(&l);
    lc_inserer_queue(&l, creer_produit(1, "Samsung Galaxy", 150000, 10, "Electronique"));
    lc_inserer_queue(&l, creer_produit(2, "iPhone 14",      450000,  5, "Electronique"));
    lc_inserer_queue(&l, creer_produit(3, "Nike Air Max",    75000, 20, "Chaussures"));
    lc_afficher(&l);
    lc_liberer(&l);

    /* ===== TEST ABR ===== */
    printf("\n=============================\n");
    printf("       TEST ABR\n");
    printf("=============================\n");
    ABR a;
    abr_init(&a);
    a.racine = abr_inserer(a.racine, creer_produit(3, "Nike Air Max",   75000, 20, "Chaussures"));
    a.racine = abr_inserer(a.racine, creer_produit(1, "Samsung Galaxy",150000, 10, "Electronique"));
    a.racine = abr_inserer(a.racine, creer_produit(5, "HP Laptop",     350000,  8, "Informatique"));
    a.racine = abr_inserer(a.racine, creer_produit(2, "Adidas Boost",   65000, 15, "Chaussures"));
    a.racine = abr_inserer(a.racine, creer_produit(4, "iPhone 14",     450000,  5, "Electronique"));
    printf("\n-- Parcours INFIXE --\n");
    abr_infixe(a.racine);
    abr_liberer(a.racine);

    /* ===== TEST TAS ===== */
    printf("\n=============================\n");
    printf("     TEST TAS BINAIRE\n");
    printf("=============================\n");
    Tas t;
    tas_init(&t);
    tas_inserer(&t, creer_produit(1, "Samsung Galaxy", 150000, 10, "Electronique"));
    tas_inserer(&t, creer_produit(2, "iPhone 14",      450000,  5, "Electronique"));
    tas_inserer(&t, creer_produit(3, "Nike Air Max",    75000, 20, "Chaussures"));
    tas_afficher(&t);
    tas_liberer(&t);

    /* ===== TEST TRI ET STATS ===== */
    printf("\n=============================\n");
    printf("   TEST TRI ET AGREGATIONS\n");
    printf("=============================\n");
    TableauStatique ts2;
    ts_init(&ts2);
    ts_inserer(&ts2, *creer_produit(1, "Samsung Galaxy", 150000, 10, "Electronique"));
    ts_inserer(&ts2, *creer_produit(2, "iPhone 14",      450000,  5, "Electronique"));
    ts_inserer(&ts2, *creer_produit(3, "Nike Air Max",    75000, 20, "Chaussures"));
    ts_inserer(&ts2, *creer_produit(4, "HP Laptop",      350000,  8, "Informatique"));
    ts_inserer(&ts2, *creer_produit(5, "Adidas Boost",    65000, 15, "Chaussures"));
    printf("\n-- Tri par insertion (prix) --\n");
    tri_insertion_prix(&ts2);
    ts_afficher(&ts2);
    printf("\n-- Tri rapide (nom) --\n");
    tri_rapide_nom(&ts2, 0, ts2.nb_produits - 1);
    ts_afficher(&ts2);
    ag_afficher_stats(&ts2);
    
    /* ===== TEST PERSISTANCE ===== */
printf("\n=============================\n");
printf("     TEST PERSISTANCE\n");
printf("=============================\n");

/* Sauvegarder */
sauvegarder(&ts, "produits.dat");

/* Charger dans un nouveau tableau */
TableauStatique ts3;
ts_init(&ts3);
charger(&ts3, "produits.dat");

printf("\n-- Produits charges depuis fichier --");
ts_afficher(&ts3);

/* ===== BENCHMARKS ===== */
printf("\n=============================\n");
printf("       BENCHMARKS\n");
printf("=============================\n");

srand(time(NULL));

afficher_benchmark(100);
afficher_benchmark(1000);
afficher_benchmark(10000);
afficher_benchmark(2200 );
    return 0;
}
