#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

/* ===== VARIABLES GLOBALES ===== */
TableauStatique ts;
TableauDynamique td;
ListeDouble l;
ABR a;
Tas t;

/* ===== CREER UN PRODUIT ===== */
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

/* ===== VIDER ECRAN ===== */
void vider_ecran()
{
    system("cls");
}

/* ===== PAUSE ===== */
void attendre()
{
    printf("\nAppuyez sur Entree pour continuer...");
    fflush(stdin);
    getchar();
}

/* ===== MENU TABLEAU STATIQUE ===== */
void menu_tableau_statique()
{
    int choix, id, stock;
    char nom[100], categorie[50];
    float prix;

    do {
        vider_ecran();
        printf("=====================================\n");
        printf("        TABLEAU STATIQUE\n");
        printf("=====================================\n");
        printf("1. Ajouter un produit\n");
        printf("2. Afficher tous les produits\n");
        printf("3. Rechercher par ID\n");
        printf("4. Supprimer par ID\n");
        printf("5. Trier par prix\n");
        printf("6. Trier par nom\n");
        printf("7. Statistiques\n");
        printf("0. Retour au menu principal\n");
        printf("=====================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                printf("ID      : "); scanf("%d", &id);
                printf("Nom     : "); scanf("%s", nom);
                printf("Prix    : "); scanf("%f", &prix);
                printf("Stock   : "); scanf("%d", &stock);
                printf("Categorie : "); scanf("%s", categorie);
                ts_inserer(&ts, *creer_produit(id, nom, prix, stock, categorie));
                printf("Produit ajoute avec succes !\n");
                attendre();
                break;

            case 2:
                ts_afficher(&ts);
                attendre();
                break;

            case 3:
                printf("ID a rechercher : ");
                scanf("%d", &id);
                int idx = ts_rechercher_id(&ts, id);
                if (idx != -1)
                    printf("Trouve : %s — %.2f FCFA — Stock : %d\n",
                           ts.produits[idx].nom,
                           ts.produits[idx].prix,
                           ts.produits[idx].stock);
                else
                    printf("Produit introuvable !\n");
                attendre();
                break;

            case 4:
                printf("ID a supprimer : ");
                scanf("%d", &id);
                ts_supprimer(&ts, id);
                attendre();
                break;

            case 5:
                tri_insertion_prix(&ts);
                printf("Tri par prix effectue !\n");
                ts_afficher(&ts);
                attendre();
                break;

            case 6:
                tri_rapide_nom(&ts, 0, ts.nb_produits - 1);
                printf("Tri par nom effectue !\n");
                ts_afficher(&ts);
                attendre();
                break;

            case 7:
                ag_afficher_stats(&ts);
                attendre();
                break;

            case 0:
                break;

            default:
                printf("Choix invalide !\n");
                attendre();
                break;
        }
    } while(choix != 0);
}

/* ===== MENU TABLEAU DYNAMIQUE ===== */
void menu_tableau_dynamique()
{
    int choix, id, stock;
    char nom[100], categorie[50];
    float prix;

    do {
        vider_ecran();
        printf("=====================================\n");
        printf("        TABLEAU DYNAMIQUE\n");
        printf("=====================================\n");
        printf("1. Ajouter un produit\n");
        printf("2. Afficher tous les produits\n");
        printf("3. Rechercher par ID\n");
        printf("4. Supprimer par ID\n");
        printf("0. Retour au menu principal\n");
        printf("=====================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                printf("ID      : "); scanf("%d", &id);
                printf("Nom     : "); scanf("%s", nom);
                printf("Prix    : "); scanf("%f", &prix);
                printf("Stock   : "); scanf("%d", &stock);
                printf("Categorie : "); scanf("%s", categorie);
                td_inserer(&td, creer_produit(id, nom, prix, stock, categorie));
                printf("Produit ajoute avec succes !\n");
                attendre();
                break;

            case 2:
                td_afficher(&td);
                attendre();
                break;

            case 3:
                printf("ID a rechercher : ");
                scanf("%d", &id);
                int idx2 = td_rechercher_id(&td, id);
                if (idx2 != -1)
                    printf("Trouve : %s — %.2f FCFA\n",
                           td.produits[idx2]->nom,
                           td.produits[idx2]->prix);
                else
                    printf("Produit introuvable !\n");
                attendre();
                break;

            case 4:
                printf("ID a supprimer : ");
                scanf("%d", &id);
                td_supprimer(&td, id);
                attendre();
                break;

            case 0:
                break;

            default:
                printf("Choix invalide !\n");
                attendre();
                break;
        }
    } while(choix != 0);
}

