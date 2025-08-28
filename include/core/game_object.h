#pragma once
#include <string>
#include <optional>

#include <SFML/Graphics.hpp>

#include "managers/resource_manager.h"

class GameObject {
public:
	GameObject(const ResourceManager& resourceManager, const std::string& spriteKey, sf::Vector2f position);

	void setPosition(sf::Vector2f pos);
	virtual void move(sf::Vector2f offset);
	const sf::Sprite& getSprite() const;

	virtual void update(float deltaTime) = 0;


private:
	std::optional<sf::Sprite> sprite;
	// sf::Vector2f position;

};