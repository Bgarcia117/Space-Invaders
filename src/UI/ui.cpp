#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <UI/ui.h>
#include <managers/resource_manager.h>
#include "game_objects/player.h"

constexpr sf::Vector2f LIFE_SPRITE_POS = { 110.f, 975.f };
constexpr float LIFE_SPRITE_SPACING = 45.f;

UI::UI(ResourceManager& resourceManager, int score, int highScore, int playerLives) 
	: font(resourceManager.getFont()),
	  titleTopLine(font),
	  titleBottomLine(font),
	  scoreTable(font),
	  p1ScoreText(font, scoreToText(score)),
	  p1Score(font),
	  p2ScoreText(font),
	  highScoreText(font),
	  highScoreNum(font, scoreToText(highScore)),
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
	titleTopLine.setCharacterSize(40);
	titleTopLine.setPosition({ 355.f, 204.f });

	titleBottomLine.setString("SPACE    INVADERS");
	titleBottomLine.setCharacterSize(40);
	titleBottomLine.setPosition({ 250.f, 284.f });

	scoreTable.setString("*SCORE ADVANCE TABLE*");
	scoreTable.setCharacterSize(40);
	scoreTable.setPosition({ 200.f, 404 });


}



void UI::setUpMenuSprites(ResourceManager& resourceManager) {
	lifeSprite = resourceManager.createSprite("player");
	menuAliensSprites[0] = resourceManager.createSprite("UFO");
	menuAliensSprites[1] = resourceManager.createSprite("squid");
	menuAliensSprites[2] = resourceManager.createSprite("crab");
	menuAliensSprites[3] = resourceManager.createSprite("octopus");

	menuAliensSprites[0]->setPosition({ 500.f, 500.f });
	menuAliensSprites[0]->setColor(sf::Color::White);
	menuAliensSprites[1]->setPosition({ 500.f, 550.f });
	menuAliensSprites[2]->setPosition({ 500.f, 600.f });
	menuAliensSprites[3]->setPosition({ 500.f, 650.f });


	sf::Color spriteColor = menuAliensSprites[0]->getColor();
	std::cout << "Color of UFO: " << static_cast<int>(spriteColor.r) << ", " << static_cast<int>(spriteColor.g) << ", " << static_cast<int>(spriteColor.b) << std::endl;
}





void UI::setUpHUD() {
	// Player 1
	p1ScoreText.setCharacterSize(40); 
	p1ScoreText.setPosition({ 115.f, 90.f });
	p1Score.setString("SCORE< 1 >"); // TODO: Swap score and score text
	p1Score.setCharacterSize(40);
	p1Score.setPosition({ 70.f, 45.f });

	// Player 2
	p2ScoreText.setString("SCORE< 2 >");
	p2ScoreText.setCharacterSize(40);
	p2ScoreText.setPosition({ 520.f, 45.f });

	highScoreText.setString("HI-SCORE");
	highScoreText.setCharacterSize(40);
	highScoreText.setPosition({ 320.f, 45.f });
	highScoreNum.setCharacterSize(40);
	highScoreNum.setPosition({ 355.f, 90.f });

	livesLeft.setCharacterSize(40);
	livesLeft.setPosition({ 65.f, 960.f });
}