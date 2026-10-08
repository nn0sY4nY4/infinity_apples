#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
	void InitGame(GameState& gameState)
	{
		// Init game resources (terminate if error)
		assert(gameState.playerTexture.loadFromFile(RESOURCES_PATH + "Pacman.png"));
		assert(gameState.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(gameState.wallTexture.loadFromFile(RESOURCES_PATH + "Wall.png"));
		assert(gameState.webTexture.loadFromFile(RESOURCES_PATH + "Web.png"));
		assert(gameState.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		InitUI(gameState.uiState, gameState.font);
		RestartGame(gameState);

		if (!gameState.backMusic.openFromFile("Resources/pacman.wav"))
			return;

		gameState.backMusic.setLoop(true);
		gameState.backMusic.play();
		gameState.backMusic.setVolume(75);

		if (!gameState.eatBuffer.loadFromFile("Resources/eat.wav"))
			return;

		if (!gameState.crashBuffer.loadFromFile("Resources/crash.wav"))
			return;

		if (!gameState.slowBuffer.loadFromFile("Resources/slow.wav"))
			return;

		gameState.eatSound.setBuffer(gameState.eatBuffer);
		gameState.eatSound.setVolume(50);
		gameState.crashSound.setBuffer(gameState.crashBuffer);
		gameState.crashSound.setVolume(75);
		gameState.slowSound.setBuffer(gameState.slowBuffer);
		gameState.slowSound.setVolume(50);
	}

	void RestartGame(GameState& gameState)
	{
		// Init player
		InitPlayer(gameState.player, gameState.playerTexture);
		// Init apples
		for (int i = 0; i < NUM_APPLES; i++)
		{
			InitApple(gameState.apples[i], gameState.appleTexture);
		}
		//Init walls
		for (int i = 0; i < NUM_WALLS; i++)
		{
			InitWall(gameState.walls[i], gameState.wallTexture);
		}
		//Init webs
		for (int i = 0; i < NUM_WEBS; i++)
		{
			InitWeb(gameState.webs[i], gameState.webTexture);
		}

		// Init game state
		gameState.backMusic.play();
		gameState.numEatenApples = 0;
		gameState.isGameOver = false;
		gameState.timeSinceGameOver = 0.f;
	}

	void HandleInput(GameState& gameState)
	{
		if (gameState.isGameOver)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				RestartGame(gameState);
			}

			// We don't handle input in game over state
			return;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||
			sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			gameState.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||
			sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			gameState.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||
			sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			gameState.player.direction = PlayerDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||
			sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			gameState.player.direction = PlayerDirection::Left;
		}
	}

	void UpdateGame(GameState& gameState, float timeDelta)
	{
		if (!gameState.isGameOver)
		{
			// Update player
			UpdatePlayer(gameState.player, timeDelta);

			for (int i = 0; i < NUM_APPLES; i++)
			{
				// Check collision with apple
				if (HasPlayerCollisionWithApple(gameState.player, gameState.apples[i]))
				{
					gameState.eatSound.play();
					// Move apple to a new random position
					InitApple(gameState.apples[i], gameState.appleTexture);
					// Increase eaten apples counter
					gameState.numEatenApples++;
					// Increase player speed
					gameState.player.speed += ACCELERATION;

				}
			}

			// Check collision with screen border
			if (HasPlayerCollisionWithScreenBorder(gameState.player))
			{
				gameState.backMusic.stop();
				gameState.crashSound.play();
				gameState.isGameOver = true;
				gameState.timeSinceGameOver = 0.f;
			}

			for (int i = 0; i < NUM_WALLS; i++)
			{
				// Check collision with walls
				if (HasPlayerCollisionWithWall(gameState.player, gameState.walls[i]))
				{
					gameState.backMusic.stop();
					gameState.crashSound.play();
					gameState.isGameOver = true;
					gameState.timeSinceGameOver = 0.f;
				}
			}

			bool isOnWeb = false;

			for (int i = 0; i < NUM_WEBS; i++)
			{
				if (HasPlayerCollisionWithWeb(gameState.player, gameState.webs[i]))
				{
					isOnWeb = true;
					break;
				}
			}
			
			if (isOnWeb && !gameState.player.isOnWeb)
			{
					gameState.slowSound.play();
					gameState.player.speed += SLOWDOWN;

					if (gameState.player.speed < 0.f)
					{
						gameState.player.speed = 0.f;
					}

			}
			gameState.player.isOnWeb = isOnWeb;
		}
		else
		{
			gameState.timeSinceGameOver += timeDelta;
		}

		UpdateUI(gameState.uiState, gameState, timeDelta);
	}

	void DrawGame(GameState& gameState, sf::RenderWindow& window)
	{
		// Draw player
		DrawPlayer(gameState.player, window);
		// Draw apples
		for (int i = 0; i < NUM_APPLES; i++)
		{
			DrawApple(gameState.apples[i], window);
		}

		for (int i = 0; i < NUM_WALLS; i++)
		{
			DrawWall(gameState.walls[i], window);
		}
		
		for (int i = 0; i < NUM_WEBS; i++)
		{
			DrawWeb(gameState.webs[i], window);
		}

		DrawUI(gameState.uiState, window);
	}
}
