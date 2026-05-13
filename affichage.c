#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "affichage.h"
#include "livre.h"
#include "emprunt.h"
#include "rendre.h"
#include "couleurs.h"

/* -----------------------------------------------
   affichage.c  -  Menus et interface utilisateur
   ----------------------------------------------- */

// Retourne 1 si la chaîne contient un chiffre, 0 sinon
int contientChiffre(char chaine[]) {
    for (int i = 0; chaine[i] != '\0'; i++) {
        if (chaine[i] >= '0' && chaine[i] <= '9') {
            return 1;
        }
    }
    return 0;
}

// Affiche le menu d'accueil
void afficherEnteteAccueil() {
    printf("\n" CYAN "╔════════════════════════════════════════════╗\n");
    printf("║  📖   BIENVENUE À LA BIBLIOTHÈQUE  📖      ║\n");
    printf("╚════════════════════════════════════════════╝\n" RESET);
    printf(BLANC "  1. 🔑  Se connecter\n");
    printf("  2. 📝  Créer un compte\n");
    printf("  3. 🚪  Quitter\n" RESET);
    printf(JAUNE "  Choix : " RESET);
}

// Gère toute l'interface après connexion
void gererInterfaceUtilisateur(User current, Livre livres[], Emprunt emprunts[]) {
    int action;
    int nbLivres, nbEmprunts;

    while (1) {
        nbLivres   = chargerLivres(livres);
        trierAuteursAlpha(livres, nbLivres);   // ← tri automatique à chaque tour
        nbEmprunts = chargerEmprunts(emprunts);

        // Délai de rendu selon le rôle
        long delai;
        if (strcmp(current.role, "prof") == 0) {
            delai = 180;
        } else {
            delai = 120;
        }

        int countPerso = 0;
        int aRetard    = 0;

        // ── AFFICHAGE DES EMPRUNTS ────────────────────────────────────────
        printf("\n" JAUNE "╔════════════════════════════════════════════╗\n");
        printf("║        📚  MES EMPRUNTS ACTUELS  📚        ║\n");
        printf("╚════════════════════════════════════════════╝\n" RESET);

        for (int i = 0; i < nbEmprunts; i++) {
            if (strcmp(emprunts[i].login, current.login) == 0) {
                long tempsLimite = emprunts[i].dateEmprunt + delai;
                struct tm *t = localtime(&tempsLimite);

                printf(CYAN "  📗 Livre ID: %d" RESET " | À rendre avant: %02d:%02d:%02d",
                       emprunts[i].idLivre, t->tm_hour, t->tm_min, t->tm_sec);

                if (time(NULL) > tempsLimite) {
                    printf(ROUGE "  ⏰ RETARD !" RESET);
                    aRetard = 1;
                }
                printf("\n");
                countPerso++;
            }
        }

        if (countPerso == 0) {
            printf(VERT "  ✅ Aucun livre emprunté pour l'instant.\n" RESET);
        }
        printf(JAUNE "════════════════════════════════════════════\n" RESET);

        // ── MENU PRINCIPAL ────────────────────────────────────────────────
        printf("\n" BLANC "  👋 Bonjour " VERT "%s" RESET BLANC " (%s)\n" RESET,
               current.login, current.role);
        printf(BLANC "  [1] 📥  Emprunter un livre\n");
        printf("  [2] 📚  Voir tout le stock\n");
        printf("  [3] 📤  Rendre un livre\n");
        if (strcmp(current.role, "prof") == 0) {
            printf("  [4] ➕  Ajouter un livre\n");
        }
        printf("  [5] 🚪  Se déconnecter\n" RESET);
        printf(JAUNE "  Choix > " RESET);

        if (scanf("%d", &action) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        // ── ACTION 1 : EMPRUNTER ──────────────────────────────────────────
        if (action == 1) {
            int max;
            if (strcmp(current.role, "prof") == 0) {
                max = 5;
            } else {
                max = 3;
            }

            if (aRetard) {
                printf(ROUGE "\n  🚫 Tu as des livres en RETARD ! Rends-les d'abord.\n" RESET);
            } else if (countPerso >= max) {
                printf(ROUGE "\n  🚫 Quota atteint (%d/%d). Rends un livre avant d'en emprunter.\n" RESET, countPerso, max);
            } else {
                // les livres sont déjà triés par auteur, on affiche directement
                afficherLivres(livres, nbLivres);

                // Saisie de l'ID
                printf(JAUNE "\n  ID du livre à emprunter : " RESET);
                int id;
                if (scanf("%d", &id) == 1) {
                    int trouve = 0;
                    for (int i = 0; i < nbLivres; i++) {
                        if (livres[i].id == id) {
                            if (livres[i].disponible == 0) {
                                printf(ROUGE "\n  ❌ Désolé ! \"%s\" est DÉJÀ EMPRUNTÉ par quelqu'un d'autre.\n" RESET,
                                       livres[i].titre);
                                printf(JAUNE "  💡 Essaie un autre livre ou reviens plus tard !\n" RESET);
                            } else {
                                Emprunt e;
                                e.idLivre     = id;
                                e.dateEmprunt = (long)time(NULL);
                                strcpy(e.login, current.login);

                                ajouterEmprunt(e);
                                livres[i].disponible = 0;
                                sauvegarderLivres(livres, nbLivres);

                                printf(VERT "\n  ✅ \"%s\" emprunté ! Bonne lecture 📖\n" RESET,
                                       livres[i].titre);
                            }
                            trouve = 1;
                            break;
                        }
                    }
                    if (!trouve) {
                        printf(ROUGE "\n  ❌ Aucun livre avec cet ID.\n" RESET);
                    }
                }
                while (getchar() != '\n');
            }
        }

        // ── ACTION 2 : STOCK GLOBAL ───────────────────────────────────────
        else if (action == 2) {
            afficherLivres(livres, nbLivres);
        }

        // ── ACTION 3 : RENDRE UN LIVRE ────────────────────────────────────
        else if (action == 3) {
            if (countPerso == 0) {
                printf(JAUNE "\n  😄 Tu n'as aucun livre à rendre !\n" RESET);
            } else {
                printf(JAUNE "\n  ID du livre à rendre : " RESET);
                int idRendre;
                if (scanf("%d", &idRendre) == 1) {
                    rendreLivre(idRendre, current.login, livres, nbLivres, emprunts, nbEmprunts);
                }
                while (getchar() != '\n');
            }
        }

        // ── ACTION 4 : AJOUTER UN LIVRE (prof seulement) ─────────────────
        else if (action == 4 && strcmp(current.role, "prof") == 0) {
            Livre n;
            n.id = nbLivres + 1;

            printf(CYAN "\n  ── Ajout d'un nouveau livre ──\n" RESET);

            printf("  Titre : ");
            fgets(n.titre, 50, stdin);
            n.titre[strcspn(n.titre, "\n")] = 0;

            do {
                printf("  Auteur (sans chiffres) : ");
                fgets(n.auteur, 50, stdin);
                n.auteur[strcspn(n.auteur, "\n")] = 0;

                if (contientChiffre(n.auteur)) {
                    printf(ROUGE "  ❌ Le nom de l'auteur ne doit pas contenir de chiffres !\n" RESET);
                }
            } while (contientChiffre(n.auteur));

            printf("  Catégorie : ");
            fgets(n.categorie, 50, stdin);
            n.categorie[strcspn(n.categorie, "\n")] = 0;

            n.disponible     = 1;
            livres[nbLivres] = n;
            sauvegarderLivres(livres, nbLivres + 1);

            printf(VERT "\n  ✅ Livre \"%s\" ajouté au stock !\n" RESET, n.titre);
        }

        // ── ACTION 5 : DÉCONNEXION ────────────────────────────────────────
        else if (action == 5) {
            printf(CYAN "\n  👋 À bientôt %s !\n\n" RESET, current.login);
            break;
        }
    }
}