#include <string>
#include <SFML/Graphics.hpp>
#include "core/game.h"
#include "managers/resource_manager.h"
#include "game_objects/player.h"
#include "game_objects/alien.h"
#include <UI/ui.h>

constexpr int MAX_SIDE_MOVES = 3;
constexpr float ALIEN_SPEED = 0.25f;
constexpr sf::Vector2f ALIEN_HORIZONTAL_STEP = { 8.f, 0.f };
constexpr sf::Vector2f ALIEN_VERTICAL_STEP = { 0.f, 20.f };
constexpr sf::Vector2f PLAYER_START_POS = { 500.f, 870.f };
constexpr sf::Vector2f PLAYER_SPEED = { 150.f, 0.f };

Game::Game() : resourceManager(), 
               player(resourceManager, PLAYER_START_POS),
	           alienMoveTimer(ALIEN_SPEED),
	           ui(resourceManager, score, highScore, player.getLives()) {


}

void Game::init() {
	initAliens();
}

void Game::begin() {
	gameState = PLAYING;
	
}

void Game::update(sf::RenderTarget& target, float deltaTime) {
	switch (gameState) {
	    case MENU: 
		    ui.renderMenu(target);
			ui.renderHUD(target, player);
		    break;
	    case PLAYING:
		    ui.renderHUD(target, player);

		    movePlayer(deltaTime);
		    moveAliens(aliens, deltaTime);

		    // Draw alien after flipping sprite
		    for (auto& alien : aliens) {
			    alien.update(deltaTime);
			    target.draw(alien.getCurrentSprite());
		    }
		    target.draw(player.getSprite());

		    break;
	    default:
		    ui.renderHUD(target, player);
		    std::cout << "Default case! Check code!";

	}

}


// Puts aliens in initial positions
void Game::initAliens() {
	for (int row = 4; row >= 0; row--) {
		for (int col = 0; col < 11; col++) {
			AlienType type = AlienType::SQUID;
			// Left offset + (col * spacing), Top offset + (row * spacing)
			sf::Vector2f position = { 120.f + col * 50.f, 200.f + row * 50 };

			if (row > 0 && row < 3) {
				type = AlienType::CRAB;
				position = { 115.f + col * 50.f, 200.f + row * 50 };
			}
			else if (row > 2) {
				type = AlienType::OCTOPUS;
			}

			aliens.emplace_back(resourceManager, type, position);
		}
	}

}

void Game::moveAliens(std::vector<Alien>& aliens, float deltaTime) {
	alienMoveTimer -= deltaTime;

	if (alienMoveTimer <= 0) {
		if (alienMoveCounter < MAX_SIDE_MOVES && aliensDirection == alienDirection::RIGHT) {
			for (int i = 0; i < 11 && aliensMoved < aliens.size(); i++)  {
				aliens[aliensMoved].move(ALIEN_HORIZONTAL_STEP);
				aliensMoved++;
			}

			if (aliensMoved >= aliens.size()) {
				aliensMoved = 0;
				alienMoveCounter++;
			}

		}
		else if (alienMoveCounter == MAX_SIDE_MOVES) {
			for (auto& alien : aliens) {
				alien.move(ALIEN_VERTICAL_STEP);
			}

			alienMoveCounter = 0;
			aliensDirection = (aliensDirection == alienDirection::RIGHT) ?
				alienDirection::LEFT : alienDirection::RIGHT;

		}
		else if (alienMoveCounter < MAX_SIDE_MOVES && aliensDirection == alienDirection::LEFT) {
			for (int i = 0; i < 11 && aliensMoved < aliens.size(); i++) {
				aliens[aliensMoved].move({ -ALIEN_HORIZONTAL_STEP.x, ALIEN_HORIZONTAL_STEP.y });
				aliensMoved++;
			}

			if (aliensMoved >= aliens.size()) {
				aliensMoved = 0;
				alienMoveCounter++;
			}

		}
		alienMoveTimer = ALIEN_SPEED;
	}
}

void Game::movePlayer(float deltaTime) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
		player.move({ -PLAYER_SPEED.x * deltaTime, PLAYER_SPEED.y });
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) { 
		player.move({ PLAYER_SPEED.x * deltaTime, PLAYER_SPEED.y });
	}

}

std::string Game::convertScore(int score) {
	std::string strScore = std::to_string(score);

	while (strScore.length() < 4) {
		strScore = "0" + strScore;
	}

	return strScore;
}
