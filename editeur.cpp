#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SFML/SFML.h>
#include <SFML/SFML_image.h>

#include "const.h"
#include "editeur.h"
#include "fichiers.h"

void editeur(sf::Transformable* ecran)
{
	sf::Transformable *mur = NULL, *caisse = NULL, *objectif = NULL, *mario = NULL;
	SFML_Rect position;
	SFML_Event event;

	int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
	int objetActuel = MUR, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des objets et du niveau
	mur = IMG_Load("mur.jpg");
	caisse = IMG_Load("caisse.jpg");
	objectif = IMG_Load("objectif.png");
	mario = IMG_Load("mario_bas.gif");

	if (!chargerNiveau(carte))
		exit(EXIT_FAILURE);

	// Boucle infinie de l'�diteur
	while (continuer)
	{
		SFML_WaitEvent(&event);
		switch (event.type)
		{
		case SFML_QUIT:
			continuer = 0;
			break;
		case SFML_MOUSEBUTTONDOWN:
			if (event.button.button == SFML_BUTTON_LEFT)
			{
				// On met l'objet actuellement choisi (mur, caisse...) � l'endroit du clic
				carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
				clicGaucheEnCours = 1; // On active un bool�en pour retenir qu'un bouton est enfonc�
			}
			else if (event.button.button == SFML_BUTTON_RIGHT) // Le clic droit sert � effacer
			{
				carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
				clicDroitEnCours = 1;
			}
			break;
		case SFML_MOUSEBUTTONUP: // On d�sactive le bool�en qui disait qu'un bouton �tait enfonc�
			if (event.button.button == SFML_BUTTON_LEFT)
				clicGaucheEnCours = 0;
			else if (event.button.button == SFML_BUTTON_RIGHT)
				clicDroitEnCours = 0;
			break;
		case SFML_MOUSEMOTION:
			if (clicGaucheEnCours) // Si on d�place la souris et que le bouton gauche de la souris est enfonc�
			{
				carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
			}
			else if (clicDroitEnCours) // Pareil pour le bouton droit de la souris
			{
				carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
			}
			break;
		case SFML_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SFMLK_ESCAPE:
				continuer = 0;
				break;
			case SFMLK_s:
				sauvegarderNiveau(carte);
				break;
			case SFMLK_c:
				chargerNiveau(carte);
				break;
			case SFMLK_KP1:
				objetActuel = MUR;
				break;
			case SFMLK_KP2:
				objetActuel = CAISSE;
				break;
			case SFMLK_KP3:
				objetActuel = OBJECTIF;
				break;
			case SFMLK_KP4:
				objetActuel = MARIO;
				break;
			}
			break;
		}

		// Effacement de l'�cran
		SFML_FillRect(ecran, NULL, SFML_MapRGB(ecran->format, 255, 255, 255));

		// Placement des objets � l'�cran
		for (i = 0; i < NB_BLOCS_LARGEUR; i++)
		{
			for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
			{
				position.x = i * TAILLE_BLOC;
				position.y = j * TAILLE_BLOC;

				switch (carte[i][j])
				{
				case MUR:
					SFML_BlitSurface(mur, NULL, ecran, &position);
					break;
				case CAISSE:
					SFML_BlitSurface(caisse, NULL, ecran, &position);
					break;
				case OBJECTIF:
					SFML_BlitSurface(objectif, NULL, ecran, &position);
					break;
				case MARIO:
					SFML_BlitSurface(mario, NULL, ecran, &position);
					break;
				}
			}
		}

		// Mise � jour de l'�cran
		SDL_Flip(ecran);
	}

	SDL_FreeSurface(mur);
	SFML_FreeSurface(caisse);
	SFML_FreeSurface(objectif);
	SFML_FreeSurface(mario);
}