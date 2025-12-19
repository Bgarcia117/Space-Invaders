#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <UI/ui.h>
#include <managers/resource_manager.h>
#include "game_objects/player.h"

constexpr int TEXT_SIZE = 40; 

// Menu Text Positions
constexpr sf::Vector2f TITLE_TOP_LINE_POS = { 355.f, 204.f };
constexpr sf::Vector2f TITLE_BOTTOM_LINE_POS = { 250.f, 284.f };
constexpr sf::Vector2f SCORE_TABLE_POS = { 195.f, 404.f };
constexpr sf::Vector2f UFO_POINTS_TEXT_POS = { 320.f, 460.f };
constexpr sf::Vector2f SQUID_POINTS_TEXT_POS = { 320.f, 510.f };

// Menu Alien Sprite Positions
constexpr sf::Vector2f MENU_UFO_POS = { 275.f, 480.f };
constexpr sf::Vector2f MENU_SQUID_POS = { 286.f, 525.f };
constexpr sf::Vector2f MENU_CRAB_POS = { 282.f, 575.f };
constexpr sf::Vector2f MENU_OCTOPUS_POS = { 283.f, 625.f };

// Menu Alien Sprite Scales (Scales sprite size)
constexpr sf::Vector2f MENU_UFO_SCALE = { 1.75f, 1.60f };
constexpr sf::Vector2f MENU_SQUID_SCALE = { 1.5f, 1.5f };
constexpr sf::Vector2f MENU_CRAB_SCALE = { 1.37f, 1.35f };
constexpr sf::Vector2f MENU_OCTOPUS_SCALE = { 1.62f, 1.54f };

// In-game HUD Text Positions
// Player 1
constexpr sf::Vector2f P1_SCORE_TEXT_POS = { 115.f, 90.f };
constexpr sf::Vector2f P1_SCORE_POS = { 70.f, 45.f };
// Player 2
constexpr sf::Vector2f P2_SCORE_TEXT_POS = { 520.f, 45.f };

constexpr sf::Vector2f HIGH_SCORE_TEXT_POS = { 320.f, 45.f };
constexpr sf::Vector2f HIGH_SCORE_NUM_POS = { 355.f, 90.f };
constexpr sf::Vector2f LIVES_LEFT_POS = { 65.f, 960.f };
constexpr sf::Vector2f LIFE_SPRITE_POS = { 110.f, 975.f };
constexpr float LIFE_SPRITE_SPACING = 45.f;

UI::UI(ResourceManager& resourceManager, int score, int highScore, int playerLives) 
	: font(resourceManager.getFont()),
	  p1ScoreText(font, scoreToText(score)),
	  p1Score(font),
	  p2ScoreText(font),
	  highScoreText(font),
	  highScoreNum(font, scoreToText(highScore)),
	  titleTopLine(font),
	  titleBottomLine(font),
	  scoreTable(font),
      ufoPointsText(font),
      squidPointsText(font),
      crabPointsText(font),
      octopusPointsText(font),
	  livesLeft(font, std::to_string(playerLives)) {

	setUpMenuText();
	setUpMenuSprites(resourceManager);
	setUpHUD();
	// Add game over screen

}

std::string UI::scoreToText(int score) {
	std::string strScore = std::to_string(score);

	while (strScore.length() < 4) {
		strScore = "0" + strScore;
	}

	return strScore;
}

// Displays the start menu
void UI::renderMenu(sf::RenderTarget& target) {
	target.draw(titleTopLine);
	target.draw(titleBottomLine);
	target.draw(p1ScoreText);
	target.draw(p1Score);
	target.draw(p2ScoreText);
	target.draw(highScoreText);
	target.draw(highScoreNum);
	target.draw(scoreTable);
	target.draw(*menuAliensSprites[0]);
	target.draw(*menuAliensSprites[1]);
	target.draw(*menuAliensSprites[2]);
	target.draw(*menuAliensSprites[3]);
	target.draw(ufoPointsText);
	target.draw(squidPointsText);
}


// Displays the in-game HUD
void UI::renderHUD(sf::RenderTarget& target, const Player& playerOne) {
	target.draw(p1ScoreText);
	target.draw(p1Score);
	target.draw(p2ScoreText);
	target.draw(highScoreText);
	target.draw(highScoreNum);
	target.draw(livesLeft);


	//	Displays a player sprite for each life left
	for (int i = 0; i < playerOne.getLives() - 1; i++) {
		lifeSprite->setPosition({ LIFE_SPRITE_POS.x + (i * LIFE_SPRITE_SPACING), LIFE_SPRITE_POS.y });
		target.draw(*lifeSprite);
	}
}

void UI::setUpMenuText() {
	titleTopLine.setString("PLAY");
	titleTopLine.setCharacterSize(TEXT_SIZE);
	titleTopLine.setPosition(TITLE_TOP_LINE_POS);

	titleBottomLine.setString("SPACE    INVADERS");
	titleBottomLine.setCharacterSize(TEXT_SIZE);
	titleBottomLine.setPosition(TITLE_BOTTOM_LINE_POS);

	scoreTable.setString("*SCORE ADVANCE TABLE*");
	scoreTable.setCharacterSize(TEXT_SIZE);
	scoreTable.setPosition(SCORE_TABLE_POS);

	ufoPointsText.setString("=? MYSTERY");
	ufoPointsText.setCharacterSize(TEXT_SIZE);
	ufoPointsText.setPosition(UFO_POINTS_TEXT_POS);

	squidPointsText.setString("=30 POINTS");
	squidPointsText.setCharacterSize(TEXT_SIZE);
	squidPointsText.setPosition(SQUID_POINTS_TEXT_POS);

	/*
	crabPointsText.setString("=20 POINTS");
	crabPointsText.setCharacterSize(TEXT_SIZE);

	octopusPointsText.setString("10 POINTS");
	octopusPointsText.setCharacterSize(TEXT_SIZE);
	*/
}



void UI::setUpMenuSprites(ResourceManager& resourceManager) {
	lifeSprite = resourceManager.createSprite("player");

	menuAliensSprites[0] = resourceManager.createSprite("UFO");
	menuAliensSprites[1] = resourceManager.createSprite("squid");
	menuAliensSprites[2] = resourceManager.createSprite("crabTwo");
	menuAliensSprites[3] = resourceManager.createSprite("octopus");

	// UFO
	menuAliensSprites[0]->setPosition(MENU_UFO_POS);
	menuAliensSprites[0]->setScale(MENU_UFO_SCALE);
	// TODO: Fix colors: menuAliensSprites[0]->setColor(sf::Color::White);

	// Squid
	menuAliensSprites[1]->setPosition(MENU_SQUID_POS);
	menuAliensSprites[1]->setScale(MENU_SQUID_SCALE);

	// Crab
	menuAliensSprites[2]->setPosition(MENU_CRAB_POS);
	menuAliensSprites[2]->setScale(MENU_CRAB_SCALE);

	// Octopus
	menuAliensSprites[3]->setPosition(MENU_OCTOPUS_POS);
	menuAliensSprites[3]->setScale(MENU_OCTOPUS_POS);


	
}

void UI::setUpHUD() {
	// Player 1
	p1ScoreText.setCharacterSize(TEXT_SIZE); 
	p1ScoreText.setPosition(P1_SCORE_TEXT_POS);
	p1Score.setString("SCORE< 1 >"); // TODO: Swap score and score text
	p1Score.setCharacterSize(TEXT_SIZE);
	p1Score.setPosition(P1_SCORE_POS);

	// Player 2
	p2ScoreText.setString("SCORE< 2 >");
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