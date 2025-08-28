#pragma once
#include "core/game_object.h"
#include "managers/resource_manager.h"

constexpr sf::Vector2f PLAYER_START_POS = { 500.f, 500.f };

class Player : public GameObject {
public:
	Player(const ResourceManager& resourceManager, sf::Vector2f position = PLAYER_START_POS);
	void update(float deltaTime) override;

private:
	int lives;
};