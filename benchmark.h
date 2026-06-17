#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "structures.h"
#include "tableau_statistique.h"
#include "tableau_dynamique.h"
#include "liste_chainee.h"
#include "abr.h"
#include "tas.h"

/* Générer des produits aléatoires */
void generer_produits(TableauStatique *ts, int n);

/* Benchmarks insertion */
double bench_insertion_ts(int n);
double bench_insertion_td(int n);
double bench_insertion_lc(int n);
double bench_insertion_abr(int n);
double bench_insertion_tas(int n);

/* Afficher les résultats */
void afficher_benchmark(int n);

#endif
