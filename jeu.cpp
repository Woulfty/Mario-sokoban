#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <SFML/SFML.h>
#include <SFML/SFML_image.h>

#include "constantes.h"
#include "jeu.h"

void jouer(sf::fenetre*ecran)
{
	entity.setOrigin( *mario[4] = {NULL}); // 4 surfaces pour chacune des directions de mario
    entity.setOrigin( *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL);
    entity.setPosition(positionJoueur);
    entity.move(event);

    int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    // Chargement des sprites (decors, personnage...)
    mur = IMG_Load("mur.jpg");
    caisse = IMG_Load("caisse.jpg");
    caisseOK = IMG_Load("caisse_ok.jpg");
    objectif = IMG_Load("objectif.png");
    mario[BAS] = IMG_Load("mario_bas.gif");
    mario[GAUCHE] = IMG_Load("mario_gauche.gif");
    mario[HAUT] = IMG_Load("mario_haut.gif");
    mario[DROITE] = IMG_Load("mario_droite.gif");

	marioActuel = mario[BAS];

	if (!chargerNiveau(carte))
        exit(EXIT_FAILURE);

	for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            if (carte[i][j] == MARIO)
            {
                positionJoueur.x = i;
                positionJoueur.y = j;
                carte[i][j] = VIDE;
            }
        }
    }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::z))
		{
			// la touche "z" est enfoncée : on l'envoie en haut
            marioActuel = mario[HAUT];
			deplacerJoueur(carte, &positionJoueur, HAUT);
			break;
        }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::d))
		{
			// la touche "d" est enfoncée : on l'envoie a droite
			marioActuel = mario[DROITE];
			deplacerJoueur(carte, &positionJoueur, DROITE);
			break;
        }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::q))
		{
			// la touche "q" est enfoncée : on l'envoie a gauche
			marioActuel = mario[GAUCHE];
			deplacerJoueur(carte, &positionJoueur, GAUCHE);
			break;
        }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::s))
		{
			// la touche "s" est enfoncée : on l'envoie en bas
			marioActuel = mario[BAS];
			deplacerJoueur(carte, &positionJoueur, BAS);
			break;
        }

	sf::Sprite(ecran, NULL, entity.setScale(ecran->format, 255, 255, 255));

	objectifsRestants = 0;

        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case MUR:
                        entity.setScale(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        entity.setScale(caisse, NULL, ecran, &position);
                        break;
                    case CAISSE_OK:
                        entity.setScale(caisseOK, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        entity.setScale(objectif, NULL, ecran, &position);
                        objectifsRestants = 1;
                        break;
                }
            }
        }

	if (!objectifsRestants)
            continuer = 0;

	position.x = positionJoueur.x * TAILLE_BLOC;
    position.y = positionJoueur.y * TAILLE_BLOC;
    entity.setPosition(marioActuel, NULL, ecran, &position);

}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], entity.setPosition(*pos), int direction)
{

    switch(direction)
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

