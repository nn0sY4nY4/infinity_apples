#include "UI.h"
#include "Game.h"
#include <string>

namespace ApplesGame
{
	void InitUI(UIState& uiState, const sf::Font& font) 
	{
		uiState.scoreText.setFont(font);
		uiState.scoreText.setCharacterSize(18);
		uiState.scoreText.setFillColor(sf::Color::Yellow);

		uiState.inputHintText.setFont(font);
		uiState.inputHintText.setCharacterSize(15);
		uiState.inputHintText.setFillColor(sf::Color::White);
		uiState.inputHintText.setString("Use arrow keys to move, Space to restart, ESC to exit");
		uiState.inputHintText.setOrigin(GetTextOrigin(uiState.inputHintText, { 1.f, 0.f } ));

		uiState.isGameOverTextVisible = false;
		uiState.gameOverText.setFont(font);
		uiState.gameOverText.setCharacterSize(48);
		uiState.gameOverText.setStyle(sf::Text::Bold);
		uiState.gameOverText.setFillColor(sf::Color::Red);
		uiState.gameOverText.setString("GAME OVER");
		uiState.gameOverText.setOrigin(GetTextOrigin(uiState.gameOverText, { 0.5f, 0.5f }));

		uiState.hpBarBack.setSize(sf::Vector2f(200.f, 20.f));
		uiState.hpBarBack.setFillColor(sf::Color(60,60,60));
		uiState.hpBarBack.setOutlineThickness(2.f);
		uiState.hpBarBack.setOutlineColor(sf::Color::White);

		uiState.hpBar.setSize(sf::Vector2f(200.f, 20.f));
		uiState.hpBar.setFillColor(sf::Color::Green);
	}

	void UpdateUI(UIState& uiState, const struct GameState& gameState, float timeDelta)
	{
		uiState.scoreText.setString
		(
			"\nApples eaten: " + std::to_string(gameState.numEatenApples) + "\nUr speed : " + std::to_string(gameState.player.speed)
		);

		uiState.isGameOverTextVisible = gameState.isGameOver;
		sf::Color gameOverTextColor = (int)gameState.timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
		uiState.gameOverText.setFillColor(gameOverTextColor);

		uiState.hpBar.setSize(sf::Vector2f(200.f * (float)gameState.player.HP / INITIAL_HP, 20.f));
		if ((float)gameState.player.HP / INITIAL_HP > 0.5f)
			uiState.hpBar.setFillColor(sf::Color::Green);
		else if ((float)gameState.player.HP / INITIAL_HP > 0.25f)
			uiState.hpBar.setFillColor(sf::Color::Yellow);
		else
			uiState.hpBar.setFillColor(sf::Color::Red);
	}

	void DrawUI(UIState& uiState, sf::RenderWindow& window)
	{
		uiState.scoreText.setPosition(10.f, 15.f);
		window.draw(uiState.scoreText);

		uiState.hpBarBack.setPosition(10.f, 10.f);
		window.draw(uiState.hpBarBack);

		uiState.hpBar.setPosition(10.f, 10.f);
		window.draw(uiState.hpBar);

		uiState.inputHintText.setPosition(window.getSize().x - 10.f, 10.f);
		window.draw(uiState.inputHintText);

		if (uiState.isGameOverTextVisible)
		{
			uiState.gameOverText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			window.draw(uiState.gameOverText);
		}
	}
}

