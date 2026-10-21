#include "Player.h"
#include <assert.h>
#include "GameSettings.h"
#include "Apple.h"
#include "Wall.h"
#include "Web.h"


namespace ApplesGame
{
	void InitPlayer(Player& player, const sf::Texture& texture)
	{
		// Init player state
		player.position.x = (float)SCREEN_WIDTH / 2.f;
		player.position.y = (float)SCREEN_HEGHT / 2.f;
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Up;
		player.isOnWeb = false;
		player.HP = INITIAL_HP;

		// Init sprite
		player.sprite.setTexture(texture);
		player.sprite.setOrigin(GetSpriteOrigin(player.sprite, {0.5f, 0.5f})); // We need to use texture as origin ignores scale
		player.sprite.setScale(GetSpriteScale(player.sprite, {PLAYER_SIZE, PLAYER_SIZE}));
	}

	void UpdatePlayer(Player& player, float timeDelta)
	{
		// Move player
		switch (player.direction)
		{
			case PlayerDirection::Up:
			{
				player.position.y -= player.speed * timeDelta;
				break;
			}
			case PlayerDirection::Right:
			{
				player.position.x += player.speed * timeDelta;
				break;
			}
			case PlayerDirection::Down:
			{
				player.position.y += player.speed * timeDelta;
				break;
			}
			case PlayerDirection::Left:
			{
				player.position.x -= player.speed * timeDelta;
				break;
			}
		}
	}

	bool HasPlayerCollisionWithScreenBorder(const Player& player)
	{
		return (player.position.x - PLAYER_SIZE / 2.f < 0) ||
			(player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH) ||
			(player.position.y - PLAYER_SIZE / 2.f < 0) ||
			(player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEGHT);
	}

	bool HasPlayerCollisionWithApple(const Player& player, const Apple& apple)
	{
		float dx = player.position.x - apple.position.x;
		float dy = player.position.y - apple.position.y;
		float distance = sqrt(dx * dx + dy * dy);
		return distance < (PLAYER_SIZE + APPLE_SIZE) / 2.f;
	}

	bool HasPlayerCollisionWithWall(const Player& player, const Wall& wall)
	{
		float dx = player.position.x - wall.position.x;
		float dy = player.position.y - wall.position.y;
		float distance = sqrt(dx * dx + dy * dy);
		return distance < (PLAYER_SIZE + WALL_SIZE) / 2.f;
	}

	bool HasPlayerCollisionWithWeb(const Player& player, const Web& web)
	{
		float dx = player.position.x - web.position.x;
		float dy = player.position.y - web.position.y;
		float distance = sqrt(dx * dx + dy * dy);
		return distance < (PLAYER_SIZE + WEB_SIZE) / 2.f;
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(OurVectorToSf(player.position));

		const sf::Vector2f spriteScale = (GetSpriteScale(player.sprite, { PLAYER_SIZE, PLAYER_SIZE }));

		// We need to rotate and flip sprite to match player direction
		switch (player.direction)
		{
			case PlayerDirection::Up:
			{
				player.sprite.setScale(spriteScale.x, spriteScale.y);
				player.sprite.setRotation(-90.f);
				break;
			}
			case PlayerDirection::Right:
			{
				player.sprite.setScale(spriteScale.x, spriteScale.y);
				player.sprite.setRotation(0.f);
				break;
			}
			case PlayerDirection::Down:
			{
				player.sprite.setScale(spriteScale.x, spriteScale.y);
				player.sprite.setRotation(90.f);
				break;
			}
			case PlayerDirection::Left:
			{
				player.sprite.setScale(-spriteScale.x, spriteScale.y);
				player.sprite.setRotation(0.f);
				break;
			}
		}

		window.draw(player.sprite);
	}
}
