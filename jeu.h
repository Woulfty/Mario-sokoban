#pragma once
#include <SFML/Graphics.hpp>

void jouer(sf::RenderWindow* ecran);
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i * pos, int direction);
void deplacerCaisse(int *premiereCase, int *secondeCase);