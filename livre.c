#include <stdio.h>
#include <string.h>
#include "livre.h"

// Charge les livres depuis le fichier
int chargerLivres(Livre livres[]) {
    FILE *f = fopen("txt/livres.txt", "r");
    if (f == NULL) return 0;

    int i = 0;
    // On boucle tant qu'on a de la place dans le tableau (limite 100)
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

// Affiche uniquement les livres EMPRUNTÉS (disponible == 0)
void afficherLivresEmpruntes(Livre livres[], int n) {
    printf("\n--- Liste des Livres Empruntes ---\n");
    int compteur = 0;

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

// Sauvegarde l'état des livres (écrase le fichier avec les nouvelles disponibilités)
void sauvegarderLivres(Livre livres[], int n) {
    FILE *f = fopen("txt/livres.txt", "w");
    if (f == NULL) {
        printf("[ERREUR] Impossible de sauvegarder les livres.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d %s %s %s %d\n", livres[i].id, livres[i].titre, 
                livres[i].auteur, livres[i].categorie, livres[i].disponible);
    }
    fclose(f);
}

// TRI à bulles alphabétique sur le titre
void trierLivresAlpha(Livre livres[], int n) {
    Livre temp; 
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Utilise strcmp de <string.h> pour comparer les titres
            if (strcmp(livres[j].titre, livres[j+1].titre) > 0) {
                temp = livres[j];
                livres[j] = livres[j+1];
                livres[j+1] = temp;
            }
        }
    }
}