#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <UI/ui.h>
#include <managers/resource_manager.h>
#include "game_objects/player.h"

constexpr int TEXT_SIZE = 22;

// Colors
constexpr sf::Color LIGHT_GREEN(42, 249, 50);

// HUD Text Positions
// Player 1
constexpr sf::Vector2f P1_SCORE_TEXT_POS = { 115.f, 90.f };
constexpr sf::Vector2f P1_SCORE_NUM_POS = { 70.f, 45.f };

// Player 2
constexpr sf::Vector2f P2_SCORE_TEXT_POS = { 530.f, 45.f };

constexpr sf::Vector2f HIGH_SCORE_TEXT_POS = { 300.f, 45.f };
constexpr sf::Vector2f HIGH_SCORE_NUM_POS = { 320.f, 90.f };
constexpr sf::Vector2f LIVES_LEFT_POS = { 65.f, 960.f };
constexpr sf::Vector2f LIFE_SPRITE_POS = { 110.f, 960.f };
constexpr float LIFE_SPRITE_SPACING = 45.f;

// Coin Menu Text Positons 
constexpr sf::Vector2f INSERT_COIN_TEXT_POS = { 250.f, 300.f };
constexpr sf::Vector2f SELECT_PROMPT_TEXT_POS = { 180.f, 400.f };
constexpr sf::Vector2f ONE_PLAYER_TEXT_POS = { 180.f, 475.f };
constexpr sf::Vector2f TWO_PLAYER_TEXT_POS = { 180.f, 550.f };

// Menu Table Text Positions
constexpr sf::Vector2f TITLE_TOP_LINE_POS = { 345.f, 224.f };
constexpr sf::Vector2f TITLE_BOTTOM_LINE_POS = { 210.f, 304.f };
constexpr sf::Vector2f SCORE_TABLE_POS = { 160.f, 414.f };
constexpr sf::Vector2f UFO_POINTS_TEXT_POS = { 290.f, 480.f };
constexpr sf::Vector2f SQUID_POINTS_TEXT_POS = { 290.f, 530.f };
constexpr sf::Vector2f CRAB_POINTS_TEXT_POS = { 290.f, 580.f };
constexpr sf::Vector2f OCTOPUS_POINTS_TEXT_POS = { 290.f, 630.f };
constexpr sf::Vector2f CREDITS_TEXT_POS = { 520.f, 960.f };

// Menu Table Alien Sprite Positions
constexpr sf::Vector2f MENU_UFO_POS = { 245.f, 480.f };
constexpr sf::Vector2f MENU_SQUID_POS = { 256.f, 528.f };
constexpr sf::Vector2f MENU_CRAB_POS = { 252.f, 580.f };
constexpr sf::Vector2f MENU_OCTOPUS_POS = { 253.f, 630.f };

// Menu Table Alien Sprite Scales (Scales sprite size)
constexpr sf::Vector2f MENU_UFO_SCALE = { 1.75f, 1.60f };
constexpr sf::Vector2f MENU_SQUID_SCALE = { 1.5f, 1.5f };
constexpr sf::Vector2f MENU_CRAB_SCALE = { 1.37f, 1.35f };
constexpr sf::Vector2f MENU_OCTOPUS_SCALE = { 1.62f, 1.57f };



UI::UI(ResourceManager& resourceManager, int score, int highScore, int playerLives) 
	: font(resourceManager.getFont()),
	insertCoinText(font),
	selectPromptText(font),
	onePlayerText(font),
	twoPlayerText(font),
	p1ScoreText(font, scoreToText(score)),
	p1Score(font),
	p2ScoreText(font),
	highScoreText(font),
	highScoreNum(font, scoreToText(highScore)),
	creditsText(font),
	titleTopLine(font),
	titleBottomLine(font),
	scoreTable(font),
    ufoPointsText(font),
    squidPointsText(font),
    crabPointsText(font),
    octopusPointsText(font),
	livesLeft(font, std::to_string(playerLives)) {

	setUpHUD();
	setUpCoinMenu();
	setUpTableMenu();
	setUpSprites(resourceManager);
	// TODO: Add game over screen
	startTypingCoinMenu();
	// startTypingTableMenu();
}

