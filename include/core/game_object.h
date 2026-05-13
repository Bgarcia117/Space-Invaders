#pragma once
#include <string>
#include <optional>

#include <SFML/Graphics.hpp>

#include "managers/resource_manager.h"

class GameObject {
public:
	GameObject(const ResourceManager& resourceManager, const std::string& spriteKey, sf::Vector2f position);

	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	virtual void move(sf::Vector2f offset);

	void setSpriteColor(sf::Color color);
	const sf::Sprite& getSprite() const;

	virtual void update(float deltaTime) = 0;

	bool collidesWith(const GameObject& object);

private:
	std::optional<sf::Sprite> sprite;
	// sf::Vector2f position;

};