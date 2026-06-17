#ifndef AGREGATIONS_H
#define AGREGATIONS_H

#include "structures.h"
#include "tableau_statistique.h"

/* Agrégations sur le prix */
float ag_minimum(TableauStatique *ts);
float ag_maximum(TableauStatique *ts);
float ag_moyenne(TableauStatique *ts);
float ag_mediane(TableauStatique *ts);
float ag_ecart_type(TableauStatique *ts);
void  ag_afficher_stats(TableauStatique *ts);

#endif
