#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "const.h"
#include "jeu.h"
#include "editeur.h"
int main(int argc, char **argv)
{
    sf::Window window(sf::VideoMode(800, 600), "My window");

    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

	{
		SFML_Surface *ecran = NULL, *menu = NULL;
		SFML_Rect positionMenu;
		SFML_Event event;

		int continuer = 1;

		SFML_Init(SDL_INIT_VIDEO);

		SFML_WM_SetIcon(IMG_Load("caisse.jpg"), NULL);
		ecran = SFML_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
		SFML_WM_SetCaption("Mario Sokoban", NULL);

		menu = IMG_Load("menu.jpg");
		positionMenu.x = 0;
		positionMenu.y = 0;

		while (continuer)
		{
			SFML_WaitEvent(&event);
			switch (event.type)
			{
			case SFML_QUIT:
				continuer = 0;
				break;
			case SFML_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SFML_ESCAPE: // Veut arrêter le jeu
					continuer = 0;
					break;
				case SFML_KP1: // Demande à jouer
					jouer(ecran);
					break;
				case SFML_KP2: // Demande l'éditeur de niveaux
					editeur(ecran);
					break;
				}
				break;
			}

			// Effacement de l'écran
			SFML_FillRect(ecran, NULL, SFML_MapRGB(ecran->format, 0, 0, 0));
			SFML_BlitSurface(menu, NULL, ecran, &positionMenu);
			SFML_Flip(ecran);
		}

		SFML_FreeSurface(menu);
		SFML_Quit();

		return EXIT_SUCCESS;
	}







	
}