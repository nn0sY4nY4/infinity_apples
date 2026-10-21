#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Game.h"

using namespace ApplesGame;

enum class GameScreen
{
    Menu,
    Playing
};

void HandleWindowEvents(
    sf::RenderWindow& window,
    GameScreen& screen,
    GameState& gameState,
    sf::Clock& game_clock,
    sf::Time& lastTime)
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type != sf::Event::KeyPressed)
            continue;

        if (event.key.code == sf::Keyboard::Escape)
        {
            if (screen == GameScreen::Playing)
                screen = GameScreen::Menu;
            else
                window.close();

            continue;
        }

        if (screen != GameScreen::Menu)
            continue;

        switch (event.key.code)
        {
        case sf::Keyboard::Num1:
            gameState.mode = GameMode::FiniteApples;
            break;

        case sf::Keyboard::Num2:
            gameState.mode = GameMode::InfiniteApples;
            break;

        case sf::Keyboard::Num3:
            gameState.mode = GameMode::InfiniteApplesBoost;
            break;

        default:
            continue;
        }

        RestartGame(gameState);
        screen = GameScreen::Playing;
        lastTime = game_clock.getElapsedTime();
    }
}

int main()
{
	// Init random number generator
	unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
	srand(seed);

	// Init window
	sf::RenderWindow window(sf::VideoMode(ApplesGame::SCREEN_WIDTH, ApplesGame::SCREEN_HEGHT), "InfinityApples");

	ApplesGame::GameState gameState;
	InitGame(gameState);

	// Init game clock
	sf::Clock game_clock;
	sf::Time lastTime = game_clock.getElapsedTime();

    GameScreen screen = GameScreen::Menu;

    sf::Font font;
    if (!font.loadFromFile(
        RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"))
    {
        return 1;
    }

    sf::Text menuText;
    menuText.setFont(font);
    menuText.setCharacterSize(32);
    menuText.setFillColor(sf::Color::White);
    menuText.setString(
        "INFINITY APPLES\n\n"
        "1 - Finite Apples\n\n"
        "2 - Infinite Apples\n\n"
        "3 - Infinite Apples + Boost\n\n"
        "ESC - Exit"
    );
    menuText.setPosition(100.f, 70.f);

    while (window.isOpen())
    {
        HandleWindowEvents(
            window, screen, gameState, game_clock, lastTime);

        if (!window.isOpen())
            break;

        window.clear(sf::Color(143, 71, 71));

        if (screen == GameScreen::Menu)
        {
            window.draw(menuText);
        }
        else
        {
            HandleInput(gameState);

            sf::Time currentTime = game_clock.getElapsedTime();
            float timeDelta =
                currentTime.asSeconds() - lastTime.asSeconds();
            lastTime = currentTime;

            UpdateGame(gameState, timeDelta);
            DrawGame(gameState, window);
        }

        window.display();
    }
}