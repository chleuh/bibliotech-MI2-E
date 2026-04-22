#ifndef EMPRUNT_H
#define EMPRUNT_H

typedef struct {
    int idLivre;
    char login[50];
    long dateEmprunt;
} Emprunt;

int chargerEmprunts(Emprunt emprunts[]);
void ajouterEmprunt(Emprunt e);

#endif