#include <stdio.h>
#include <time.h>
#include "emprunt.h"

// 1. CHARGER : Lit le fichier des emprunts et les met dans le tableau
int chargerEmprunts(Emprunt emprunts[]) {
    FILE *f = fopen("txt/emprunts.txt", "r");
    if (f == NULL) {a
        return 0; 
    }
    int i = 0;
    while (i < 100) {
        // On lit : ID du livre, Login de l'emprunteur et Date (format long)
        int lus = fscanf(f, "%d %s %ld", 
                         &emprunts[i].idLivre, 
                         emprunts[i].login, 
                         &emprunts[i].dateEmprunt);
        if (lus != 3) {
            break;
        }
        i++; 
    }

    fclose(f);
    return i; 
}

// 2. AJOUTER : Enregistre un nouvel emprunt à la suite du fichier
void ajouterEmprunt(Emprunt e) {
    FILE *f = fopen("txt/emprunts.txt", "a");

    if (f != NULL) {
        fprintf(f, "%d %s %ld\n", e.idLivre, e.login, e.dateEmprunt);
        fclose(f);
    }
}