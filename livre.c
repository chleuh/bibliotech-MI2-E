#include <stdio.h>
#include "livre.h"

// Charge les livres depuis le fichier
int chargerLivres(Livre livres[]) {
    FILE *f = fopen("txt/livres.txt", "r");
    if (f == NULL) return 0;
    int i = 0;
    // On boucle tant qu'on a de la place dans le tableau
    while (i < 100) {
        int score = fscanf(f, "%d %s %s %s %d", 
                           &livres[i].id, 
                           livres[i].titre, 
                           livres[i].auteur, 
                           livres[i].categorie, 
                           &livres[i].disponible);
        if (score != 5) {
            break; 
        }
        i++;
    }

    fclose(f);
    return i; // On renvoie le nombre total de livres lus
}

// Affiche uniquement les livres DISPONIBLES (disponible == 1)
void afficherLivres(Livre livres[], int n) {
    printf("\n--- Liste des Livres Disponibles ---\n");
    int compteur = 0;

    // Boucle qui parcourt le tableau de livres
    for (int i = 0; i < n; i++) {
        if (livres[i].disponible == 1) {
            printf("ID: %d | %s - %s [%s]\n", 
                   livres[i].id, 
                   livres[i].titre, 
                   livres[i].auteur, 
                   livres[i].categorie);
            compteur++; 
        }
    }
    if (compteur == 0) {
        printf("Aucun livre disponible en rayon.\n");
    }
}

// NOUVEAU : Affiche uniquement les livres EMPRUNTÉS (disponible == 0)
void afficherLivresEmpruntes(Livre livres[], int n) {
    printf("\n--- Liste des Livres Empruntes ---\n");
    int compteur = 0;

    // On parcourt la liste des livres
    for (int i = 0; i < n; i++) {
        if (livres[i].disponible == 0) {
            printf("ID: %d | %s - %s [%s]\n", 
                   livres[i].id, 
                   livres[i].titre, 
                   livres[i].auteur, 
                   livres[i].categorie);
            compteur++; 
        }
    }
    if (compteur == 0) {
        printf("Aucun livre n'est emprunte actuellement.\n");
    }
}

// NOUVEAU : Sauvegarde l'état des livres (pour garder les 0 et les 1)
void sauvegarderLivres(Livre livres[], int n) {
    FILE *f = fopen("txt/livres.txt", "w"); 
    if (f == NULL) {
        printf("[ERREUR] Impossible de sauvegarder dans le fichier.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d %s %s %s %d\n", 
                livres[i].id, 
                livres[i].titre, 
                livres[i].auteur, 
                livres[i].categorie, 
                livres[i].disponible);
    }
    fclose(f);
}