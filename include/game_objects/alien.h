#pragma once
#include <SFML/Graphics.hpp> // Testing
#include <optional> // Testing
#include "core/game_object.h"
#include "managers/resource_manager.h"

class Alien : public GameObject {
public:
	Alien(const ResourceManager& resourceManager);
	void move() override;

private:
	std::optional<sf::Sprite> sprite;
};