std::string UI::scoreToText(int score) {
	std::string strScore = std::to_string(score);

	while (strScore.length() < 4) {
		strScore = "0" + strScore;
	}

	return strScore;
}

// Displays the HUD overlay
void UI::renderHUD(sf::RenderTarget& target, const Player& playerOne, bool showLives) {
	target.draw(p1ScoreText);
	target.draw(p1Score);
	target.draw(p2ScoreText);
	target.draw(highScoreText);
	target.draw(highScoreNum);


	if (showLives) {
		target.draw(livesLeft);
		//	Displays a player sprite for each life left
		for (int i = 0; i < playerOne.getLives() - 1; i++) {
			lifeSprite->setPosition({ LIFE_SPRITE_POS.x + (i * LIFE_SPRITE_SPACING), LIFE_SPRITE_POS.y });
			target.draw(*lifeSprite);
		}
	}
}

void UI::renderCoinMenu(sf::RenderTarget& target) {
	target.draw(insertCoinText);
	target.draw(selectPromptText);
	target.draw(onePlayerText);
	target.draw(twoPlayerText);
}

// Displays the start menu
void UI::renderTableMenu(sf::RenderTarget& target) {
	target.draw(titleTopLine);
	target.draw(titleBottomLine);
	target.draw(scoreTable);
	target.draw(*menuAliensSprites[0]);
	target.draw(*menuAliensSprites[1]);
	target.draw(*menuAliensSprites[2]);
	target.draw(*menuAliensSprites[3]);
	target.draw(ufoPointsText);
	target.draw(squidPointsText);
	target.draw(crabPointsText);
	target.draw(octopusPointsText);
	target.draw(creditsText);
}

void UI::handleMenuInput(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Key::W || key == sf::Keyboard::Key::Up) {
		onePlayerText.setFillColor(LIGHT_GREEN);
		twoPlayerText.setFillColor(sf::Color::White);
	}

	if (key == sf::Keyboard::Key::S || key == sf::Keyboard::Key::Down) {
		onePlayerText.setFillColor(sf::Color::White);
		twoPlayerText.setFillColor(LIGHT_GREEN);
	}
}

// Private Functions
void UI::setUpHUD() {
	// Player 1
	p1ScoreText.setCharacterSize(TEXT_SIZE);
	p1ScoreText.setPosition(P1_SCORE_TEXT_POS);
	p1Score.setString("SCORE<1>");
	p1Score.setCharacterSize(TEXT_SIZE);
	p1Score.setPosition(P1_SCORE_NUM_POS);

	// Player 2
	p2ScoreText.setString("SCORE<2>");
	p2ScoreText.setCharacterSize(TEXT_SIZE);
	p2ScoreText.setPosition(P2_SCORE_TEXT_POS);

	highScoreText.setString("HI-SCORE");
	highScoreText.setCharacterSize(TEXT_SIZE);
	highScoreText.setPosition(HIGH_SCORE_TEXT_POS);
	highScoreNum.setCharacterSize(TEXT_SIZE);
	highScoreNum.setPosition(HIGH_SCORE_NUM_POS);

	livesLeft.setCharacterSize(TEXT_SIZE);
	livesLeft.setPosition(LIVES_LEFT_POS);
}

void UI::setUpCoinMenu() {
	insertCoinText.setString("INSERT   COIN");
	insertCoinText.setCharacterSize(TEXT_SIZE);
	insertCoinText.setPosition(INSERT_COIN_TEXT_POS);

	selectPromptText.setCharacterSize(TEXT_SIZE);
	selectPromptText.setPosition(SELECT_PROMPT_TEXT_POS);

	onePlayerText.setCharacterSize(TEXT_SIZE);
	onePlayerText.setPosition(ONE_PLAYER_TEXT_POS);
	onePlayerText.setFillColor(LIGHT_GREEN);

	twoPlayerText.setCharacterSize(TEXT_SIZE);
	twoPlayerText.setPosition(TWO_PLAYER_TEXT_POS);
}


