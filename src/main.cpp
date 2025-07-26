#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>

constexpr int SCREEN_WIDTH = 1600;
constexpr int SCREEN_HEIGHT = 900;

int main() {
	sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned int>(SCREEN_WIDTH),
		                                    static_cast<unsigned int>(SCREEN_HEIGHT)}),
		                                    "Space Invaders Clone");

	const sf::Vector2u textureSize = texture.getSize();
	const float scaleX = desiredWidth / textureSize.x;
	const float scaleY = desiredHeight / textureSize.y;

	// Apply the scale
	sprite.setScale({ scaleX, scaleY });

	sprite.setColor({ 255, 255, 255, 255 });
	sprite.setPosition({ 100.f, 25.f });

	// Run as long as the window is open
	while (window.isOpen()) {

		// Check all events triggered in the loop
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		window.clear(sf::Color::White);
		window.draw(sprite);
		window.display();
	}

	std::cout << __cplusplus << "\n";

	return 0;
}