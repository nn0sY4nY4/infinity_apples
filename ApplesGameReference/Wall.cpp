#include "Wall.h"
#include "GameSettings.h"

#include <cstdlib>

namespace ApplesGame
{
	void InitWall(Wall& wall, const sf::Texture& texture)
	{
		// init wall state
		wall.position.x = (float)(rand() % (SCREEN_WIDTH + 1));
		wall.position.y = (float)(rand() % (SCREEN_HEGHT + 1));

		// Init sprite
		wall.sprite.setTexture(texture);
		wall.sprite.setOrigin(GetSpriteOrigin(wall.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		wall.sprite.setScale(GetSpriteScale(wall.sprite, { WALL_SIZE, WALL_SIZE }));
	}

	void DrawWall(Wall& wall, sf::RenderWindow& window)
	{
		wall.sprite.setPosition(OurVectorToSf(wall.position));
		window.draw(wall.sprite);
	}
}