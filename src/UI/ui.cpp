#include <string>
#include <SFML/Graphics.hpp>
#include <UI/ui.h>
#include <managers/resource_manager.h>

UI::UI(ResourceManager& resourceManager, int score, int highScore, int playerLives) 
	: p1ScoreText(resourceManager.getFont(), scoreToText(score)),
	  p1Score(resourceManager.getFont(), "SCORE< 1 >"),
	  p2ScoreText(resourceManager.getFont(), "SCORE< 2 >"),
	  highScoreText(resourceManager.getFont(), "HI-SCORE"),
	  highScoreNum(resourceManager.getFont(), scoreToText(highScore)),
	  livesLeft(resourceManager.getFont(), std::to_string(playerLives)) { // Pass through Player.getLives()
	
	// Configure Start Menu Text


	// Configure in-game HUD
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
	livesLeft.setPosition({ 65.f, 960.f });

	// Configure game over screen


}

std::string UI::scoreToText(int score) {
	std::string strScore = std::to_string(score);

	while (strScore.length() < 4) {
		strScore = "0" + strScore;
	}

	return strScore;
}

void UI::renderMenu(sf::RenderTarget& target) {
	target.draw(p1ScoreText);
	target.draw(p1Score);
	target.draw(p2ScoreText);
	target.draw(highScoreText);
	target.draw(highScoreNum);
	target.draw(livesLeft);
}