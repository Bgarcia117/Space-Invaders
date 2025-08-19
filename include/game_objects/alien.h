#pragma once
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
	void move() override;
	const sf::Sprite& getCurrentSprite() const;

private:
	std::optional<sf::Sprite> sprite2;
	AlienType type;
	int pointValue;
	bool useSprite1;
	float spriteFlipTimer;

	std::string getSpriteKey(AlienType type);
	std::string getNextSpriteKey(AlienType type); // Gets second position sprite key
	int getPointValue(AlienType type);
};