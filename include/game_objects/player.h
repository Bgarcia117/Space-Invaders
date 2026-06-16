#pragma once
#include "core/game_object.h"
#include "managers/resource_manager.h"
#include "game_objects/bullet.h"
#include <SFML/Audio.hpp>
#include <optional>

class Player : public GameObject {
public:
	Player(const ResourceManager& resourceManager, sf::Vector2f position);
	void update(float deltaTime) override;
	void move(sf::Vector2f offset) override;
	int getLives() const { return lives; }
	void loseLife() { if (lives > 0) lives--; }
	void resetLives() { lives = 3; }
	Bullet shoot(const ResourceManager& resourceManager);

	void kill();
	bool isDying() const { return dying; }
	bool isDead() const { return dying && deathTimer <= 0.0f; }
	void respawn(sf::Vector2f position);
	const sf::Sprite& getCurrentSprite() const;


private:
	enum class SpriteState { ALIVE, DEATH_ONE, DEATH_TWO };
	int lives;
	std::optional<sf::Sound> shootSound;

	SpriteState spriteState;
	std::optional<sf::Sprite> deathSpriteOne;
	std::optional<sf::Sprite> deathSpriteTwo;
	bool dying;
	float deathTimer;
	float spriteFlipTimer;

};