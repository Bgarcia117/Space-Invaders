#include <string>
#include <SFML/Graphics.hpp>
#include "core/game_object.h"
#include "managers/resource_manager.h"

GameObject::GameObject(const ResourceManager& resourceManager, const std::string& spriteKey, 
	                   const sf::Vector2f position) {

	const SpriteConfig& spriteConfig = resourceManager.getSpriteConfig(spriteKey);
	const sf::Texture& texture = resourceManager.getTexture(spriteConfig.textureKey);

	// Load Texure onto sprite
	sprite.emplace(texture);
	sprite->setTextureRect(spriteConfig.textureRect);
	sprite->setScale(spriteConfig.scale);
	sprite->setPosition({position});
}


void GameObject::setPosition(sf::Vector2f pos) {
	if (!sprite.has_value()) {
		std::cerr << "Sprite has not been initializied!" << std::endl;
	}

	sprite->setPosition(pos);
}

void GameObject::setSpriteColor(sf::Color color) {
	sprite->setColor(color);
}

void GameObject::move(sf::Vector2f offset) {
	if (!sprite.has_value()) {
		std::cerr << "Sprite has not been initializied!" << std::endl;
	}

	sprite->move({offset.x, offset.y});
}

const sf::Sprite& GameObject::getSprite() const {
	if (!sprite.has_value()) {
		std::cerr << "Texture has not been loaded!" << std::endl;
	}

	return *sprite;
}