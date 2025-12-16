#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <managers/resource_manager.h>

class UI {
public:
	UI(ResourceManager& resourceManager, int score, int highScore, int playerLives);
	std::string scoreToText(int score);
	void renderMenu(sf::RenderTarget& target);


private:
	// HUD while in game
	sf::Text p1ScoreText;
	sf::Text p1Score;
	sf::Text p2ScoreText;
	sf::Text highScoreText;
	sf::Text highScoreNum;
	sf::Text livesLeft;


};