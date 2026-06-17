#ifndef TRI_H
#define TRI_H

#include "structures.h"
#include "tableau_statistique.h"

/* Tri par insertion — O(n²) */
void tri_insertion_prix(TableauStatique *ts);
void tri_insertion_nom(TableauStatique *ts);

/* Tri rapide — O(n log n) */
void tri_rapide_prix(TableauStatique *ts, int gauche, int droite);
void tri_rapide_nom(TableauStatique *ts, int gauche, int droite);

#endif
