#include <stdio.h>
#include <string.h>
#include "user.h"

// Charge les utilisateurs du fichier vers le tableau
int chargerUsers(User users[]) {
    FILE *f = fopen("txt/users.txt", "r");
    if (f == NULL) {
        return 0; 
    }

    int i = 0;
    while (i < MAX) {
        int lus = fscanf(f, "%s %s %s", users[i].login, users[i].password, users[i].role);
        if (lus != 3) {
            break; 
        }
        i++; 
    }
    fclose(f);
    return i; 
}

// Ajoute un nouvel utilisateur à la fin du fichier texte
void sauvegarderUser(User u) {
    FILE *f = fopen("txt/users.txt", "a");

    if (f != NULL) {
        fprintf(f, "\n %s %s %s\n", u.login, u.password, u.role);
        fclose(f);
    }
}

// Demande les identifiants et vérifie s'ils existent dans le tableau
User connexion(User users[], int n) {
    char login[50], password[50];

    printf("Login : ");
    scanf("%s", login);
    printf("Mot de passe : ");
    scanf("%s", password);

    // On parcourt tout le tableau des utilisateurs chargés
    for (int i = 0; i < n; i++) {
        // Si le login correspond ET le mot de passe correspond
        if (strcmp(login, users[i].login) == 0 && strcmp(password, users[i].password) == 0) {
            return users[i]; 
        }
    }

    // Si on arrive ici, la connexion a échoué
    User vide = {"", "", ""};
    return vide; 
}