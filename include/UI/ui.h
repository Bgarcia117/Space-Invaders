#pragma once
#include <optional>
#include <array>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <managers/resource_manager.h>
#include "game_objects/player.h"

class UI {
public:
	UI(ResourceManager& resourceManager, int score, int highScore, int playerLives);
	std::string scoreToText(int score);
	void renderMenu(sf::RenderTarget& target);
	void renderHUD(sf::RenderTarget& target, const Player& playerOne);


private:
	// Displayed on menu & HUD
	sf::Font& font;
	sf::Text p1ScoreText;
	sf::Text p1Score;
	sf::Text p2ScoreText;
	sf::Text highScoreText;
	sf::Text highScoreNum;
	sf::Text creditsText;

	// Displayed on Start menu
	sf::Text titleTopLine;
	sf::Text titleBottomLine;
	sf::Text scoreTable;
	sf::Text ufoPointsText;
	sf::Text squidPointsText;
	sf::Text crabPointsText;
	sf::Text octopusPointsText;
	std::array<std::optional<sf::Sprite>, 4> menuAliensSprites;


	// HUD display while in game
	sf::Text livesLeft;
	std::optional<sf::Sprite> lifeSprite;

	void setUpMenuText();
	void setUpMenuSprites(ResourceManager& resourceManager);
	void setUpHUD();

};