void UI::setUpTableMenu() {
	titleTopLine.setCharacterSize(TEXT_SIZE);
	titleTopLine.setPosition(TITLE_TOP_LINE_POS);

	titleBottomLine.setCharacterSize(TEXT_SIZE);
	titleBottomLine.setPosition(TITLE_BOTTOM_LINE_POS);

	// scoreTable.setString("*SCORE ADVANCE TABLE*");
	scoreTable.setCharacterSize(TEXT_SIZE);
	scoreTable.setPosition(SCORE_TABLE_POS);

	ufoPointsText.setString("=? MYSTERY");
	ufoPointsText.setCharacterSize(TEXT_SIZE);
	ufoPointsText.setPosition(UFO_POINTS_TEXT_POS);

	squidPointsText.setString("=30 POINTS");
	squidPointsText.setCharacterSize(TEXT_SIZE);
	squidPointsText.setPosition(SQUID_POINTS_TEXT_POS);

	crabPointsText.setString("=20 POINTS");
	crabPointsText.setCharacterSize(TEXT_SIZE);
	crabPointsText.setPosition(CRAB_POINTS_TEXT_POS);

	octopusPointsText.setString("=10 POINTS");
	octopusPointsText.setCharacterSize(TEXT_SIZE);
	octopusPointsText.setPosition(OCTOPUS_POINTS_TEXT_POS);
	octopusPointsText.setFillColor(LIGHT_GREEN);

	creditsText.setString("CREDIT  00");
	creditsText.setCharacterSize(TEXT_SIZE);
	creditsText.setPosition(CREDITS_TEXT_POS);

}


void UI::setUpSprites(ResourceManager& resourceManager) {
	lifeSprite = resourceManager.createSprite("player");
	lifeSprite->setColor(LIGHT_GREEN);

	menuAliensSprites[0] = resourceManager.createSprite("UFO");
	menuAliensSprites[1] = resourceManager.createSprite("squid");
	menuAliensSprites[2] = resourceManager.createSprite("crabTwo");
	menuAliensSprites[3] = resourceManager.createSprite("octopus");

	// UFO
	menuAliensSprites[0]->setPosition(MENU_UFO_POS);
	menuAliensSprites[0]->setScale(MENU_UFO_SCALE);

	// Squid
	menuAliensSprites[1]->setPosition(MENU_SQUID_POS);
	menuAliensSprites[1]->setScale(MENU_SQUID_SCALE);

	// Crab
	menuAliensSprites[2]->setPosition(MENU_CRAB_POS);
	menuAliensSprites[2]->setScale(MENU_CRAB_SCALE);

	// Octopus
	menuAliensSprites[3]->setPosition(MENU_OCTOPUS_POS);
	menuAliensSprites[3]->setScale(MENU_OCTOPUS_SCALE);
	menuAliensSprites[3]->setColor(LIGHT_GREEN);

}

void UI::startTypingCoinMenu() {
	while (!typingQueue.empty()) {
		typingQueue.pop();
	}

	typingQueue.push({ "<1  OR  2 PLAYERS>" , &selectPromptText });
	typingQueue.push({ "*1  PLAYER   1 COIN" , &onePlayerText });
	typingQueue.push({ "*2  PLAYERS  2 COINS", &twoPlayerText });

	startNextText();
}

void UI::startTypingTableMenu() {
	typingQueue.push({ "PLAY" , &titleTopLine });
	typingQueue.push({ "SPACE    INVADERS" , &titleBottomLine });

	


	scoreTable.setString("*SCORE ADVANCE TABLE*");

	startNextText();

	
}

void UI::startNextText() {
	if (typingQueue.empty()) {
		currentTextPtr = nullptr;
		return;
	}

	TextToType next = typingQueue.front();
	typingQueue.pop();

	currentFullText = next.fullText;
	currentTextPtr = next.textPtr;
	charIndex = 0;
	timePassed = 0.0f;
}

void UI::updateTypeWriter(float deltaTime) {
	if (!currentTextPtr) return;

	timePassed += deltaTime;

	while (timePassed >= timePerChar && charIndex < currentFullText.length()) {
		charIndex++;
		timePassed -= timePerChar; 

		// Show more of the full string
		currentTextPtr->setString(currentFullText.substr(0, charIndex));

		// Move to next text to show in the queue
		if (charIndex >= currentFullText.length()) {
			startNextText();
		}
	}
}