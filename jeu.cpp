#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "const.h"
#include "jeu.h"
#include "utils.h"
#include "fichier.h"


int jouer(sf::RenderWindow* Window)
{
	sf::Sprite vide, mur, caisse, objectif, mario, caisse_ok;
	sf::Sprite *allSprite[6] = { &vide, &mur, &caisse, &objectif, &mario, &caisse_ok };
	sf::Vector2i positionJoueur;

	int  objectifsRestants = 0, continuer = 1, direction = BAS, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des sprites (decors, personnage...)
	sf::Texture textureVide, textureMur, textureCaisse, textureCaisseOk, textureObjectif, textureMario[5];

	textureVide.loadFromFile("vide.png");
	vide.setTexture(textureVide);

	textureMur.loadFromFile("mur.jpg");
	mur.setTexture(textureMur);

	textureCaisse.loadFromFile("caisse.jpg");
	caisse.setTexture(textureCaisse);

	textureCaisseOk.loadFromFile("caisse_ok.jpg");
	caisse_ok.setTexture(textureCaisseOk);

	textureObjectif.loadFromFile("objectif.png");
	objectif.setTexture(textureObjectif);

	textureMario[HAUT].loadFromFile("mario_haut.GIF");

	textureMario[BAS].loadFromFile("mario_bas.GIF");

	textureMario[GAUCHE].loadFromFile("mario_gauche.GIF");

	textureMario[DROITE].loadFromFile("mario_droite.GIF");
	
	chargerNiveau(carte);
		

	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			if (carte[i][j] == MARIO)
			{
				positionJoueur.x = i;
				positionJoueur.y = j;
				
			}
		}
	}

	while (continuer == 1) {
		// On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (Window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				Window->close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					continuer = 0;
					return -1;
				}

				if (event.key.code == sf::Keyboard::Backspace) {
					return jouer(Window);
				}

				if (event.key.code == sf::Keyboard::Z) {
					deplacerJoueur(carte, &positionJoueur, HAUT);
					direction = HAUT;
				}

				if (event.key.code == sf::Keyboard::S) {
					deplacerJoueur(carte, &positionJoueur, BAS);
					direction = BAS;
				}

				if (event.key.code == sf::Keyboard::Q) {
					deplacerJoueur(carte, &positionJoueur, GAUCHE);
					direction = GAUCHE;
				}

				if (event.key.code == sf::Keyboard::D) {
					deplacerJoueur(carte, &positionJoueur, DROITE);
					direction = DROITE;
				}

				carte[positionJoueur.x][positionJoueur.y] = MARIO;
			}

			// Affichage du niveau 
			sf::FloatRect Position;
			for (int ligne = 0; ligne < NB_BLOCS_LARGEUR; ligne++) {
				for (int colonne = 0; colonne < NB_BLOCS_HAUTEUR; colonne++) {
					Position.top = colonne * TAILLE_BLOC;
					Position.left = ligne * TAILLE_BLOC;
					sf::Sprite* sprite = allSprite[carte[ligne][colonne]];
					sprite->setPosition(Position.left, Position.top);
					Window->draw(*sprite);
				}
			}
			mario.setTexture(textureMario[direction]);

			Window->display();
		}
		Window->clear(sf::Color::Black);
	}
	return 0;
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i * pos, int direction)
{

	switch (direction)
	{
	case HAUT:
		if (pos->y - 1 < 0)
			break;
		if (carte[pos->x][pos->y - 1] == MUR|| carte[pos->x][pos->y - 1] == OBJECTIF|| carte[pos->x][pos->y - 1] == CAISSE_OK)
			break;
		if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
			(pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
				carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
			break;
		deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);

		pos->y--;
		carte[pos->x][pos->y + 1]=VIDE;
		break;

	case BAS:
		if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
			break;
		if (carte[pos->x][pos->y + 1] == MUR|| carte[pos->x][pos->y + 1] == OBJECTIF|| carte[pos->x][pos->y + 1] == CAISSE_OK)
			break;

		if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) &&
			(pos->y + 2 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos->y + 2] == MUR ||
				carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK))
			break;


		deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);

		pos->y++;
		carte[pos->x][pos->y - 1] = VIDE;
		break;


	case GAUCHE:
		if (pos->x - 1 < 0)
			break;
		if (carte[pos->x - 1][pos->y] == MUR|| carte[pos->x - 1][pos->y] == OBJECTIF|| carte[pos->x - 1][pos->y] == CAISSE_OK)
			break;

		if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) &&
			(pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR ||
				carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK))
			break;


		deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);

		pos->x--;
		carte[pos->x +1][pos->y] = VIDE;
		break;


	case DROITE:
		if (pos->x + 1 >= NB_BLOCS_LARGEUR)
			break;
		if (carte[pos->x + 1][pos->y] == MUR || carte[pos->x + 1][pos->y] == OBJECTIF|| carte[pos->x + 1][pos->y] == CAISSE_OK)
			break;

		if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) &&
			(pos->x + 2 >= NB_BLOCS_LARGEUR || carte[pos->x + 2][pos->y] == MUR ||
				carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK))
			break;

		deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);

		pos->x++;
		carte[pos->x - 1][pos->y] = VIDE;
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