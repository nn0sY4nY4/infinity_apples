#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct Wall
	{
		Position position;
		sf::Sprite sprite;
	};

	void InitWall(Wall& wall, const sf::Texture& texture);
	void DrawWall(Wall& wall, sf::RenderWindow& window);
}
