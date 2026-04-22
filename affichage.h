#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "user.h"
#include "livre.h"
#include "emprunt.h"

// Affiche l'accueil (Connexion/Inscription)
void afficherEnteteAccueil();

// Gère TOUTE l'interface une fois que l'utilisateur est connecté
void gererInterfaceUtilisateur(User current, Livre livres[], Emprunt emprunts[]);

#endif