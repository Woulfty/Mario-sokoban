#pragma once
#pragma once
#include <SFML/Graphics.hpp>

int jouer(sf::RenderWindow* Window);
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i * pos, int direction);
void deplacerCaisse(int *premiereCase, int *secondeCase);