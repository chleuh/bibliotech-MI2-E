#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "user.h"
#include "livre.h"
#include "emprunt.h"
#include "affichage.h"

// Vide le tampon d'entrée pour éviter les boucles infinies avec scanf
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
                printf("[ERREUR] : Entrez un chiffre valide.\n");
                viderBuffer(); 
                continue; 
            }
            viderBuffer();

            // --- OPTION 1 : CONNEXION ---
            if (choix == 1) {
                current = connexion(users, nbUsers);
                if (strlen(current.login) > 0) { 
                    connecte = 1; 
                    break; // Sort du do-while pour aller vers l'interface utilisateur
                } else {
                    printf("\n[ERREUR] Login ou mot de passe incorrect.\n");
                }
            } 
            // --- OPTION 2 : CRÉATION DE COMPTE ---
            else if (choix == 2) {
                char nouveauLogin[50];
                int loginExiste = 0;

                printf("Login: "); 
                scanf("%s", nouveauLogin);

                // Vérification si le login est déjà pris
                for (int i = 0; i < nbUsers; i++) {
                    if (strcmp(users[i].login, nouveauLogin) == 0) {
                        loginExiste = 1;
                        break;
                    }
                }

                if (loginExiste) {
                    printf("\n[ERREUR] Ce login existe deja ! Choisis-en un autre.\n");
                } else {
                    strcpy(current.login, nouveauLogin);
                    printf("Mot de passe: "); 
                    scanf("%s", current.password);
                    
                    int v = 0;
                    while(!v) {
                        printf("Role (etudiant/prof): "); 
                        scanf("%s", current.role);

                        if (strcmp(current.role, "etudiant") == 0) {
                            v = 1;
                        } 
                        else if (strcmp(current.role, "prof") == 0) {
                            v = 1;
                        } 
                        else {
                            printf("[ERREUR] Tapez exactement 'etudiant' ou 'prof'.\n");
                        }
                    }
                    sauvegarderUser(current);
                    printf("[OK] Compte cree ! Connectez-vous.\n");
                }
            }
            // --- OPTION 3 : QUITTER ---
            else if (choix == 3) {
                printf("\nFermeture de l'application. Au revoir !\n");
                return 0; 
            }
        } while (choix != 3);

        // Si la connexion a réussi, on lance l'interface de la bibliothèque
        if (connecte) {
            gererInterfaceUtilisateur(current, livres, emprunts);
        }
    }
    return 0;
}