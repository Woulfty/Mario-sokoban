#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "const.h"
#include "jeu.h"
#include "utils.h"
#include "fichier.h"


void jouer(sf::RenderWindow* Window)
{
	sf::Sprite * mario[4];
	sf::Sprite * marioActuel;
	sf::Sprite *mur, *caisse, *caisseOK, *objectif;
	sf::Vector2i positionJoueur;

	int  objectifsRestants = 0, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des sprites (decors, personnage...)
	mur = loadSprite("mur.jpg");
	caisse = loadSprite("caisse.jpg");
	caisseOK = loadSprite("caisse_ok.jpg");
	objectif = loadSprite("objectif.png");
	mario[BAS] = loadSprite("mario_bas.gif");
	mario[GAUCHE] = loadSprite("mario_gauche.gif");
	mario[HAUT] = loadSprite("mario_haut.gif");
	mario[DROITE] = loadSprite("mario_droite.gif");

	marioActuel = mario[BAS];
	/*
	if (!chargerNiveau(carte))
		exit(EXIT_FAILURE);
		*/

	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			if (carte[i][j] == MARIO)
			{
				positionJoueur.x = i;
				positionJoueur.y = j;
				carte[i][j] = VIDE;
			}
		}
	}

	while (Window->isOpen())
	{
		Window->clear();
		sf::Event event;
		while (Window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Z)
				{
					// la touche "z" est enfoncée : on l'envoie en haut
					marioActuel = mario[HAUT];
					deplacerJoueur(carte, &positionJoueur, HAUT);

				}
				if (event.key.code == sf::Keyboard::D)
				{
					// la touche "d" est enfoncée : on l'envoie a droite
					marioActuel = mario[DROITE];
					deplacerJoueur(carte, &positionJoueur, DROITE);

				}
				if (event.key.code == sf::Keyboard::Q)
				{
					// la touche "q" est enfoncée : on l'envoie a gauche
					marioActuel = mario[GAUCHE];
					deplacerJoueur(carte, &positionJoueur, GAUCHE);

				}
				if (event.key.code == sf::Keyboard::S)
				{
					// la touche "s" est enfoncée : on l'envoie en bas
					marioActuel = mario[BAS];
					deplacerJoueur(carte, &positionJoueur, BAS);

				}


			}
		}


		objectifsRestants = 0;

		sf::Vector2i position;
		for (i = 0; i < NB_BLOCS_LARGEUR; i++)
		{
			for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
			{
				position.x = i * TAILLE_BLOC;
				position.y = j * TAILLE_BLOC;
				sf::Sprite * entity = nullptr;

				switch (carte[i][j])
				{
				case MUR:
					entity = mur;
					break;
				case CAISSE:
					entity = caisse;
					break;
				case CAISSE_OK:
					entity = caisseOK;
					break;
				case OBJECTIF:
					entity = objectif;
					objectifsRestants++;
					break;
				}

				if (entity != nullptr)
				{
					entity->setPosition(position.x, position.y);
					Window->draw(*entity);
				}
			}
		}

		if (!objectifsRestants)


			position.x = positionJoueur.x * TAILLE_BLOC;
		position.y = positionJoueur.y * TAILLE_BLOC;
		marioActuel->setPosition(position.x, position.y);
		Window->draw(*marioActuel);

		Window->display();



	}

}
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i * pos, int direction)
{

	switch (direction)
	{
	case HAUT:
		if (pos->y - 1 < 0)
			break;
		if (carte[pos->x][pos->y - 1] == MUR)
			break;
		if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
			(pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
				carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
			break;
		deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);

		pos->y--;
		break;

	case BAS:
		if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
			break;
		if (carte[pos->x][pos->y + 1] == MUR)
			break;

		if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) &&
			(pos->y + 2 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos->y + 2] == MUR ||
				carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK))
			break;


		deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);

		pos->y++;
		break;


	case GAUCHE:
		if (pos->x - 1 < 0)
			break;
		if (carte[pos->x - 1][pos->y] == MUR)
			break;

		if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) &&
			(pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR ||
				carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK))
			break;


		deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);

		pos->x--;
		break;


	case DROITE:
		if (pos->x + 1 >= NB_BLOCS_LARGEUR)
			break;
		if (carte[pos->x + 1][pos->y] == MUR)
			break;

		if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) &&
			(pos->x + 2 >= NB_BLOCS_LARGEUR || carte[pos->x + 2][pos->y] == MUR ||
				carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK))
			break;

		deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);

		pos->x++;
		break;
	}
}

void deplacerCaisse(int *premiereCase, int *secondeCase)
{
	if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK)
	{
		if (*secondeCase == OBJECTIF)
			*secondeCase = CAISSE_OK;
		else
			*secondeCase = CAISSE;

		if (*premiereCase == CAISSE_OK)
			*premiereCase = OBJECTIF;
		else
			*premiereCase = VIDE;
	}
}