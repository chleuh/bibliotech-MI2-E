#ifndef LIVRE_H
#define LIVRE_H

/* -----------------------------------------------
   livre.h  -  Déclarations pour les livres
   ----------------------------------------------- */

typedef struct {
    int id;
    char titre[50];
    char auteur[50];
    char categorie[50];
    int disponible; // 1 = disponible, 0 = déjà emprunté
} Livre;

// Charger les livres depuis le fichier texte
int chargerLivres(Livre livres[]);

// Afficher les livres disponibles
void afficherLivres(Livre livres[], int n);

// Afficher les livres déjà empruntés
void afficherLivresEmpruntes(Livre livres[], int n);

// Sauvegarder les livres dans le fichier texte
void sauvegarderLivres(Livre livres[], int n);

// Trier par TITRE alphabétique (existant)
void trierLivresAlpha(Livre livres[], int n);

// Trier par AUTEUR alphabétique (nouveau !)
void trierAuteursAlpha(Livre livres[], int n);

#endif