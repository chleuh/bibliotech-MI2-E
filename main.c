#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "user.h"
#include "livre.h"
#include "emprunt.h"

// Fonction pour vider le buffer
void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//  TRI a bulles pour trier les livres    
void trierLivresAlpha(Livre livres[], int n) {
    Livre temp; 
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Si le titre J est plus grand que le suivant, on inverse
            if (strcmp(livres[j].titre, livres[j+1].titre) > 0) {
                temp = livres[j];
                livres[j] = livres[j+1];
                livres[j+1] = temp;
            }
        }
    }
}

int main() {
    User users[MAX];
    Livre livres[100];
    Emprunt emprunts[100];
    User current;
    int nbUsers, nbLivres, nbEmprunts, choix;
    int action;
    int connecte;

    // --- GRANDE BOUCLE PRINCIPALE (RETOUR ACCUEIL) ---
    while (1) {
        connecte = 0; 

        // --- PHASE 1 : CONNEXION / INSCRIPTION ---
        do {
            nbUsers = chargerUsers(users);
            printf("\n╔════════════════════════════════════════════╗\n");
            printf("║              BIBLIOTHEQUE - ACCUEIL         ║\n");
            printf("╚════════════════════════════════════════════╝\n");
            printf("1. Se connecter\n2. Creer un compte\n3. Quitter le programme\nChoix : ");

            if (scanf("%d", &choix) != 1) { 
                printf("[ERREUR] : Entrez un chiffre.\n");
                viderBuffer(); 
                continue; 
            }
            viderBuffer();

            if (choix == 1) {
                current = connexion(users, nbUsers);
                if (strlen(current.login) > 0) { 
                    connecte = 1; 
                    break; 
                } else {
                    printf("\n[ERREUR] Login ou mot de passe incorrect.\n");
                }
            } 
            else if (choix == 2) {
                printf("Login: "); scanf("%s", current.login);
                printf("Mot de passe: "); scanf("%s", current.password);
                int v = 0;
                while(!v) {
                    printf("Role (etudiant/prof): "); scanf("%s", current.role);
                    if(strcmp(current.role,"etudiant")==0 || strcmp(current.role,"prof")==0) v=1;
                    else printf("[ERREUR] Tapez 'etudiant' ou 'prof'.\n");
                }
                sauvegarderUser(current);
                printf("[OK] Compte cree ! Connectez-vous.\n");
            }
            else if (choix == 3) {
                printf("\nFermeture de l'application. Au revoir !\n");
                return 0; 
            }
        } while (choix != 3);

        // --- PHASE 2 : INTERFACE UTILISATEUR CONNECTÉ ---
        if (connecte) {
            while (1) {
                nbLivres = chargerLivres(livres);
                nbEmprunts = chargerEmprunts(emprunts);
                long delai = (strcmp(current.role, "prof") == 0) ? 180 : 120;

                printf("\n  Bonjour %s (%s)\n", current.login, current.role);

                printf("\n  >>> MES EMPRUNTS ACTUELS <<<\n");
                printf("  --------------------------------------------------\n");

                int countPerso = 0;
                int aRetard = 0;

                for (int i = 0; i < nbEmprunts; i++) {
                    // Si le nom sur l'emprunt est le mien
                    if (strcmp(emprunts[i].login, current.login) == 0) {

                        // 1. On calcule quand il doit être rendu
                        long tempsLimite = emprunts[i].dateEmprunt + delai;

                        // 2. On transforme ce chiffre en Heure:Minute:Seconde
                        struct tm *t = localtime(&tempsLimite);

                        // 3. On affiche la ligne du livre
                        printf("  Livre ID: %d | Rendre a: %d:%d:%d", 
                                emprunts[i].idLivre, t->tm_hour, t->tm_min, t->tm_sec);

                        // 4. Est-ce que l'heure actuelle a dépassé la limite ?
                        if (time(NULL) > tempsLimite) {
                            printf(" -> RETARD !");
                            aRetard = 1;
                        }

                        printf("\n"); // On passe à la ligne pour le livre suivant
                        countPerso = countPerso + 1;
                    }
                }

                // Si après avoir tout fouillé on n'a rien trouvé
                if (countPerso == 0) {
                    printf("  Vous n'avez aucun livre.\n");
                }
                printf("  --------------------------------------------------\n");

                printf("\n  [1] Emprunter un livre\n");
                printf("  [2] Voir le stock global\n");
                if (strcmp(current.role, "prof") == 0) printf("  [3] Ajouter un nouveau livre\n");
                printf("  [4] Se deconnecter\n");
                printf("\n  Choix > ");

                if (scanf("%d", &action) != 1) { viderBuffer(); continue; }
                viderBuffer();

                if (action == 1) {
                    int max = (strcmp(current.role, "prof") == 0) ? 5 : 3;
                    if (aRetard) {
                        printf("\n  [BLOQUE] : Tu as des retards ! Rends tes livres d'abord.\n");
                    } else if (countPerso >= max) {
                        printf("\n  [BLOQUE] : Quota de %d livres atteint.\n", max);
                    } else {
                        printf("\n--- RECHERCHE ---\n1. Par titre \n2. Par categorie\nChoix : ");
                        int mode; scanf("%d", &mode); viderBuffer();

                        if (mode == 1) {
                            trierLivresAlpha(livres, nbLivres); // Appel de ta fonction de tri
                            afficherLivres(livres, nbLivres);
                        } else {
                            char cat[50]; printf("Categorie : "); scanf("%s", cat);
                            printf("\nResultats pour %s :\n", cat);
                            for(int i=0; i<nbLivres; i++) {
                                if(strcmp(livres[i].categorie, cat) == 0 && livres[i].disponible == 1)
                                    printf("[%d] %s - %s\n", livres[i].id, livres[i].titre, livres[i].auteur);
                            }
                        }

                        int id; printf("\nID du livre a emprunter : ");
                        if (scanf("%d", &id) == 1) {
                            int trouve = 0;
                            for (int i = 0; i < nbLivres; i++) {
                                if (livres[i].id == id && livres[i].disponible == 1) {
                                    Emprunt e = {id, "", time(NULL)};
                                    strcpy(e.login, current.login);
                                    ajouterEmprunt(e);
                                    livres[i].disponible = 0;
                                    sauvegarderLivres(livres, nbLivres);
                                    printf("  [SUCCES] : Emprunt valide !\n");
                                    trouve = 1; break;
                                }
                            }
                            if(!trouve) printf("  [ERREUR] : ID invalide ou deja pris.\n");
                        }
                        viderBuffer();
                    }
                } 
                else if (action == 2) {
                    afficherLivres(livres, nbLivres);
                }
                else if (action == 3 && strcmp(current.role, "prof") == 0) {
                    Livre n; 
                    n.id = nbLivres + 1;

                    // Utilisation de fgets pour séparer titre, auteur et catégorie sans bug
                    printf("Titre: ");
                    fgets(n.titre, 50, stdin);
                    n.titre[strcspn(n.titre, "\n")] = 0;

                    printf("Auteur: ");
                    fgets(n.auteur, 50, stdin);
                    n.auteur[strcspn(n.auteur, "\n")] = 0;

                    printf("Categorie: ");
                    fgets(n.categorie, 50, stdin);
                    n.categorie[strcspn(n.categorie, "\n")] = 0;

                    n.disponible = 1;
                    livres[nbLivres] = n;
                    sauvegarderLivres(livres, nbLivres + 1);
                    printf("  [OK] : Livre ajoute au stock !\n");
                }
                else if (action == 4) {
                    printf("\n>>> Deconnexion reussie. Retour a l'accueil...\n");
                    break; 
                }
            }
        }
    }
    return 0;
}