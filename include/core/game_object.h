#pragma once
#include <string>
#include <optional>

#include <SFML/Graphics.hpp>

#include "managers/resource_manager.h"

class GameObject {
public:
	GameObject(const ResourceManager& spriteManager, const std::string& textureKey, sf::Vector2f scaler);
	virtual void move() = 0;
	void setPosition(sf::Vector2f pos);
	const sf::Sprite& getSprite() const; // For testing to draw

private:
	std::optional<sf::Sprite> sprite;
	// sf::Vector2f position;

};