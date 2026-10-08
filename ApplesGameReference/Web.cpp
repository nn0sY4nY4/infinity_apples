#include "Web.h"
#include "GameSettings.h"

#include <cstdlib>

namespace ApplesGame
{
	void InitWeb(Web& web, const sf::Texture& texture)
	{
		// init wóè state
		web.position.x = (float)(rand() % (SCREEN_WIDTH + 1));
		web.position.y = (float)(rand() % (SCREEN_HEGHT + 1));

		// Init sprite
		web.sprite.setTexture(texture);
		web.sprite.setOrigin(GetSpriteOrigin(web.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		web.sprite.setScale(GetSpriteScale(web.sprite, { WEB_SIZE, WEB_SIZE }));
	}

	void DrawWeb(Web& web, sf::RenderWindow& window)
	{
		web.sprite.setPosition(OurVectorToSf(web.position));
		window.draw(web.sprite);
	}
}