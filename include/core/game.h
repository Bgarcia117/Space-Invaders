#pragma once
#include <memory>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "managers/resource_manager.h"
#include "game_objects/alien.h"
#include "game_objects/player.h"

enum GameState { MENU, PLAYING, GAMEOVER };

class Game {
public:
	Game();
	void init();
	void begin();
	void update(sf::RenderTarget& target);

private:
	ResourceManager resourceManager;
	Player player;
	std::vector<Alien> aliens;
	GameState gameState = GameState::MENU;

	bool gameOver = false;
	int score = 0;
	int highScore = 0;

	sf::Text p1ScoreText;
	sf::Text p1Score;
	sf::Text p2ScoreText;
	sf::Text highScoreText;
	sf::Text highScoreNum;

	void initPlayer();
	void initAliens();
	std::string convertScore(int score);
};