

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "const.cpp"

int main(int argc, char **argv)
{
	sf::RenderWindow Window(sf::VideoMode(500, 500), "SFML window");

	// Charger les textures & sprite une fois avant la boucle de jeu
	sf::Texture texture;
	if (!texture.loadFromFile("menu.JPG"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);
	sf::Style::Close;

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("super.MP3"))
		return -1;
	


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
		// C'est ici qu'il faut dessiner toute les choses que vous voulez afficher � l'�cran


		// Update the window
		Window.display();
	}
		
		// on inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				// la touche "1" est enfonc�e : on l'envoie sur le jeux
				character.move("jeux.cpp");
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				// la touche "2" est enfonc�e : on l'envoie sur l'�diteur
				character.move("editeur.cpp");
			}

			// �v�nement "fermeture demand�e" : on ferme la fen�tre
			if (event.type == sf::Event::Closed)
			{ 
				Window.close();
		
			}
		
		}
		
            return 0;

	}


	