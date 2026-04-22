#ifndef USER_H
#define USER_H

#define MAX 100

typedef struct {
    char login[50];
    char password[50];
    char role[20]; // "etudiant" ou "prof"
} User;

int chargerUsers(User users[]);
void sauvegarderUser(User u);
User connexion(User users[], int n);

#endif