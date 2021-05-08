#include "utils.h"

sf::Sprite * loadSprite(std::string path)
{
	sf::Sprite * result = nullptr;

	sf::Texture * texture = new sf::Texture();
	if (texture->loadFromFile(path) == true)
	{
		result = new sf::Sprite(*texture);
	}

	return result;
}

void removeSprite(sf::Sprite * sprite)
{
	delete sprite->getTexture();
	delete sprite;
}