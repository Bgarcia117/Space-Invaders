#include <SFML/Graphics.hpp>
#include "core/game.h"
#include "managers/resource_manager.h"
#include "game_objects/player.h"
#include "game_objects/alien.h"



Game::Game() : resourceManager(), player(resourceManager), gameOver(false), score(0) {

}

void Game::init() {
	initAliens();
}

void Game::begin() {
	gameState = PLAYING;
	
}

void Game::update(sf::RenderTarget& target) {
	for (auto alien : aliens) {
		target.draw(alien.getSprite());
	}
}

void Game::initPlayer() {
	// set position
	// Call constructor:
}

void Game::initAliens() {
	
	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 11; col++) {
			AlienType type = AlienType::SQUID;
			// Left offset + (col * spacing), Top offset + (row * spacing)
			sf::Vector2f position = { 75.f + col * 60.f, 150.f + row * 50 };

			if (row > 0 && row < 3) {
				type = AlienType::CRAB;
			    position = {70.f + col * 60.f, 150.f + row * 50};
			}
			else if (row > 2) {
				type = AlienType::OCTOPUS;
			}
			
			aliens.emplace_back(resourceManager, type, position);
		}
	}

}