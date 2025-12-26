#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/game.h" 

constexpr int SCREEN_WIDTH = 768;
constexpr int SCREEN_HEIGHT = 1024;

int main() {
	Game game;
	game.init();

	sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned int>(SCREEN_WIDTH),
		                                    static_cast<unsigned int>(SCREEN_HEIGHT)}),
		                                    "Space Invaders Clone");
	window.setFramerateLimit(60);

	sf::Clock clock;

	// Run as long as the window is open
	while (window.isOpen()) {
		// Time passed since last frame
		float deltaTime = clock.restart().asSeconds();

		// Check all events triggered in the loop
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}

			game.handleInput(*event);
		}

		window.clear(sf::Color::Black);
		game.update(window, deltaTime);
		window.display();
	}

	return 0;
}