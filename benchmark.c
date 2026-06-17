#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "benchmark.h"
#include "tri.h"

/* Générer un produit aléatoire */
Produit *generer_produit_aleatoire(int id)
{
    Produit *p = malloc(sizeof(Produit));
    p->id      = id;
    p->prix    = (float)(rand() % 500000 + 1000);
    p->stock   = rand() % 100 + 1;
    p->description = malloc(50 * sizeof(char));

    sprintf(p->nom,         "Produit_%d", id);
    sprintf(p->categorie,   "Cat_%d", rand() % 5);
    sprintf(p->description, "Description_%d", id);

    p->date_ajout.jour  = rand() % 28 + 1;
    p->date_ajout.mois  = rand() % 12 + 1;
    p->date_ajout.annee = 2026;
    return p;
}

/* Benchmark insertion tableau statique */
double bench_insertion_ts(int n)
{
    TableauStatique ts;
    ts_init(&ts);
    clock_t debut = clock();
    int i;
    for (i = 0; i < n && i < MAX; i++) {
        Produit *p = generer_produit_aleatoire(i + 1);
        ts_inserer(&ts, *p);
        free(p->description);
        free(p);
    }
    clock_t fin = clock();
    return (double)(fin - debut) / CLOCKS_PER_SEC * 1000;
}

/* Benchmark insertion tableau dynamique */
double bench_insertion_td(int n)
{
    TableauDynamique td;
    td_init(&td);
    clock_t debut = clock();
    int i;
    for (i = 0; i < n; i++) {
        Produit *p = generer_produit_aleatoire(i + 1);
        td_inserer(&td, p);
    }
    clock_t fin = clock();
    td_liberer(&td);
    return (double)(fin - debut) / CLOCKS_PER_SEC * 1000;
}

/* Benchmark insertion liste chainee */
double bench_insertion_lc(int n)
{
    ListeDouble l;
    lc_init(&l);
    clock_t debut = clock();
    int i;
    for (i = 0; i < n; i++) {
        Produit *p = generer_produit_aleatoire(i + 1);
        lc_inserer_queue(&l, p);
    }
    clock_t fin = clock();
    lc_liberer(&l);
    return (double)(fin - debut) / CLOCKS_PER_SEC * 1000;
}

/* Benchmark insertion ABR */
double bench_insertion_abr(int n)
{
    ABR a;
    abr_init(&a);
    clock_t debut = clock();
    int i;
    for (i = 0; i < n; i++) {
        Produit *p = generer_produit_aleatoire(i + 1);
        a.racine = abr_inserer(a.racine, p);
    }
    clock_t fin = clock();
    abr_liberer(a.racine);
    return (double)(fin - debut) / CLOCKS_PER_SEC * 1000;
}

/* Benchmark insertion tas */
double bench_insertion_tas(int n)
{
    Tas t;
    tas_init(&t);
    clock_t debut = clock();
    int i;
    for (i = 0; i < n && i < TAS_MAX; i++) {
        Produit *p = generer_produit_aleatoire(i + 1);
        tas_inserer(&t, p);
    }
    clock_t fin = clock();
    tas_liberer(&t);
    return (double)(fin - debut) / CLOCKS_PER_SEC * 1000;
}

/* Afficher benchmark pour une taille n */
void afficher_benchmark(int n)
{
    printf("\n--- Benchmark n = %d ---\n", n);
    printf("%-25s %-15s\n", "Structure", "Temps (ms)");
    printf("----------------------------------------\n");
    printf("%-25s %-15.4f\n", "Tableau statique",   bench_insertion_ts(n));
    printf("%-25s %-15.4f\n", "Tableau dynamique",  bench_insertion_td(n));
    printf("%-25s %-15.4f\n", "Liste chainee",      bench_insertion_lc(n));
    printf("%-25s %-15.4f\n", "ABR",                bench_insertion_abr(n));
    printf("%-25s %-15.4f\n", "Tas binaire",        bench_insertion_tas(n));
}
