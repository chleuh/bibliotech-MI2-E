#ifndef LIVRE_H
#define LIVRE_H

// Structure représentant un livre dans la base de données
typedef struct {
    int id;
    char titre[50];
    char auteur[50];
    char categorie[50];
    int disponible; // 1 si disponible, 0 si emprunté
} Livre;

int chargerLivres(Livre livres[]);

void afficherLivres(Livre livres[], int n);

void afficherLivresEmpruntes(Livre livres[], int n);

void sauvegarderLivres(Livre livres[], int n);

void trierLivresAlpha(Livre livres[], int n);

#endif