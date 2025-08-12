#include <string>
#include <SFML/Graphics.hpp>
#include "core/game.h"
#include "managers/resource_manager.h"
#include "game_objects/player.h"
#include "game_objects/alien.h"



Game::Game() : resourceManager(), 
               player(resourceManager),
	           p1ScoreText(resourceManager.getFont(), convertScore(score)),
               p1Score(resourceManager.getFont(), "SCORE< 1 >"),
	           p2ScoreText(resourceManager.getFont(), "SCORE< 2 >"),
               highScoreText(resourceManager.getFont(), "HI-SCORE"),
               highScoreNum(resourceManager.getFont(), convertScore(highScore)) {


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

	// TODO: Add options for game states
	target.draw(p1ScoreText);
	target.draw(p1Score);
	target.draw(p2ScoreText);
	target.draw(highScoreText);
	target.draw(highScoreNum);
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

std::string Game::convertScore(int score) {
	std::string strScore = std::to_string(score);

	while (strScore.length() < 4) {
		strScore = "0" + strScore;
	}

	return strScore;
}