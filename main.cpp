
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "const.h"
#include "jeu.h"
#include "editeur.h"
#include "fichier.h"

int main(int argc, char **argv)
{
	sf::RenderWindow Window(sf::VideoMode(500, 500), "Mario Sokoban");

	// Charger les textures & sprite une fois avant la boucle de jeu
	sf::Texture texture;
	if (!texture.loadFromFile("menu.JPG"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);
	sf::Style::Close;

	sf::Music buffer;
	if (!buffer.openFromFile("super.ogg"))
		return -1;

	buffer.play();

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

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Numpad1)
				{
					// la touche "1" est enfoncée : on l'envoie sur le jeux
					jouer(&Window);
				}
				if (event.key.code == sf::Keyboard::Numpad2)
				{
					// la touche "2" est enfoncée : on l'envoie sur l'éditeur
					editeur(&Window);
				}
			}
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

	return 0;
}