#include <stdio.h>
#include <string.h>
#include "livre.h"
#include "couleurs.h"

/* -----------------------------------------------
   livre.c  -  Gestion des livres
   ----------------------------------------------- */

// Charge les livres depuis le fichier texte
int chargerLivres(Livre livres[]) {
    FILE *f = fopen("txt/livres.txt", "r");
    if (f == NULL) return 0;

    int i = 0;
    while (i < 100) {
        int score = fscanf(f, "%d %s %s %s %d",
                           &livres[i].id,
                           livres[i].titre,
                           livres[i].auteur,
                           livres[i].categorie,
                           &livres[i].disponible);
        if (score != 5) break;
        i++;
    }

    fclose(f);
    return i;
}

// Affiche les livres disponibles avec couleurs et emojis
void afficherLivres(Livre livres[], int n) {
    printf("\n" CYAN "📚  ══════════════════════════════════════════\n");
    printf("      Liste des Livres Disponibles\n");
    printf("══════════════════════════════════════════\n" RESET);

    int compteur = 0;
    for (int i = 0; i < n; i++) {
        if (livres[i].disponible == 1) {
            printf(VERT "  ✅ ID: %d" RESET " | %s - %s [%s]\n",
                   livres[i].id, livres[i].titre,
                   livres[i].auteur, livres[i].categorie);
            compteur++;
        }
    }

    if (compteur == 0) {
        printf(JAUNE "  😔 Aucun livre disponible en rayon.\n" RESET);
    }
    printf(CYAN "══════════════════════════════════════════\n" RESET);
}

// Affiche les livres empruntés avec message clair
void afficherLivresEmpruntes(Livre livres[], int n) {
    printf("\n" ROUGE "📕  ══════════════════════════════════════════\n");
    printf("      Liste des Livres Empruntés\n");
    printf("══════════════════════════════════════════\n" RESET);

    int compteur = 0;
    for (int i = 0; i < n; i++) {
        if (livres[i].disponible == 0) {
            printf(ROUGE "  ❌ ID: %d" RESET " | %s - %s [%s]"
                   JAUNE "  ⚠️  DÉJÀ EMPRUNTÉ\n" RESET,
                   livres[i].id, livres[i].titre,
                   livres[i].auteur, livres[i].categorie);
            compteur++;
        }
    }

    if (compteur == 0) {
        printf(VERT "  🎉 Aucun livre n'est emprunté actuellement.\n" RESET);
    }
    printf(ROUGE "══════════════════════════════════════════\n" RESET);
}

// Sauvegarde l'état de tous les livres dans le fichier texte
void sauvegarderLivres(Livre livres[], int n) {
    FILE *f = fopen("txt/livres.txt", "w");
    if (f == NULL) {
        printf(ROUGE "  [ERREUR] Impossible de sauvegarder les livres.\n" RESET);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d %s %s %s %d\n",
                livres[i].id, livres[i].titre,
                livres[i].auteur, livres[i].categorie,
                livres[i].disponible);
    }
    fclose(f);
}

// Tri à bulles par TITRE (A → Z)
void trierLivresAlpha(Livre livres[], int n) {
    Livre temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(livres[j].titre, livres[j+1].titre) > 0) {
                temp        = livres[j];
                livres[j]   = livres[j+1];
                livres[j+1] = temp;
            }
        }
    }
}

// Tri à bulles par AUTEUR (A → Z)
void trierAuteursAlpha(Livre livres[], int n) {
    Livre temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(livres[j].auteur, livres[j+1].auteur) > 0) {
                temp        = livres[j];
                livres[j]   = livres[j+1];
                livres[j+1] = temp;
            }
        }
    }
    // pas de printf ici, sinon ca s'affiche en boucle
}