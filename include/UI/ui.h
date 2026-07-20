#pragma once
#include <optional>
#include <array>
#include <string>
#include <queue>
#include <vector>
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
	void renderPlayP1(sf::RenderTarget& target);
	void renderGameOver(sf::RenderTarget& target);
	void renderBottomLine(sf::RenderTarget& target) const;
	void handleMenuInput(sf::Keyboard::Key key);

	void startTypingCoinMenu();
	void startTypingTableMenu();
	void startTypingGameOver();

	void setCredits(int credits);
	void setHighScore(int value);

	/**
	 * @brief Advances the typewriter to reveal the next letter in the text to be displayed.
	 *
	 * Reveals one letter at a time of the current full text to be displayed based on elapsed time.
	 * When the current text is fully revealed, it moves on to the next text in the queue.
	 * If the current entry is "displayTable", waits for TABLE_REVEAL_PAUSE seconds before
	 * displaying the score advance table and its sprites. (Simulates the original game menu)
	 *
	 * @param deltaTime the amount of time passed since the last frame was rendered
	 */
	void updateTypeWriter(float deltaTime);
	void setP1Score(int score);
	void setP1ScoreVisible(bool visible);
	bool isOnePlayerSelected() const;

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

	// Play Player One Menu
	sf::Text playP1Text;
	bool p1ScoreVisible = true;
	bool onePlayerSelected = true;

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
	std::vector<sf::Sprite> gameOverLetters;
	int gameOverLettersShown = 0;
	bool gameOverTyping = false;
	float gameOverTypeTimer = 0.0f;
	sf::Text pressEnterText;

	// HUD display while in game
	sf::Text livesLeft;
	std::optional<sf::Sprite> lifeSprite;
	sf::RectangleShape bottomLine;

	void setUpHUD();
	void setUpCoinMenu();
	void setUpTableMenu();
	void setUpSprites(ResourceManager& resourceManager);

	/**
	 * @brief Advances the typewriter to the next text to be displayed.
	 *
	 * Pops the front entry from the typing queue and resets the typewriter to start
	 * revealing characters from the start of the string. If the queue is empty, the
	 * current pointer is set to nullptr which stops the typewriter.
	 */
	void startNextText();
	void setUpPlayP1Text();

};