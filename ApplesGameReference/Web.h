#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct Web
	{
		Position position;
		sf::Sprite sprite;
	};

	void InitWeb(Web& web, const sf::Texture& texture);
	void DrawWeb(Web& web, sf::RenderWindow& window);
}
