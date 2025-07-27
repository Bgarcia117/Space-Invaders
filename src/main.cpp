#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "core/game.h" // Testing 
#include "game_objects/alien.h"
#include "managers/resource_manager.h"

constexpr int SCREEN_WIDTH = 1600;
constexpr int SCREEN_HEIGHT = 900;

int main() {
	// ========= TESTING =========
	Game game;
	game.begin();


	sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned int>(SCREEN_WIDTH),
		                                    static_cast<unsigned int>(SCREEN_HEIGHT)}),
		                                    "Space Invaders Clone");

	// Run as long as the window is open
	while (window.isOpen()) {

		// Check all events triggered in the loop
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		window.clear(sf::Color::White);
		window.display();
	}

	return 0;
}