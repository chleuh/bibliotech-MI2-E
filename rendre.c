#include <stdio.h>
#include <string.h>
#include "rendre.h"
#include "livre.h"
#include "couleurs.h"

/* -----------------------------------------------
   rendre.c  -  Logique pour rendre un livre
   ----------------------------------------------- */

void rendreLivre(int idLivre, char login[], Livre livres[], int nbLivres, Emprunt emprunts[], int nbEmprunts) {

    // Étape 1 : on cherche l'emprunt qui correspond à cet ID + ce login
    int trouveEmprunt = 0;
    int indexASupprimer = -1;

    for (int i = 0; i < nbEmprunts; i++) {
        if (emprunts[i].idLivre == idLivre && strcmp(emprunts[i].login, login) == 0) {
            trouveEmprunt = 1;
            indexASupprimer = i;
            break; // trouvé, on arrête
        }
    }

    // Si pas trouvé, on prévient et on s'arrête
    if (!trouveEmprunt) {
        printf(ROUGE "\n  ❌ Ce livre ne figure pas dans tes emprunts !\n" RESET);
        return;
    }

    // Étape 2 : on remet le livre disponible
    for (int i = 0; i < nbLivres; i++) {
        if (livres[i].id == idLivre) {
            livres[i].disponible = 1;
            break;
        }
    }

    // Étape 3 : on supprime l'emprunt du tableau
    // Technique : on écrase la case à supprimer par la dernière
    emprunts[indexASupprimer] = emprunts[nbEmprunts - 1];
    nbEmprunts--;

    // Étape 4 : on trie par auteur (A → Z) puis on sauvegarde
    trierAuteursAlpha(livres, nbLivres);
    sauvegarderLivres(livres, nbLivres);

    // Étape 5 : on réécrit le fichier emprunts SANS l'emprunt supprimé
    FILE *f = fopen("txt/emprunts.txt", "w");
    if (f == NULL) {
        printf(ROUGE "  [ERREUR] Impossible d'ouvrir le fichier des emprunts.\n" RESET);
        return;
    }

    for (int i = 0; i < nbEmprunts; i++) {
        fprintf(f, "%d %s %ld\n", emprunts[i].idLivre, emprunts[i].login, emprunts[i].dateEmprunt);
    }
    fclose(f);

    printf(VERT "\n  ✅ Livre rendu avec succès ! Merci 📚\n" RESET);
}