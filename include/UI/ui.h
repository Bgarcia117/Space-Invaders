#pragma once
#include <optional>
#include <array>
#include <unordered_map>
#include <string>
#include <queue>
#include <SFML/Graphics.hpp>
#include <managers/resource_manager.h>
#include "game_objects/player.h"

class UI {
public:
	UI(ResourceManager& resourceManager, int score, int highScore, int playerLives);
	std::string scoreToText(int score);
	void renderHUD(sf::RenderTarget& target, const Player& playerOne, bool showLives);
	void renderCoinMenu(sf::RenderTarget& target);
	void renderTableMenu(sf::RenderTarget& target);
	void renderGameOver(sf::RenderTarget& target);
	void handleMenuInput(sf::Keyboard::Key key);

	void startTypingCoinMenu();
	void startTypingTableMenu();
	void startTypingGameOver();
	void updateTypeWriter(float deltaTime);
	void setP1Score(int score);

private:
	// Type writer helpers
	struct TextToType {
		std::string fullText;            // Full text to be typed
		sf::Text* textPtr;               // Text obj pointer to be typed to
	};
	std::queue<TextToType> typingQueue;  // Queue of TextToType structs define above
	std::string currentFullText;         // Current entire string/text to be typed out
	sf::Text* currentTextPtr = nullptr;  // Points to sf::Text obj being typed to
	int charIndex = 0;                   // Tracks how much of a string has been shown
	float timePassed = 0.0f;             // Tracks time passed since last char was shown
	float timePerChar = 0.05f;           // Time between revealing characters

	bool showTableSprites = false;

	sf::Font& font;

	// Displayed on coin menu
	sf::Text insertCoinText;
	sf::Text selectPromptText;
	sf::Text onePlayerText;
	sf::Text twoPlayerText;

	// HUD Text
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

	// Game Over Screen Text
	sf::Text gameOverText;

	// HUD display while in game
	sf::Text livesLeft;
	std::optional<sf::Sprite> lifeSprite;

	void setUpHUD();
	void setUpCoinMenu();
	void setUpTableMenu();
	void setUpGameOverScreen();
	void setUpSprites(ResourceManager& resourceManager);
	void startNextText();

};