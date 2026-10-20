//#pragma once
//#include <SFML/Graphics.hpp>
//#include "Math.h"
//#include "GameSettings.h"
//#include "algorithm"
//
//namespace ApplesGame {
//
//	class LifeBar
//	{
//	public:
//		sf::Texture texture;
//		sf::Sprite sprite;
//		sf::RectangleShape bar;
//
//		int max = 100;
//		int hp = 100;
//
//		LifeBar()
//		{
//			if (texture.loadFromFile("Resources/;ife.png"))
//			{
//				sprite.setTexture(texture);
//
//				sprite.setTextureRect(
//					sf::IntRect(783, 2, 15, 84));
//
//				sprite.setScale(1.f, 1.f);
//			}
//
//			bar.setSize(sf::Vector2f(10.f, 0.f));
//			bar.setFillColor(sf::Color::Black);
//		}
//
//		void reset()
//		{
//			hp = max;
//			update(hp);
//		}
//
//		void update(int k)
//		{
//			hp = std::max(0, std::min(k, max));
//
//			// At 100 HP the black rectangle has zero height.
//			// At 0 HP it covers the full 70-pixel bar.
//			float emptyHeight =
//				70.f * (max - hp) / max;
//
//			bar.setSize(
//				sf::Vector2f(10.f, emptyHeight));
//		}
//
//		void draw(sf::RenderWindow& window)
//		{
//			sf::Vector2f center =
//				window.getView().getCenter();
//
//			sf::Vector2f size =
//				window.getView().getSize();
//
//			float x = center.x - size.x / 2.f + 10.f;
//			float y = center.y - size.y / 2.f + 10.f;
//
//			sprite.setPosition(x, y);
//			bar.setPosition(x + 4.f, y + 4.f);
//
//			// First draw the health image, then its black overlay.
//			window.draw(sprite);
//			window.draw(bar);
//		}
//	};
//}
//
