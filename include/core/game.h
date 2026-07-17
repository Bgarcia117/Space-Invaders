#pragma once
#include <vector>
#include <string>
#include <optional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "managers/resource_manager.h"
#include "game_objects/alien.h"
#include "game_objects/player.h"
#include "game_objects/bullet.h"
#include "game_objects/barrier.h"
#include <UI/ui.h>

enum GameState { COINMENU, TABLEMENU, PLAYING, GAMEOVER, ROUNDWON };

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
	std::vector<Barrier> barriers;
	std::optional<Alien> ufo;
	std::optional<sf::Sound> ufoSound;
	std::optional<sf::Sound> alienExplosionSound;
	std::optional<sf::Sound> playerDeathSound;
	std::optional<sf::Sound> ufoDeathSound;
	GameState gameState = GameState::COINMENU;
	alienDirection aliensDirection = alienDirection::RIGHT;

	int score = 0;
	int highScore = 0;
	float alienMoveTimer = 0.f;
	int nextAlienToMove = 0;

	// UFO Variables
	int playerShotCount = 0;
	int ufoScoreThreshold = 23;
	float ufoSpawnTimer = 25.6f;
	float ufoDirection = 1.f;
	float ufoScoreTextTimer = 0.0f;
	int lastUFOScore = 0;
	std::optional<sf::Text> ufoScoreText;


	float alienShootTimer = 1.0f;
	float alienShootInterval = 1.0f;

	UI ui;

	void initAliens();
	void moveAliens(std::vector<Alien>& aliens, float deltaTime);
	void initBarriers();
	void updateUFOTimer(float deltaTime);
	void spawnUFO();
	int getUFOScore() const;
	void checkBulletAlienCollision();
	void checkBulletPlayerCollision();
	void checkBulletBarrierCollision();
	void updateAlienShots(float deltaTime);
	std::string convertScore(int score);
	void resetGame();
	bool aliensReachedGround() const;
};