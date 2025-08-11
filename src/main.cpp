#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "core/game.h" 
#include "game_objects/alien.h"
#include "managers/resource_manager.h"

constexpr int SCREEN_WIDTH = 768;
constexpr int SCREEN_HEIGHT = 1024;

int main() {
	// ========= TESTING =========
	Game game;
	game.init();
	/*
	const sf::Texture texture("assets/sprites/new-alien.png");
	sf::Sprite sprite(texture);
	sprite.setTextureRect({ {0, 0}, {192, 192} }); // Top Corner , Right Corner
	// sprite.setColor(sf::Color::Red);
	sprite.setPosition({ 500.f, 500.f });
	*/

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

		window.clear(sf::Color::Black);
		game.update(window);
		window.display();
	}

	return 0;
}