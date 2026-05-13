#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "user.h"
#include "livre.h"
#include "emprunt.h"

/* -----------------------------------------------
   affichage.h  -  Déclarations de l'interface
   ----------------------------------------------- */

// Affiche le menu d'accueil (connexion / inscription)
void afficherEnteteAccueil();

// Gère toute l'interface une fois connecté
void gererInterfaceUtilisateur(User current, Livre livres[], Emprunt emprunts[]);

#endif