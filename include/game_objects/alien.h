#pragma once
#include <coroutine>
#include <SFML/Graphics.hpp>
#include "core/game_object.h"
#include "managers/resource_manager.h"

enum class AlienType {
	SQUID,
	CRAB,
	OCTOPUS,
	UFO
};

class Alien : public GameObject {
public:
	Alien(const ResourceManager& resourceManager, AlienType alienType, sf::Vector2f position);
	void update(float deltaTime) override;
	void move(sf::Vector2f offset) override;
	const sf::Sprite& getCurrentSprite() const;
	bool isDying() const { return dying; }
	void kill() { dying = true; }

private:
	enum class SpriteState { ARMSUP, ARMSDOWN, DEATH };
	SpriteState spritesState;
	std::optional<sf::Sprite> sprite2;
	std::optional<sf::Sprite> deathSprite;
	AlienType type;
	int pointValue;
	bool dying;
	float spriteFlipTimer;

	std::string getSpriteKey(AlienType type);
	std::string getNextSpriteKey(AlienType type); // Gets second position sprite key
	int getPointValue(AlienType type);
};