/* ===== MENU LISTE CHAINEE ===== */
void menu_liste_chainee()
{
    int choix, id, stock;
    char nom[100], categorie[50];
    float prix;

    do {
        vider_ecran();
        printf("=====================================\n");
        printf("      LISTE DOUBLEMENT CHAINEE\n");
        printf("=====================================\n");
        printf("1. Ajouter en tete\n");
        printf("2. Ajouter en queue\n");
        printf("3. Afficher (ordre normal)\n");
        printf("4. Afficher (ordre inverse)\n");
        printf("5. Rechercher par ID\n");
        printf("6. Supprimer par ID\n");
        printf("0. Retour au menu principal\n");
        printf("=====================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                printf("ID      : "); scanf("%d", &id);
                printf("Nom     : "); scanf("%s", nom);
                printf("Prix    : "); scanf("%f", &prix);
                printf("Stock   : "); scanf("%d", &stock);
                printf("Categorie : "); scanf("%s", categorie);
                lc_inserer_tete(&l, creer_produit(id, nom, prix, stock, categorie));
                printf("Produit ajoute en tete !\n");
                attendre();
                break;

            case 2:
                printf("ID      : "); scanf("%d", &id);
                printf("Nom     : "); scanf("%s", nom);
                printf("Prix    : "); scanf("%f", &prix);
                printf("Stock   : "); scanf("%d", &stock);
                printf("Categorie : "); scanf("%s", categorie);
                lc_inserer_queue(&l, creer_produit(id, nom, prix, stock, categorie));
                printf("Produit ajoute en queue !\n");
                attendre();
                break;

            case 3:
                lc_afficher(&l);
                attendre();
                break;

            case 4:
                lc_afficher_inverse(&l);
                attendre();
                break;

            case 5:
                printf("ID a rechercher : ");
                scanf("%d", &id);
                Noeud *n = lc_rechercher_id(&l, id);
                if (n != NULL)
                    printf("Trouve : %s — %.2f FCFA\n",
                           n->produit->nom, n->produit->prix);
                else
                    printf("Produit introuvable !\n");
                attendre();
                break;

            case 6:
                printf("ID a supprimer : ");
                scanf("%d", &id);
                lc_supprimer(&l, id);
                attendre();
                break;

            case 0:
                break;

            default:
                printf("Choix invalide !\n");
                attendre();
                break;
        }
    } while(choix != 0);
}

/* ===== MENU ABR ===== */
void menu_abr()
{
    int choix, id, stock;
    char nom[100], categorie[50];
    float prix;

    do {
        vider_ecran();
        printf("=====================================\n");
        printf("     ARBRE BINAIRE DE RECHERCHE\n");
        printf("=====================================\n");
        printf("1. Ajouter un produit\n");
        printf("2. Parcours INFIXE (trie par ID)\n");
        printf("3. Parcours PREFIXE\n");
        printf("4. Parcours POSTFIXE\n");
        printf("5. Rechercher par ID\n");
        printf("6. Supprimer par ID\n");
        printf("0. Retour au menu principal\n");
        printf("=====================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                printf("ID      : "); scanf("%d", &id);
                printf("Nom     : "); scanf("%s", nom);
                printf("Prix    : "); scanf("%f", &prix);
                printf("Stock   : "); scanf("%d", &stock);
                printf("Categorie : "); scanf("%s", categorie);
                a.racine = abr_inserer(a.racine,
                           creer_produit(id, nom, prix, stock, categorie));
                printf("Produit ajoute dans l'ABR !\n");
                attendre();
                break;

            case 2:
                printf("\n-- Parcours INFIXE --\n");
                printf("%-5s %-20s %-10s\n", "ID", "Nom", "Prix");
                printf("----------------------------------------\n");
                abr_infixe(a.racine);
                attendre();
                break;

            case 3:
                printf("\n-- Parcours PREFIXE --\n");
                printf("%-5s %-20s %-10s\n", "ID", "Nom", "Prix");
                printf("----------------------------------------\n");
                abr_prefixe(a.racine);
                attendre();
                break;

            case 4:
                printf("\n-- Parcours POSTFIXE --\n");
                printf("%-5s %-20s %-10s\n", "ID", "Nom", "Prix");
                printf("----------------------------------------\n");
                abr_postfixe(a.racine);
                attendre();
                break;

            case 5:
                printf("ID a rechercher : ");
                scanf("%d", &id);
                NoeudABR *trouve = abr_rechercher(a.racine, id);
                if (trouve != NULL)
                    printf("Trouve : %s — %.2f FCFA\n",
                           trouve->produit->nom,
                           trouve->produit->prix);
                else
                    printf("Produit introuvable !\n");
                attendre();
                break;

            case 6:
                printf("ID a supprimer : ");
                scanf("%d", &id);
                a.racine = abr_supprimer(a.racine, id);
                attendre();
                break;

            case 0:
                break;

            default:
                printf("Choix invalide !\n");
                attendre();
                break;
        }
    } while(choix != 0);
}

