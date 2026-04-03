#pragma once
#include <memory>
#include <vector>
#include <string>
#include <optional>
#include <SFML/Graphics.hpp>
#include "managers/resource_manager.h"
#include "game_objects/alien.h"
#include "game_objects/player.h"
#include "game_objects/bullet.h"
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
	std::vector<Bullet> bullets;
	std::optional<Alien> ufo;
	GameState gameState = GameState::COINMENU;
	alienDirection aliensDirection = alienDirection::RIGHT;

	bool gameOver = false;
	int score = 0;
	int highScore = 0;
	int alienMoveCounter = 0;
	float alienMoveTimer = 0.f;
	int aliensMoved = 0;

	// UFO Variables
	int playerShotCount = 0;
	int ufoScoreThreshold = 23;
	float ufoSpawnTimer = 25.6f;

	UI ui;

	void initAliens();
	void moveAliens(std::vector<Alien>& aliens, float deltaTime);
	void updateUFOTimer(float deltaTime);
	void spawnUFO();
	void checkBulletAlienCollision();
	std::string convertScore(int score);
};