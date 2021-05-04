

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "const.cpp"

int main(int argc, char **argv)
{
	sf::RenderWindow Window(sf::VideoMode(800, 600), "SFML window");

	// Charger les textures & sprite une fois avant la boucle de jeu
	sf::Texture texture;
	if (!texture.loadFromFile("menu.JPG"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);

	// Boucle de jeu
	while (Window.isOpen())
	{
		// Process events
		sf::Event event;
		while (Window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				Window.close();
		}
		// Clear screen
		Window.clear();
		// Draw the sprites
		Window.draw(sprite);
		// ...
		// C'est ici qu'il faut dessiner toute les choses que vous voulez afficher à l'écran


		// Update the window
		Window.display();
	}
		
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (Window.pollEvent(event))
		{
			
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == sf::Event::Closed)
			{ 
				Window.close();
		
			}
		
		}
		
            return 0;
	}


	