#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "livre.h"
#include "emprunt.h"
#include "affichage.h"
#include "couleurs.h"  // les couleurs viennent d'ici

/* -----------------------------------------------
   main.c  -  Point d'entrée du programme
   ----------------------------------------------- */

// Vide le tampon pour éviter les boucles infinies avec scanf
void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    User users[MAX];
    Livre livres[100];
    Emprunt emprunts[100];
    User current;
    int nbUsers, choix, connecte;

    while (1) {
        connecte = 0;

        do {
            nbUsers = chargerUsers(users);
            afficherEnteteAccueil();

            if (scanf("%d", &choix) != 1) {
                printf(ROUGE "  ❌ Entrez un chiffre valide.\n" RESET);
                viderBuffer();
                continue;
            }
            viderBuffer();

            // ── OPTION 1 : CONNEXION ──────────────────────────────────────
            if (choix == 1) {
                current = connexion(users, nbUsers);
                if (strlen(current.login) > 0) {
                    connecte = 1;
                    printf(VERT "\n  ✅ Connexion réussie ! Bienvenue %s 👋\n" RESET, current.login);
                    break;
                } else {
                    printf(ROUGE "\n  ❌ Login ou mot de passe incorrect. Réessaie !\n" RESET);
                }
            }

            // ── OPTION 2 : CRÉER UN COMPTE ────────────────────────────────
            else if (choix == 2) {
                char nouveauLogin[50];
                int loginExiste = 0;

                printf(JAUNE "  Login : " RESET);
                scanf("%s", nouveauLogin);

                for (int i = 0; i < nbUsers; i++) {
                    if (strcmp(users[i].login, nouveauLogin) == 0) {
                        loginExiste = 1;
                        break;
                    }
                }

                if (loginExiste) {
                    printf(ROUGE "\n  ❌ Ce login existe déjà ! Choisis-en un autre.\n" RESET);
                } else {
                    strcpy(current.login, nouveauLogin);
                    printf(JAUNE "  Mot de passe : " RESET);
                    scanf("%s", current.password);

                    int valide = 0;
                    while (!valide) {
                        printf(JAUNE "  Rôle (etudiant / prof) : " RESET);
                        scanf("%s", current.role);

                        if (strcmp(current.role, "etudiant") == 0) {
                            valide = 1;
                        } else if (strcmp(current.role, "prof") == 0) {
                            valide = 1;
                        } else {
                            printf(ROUGE "  ❌ Tape exactement 'etudiant' ou 'prof'.\n" RESET);
                        }
                    }

                    sauvegarderUser(current);
                    printf(VERT "\n  ✅ Compte créé ! Connecte-toi maintenant.\n" RESET);
                }
            }

            // ── OPTION 3 : QUITTER ────────────────────────────────────────
            else if (choix == 3) {
                printf(CYAN "\n  🚪 Au revoir ! 👋\n\n" RESET);
                return 0;
            }

        } while (choix != 3);

        if (connecte) {
            gererInterfaceUtilisateur(current, livres, emprunts);
        }
    }

    return 0;
}