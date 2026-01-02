#pragma once
#include <memory>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "managers/resource_manager.h"
#include "game_objects/alien.h"
#include "game_objects/player.h"
#include <UI/ui.h>

enum GameState { COINMENU, TABLEMENU, PLAYING, GAMEOVER };

class Game {
public:
	Game();
	void init();
	void begin();
	void update(sf::RenderTarget& target, float deltaTime);
	void render(sf::RenderTarget& target, float deltaTime);
	void handleInput(const sf::Event& event);

private:
	enum alienDirection {LEFT, RIGHT, DOWN};

	ResourceManager resourceManager;
	
	Player player;
	std::vector<Alien> aliens;
	GameState gameState = GameState::COINMENU;
	alienDirection aliensDirection = alienDirection::RIGHT;

	bool gameOver = false;
	int score = 0;
	int highScore = 0;
	int alienMoveCounter = 0;
	float alienMoveTimer = 0.f;
	int aliensMoved = 0;

	UI ui;

	void initAliens();
	void moveAliens(std::vector<Alien>& aliens, float deltaTime);
	void movePlayer(float deltaTime);
	std::string convertScore(int score);
};