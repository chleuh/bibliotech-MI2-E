#include <stdio.h>
#include <time.h>
#include "emprunt.h"

// 1. CHARGER : Lit le fichier des emprunts et les met dans le tableau
int chargerEmprunts(Emprunt emprunts[]) {
    FILE *f = fopen("txt/emprunts.txt", "r");

    if (f == NULL) {
        return 0; 
    }

    int i = 0;
    while (i < 100) {
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

// 2. AJOUTER : Ajoute un emprunt à la fin du fichier texte
void ajouterEmprunt(Emprunt e) {
    // Mode "a" : ouvre le fichier en mode ajout à la fin
    FILE *f = fopen("txt/emprunts.txt", "a");

    if (f != NULL) {
        fprintf(f, "%d %s %ld\n", e.idLivre, e.login, e.dateEmprunt);
        fclose(f);
    }
}