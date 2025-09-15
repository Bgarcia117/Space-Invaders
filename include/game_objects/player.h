#pragma once
#include "core/game_object.h"
#include "managers/resource_manager.h"

class Player : public GameObject {
public:
	Player(const ResourceManager& resourceManager, sf::Vector2f position);
	void update(float deltaTime) override;

private:
	int lives;
};