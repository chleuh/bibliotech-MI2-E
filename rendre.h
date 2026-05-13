#ifndef RENDRE_H
#define RENDRE_H

#include "livre.h"
#include "emprunt.h"

/* -----------------------------------------------
   rendre.h  -  Fonctions pour rendre un livre
   ----------------------------------------------- */

// Rend un livre : supprime l'emprunt et remet disponible = 1
void rendreLivre(int idLivre, char login[], Livre livres[], int nbLivres, Emprunt emprunts[], int nbEmprunts);

#endif