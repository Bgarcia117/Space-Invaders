#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>

constexpr int SCREEN_WIDTH = 1600;
constexpr int SCREEN_HEIGHT = 900;

int main() {
	const sf::Texture texture("assets/sprites/alien.png");
    
	sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned int>(SCREEN_WIDTH),
		                                    static_cast<unsigned int>(SCREEN_HEIGHT)}),
		                                    "Space Invaders Clone");

	sf::Sprite sprite(texture);
	sprite.setTextureRect({ {10, 10}, {50, 30} });
	sprite.setColor({ 255, 255, 255, 200 });
	sprite.setPosition({ 100.f, 25.f });

	// Run as long as the window is open
	while (window.isOpen()) {

		// Check all events triggered in the loop
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		window.clear();
		// window.draw(sprite);
		window.display();
	}

	return 0;
}