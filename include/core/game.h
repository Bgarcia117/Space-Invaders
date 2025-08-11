#pragma once
#include <memory>
#include <vector>
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
	bool gameOver;
	int score;

	void initPlayer();
	void initAliens();
};