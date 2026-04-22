#ifndef LIVRE_H
#define LIVRE_H

typedef struct {
    int id;
    char titre[100];
    char auteur[100];
    char categorie[50];
    int disponible; // 1 = dispo, 0 = emprunté
} Livre;

int chargerLivres(Livre livres[]);
void afficherLivres(Livre livres[], int n);

#endif