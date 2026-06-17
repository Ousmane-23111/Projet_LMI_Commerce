#ifndef STRUCTURES_H
#define STRUCTURES_H

/* ===== DATE ===== */
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

/* ===== PRODUIT ===== */
typedef struct {
    int    id;
    char   nom[100];
    char  *description;   /* longueur variable */
    float  prix;
    int    stock;
    char   categorie[50];
    Date   date_ajout;
} Produit;

/* ===== LIGNE DE COMMANDE ===== */
typedef struct {
    Produit *produit;
    int      quantite;
    float    prix_unitaire;
} LigneCommande;

/* ===== COMMANDE ===== */
typedef struct {
    int            id;
    Date           date_commande;
    float          montant_total;
    char           statut[20];
    LigneCommande *lignes;
    int            nb_lignes;
} Commande;

/* ===== CLIENT ===== */
typedef struct {
    int       id;
    char      nom[100];
    char     *email;       /* longueur variable */
    float     solde;
    int       nb_commandes;
    Date      date_inscription;
    Commande *commandes;   /* tableau de commandes */
} Client;

#endif
