#ifndef PERSISTANCE_H
#define PERSISTANCE_H

#include "structures.h"
#include "tableau_statistique.h"

/* Sauvegarder les produits dans un fichier binaire */
void sauvegarder(TableauStatique *ts, char *nom_fichier);

/* Charger les produits depuis un fichier binaire */
void charger(TableauStatique *ts, char *nom_fichier);

#endif
