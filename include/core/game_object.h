#pragma once
#include <string>
#include <optional>
#include <SFML/Graphics.hpp>
#include "managers/resource_manager.h"
#include "resource_ids.h"

struct GameObjectConfig {
	std::string textureKey;
	sf::Vector2f size;
	sf::Vector2f position;
};

class GameObject {
public:
	GameObject(ResourceManager& spriteManager, GameObjectConfig& config);
	const sf::Sprite& getSprite() const;
	virtual void move() = 0;

private:
	std::optional<sf::Sprite> sprite;
};