/* ===== MENU TAS BINAIRE ===== */
void menu_tas()
{
    int choix, id, stock;
    char nom[100], categorie[50];
    float prix;

    do {
        vider_ecran();
        printf("=====================================\n");
        printf("          TAS BINAIRE\n");
        printf("=====================================\n");
        printf("1. Ajouter un produit\n");
        printf("2. Afficher le tas\n");
        printf("3. Extraire le produit le plus cher\n");
        printf("0. Retour au menu principal\n");
        printf("=====================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                printf("ID      : "); scanf("%d", &id);
                printf("Nom     : "); scanf("%s", nom);
                printf("Prix    : "); scanf("%f", &prix);
                printf("Stock   : "); scanf("%d", &stock);
                printf("Categorie : "); scanf("%s", categorie);
                tas_inserer(&t, creer_produit(id, nom, prix, stock, categorie));
                printf("Produit ajoute dans le tas !\n");
                attendre();
                break;

            case 2:
                tas_afficher(&t);
                attendre();
                break;

            case 3:{
            	
                Produit *max = tas_extraire_max(&t);
                if (max != NULL)
                    printf("Produit le plus cher : %s — %.2f FCFA\n",
                           max->nom, max->prix);
                attendre();
                break;
           }
            case 0:
                break;

            default:
                printf("Choix invalide !\n");
                attendre();
                break;
        }
    } while(choix != 0);
}

/* ===== MENU PERSISTANCE ===== */
void menu_persistance()
{
    int choix;

    do {
        vider_ecran();
        printf("=====================================\n");
        printf("           PERSISTANCE\n");
        printf("=====================================\n");
        printf("1. Sauvegarder (Tableau Statique)\n");
        printf("2. Charger (Tableau Statique)\n");
        printf("0. Retour au menu principal\n");
        printf("=====================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                sauvegarder(&ts, "produits.dat");
                attendre();
                break;

            case 2:
                charger(&ts, "produits.dat");
                attendre();
                break;

            case 0:
                break;
        }
    } while(choix != 0);
}

/* ===== MENU BENCHMARK ===== */
void menu_benchmark()
{
    int choix;

    do {
        vider_ecran();
        printf("=====================================\n");
        printf("            BENCHMARKS\n");
        printf("=====================================\n");
        printf("1. Benchmark n = 100\n");
        printf("2. Benchmark n = 1 000\n");
        printf("3. Benchmark n = 10 000\n");
        printf("4. Tous les benchmarks\n");
        printf("0. Retour au menu principal\n");
        printf("=====================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                srand(time(NULL));
                afficher_benchmark(100);
                attendre();
                break;

            case 2:
                srand(time(NULL));
                afficher_benchmark(1000);
                attendre();
                break;

            case 3:
                srand(time(NULL));
                afficher_benchmark(10000);
                attendre();
                break;

            case 4:
                srand(time(NULL));
                afficher_benchmark(100);
                afficher_benchmark(1000);
                afficher_benchmark(10000);
                attendre();
                break;

            case 0:
                break;
        }
    } while(choix != 0);
}

/* ===== MENU PRINCIPAL ===== */
int main()
{
    int choix;

    /* Initialisation des structures */
    ts_init(&ts);
    td_init(&td);
    lc_init(&l);
    abr_init(&a);
    tas_init(&t);

    do {
        vider_ecran();
        printf("=====================================\n");
        printf("    SYSTEME DE COMMERCE EN LIGNE\n");
        printf("    Ousmane Gueye — LMI 2 — 2026\n");
        printf("=====================================\n");
        printf("1. Tableau Statique\n");
        printf("2. Tableau Dynamique\n");
        printf("3. Liste Doublement Chainee\n");
        printf("4. Arbre Binaire de Recherche\n");
        printf("5. Tas Binaire\n");
        printf("6. Persistance (Sauvegarde/Chargement)\n");
        printf("7. Benchmarks\n");
        printf("0. Quitter\n");
        printf("=====================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch(choix) {
            case 1: menu_tableau_statique(); break;
            case 2: menu_tableau_dynamique(); break;
            case 3: menu_liste_chainee(); break;
            case 4: menu_abr(); break;
            case 5: menu_tas(); break;
            case 6: menu_persistance(); break;
            case 7: menu_benchmark(); break;
            case 0:
                printf("\nAu revoir !\n");
                break;
            default:
                printf("Choix invalide !\n");
                attendre();
                break;
        }
    } while(choix != 0);

    /* Liberer la memoire */
    td_liberer(&td);
    lc_liberer(&l);
    abr_liberer(a.racine);

    return 0;
}
