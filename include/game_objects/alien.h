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
	void move() override;

private:
	AlienType type;
	int pointValue;

	std::string getSpriteKey(AlienType type);
	int getPointValue(AlienType type);
};