#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "affichage.h"
#include "livre.h"   
#include "emprunt.h" 

// --- NOUVELLE FONCTION DE VÉRIFICATION ---
// Retourne 1 si la chaîne contient un chiffre, 0 sinon
int contientChiffre(char chaine[]) {
    for (int i = 0; chaine[i] != '\0'; i++) {
        if (chaine[i] >= '0' && chaine[i] <= '9') {
            return 1;
        }
    }
    return 0;
}

// Affiche l'entête du menu principal
void afficherEnteteAccueil() {
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║               BIBLIOTHEQUE - ACCUEIL       ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("1. Se connecter\n2. Creer un compte\n3. Quitter\nChoix : ");
}

// Gère toute l'interface après connexion
void gererInterfaceUtilisateur(User current, Livre livres[], Emprunt emprunts[]) {
    int action;
    int nbLivres, nbEmprunts;

    while (1) {
        nbLivres = chargerLivres(livres);
        nbEmprunts = chargerEmprunts(emprunts);

        long delai = (strcmp(current.role, "prof") == 0) ? 180 : 120;
        int countPerso = 0, aRetard = 0;

        // --- SECTION : AFFICHAGE DES EMPRUNTS ---
        printf("\n  >>> MES EMPRUNTS ACTUELS <<<\n");
        printf("  --------------------------------------------------\n");
        for (int i = 0; i < nbEmprunts; i++) {
            if (strcmp(emprunts[i].login, current.login) == 0) {
                long tempsLimite = emprunts[i].dateEmprunt + delai;
                struct tm *t = localtime(&tempsLimite);

                printf("  Livre ID: %d | Rendre a: %d:%d:%d", 
                        emprunts[i].idLivre, t->tm_hour, t->tm_min, t->tm_sec);

                if (time(NULL) > tempsLimite) {
                    printf(" -> /!\\ RETARD /!\\");
                    aRetard = 1;
                }
                printf("\n");
                countPerso++;
            }
        }
        if (countPerso == 0) printf("  Aucun livre emprunte.\n");
        printf("  --------------------------------------------------\n");

        // --- SECTION : MENU D'ACTIONS ---
        printf("\n  Bonjour %s (%s)\n", current.login, current.role);
        printf("  [1] Emprunter\n  [2] Stock global\n");
        if (strcmp(current.role, "prof") == 0) printf("  [3] Ajouter livre\n");
        printf("  [4] Se deconnecter\n  Choix > ");

        if (scanf("%d", &action) != 1) { 
            while (getchar() != '\n'); 
            continue; 
        }
        while (getchar() != '\n'); 

        // --- LOGIQUE DES ACTIONS ---
        if (action == 1) {
            int max = (strcmp(current.role, "prof") == 0) ? 5 : 3;
            if (aRetard) printf("\n[BLOQUE] Rends tes livres en retard !\n");
            else if (countPerso >= max) printf("\n[BLOQUE] Quota atteint.\n");
            else {
                printf("\n1. Titre\n2. Categorie\nChoix : ");
                int mode; scanf("%d", &mode); while (getchar() != '\n');
                if (mode == 1) { 
                    trierLivresAlpha(livres, nbLivres); 
                    afficherLivres(livres, nbLivres); 
                }
                else {
                    char cat[50]; printf("Cat : "); scanf("%s", cat);
                    for(int i=0; i<nbLivres; i++)
                        if(strcmp(livres[i].categorie, cat) == 0 && livres[i].disponible == 1)
                            printf("[%d] %s\n", livres[i].id, livres[i].titre);
                }

                int id; printf("\nID a emprunter : ");
                if (scanf("%d", &id) == 1) {
                    int trouve = 0;
                    for (int i = 0; i < nbLivres; i++) {
                        if (livres[i].id == id && livres[i].disponible == 1) {
                            Emprunt e = {id, "", (long)time(NULL)};
                            strcpy(e.login, current.login);
                            ajouterEmprunt(e);
                            livres[i].disponible = 0;
                            sauvegarderLivres(livres, nbLivres);
                            printf("[SUCCES] Emprunt effectue.\n"); 
                            trouve = 1; 
                            break;
                        }
                    }
                    if (!trouve) printf("[ERREUR] ID introuvable ou indisponible.\n");
                }
            }
        } 
        else if (action == 2) {
            afficherLivres(livres, nbLivres);
        }
        else if (action == 3 && strcmp(current.role, "prof") == 0) {
            Livre n; 
            n.id = nbLivres + 1;
            printf("Titre: "); fgets(n.titre, 50, stdin); n.titre[strcspn(n.titre, "\n")] = 0;

            // --- BOUCLE DE VÉRIFICATION POUR L'AUTEUR ---
            do {
                printf("Auteur (sans chiffres) : "); 
                fgets(n.auteur, 50, stdin); 
                n.auteur[strcspn(n.auteur, "\n")] = 0;

                if (contientChiffre(n.auteur)) {
                    printf("[ERREUR] Le nom de l'auteur ne doit pas contenir de chiffres.\n");
                }
            } while (contientChiffre(n.auteur));

            printf("Cat: "); fgets(n.categorie, 50, stdin); n.categorie[strcspn(n.categorie, "\n")] = 0;
            n.disponible = 1; 
            livres[nbLivres] = n;
            sauvegarderLivres(livres, nbLivres + 1);
            printf("[OK] Livre ajoute au stock.\n");
        }
        else if (action == 4) {
            printf("Deconnexion...\n");
            break; 
        }
    }
}