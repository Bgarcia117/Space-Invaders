#include <string>
#include <SFML/Graphics.hpp>
#include "core/game.h"
#include "managers/resource_manager.h"
#include "game_objects/player.h"
#include "game_objects/alien.h"

constexpr int MAX_SIDE_MOVES = 3;
constexpr float ALIEN_SPEED = 0.25f;
constexpr sf::Vector2f ALIEN_HORIZONTAL_STEP = { 8.f, 0.f };
constexpr sf::Vector2f ALIEN_VERTICAL_STEP = { 0.f, 20.f };
constexpr sf::Vector2f PLAYER_START_POS = { 500.f, 950.f };

Game::Game() : resourceManager(), 
               player(resourceManager, PLAYER_START_POS),
	           p1ScoreText(resourceManager.getFont(), convertScore(score)),
               p1Score(resourceManager.getFont(), "SCORE< 1 >"),
	           p2ScoreText(resourceManager.getFont(), "SCORE< 2 >"),
               highScoreText(resourceManager.getFont(), "HI-SCORE"),
               highScoreNum(resourceManager.getFont(), convertScore(highScore)),
	           livesLeft(resourceManager.getFont(), "3"), 
               alienMoveTimer(ALIEN_SPEED) {


	p1ScoreText.setCharacterSize(40);
	p1ScoreText.setPosition({ 115.f, 90.f });
	p1Score.setCharacterSize(40);
	p1Score.setPosition({ 70.f, 45.f });

	p2ScoreText.setCharacterSize(40);
	p2ScoreText.setPosition({ 520.f, 45.f });

	highScoreText.setCharacterSize(40);
	highScoreText.setPosition({ 310.f, 45.f });
	highScoreNum.setCharacterSize(40);
	highScoreNum.setPosition({ 345.f, 90.f });

	livesLeft.setCharacterSize(40);
	livesLeft.setPosition({ 70.f, 950.f });

}

void Game::init() {
	initAliens();
}

void Game::begin() {
	gameState = PLAYING;
	
}

void Game::update(sf::RenderTarget& target, float deltaTime) {

	moveAliens(aliens, deltaTime);
	
	for (auto& alien : aliens) {
		alien.update(deltaTime);
		target.draw(alien.getCurrentSprite());
	}
	target.draw(player.getSprite());

	// TODO: Add options for game states
	target.draw(p1ScoreText);
	target.draw(p1Score);
	target.draw(p2ScoreText);
	target.draw(highScoreText);
	target.draw(highScoreNum);
	target.draw(livesLeft);
}

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

// TODO: FIX ORDER IN WHICH THE ALIENS START MOVING & DECREASE STEP AMOUNT
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

std::string Game::convertScore(int score) {
	std::string strScore = std::to_string(score);

	while (strScore.length() < 4) {
		strScore = "0" + strScore;
	}

	return strScore;
}