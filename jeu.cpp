/*
jeu.c
-----

Par mateo21, pour Le Site du Z�r0 (www.siteduzero.com)

R�le : fonctions du jeu.
*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <SFML/SFML.h>
#include <SFML/SFML_image.h>

#include "constantes.h"
#include "jeu.h"

void jouer(sf::Transformable* ecran)
{
    entity.setOrigin( *mario[4] = {NULL}); // 4 surfaces pour chacune des directions de mario
    entity.setOrigin( *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL);
    entity.setPosition(positionJoueur);
    entity.move(event);

    int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    // Chargement des sprites (d�cors, personnage...)
    mur = IMG_Load("mur.jpg");
    caisse = IMG_Load("caisse.jpg");
    caisseOK = IMG_Load("caisse_ok.jpg");
    objectif = IMG_Load("objectif.png");
    mario[BAS] = IMG_Load("mario_bas.gif");
    mario[GAUCHE] = IMG_Load("mario_gauche.gif");
    mario[HAUT] = IMG_Load("mario_haut.gif");
    mario[DROITE] = IMG_Load("mario_droite.gif");

    marioActuel = mario[BAS]; // Mario sera dirig� vers le bas au d�part

    // Chargement du niveau
    if (!chargerNiveau(carte))
        exit(EXIT_FAILURE); // On arr�te le jeu si on n'a pas pu charger le niveau

    // Recherche de la position de Mario au d�part
    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            if (carte[i][j] == MARIO) // Si Mario se trouve � cette position sur la carte
            {
                positionJoueur.x = i;
                positionJoueur.y = j;
                carte[i][j] = VIDE;
            }
        }
    }

    // Activation de la r�p�tition des touches
    sf::Event KeyPressed(100, 100);
	if (App.GetEvent(KeyPressed)){
		while (continuer)
		{
			SFML_WaitEvent(&event);
	switch(event.type)
{
		case SFML_QUIT:
			continuer = 0;
			break;
		case KeyPressed:
			switch(event.key.keysym.sym)
			{
				case SFMLK_ESCAPE:
					continuer = 0;
					break;
					//Commande pour allé en haut
				case Event.Key.Z:
					marioActuel = mario[HAUT];
					deplacerJoueur(carte, &positionJoueur, HAUT);
					break;
					//commande pour allé en bas
				case Event.Key.S:
					marioActuel = mario[BAS];
					deplacerJoueur(carte, &positionJoueur, BAS);
					break;
					//Commande pour allé a droite
				case Event.Key.D:
					marioActuel = mario[DROITE];
					deplacerJoueur(carte, &positionJoueur, DROITE);
					break;
					//Commande pour allé a gauche
				case Event.Key.Q:
					marioActuel = mario[GAUCHE];
					deplacerJoueur(carte, &positionJoueur, GAUCHE);
					break;
			}
			break;
	}
}

        // Effacement de l'�cran
        sf::Sprite(ecran, NULL, entity.setScale(ecran->format, 255, 255, 255));

        // Placement des objets � l'�cran
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

        // Si on n'a trouv� aucun objectif sur la carte, c'est qu'on a gagn�
        if (!objectifsRestants)
            continuer = 0;

        // On place le joueur � la bonne position
        position.x = positionJoueur.x * TAILLE_BLOC;
        position.y = positionJoueur.y * TAILLE_BLOC;
        entity.setPosition(marioActuel, NULL, ecran, &position);



        SFML_Flip(ecran);
    }
    /*
        // D�sactivation de la r�p�tition des touches (remise � 0)
        sf::Sprite(0, 0);

        // Lib�ration des surfaces charg�es
        SFML_FreeSurface(mur);
        SFML_FreeSurface(caisse);
        SFML_FreeSurface(caisseOK);
        SFML_FreeSurface(objectif);
        for (i = 0 ; i < 4 ; i++)
            SFML_FreeSurface(mario[i]);
    */
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], entity.setPosition(*pos), int direction)
{
    switch(direction)
    {
        case HAUT:
            if (pos->y - 1 < 0) // Si le joueur d�passe l'�cran, on arr�te
                break;
            if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur, on arr�te
                break;
            // Si on veut pousser une caisse, il faut v�rifier qu'il n'y a pas de mur derri�re (ou une autre caisse, ou la limite du monde)
            if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
                (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
                carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
                break;

            // Si on arrive l�, c'est qu'on peut d�placer le joueur !
            // On v�rifie d'abord s'il y a une caisse � d�placer
            deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);

            pos->y--; // On peut enfin faire monter le joueur (oufff !)
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

