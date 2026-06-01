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
	int getLives() const { return lives; }
	Bullet shoot(const ResourceManager& resourceManager);

private:
	int lives;
	std::optional<sf::Sound> shootSound;
};