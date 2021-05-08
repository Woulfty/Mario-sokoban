#pragma once

#include <SFML/Graphics.hpp>
#include <string>

sf::Sprite * loadSprite(std::string path);
void removeSprite(sf::Sprite * sprite);